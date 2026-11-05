#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include "gameplay/entity.h"

namespace lf2 {

constexpr size_t MAX_CONTROL_PLAYERS = 4;
constexpr size_t KEYS_PER_PLAYER = 11;
constexpr uint32_t LF2_REPLAY_MAGIC = 0x4C463252; // "R2FL" (Little Fighter 2 Replay)

// 1:1 Player Control Configuration from data/control.txt (0x00423480)
struct control_config_t {
    std::array<std::array<int32_t, KEYS_PER_PLAYER>, MAX_CONTROL_PLAYERS> player_keys{};
    std::array<std::string, MAX_CONTROL_PLAYERS> player_names{};
    int32_t demo_mode = 0;
    int32_t replay_mode = 0;

    bool load_from_file(const std::string& filepath);
    bool save_to_file(const std::string& filepath) const;
};

// Replay Battle Header (0x0042D080 / 0x0043453A)
#pragma pack(push, 1)
struct replay_slot_t {
    int32_t character_id;
    int32_t team;
    uint8_t is_cpu;
};

struct replay_header_t {
    uint32_t magic;          // LF2_REPLAY_MAGIC
    uint32_t prng_seed;      // Initial index into the 3,000-byte PRNG circular table
    uint8_t  game_mode;      // 0: VS, 1: Stage, 2: Survival, 3: 1-on-1
    uint8_t  stage_number;   // Stage 1..5
    uint8_t  difficulty;     // 0: Easy, 1: Normal, 2: Difficult, 3: CRAZY!
    uint8_t  player_count;   // Number of active character slots
    replay_slot_t slots[8];  // 8 player slot configs
    uint32_t total_frames;   // Recorded frame count
};

// 1:1 Frame-by-Frame Recorded Input Record
struct replay_frame_t {
    uint8_t inputs[8];       // Packed input bitmasks for player slots 0..7
    uint8_t control_flags;   // F1 pause, F2 step, etc.
};
#pragma pack(pop)

static_assert(sizeof(replay_frame_t) == 9, "replay_frame_t must be packed to 9 bytes");

// Authentic LF2 v2.0 Secondary Obfuscation Cipher Key (0x0044D7A0)
// Exactly 1,345 characters in the .data section of lf2.exe (SHA256: a1e3e58e52cb7091bff6e1ea7ed8e14274b882f51134af69ca4ce0a72cc8613b)
extern const char REPLAY_CIPHER_KEY[1346];

// Replay file storage format
enum class replay_format_t {
    UNKNOWN,
    LEGACY_RAW,        // Raw uncompressed stream (starts with magic LF2_REPLAY_MAGIC)
    V2_COMPRESSED,     // Modern LF2 v2.0 deflated stream with secondary cipher
    AUTHENTIC_V2_RAW   // Shipped authentic 6.4MB full buffer deflated with secondary cipher
};

// 1:1 Parity with 0x0043DD60 & 0x0043E620 secondary obfuscation cipher
void replay_cipher_encrypt(uint8_t* buffer, size_t size);
void replay_cipher_decrypt(uint8_t* buffer, size_t size);

// Zlib deflation and inflation pipeline for replay streams
bool compress_replay_stream(const uint8_t* src, size_t src_len, std::vector<uint8_t>& out_compressed);
bool decompress_replay_stream(const uint8_t* src, size_t src_len, std::vector<uint8_t>& out_decompressed, size_t max_uncompressed_size = 0x631200);

// Replay Recording Manager (0x00402980 & 0x0043DD60)
class replay_recorder_t {
public:
    replay_recorder_t();
    ~replay_recorder_t();

    bool start_recording(const replay_header_t& header, const std::string& filepath, bool compress = true);
    void record_frame(const uint8_t player_inputs[8], uint8_t control_flags = 0);
    bool finish_recording();
    void cancel_recording();

    bool is_recording() const { return m_recording; }
    size_t get_recorded_frames() const { return m_frames.size(); }
    const std::string& get_filepath() const { return m_filepath; }
    bool is_compression_enabled() const { return m_compress; }
    void set_compression_enabled(bool enabled) { m_compress = enabled; }

    static std::string generate_filename(int mode, int stage);

private:
    bool m_recording = false;
    bool m_compress = true;
    std::string m_filepath;
    replay_header_t m_header{};
    std::vector<replay_frame_t> m_frames;
};

// Replay Playback Controller (0x00421D07 & 0x0043E620)
class replay_player_t {
public:
    replay_player_t();
    ~replay_player_t();

    bool open_replay(const std::string& filepath);
    bool read_frame(uint8_t out_inputs[8], uint8_t& out_flags);
    void close();

    bool is_open() const { return m_loaded; }
    bool is_finished() const { return m_current_frame >= m_frames.size(); }
    size_t get_current_frame() const { return m_current_frame; }
    size_t get_total_frames() const { return m_frames.size(); }
    const replay_header_t& get_header() const { return m_header; }
    replay_format_t get_format() const { return m_format; }

private:
    bool m_loaded = false;
    replay_format_t m_format = replay_format_t::UNKNOWN;
    replay_header_t m_header{};
    std::vector<replay_frame_t> m_frames;
    size_t m_current_frame = 0;
};

} // namespace lf2

