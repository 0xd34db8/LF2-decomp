#include "replay.h"
#include "core/global.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <zlib.h>

namespace lf2 {

// Authentic LF2 v2.0 Secondary Obfuscation Cipher Key (0x0044D7A0)
// Exactly 1,345 characters in the .data section of lf2.exe (SHA256: a1e3e58e52cb7091bff6e1ea7ed8e14274b882f51134af69ca4ce0a72cc8613b)
const char REPLAY_CIPHER_KEY[1346] =
    "1545661123545613454563115345689405689745604785048986746544565456136456245431"
    "2533445678979896784059687456091782394756456465544556446655457455664756448745"
    "2745645562344562436545143854546475674965478568456745653456544839758943486789"
    "4576845120873105456014566402435664056405766456778981904859018359719402875091"
    "2712309585959025903485028490134472190217021375815872018620461270456072816578"
    "6150742721078651876510768150401865107486150745189750163541864518675018675018"
    "6745018674745604785048986746544565456136456245431253344567897989678405968745"
    "6091782393095859590259034850284901344721902170213758158720186204612704560728"
    "1657861507427210786518762436545143854546475674965478568456745653456544839758"
    "9434867894576846134545631153456894056897456047850489867465445654561364562454"
    "3125334456789798967840596874560917823947564564655445564466554574556647564487"
    "4527456455623445624365451438545464756749654785684567456534565448397589434867"
    "8945768451208731054560145664024356640564057664567789819048590183597194028750"
    "9127123095859590259034850284901344721902170213758158720186204612704560728165"
    "7861507427210786518765107681504018651074861507451897501635418645186750186750"
    "1867450186747456047850489867465445654561364562454312533445678979896784059687"
    "4560917823930958595902590348502849013447219021702137581587201862046127045607"
    "28165786150742721078651876243654514385454647567496547";

// 1:1 Parity with 0x0043DD60 secondary obfuscation cipher encryption
void replay_cipher_encrypt(uint8_t* buffer, size_t size) {
    if (!buffer || size == 0) return;
    constexpr size_t key_len = sizeof(REPLAY_CIPHER_KEY) - 1; // 1345 bytes
    size_t n = std::min(size, key_len);
    for (size_t i = 0; i < n; ++i) {
        buffer[i] = static_cast<uint8_t>(buffer[i] + static_cast<uint8_t>(REPLAY_CIPHER_KEY[i]) - 0x30);
    }
}

// 1:1 Parity with 0x0043E620 secondary obfuscation cipher decryption
void replay_cipher_decrypt(uint8_t* buffer, size_t size) {
    if (!buffer || size == 0) return;
    constexpr size_t key_len = sizeof(REPLAY_CIPHER_KEY) - 1; // 1345 bytes
    size_t n = std::min(size, key_len);
    for (size_t i = 0; i < n; ++i) {
        buffer[i] = static_cast<uint8_t>(buffer[i] - static_cast<uint8_t>(REPLAY_CIPHER_KEY[i]) + 0x30);
    }
}

// Zlib deflation and inflation pipeline for replay streams
bool compress_replay_stream(const uint8_t* src, size_t src_len, std::vector<uint8_t>& out_compressed) {
    if (!src || src_len == 0) return false;
    uLong bound = compressBound(static_cast<uLong>(src_len));
    out_compressed.resize(bound);
    uLongf comp_len = bound;
    int ret = compress(reinterpret_cast<Bytef*>(out_compressed.data()), &comp_len,
                       reinterpret_cast<const Bytef*>(src), static_cast<uLong>(src_len));
    if (ret != Z_OK) {
        out_compressed.clear();
        return false;
    }
    out_compressed.resize(comp_len);
    return true;
}

bool decompress_replay_stream(const uint8_t* src, size_t src_len, std::vector<uint8_t>& out_decompressed, size_t max_uncompressed_size) {
    if (!src || src_len == 0) return false;
    out_decompressed.resize(max_uncompressed_size);
    uLongf uncomp_len = static_cast<uLongf>(max_uncompressed_size);
    int ret = uncompress(reinterpret_cast<Bytef*>(out_decompressed.data()), &uncomp_len,
                         reinterpret_cast<const Bytef*>(src), static_cast<uLong>(src_len));
    if (ret != Z_OK) {
        out_decompressed.clear();
        return false;
    }
    out_decompressed.resize(uncomp_len);
    return true;
}

// VERIFIED: LF2 0x00423480
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

    // 0x00423590: Read 3 profile strings (Name, Email, Info)
    std::string dummy;
    std::getline(file, dummy);
    if (std::getline(file, profile_name)) {
        if (!profile_name.empty() && profile_name.back() == '\r') profile_name.pop_back();
    }
    if (std::getline(file, profile_email)) {
        if (!profile_email.empty() && profile_email.back() == '\r') profile_email.pop_back();
    }
    if (std::getline(file, profile_info)) {
        if (!profile_info.empty() && profile_info.back() == '\r') profile_info.pop_back();
    }

    return true;
}

// VERIFIED: LF2 0x00423230
bool control_config_t::save_to_file(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        return false;
    }

    // 0x00423230: Write 11 space-separated keys per player line
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (size_t k = 0; k < KEYS_PER_PLAYER; ++k) {
            file << player_keys[p][k] << (k == KEYS_PER_PLAYER - 1 ? "\n" : " ");
        }
    }

    // Write 4 player names (convert ' ' to '`')
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        std::string encoded = player_names[p];
        if (encoded.empty()) encoded = "Player";
        for (char& c : encoded) {
            if (c == ' ') c = '`';
        }
        file << encoded << "\n";
    }

    file << demo_mode << "\n";
    file << replay_mode << "\n";
    file << profile_name << "\n";
    file << profile_email << "\n";
    file << profile_info << "\n";

    return true;
}

void replay_backup_state_t::write_to_block(std::vector<uint8_t>& block) const {
    if (block.size() < AUTHENTIC_LFR_BLOCK_SIZE) {
        block.resize(AUTHENTIC_LFR_BLOCK_SIZE, 0);
    }
    int32_t* u32 = reinterpret_cast<int32_t*>(block.data());
    u32[0] = difficulty;
    u32[AUTHENTIC_LFR_UNLOCK1_OFFSET / 4] = unlock_chars;
    u32[AUTHENTIC_LFR_UNLOCK2_OFFSET / 4] = unlock_fkeys;
    for (int i = 0; i < 8; ++i) {
        char* dst = reinterpret_cast<char*>(block.data() + 0x14C + i * 11);
        std::memset(dst, 0, 11);
        std::strncpy(dst, player_names[i].c_str(), 10);
    }
    std::memset(block.data() + 0x630BC0, 0, 100);
    std::strncpy(reinterpret_cast<char*>(block.data() + 0x630BC0), profile_name.c_str(), 99);
    std::memset(block.data() + 0x630C24, 0, 400);
    std::strncpy(reinterpret_cast<char*>(block.data() + 0x630C24), profile_info.c_str(), 399);
    std::memset(block.data() + 0x630DB4, 0, 100);
    std::strncpy(reinterpret_cast<char*>(block.data() + 0x630DB4), profile_email.c_str(), 99);
}

// VERIFIED: LF2 0x0043df00
void replay_backup_state_t::restore_from_block(const std::vector<uint8_t>& block) {
    if (block.size() < AUTHENTIC_LFR_BLOCK_SIZE) return;
    const int32_t* u32 = reinterpret_cast<const int32_t*>(block.data());
    difficulty = u32[0];
    unlock_chars = u32[AUTHENTIC_LFR_UNLOCK1_OFFSET / 4];
    unlock_fkeys = u32[AUTHENTIC_LFR_UNLOCK2_OFFSET / 4];
    for (int i = 0; i < 8; ++i) {
        const char* src = reinterpret_cast<const char*>(block.data() + 0x14C + i * 11);
        char tmp[12] = {0};
        std::memcpy(tmp, src, 11);
        player_names[i] = tmp;
    }
    char name_buf[101] = {0};
    std::memcpy(name_buf, block.data() + 0x630BC0, 100);
    profile_name = name_buf;
    char info_buf[401] = {0};
    std::memcpy(info_buf, block.data() + 0x630C24, 400);
    profile_info = info_buf;
    char email_buf[101] = {0};
    std::memcpy(email_buf, block.data() + 0x630DB4, 100);
    profile_email = email_buf;
}

int32_t compute_active_hp_sum(const global_t& world) {
    int32_t hp_sum = 0;
    for (int i = 0; i < 20; ++i) {
        if (world.is_object_exists[i] == 1 && world.objects[i] != nullptr) {
            hp_sum += world.objects[i]->hp;
        }
    }
    return hp_sum;
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

bool replay_recorder_t::start_recording(const replay_header_t& header, const std::string& filepath, bool compress) {
    m_header = header;
    m_header.magic = LF2_REPLAY_MAGIC;
    m_header.total_frames = 0;
    m_filepath = filepath;
    m_compress = compress;
    m_authentic_v2 = false;
    m_authentic_frame_count = 0;
    m_raw_block.clear();
    m_frames.clear();
    m_recording = true;
    return true;
}

bool replay_recorder_t::start_authentic_recording(int32_t difficulty, int32_t game_mode, int32_t unlock_chars, int32_t unlock_fkeys, const std::string& filepath) {
    m_filepath = filepath;
    m_compress = true;
    m_authentic_v2 = true;
    m_authentic_frame_count = 0;
    m_frames.clear();
    m_raw_block.assign(AUTHENTIC_LFR_BLOCK_SIZE, 0);
    int32_t* u32 = reinterpret_cast<int32_t*>(m_raw_block.data());
    u32[0] = difficulty;
    u32[2] = unlock_chars;
    u32[3] = unlock_fkeys;
    u32[0x52] = game_mode;
    m_recording = true;
    return true;
}

void replay_recorder_t::record_frame(const uint8_t player_inputs[8], uint8_t control_flags) {
    if (!m_recording) return;

    if (m_authentic_v2) {
        replay_frame_10_t rec{};
        std::memcpy(rec.inputs, player_inputs, 8);
        rec.func_flags = control_flags;
        record_frame_10(rec, 0);
        return;
    }

    replay_frame_t frame{};
    std::memcpy(frame.inputs, player_inputs, sizeof(frame.inputs));
    frame.control_flags = control_flags;
    m_frames.push_back(frame);
}

// VERIFIED: LF2 0x0043db40
bool replay_recorder_t::record_frame_10(const replay_frame_10_t& rec, int32_t active_hp_sum) {
    if (!m_recording) return false;
    if (!m_authentic_v2) {
        replay_frame_t frame{};
        std::memcpy(frame.inputs, rec.inputs, 8);
        frame.control_flags = rec.func_flags;
        m_frames.push_back(frame);
        return true;
    }
    if (m_authentic_frame_count >= AUTHENTIC_LFR_MAX_FRAMES) {
        m_recording = false;
        return false;
    }

    // 0x0043DB40: Write 10-byte record to +0x2B38 + frame * 10
    size_t dst_off = AUTHENTIC_LFR_FRAMES_OFFSET + m_authentic_frame_count * 10;
    std::memcpy(m_raw_block.data() + dst_off, &rec, 10);

    // 0x0041D65C: Write 150-frame periodic active-HP sum at +0x14B8 + (frame / 150) * 4
    if ((m_authentic_frame_count % AUTHENTIC_LFR_HP_INTERVAL) == 0) {
        size_t sum_off = AUTHENTIC_LFR_HP_CHECKSUM_OFFSET + (m_authentic_frame_count / AUTHENTIC_LFR_HP_INTERVAL) * 4;
        std::memcpy(m_raw_block.data() + sum_off, &active_hp_sum, sizeof(int32_t));
    }

    m_authentic_frame_count++;
    return true;
}

// VERIFIED: LF2 0x0043dd60
bool replay_recorder_t::finish_recording() {
    if (!m_recording) return false;

    std::ofstream out(m_filepath, std::ios::binary);
    if (!out.is_open()) {
        m_recording = false;
        return false;
    }

    if (m_authentic_v2) {
        std::vector<uint8_t> comp;
        if (!compress_replay_stream(m_raw_block.data(), m_raw_block.size(), comp)) {
            out.close();
            m_recording = false;
            return false;
        }
        replay_cipher_encrypt(comp.data(), comp.size());
        uint32_t comp_sz = static_cast<uint32_t>(comp.size());
        out.write(reinterpret_cast<const char*>(&comp_sz), sizeof(comp_sz));
        out.write(reinterpret_cast<const char*>(comp.data()), comp.size());
        out.close();
        m_recording = false;
        return true;
    }

    m_header.total_frames = static_cast<uint32_t>(m_frames.size());

    if (m_compress) {
        // Build uncompressed stream: header + frames
        size_t uncomp_sz = sizeof(m_header) + m_frames.size() * sizeof(replay_frame_t);
        std::vector<uint8_t> uncomp(uncomp_sz);
        std::memcpy(uncomp.data(), &m_header, sizeof(m_header));
        if (!m_frames.empty()) {
            std::memcpy(uncomp.data() + sizeof(m_header),
                        m_frames.data(),
                        m_frames.size() * sizeof(replay_frame_t));
        }

        // Deflate stream using zlib
        std::vector<uint8_t> comp;
        if (!compress_replay_stream(uncomp.data(), uncomp.size(), comp)) {
            out.close();
            m_recording = false;
            return false;
        }

        // Apply authentic secondary cipher (0x0043DD60)
        replay_cipher_encrypt(comp.data(), comp.size());

        // Write 4-byte compressed size followed by encrypted deflated stream
        uint32_t comp_sz = static_cast<uint32_t>(comp.size());
        out.write(reinterpret_cast<const char*>(&comp_sz), sizeof(comp_sz));
        out.write(reinterpret_cast<const char*>(comp.data()), comp.size());
    } else {
        // Raw legacy uncompressed stream
        out.write(reinterpret_cast<const char*>(&m_header), sizeof(m_header));
        if (!m_frames.empty()) {
            out.write(reinterpret_cast<const char*>(m_frames.data()),
                      m_frames.size() * sizeof(replay_frame_t));
        }
    }

    out.close();
    m_recording = false;
    return true;
}

void replay_recorder_t::cancel_recording() {
    m_frames.clear();
    m_raw_block.clear();
    m_authentic_frame_count = 0;
    m_authentic_v2 = false;
    m_recording = false;
}

replay_player_t::replay_player_t() = default;
replay_player_t::~replay_player_t() {
    close();
}

// VERIFIED: LF2 0x0043e620
// VERIFIED: LF2 0x0043dfa0
bool replay_player_t::open_replay(const std::string& filepath) {
    close();

    std::ifstream in(filepath, std::ios::binary | std::ios::ate);
    if (!in.is_open()) {
        return false;
    }

    std::streamsize file_size = in.tellg();
    if (file_size < 4) {
        return false;
    }

    in.seekg(0, std::ios::beg);

    uint32_t magic_or_size = 0;
    if (!in.read(reinterpret_cast<char*>(&magic_or_size), sizeof(magic_or_size))) {
        return false;
    }

    if (magic_or_size == LF2_REPLAY_MAGIC) {
        // Format A: Uncompressed legacy stream starting with LF2_REPLAY_MAGIC
        in.seekg(0, std::ios::beg);
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

        m_format = replay_format_t::LEGACY_RAW;
        m_loaded = true;
        m_current_frame = 0;
        return true;
    }

    // Format B: LF2 v2.0 Deflated stream with secondary cipher
    uint32_t comp_size = magic_or_size;
    if (comp_size == 0 || comp_size > static_cast<uint32_t>(file_size - 4)) {
        return false;
    }

    std::vector<uint8_t> comp_data(comp_size);
    if (!in.read(reinterpret_cast<char*>(comp_data.data()), comp_size)) {
        return false;
    }

    // Decipher using 0x0043E620 secondary cipher
    replay_cipher_decrypt(comp_data.data(), comp_data.size());

    // Inflate stream using zlib
    std::vector<uint8_t> uncomp_data;
    if (!decompress_replay_stream(comp_data.data(), comp_data.size(), uncomp_data)) {
        return false;
    }

    // Check uncompressed payload
    if (uncomp_data.size() >= sizeof(replay_header_t)) {
        uint32_t uncomp_magic = *reinterpret_cast<const uint32_t*>(uncomp_data.data());
        if (uncomp_magic == LF2_REPLAY_MAGIC) {
            std::memcpy(&m_header, uncomp_data.data(), sizeof(m_header));
            m_frames.resize(m_header.total_frames);
            if (m_header.total_frames > 0) {
                size_t expected_frames_bytes = m_header.total_frames * sizeof(replay_frame_t);
                if (uncomp_data.size() >= sizeof(m_header) + expected_frames_bytes) {
                    std::memcpy(m_frames.data(),
                                uncomp_data.data() + sizeof(m_header),
                                expected_frames_bytes);
                }
            }

            m_format = replay_format_t::V2_COMPRESSED;
            m_loaded = true;
            m_current_frame = 0;
            return true;
        }
    }

    // Authentic LF2 full 0x630E18 memory dump
    if (uncomp_data.size() == AUTHENTIC_LFR_BLOCK_SIZE) {
        std::memset(&m_header, 0, sizeof(m_header));
        m_header.magic = LF2_REPLAY_MAGIC;
        m_header.difficulty = uncomp_data[0];
        m_header.game_mode = static_cast<uint8_t>(*reinterpret_cast<const uint32_t*>(uncomp_data.data() + 0x52 * 4));
        m_header.prng_seed = *reinterpret_cast<const uint32_t*>(uncomp_data.data() + 0x231 * 4);
        m_raw_block = std::move(uncomp_data);
        m_format = replay_format_t::AUTHENTIC_V2_RAW;
        m_loaded = true;
        m_current_frame = 0;
        return true;
    }

    return false;
}

bool replay_player_t::read_frame(uint8_t out_inputs[8], uint8_t& out_flags) {
    if (m_format == replay_format_t::AUTHENTIC_V2_RAW) {
        replay_frame_10_t rec{};
        bool ok = false;
        if (!read_frame_10(rec, 0, ok)) {
            return false;
        }
        std::memcpy(out_inputs, rec.inputs, 8);
        out_flags = rec.func_flags;
        return true;
    }

    if (!m_loaded || m_current_frame >= m_frames.size()) {
        return false;
    }

    const auto& frame = m_frames[m_current_frame++];
    std::memcpy(out_inputs, frame.inputs, 8);
    out_flags = frame.control_flags;
    return true;
}

// VERIFIED: LF2 0x0043dc50
bool replay_player_t::read_frame_10(replay_frame_10_t& out_rec, int32_t current_hp_sum, bool& out_checksum_ok) {
    out_checksum_ok = true;
    if (!m_loaded) return false;

    if (m_format == replay_format_t::AUTHENTIC_V2_RAW) {
        if (m_current_frame >= AUTHENTIC_LFR_MAX_FRAMES || m_raw_block.size() < AUTHENTIC_LFR_BLOCK_SIZE) {
            return false;
        }
        // 0x0043DC50: Read 10-byte record from +0x2B38 + frame * 10
        size_t off = AUTHENTIC_LFR_FRAMES_OFFSET + m_current_frame * 10;
        std::memcpy(&out_rec, m_raw_block.data() + off, 10);

        if ((m_current_frame % AUTHENTIC_LFR_HP_INTERVAL) == 0) {
            size_t sum_off = AUTHENTIC_LFR_HP_CHECKSUM_OFFSET + (m_current_frame / AUTHENTIC_LFR_HP_INTERVAL) * 4;
            int32_t expected_sum = 0;
            std::memcpy(&expected_sum, m_raw_block.data() + sum_off, sizeof(int32_t));
            out_checksum_ok = (current_hp_sum == expected_sum);
        }
        m_current_frame++;
        return true;
    }

    if (m_current_frame >= m_frames.size()) {
        return false;
    }
    const auto& frame = m_frames[m_current_frame++];
    std::memcpy(out_rec.inputs, frame.inputs, 8);
    out_rec.func_flags = frame.control_flags;
    out_rec.unlock_flags = 0;
    return true;
}

// LIFTED: LF2 0x0043d2a0
void replay_player_t::close() {
    m_loaded = false;
    m_frames.clear();
    m_raw_block.clear();
    m_current_frame = 0;
}

} // namespace lf2

