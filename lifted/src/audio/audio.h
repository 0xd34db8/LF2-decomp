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
};

// Modern SDL2 Audio Pipeline abstracting legacy DirectSound (0x00401970 & 0x00401A30)
class audio_system_t {
public:
    static constexpr uint32_t MAX_CHANNELS = 32;
    static constexpr uint32_t MAX_SOUND_IDS = 256;

    audio_system_t();
    ~audio_system_t();

    bool init();
    void cleanup();

    // Sound loading
    bool load_sound(uint32_t sound_id, const std::string& filepath);
    bool load_sound_from_memory(uint32_t sound_id, const uint8_t* data, size_t size);

    // Playback
    int32_t play_sound(uint32_t sound_id, bool loop = false, int volume = SDL_MIX_MAXVOLUME);
    void stop_sound(uint32_t sound_id);
    void stop_all();

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
};

// Global audio singleton
audio_system_t& get_audio_system();

} // namespace lf2

