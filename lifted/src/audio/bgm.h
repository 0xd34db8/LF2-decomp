#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <SDL.h>

namespace lf2 {

// Authentic track IDs (0x00402130 & 0x004025D0)
enum bgm_track_id_t : int32_t {
    BGM_TRACK_OFF        = -1,
    BGM_TRACK_RANDOM     =  0,
    BGM_TRACK_MAIN       =  1, // bgm/main.wma
    BGM_TRACK_STAGE1     =  2, // bgm/stage1.wma
    BGM_TRACK_STAGE2     =  3, // bgm/stage2.wma
    BGM_TRACK_STAGE3     =  4, // bgm/stage3.wma
    BGM_TRACK_STAGE4     =  5, // bgm/stage4.wma
    BGM_TRACK_STAGE5     =  6, // bgm/stage5.wma
    BGM_TRACK_BOSS1      =  7, // bgm/boss1.wma
    BGM_TRACK_BOSS2      =  8  // bgm/boss2.wma (Final Boss)
};

// Cross-Platform Modern Background Music Streamer (Replacing DirectShow COM 0x00401C90-0x004025D0)
class bgm_manager_t {
public:
    static constexpr int32_t DEFAULT_VOLUME = 80;

    bgm_manager_t();
    ~bgm_manager_t();

    bool init();
    void cleanup();

    // Playback control matching 0x00402020 / 0x00402000 / 0x00402100
    bool play(const std::string& filepath);
    bool play_track(int32_t track_id);
    bool play_staged();
    void stop();
    void pause();

    // Volume & Configuration matching 0x00401F30
    void set_volume(int32_t vol); // 0..100
    int32_t get_volume() const { return m_volume; }
    void set_enabled(bool enabled);
    bool is_enabled() const { return m_enabled; }

    // Looping matching 0x00401E90
    void set_looping(bool loop) { m_looping = loop; }
    bool is_looping() const { return m_looping; }
    bool is_playing() const { return m_playing; }

    // Track state queries
    int32_t get_current_track_id() const { return m_track_id; }
    const std::string& get_current_track_path() const { return m_current_track_path; }
    const std::string& get_staged_track_path() const { return m_staged_track_path; }
    const std::string& get_track_title() const { return m_track_title; }
    const std::string& get_hud_text() const { return m_hud_text; }

    // Menu HUD & Track Cycler (0x00402130)
    void menu_input(int32_t toggle_mode, int32_t left, int32_t right);

    // Stage & Boss BGM transitions
    void on_stage_start(int32_t stage_id);
    void on_boss_spawn(int32_t stage_id);
    void on_boss_defeated();

    // SDL2 Audio callback mixing
    void mix_audio(uint8_t* stream, int32_t len, SDL_AudioFormat format);

    // Helper to resolve track paths
    static std::string get_track_filepath(int32_t track_id);
    static std::string get_track_name(int32_t track_id);

private:
    bool decode_file_to_pcm(const std::string& path, std::vector<uint8_t>& out_pcm);
    std::string find_audio_file(const std::string& path) const;

private:
    bool m_initialized = false;
    bool m_enabled = true;
    bool m_playing = false;
    bool m_looping = true;
    int32_t m_volume = DEFAULT_VOLUME;
    int32_t m_track_id = BGM_TRACK_RANDOM;

    std::string m_current_track_path;
    std::string m_staged_track_path;
    std::string m_saved_stage_track_path;
    std::string m_track_title = "Random";
    std::string m_hud_text = "Music: Random";

    std::vector<uint8_t> m_decoded_pcm;
    size_t m_pcm_cursor = 0;
};

// Global BGM singleton
bgm_manager_t& get_bgm_manager();

} // namespace lf2
