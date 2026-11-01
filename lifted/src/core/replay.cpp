#include "replay.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iostream>

namespace lf2 {

bool control_config_t::load_from_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false;
    }

    // 0x004234D0: Read 11 keys for 4 players
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (size_t k = 0; k < KEYS_PER_PLAYER; ++k) {
            if (!(file >> player_keys[p][k])) {
                return false;
            }
        }
    }

    // 0x00423510: Read 4 player names
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        std::string raw_name;
        if (!(file >> raw_name)) {
            return false;
        }
        // Authentic LF2: convert '`' to space ' ' (0x0042353A)
        for (char& c : raw_name) {
            if (c == '`') c = ' ';
        }
        player_names[p] = raw_name;
    }

    // 0x0042356B: Read demo & replay mode flags
    file >> demo_mode;
    file >> replay_mode;

    return true;
}

bool control_config_t::save_to_file(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        return false;
    }

    // 0x004233E0: Write 11 keys per player
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (size_t k = 0; k < KEYS_PER_PLAYER; ++k) {
            file << player_keys[p][k] << "\n";
        }
    }

    // Write 4 player names (convert ' ' to '`')
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        std::string encoded = player_names[p];
        if (encoded.empty()) encoded = "Player";
        for (char& c : encoded) {
            if (c == ' ') c = '`';
        }
        file << encoded << (p == MAX_CONTROL_PLAYERS - 1 ? "\n" : " ");
    }

    file << demo_mode << "\n";
    file << replay_mode << "\n";

    return true;
}

replay_recorder_t::replay_recorder_t() = default;
replay_recorder_t::~replay_recorder_t() {
    if (m_recording) {
        finish_recording();
    }
}

std::string replay_recorder_t::generate_filename(int mode, int stage) {
    time_t rawtime;
    time(&rawtime);
    struct tm* t = localtime(&rawtime);

    char buf[128];
    // 0x0042D09F: "%4d%02d%02d_%02d%02d%02d"
    snprintf(buf, sizeof(buf), "%04d%02d%02d_%02d%02d%02d",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);

    std::string filename = buf;
    if (mode == 1) { // Stage Mode
        if (stage >= 5) {
            filename += "_Survival";
        } else {
            filename += "_Stage_" + std::to_string(stage + 1);
        }
    } else {
        filename += "_VS";
    }

    filename += ".lfr";
    return filename;
}

bool replay_recorder_t::start_recording(const replay_header_t& header, const std::string& filepath) {
    m_header = header;
    m_header.magic = LF2_REPLAY_MAGIC;
    m_header.total_frames = 0;
    m_filepath = filepath;
    m_frames.clear();
    m_recording = true;
    return true;
}

void replay_recorder_t::record_frame(const uint8_t player_inputs[8], uint8_t control_flags) {
    if (!m_recording) return;

    replay_frame_t frame{};
    std::memcpy(frame.inputs, player_inputs, sizeof(frame.inputs));
    frame.control_flags = control_flags;
    m_frames.push_back(frame);
}

bool replay_recorder_t::finish_recording() {
    if (!m_recording) return false;

    m_header.total_frames = static_cast<uint32_t>(m_frames.size());

    std::ofstream out(m_filepath, std::ios::binary);
    if (!out.is_open()) {
        m_recording = false;
        return false;
    }

    out.write(reinterpret_cast<const char*>(&m_header), sizeof(m_header));
    if (!m_frames.empty()) {
        out.write(reinterpret_cast<const char*>(m_frames.data()),
                  m_frames.size() * sizeof(replay_frame_t));
    }

    out.close();
    m_recording = false;
    return true;
}

void replay_recorder_t::cancel_recording() {
    m_frames.clear();
    m_recording = false;
}

replay_player_t::replay_player_t() = default;
replay_player_t::~replay_player_t() {
    close();
}

bool replay_player_t::open_replay(const std::string& filepath) {
    close();

    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    if (!in.read(reinterpret_cast<char*>(&m_header), sizeof(m_header))) {
        return false;
    }

    if (m_header.magic != LF2_REPLAY_MAGIC) {
        return false;
    }

    m_frames.resize(m_header.total_frames);
    if (m_header.total_frames > 0) {
        if (!in.read(reinterpret_cast<char*>(m_frames.data()),
                     m_header.total_frames * sizeof(replay_frame_t))) {
            return false;
        }
    }

    m_loaded = true;
    m_current_frame = 0;
    return true;
}

bool replay_player_t::read_frame(uint8_t out_inputs[8], uint8_t& out_flags) {
    if (!m_loaded || m_current_frame >= m_frames.size()) {
        return false;
    }

    const auto& frame = m_frames[m_current_frame++];
    std::memcpy(out_inputs, frame.inputs, 8);
    out_flags = frame.control_flags;
    return true;
}

void replay_player_t::close() {
    m_loaded = false;
    m_frames.clear();
    m_current_frame = 0;
}

} // namespace lf2

