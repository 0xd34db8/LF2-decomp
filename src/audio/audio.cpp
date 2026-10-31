#include "audio/audio.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

namespace lf2 {

audio_system_t::audio_system_t()
{
    // Default obtained spec in case audio device is headless
    m_obtained_spec.freq = 44100;
    m_obtained_spec.format = AUDIO_S16SYS;
    m_obtained_spec.channels = 2;
    m_obtained_spec.samples = 1024;
}

audio_system_t::~audio_system_t()
{
    cleanup();
}

bool audio_system_t::init()
{
    if (m_initialized) return true;

    if (SDL_WasInit(SDL_INIT_AUDIO) == 0) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            std::cerr << "[LF2 AUDIO] Warning: SDL Audio subsystem init failed: " << SDL_GetError() << std::endl;
        }
    }

    SDL_AudioSpec desired;
    std::memset(&desired, 0, sizeof(desired));
    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    desired.samples = 1024;
    desired.callback = [](void* userdata, Uint8* stream, int len) {
        static_cast<audio_system_t*>(userdata)->audio_callback(stream, len);
    };
    desired.userdata = this;

    m_device_id = SDL_OpenAudioDevice(nullptr, 0, &desired, &m_obtained_spec, 0);
    if (m_device_id == 0) {
        // Headless audio fallback: software mixing remains fully functional for tests
        m_obtained_spec = desired;
    } else {
        SDL_PauseAudioDevice(m_device_id, 0); // Start playback
    }

    m_initialized = true;
    return true;
}

void audio_system_t::cleanup()
{
    stop_all();

    if (m_device_id != 0) {
        SDL_CloseAudioDevice(m_device_id);
        m_device_id = 0;
    }

    for (auto& pair : m_samples) {
        delete[] pair.second.buffer;
    }
    m_samples.clear();

    m_initialized = false;
}

bool audio_system_t::load_sound(uint32_t sound_id, const std::string& filepath)
{
    if (!m_initialized) {
        if (!init()) return false;
    }

    SDL_AudioSpec wav_spec;
    Uint8* wav_buffer = nullptr;
    Uint32 wav_length = 0;

    if (!SDL_LoadWAV(filepath.c_str(), &wav_spec, &wav_buffer, &wav_length)) {
        return false;
    }

    sound_sample_t sample;
    SDL_AudioCVT cvt;
    if (SDL_BuildAudioCVT(&cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
                          m_obtained_spec.format, m_obtained_spec.channels, m_obtained_spec.freq) > 0) {
        cvt.len = static_cast<int>(wav_length);
        cvt.buf = static_cast<Uint8*>(std::malloc(cvt.len * cvt.len_mult));
        if (cvt.buf) {
            std::memcpy(cvt.buf, wav_buffer, wav_length);
            SDL_ConvertAudio(&cvt);

            sample.buffer = new uint8_t[cvt.len_cvt];
            std::memcpy(sample.buffer, cvt.buf, cvt.len_cvt);
            sample.length = static_cast<uint32_t>(cvt.len_cvt);
            std::free(cvt.buf);
        } else {
            SDL_FreeWAV(wav_buffer);
            return false;
        }
    } else {
        sample.buffer = new uint8_t[wav_length];
        std::memcpy(sample.buffer, wav_buffer, wav_length);
        sample.length = wav_length;
    }

    SDL_FreeWAV(wav_buffer);

    // If sound_id already exists, replace it
    auto it = m_samples.find(sound_id);
    if (it != m_samples.end()) {
        delete[] it->second.buffer;
    }
    m_samples[sound_id] = sample;
    return true;
}

bool audio_system_t::load_sound_from_memory(uint32_t sound_id, const uint8_t* data, size_t size)
{
    if (!m_initialized) {
        if (!init()) return false;
    }

    SDL_RWops* rw = SDL_RWFromConstMem(data, static_cast<int>(size));
    if (!rw) return false;

    SDL_AudioSpec wav_spec;
    Uint8* wav_buffer = nullptr;
    Uint32 wav_length = 0;

    if (!SDL_LoadWAV_RW(rw, 1, &wav_spec, &wav_buffer, &wav_length)) {
        return false;
    }

    sound_sample_t sample;
    SDL_AudioCVT cvt;
    if (SDL_BuildAudioCVT(&cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
                          m_obtained_spec.format, m_obtained_spec.channels, m_obtained_spec.freq) > 0) {
        cvt.len = static_cast<int>(wav_length);
        cvt.buf = static_cast<Uint8*>(std::malloc(cvt.len * cvt.len_mult));
        if (cvt.buf) {
            std::memcpy(cvt.buf, wav_buffer, wav_length);
            SDL_ConvertAudio(&cvt);

            sample.buffer = new uint8_t[cvt.len_cvt];
            std::memcpy(sample.buffer, cvt.buf, cvt.len_cvt);
            sample.length = static_cast<uint32_t>(cvt.len_cvt);
            std::free(cvt.buf);
        } else {
            SDL_FreeWAV(wav_buffer);
            return false;
        }
    } else {
        sample.buffer = new uint8_t[wav_length];
        std::memcpy(sample.buffer, wav_buffer, wav_length);
        sample.length = wav_length;
    }

    SDL_FreeWAV(wav_buffer);

    auto it = m_samples.find(sound_id);
    if (it != m_samples.end()) {
        delete[] it->second.buffer;
    }
    m_samples[sound_id] = sample;
    return true;
}

int32_t audio_system_t::play_sound(uint32_t sound_id, bool loop, int volume)
{
    auto it = m_samples.find(sound_id);
    if (it == m_samples.end() || it->second.buffer == nullptr) {
        return -1;
    }

    if (m_device_id != 0) {
        SDL_LockAudioDevice(m_device_id);
    }

    // Find free channel or oldest channel
    int32_t chosen_channel = -1;
    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        if (!m_channels[i].active) {
            chosen_channel = static_cast<int32_t>(i);
            break;
        }
    }

    if (chosen_channel == -1) {
        chosen_channel = 0; // Preempt channel 0 if all active
    }

    m_channels[chosen_channel].pos = it->second.buffer;
    m_channels[chosen_channel].remaining = it->second.length;
    m_channels[chosen_channel].active = true;
    m_channels[chosen_channel].loop = loop;
    m_channels[chosen_channel].sound_id = sound_id;
    m_channels[chosen_channel].volume = std::clamp(volume, 0, static_cast<int>(SDL_MIX_MAXVOLUME));

    if (m_device_id != 0) {
        SDL_UnlockAudioDevice(m_device_id);
    }

    return chosen_channel;
}

void audio_system_t::stop_sound(uint32_t sound_id)
{
    if (m_device_id != 0) {
        SDL_LockAudioDevice(m_device_id);
    }

    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        if (m_channels[i].active && m_channels[i].sound_id == sound_id) {
            m_channels[i].active = false;
        }
    }

    if (m_device_id != 0) {
        SDL_UnlockAudioDevice(m_device_id);
    }
}

void audio_system_t::stop_all()
{
    if (m_device_id != 0) {
        SDL_LockAudioDevice(m_device_id);
    }

    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        m_channels[i].active = false;
    }

    if (m_device_id != 0) {
        SDL_UnlockAudioDevice(m_device_id);
    }
}

void audio_system_t::set_master_volume(int volume)
{
    m_master_volume = std::clamp(volume, 0, static_cast<int>(SDL_MIX_MAXVOLUME));
}

void audio_system_t::set_mute(bool mute)
{
    m_muted = mute;
}

uint32_t audio_system_t::get_active_channel_count() const
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        if (m_channels[i].active) count++;
    }
    return count;
}

void audio_system_t::on_frame_sound(uint32_t sound_tag)
{
    if (sound_tag == 0) return;

    // Check if sound is loaded
    if (m_samples.find(sound_tag) == m_samples.end()) {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "data/%03u.wav", sound_tag);
        if (!load_sound(sound_tag, buf)) {
            std::snprintf(buf, sizeof(buf), ".legacy/data/%03u.wav", sound_tag);
            load_sound(sound_tag, buf);
        }
    }

    play_sound(sound_tag, false);
}

void audio_system_t::audio_callback(uint8_t* stream, int len)
{
    std::memset(stream, 0, len);
    if (m_muted) return;

    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        if (!m_channels[i].active || m_channels[i].remaining == 0) continue;

        uint32_t mix_len = std::min(static_cast<uint32_t>(len), m_channels[i].remaining);
        int effective_vol = (m_channels[i].volume * m_master_volume) / SDL_MIX_MAXVOLUME;

        SDL_MixAudioFormat(stream, m_channels[i].pos, m_obtained_spec.format, mix_len, effective_vol);

        m_channels[i].pos += mix_len;
        m_channels[i].remaining -= mix_len;

        if (m_channels[i].remaining == 0) {
            if (m_channels[i].loop) {
                auto it = m_samples.find(m_channels[i].sound_id);
                if (it != m_samples.end()) {
                    m_channels[i].pos = it->second.buffer;
                    m_channels[i].remaining = it->second.length;
                } else {
                    m_channels[i].active = false;
                }
            } else {
                m_channels[i].active = false;
            }
        }
    }
}

audio_system_t& get_audio_system()
{
    static audio_system_t instance;
    return instance;
}

} // namespace lf2

