#pragma once

#include <cstdint>
#include <string>
#include <SDL.h>
#include "constants.h"
#include "global.h"
#include "renderer.h"
#include "background.h"
#include "entity.h"
#include "dat_loader.h"

namespace lf2 {

// Window and timing parameters authentic to lf2.exe
constexpr int WINDOW_WIDTH = 794;           // DAT_0044d78c in binary
constexpr int WINDOW_HEIGHT = 550;          // DAT_0044d790 in binary
constexpr const char* WINDOW_TITLE = "Little Fighter 2"; // 0x00447620 in binary
constexpr const char* WINDOW_CLASS_NAME = "Marti";       // 0x00447634 in binary

// Authentic timing constants from func_0043cf40 (WinMain)
constexpr uint32_t TICK_STEP_MENU_MS = 3;         // 3 ms tick step in menu / loading (DAT_0044d02c == 0)
constexpr uint32_t TICK_STEP_BATTLE_MS = 33;      // 0x21 (33 ms) fixed step in battle (~30.3 FPS)
constexpr uint32_t MAX_ACCUMULATOR_LAG_MS = 100;  // 100 ms spiral-of-death clamp
constexpr uint32_t MAX_SLEEP_CHUNK_MS = 5;        // 5 ms CPU yield chunking
constexpr uint32_t FRAME_COUNTER_MODULO = 60;     // 0x3C ticks modulo counter (DAT_00458580)

// Virtual Key Code constants matching Win32 legacy LF2 expectations
enum VirtualKey : uint8_t {
    VK_LF2_BACKSPACE   = 0x08,
    VK_LF2_TAB         = 0x09,
    VK_LF2_RETURN      = 0x0D,
    VK_LF2_SHIFT       = 0x10,
    VK_LF2_CONTROL     = 0x11,
    VK_LF2_MENU        = 0x12, // Alt
    VK_LF2_PAUSE       = 0x13,
    VK_LF2_ESCAPE      = 0x1B,
    VK_LF2_SPACE       = 0x20,
    VK_LF2_LEFT        = 0x25,
    VK_LF2_UP          = 0x26,
    VK_LF2_RIGHT       = 0x27,
    VK_LF2_DOWN        = 0x28,
    VK_LF2_NUMPAD0     = 0x60,
    VK_LF2_NUMPAD1     = 0x61,
    VK_LF2_NUMPAD2     = 0x62,
    VK_LF2_NUMPAD3     = 0x63,
    VK_LF2_NUMPAD4     = 0x64,
    VK_LF2_NUMPAD5     = 0x65,
    VK_LF2_NUMPAD6     = 0x66,
    VK_LF2_NUMPAD7     = 0x67,
    VK_LF2_NUMPAD8     = 0x68,
    VK_LF2_NUMPAD9     = 0x69,
    VK_LF2_F1          = 0x70,
    VK_LF2_F2          = 0x71,
    VK_LF2_F3          = 0x72,
    VK_LF2_F4          = 0x73,
    VK_LF2_F5          = 0x74,
    VK_LF2_F6          = 0x75,
    VK_LF2_F7          = 0x76,
    VK_LF2_F8          = 0x77,
    VK_LF2_F9          = 0x78,
    VK_LF2_F10         = 0x79,
    VK_LF2_F11         = 0x7A,
    VK_LF2_F12         = 0x7B,
    VK_LF2_OEM_PERIOD  = 0xBE  // '.' key used for "lf2.net" and "herofighter.com"
};

// Application lifecycle and window/platform wrapper
class app_t {
public:
    app_t();
    ~app_t();

    // Application Lifecycle
    bool init(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, bool fullscreen = false);
    void run();
    void shutdown();

    // Event & Message Handling (Translates SDL2 events into authentic LF2 state tables)
    void process_events();

    // Game Loop Execution Steps
    void update();
    void render();

    // Keyboard & Input Queries
    bool is_key_down(uint8_t vk) const { return m_key_states[vk] == 'd'; }
    bool is_key_up(uint8_t vk) const { return m_key_states[vk] == 'u'; }
    uint8_t get_key_state(uint8_t vk) const { return m_key_states[vk]; }

    // Cheat Code State Queries
    bool is_lf2net_unlocked() const { return m_cheat_lf2net == 'd'; }
    bool is_herofighter_unlocked() const { return m_cheat_herofighter == 'd'; }
    bool is_dev_mode_enabled() const { return m_cheat_dev_mode == 1; }

    // Timing & Mode Controls
    void set_in_battle(bool in_battle) { m_in_battle = in_battle; }
    bool is_in_battle() const { return m_in_battle; }
    void toggle_fullscreen();

    // Access to global game state
    global_t& get_world() { return m_world; }
    const global_t& get_world() const { return m_world; }

    // Graphics, Camera & Background pipeline access
    renderer_t& get_graphics() { return m_graphics; }
    const renderer_t& get_graphics() const { return m_graphics; }
    camera_t& get_camera() { return m_camera; }
    const camera_t& get_camera() const { return m_camera; }
    background_t& get_background() { return m_background; }
    const background_t& get_background() const { return m_background; }
    void set_stage_loaded(bool loaded) { m_stage_loaded = loaded; }
    bool is_stage_loaded() const { return m_stage_loaded; }

    // Mouse coordinates and buttons
    int16_t get_mouse_x() const { return m_mouse_x; }
    int16_t get_mouse_y() const { return m_mouse_y; }
    bool is_mouse_lbutton() const { return m_mouse_lbutton != 0; }
    bool is_mouse_rbutton() const { return m_mouse_rbutton != 0; }

    // Frame statistics
    uint32_t get_frame_counter() const { return m_frame_counter; }
    uint64_t get_total_ticks() const { return m_total_ticks; }
    void request_quit() { m_running = false; }

private:
    void reset_input();
    void on_key_down(uint8_t vk);
    void on_key_up(uint8_t vk);
    uint8_t sdl_key_to_vk(SDL_Keycode key, SDL_Scancode scancode);

private:
    // SDL2 Windowing & Rendering handles
    SDL_Window*     m_window;
    SDL_Renderer*   m_renderer;

    // Window dimensions and states
    int             m_width;
    int             m_height;
    bool            m_fullscreen;
    bool            m_running;
    bool            m_in_battle;
    int32_t         m_active_state;     // 0x00451dac in binary (1 = active window, 0 = inactive)

    // Authentic LF2 256-byte keyboard state array (0x00455378 in binary)
    // Initialized to 'u' (0x75); set to 'd' (0x64) when pressed
    uint8_t         m_key_states[256];

    // Mouse states (0x004546f0, 0x00453cdc, 0x00457580, 0x004527e4)
    int16_t         m_mouse_x;
    int16_t         m_mouse_y;
    int32_t         m_mouse_lbutton;
    int32_t         m_mouse_rbutton;

    // Secret Cheat Code State Trackers
    uint8_t         m_cheat_lf2net;          // 0x00455471: 'd' when unlocked
    uint8_t         m_cheat_herofighter;     // 0x00455470: 'd' when unlocked
    int32_t         m_cheat_lf2net_idx;      // 0x0045857c: progression index in "lf2.net"
    int32_t         m_cheat_herofighter_idx; // 0x00458578: progression index in "herofighter.com"
    int32_t         m_cheat_abc_idx;         // 0x004593a4: dev key sequence 'A' -> 'B' -> 'C'
    int32_t         m_cheat_dev_mode;        // 0x00450bec: dev mode unlocked flag

    // Frame pacing and timing counters (0x00458580 in binary)
    uint32_t        m_frame_counter;
    uint64_t        m_total_ticks;

    // Game world container
    global_t        m_world;

    // Graphics abstraction, Camera & Parallax Background pipeline
    renderer_t      m_graphics;
    camera_t        m_camera;
    background_t    m_background;
    bool            m_stage_loaded{false};

    // Active player character (Davis)
    object_t        m_player;
    file_t          m_davis_file;
    bool            m_player_loaded{false};
};

} // namespace lf2

