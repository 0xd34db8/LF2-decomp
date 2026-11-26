#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL.h>

namespace lf2 {

struct sound_sample_t {
    uint8_t* buffer = nullptr;
    uint32_t length = 0;
};

struct active_channel_t {
    const uint8_t* pos = nullptr;
    uint32_t remaining = 0;
    bool active = false;
    bool loop = false;
    uint32_t sound_id = 0;
    int volume = SDL_MIX_MAXVOLUME;
    int left_gain = 100;   // 0..100 stereo pan scale
    int right_gain = 100;  // 0..100 stereo pan scale
};

// Modern SDL2 Audio Pipeline abstracting legacy DirectSound (0x00401970, 0x00401A30, 0x00416FB0, 0x00417090, 0x00419E60)
class audio_system_t {
public:
    static constexpr uint32_t MAX_CHANNELS = 32;
    static constexpr uint32_t MAX_SOUND_IDS = 256;
    static constexpr size_t NUM_FIXED_SOUNDS = 18;
    static constexpr uint32_t FIXED_SOUND_BASE = 600;
    static constexpr uint32_t MAX_ITEM_SOUNDS = 400;
    static constexpr uint32_t MAX_FIXED_SOUNDS = 80;

    audio_system_t();
    ~audio_system_t();

    bool init();
    void cleanup();

    // Sound loading
    bool load_sound(uint32_t sound_id, const std::string& filepath);
    bool load_sound_from_memory(uint32_t sound_id, const uint8_t* data, size_t size);
    void preload_fixed_battle_sounds();
    static const char* get_fixed_sound_path(size_t index);

    // Playback
    int32_t play_sound(uint32_t sound_id, bool loop = false, int volume = SDL_MIX_MAXVOLUME,
                       int left_gain = 100, int right_gain = 100);
    void stop_sound(uint32_t sound_id);
    void stop_all();

    // Spatial Stereo Panning & End-of-Frame Flush (0x00416FB0, 0x00417090, 0x00419E60)
    void set_camera_x(int32_t camera_x) { m_camera_x = camera_x; }
    int32_t get_camera_x() const { return m_camera_x; }
    void queue_item_sound(int32_t world_x, int32_t camera_x, int32_t sound_id);
    void queue_fixed_sound(int32_t world_x, int32_t camera_x, int32_t fixed_idx);
    void queue_item_sound(int32_t world_x, int32_t sound_id) { queue_item_sound(world_x, m_camera_x, sound_id); }
    void queue_fixed_sound(int32_t world_x, int32_t fixed_idx) { queue_fixed_sound(world_x, m_camera_x, fixed_idx); }
    void flush_queued_sounds();
    int32_t get_last_item_pan(int32_t sound_id) const;
    int32_t get_last_item_vol(int32_t sound_id) const;
    int32_t get_last_fixed_pan(int32_t fixed_idx) const;
    int32_t get_last_fixed_vol(int32_t fixed_idx) const;
    uint32_t get_fixed_play_count(int32_t fixed_idx) const;

    // Volume & Settings
    void set_master_volume(int volume);
    int get_master_volume() const { return m_master_volume; }
    void set_mute(bool mute);
    bool is_muted() const { return m_muted; }

    bool is_initialized() const { return m_initialized; }
    size_t get_loaded_count() const { return m_samples.size(); }
    uint32_t get_active_channel_count() const;

    // DirectSound Parity Hook: play sound referenced by frame_t::sound
    void on_frame_sound(uint32_t sound_tag);

    // Internal SDL audio callback
    void audio_callback(uint8_t* stream, int len);

private:
    bool m_initialized = false;
    bool m_muted = false;
    int m_master_volume = SDL_MIX_MAXVOLUME;
    SDL_AudioDeviceID m_device_id = 0;
    SDL_AudioSpec m_obtained_spec{};

    std::unordered_map<uint32_t, sound_sample_t> m_samples;
    active_channel_t m_channels[MAX_CHANNELS]{};

    // Spatial sound queues (0x00457588 / 0x00453E10)
    int32_t m_camera_x = 0;
    int32_t m_item_queued[MAX_ITEM_SOUNDS]{};
    int32_t m_item_left[MAX_ITEM_SOUNDS]{};
    int32_t m_item_right[MAX_ITEM_SOUNDS]{};
    int32_t m_last_item_pan[MAX_ITEM_SOUNDS]{};
    int32_t m_last_item_vol[MAX_ITEM_SOUNDS]{};

    int32_t m_fixed_queued[MAX_FIXED_SOUNDS]{};
    int32_t m_fixed_left[MAX_FIXED_SOUNDS]{};
    int32_t m_fixed_right[MAX_FIXED_SOUNDS]{};
    int32_t m_last_fixed_pan[MAX_FIXED_SOUNDS]{};
    int32_t m_last_fixed_vol[MAX_FIXED_SOUNDS]{};
    uint32_t m_fixed_play_count[MAX_FIXED_SOUNDS]{};
};

// Global audio singleton
audio_system_t& get_audio_system();

} // namespace lf2

