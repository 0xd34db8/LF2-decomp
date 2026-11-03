#include "app.h"
#include "app/options.h"
#include "menu.h"
#include "gameplay/ai.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <filesystem>

namespace lf2 {

void control_config_t::init_defaults() {
    // Authentic default controls from LF2 control.txt (0x00419a60 & 0x00423480)
    // Player 1 (Slot 0): Numpad 8, 2, 4, 6, 5, 0, +
    players[0].device = 0;
    players[0].keys[0] = 0;   // keyboard
    players[0].keys[1] = 104; // VK_NUMPAD8 (Up)
    players[0].keys[2] = 98;  // VK_NUMPAD2 (Down)
    players[0].keys[3] = 100; // VK_NUMPAD4 (Left)
    players[0].keys[4] = 102; // VK_NUMPAD6 (Right)
    players[0].keys[5] = 101; // VK_NUMPAD5 (Attack)
    players[0].keys[6] = 96;  // VK_NUMPAD0 (Jump)
    players[0].keys[7] = 107; // VK_ADD '+' (Defend)

    // Player 2 (Slot 1): W, X, A, D, S, Tab, `
    players[1].device = 0;
    players[1].keys[0] = 0;
    players[1].keys[1] = 87;  // 'W' (Up)
    players[1].keys[2] = 88;  // 'X' (Down)
    players[1].keys[3] = 65;  // 'A' (Left)
    players[1].keys[4] = 68;  // 'D' (Right)
    players[1].keys[5] = 83;  // 'S' (Attack)
    players[1].keys[6] = 9;   // VK_TAB (Jump)
    players[1].keys[7] = 192; // VK_OEM_3 '`' (Defend)

    // Player 3 (Slot 2): Up, Down, Left, Right, Enter, RShift, RCtrl
    players[2].device = 0;
    players[2].keys[0] = 0;
    players[2].keys[1] = 38;  // VK_UP (Up)
    players[2].keys[2] = 40;  // VK_DOWN (Down)
    players[2].keys[3] = 37;  // VK_LEFT (Left)
    players[2].keys[4] = 39;  // VK_RIGHT (Right)
    players[2].keys[5] = 13;  // VK_RETURN (Attack)
    players[2].keys[6] = 16;  // VK_SHIFT (Jump)
    players[2].keys[7] = 17;  // VK_CONTROL (Defend)

    // Player 4 (Slot 3): I, ,, J, L, K, Space, .
    players[3].device = 0;
    players[3].keys[0] = 0;
    players[3].keys[1] = 73;  // 'I' (Up)
    players[3].keys[2] = 188; // VK_OEM_COMMA ',' (Down)
    players[3].keys[3] = 74;  // 'J' (Left)
    players[3].keys[4] = 76;  // 'L' (Right)
    players[3].keys[5] = 75;  // 'K' (Attack)
    players[3].keys[6] = 32;  // VK_SPACE (Jump)
    players[3].keys[7] = 190; // VK_OEM_PERIOD '.' (Defend)

    std::strcpy(players[0].name, "1");
    std::strcpy(players[1].name, "2");
    std::strcpy(players[2].name, "3");
    std::strcpy(players[3].name, "4");
    demo_mode = 1;
    replay_mode = 0;
}

bool control_config_t::load_from_file(const std::string& path) {
    FILE* fp = std::fopen(path.c_str(), "r");
    if (!fp) {
        return false;
    }

    for (int p = 0; p < 4; ++p) {
        for (int k = 0; k < 11; ++k) {
            if (std::fscanf(fp, "%d", &players[p].keys[k]) != 1) {
                std::fclose(fp);
                return false;
            }
        }
        players[p].device = players[p].keys[0];
    }

    if (std::fscanf(fp, "%15s %15s %15s %15s",
                    players[0].name, players[1].name,
                    players[2].name, players[3].name) == 4) {
        for (int p = 0; p < 4; ++p) {
            for (int i = 0; players[p].name[i]; ++i) {
                if (players[p].name[i] == '`') {
                    players[p].name[i] = ' ';
                }
            }
        }
    }

    std::fscanf(fp, "%d", &demo_mode);
    std::fscanf(fp, "%d", &replay_mode);

    std::fclose(fp);
    return true;
}

app_t::app_t()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_width(WINDOW_WIDTH)
    , m_height(WINDOW_HEIGHT)
    , m_fullscreen(false)
    , m_running(false)
    , m_in_battle(false)
    , m_active_state(1)
    , m_mouse_x(0)
    , m_mouse_y(0)
    , m_mouse_lbutton(0)
    , m_mouse_rbutton(0)
    , m_cheat_lf2net('u')
    , m_cheat_herofighter('u')
    , m_cheat_lf2net_idx(0)
    , m_cheat_herofighter_idx(0)
    , m_cheat_abc_idx(0)
    , m_cheat_dev_mode(0)
    , m_frame_counter(0)
    , m_total_ticks(0)
    , m_scene(scene_t::TITLE)
    , m_menu_bg_idx(1 + (std::rand() % 13))
    , m_title_cursor(0)
    , m_mode_cursor(0)
    , m_selected_mode(MODE_VS)
    , m_modal_cpu_open(false)
    , m_cpu_count(1)
    , m_loading_timer(0)
    , m_loading_filename("")
    , m_battle_paused(false)
    , m_stage_loaded(false)
    , m_num_fighters(0)
{
    m_control_cfg.init_defaults();
    reset_input();
    std::memset(m_prev_key_states, 0x75, sizeof(m_prev_key_states));
    std::memset(&m_world, 0, sizeof(m_world));
    std::memset(m_fighters, 0, sizeof(m_fighters));
    std::memset(m_loaded_files, 0, sizeof(m_loaded_files));

    for (int i = 0; i < 8; ++i) {
        m_slots[i].joined = false;
        m_slots[i].is_ready = false;
        m_slots[i].is_human = (i == 0);
        m_slots[i].roster_idx = (i == 0) ? 1 : 0; // P1 default Davis, others Random
        m_slots[i].team = (i == 0) ? 1 : 2;
        m_slots[i].countdown = 5;
        m_slots[i].countdown_timer = 0;
    }
}

app_t::~app_t() {
    shutdown();
}

void app_t::reset_input() {
    std::memset(m_key_states, 0x75, sizeof(m_key_states));
    m_mouse_lbutton = 0;
    m_mouse_rbutton = 0;
}

bool app_t::init(int width, int height, bool fullscreen, bool test_mode) {
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;

    // Check if running from outside build/ directory but data is next to executable
    char* base_path = SDL_GetBasePath();
    if (base_path) {
        std::filesystem::path exe_dir(base_path);
        SDL_free(base_path);
        if (!std::filesystem::exists("data/data.txt") && !std::filesystem::exists("data/control.txt")) {
            if (std::filesystem::exists(exe_dir / "data/data.txt") || std::filesystem::exists(exe_dir / "data/control.txt")) {
                std::error_code ec;
                std::filesystem::current_path(exe_dir, ec);
            }
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        std::cerr << "[LF2] SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    uint32_t window_flags = SDL_WINDOW_SHOWN;
    if (m_fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }

    m_window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_width,
        m_height,
        window_flags
    );

    if (!m_window) {
        std::cerr << "[LF2] SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!m_renderer) {
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
        if (!m_renderer) {
            std::cerr << "[LF2] SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            SDL_Quit();
            return false;
        }
    }

    SDL_RenderSetLogicalSize(m_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    m_graphics.set_sdl_renderer(m_renderer);

    // Verify presence of authentic game data folders ('data', 'bg', 'sprite')
    bool has_game_data = std::filesystem::exists("data/data.txt") ||
                         std::filesystem::exists("data/control.txt");

    if (!has_game_data) {
        char* base = SDL_GetBasePath();
        std::string exe_folder = base ? base : "./";
        if (base) SDL_free(base);

        std::string prompt_msg =
            "Little Fighter 2 game data was not found!\n\n"
            "Please copy or place the original LF2 game data folders into this build directory:\n"
            "  - " + exe_folder + "data\\\n"
            "  - " + exe_folder + "bg\\\n"
            "  - " + exe_folder + "sprite\\\n\n"
            "Then restart the game.";

        std::cerr << "======================================================================\n"
                  << "[LF2 NOTICE] Authentic game data missing!\n"
                  << prompt_msg << "\n"
                  << "======================================================================\n" << std::endl;

        if (!test_mode) {
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_WARNING,
                "Little Fighter 2 - Game Data Required",
                prompt_msg.c_str(),
                m_window
            );
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            SDL_Quit();
            return false;
        }
    }

    // Initialize Audio System and preload authentic UI sounds matching 0x0043cf40 (WinMain)
    if (get_audio_system().init()) {
        get_audio_system().load_sound(SOUND_JOIN, "data/m_join.wav");
        get_audio_system().load_sound(SOUND_OK, "data/m_ok.wav");
        get_audio_system().load_sound(SOUND_CANCEL, "data/m_cancel.wav");
        get_audio_system().load_sound(SOUND_PASS, "data/m_pass.wav");
        get_audio_system().load_sound(SOUND_END, "data/m_end.wav");
    }

    // Load authentic Player Controls from control.txt (0x00423480)
    m_control_cfg.load_from_file("data/control.txt");

    change_scene(scene_t::TITLE);
    reset_input();
    m_running = true;
    return true;
}

void app_t::shutdown() {
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_loaded_files[i]) {
            dat_loader_t::free_file_resources(m_loaded_files[i]);
            delete m_loaded_files[i];
            m_loaded_files[i] = nullptr;
        }
    }
    m_graphics.clear_textures();
    m_graphics.set_sdl_renderer(nullptr);
    get_audio_system().cleanup();

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}

void app_t::toggle_fullscreen() {
    m_fullscreen = !m_fullscreen;
    if (m_window) {
        SDL_SetWindowFullscreen(m_window, m_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    }
}

uint8_t app_t::sdl_key_to_vk(SDL_Keycode key, SDL_Scancode scancode) {
    (void)scancode;
    if (key >= SDLK_a && key <= SDLK_z) {
        return static_cast<uint8_t>('A' + (key - SDLK_a));
    }
    if (key >= SDLK_0 && key <= SDLK_9) {
        return static_cast<uint8_t>('0' + (key - SDLK_0));
    }

    switch (key) {
    case SDLK_BACKSPACE:   return VK_LF2_BACKSPACE;
    case SDLK_TAB:         return VK_LF2_TAB;
    case SDLK_RETURN:
    case SDLK_KP_ENTER:    return VK_LF2_RETURN;
    case SDLK_PAUSE:       return VK_LF2_PAUSE;
    case SDLK_ESCAPE:      return VK_LF2_ESCAPE;
    case SDLK_SPACE:       return VK_LF2_SPACE;
    case SDLK_LEFT:        return VK_LF2_LEFT;
    case SDLK_UP:          return VK_LF2_UP;
    case SDLK_RIGHT:       return VK_LF2_RIGHT;
    case SDLK_DOWN:        return VK_LF2_DOWN;

    case SDLK_LSHIFT:
    case SDLK_RSHIFT:      return VK_LF2_SHIFT;
    case SDLK_LCTRL:
    case SDLK_RCTRL:       return VK_LF2_CONTROL;
    case SDLK_LALT:
    case SDLK_RALT:        return VK_LF2_MENU;

    case SDLK_KP_0:        return VK_LF2_NUMPAD0;   // 0x60 (96) (P1 Jump)
    case SDLK_KP_1:        return VK_LF2_NUMPAD1;   // 0x61 (97)
    case SDLK_KP_2:        return VK_LF2_NUMPAD2;   // 0x62 (98) (P1 Down)
    case SDLK_KP_3:        return VK_LF2_NUMPAD3;   // 0x63 (99)
    case SDLK_KP_4:        return VK_LF2_NUMPAD4;   // 0x64 (100) (P1 Left)
    case SDLK_KP_5:        return VK_LF2_NUMPAD5;   // 0x65 (101) (P1 Attack)
    case SDLK_KP_6:        return VK_LF2_NUMPAD6;   // 0x66 (102) (P1 Right)
    case SDLK_KP_7:        return VK_LF2_NUMPAD7;   // 0x67 (103)
    case SDLK_KP_8:        return VK_LF2_NUMPAD8;   // 0x68 (104) (P1 Up)
    case SDLK_KP_9:        return VK_LF2_NUMPAD9;   // 0x69 (105)
    case SDLK_KP_MULTIPLY: return VK_LF2_MULTIPLY;  // 0x6A (106)
    case SDLK_KP_PLUS:     return VK_LF2_ADD;       // 0x6B (107) (P1 Defend)
    case SDLK_KP_MINUS:    return VK_LF2_SUBTRACT;  // 0x6D (109)
    case SDLK_KP_PERIOD:   return VK_LF2_DECIMAL;   // 0x6E (110)
    case SDLK_KP_DIVIDE:   return VK_LF2_DIVIDE;    // 0x6F (111)

    case SDLK_F1:          return VK_LF2_F1;
    case SDLK_F2:          return VK_LF2_F2;
    case SDLK_F3:          return VK_LF2_F3;
    case SDLK_F4:          return VK_LF2_F4;
    case SDLK_F5:          return VK_LF2_F5;
    case SDLK_F6:          return VK_LF2_F6;
    case SDLK_F7:          return VK_LF2_F7;
    case SDLK_F8:          return VK_LF2_F8;
    case SDLK_F9:          return VK_LF2_F9;
    case SDLK_F10:         return VK_LF2_F10;
    case SDLK_F11:         return VK_LF2_F11;
    case SDLK_F12:         return VK_LF2_F12;

    case SDLK_SEMICOLON:   return VK_LF2_OEM_1;     // 0xBA (186)
    case SDLK_EQUALS:      return VK_LF2_OEM_PLUS;  // 0xBB (187)
    case SDLK_COMMA:       return VK_LF2_OEM_COMMA; // 0xBC (188) (P4 Down)
    case SDLK_MINUS:       return VK_LF2_OEM_MINUS; // 0xBD (189)
    case SDLK_PERIOD:      return VK_LF2_OEM_PERIOD;// 0xBE (190) (P4 Defend)
    case SDLK_SLASH:       return VK_LF2_OEM_2;     // 0xBF (191)
    case SDLK_BACKQUOTE:   return VK_LF2_OEM_3;     // 0xC0 (192) (P2 Defend)
    case SDLK_LEFTBRACKET: return VK_LF2_OEM_4;     // 0xDB (219)
    case SDLK_BACKSLASH:   return VK_LF2_OEM_5;     // 0xDC (220)
    case SDLK_RIGHTBRACKET:return VK_LF2_OEM_6;     // 0xDD (221)
    case SDLK_QUOTE:       return VK_LF2_OEM_7;     // 0xDE (222)

    default:
        if (key < 256) {
            return static_cast<uint8_t>(key);
        }
        return 0;
    }
}

void app_t::on_key_down(uint8_t vk) {
    m_key_states[vk] = 'd';

    // Secret Cheat Code 1: "lf2.net"
    switch (m_cheat_lf2net_idx) {
    case 0: if (vk == 'L') m_cheat_lf2net_idx = 1; break;
    case 1: if (vk == 'F') m_cheat_lf2net_idx = 2; else if (vk != 'L') m_cheat_lf2net_idx = 0; break;
    case 2: if (vk == '2') m_cheat_lf2net_idx = 3; else if (vk == 'L') m_cheat_lf2net_idx = 1; else m_cheat_lf2net_idx = 0; break;
    case 3: if (vk == VK_LF2_OEM_PERIOD || vk == 0xBE || vk == '.') m_cheat_lf2net_idx = 4; else if (vk == 'L') m_cheat_lf2net_idx = 1; else m_cheat_lf2net_idx = 0; break;
    case 4: if (vk == 'N') m_cheat_lf2net_idx = 5; else if (vk == 'L') m_cheat_lf2net_idx = 1; else m_cheat_lf2net_idx = 0; break;
    case 5: if (vk == 'E') m_cheat_lf2net_idx = 6; else if (vk == 'L') m_cheat_lf2net_idx = 1; else m_cheat_lf2net_idx = 0; break;
    case 6:
        if (vk == 'T') m_cheat_lf2net = 'd';
        if (vk == 'L') m_cheat_lf2net_idx = 1; else m_cheat_lf2net_idx = 0;
        break;
    default: m_cheat_lf2net_idx = 0; break;
    }

    // Secret Cheat Code 2: "herofighter.com"
    switch (m_cheat_herofighter_idx) {
    case 0: if (vk == 'H') m_cheat_herofighter_idx = 1; break;
    case 1: if (vk == 'E') m_cheat_herofighter_idx = 2; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 2: if (vk == 'R') m_cheat_herofighter_idx = 3; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 3: if (vk == 'O') m_cheat_herofighter_idx = 4; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 4: if (vk == 'F') m_cheat_herofighter_idx = 5; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 5: if (vk == 'I') m_cheat_herofighter_idx = 6; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 6: if (vk == 'G') m_cheat_herofighter_idx = 7; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 7: if (vk == 'H') m_cheat_herofighter_idx = 8; else m_cheat_herofighter_idx = 0; break;
    case 8: if (vk == 'T') m_cheat_herofighter_idx = 9; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 9: if (vk == 'E') m_cheat_herofighter_idx = 10; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 10: if (vk == 'R') m_cheat_herofighter_idx = 11; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 11: if (vk == VK_LF2_OEM_PERIOD || vk == 0xBE || vk == '.') m_cheat_herofighter_idx = 12; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 12: if (vk == 'C') m_cheat_herofighter_idx = 13; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 13: if (vk == 'O') m_cheat_herofighter_idx = 14; else if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0; break;
    case 14:
        if (vk == 'M') m_cheat_herofighter = 'd';
        if (vk == 'H') m_cheat_herofighter_idx = 1; else m_cheat_herofighter_idx = 0;
        break;
    default: m_cheat_herofighter_idx = 0; break;
    }

    // Secret Dev Mode Cheat: "A-B-C"
    if (m_cheat_abc_idx == 0) {
        if (vk == 'A') m_cheat_abc_idx = 1;
    } else if (m_cheat_abc_idx == 1) {
        if (vk == 'B') m_cheat_abc_idx = 2;
        else if (vk != 'A') m_cheat_abc_idx = 0;
    } else if (m_cheat_abc_idx == 2) {
        if (vk == 'C') {
            m_cheat_abc_idx = 3;
            m_cheat_dev_mode = 1;
        } else if (vk != 'B') {
            m_cheat_abc_idx = 0;
        }
    }
}

void app_t::on_key_up(uint8_t vk) {
    m_key_states[vk] = 'u';
}

void app_t::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (m_scene == scene_t::OPTIONS && m_options_ui) {
            if (m_options_ui->handle_event(event, this)) {
                continue;
            }
        }

        switch (event.type) {
        case SDL_QUIT:
            m_running = false;
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                m_active_state = 1;
            } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                m_active_state = 0;
            }
            break;

        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
                toggle_fullscreen();
                break;
            }
            uint8_t vk = sdl_key_to_vk(event.key.keysym.sym, event.key.keysym.scancode);
            if (vk != 0) {
                on_key_down(vk);
            }
            break;
        }

        case SDL_KEYUP: {
            uint8_t vk = sdl_key_to_vk(event.key.keysym.sym, event.key.keysym.scancode);
            if (vk != 0) {
                on_key_up(vk);
            }
            break;
        }

        case SDL_MOUSEMOTION:
            m_mouse_x = static_cast<int16_t>(event.motion.x);
            m_mouse_y = static_cast<int16_t>(event.motion.y);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouse_lbutton = 1;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouse_rbutton = 1;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouse_lbutton = 0;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouse_rbutton = 0;
            }
            break;

        default:
            break;
        }
    }
}

bool app_t::is_player_key_down(int player_idx, ctrl_action_t action) const {
    if (player_idx < 0 || player_idx >= 4) return false;
    int key_idx = static_cast<int>(action);
    if (key_idx < 1 || key_idx > 7) return false;
    uint8_t vk = static_cast<uint8_t>(m_control_cfg.players[player_idx].keys[key_idx]);
    return is_key_down(vk);
}

bool app_t::is_player_key_just_pressed(int player_idx, ctrl_action_t action) const {
    if (player_idx < 0 || player_idx >= 4) return false;
    int key_idx = static_cast<int>(action);
    if (key_idx < 1 || key_idx > 7) return false;
    uint8_t vk = static_cast<uint8_t>(m_control_cfg.players[player_idx].keys[key_idx]);
    return is_key_just_pressed(vk);
}

bool app_t::is_any_player_key_just_pressed(ctrl_action_t action) const {
    for (int p = 0; p < 4; ++p) {
        if (is_player_key_just_pressed(p, action)) return true;
    }
    return false;
}

void app_t::play_ui_sound(uint32_t sound_id) {
    get_audio_system().play_sound(sound_id, false);
}

void app_t::change_scene(scene_t next_scene) {
    m_scene = next_scene;
    m_in_battle = (m_scene == scene_t::BATTLE);

    if (m_scene == scene_t::TITLE) {
        m_menu_bg_idx = 1 + (std::rand() % 13);
    } else if (m_scene == scene_t::OPTIONS) {
        if (!m_options_ui) {
            m_options_ui = std::make_unique<options_ui_t>();
        }
        m_options_ui->init(this);
    } else if (m_scene == scene_t::CHAR_SELECT) {
        for (int i = 0; i < 8; ++i) {
            m_slots[i].joined = false;
            m_slots[i].is_ready = false;
            m_slots[i].is_human = (i < 4);
            m_slots[i].roster_idx = (i == 0) ? 1 : 0; // P1 default Davis, others Random
            m_slots[i].team = (i % 2 == 0) ? 1 : 2;
            m_slots[i].countdown = 5;
            m_slots[i].countdown_timer = 0;
        }
        m_modal_cpu_open = false;
        m_cpu_count = 1;
    } else if (m_scene == scene_t::LOADING) {
        m_loading_timer = 0;
        const auto& roster = get_game_roster();
        int idx = m_slots[0].roster_idx;
        if (idx >= 0 && idx < static_cast<int>(roster.size())) {
            m_loading_filename = roster[idx].dat_file;
        } else {
            m_loading_filename = "data/davis.dat";
        }
    }
}

void app_t::update_title() {
    if (is_any_player_key_just_pressed(ctrl_action_t::UP)) {
        m_title_cursor = (m_title_cursor + 4) % 5;
        play_ui_sound(SOUND_OK);
    } else if (is_any_player_key_just_pressed(ctrl_action_t::DOWN)) {
        m_title_cursor = (m_title_cursor + 1) % 5;
        play_ui_sound(SOUND_OK);
    }

    if (is_any_player_key_just_pressed(ctrl_action_t::ATTACK)) {
        play_ui_sound(SOUND_OK);
        if (m_title_cursor == 0) {
            change_scene(scene_t::MODE_SELECT);
        } else if (m_title_cursor == 2) {
            change_scene(scene_t::OPTIONS);
            if (m_options_ui) {
                m_options_ui->set_substate(options_substate_t::CONTROL_SETTINGS);
            }
        } else if (m_title_cursor == 3) {
            change_scene(scene_t::OPTIONS);
            if (m_options_ui) {
                m_options_ui->set_substate(options_substate_t::PROFILE_SETTINGS);
            }
        }
    }

    if (is_any_player_key_just_pressed(ctrl_action_t::DEFEND) || is_key_just_pressed(VK_LF2_ESCAPE)) {
        play_ui_sound(SOUND_CANCEL);
        m_running = false;
    }
}

void app_t::render_title() {
    m_graphics.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 11, 28, 92, 255, true);

    std::string back_path = "data/ui/MENU_BACK" + std::to_string(m_menu_bg_idx) + ".bmp";
    SDL_Texture* back_tex = m_graphics.load_texture(back_path, true);
    if (back_tex) {
        m_graphics.draw_sprite(back_tex, nullptr, 0, 0);
    }

    // Authentic Title Logo from MENU_CLIP.bmp slice 1: (0, 41, 496, 80)
    SDL_Texture* clip_tex = m_graphics.load_texture("data/ui/MENU_CLIP.bmp", true);
    if (clip_tex) {
        SDL_Rect src_logo = { 0, 41, 496, 80 };
        m_graphics.draw_sprite(clip_tex, &src_logo, 200, 70);
    } else {
        SDL_Texture* slogan_tex = m_graphics.load_texture("data/ui/SLOGAN.bmp", true);
        if (slogan_tex) {
            m_graphics.draw_sprite(slogan_tex, nullptr, 160, 40);
        }
    }

    m_graphics.draw_text("小朋友齊打交 (二) ver 2.0a", 480, 158, 200, 220, 255, 1);

    static const char* title_items[] = {
        "game start (開始遊戲)",
        "network game (連線遊戲)",
        "control settings (控制設定)",
        "recording info (錄影資料)",
        "official website (官方網頁)"
    };

    SDL_Texture* words0_tex = m_graphics.load_texture("data/ui/WORDS0.bmp", true);
    SDL_Texture* words1_tex = m_graphics.load_texture("data/ui/WORDS1.bmp", true);

    for (int i = 0; i < 5; ++i) {
        int y = 220 + i * 32;
        SDL_Rect src_slice = { 0, i * 28, 251, 28 };
        if (i == m_title_cursor) {
            m_graphics.draw_rect(275, y - 4, 270, 26, 45, 75, 165, 180, true);
            m_graphics.draw_rect(275, y - 4, 270, 26, 150, 190, 255, 255, false);
            if (words0_tex) {
                m_graphics.draw_sprite(words0_tex, &src_slice, 285, y - 2);
            } else {
                m_graphics.draw_text(title_items[i], 285, y, 255, 255, 255, 1, false);
            }
        } else {
            if (words1_tex) {
                m_graphics.draw_sprite(words1_tex, &src_slice, 285, y - 2);
            } else {
                m_graphics.draw_text(title_items[i], 285, y, 140, 165, 220, 1);
            }
        }
    }

    m_graphics.draw_text("by Marti Wong, Starsky Wong", 540, 475, 120, 160, 220, 1);
    m_graphics.draw_text("1999-2008, all rights reserved", 540, 492, 120, 160, 220, 1);
    m_graphics.draw_text("http://www.LittleFighter.com", 540, 509, 120, 160, 220, 1);
}

void app_t::update_mode_select() {
    if (is_any_player_key_just_pressed(ctrl_action_t::UP)) {
        m_mode_cursor = (m_mode_cursor + 7) % 8;
        play_ui_sound(SOUND_OK);
    } else if (is_any_player_key_just_pressed(ctrl_action_t::DOWN)) {
        m_mode_cursor = (m_mode_cursor + 1) % 8;
        play_ui_sound(SOUND_OK);
    }

    if (is_any_player_key_just_pressed(ctrl_action_t::ATTACK)) {
        play_ui_sound(SOUND_OK);
        if (m_mode_cursor == 7) {
            change_scene(scene_t::TITLE);
        } else {
            m_selected_mode = static_cast<game_mode_t>(m_mode_cursor);
            change_scene(scene_t::CHAR_SELECT);
        }
    }

    if (is_any_player_key_just_pressed(ctrl_action_t::DEFEND) || is_key_just_pressed(VK_LF2_ESCAPE)) {
        play_ui_sound(SOUND_CANCEL);
        change_scene(scene_t::TITLE);
    }
}

void app_t::render_mode_select() {
    m_graphics.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 11, 28, 92, 255, true);

    std::string back_path = "data/ui/MENU_BACK" + std::to_string(m_menu_bg_idx) + ".bmp";
    SDL_Texture* back_tex = m_graphics.load_texture(back_path, true);
    if (back_tex) {
        m_graphics.draw_sprite(back_tex, nullptr, 0, 0);
    }

    // Authentic Title Logo from MENU_CLIP.bmp slice 1: (0, 41, 496, 80)
    SDL_Texture* clip_tex = m_graphics.load_texture("data/ui/MENU_CLIP.bmp", true);
    if (clip_tex) {
        SDL_Rect src_logo = { 0, 41, 496, 80 };
        m_graphics.draw_sprite(clip_tex, &src_logo, 200, 70);
    }

    m_graphics.draw_text("小朋友齊打交 (二) ver 2.0a", 480, 158, 200, 220, 255, 1);

    static const char* mode_items[] = {
        "VS mode (對決模式)",
        "Stage mode (闖關模式)",
        "1 on 1 Championship (淘汰賽)",
        "2 on 2 Championship (淘汰賽)",
        "Battle mode (戰爭模式)",
        "Demo (遊戲示範)",
        "Playback Recording (錄影重播)",
        "Quit (離開遊戲)"
    };

    static const SDL_Rect mc3_mode_rects[] = {
        { 32, 331, 210, 22 }, // 0: VS mode
        { 18, 358, 238, 24 }, // 1: Stage mode
        {  0, 385, 275, 23 }, // 2: 1 on 1 Championship
        {  0, 412, 275, 24 }, // 3: 2 on 2 Championship
        { 33, 438, 206, 24 }, // 4: Battle mode
        { 42, 466, 188, 23 }, // 5: Demo
        {  0, 493, 277, 25 }, // 6: Playback Recording
        { 55, 521, 165, 23 }  // 7: Quit
    };

    SDL_Texture* mc3_tex = m_graphics.load_texture("data/ui/MENU_CLIP3.bmp", true);

    for (int i = 0; i < 8; ++i) {
        int y = 205 + i * 28;
        if (i == m_mode_cursor) {
            m_graphics.draw_rect(250, y - 3, 330, 24, 45, 75, 165, 180, true);
            m_graphics.draw_rect(250, y - 3, 330, 24, 150, 190, 255, 255, false);
            if (mc3_tex) {
                m_graphics.draw_sprite(mc3_tex, &mc3_mode_rects[i], 265, y);
            } else {
                m_graphics.draw_text(mode_items[i], 265, y, 255, 255, 255, 1, false);
            }
        } else {
            if (mc3_tex) {
                m_graphics.draw_sprite(mc3_tex, &mc3_mode_rects[i], 265, y);
            } else {
                m_graphics.draw_text(mode_items[i], 265, y, 140, 165, 220, 1);
            }
        }
    }

    m_graphics.draw_text("by Marti Wong, Starsky Wong", 540, 475, 120, 160, 220, 1);
    m_graphics.draw_text("1999-2008, all rights reserved", 540, 492, 120, 160, 220, 1);
    m_graphics.draw_text("http://www.LittleFighter.com", 540, 509, 120, 160, 220, 1);
}

void app_t::update_char_select() {
    const auto& roster = get_game_roster();
    int roster_count = static_cast<int>(roster.size());

    // 1. CPU Modal Dialog
    if (m_modal_cpu_open) {
        if (is_any_player_key_just_pressed(ctrl_action_t::LEFT)) {
            m_cpu_count = (m_cpu_count > 0) ? (m_cpu_count - 1) : 0;
            play_ui_sound(SOUND_OK);
        } else if (is_any_player_key_just_pressed(ctrl_action_t::RIGHT)) {
            m_cpu_count = (m_cpu_count < 7) ? (m_cpu_count + 1) : 7;
            play_ui_sound(SOUND_OK);
        }

        if (is_any_player_key_just_pressed(ctrl_action_t::ATTACK)) {
            // Fill CPU slots for remaining unjoined slots
            int cpus_needed = m_cpu_count;
            for (int i = 0; i < 8 && cpus_needed > 0; ++i) {
                if (!m_slots[i].joined) {
                    m_slots[i].joined = true;
                    m_slots[i].is_human = false;
                    m_slots[i].is_ready = true;
                    m_slots[i].roster_idx = ((i + 1) % (roster_count - 1)) + 1;
                    m_slots[i].team = (i % 2 == 1) ? 2 : 1;
                    cpus_needed--;
                }
            }
            play_ui_sound(SOUND_PASS);
            change_scene(scene_t::LOADING);
            return;
        }

        if (is_any_player_key_just_pressed(ctrl_action_t::DEFEND)) {
            m_modal_cpu_open = false;
            for (int p = 0; p < 4; ++p) {
                if (m_slots[p].joined && m_slots[p].is_human) {
                    m_slots[p].is_ready = false;
                    m_slots[p].countdown = 5;
                    m_slots[p].countdown_timer = 0;
                }
            }
            play_ui_sound(SOUND_CANCEL);
            return;
        }
        return;
    }

    // 2. Poll player slots 0..3 for human input using configured player keys
    int num_joined = 0;
    int num_ready_done = 0;

    for (int p = 0; p < 4; ++p) {
        if (!m_slots[p].joined) {
            // Authentic Join check: player p presses their own Attack key
            if (is_player_key_just_pressed(p, ctrl_action_t::ATTACK)) {
                m_slots[p].joined = true;
                m_slots[p].is_human = true;
                m_slots[p].is_ready = false;
                m_slots[p].countdown = 5;
                m_slots[p].countdown_timer = 0;
                play_ui_sound(SOUND_JOIN);
            }
        } else {
            num_joined++;
            if (!m_slots[p].is_ready) {
                if (is_player_key_just_pressed(p, ctrl_action_t::LEFT)) {
                    m_slots[p].roster_idx = (m_slots[p].roster_idx + roster_count - 1) % roster_count;
                    play_ui_sound(SOUND_OK);
                } else if (is_player_key_just_pressed(p, ctrl_action_t::RIGHT)) {
                    m_slots[p].roster_idx = (m_slots[p].roster_idx + 1) % roster_count;
                    play_ui_sound(SOUND_OK);
                }

                if (is_player_key_just_pressed(p, ctrl_action_t::UP)) {
                    m_slots[p].team = (m_slots[p].team % 4) + 1;
                    play_ui_sound(SOUND_OK);
                } else if (is_player_key_just_pressed(p, ctrl_action_t::DOWN)) {
                    m_slots[p].team = (m_slots[p].team == 1) ? 4 : (m_slots[p].team - 1);
                    play_ui_sound(SOUND_OK);
                }

                if (is_player_key_just_pressed(p, ctrl_action_t::ATTACK)) {
                    m_slots[p].is_ready = true;
                    m_slots[p].countdown = 5;
                    m_slots[p].countdown_timer = 0;
                    play_ui_sound(SOUND_OK);
                } else if (is_player_key_just_pressed(p, ctrl_action_t::DEFEND)) {
                    m_slots[p].joined = false;
                    play_ui_sound(SOUND_CANCEL);
                }
            } else {
                // Player is locked in! Authentic mechanic: Jump button skips countdown
                if (is_player_key_just_pressed(p, ctrl_action_t::JUMP)) {
                    m_slots[p].countdown = 0;
                }

                if (is_player_key_just_pressed(p, ctrl_action_t::DEFEND)) {
                    m_slots[p].is_ready = false;
                    m_slots[p].countdown = 5;
                    m_slots[p].countdown_timer = 0;
                    play_ui_sound(SOUND_CANCEL);
                } else {
                    if (m_slots[p].countdown > 0) {
                        m_slots[p].countdown_timer++;
                        if (m_slots[p].countdown_timer >= 30) {
                            m_slots[p].countdown_timer = 0;
                            m_slots[p].countdown--;
                        }
                    } else {
                        num_ready_done++;
                    }
                }
            }
        }
    }

    // 3. If no players are joined, Defend or Escape returns to mode selection
    if (num_joined == 0) {
        if (is_any_player_key_just_pressed(ctrl_action_t::DEFEND) || is_key_just_pressed(VK_LF2_ESCAPE)) {
            play_ui_sound(SOUND_CANCEL);
            change_scene(scene_t::MODE_SELECT);
            return;
        }
    }

    // 4. If all joined players are ready and finished countdown
    if (num_joined > 0 && num_ready_done == num_joined) {
        if (m_selected_mode == MODE_VS) {
            m_modal_cpu_open = true;
            m_cpu_count = 1;
            play_ui_sound(SOUND_PASS);
        } else {
            play_ui_sound(SOUND_PASS);
            change_scene(scene_t::LOADING);
        }
    }
}

void app_t::render_char_select() {
    m_graphics.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 16, 255, true);

    // Blit authentic CHARMENU.bmp at (40, 33) matching 0x00429730
    SDL_Texture* charmenu_tex = m_graphics.load_texture("data/ui/CHARMENU.bmp", false);
    if (charmenu_tex) {
        m_graphics.draw_sprite(charmenu_tex, nullptr, 40, 33);
    }

    const auto& roster = get_game_roster();
    // Authentic alternating CMA.bmp and CMA2.bmp for blinking join prompt
    const char* cma_file = ((m_frame_counter / 15) % 2 == 0) ? "data/ui/CMA.bmp" : "data/ui/CMA2.bmp";
    SDL_Texture* cma_tex = m_graphics.load_texture(cma_file, true);
    SDL_Texture* rface_tex = m_graphics.load_texture("data/ui/RFACE.bmp", true);

    // 8 card slots matching 0x00429730 geometry:
    // card_x = 147 + col * 153, card_y = 94 + row * 212
    for (int i = 0; i < 8; ++i) {
        int col = i % 4;
        int row = i / 4;
        int card_x = 147 + col * 153;
        int card_y = 94 + row * 212;

        if (!m_slots[i].joined) {
            if (cma_tex) {
                m_graphics.draw_sprite(cma_tex, nullptr, card_x, card_y + 27);
            }
            m_graphics.draw_text("Join?", card_x + 35, card_y + 125, 90, 150, 255, 1);
        } else {
            int r_idx = m_slots[i].roster_idx;
            if (r_idx == 0) {
                if (rface_tex) {
                    m_graphics.draw_sprite(rface_tex, nullptr, card_x, card_y);
                }
                m_graphics.draw_text("Random", card_x + 28, card_y + 147, 100, 180, 255, 1);
            } else if (r_idx > 0 && r_idx < static_cast<int>(roster.size())) {
                SDL_Texture* head_tex = m_graphics.load_texture(roster[r_idx].head_f, true);
                if (head_tex) {
                    m_graphics.draw_sprite(head_tex, nullptr, card_x, card_y);
                }
                m_graphics.draw_text(roster[r_idx].name, card_x + 28, card_y + 147, 255, 255, 255, 1);
            }

            std::string player_str = m_slots[i].is_human ? std::to_string(i + 1) : "CPU";
            m_graphics.draw_text(player_str, card_x + 45, card_y + 125, 255, 255, 255, 1);

            std::string team_str = "Team " + std::to_string(m_slots[i].team);
            m_graphics.draw_text(team_str, card_x + 28, card_y + 169, 100, 200, 255, 1);

            if (m_slots[i].is_ready) {
                // Golden highlight border around locked-in slot
                m_graphics.draw_rect(card_x - 1, card_y - 1, 122, 122, 255, 215, 0, 255, false);

                // Authentic Countdown Numbers (CM5..CM1.bmp) centered over portrait card
                int cd = std::clamp(m_slots[i].countdown, 1, 5);
                std::string cm_file = "data/ui/CM" + std::to_string(cd) + ".bmp";
                SDL_Texture* cm_tex = m_graphics.load_texture(cm_file, true);
                if (cm_tex) {
                    m_graphics.draw_sprite(cm_tex, nullptr, card_x + 34, card_y + 31);
                }
            }
        }
    }

    // Modal popup: "How many Computer Players?"
    if (m_modal_cpu_open) {
        m_graphics.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 140, true);

        SDL_Texture* cmc_tex = m_graphics.load_texture("data/ui/CMC.bmp", false);
        if (cmc_tex) {
            m_graphics.draw_sprite(cmc_tex, nullptr, 214, 219);
        }

        for (int n = 0; n <= 7; ++n) {
            int num_x = 286 + n * 30;
            int num_y = 286;
            bool selected = (n == m_cpu_count);
            m_graphics.draw_text(std::to_string(n), num_x, num_y, selected ? 255 : 170, selected ? 255 : 170, 255, 1);

            if (selected) {
                m_graphics.draw_rect(280 + n * 30, 283, 21, 21, 255, 255, 255, 255, false);
            }
        }
    }
}

void app_t::update_loading() {
    m_loading_timer++;

    if (m_loading_timer == 10) {
        m_loading_filename = "bg/sys/hkc/bg.dat";
    } else if (m_loading_timer == 20) {
        start_battle();
    } else if (m_loading_timer >= 40) {
        change_scene(scene_t::BATTLE);
    }
}

void app_t::render_loading() {
    m_graphics.draw_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 11, 28, 92, 255, true);

    // Authentic full-screen loading background with chibi lineup & Now Loading
    SDL_Texture* wait_tex = m_graphics.load_texture("data/ui/MENU_WAIT.bmp", false);
    if (wait_tex) {
        m_graphics.draw_sprite(wait_tex, nullptr, 0, 0);
    }

    // Dynamic file loading progress indicator (matching authentic loading screen)
    if (!m_loading_filename.empty()) {
        m_graphics.draw_text(m_loading_filename, 607, 75, 255, 255, 255, 1);
    }
}

void app_t::start_battle() {
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_loaded_files[i]) {
            dat_loader_t::free_file_resources(m_loaded_files[i]);
            delete m_loaded_files[i];
            m_loaded_files[i] = nullptr;
        }
    }
    std::memset(&m_world, 0, sizeof(m_world));
    std::memset(m_fighters, 0, sizeof(m_fighters));
    m_num_fighters = 0;
    m_battle_paused = false;

    // Load Stage
    const std::string bg_candidates[] = {
        "bg/sys/hkc/bg.dat",
        "bg/template/1/bg.dat"
    };
    m_stage_loaded = false;
    for (const auto& bg_path : bg_candidates) {
        if (m_background.load_from_file(bg_path)) {
            m_stage_loaded = true;
            m_camera.set_stage_width(m_background.width);
            break;
        }
    }

    const auto& roster = get_game_roster();
    int32_t z_mid = m_stage_loaded ? ((m_background.zboundary_min + m_background.zboundary_max) / 2) : 250;

    for (int i = 0; i < 8; ++i) {
        if (!m_slots[i].joined) continue;

        int r_idx = m_slots[i].roster_idx;
        if (r_idx <= 0 || r_idx >= static_cast<int>(roster.size())) {
            // Authentic random pick: select among available characters
            r_idx = 1 + (std::rand() % (roster.size() - 1));
        }

        const auto& entry = roster[r_idx];
        file_t* loaded_file = new file_t();
        bool file_ok = dat_loader_t::load_file(loaded_file, entry.dat_file, entry.id, TYPE_CHARACTER);
        if (!file_ok) {
            delete loaded_file;
            continue;
        }
        m_loaded_files[m_num_fighters] = loaded_file;

        object_t* fighter = &m_fighters[m_num_fighters];
        object_init(fighter);
        fighter->file = loaded_file;
        fighter->team = m_slots[i].team;
        fighter->owner = static_cast<uint32_t>(i);
        fighter->hp = 500;
        fighter->dark_hp = 500;
        fighter->max_hp = 500;
        fighter->mp = 500;
        fighter->invincible_time = 75;

        fighter->x = (m_num_fighters == 0) ? 250 : (450 + (m_num_fighters - 1) * 130);
        fighter->y = 0;
        fighter->z = z_mid + ((m_num_fighters % 2 == 0) ? -20 : 20);
        fighter->x_position = fighter->x;
        fighter->y_position = 0.0;
        fighter->z_position = fighter->z;
        fighter->facing = (m_num_fighters == 0) ? FACING_RIGHT : FACING_LEFT;
        fighter->frame_id1 = 0;

        m_world.objects[m_num_fighters] = fighter;
        m_world.is_object_exists[m_num_fighters] = 1;
        m_num_fighters++;
    }

    m_camera.x = 0;
    m_camera.y = 0;
}

void app_t::return_to_menu() {
    play_ui_sound(SOUND_CANCEL);
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_loaded_files[i]) {
            dat_loader_t::free_file_resources(m_loaded_files[i]);
            delete m_loaded_files[i];
            m_loaded_files[i] = nullptr;
        }
    }
    std::memset(&m_world, 0, sizeof(m_world));
    std::memset(m_fighters, 0, sizeof(m_fighters));
    m_num_fighters = 0;
    m_battle_paused = false;

    change_scene(scene_t::MODE_SELECT);
}

void app_t::update_battle() {
    if (is_key_just_pressed(VK_LF2_F4) || is_key_just_pressed(VK_LF2_ESCAPE)) {
        return_to_menu();
        return;
    }

    if (is_key_just_pressed(VK_LF2_F1)) {
        m_battle_paused = !m_battle_paused;
        play_ui_sound(SOUND_OK);
    }

    if (m_battle_paused) {
        if (!is_key_just_pressed(VK_LF2_F2)) {
            return;
        }
    }

    // Process inputs for all active fighters (Players 0..3 read their control.txt mappings)
    for (uint32_t i = 0; i < m_num_fighters; ++i) {
        object_t* fighter = &m_fighters[i];
        if (!fighter->file) continue;

        uint32_t slot = fighter->owner;
        if (slot < 4 && m_slots[slot].is_human) {
            input_state_t input;
            input.left   = is_player_key_down(slot, ctrl_action_t::LEFT);
            input.right  = is_player_key_down(slot, ctrl_action_t::RIGHT);
            input.up     = is_player_key_down(slot, ctrl_action_t::UP);
            input.down   = is_player_key_down(slot, ctrl_action_t::DOWN);
            input.attack = is_player_key_down(slot, ctrl_action_t::ATTACK);
            input.jump   = is_player_key_down(slot, ctrl_action_t::JUMP);
            input.defend = is_player_key_down(slot, ctrl_action_t::DEFEND);

            object_handle_input(fighter, input);
        } else {
            ai_tick(&m_world, i, AI_NORMAL);
        }
    }

    int32_t z_min = m_stage_loaded ? m_background.zboundary_min : 0;
    int32_t z_max = m_stage_loaded ? m_background.zboundary_max : 400;
    int32_t stage_w = m_stage_loaded ? m_background.width : 2000;

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        object_t* obj = m_world.objects[i];
        if (!obj || !obj->file) continue;

        object_update_physics(obj);
        object_update_motion(obj, z_min, z_max, stage_w);
        object_apply_ground_friction(obj, 0.6);
        object_tick_frame(obj);
    }

    // Hitbox interactions & attacks
    m_world.process_all_attacks();

    if (m_num_fighters > 0) {
        m_camera.update_target(m_fighters[0].x);
    }
}

void app_t::render_battle() {
    SDL_SetRenderDrawColor(m_renderer, 10, 10, 16, 255);
    SDL_RenderClear(m_renderer);

    if (m_stage_loaded) {
        m_graphics.draw_background(&m_background, m_camera.x, m_camera.y);
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        const object_t* obj = m_world.objects[i];
        if (!obj || !obj->file) continue;

        if (m_stage_loaded && !m_background.shadow_path.empty()) {
            SDL_Texture* shadow_tex = m_graphics.load_texture(m_background.shadow_path, true);
            if (shadow_tex) {
                m_graphics.draw_shadow(shadow_tex, obj->x, obj->z, m_camera.x, m_camera.y,
                                       m_background.shadow_w, m_background.shadow_h);
            }
        }
        m_graphics.draw_character(obj->file, obj, m_camera.x, m_camera.y);
    }

    // In-game HUD
    const auto& roster = get_game_roster();
    for (uint32_t i = 0; i < m_num_fighters; ++i) {
        int32_t hud_x = 10 + (i % 4) * 190;
        int32_t hud_y = 10 + (i / 4) * 45;

        int r_idx = m_slots[i].roster_idx;
        std::string name = (r_idx >= 0 && r_idx < static_cast<int>(roster.size())) ? roster[r_idx].name : "Fighter";
        std::string small_path = (r_idx >= 0 && r_idx < static_cast<int>(roster.size())) ? roster[r_idx].head_s : "";

        if (!small_path.empty()) {
            SDL_Texture* face_tex = m_graphics.load_texture(small_path, true);
            if (face_tex) {
                m_graphics.draw_sprite(face_tex, nullptr, hud_x, hud_y);
            }
        }

        std::string label = (i == 0) ? ("1P " + name) : (std::to_string(i + 1) + "P " + name);
        m_graphics.draw_text(label, hud_x + 36, hud_y, 255, 255, 255, 1);

        int32_t hp = std::max(0, m_fighters[i].hp);
        int32_t max_hp = std::max(1, m_fighters[i].max_hp);
        int32_t hp_w = (hp * 100) / max_hp;

        m_graphics.draw_rect(hud_x + 36, hud_y + 11, 102, 9, 40, 40, 40, 200, true);
        m_graphics.draw_rect(hud_x + 37, hud_y + 12, hp_w, 7, 220, 40, 40, 255, true);
        m_graphics.draw_rect(hud_x + 36, hud_y + 11, 102, 9, 180, 180, 180, 255, false);

        int32_t mp = std::max(0, m_fighters[i].mp);
        int32_t mp_w = (mp * 100) / 500;

        m_graphics.draw_rect(hud_x + 36, hud_y + 22, 102, 7, 30, 30, 50, 200, true);
        m_graphics.draw_rect(hud_x + 37, hud_y + 23, mp_w, 5, 40, 120, 240, 255, true);
        m_graphics.draw_rect(hud_x + 36, hud_y + 22, 102, 7, 140, 160, 200, 255, false);
    }

    if (m_battle_paused) {
        m_graphics.draw_text("PAUSED", 360, 240, 255, 255, 0, 3);
    }
}

void app_t::update() {
    switch (m_scene) {
    case scene_t::TITLE:
        update_title();
        break;
    case scene_t::MODE_SELECT:
        update_mode_select();
        break;
    case scene_t::CHAR_SELECT:
        update_char_select();
        break;
    case scene_t::LOADING:
        update_loading();
        break;
    case scene_t::BATTLE:
        update_battle();
        break;
    case scene_t::OPTIONS:
        if (m_options_ui) {
            m_options_ui->update(this);
        }
        break;
    }

    std::memcpy(m_prev_key_states, m_key_states, sizeof(m_key_states));
}

void app_t::render() {
    if (!m_renderer) return;

    switch (m_scene) {
    case scene_t::TITLE:
        render_title();
        break;
    case scene_t::MODE_SELECT:
        render_mode_select();
        break;
    case scene_t::CHAR_SELECT:
        render_char_select();
        break;
    case scene_t::LOADING:
        render_loading();
        break;
    case scene_t::BATTLE:
        render_battle();
        break;
    case scene_t::OPTIONS:
        if (m_options_ui) {
            m_options_ui->render(m_graphics, this);
        }
        break;
    }

    SDL_RenderPresent(m_renderer);
}

void app_t::run() {
    uint32_t last_time = SDL_GetTicks();
    m_running = true;

    while (m_running) {
        process_events();
        if (!m_running) break;

        const uint32_t step = TICK_STEP_BATTLE_MS; // Authentic 30.3 FPS across all scenes (33 ms)

        uint32_t now = SDL_GetTicks();
        if (now - last_time > step) {
            now = SDL_GetTicks();
            if (now - last_time > MAX_ACCUMULATOR_LAG_MS) {
                last_time = SDL_GetTicks() - MAX_ACCUMULATOR_LAG_MS;
            }
            last_time += step;

            update();
            render();
        }

        now = SDL_GetTicks();
        int32_t remaining = static_cast<int32_t>((last_time - now) + step);
        if (remaining > 0) {
            if (remaining > static_cast<int32_t>(MAX_SLEEP_CHUNK_MS)) {
                remaining = static_cast<int32_t>(MAX_SLEEP_CHUNK_MS);
            }
            SDL_Delay(static_cast<uint32_t>(remaining));
        }

        m_frame_counter = (m_frame_counter + 1) % FRAME_COUNTER_MODULO;
        m_total_ticks++;
    }
}

options_ui_t* app_t::get_options_ui() {
    if (!m_options_ui) {
        m_options_ui = std::make_unique<options_ui_t>();
        m_options_ui->init(this);
    }
    return m_options_ui.get();
}

} // namespace lf2
