#include "app/options.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

namespace lf2 {

// 1:1 Parity with 0x00422B00 (FUN_00422b00)
std::string get_key_name(int key_code) {
    if (key_code == 0x20) return "Space";
    if (key_code == 0x0D) return "Enter";

    // 'A'..'Z'
    if (key_code >= 0x41 && key_code <= 0x5A) {
        return std::string(1, static_cast<char>(key_code));
    }

    // Keypad numbers 0..9 (0x60..0x69)
    if (key_code >= 0x60 && key_code <= 0x69) {
        return "Keypad: " + std::string(1, static_cast<char>('0' + (key_code - 0x60)));
    }

    // Keypad symbols
    if (key_code == 0x6B) return "Keypad: +";
    if (key_code == 0x6D) return "Keypad: -";
    if (key_code == 0x6A) return "Keypad: *";
    if (key_code == 0x6F) return "Keypad: /";
    if (key_code == 0x6E) return "Keypad: .";

    // Numbers '0'..'9' (0x30..0x39)
    if (key_code >= 0x30 && key_code <= 0x39) {
        return std::string(1, static_cast<char>(key_code));
    }

    // Standard Punctuation
    switch (key_code) {
        case 0xBD: return "-";
        case 0xBB: return "=";
        case 0xDB: return "[";
        case 0xDD: return "]";
        case 0xBA: return ";";
        case 0xDE: return "'";
        case 0xDC: return "\\";
        case 0xBC: return ",";
        case 0xBE: return ".";
        case 0xBF: return "/";
        case 0xC0: return "`";
        case 0x11: return "Ctrl";
        case 0x10: return "Shift";
        case 0x09: return "Tab";
        case 0x08: return "Backspace";
        case 0x2D: return "Insert";
        case 0x2E: return "Delete";
        case 0x24: return "Home";
        case 0x23: return "End";
        case 0x21: return "PageUp";
        case 0x22: return "PageDown";
        case 0x26: return "Up";
        case 0x25: return "Left";
        case 0x28: return "Down";
        case 0x27: return "Right";
        case 0x14: return "CapsLock";
        default: break;
    }

    // Gamepad button synthetic virtual keys
    if (key_code >= 1000 && key_code < 1016) {
        return "Btn " + std::to_string(key_code - 1000 + 1);
    }

    return "none";
}

int get_key_name_width_adj(int key_code) {
    if (key_code == 0x20 || key_code == 0x0D) return 10;
    if (key_code >= 0x41 && key_code <= 0x5A) return 0;
    if (key_code >= 0x60 && key_code <= 0x69) return 15;
    if (key_code >= 0x6A && key_code <= 0x6F) return 15;
    if (key_code >= 0x30 && key_code <= 0x39) return 0;

    switch (key_code) {
        case 0xBD: case 0xBB: case 0xDB: case 0xDD:
        case 0xBA: case 0xDE: case 0xDC: case 0xBC:
        case 0xBE: case 0xBF: case 0xC0:
            return 0;
        case 0x11: case 0x10: return 7;
        case 0x09: return 5;
        case 0x08: return 13;
        case 0x2D: case 0x2E: return 8;
        case 0x24: return 6;
        case 0x23: return 5;
        case 0x21: return 10;
        case 0x22: return 14;
        case 0x26: return 2;
        case 0x25: return 4;
        case 0x28: return 5;
        case 0x27: return 6;
        case 0x14: return 16;
        default: break;
    }
    return 8;
}

// 1:1 Parity with 0x00422F60 (FUN_00422f60)
char vk_to_ascii(int key_code, bool shift_down, bool caps_lock) {
    if (key_code == 0x20) return ' ';

    // Letters 'A'..'Z' (0x41..0x5A)
    if (key_code >= 0x41 && key_code <= 0x5A) {
        bool upper = (shift_down ^ caps_lock);
        return upper ? static_cast<char>(key_code) : static_cast<char>(key_code + 0x20);
    }

    // Keypad numbers 0..9 (0x60..0x69)
    if (key_code >= 0x60 && key_code <= 0x69) {
        return static_cast<char>('0' + (key_code - 0x60));
    }
    if (key_code == 0x6B) return '+';
    if (key_code == 0x6D) return '-';
    if (key_code == 0x6A) return '*';
    if (key_code == 0x6F) return '/';
    if (key_code == 0x6E) return '.';

    // Shifted symbols
    if (shift_down) {
        switch (key_code) {
            case 0xBD: return '_';
            case 0xBB: return '+';
            case 0xDB: return '{';
            case 0xDD: return '}';
            case 0xBA: return ':';
            case 0xDE: return '\"';
            case 0xDC: return '|';
            case 0xBC: return '<';
            case 0xBE: return '>';
            case 0xBF: return '?';
            case 0xC0: return '~';
            case 0x31: return '!';
            case 0x32: return '@';
            case 0x33: return '#';
            case 0x34: return '$';
            case 0x35: return '%';
            case 0x36: return '^';
            case 0x37: return '&';
            case 0x38: return '*';
            case 0x39: return '(';
            case 0x30: return ')';
            default: break;
        }
    } else {
        switch (key_code) {
            case 0xBD: return '-';
            case 0xBB: return '=';
            case 0xDB: return '[';
            case 0xDD: return ']';
            case 0xBA: return ';';
            case 0xDE: return '\'';
            case 0xDC: return '\\';
            case 0xBC: return ',';
            case 0xBE: return '.';
            case 0xBF: return '/';
            case 0xC0: return '`';
            default: break;
        }
    }

    // Number keys '0'..'9' (0x30..0x39) when unshifted
    if (key_code >= 0x30 && key_code <= 0x39) {
        return static_cast<char>(key_code);
    }

    // Navigation and keypad controls
    if (key_code == 0x21) return '9'; // PageUp
    if (key_code == 0x22) return '3'; // PageDown
    if (key_code == 0x23) return '1'; // End
    if (key_code == 0x24) return '7'; // Home
    if (key_code == 0x25) return '4'; // Left
    if (key_code == 0x26) return '8'; // Up
    if (key_code == 0x27) return '6'; // Right
    if (key_code == 0x28) return '2'; // Down
    if (key_code == 0x0C) return '5'; // Clear
    if (key_code == 0x2D) return '0'; // Insert

    return '\0';
}

options_ui_t::options_ui_t() {
    m_cfg.init_defaults();
}

void options_ui_t::init(app_t* app) {
    if (app) {
        m_cfg = app->get_control_config();
    }
    reload_controls("data/control.txt");
    m_substate = options_substate_t::CONTROL_SETTINGS;
    m_rebind_player = -1;
    m_rebind_action_idx = -1;
    m_editing_player_name = -1;
}

void options_ui_t::reset() {
    m_rebind_player = -1;
    m_rebind_action_idx = -1;
    m_editing_player_name = -1;
    m_editing_profile_field = 0;
}

void options_ui_t::set_substate(options_substate_t substate) {
    m_substate = substate;
    reset();
}

void options_ui_t::start_rebind(int player_idx, int action_idx) {
    if (player_idx >= 0 && player_idx < 4 && action_idx >= 1 && action_idx <= 7) {
        m_rebind_player = player_idx;
        m_rebind_action_idx = action_idx;
        m_editing_player_name = -1;
    }
}

void options_ui_t::cancel_rebind() {
    m_rebind_player = -1;
    m_rebind_action_idx = -1;
}

void options_ui_t::apply_rebind(int vk_code) {
    if (is_rebinding()) {
        m_cfg.players[m_rebind_player].keys[m_rebind_action_idx] = vk_code;
        m_rebind_player = -1;
        m_rebind_action_idx = -1;
    }
}

void options_ui_t::start_editing_name(int player_idx) {
    if (player_idx >= 0 && player_idx < 4) {
        m_editing_player_name = player_idx;
        m_rebind_player = -1;
        m_rebind_action_idx = -1;
    }
}

void options_ui_t::finish_editing_name() {
    m_editing_player_name = -1;
}

void options_ui_t::reset_to_defaults() {
    m_cfg.init_defaults();
    reset();
}

bool options_ui_t::reload_controls(const std::string& path) {
    bool ok = m_cfg.load_from_file(path);
    reset();
    if (ok) {
        std::ifstream f(path);
        if (f.is_open()) {
            std::string line;
            for (int i = 0; i < 7 && std::getline(f, line); ++i) {}
            if (std::getline(f, line)) {
                while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
                if (!line.empty()) m_profile_name = line;
            }
            if (std::getline(f, line)) {
                while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
                if (!line.empty()) m_profile_email = line;
            }
            if (std::getline(f, line)) {
                while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
                if (!line.empty()) m_profile_info = line;
            }
        }
    }
    return ok;
}

bool options_ui_t::save_controls(const std::string& path) {
    FILE* fp = fopen(path.c_str(), "w");
    if (!fp) return false;

    // 4 players x 11 keys
    for (int p = 0; p < 4; ++p) {
        for (int k = 0; k < 11; ++k) {
            fprintf(fp, "%d ", m_cfg.players[p].keys[k]);
        }
        fprintf(fp, "\n");
    }

    // 4 player names with spaces replaced by '`'
    for (int p = 0; p < 4; ++p) {
        char name_buf[16] = {0};
        strncpy(name_buf, m_cfg.players[p].name, 15);
        if (name_buf[0] == '\0') {
            snprintf(name_buf, sizeof(name_buf), "%d", p + 1);
        }
        for (int i = 0; name_buf[i]; ++i) {
            if (name_buf[i] == ' ') name_buf[i] = '`';
        }
        fprintf(fp, "%s%s", name_buf, (p == 3) ? "\n" : " ");
    }

    // Demo & replay flags
    fprintf(fp, "%d\n", m_cfg.demo_mode);
    fprintf(fp, "%d\n", m_cfg.replay_mode);

    // Profile strings
    fprintf(fp, "%s\n", m_profile_name.empty() ? "<No name>" : m_profile_name.c_str());
    fprintf(fp, "%s\n", m_profile_email.empty() ? "<No email>" : m_profile_email.c_str());
    fprintf(fp, "%s",   m_profile_info.empty() ? "<No info>" : m_profile_info.c_str());

    fclose(fp);
    return true;
}

void options_ui_t::toggle_fullscreen(app_t* app) {
    m_fullscreen = !m_fullscreen;
    if (app) {
        app->toggle_fullscreen();
    }
}

bool options_ui_t::handle_event(const SDL_Event& event, app_t* app) {
    if (event.type == SDL_KEYDOWN) {
        SDL_Keycode sym = event.key.keysym.sym;
        bool shift_down = (event.key.keysym.mod & KMOD_SHIFT) != 0;
        bool caps_lock = (event.key.keysym.mod & KMOD_CAPS) != 0;

        // If in active key rebind mode:
        if (is_rebinding()) {
            if (sym == SDLK_ESCAPE) {
                cancel_rebind();
                if (app) app->play_ui_sound(SOUND_CANCEL);
                return true;
            }

            // Convert SDL keycode to LF2 Win32 Virtual Key code
            int vk = 0;
            if (sym >= SDLK_a && sym <= SDLK_z) {
                vk = 0x41 + (sym - SDLK_a);
            } else if (sym >= SDLK_0 && sym <= SDLK_9) {
                vk = 0x30 + (sym - SDLK_0);
            } else if (sym >= SDLK_KP_1 && sym <= SDLK_KP_9) {
                vk = 0x61 + (sym - SDLK_KP_1);
            } else if (sym == SDLK_KP_0) {
                vk = 0x60;
            } else if (sym == SDLK_UP) vk = 0x26;
            else if (sym == SDLK_DOWN) vk = 0x28;
            else if (sym == SDLK_LEFT) vk = 0x25;
            else if (sym == SDLK_RIGHT) vk = 0x27;
            else if (sym == SDLK_SPACE) vk = 0x20;
            else if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER) vk = 0x0D;
            else if (sym == SDLK_LSHIFT || sym == SDLK_RSHIFT) vk = 0x10;
            else if (sym == SDLK_LCTRL || sym == SDLK_RCTRL) vk = 0x11;
            else if (sym == SDLK_TAB) vk = 0x09;
            else if (sym == SDLK_BACKSPACE) vk = 0x08;
            else if (sym == SDLK_INSERT) vk = 0x2D;
            else if (sym == SDLK_DELETE) vk = 0x2E;
            else if (sym == SDLK_HOME) vk = 0x24;
            else if (sym == SDLK_END) vk = 0x23;
            else if (sym == SDLK_PAGEUP) vk = 0x21;
            else if (sym == SDLK_PAGEDOWN) vk = 0x22;
            else if (sym == SDLK_KP_PLUS) vk = 0x6B;
            else if (sym == SDLK_KP_MINUS) vk = 0x6D;
            else if (sym == SDLK_KP_MULTIPLY) vk = 0x6A;
            else if (sym == SDLK_KP_DIVIDE) vk = 0x6F;
            else if (sym == SDLK_KP_PERIOD) vk = 0x6E;
            else if (sym == SDLK_SEMICOLON) vk = 0xBA;
            else if (sym == SDLK_EQUALS) vk = 0xBB;
            else if (sym == SDLK_COMMA) vk = 0xBC;
            else if (sym == SDLK_MINUS) vk = 0xBD;
            else if (sym == SDLK_PERIOD) vk = 0xBE;
            else if (sym == SDLK_SLASH) vk = 0xBF;
            else if (sym == SDLK_BACKQUOTE) vk = 0xC0;
            else if (sym == SDLK_LEFTBRACKET) vk = 0xDB;
            else if (sym == SDLK_BACKSLASH) vk = 0xDC;
            else if (sym == SDLK_RIGHTBRACKET) vk = 0xDD;
            else if (sym == SDLK_QUOTE) vk = 0xDE;
            else {
                vk = static_cast<int>(sym);
            }

            apply_rebind(vk);
            if (app) app->play_ui_sound(SOUND_OK);
            return true;
        }

        // If editing player name:
        if (is_editing_name()) {
            char* name = m_cfg.players[m_editing_player_name].name;
            size_t len = strlen(name);
            if (sym == SDLK_RETURN || sym == SDLK_ESCAPE) {
                finish_editing_name();
                if (app) app->play_ui_sound(SOUND_OK);
                return true;
            } else if (sym == SDLK_BACKSPACE) {
                if (len > 0) {
                    name[len - 1] = '\0';
                }
                return true;
            } else {
                int vk = 0;
                if (sym >= SDLK_a && sym <= SDLK_z) vk = 0x41 + (sym - SDLK_a);
                else if (sym >= SDLK_0 && sym <= SDLK_9) vk = 0x30 + (sym - SDLK_0);
                else if (sym == SDLK_SPACE) vk = 0x20;
                else if (sym == SDLK_MINUS) vk = 0xBD;
                else if (sym == SDLK_PERIOD) vk = 0xBE;

                char c = vk_to_ascii(vk, shift_down, caps_lock);
                if (c != '\0' && len < 10) {
                    name[len] = c;
                    name[len + 1] = '\0';
                }
                return true;
            }
        }

        // Global keys in options screen:
        if (sym == SDLK_ESCAPE) {
            if (app) {
                app->play_ui_sound(SOUND_CANCEL);
                reload_controls();
                app->change_scene(scene_t::TITLE);
            }
            return true;
        }
    }

    // Gamepad button press rebinding support
    if (event.type == SDL_JOYBUTTONDOWN && is_rebinding()) {
        int btn = event.jbutton.button;
        int vk = 1000 + btn; // Synthetic keycode for gamepad button
        apply_rebind(vk);
        if (app) app->play_ui_sound(SOUND_OK);
        return true;
    }

    // Mouse click handling
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        int mx = event.button.x;
        int my = event.button.y;

        // Substate 6: Control screen click handling
        if (m_substate == options_substate_t::CONTROL_SETTINGS) {
            // Check 4 player columns
            for (int p = 0; p < 4; ++p) {
                int col_x = 70 + p * 175;

                // Player name box click (y: 110..136)
                if (mx >= col_x && mx <= col_x + 155 && my >= 110 && my <= 136) {
                    start_editing_name(p);
                    if (app) app->play_ui_sound(SOUND_OK);
                    return true;
                }

                // Device toggle button (y: 145..170)
                if (mx >= col_x && mx <= col_x + 155 && my >= 145 && my <= 170) {
                    m_cfg.players[p].device = (m_cfg.players[p].device + 1) % 3;
                    m_cfg.players[p].keys[0] = m_cfg.players[p].device;
                    if (app) app->play_ui_sound(SOUND_OK);
                    return true;
                }

                // Action keys 1..7 (Up, Down, Left, Right, Attack, Jump, Defend) (y: 180 + k * 30)
                for (int k = 0; k < 7; ++k) {
                    int ky = 185 + k * 32;
                    if (mx >= col_x + 65 && mx <= col_x + 155 && my >= ky && my <= ky + 26) {
                        start_rebind(p, k + 1);
                        if (app) app->play_ui_sound(SOUND_OK);
                        return true;
                    }
                }
            }

            // Bottom control buttons:
            // "Defaults": (70, 440, 110, 32)
            if (mx >= 70 && mx <= 180 && my >= 440 && my <= 472) {
                reset_to_defaults();
                if (app) app->play_ui_sound(SOUND_JOIN);
                return true;
            }
            // "Display / Fullscreen": (200, 440, 160, 32)
            if (mx >= 200 && mx <= 360 && my >= 440 && my <= 472) {
                toggle_fullscreen(app);
                if (app) app->play_ui_sound(SOUND_OK);
                return true;
            }
            // "Auto Record: ON/OFF": (380, 440, 150, 32)
            if (mx >= 380 && mx <= 530 && my >= 440 && my <= 472) {
                set_auto_record(!is_auto_record_enabled());
                if (app) app->play_ui_sound(SOUND_OK);
                return true;
            }
            // "Save": (550, 440, 95, 32)
            if (mx >= 550 && mx <= 645 && my >= 440 && my <= 472) {
                save_controls();
                if (app) {
                    app->set_control_config(m_cfg);
                    app->play_ui_sound(SOUND_OK);
                    app->change_scene(scene_t::TITLE);
                }
                return true;
            }
            // "Cancel": (660, 440, 95, 32)
            if (mx >= 660 && mx <= 755 && my >= 440 && my <= 472) {
                reload_controls();
                if (app) {
                    app->play_ui_sound(SOUND_CANCEL);
                    app->change_scene(scene_t::TITLE);
                }
                return true;
            }
        } else if (m_substate == options_substate_t::PROFILE_SETTINGS) {
            // "Back": (340, 440, 110, 32)
            if (mx >= 340 && mx <= 450 && my >= 440 && my <= 472) {
                if (app) {
                    app->play_ui_sound(SOUND_CANCEL);
                    app->change_scene(scene_t::TITLE);
                }
                return true;
            }
        }
    }

    return false;
}

void options_ui_t::update(app_t* app) {
    (void)app;
    m_cursor_blink_ticks++;
    if (m_cursor_blink_ticks % 16 == 0) {
        m_cursor_visible = !m_cursor_visible;
    }
}

void options_ui_t::render(renderer_t& gfx, app_t* app) {
    if (m_substate == options_substate_t::CONTROL_SETTINGS) {
        render_control_screen(gfx, app);
    } else if (m_substate == options_substate_t::PROFILE_SETTINGS) {
        render_profile_screen(gfx, app);
    } else {
        render_display_screen(gfx, app);
    }
}

void options_ui_t::render_control_screen(renderer_t& gfx, app_t* app) {
    (void)app;
    // Background layer
    std::string bg_file = "data/ui/MENU_BACK1.bmp";
    SDL_Texture* bg_tex = gfx.load_texture(bg_file, true);
    if (bg_tex) {
        gfx.draw_sprite(bg_tex, nullptr, 0, 0);
    } else {
        gfx.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 14, 25, 65, 255, true);
    }

    // Semi-transparent overlay panel
    gfx.draw_rect(40, 40, 714, 460, 10, 20, 50, 220, true);
    gfx.draw_rect(40, 40, 714, 460, 70, 110, 190, 255, false);

    // Title banner
    gfx.draw_rect(40, 40, 714, 45, 25, 55, 120, 255, true);
    gfx.draw_text("CONTROL SETTINGS & DISPLAY OPTIONS", 200, 52, 255, 255, 255, 1);

    static const char* action_labels[] = {
        "UP", "DOWN", "LEFT", "RIGHT", "ATTACK", "JUMP", "DEFEND"
    };

    // Render 4 Player Columns
    for (int p = 0; p < 4; ++p) {
        int col_x = 70 + p * 175;

        // Player Column Frame
        gfx.draw_rect(col_x, 95, 155, 330, 20, 35, 80, 180, true);
        gfx.draw_rect(col_x, 95, 155, 330, 60, 90, 160, 255, false);

        // Player Name Box
        bool editing_this_name = (m_editing_player_name == p);
        if (editing_this_name) {
            gfx.draw_rect(col_x + 5, 105, 145, 28, 50, 80, 160, 255, true);
            gfx.draw_rect(col_x + 5, 105, 145, 28, 255, 230, 80, 255, false);
        } else {
            gfx.draw_rect(col_x + 5, 105, 145, 28, 30, 50, 110, 255, true);
        }

        std::string display_name = m_cfg.players[p].name;
        if (display_name.empty()) {
            display_name = "Player " + std::to_string(p + 1);
        }
        if (editing_this_name && m_cursor_visible) {
            display_name += "_";
        }
        gfx.draw_text(display_name.c_str(), col_x + 12, 112, 255, 255, 255, 1);

        // Device Mode Selector (Keyboard vs Gamepad)
        int dev = m_cfg.players[p].device;
        std::string dev_label = (dev == 0) ? "KEYBOARD" : ("GAMEPAD " + std::to_string(dev));
        gfx.draw_rect(col_x + 5, 140, 145, 26, 40, 65, 130, 255, true);
        gfx.draw_rect(col_x + 5, 140, 145, 26, 90, 130, 210, 255, false);
        gfx.draw_text(dev_label.c_str(), col_x + 25, 146, 200, 230, 255, 1);

        // Action Keys 1..7
        for (int k = 0; k < 7; ++k) {
            int ky = 180 + k * 32;

            // Action name label
            gfx.draw_text(action_labels[k], col_x + 10, ky + 6, 170, 195, 235, 1);

            // Key value box
            bool is_active_rebind = (m_rebind_player == p && m_rebind_action_idx == (k + 1));
            int key_code = m_cfg.players[p].keys[k + 1];

            if (is_active_rebind) {
                // Pulsing highlight when waiting for key
                uint8_t pulse = m_cursor_visible ? 255 : 120;
                gfx.draw_rect(col_x + 65, ky, 85, 26, 180, 60, 60, 255, true);
                gfx.draw_rect(col_x + 65, ky, 85, 26, pulse, pulse, 255, 255, false);
                gfx.draw_text("PRESS KEY", col_x + 70, ky + 6, 255, 255, 255, 1);
            } else {
                gfx.draw_rect(col_x + 65, ky, 85, 26, 25, 45, 95, 255, true);
                gfx.draw_rect(col_x + 65, ky, 85, 26, 80, 110, 180, 255, false);
                std::string kname = get_key_name(key_code);
                gfx.draw_text(kname.c_str(), col_x + 72, ky + 6, 230, 240, 255, 1);
            }
        }
    }

    // Bottom Action Buttons:
    // 1. Defaults Button
    gfx.draw_rect(70, 440, 110, 32, 35, 60, 120, 255, true);
    gfx.draw_rect(70, 440, 110, 32, 100, 150, 220, 255, false);
    gfx.draw_text("DEFAULTS", 88, 448, 220, 240, 255, 1);

    // 2. Fullscreen Button
    std::string fs_label = m_fullscreen ? "WINDOWED" : "FULLSCREEN";
    gfx.draw_rect(200, 440, 160, 32, 35, 60, 120, 255, true);
    gfx.draw_rect(200, 440, 160, 32, 100, 150, 220, 255, false);
    gfx.draw_text(fs_label.c_str(), 230, 448, 220, 240, 255, 1);

    // 3. Auto-Record Replay Toggle Button
    std::string rec_label = is_auto_record_enabled() ? "RECORD: ON" : "RECORD: OFF";
    gfx.draw_rect(380, 440, 150, 32, 35, 60, 120, 255, true);
    gfx.draw_rect(380, 440, 150, 32, 100, 150, 220, 255, false);
    gfx.draw_text(rec_label.c_str(), 400, 448, 220, 240, 255, 1);

    // 4. Save Button
    gfx.draw_rect(550, 440, 95, 32, 30, 120, 60, 255, true);
    gfx.draw_rect(550, 440, 95, 32, 80, 220, 120, 255, false);
    gfx.draw_text("SAVE", 578, 448, 255, 255, 255, 1);

    // 5. Cancel Button
    gfx.draw_rect(660, 440, 95, 32, 120, 40, 40, 255, true);
    gfx.draw_rect(660, 440, 95, 32, 220, 90, 90, 255, false);
    gfx.draw_text("CANCEL", 680, 448, 255, 255, 255, 1);

    // Instructions footer
    gfx.draw_text("Click any key cell to rebind. Press ESC to cancel. Backspace edits names.", 140, 485, 160, 190, 230, 1);
}

void options_ui_t::render_profile_screen(renderer_t& gfx, app_t* app) {
    (void)app;
    std::string bg_file = "data/ui/MENU_BACK1.bmp";
    SDL_Texture* bg_tex = gfx.load_texture(bg_file, true);
    if (bg_tex) {
        gfx.draw_sprite(bg_tex, nullptr, 0, 0);
    } else {
        gfx.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 15, 25, 60, 255, true);
    }

    // Panel box
    gfx.draw_rect(100, 50, 594, 440, 10, 20, 50, 220, true);
    gfx.draw_rect(100, 50, 594, 440, 70, 110, 190, 255, false);

    gfx.draw_text("PLAYER SYSTEM PROFILE & RECORDINGS", 220, 80, 255, 255, 255, 1);
    gfx.draw_text(("Name:  " + m_profile_name).c_str(), 150, 160, 220, 230, 255, 1);
    gfx.draw_text(("Email: " + m_profile_email).c_str(), 150, 210, 220, 230, 255, 1);
    gfx.draw_text(("Info:  " + m_profile_info).c_str(), 150, 260, 220, 230, 255, 1);

    std::string rec_label = "Auto Record Replays: " + std::string(is_auto_record_enabled() ? "ENABLED" : "DISABLED");
    gfx.draw_text(rec_label.c_str(), 150, 320, 180, 220, 255, 1);

    // Back Button
    gfx.draw_rect(340, 440, 110, 32, 35, 60, 120, 255, true);
    gfx.draw_rect(340, 440, 110, 32, 100, 150, 220, 255, false);
    gfx.draw_text("BACK", 375, 448, 255, 255, 255, 1);
}

void options_ui_t::render_display_screen(renderer_t& gfx, app_t* app) {
    (void)app;
    gfx.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 15, 25, 60, 255, true);
    gfx.draw_text("DISPLAY CONFIGURATION", 280, 60, 255, 255, 255, 1);
}

} // namespace lf2
