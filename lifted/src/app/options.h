#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <SDL.h>
#include "app/app.h"
#include "graphics/renderer.h"

namespace lf2 {

// 1:1 Parity with 0x00422B00 (FUN_00422b00)
// Maps Win32 Virtual Key code to human-readable string and font offset width adjustment
std::string get_key_name(int key_code);
int get_key_name_width_adj(int key_code);

// 1:1 Parity with 0x00422F60 (FUN_00422f60)
// Converts Virtual Key code to ASCII character with Shift, CapsLock, and numpad evaluation
char vk_to_ascii(int key_code, bool shift_down, bool caps_lock = false);

// Substates for the Options UI (0x004246B0)
enum class options_substate_t : int {
    ROOT             = 0,
    NETWORK_SETUP    = 1,
    NETWORK_WAIT     = 2,
    NETWORK_CONNECT  = 3,
    NETWORK_CONNECTED= 4,
    CONTROL_SETTINGS = 6,
    PROFILE_SETTINGS = 7,
    CHALLENGE_INFO   = 8,
    CREDITS          = -1,
    DISPLAY_SWITCH   = -3
};

// Interactive Options & Control Configuration UI Controller (0x004246B0)
class options_ui_t {
public:
    options_ui_t();
    ~options_ui_t() = default;

    void init(app_t* app);
    void reset();

    // Mode navigation
    void set_substate(options_substate_t substate);
    options_substate_t get_substate() const { return m_substate; }

    // Event & Input processing
    bool handle_event(const SDL_Event& event, app_t* app);
    void update(app_t* app);
    void render(renderer_t& gfx, app_t* app);

    // Rebinding state queries
    bool is_rebinding() const { return m_rebind_player >= 0 && m_rebind_action_idx >= 0; }
    int get_rebinding_player() const { return m_rebind_player; }
    int get_rebinding_action() const { return m_rebind_action_idx; }

    // Start rebinding an action key for a player (player: 0..3, action_idx: 1..7)
    void start_rebind(int player_idx, int action_idx);
    void cancel_rebind();
    void apply_rebind(int vk_code);

    // Player name editing
    bool is_editing_name() const { return m_editing_player_name >= 0; }
    int get_editing_player() const { return m_editing_player_name; }
    void start_editing_name(int player_idx);
    void finish_editing_name();

    // Save and cancel operations (0x00423230 & 0x00423480)
    bool save_controls(const std::string& path = "data/control.txt");
    bool reload_controls(const std::string& path = "data/control.txt");
    void reset_to_defaults();

    // Configuration access
    control_config_t& get_config() { return m_cfg; }
    const control_config_t& get_config() const { return m_cfg; }

    // Display options
    void toggle_fullscreen(app_t* app);
    bool is_fullscreen() const { return m_fullscreen; }

    // System profile strings
    const std::string& get_profile_name() const { return m_profile_name; }
    const std::string& get_profile_email() const { return m_profile_email; }
    const std::string& get_profile_info() const { return m_profile_info; }
    void set_profile_name(const std::string& name) { m_profile_name = name; }
    void set_profile_email(const std::string& email) { m_profile_email = email; }
    void set_profile_info(const std::string& info) { m_profile_info = info; }

    // Auto-record replay flag
    bool is_auto_record_enabled() const { return m_cfg.replay_mode != 0; }
    void set_auto_record(bool enabled) { m_cfg.replay_mode = enabled ? 1 : 0; }

private:
    options_substate_t m_substate = options_substate_t::CONTROL_SETTINGS;
    control_config_t m_cfg;

    // Active interactive rebinding state
    int m_rebind_player = -1;      // 0..3, or -1
    int m_rebind_action_idx = -1;  // 1: Up, 2: Down, 3: Left, 4: Right, 5: Attack, 6: Jump, 7: Defend

    // Active name editing state
    int m_editing_player_name = -1; // 0..3, or -1

    // Active profile string editing field (0: none, 1: name, 2: info, 3: email)
    int m_editing_profile_field = 0;

    // Cursor blink animation timer
    uint32_t m_cursor_blink_ticks = 0;
    bool m_cursor_visible = true;

    // System profile information (0x0044FD18, 0x0044F890, 0x0044F900)
    std::string m_profile_name = "<No name>";
    std::string m_profile_email = "<No email>";
    std::string m_profile_info = "<No info>";

    // Display mode
    bool m_fullscreen = false;

    // Mouse click state
    bool m_mouse_prev_down = false;

    // Helpers for UI rendering
    void render_control_screen(renderer_t& gfx, app_t* app);
    void render_profile_screen(renderer_t& gfx, app_t* app);
    void render_display_screen(renderer_t& gfx, app_t* app);
};

} // namespace lf2

