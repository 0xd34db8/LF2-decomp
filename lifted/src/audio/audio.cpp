#include "audio/audio.h"
#include "audio/bgm.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

namespace lf2 {

namespace {

// 18 fixed battle sound WAVs loaded into DAT_00451db0[0..17] at startup (0x0041C000)
const char* const FIXED_BATTLE_SOUND_PATHS[audio_system_t::NUM_FIXED_SOUNDS] = {
    "data/001.wav", "data/002.wav", "data/006.wav", "data/010.wav",
    "data/011.wav", "data/004.wav", "data/016.wav", "data/017.wav",
    "data/020.wav", "data/021.wav", "data/025.wav", "data/032.wav",
    "data/033.wav", "data/039.wav", "data/065.wav", "data/066.wav",
    "data/068.wav", "data/085.wav"
};

void compute_ear_volumes(int32_t world_x, int32_t camera_x, int32_t& out_left, int32_t& out_right) {
    int32_t left_dist = (world_x - camera_x) - 200;
    if (left_dist < 0) left_dist = -left_dist;
    if (left_dist < 200) out_left = 100;
    else if (left_dist < 400) out_left = ((400 - left_dist) * 100) / 200;
    else out_left = 0;

    int32_t right_dist = (world_x - camera_x) - 600;
    if (right_dist < 0) right_dist = -right_dist;
    if (right_dist < 200) out_right = 100;
    else if (right_dist < 400) out_right = ((400 - right_dist) * 100) / 200;
    else out_right = 0;
}

} // namespace

const char* audio_system_t::get_fixed_sound_path(size_t index)
{
    if (index >= NUM_FIXED_SOUNDS) return nullptr;
    return FIXED_BATTLE_SOUND_PATHS[index];
}

void audio_system_t::preload_fixed_battle_sounds()
{
    for (size_t i = 0; i < NUM_FIXED_SOUNDS; ++i) {
        load_sound(FIXED_SOUND_BASE + static_cast<uint32_t>(i), FIXED_BATTLE_SOUND_PATHS[i]);
    }
}

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

// VERIFIED: LF2 0x00401970
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

    // Try opening audio device with strict desired format so SDL converts automatically.
    // If that fails, fall back to allowing format change.
    m_device_id = SDL_OpenAudioDevice(nullptr, 0, &desired, &m_obtained_spec, 0);
    if (m_device_id == 0) {
        m_device_id = SDL_OpenAudioDevice(nullptr, 0, &desired, &m_obtained_spec, SDL_AUDIO_ALLOW_ANY_CHANGE);
    }

    if (m_device_id == 0) {
        // Headless audio fallback: software mixing remains fully functional for tests
        m_obtained_spec = desired;
    } else {
        SDL_PauseAudioDevice(m_device_id, 0); // Start playback
    }

    m_initialized = true;
    return true;
}

// VERIFIED: LF2 0x004019b0
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

// VERIFIED: LF2 0x004014e0
bool audio_system_t::load_sound(uint32_t sound_id, const std::string& filepath)
{
    if (!m_initialized) {
        if (!init()) return false;
    }

    std::string path = filepath;
    for (char& c : path) {
        if (c == '\\') c = '/';
    }

    SDL_AudioSpec wav_spec;
    Uint8* wav_buffer = nullptr;
    Uint32 wav_length = 0;

    if (!SDL_LoadWAV(path.c_str(), &wav_spec, &wav_buffer, &wav_length)) {
        char* base = SDL_GetBasePath();
        if (base) {
            std::string alt_path = std::string(base) + path;
            SDL_free(base);
            if (!SDL_LoadWAV(alt_path.c_str(), &wav_spec, &wav_buffer, &wav_length)) {
                return false;
            }
        } else {
            return false;
        }
    }

    sound_sample_t sample;
    sample.buffer = nullptr;
    sample.length = 0;

    SDL_AudioCVT cvt;
    int cvt_res = SDL_BuildAudioCVT(&cvt, wav_spec.format, wav_spec.channels, wav_spec.freq,
                                    m_obtained_spec.format, m_obtained_spec.channels, m_obtained_spec.freq);
    if (cvt_res > 0) {
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
        // Format already matches (cvt_res == 0) or unsupported conversion (cvt_res < 0)
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

// VERIFIED: LF2 0x00401a30
int32_t audio_system_t::play_sound(uint32_t sound_id, bool loop, int volume, int left_gain, int right_gain)
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
    m_channels[chosen_channel].left_gain = std::clamp(left_gain, 0, 100);
    m_channels[chosen_channel].right_gain = std::clamp(right_gain, 0, 100);

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

// VERIFIED: LF2 0x00402810
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

// VERIFIED: LF2 0x00416fb0
void audio_system_t::queue_item_sound(int32_t world_x, int32_t camera_x, int32_t sound_id)
{
    if (sound_id < 0 || sound_id >= static_cast<int32_t>(MAX_ITEM_SOUNDS)) return;
    int32_t left = 0, right = 0;
    compute_ear_volumes(world_x, camera_x, left, right);
    if (m_item_queued[sound_id] == 0) {
        m_item_left[sound_id] = 0;
        m_item_right[sound_id] = 0;
    }
    m_item_left[sound_id] += left;
    m_item_right[sound_id] += right;
    m_item_queued[sound_id] = 1;
}

// VERIFIED: LF2 0x00417090
void audio_system_t::queue_fixed_sound(int32_t world_x, int32_t camera_x, int32_t fixed_idx)
{
    if (fixed_idx < 0 || fixed_idx >= static_cast<int32_t>(MAX_FIXED_SOUNDS)) return;
    int32_t left = 0, right = 0;
    compute_ear_volumes(world_x, camera_x, left, right);
    if (m_fixed_queued[fixed_idx] == 0) {
        m_fixed_left[fixed_idx] = 0;
        m_fixed_right[fixed_idx] = 0;
    }
    m_fixed_left[fixed_idx] += left;
    m_fixed_right[fixed_idx] += right;
    m_fixed_queued[fixed_idx] = 1;
}

// VERIFIED: LF2 0x00419e60
void audio_system_t::flush_queued_sounds()
{
    int master_pct = (m_master_volume * 100) / SDL_MIX_MAXVOLUME;

    for (uint32_t i = 0; i < MAX_ITEM_SOUNDS; ++i) {
        if (m_item_queued[i] > 0) {
            int32_t left = m_item_left[i];
            int32_t right = m_item_right[i];
            int32_t strength = left + right;
            m_item_queued[i] = 0;
            if (strength > 100) strength = 100;
            else if (strength < 1) continue;

            m_last_item_pan[i] = ((right - left) * 1500) / 100;
            m_last_item_vol[i] = ((master_pct - 100) * 3800) / 100 + ((strength - 100) * 2000) / 100;
            if (master_pct > 0) {
                if (i > 0 && m_samples.find(i) == m_samples.end()) {
                    char buf[64];
                    std::snprintf(buf, sizeof(buf), "data/%03u.wav", i);
                    load_sound(i, buf);
                }
                int ch_vol = (strength * SDL_MIX_MAXVOLUME) / 100;
                play_sound(i, false, ch_vol, std::min(100, left), std::min(100, right));
            }
        }
    }

    for (uint32_t i = 0; i < MAX_FIXED_SOUNDS; ++i) {
        if (m_fixed_queued[i] > 0) {
            int32_t left = m_fixed_left[i];
            int32_t right = m_fixed_right[i];
            int32_t strength = left + right;
            m_fixed_queued[i] = 0;
            if (strength > 100) strength = 100;
            else if (strength < 1) continue;

            m_last_fixed_pan[i] = ((right - left) * 1500) / 100;
            m_last_fixed_vol[i] = ((master_pct - 100) * 3800) / 100 + ((strength - 100) * 2000) / 100;
            if (master_pct > 0) {
                if (i < NUM_FIXED_SOUNDS && m_samples.find(FIXED_SOUND_BASE + i) == m_samples.end()) {
                    const char* fp = get_fixed_sound_path(i);
                    if (fp) load_sound(FIXED_SOUND_BASE + i, fp);
                }
                m_fixed_play_count[i]++;
                int ch_vol = (strength * SDL_MIX_MAXVOLUME) / 100;
                play_sound(FIXED_SOUND_BASE + i, false, ch_vol, std::min(100, left), std::min(100, right));
            }
        }
    }
}

int32_t audio_system_t::get_last_item_pan(int32_t sound_id) const
{
    if (sound_id < 0 || sound_id >= static_cast<int32_t>(MAX_ITEM_SOUNDS)) return 0;
    return m_last_item_pan[sound_id];
}

int32_t audio_system_t::get_last_item_vol(int32_t sound_id) const
{
    if (sound_id < 0 || sound_id >= static_cast<int32_t>(MAX_ITEM_SOUNDS)) return 0;
    return m_last_item_vol[sound_id];
}

int32_t audio_system_t::get_last_fixed_pan(int32_t fixed_idx) const
{
    if (fixed_idx < 0 || fixed_idx >= static_cast<int32_t>(MAX_FIXED_SOUNDS)) return 0;
    return m_last_fixed_pan[fixed_idx];
}

int32_t audio_system_t::get_last_fixed_vol(int32_t fixed_idx) const
{
    if (fixed_idx < 0 || fixed_idx >= static_cast<int32_t>(MAX_FIXED_SOUNDS)) return 0;
    return m_last_fixed_vol[fixed_idx];
}

uint32_t audio_system_t::get_fixed_play_count(int32_t fixed_idx) const
{
    if (fixed_idx < 0 || fixed_idx >= static_cast<int32_t>(MAX_FIXED_SOUNDS)) return 0;
    return m_fixed_play_count[fixed_idx];
}

void audio_system_t::on_frame_sound(uint32_t sound_tag)
{
    if (sound_tag == 0) return;

    // Check if sound is loaded
    if (m_samples.find(sound_tag) == m_samples.end()) {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "data/%03u.wav", sound_tag);
        load_sound(sound_tag, buf);
    }

    play_sound(sound_tag, false);
}

void audio_system_t::audio_callback(uint8_t* stream, int len)
{
    std::memset(stream, 0, len);
    if (m_muted) return;

    // Mix background music stream first
    get_bgm_manager().mix_audio(stream, len, m_obtained_spec.format);

    for (uint32_t i = 0; i < MAX_CHANNELS; ++i) {
        if (!m_channels[i].active || m_channels[i].remaining == 0) continue;

        uint32_t mix_len = std::min(static_cast<uint32_t>(len), m_channels[i].remaining);
        int effective_vol = (m_channels[i].volume * m_master_volume) / SDL_MIX_MAXVOLUME;

        if (m_obtained_spec.format == AUDIO_S16SYS && m_obtained_spec.channels == 2 &&
            (m_channels[i].left_gain != 100 || m_channels[i].right_gain != 100)) {
            const int16_t* src = reinterpret_cast<const int16_t*>(m_channels[i].pos);
            int16_t* dst = reinterpret_cast<int16_t*>(stream);
            uint32_t frames = mix_len / (sizeof(int16_t) * 2);
            int lg = m_channels[i].left_gain;
            int rg = m_channels[i].right_gain;
            for (uint32_t f = 0; f < frames; ++f) {
                int32_t l_sample = (static_cast<int32_t>(src[f * 2]) * effective_vol * lg) / (SDL_MIX_MAXVOLUME * 100);
                int32_t r_sample = (static_cast<int32_t>(src[f * 2 + 1]) * effective_vol * rg) / (SDL_MIX_MAXVOLUME * 100);
                dst[f * 2] = static_cast<int16_t>(std::clamp(static_cast<int32_t>(dst[f * 2]) + l_sample, -32768, 32767));
                dst[f * 2 + 1] = static_cast<int16_t>(std::clamp(static_cast<int32_t>(dst[f * 2 + 1]) + r_sample, -32768, 32767));
            }
        } else {
            SDL_MixAudioFormat(stream, m_channels[i].pos, m_obtained_spec.format, mix_len, effective_vol);
        }

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

