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

// Authentic LF2 v2.0 Full Block Replay Offsets & Limits (0x0043DB40 / 0x0043DC50 / 0x0041BC90)
constexpr size_t AUTHENTIC_LFR_BLOCK_SIZE         = 0x630E18; // 6,491,672 bytes uncompressed
constexpr size_t AUTHENTIC_LFR_HP_CHECKSUM_OFFSET = 0x14B8;   // 150-frame int32 HP sum table
constexpr size_t AUTHENTIC_LFR_FRAMES_OFFSET      = 0x2B38;   // 10-byte per-frame input records
constexpr size_t AUTHENTIC_LFR_UNLOCK1_OFFSET     = 0x630BB8; // Backup unlock_chars (lf2.net)
constexpr size_t AUTHENTIC_LFR_UNLOCK2_OFFSET     = 0x630BBC; // Backup unlock_fkeys (herofighter.com)
constexpr size_t AUTHENTIC_LFR_MAX_FRAMES         = 0x9E33F;  // 647,999 frames (~3 hours @ 60hz/30hz phase)
constexpr size_t AUTHENTIC_LFR_HP_INTERVAL        = 150;      // 0x96 frames per HP checksum entry

enum ReplayFuncBits : uint8_t {
    REPLAY_FKEY_F3 = 0x04,
    REPLAY_FKEY_F6 = 0x10,
    REPLAY_FKEY_F7 = 0x20,
    REPLAY_FKEY_F8 = 0x40,
    REPLAY_FKEY_F9 = 0x80,
};

enum ReplayUnlockBits : uint8_t {
    REPLAY_UNLOCK_LF2NET      = 0x01,
    REPLAY_UNLOCK_HEROFIGHTER = 0x02,
};

// 1:1 Player Control Configuration from data/control.txt (0x00423480)
struct control_config_t {
    std::array<std::array<int32_t, KEYS_PER_PLAYER>, MAX_CONTROL_PLAYERS> player_keys{};
    std::array<std::string, MAX_CONTROL_PLAYERS> player_names{};
    int32_t demo_mode = 0;
    int32_t replay_mode = 0;
    std::string profile_name;
    std::string profile_email;
    std::string profile_info;

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

// 1:1 Frame-by-Frame Recorded Input Record (9-byte legacy API compat)
struct replay_frame_t {
    uint8_t inputs[8];       // Packed input bitmasks for player slots 0..7
    uint8_t control_flags;   // Function key flags
};

// Authentic 10-byte LF2 v2.0 Frame Record (0x0043DB40 / 0x0043DC50)
struct replay_frame_10_t {
    uint8_t inputs[8];       // +0..+7: Packed player 0..7 input bitmasks
    uint8_t func_flags;      // +8: ReplayFuncBits (F3/F6/F7/F8/F9)
    uint8_t unlock_flags;    // +9: ReplayUnlockBits (lf2.net / herofighter.com)
};
#pragma pack(pop)

static_assert(sizeof(replay_frame_t) == 9, "replay_frame_t must be packed to 9 bytes");
static_assert(sizeof(replay_frame_10_t) == 10, "replay_frame_10_t must be packed to 10 bytes");

// 1:1 Config Backup/Restore State for Replay Playback (0x0043DF00 / 0x0043DFA0)
struct replay_backup_state_t {
    int32_t difficulty = 1;
    std::array<std::string, 8> player_names{};
    std::string profile_name;
    std::string profile_info;
    std::string profile_email;
    int32_t unlock_chars = 0;
    int32_t unlock_fkeys = 0;
    bool active = false;

    void write_to_block(std::vector<uint8_t>& block) const;
    void restore_from_block(const std::vector<uint8_t>& block);
};

// Computes 20-slot active character HP sum for 150-frame replay checksums
int32_t compute_active_hp_sum(const global_t& world);

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
    bool start_authentic_recording(int32_t difficulty, int32_t game_mode, int32_t unlock_chars, int32_t unlock_fkeys, const std::string& filepath);
    bool record_frame_10(const replay_frame_10_t& rec, int32_t active_hp_sum);
    bool finish_recording();
    void cancel_recording();

    bool is_recording() const { return m_recording; }
    bool is_authentic_v2() const { return m_authentic_v2; }
    size_t get_recorded_frames() const { return m_authentic_v2 ? m_authentic_frame_count : m_frames.size(); }
    const std::string& get_filepath() const { return m_filepath; }
    bool is_compression_enabled() const { return m_compress; }
    void set_compression_enabled(bool enabled) { m_compress = enabled; }
    const std::vector<uint8_t>& get_raw_block() const { return m_raw_block; }

    static std::string generate_filename(int mode, int stage);

private:
    bool m_recording = false;
    bool m_compress = true;
    bool m_authentic_v2 = false;
    std::string m_filepath;
    replay_header_t m_header{};
    std::vector<replay_frame_t> m_frames;
    std::vector<uint8_t> m_raw_block;
    size_t m_authentic_frame_count = 0;
};

// Replay Playback Controller (0x00421D07 & 0x0043E620 & 0x0043DC50)
class replay_player_t {
public:
    replay_player_t();
    ~replay_player_t();

    bool open_replay(const std::string& filepath);
    bool read_frame(uint8_t out_inputs[8], uint8_t& out_flags);
    bool read_frame_10(replay_frame_10_t& out_rec, int32_t current_hp_sum, bool& out_checksum_ok);
    void close();

    bool is_open() const { return m_loaded; }
    bool is_finished() const { return m_current_frame >= get_total_frames(); }
    size_t get_current_frame() const { return m_current_frame; }
    size_t get_total_frames() const { return (m_format == replay_format_t::AUTHENTIC_V2_RAW) ? AUTHENTIC_LFR_MAX_FRAMES : m_frames.size(); }
    const replay_header_t& get_header() const { return m_header; }
    replay_format_t get_format() const { return m_format; }
    const std::vector<uint8_t>& get_raw_block() const { return m_raw_block; }

private:
    bool m_loaded = false;
    replay_format_t m_format = replay_format_t::UNKNOWN;
    replay_header_t m_header{};
    std::vector<replay_frame_t> m_frames;
    std::vector<uint8_t> m_raw_block;
    size_t m_current_frame = 0;
};

} // namespace lf2

