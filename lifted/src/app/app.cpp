#include "app.h"
#include "app/options.h"
#include "menu.h"
#include "gameplay/ai.h"
#include "gameplay/grapple.h"
#include "gameplay/weapon.h"
#include "core/random.h"
#include "audio/bgm.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <filesystem>

namespace lf2 {

void app_control_config_t::init_defaults() {
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
    std::strcpy(profile_name, "<No name>");
    std::strcpy(profile_email, "<No email>");
    std::strcpy(profile_info, "<No info>");
}

bool app_control_config_t::load_from_file(const std::string& path) {
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

    auto read_profile_line = [](FILE* f, char* dest, size_t max_len) {
        char buf[128] = {0};
        if (std::fgets(buf, sizeof(buf), f)) {
            size_t len = std::strlen(buf);
            while (len > 0 && (buf[len - 1] == '\r' || buf[len - 1] == '\n')) {
                buf[--len] = '\0';
            }
            if (len > 0) {
                std::strncpy(dest, buf, max_len - 1);
                dest[max_len - 1] = '\0';
            }
        }
    };

    int ch = std::fgetc(fp);
    while (ch == '\r' || ch == '\n') {
        ch = std::fgetc(fp);
    }
    if (ch != EOF) {
        std::ungetc(ch, fp);
        read_profile_line(fp, profile_name, sizeof(profile_name));
        read_profile_line(fp, profile_email, sizeof(profile_email));
        read_profile_line(fp, profile_info, sizeof(profile_info));
    }

    std::fclose(fp);
    return true;
}

bool app_control_config_t::save_to_file(const std::string& path) const {
    FILE* fp = std::fopen(path.c_str(), "w");
    if (!fp) {
        return false;
    }

    for (int p = 0; p < 4; ++p) {
        for (int k = 0; k < 11; ++k) {
            std::fprintf(fp, "%d%s", players[p].keys[k], (k == 10) ? "\n" : " ");
        }
    }

    for (int p = 0; p < 4; ++p) {
        char safe_name[16] = {0};
        std::strncpy(safe_name, players[p].name, 15);
        if (safe_name[0] == '\0') {
            std::snprintf(safe_name, sizeof(safe_name), "%d", p + 1);
        }
        for (int i = 0; safe_name[i]; ++i) {
            if (safe_name[i] == ' ') {
                safe_name[i] = '`';
            }
        }
        std::fprintf(fp, "%s%s", safe_name, (p == 3) ? "\n" : " ");
    }

    std::fprintf(fp, "%d\n", demo_mode);
    std::fprintf(fp, "%d\n", replay_mode);
    std::fprintf(fp, "%s\n", profile_name[0] ? profile_name : "<No name>");
    std::fprintf(fp, "%s\n", profile_email[0] ? profile_email : "<No email>");
    std::fprintf(fp, "%s", profile_info[0] ? profile_info : "<No info>");

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

    // Initialize Audio System and preload authentic UI & battle fixed sounds matching 0x0043cf40 (WinMain)
    if (get_audio_system().init()) {
        get_audio_system().load_sound(SOUND_JOIN, "data/m_join.wav");
        get_audio_system().load_sound(SOUND_OK, "data/m_ok.wav");
        get_audio_system().load_sound(SOUND_CANCEL, "data/m_cancel.wav");
        get_audio_system().load_sound(SOUND_PASS, "data/m_pass.wav");
        get_audio_system().load_sound(SOUND_END, "data/m_end.wav");
        get_audio_system().preload_fixed_battle_sounds();
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

    // Authentic F11 / F12 volume control (0x004028A0)
    if (vk == VK_LF2_F11) {
        m_volume_level = std::max(0, m_volume_level - 50);
        m_volume_display_timer = 50;
        get_audio_system().set_master_volume((m_volume_level * SDL_MIX_MAXVOLUME) / 1000);
        play_ui_sound(SOUND_OK);
    } else if (vk == VK_LF2_F12) {
        m_volume_level = std::min(1000, m_volume_level + 50);
        m_volume_display_timer = 50;
        get_audio_system().set_master_volume((m_volume_level * SDL_MIX_MAXVOLUME) / 1000);
        play_ui_sound(SOUND_OK);
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
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        object_init(&m_fighters[i]);
        m_world.objects[i] = &m_fighters[i];
    }
    m_num_fighters = 0;
    m_battle_paused = false;

    // Reset 0x0041BC90 Master Battle Loop state machine
    m_input_phase = 0;
    m_pause_req = 0;
    m_pause_next = 0;
    m_pause_state = 0;
    m_fkey_state = 0;
    m_fast_forward = false;
    m_unlimited_mp = false;
    m_sky_weapon_cmd = 0;
    m_recover_cmd = 0;
    m_f6_uses = 0;
    m_f7_uses = 0;
    m_f8_uses = 0;
    m_f9_uses = 0;
    m_shake = 0;
    m_counter_12 = 0;
    m_counter_3 = 0;
    m_round_counter = 0;
    m_winning_team = -1;
    m_battle_elapsed = 0;
    m_hud_visible = true;
    m_replay_panning = false;
    m_replay_cam_x = -1000;
    m_replay_cam_vx = 0;
    m_net_seq = 0;
    m_last_net_sync = SyncResult::OK;

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
    get_audio_system().set_camera_x(m_camera.x);
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        m_world.files[i] = m_loaded_files[i];
    }

    // Mode-specific initialization (0x0041C920 & 0x00438B40)
    if (m_selected_mode == MODE_STAGE) {
        m_stage_mgr.load_stages("data/stage.dat");
        m_stage_mgr.start_stage(1, &m_world);
    } else if (m_selected_mode == MODE_BATTLE) {
        m_battle_mgr.reset();
        battle_army_t army1;
        army1.army_id = 0;
        army1.team_id = 1;
        apply_authentic_battle_preset(army1, 0, 3);
        m_battle_mgr.add_army(army1);
        battle_army_t army2;
        army2.army_id = 1;
        army2.team_id = 2;
        apply_authentic_battle_preset(army2, 1, 3);
        m_battle_mgr.add_army(army2);
    }
}

void app_t::return_to_menu() {
    play_ui_sound(SOUND_CANCEL);
    get_audio_system().stop_all();
    if (m_replay_recorder.is_recording()) {
        m_replay_recorder.cancel_recording();
    }
    if (m_replay_player.is_open()) {
        m_replay_player.close();
    }
    m_has_playback_replay = false;
    m_in_battle = false;
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_loaded_files[i]) {
            dat_loader_t::free_file_resources(m_loaded_files[i]);
            delete m_loaded_files[i];
            m_loaded_files[i] = nullptr;
        }
    }
    std::memset(&m_world, 0, sizeof(m_world));
    std::memset(m_fighters, 0, sizeof(m_fighters));
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        object_init(&m_fighters[i]);
        m_world.objects[i] = &m_fighters[i];
    }
    m_num_fighters = 0;
    m_battle_paused = false;

    // Reset 0x0041BC90 Master Battle Loop state machine
    m_input_phase = 0;
    m_pause_req = 0;
    m_pause_next = 0;
    m_pause_state = 0;
    m_fkey_state = 0;
    m_fast_forward = false;
    m_unlimited_mp = false;
    m_sky_weapon_cmd = 0;
    m_recover_cmd = 0;
    m_f6_uses = 0;
    m_f7_uses = 0;
    m_f8_uses = 0;
    m_f9_uses = 0;
    m_shake = 0;
    m_counter_12 = 0;
    m_counter_3 = 0;
    m_round_counter = 0;
    m_winning_team = -1;
    m_battle_elapsed = 0;
    m_hud_visible = true;
    m_replay_panning = false;
    m_replay_cam_x = -1000;
    m_replay_cam_vx = 0;
    m_net_seq = 0;
    m_last_net_sync = SyncResult::OK;

    change_scene(scene_t::MODE_SELECT);
}

file_t* app_t::find_loaded_file(uint32_t file_id) const {
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_world.files[i] && m_world.files[i]->id == file_id) {
            return m_world.files[i];
        }
    }
    for (uint32_t i = 0; i < MAX_FILES; ++i) {
        if (m_loaded_files[i] && m_loaded_files[i]->id == file_id) {
            return m_loaded_files[i];
        }
    }
    return nullptr;
}

int32_t app_t::find_free_dynamic_slot() const {
    for (uint32_t i = 50; i < MAX_OBJECTS; ++i) {
        if (m_world.is_object_exists[i] == 0) {
            if (!m_world.objects[i]) {
                const_cast<app_t*>(this)->m_world.objects[i] = const_cast<object_t*>(&m_fighters[i]);
            }
            return static_cast<int32_t>(i);
        }
    }
    return -1;
}

void app_t::clear_vrest_for_slot(int32_t slot) {
    if (slot < 0 || slot >= static_cast<int32_t>(MAX_OBJECTS)) return;
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (m_world.is_object_exists[i] != 0 && m_world.objects[i]) {
            m_world.objects[i]->vrest_of_objects[slot] = 0;
        }
    }
}

void app_t::dispatch_fkey_action(uint8_t fkey_vk, replay_frame_10_t& rec_out) {
    const bool stage_fkeys_ok = (m_selected_mode == MODE_VS || m_cheat_herofighter == 'd');
    switch (fkey_vk) {
    case 0xFE: // Secret lf2.net toggle (0x00416C70)
        rec_out.unlock_flags |= REPLAY_UNLOCK_LF2NET;
        m_cheat_lf2net = (m_cheat_lf2net == 'd') ? 'u' : 'd';
        play_ui_sound(SOUND_OK);
        break;
    case 0xFF: // Secret herofighter.com toggle (0x00416CA0)
        rec_out.unlock_flags |= REPLAY_UNLOCK_HEROFIGHTER;
        m_cheat_herofighter = (m_cheat_herofighter == 'd') ? 'u' : 'd';
        play_ui_sound(SOUND_OK);
        break;
    case VK_LF2_F1: // Pause toggle (0x00416DD0)
        m_pause_req = 1 - m_pause_state;
        m_pause_next = m_pause_req;
        m_battle_paused = (m_pause_req == 1);
        play_ui_sound(SOUND_OK);
        break;
    case VK_LF2_F2: // Single-frame step (0x00416DF0)
        m_pause_next = 1;
        m_pause_req = 0;
        m_battle_paused = false;
        break;
    case VK_LF2_F3: // Lock F6-F9 keys (0x00416E10)
        rec_out.func_flags |= REPLAY_FKEY_F3;
        m_fkey_state = 2;
        break;
    case VK_LF2_F4: // Match exit / round trigger (0x00416CD0)
        m_pause_state = 0;
        m_pause_req = 0;
        m_pause_next = 0;
        m_battle_paused = false;
        m_fast_forward = false;
        if (m_has_playback_replay) {
            if (m_replay_player.is_open()) {
                m_replay_player.close();
            }
            m_has_playback_replay = false;
            m_selected_mode = MODE_PLAYBACK;
            m_round_counter = 0;
            if (m_window) return_to_menu();
        } else if (m_selected_mode != MODE_1ON1 && m_selected_mode != MODE_2ON2) {
            m_round_counter = 350;
        } else {
            if (m_replay_recorder.is_recording() && m_round_counter < 101) {
                m_replay_recorder.cancel_recording();
            }
            m_round_counter = 0;
            if (m_window) return_to_menu();
        }
        break;
    case VK_LF2_F5: // Simulation speed toggle (0x00416E30)
        m_fast_forward = !m_fast_forward;
        m_key_states[VK_LF2_F5] = 'u';
        break;
    case VK_LF2_F6: // Unlimited MP toggle (0x00416E60)
        if (m_fkey_state < 2 && stage_fkeys_ok) {
            rec_out.func_flags |= REPLAY_FKEY_F6;
            m_unlimited_mp = !m_unlimited_mp;
            m_f6_uses++;
            m_fkey_state = 1;
        }
        break;
    case VK_LF2_F7: // Recover HP/MP (0x00416EB0)
        if (m_fkey_state < 2 && stage_fkeys_ok) {
            rec_out.func_flags |= REPLAY_FKEY_F7;
            if (m_round_counter == 0) {
                m_recover_cmd = 1 - m_recover_cmd;
                m_f7_uses++;
                m_fkey_state = 1;
            }
        }
        break;
    case VK_LF2_F8: // Drop weapons from sky (0x00416F10)
        if (m_fkey_state < 2 && stage_fkeys_ok) {
            rec_out.func_flags |= REPLAY_FKEY_F8;
            if (m_round_counter == 0) {
                m_f8_uses++;
                m_sky_weapon_cmd = 1;
                m_fkey_state = 1;
            }
        }
        break;
    case VK_LF2_F9: // Destroy items / stage enemies (0x00416F60)
        if (m_fkey_state < 2 && stage_fkeys_ok) {
            rec_out.func_flags |= REPLAY_FKEY_F9;
            if (m_round_counter == 0) {
                m_f9_uses++;
                m_sky_weapon_cmd = 2;
                m_fkey_state = 1;
            }
        }
        break;
    default:
        break;
    }
}

void app_t::dispatch_replay_fkey_flags(const replay_frame_10_t& rec, replay_frame_10_t& rec_out) {
    if (rec.unlock_flags & REPLAY_UNLOCK_LF2NET) dispatch_fkey_action(0xFE, rec_out);
    if (rec.unlock_flags & REPLAY_UNLOCK_HEROFIGHTER) dispatch_fkey_action(0xFF, rec_out);
    if (rec.func_flags & REPLAY_FKEY_F3) dispatch_fkey_action(VK_LF2_F3, rec_out);
    if (rec.func_flags & REPLAY_FKEY_F6) dispatch_fkey_action(VK_LF2_F6, rec_out);
    if (rec.func_flags & REPLAY_FKEY_F7) dispatch_fkey_action(VK_LF2_F7, rec_out);
    if (rec.func_flags & REPLAY_FKEY_F8) dispatch_fkey_action(VK_LF2_F8, rec_out);
    if (rec.func_flags & REPLAY_FKEY_F9) dispatch_fkey_action(VK_LF2_F9, rec_out);
}

void app_t::step_battle_frame() {
    // 1. Two-frame input phase alternation (0 <-> 1) & phase-0 pause latch
    m_input_phase = (m_input_phase + 1) & 1;
    if (m_input_phase == 0) {
        m_pause_state = m_pause_req;
        m_pause_req = m_pause_next;
    }
    const bool paused = (m_pause_state == 1);
    m_battle_paused = paused;

    // 2. Replay viewer HUD toggle (F6) & manual camera pan (Left/Right/Down)
    if (m_has_playback_replay) {
        if (is_key_down(VK_LF2_F6)) {
            m_hud_visible = !m_hud_visible;
            m_key_states[VK_LF2_F6] = 'u';
        }
        if (is_key_down(VK_LF2_LEFT) || is_key_down(VK_LF2_RIGHT)) {
            if (!m_replay_panning) {
                m_replay_cam_x = m_camera.x;
                m_replay_panning = true;
            }
            if (is_key_down(VK_LF2_LEFT)) m_replay_cam_vx -= 5;
            if (is_key_down(VK_LF2_RIGHT)) m_replay_cam_vx += 5;
        }
        if (is_key_down(VK_LF2_DOWN)) {
            m_replay_panning = false;
            m_replay_cam_vx = 0;
        } else if (m_replay_panning) {
            m_replay_cam_x += m_replay_cam_vx;
            m_replay_cam_vx = (m_replay_cam_vx * 6) / 7;
        } else {
            m_replay_cam_vx = 0;
        }
    }

    replay_frame_10_t local_rec{};
    replay_frame_10_t playback_rec{};
    bool checksum_ok = true;
    if (m_has_playback_replay && m_replay_player.is_open() && !paused && m_input_phase == 0) {
        if (m_replay_player.read_frame_10(playback_rec, compute_active_hp_sum(m_world), checksum_ok)) {
            if (!checksum_ok) {
                m_replay_player.close();
                m_has_playback_replay = false;
                m_selected_mode = MODE_PLAYBACK;
                if (m_window) return_to_menu();
                return;
            }
        }
    }

    const int32_t unlock_chars = (m_cheat_lf2net == 'd') ? 1 : 0;
    const int32_t z_min = m_stage_loaded ? m_background.zboundary_min : 0;
    const int32_t z_max = m_stage_loaded ? m_background.zboundary_max : 400;
    const int32_t stage_w = m_stage_loaded ? m_background.width : 2000;

    ai_world_params_t ai_params;
    ai_params.mode = static_cast<int32_t>(m_selected_mode);
    ai_params.difficulty = 1;
    ai_params.stage_width = stage_w;
    ai_params.zboundary_min = z_min;
    ai_params.zboundary_max = z_max;
    ai_params.stage_bound = stage_w;
    ai_params.stage_last_phase = 0;
    ai_params.random_game = (m_selected_mode == MODE_DEMO);
    ai_params.unlock_chars = unlock_chars;

    const bool net_active = (m_net_mgr != nullptr && m_net_mgr->is_connected());
    net_packet_t local_pkt{};
    net_packet_t remote_pkt{};
    network_manager_t::init_packet(local_pkt);

    bool input_tick_done[MAX_OBJECTS]{};
    if (!paused && !m_has_playback_replay && !net_active) {
        for (uint32_t i = 0; i < 8; ++i) {
            if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
            uint32_t slot = m_world.objects[i]->owner;
            if (slot < 4 && m_slots[slot].joined && m_slots[slot].is_human && m_selected_mode != MODE_DEMO) {
                input_state_t in{};
                in.left   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::LEFT);
                in.right  = is_player_key_down(static_cast<int>(slot), ctrl_action_t::RIGHT);
                in.up     = is_player_key_down(static_cast<int>(slot), ctrl_action_t::UP);
                in.down   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::DOWN);
                in.attack = is_player_key_down(static_cast<int>(slot), ctrl_action_t::ATTACK);
                in.jump   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::JUMP);
                in.defend = is_player_key_down(static_cast<int>(slot), ctrl_action_t::DEFEND);
                local_rec.inputs[i] = network_manager_t::pack_input(in);
                object_handle_input(m_world.objects[i], in, m_round_counter == 0, unlock_chars);
                input_tick_done[i] = true;
            } else if (slot < 8 && m_slots[slot].joined) {
                ai_tick(&m_world, i, ai_params);
                input_tick_done[i] = true;
            }
        }
    } else if (!paused && net_active) {
        for (uint32_t i = 0; i < 8; ++i) {
            if (!m_world.is_object_exists[i] || !m_world.objects[i]) continue;
            uint32_t slot = m_world.objects[i]->owner;
            if (slot < 4 && m_slots[slot].joined && m_slots[slot].is_human) {
                input_state_t in{};
                in.left   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::LEFT);
                in.right  = is_player_key_down(static_cast<int>(slot), ctrl_action_t::RIGHT);
                in.up     = is_player_key_down(static_cast<int>(slot), ctrl_action_t::UP);
                in.down   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::DOWN);
                in.attack = is_player_key_down(static_cast<int>(slot), ctrl_action_t::ATTACK);
                in.jump   = is_player_key_down(static_cast<int>(slot), ctrl_action_t::JUMP);
                in.defend = is_player_key_down(static_cast<int>(slot), ctrl_action_t::DEFEND);
                local_pkt.player_inputs[i] = network_manager_t::pack_input(in);
                local_rec.inputs[i] = local_pkt.player_inputs[i];
            }
        }
    }

    // 3. Phase-0 F1-F9 dispatch & lockstep synchronization (0x0041BC90 / 0x0041C5F0)
    if (m_input_phase == 0) {
        if (!net_active) {
            if (m_has_playback_replay) {
                if (is_key_down(VK_LF2_F4)) { m_key_states[VK_LF2_F4] = 'u'; dispatch_fkey_action(VK_LF2_F4, local_rec); }
                if (is_key_down(VK_LF2_F5)) { m_key_states[VK_LF2_F5] = 'u'; dispatch_fkey_action(VK_LF2_F5, local_rec); }
                if (is_key_down(VK_LF2_F1)) { m_key_states[VK_LF2_F1] = 'u'; dispatch_fkey_action(VK_LF2_F1, local_rec); }
                if (is_key_down(VK_LF2_F2)) { m_key_states[VK_LF2_F2] = 'u'; dispatch_fkey_action(VK_LF2_F2, local_rec); }
                dispatch_replay_fkey_flags(playback_rec, local_rec);
            } else {
                const uint8_t fkeys[] = {
                    VK_LF2_F4, VK_LF2_F1, VK_LF2_F2, VK_LF2_F3,
                    VK_LF2_F5, VK_LF2_F6, VK_LF2_F7, VK_LF2_F8, VK_LF2_F9
                };
                for (uint8_t fk : fkeys) {
                    if (is_key_down(fk)) {
                        m_key_states[fk] = 'u';
                        dispatch_fkey_action(fk, local_rec);
                    }
                }
            }
        } else {
            if (is_key_down(VK_LF2_F1)) { local_pkt.func_keys_1 |= NET_FKEY1_F1; m_key_states[VK_LF2_F1] = 'u'; }
            if (is_key_down(VK_LF2_F2)) { local_pkt.func_keys_1 |= NET_FKEY1_F2; m_key_states[VK_LF2_F2] = 'u'; }
            if (is_key_down(VK_LF2_F3)) { local_pkt.func_keys_2 |= NET_FKEY2_F3; m_key_states[VK_LF2_F3] = 'u'; }
            if (is_key_down(VK_LF2_F4)) { local_pkt.func_keys_1 |= NET_FKEY1_F4; m_key_states[VK_LF2_F4] = 'u'; }
            if (is_key_down(VK_LF2_F5)) { local_pkt.func_keys_1 |= NET_FKEY1_F5; m_key_states[VK_LF2_F5] = 'u'; }
            if (is_key_down(VK_LF2_F6)) { local_pkt.func_keys_1 |= NET_FKEY1_F6; m_key_states[VK_LF2_F6] = 'u'; }
            if (is_key_down(VK_LF2_F7)) { local_pkt.func_keys_1 |= NET_FKEY1_F7; m_key_states[VK_LF2_F7] = 'u'; }
            if (is_key_down(VK_LF2_F8)) { local_pkt.func_keys_2 |= NET_FKEY2_F8; m_key_states[VK_LF2_F8] = 'u'; }
            if (is_key_down(VK_LF2_F9)) { local_pkt.func_keys_1 |= NET_FKEY1_F9; m_key_states[VK_LF2_F9] = 'u'; }

            m_net_seq = static_cast<uint8_t>((m_net_seq + 1) % 50);
            local_pkt.seq_counter = m_net_seq;
            local_pkt.version_tag = m_net_version;
            local_pkt.hp_checksum = network_manager_t::compute_hp_checksum(m_world.objects, 20);
            network_manager_t::encode_data_crc(local_pkt, m_data_crc);

            if (!m_net_mgr->exchange_lockstep(local_pkt, remote_pkt)) {
                m_last_net_sync = SyncResult::CONNECTION_LOST;
                return;
            }
            m_last_net_sync = network_manager_t::verify_sync(local_pkt, remote_pkt);
            if (m_last_net_sync != SyncResult::OK) {
                return;
            }

            if ((remote_pkt.func_keys_1 & NET_FKEY1_F1) || (local_pkt.func_keys_1 & NET_FKEY1_F1)) dispatch_fkey_action(VK_LF2_F1, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F2) || (local_pkt.func_keys_1 & NET_FKEY1_F2)) dispatch_fkey_action(VK_LF2_F2, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F4) || (local_pkt.func_keys_1 & NET_FKEY1_F4)) dispatch_fkey_action(VK_LF2_F4, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F5) || (local_pkt.func_keys_1 & NET_FKEY1_F5)) dispatch_fkey_action(VK_LF2_F5, local_rec);
            if ((remote_pkt.func_keys_2 & NET_FKEY2_F3) || (local_pkt.func_keys_2 & NET_FKEY2_F3)) dispatch_fkey_action(VK_LF2_F3, local_rec);
            if ((remote_pkt.func_keys_2 & NET_FKEY2_F8) || (local_pkt.func_keys_2 & NET_FKEY2_F8)) dispatch_fkey_action(VK_LF2_F8, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F6) || (local_pkt.func_keys_1 & NET_FKEY1_F6)) dispatch_fkey_action(VK_LF2_F6, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F7) || (local_pkt.func_keys_1 & NET_FKEY1_F7)) dispatch_fkey_action(VK_LF2_F7, local_rec);
            if ((remote_pkt.func_keys_1 & NET_FKEY1_F9) || (local_pkt.func_keys_1 & NET_FKEY1_F9)) dispatch_fkey_action(VK_LF2_F9, local_rec);
            if ((remote_pkt.func_keys_2 & NET_FKEY2_LF2NET) || (local_pkt.func_keys_2 & NET_FKEY2_LF2NET)) dispatch_fkey_action(0xFE, local_rec);
            if ((remote_pkt.func_keys_2 & NET_FKEY2_HEROFIGHTER) || (local_pkt.func_keys_2 & NET_FKEY2_HEROFIGHTER)) dispatch_fkey_action(0xFF, local_rec);
        }
    }

    // 4. Remote/playback input unpack & replay recording
    if (!paused) {
        if (net_active) {
            uint8_t merged_inputs[8]{};
            for (int k = 0; k < 8; ++k) {
                merged_inputs[k] = static_cast<uint8_t>(local_pkt.player_inputs[k] | remote_pkt.player_inputs[k]);
                local_rec.inputs[k] = merged_inputs[k];
            }
            slot_unpack_network_inputs(&m_world, merged_inputs, m_input_phase);
        } else if (m_has_playback_replay) {
            slot_unpack_network_inputs(&m_world, playback_rec.inputs, m_input_phase);
        }

        if (m_replay_recorder.is_recording()) {
            const replay_frame_10_t& rec_to_write = m_has_playback_replay ? playback_rec : local_rec;
            m_replay_recorder.record_frame_10(rec_to_write, compute_active_hp_sum(m_world));
        }
    }

    if (paused) {
        m_fast_forward = false;
        return;
    }
    if (m_pause_state == 2) {
        m_pause_state = 1;
        m_battle_paused = true;
    }

    // 5. Modulo frame counters & alive-team round-end state machine (0x0041BC90)
    m_shake = 1 - m_shake;
    m_counter_12 = (m_counter_12 + 1) % 12;
    m_counter_3 = (m_counter_3 + 1) % 3;

    if (m_selected_mode == MODE_STAGE) {
        bool any_player_alive = false;
        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (m_world.is_object_exists[i] && m_world.objects[i] && m_world.objects[i]->file &&
                m_world.objects[i]->hp > 0 && m_world.objects[i]->file->type == TYPE_CHARACTER &&
                m_world.objects[i]->team > 0 && m_world.objects[i]->team < 40 &&
                m_world.objects[i]->team != 5) {
                any_player_alive = true;
                break;
            }
        }
        if (!any_player_alive || m_stage_mgr.is_stage_cleared()) {
            m_round_counter++;
            if (!m_stage_mgr.is_stage_cleared() && m_round_counter == 80) {
                m_fast_forward = false;
                get_bgm_manager().pause();
                play_ui_sound(SOUND_END);
            }
        }
    } else {
        int32_t team_counts[40]{};
        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (m_world.is_object_exists[i] && m_world.objects[i] && m_world.objects[i]->file &&
                m_world.objects[i]->hp > 0 && m_world.objects[i]->file->type == TYPE_CHARACTER) {
                uint32_t t = m_world.objects[i]->team;
                if (t > 0 && t < 40 && t != 5) {
                    team_counts[t]++;
                }
            }
        }
        int32_t alive_teams = 0;
        for (int32_t t = 0; t < 40; ++t) {
            if (team_counts[t] > 0) {
                m_winning_team = t;
                alive_teams++;
            }
        }
        if (alive_teams < 2 && m_selected_mode != MODE_BATTLE) {
            if (alive_teams == 0) m_winning_team = -1;
            m_round_counter++;
            if (m_round_counter == 80) {
                if (m_selected_mode != MODE_VS && m_selected_mode != MODE_1ON1 &&
                    m_selected_mode != MODE_2ON2 && m_selected_mode != MODE_DEMO) {
                    get_bgm_manager().pause();
                }
                if (m_selected_mode != MODE_DEMO) {
                    m_fast_forward = false;
                }
                play_ui_sound(SOUND_END);
            }
        } else if (m_selected_mode != MODE_1ON1 && m_selected_mode != MODE_2ON2) {
            m_winning_team = -1;
        }
    }

    if (m_round_counter == 145) {
        m_round_counter = 144;
    } else if (m_round_counter > 349) {
        // End-of-round transformation reverts (LouisEX, Firzen fusion split, Rudolf uid)
        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
            object_t* obj = m_world.objects[i];
            if (obj->uid < 0) {
                if (obj->file->id == LOUISE_EX_DAT && m_cheat_lf2net != 'd') {
                    file_t* lf = find_loaded_file(LOUIS_DAT);
                    if (lf) obj->file = lf;
                } else if (obj->fusion_state >= 0) {
                    int32_t partner_slot = obj->fusion_partner;
                    obj->fusion_state = -1;
                    obj->firen_counter = 900;
                    file_t* sf = find_loaded_file(static_cast<uint32_t>(obj->fusion_self_id));
                    file_t* pf = find_loaded_file(static_cast<uint32_t>(obj->fusion_partner_id));
                    if (sf) obj->file = sf;
                    if (partner_slot >= 0 && partner_slot < static_cast<int32_t>(MAX_OBJECTS) &&
                        m_world.objects[partner_slot]) {
                        object_t* partner = m_world.objects[partner_slot];
                        object_init(partner);
                        if (pf) {
                            partner->file = pf;
                            partner->weapon_hp = pf->weapon_hp;
                        }
                        m_world.is_object_exists[partner_slot] = 1;
                        partner->hp = obj->hp / 2;
                        partner->dark_hp = obj->dark_hp / 2;
                        obj->hp /= 2;
                        obj->dark_hp /= 2;
                        partner->x = obj->x;
                        partner->z = obj->z;
                        partner->y = 0;
                        partner->x_position = static_cast<double>(partner->x);
                        partner->z_position = static_cast<double>(partner->z);
                        partner->y_position = 0.0;
                        obj->x_velocity = 0.0;
                        partner->x_velocity = 0.0;
                        partner->facing = static_cast<uint8_t>(1U - obj->facing);
                        obj->frame_id1 = 112;
                        partner->frame_id1 = 112;
                        obj->mp = 0;
                        partner->mp = 0;
                        partner->team = obj->team;
                    }
                }
            } else {
                file_t* orig = find_loaded_file(static_cast<uint32_t>(obj->uid));
                if (orig) {
                    obj->file = orig;
                    obj->uid = -1;
                }
            }
        }
        m_round_counter = 0;
        if (m_replay_recorder.is_recording()) {
            m_replay_recorder.finish_recording();
        }
        if (m_has_playback_replay) {
            m_replay_player.close();
            m_has_playback_replay = false;
            m_selected_mode = MODE_PLAYBACK;
        }
        if (m_window) {
            return_to_menu();
        }
        return;
    }

    if (m_round_counter >= 144) {
        for (int i = 0; i < 8; ++i) {
            if (m_world.objects[i] && (m_world.objects[i]->click_attack == 1 || m_world.objects[i]->click_jump == 1)) {
                m_round_counter = 350;
                break;
            }
        }
    }

    // 6. Per-object Loop 1: AI/hit_Fa (objects 10..399) + control input tick + Rudolf teleport & transform
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
        object_t* obj = m_world.objects[i];

        if (i >= 10) {
            if (obj->file->type == TYPE_CHARACTER) {
                ai_tick(&m_world, i, ai_params);
                input_tick_done[i] = true;
            } else if (obj->frame_id1 < MAX_FRAMES && obj->file->frames[obj->frame_id1].hit_Fa > 0) {
                object_process_hit_fa(&m_world, static_cast<int32_t>(i));
            }
        }

        if (!input_tick_done[i]) {
            object_input_tick(obj, m_round_counter == 0, unlock_chars);
        }

        if (obj->frame_id1 < MAX_FRAMES) {
            uint32_t state = obj->file->frames[obj->frame_id1].state;
            if (state == 400 && m_shake == 0) {
                m_world.teleport(i, TELEPORT_TO_ENEMY);
            } else if (state == 401 && m_shake == 0) {
                m_world.teleport(i, TELEPORT_TO_TEAM);
            }
            if (state == 500 && (obj->transformed_to_id == -1 || obj->uid > -1)) {
                obj->frame_id1 = 0;
            }
            if (state == 501 && obj->transformed_to_id > -1) {
                file_t* tf = find_loaded_file(static_cast<uint32_t>(obj->transformed_to_id));
                if (tf) {
                    obj->uid = static_cast<int32_t>(obj->file->id);
                    obj->file = tf;
                    obj->frame_id1 = 0;
                    for (uint32_t c = 0; c < MAX_OBJECTS; ++c) {
                        if (m_world.is_object_exists[c] && m_world.objects[c] &&
                            m_world.objects[c]->clone == static_cast<int32_t>(i) &&
                            m_world.objects[c]->hp > 0) {
                            m_world.objects[c]->file = tf;
                            m_world.objects[c]->frame_id1 = (m_world.objects[c]->y < 0) ? 212 : 0;
                        }
                    }
                }
            }
        }
    }

    // 7. Per-object Loop 2: Physics + removal + join_hp/reserve respawn + transform revert
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
        object_t* obj = m_world.objects[i];

        object_physics_tick(obj, m_counter_12);

        if (obj->frame_id1 < MAX_FRAMES && obj->file->frames[obj->frame_id1].state == 9998) {
            m_world.is_object_exists[i] = 0;
            continue;
        }

        if (obj->frame_id1 < MAX_FRAMES &&
            obj->file->frames[obj->frame_id1].state == STATE_LYING &&
            obj->hp <= 0 &&
            (obj->clone >= 0 || obj->team == 5 || i >= 20) &&
            obj->blink_time > 0 && obj->blink_time < 5) {
            if (obj->join_hp > 0) {
                obj->team = 1;
                obj->reserve = obj->join_reserve;
                obj->max_hp = obj->join_hp;
                obj->dark_hp = obj->join_hp;
                obj->hp = obj->join_hp;
                obj->join_hp = 0;
                obj->mp = 0;
                if (obj->file->id >= 30 && obj->file->id <= 36) {
                    obj->pic_no_gain = 140;
                }
                obj->frame_id1 = 219;
                obj->shaking = 10;
                int32_t ms = find_free_dynamic_slot();
                file_t* ef = find_loaded_file(ETC_DAT);
                if (ms != -1 && ef) {
                    object_t* m = m_world.objects[ms];
                    object_init(m);
                    m->file = ef;
                    m->weapon_hp = ef->weapon_hp;
                    m->x = obj->x;
                    m->y = obj->y;
                    m->z = obj->z + 1;
                    m->team = obj->team;
                    m->x_position = static_cast<double>(m->x);
                    m->y_position = static_cast<double>(m->y);
                    m->z_position = static_cast<double>(m->z);
                    m->frame_id1 = 6;
                    m->x_velocity = 0.0;
                    m->y_velocity = 0.0;
                    m->z_velocity = 0.0;
                    m->facing = FACING_RIGHT;
                    m_world.is_object_exists[ms] = 1;
                }
            } else if (obj->reserve < 2) {
                m_world.is_object_exists[i] = 0;
                continue;
            } else {
                obj->reserve--;
                int32_t sum_x = 0, sum_z = 0, count = 0;
                for (uint32_t t = 0; t < MAX_OBJECTS; ++t) {
                    if (m_world.is_object_exists[t] && m_world.objects[t] &&
                        m_world.objects[t]->team == obj->team && m_world.objects[t]->hp > 0) {
                        sum_x += m_world.objects[t]->x;
                        sum_z += m_world.objects[t]->z;
                        count++;
                    }
                }
                if (count > 0) {
                    int32_t rx = (sum_x / count) + lf2_random(0, 51) - 26;
                    int32_t rz = (sum_z / count) + lf2_random(0, 31) - 16;
                    obj->x = rx;
                    obj->z = rz;
                    obj->x_position = static_cast<double>(rx);
                    obj->z_position = static_cast<double>(rz);
                }
                obj->y = -300;
                obj->y_position = -300.0;
                obj->mp = 500;
                obj->dark_hp = obj->max_hp;
                obj->hp = obj->max_hp;
                obj->blink_time = 20;
                obj->frame_id1 = 212;
                obj->y_velocity = 0.0;
            }
        }

        if (obj->uid > -1 && obj->click_DJA == 3 && obj->y == 0 && obj->hp > 0) {
            obj->click_DJA = 0;
            file_t* orig = find_loaded_file(static_cast<uint32_t>(obj->uid));
            if (orig) {
                obj->file = orig;
                obj->frame_id1 = 245;
                obj->uid = -1;
                for (uint32_t c = 0; c < MAX_OBJECTS; ++c) {
                    if (m_world.is_object_exists[c] && m_world.objects[c] &&
                        m_world.objects[c]->clone == static_cast<int32_t>(i) &&
                        m_world.objects[c]->hp > 0) {
                        m_world.objects[c]->file = orig;
                        m_world.objects[c]->frame_id1 = (m_world.objects[c]->y < 0) ? 212 : 0;
                    }
                }
            }
        }
    }

    // 8. Mid-frame combat & sky weapon drop (0x00417F80 -> 0x00419380 -> 0x0042E100 -> 0x00418C30 -> 0x004187B0)
    const uint32_t game_mode = static_cast<uint32_t>(m_selected_mode);
    world_process_weapons(&m_world);

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (m_world.is_object_exists[i] && m_world.objects[i]) {
            m_world.objects[i]->successful_attacks = 0;
            m_world.objects[i]->attackable_distance = 1000;
            m_world.objects[i]->vulnerable_distance = 1000;
            m_world.objects[i]->flag_eb = 0;
        }
    }
    world_step_collisions(&m_world, game_mode);
    world_process_firzen_fusion(&m_world, unlock_chars);

    int32_t weapon_count = 0;
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
        uint32_t t = m_world.objects[i]->file->type;
        if (t == TYPE_LIGHT_WEAPON || t == TYPE_HEAVY_WEAPON || t == TYPE_THROW_WEAPON || t == TYPE_DRINK) {
            weapon_count++;
        }
        if (t == TYPE_CHARACTER) {
            m_world.attack_process(i, m_counter_12);
        }
    }

    if (weapon_count < 4 && lf2_random(0, 200) == 0) {
        file_t* cands[MAX_FILES]{};
        int32_t cand_count = 0;
        for (uint32_t f = 0; f < MAX_FILES; ++f) {
            file_t* fp = m_world.files[f] ? m_world.files[f] : m_loaded_files[f];
            if (fp && fp->id >= 100 && fp->id < 200) {
                if ((fp->id != MILK_DAT && fp->id != BEER_DAT) ||
                    (lf2_random(0, 2) != 0 && m_selected_mode != MODE_STAGE &&
                     m_selected_mode != MODE_1ON1 && m_selected_mode != MODE_2ON2 &&
                     m_selected_mode != MODE_BATTLE)) {
                    cands[cand_count++] = fp;
                }
            }
        }
        int32_t fs = find_free_dynamic_slot();
        if (cand_count > 0 && fs != -1) {
            file_t* wf = cands[lf2_random(0, cand_count)];
            object_t* w = m_world.objects[fs];
            int32_t sx = lf2_random(0, 30) + 30 + lf2_random(0, 30) * ((stage_w - 60) / 30);
            int32_t zw = (z_max > z_min + 60) ? (z_max - z_min - 60) : 60;
            int32_t sz = lf2_random(0, 30) + z_min + 30 + lf2_random(0, 30) * (zw / 30);
            object_init(w);
            w->file = wf;
            w->weapon_hp = wf->weapon_hp;
            w->x = sx; w->y = -500; w->z = sz;
            w->x_position = static_cast<double>(sx);
            w->y_position = -500.0;
            w->z_position = static_cast<double>(sz);
            w->x_velocity = 0.0; w->y_velocity = 0.0; w->z_velocity = 0.0;
            w->owner = 99;
            if (wf->id == MILK_DAT) w->hp = 200;
            m_world.is_object_exists[fs] = 1;
            clear_vrest_for_slot(fs);
        }
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (m_world.is_object_exists[i] && m_world.objects[i] && m_world.objects[i]->file &&
            m_world.objects[i]->file->type > TYPE_CHARACTER) {
            m_world.attack_process(i, m_counter_12);
        }
    }

    world_process_cpoint_chain(&m_world);
    world_process_cpoint_sync(&m_world);
    world_validate_weapon_holders(&m_world);
    world_process_weapons(&m_world);

    // Mode-specific wave / army spawning dispatch & boundary clamp
    switch (m_selected_mode) {
    case MODE_STAGE:
        m_stage_mgr.update_stage(&m_world, m_camera.x);
        break;
    case MODE_BATTLE:
        m_battle_mgr.step_simulation();
        break;
    default:
        break;
    }

    const double d_z_min = static_cast<double>(z_min);
    const double d_z_max = static_cast<double>(z_max);
    const double d_stage_w = static_cast<double>(stage_w);
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i]) continue;
        object_t* obj = m_world.objects[i];
        if (!obj || !obj->file) continue;

        if (obj->file->type == TYPE_CHARACTER) {
            if (obj->z_position < d_z_min) obj->z_position = d_z_min;
            else if (obj->z_position > d_z_max) obj->z_position = d_z_max;
        } else {
            if (obj->z_position < d_z_min - 1.0) obj->z_position = d_z_min - 1.0;
            else if (obj->z_position > d_z_max + 1.0) obj->z_position = d_z_max + 1.0;
        }
        obj->z = static_cast<int32_t>(obj->z_position);

        if (obj->file->type == TYPE_ATTACK) {
            if (obj->x_position < -300.0 || obj->x_position > d_stage_w + 300.0) {
                m_world.is_object_exists[i] = 0;
            }
        } else if (obj->file->type == TYPE_CHARACTER) {
            double x_min = (i < 20) ? ((obj->team == 5) ? -300.0 : 0.0) : -100.0;
            double x_max = (i < 20) ? d_stage_w : (d_stage_w + 100.0);
            if (obj->x_position < x_min) obj->x_position = x_min;
            else if (obj->x_position > x_max) obj->x_position = x_max;
        } else {
            if ((obj->file->id == MILK_DAT || obj->file->id == BEER_DAT) && obj->player_index > 0) {
                if (obj->x_position < 10.0) obj->x_position = 10.0;
                else if (obj->x_position > d_stage_w - 10.0) obj->x_position = d_stage_w - 10.0;
            } else if ((obj->x_position < 0.0 || obj->x_position > d_stage_w) && obj->y == 0) {
                m_world.is_object_exists[i] = 0;
            }
        }
        obj->x = static_cast<int32_t>(obj->x_position);
    }

    world_average_velocities(&m_world);

    // 9. Per-object Loop 3: transforms, regen, frame advance, opoint/weapon break/team orders, ice/fire FX
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
        object_t* obj = m_world.objects[i];

        if (obj->frame_id1 < MAX_FRAMES) {
            uint32_t pre_state = obj->file->frames[obj->frame_id1].state;
            if (obj->file->type == TYPE_CHARACTER && pre_state == 9995) {
                file_t* lex = find_loaded_file(LOUISE_EX_DAT);
                if (lex) obj->file = lex;
                obj->frame_id1 = 0;
            } else if (pre_state > 7999 && pre_state < 9000) {
                file_t* tf = find_loaded_file(pre_state - 8000);
                if (tf) obj->file = tf;
                obj->frame_id1 = 0;
                obj->pic_no_gain = 140;
            } else if (obj->file->type == TYPE_CHARACTER && pre_state == 9996 && obj->wait_counter == 1) {
                for (int p = 0; p < 5; ++p) {
                    int32_t s = find_free_dynamic_slot();
                    if (s == -1) break;
                    file_t* pf = find_loaded_file((p == 4) ? LOUIS_ARMOUR_DAT : LOUIS_WRISTER_DAT);
                    if (!pf) continue;
                    object_t* sh = m_world.objects[s];
                    object_init(sh);
                    sh->file = pf;
                    sh->weapon_hp = pf->weapon_hp;
                    sh->x = obj->x + lf2_random(0x9b, 7) - 3;
                    sh->y = obj->y + lf2_random(0x9c, 7) - 9;
                    sh->z = obj->z + 1;
                    sh->x_position = static_cast<double>(sh->x);
                    sh->y_position = static_cast<double>(sh->y);
                    sh->z_position = static_cast<double>(sh->z);
                    sh->y_velocity = -static_cast<double>(lf2_random(0x9d, 15) / 2) - 5.0;
                    sh->arest = 6;
                    if (p == 0 || p == 2) sh->z_velocity = static_cast<double>(lf2_random(0, 4)) + 3.0;
                    else if (p == 1 || p == 3) sh->z_velocity = -3.0 - static_cast<double>(lf2_random(0, 4));
                    else sh->z_velocity = 1.0;

                    if (p < 2) sh->x_velocity = -10.0 - static_cast<double>(lf2_random(0, 4));
                    else if (p < 4) sh->x_velocity = static_cast<double>(lf2_random(0, 4)) + 10.0;
                    else sh->x_velocity = static_cast<double>(lf2_random(0, 7)) - 3.0;

                    sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4));
                    sh->facing = static_cast<uint8_t>(lf2_random(0, 2));
                    m_world.is_object_exists[s] = 1;
                }
            }
        }

        if (obj->file->type == TYPE_CHARACTER) {
            if (obj->hp > 0 && obj->hp < obj->dark_hp && m_counter_12 == 0) {
                obj->hp++;
            }
            if (static_cast<int32_t>(obj->thrown_injury) < 0 && m_counter_12 == 0) {
                int32_t loss = (obj->armor_multiplier > 0) ? (900 / static_cast<int32_t>(obj->armor_multiplier)) : 9;
                obj->hp -= loss;
                obj->dark_hp -= loss / 3;
                if (obj->hp < 0) obj->hp = 0;
                if (obj->dark_hp < 0) obj->dark_hp = 0;
                obj->hp_lost += 9;
            }
            if ((obj->clone == -1 || obj->mp < 150) && obj->mp < 500 &&
                m_counter_3 == 0 && obj->blink_time >= 0) {
                int32_t eff_hp = (obj->hp > 500) ? 500 : obj->hp;
                if (obj->file->id == FIRZEN_DAT || obj->file->id == JULIAN_DAT) {
                    eff_hp /= 2;
                }
                obj->mp += (500 - eff_hp) / 100 + 1;
            }
            if (m_unlimited_mp && obj->mp < 500) {
                obj->mp = 500;
            }
        }

        object_frame_advance(obj, static_cast<int32_t>(m_selected_mode), static_cast<int32_t>(i),
                             m_unlimited_mp ? 0 : 1, m_round_counter == 0);

        int32_t curr_f = static_cast<int32_t>(obj->frame_id1);
        if (curr_f / 100 == 11 || curr_f / 100 == 12) {
            for (uint32_t c = 0; c < MAX_OBJECTS; ++c) {
                if (m_world.is_object_exists[c] && m_world.objects[c] &&
                    m_world.objects[c]->clone == static_cast<int32_t>(i)) {
                    m_world.objects[c]->blink_time = 1100 - curr_f;
                }
            }
            obj->blink_time = 1100 - curr_f;
            obj->frame_id1 = 0;
            continue;
        }

        if (curr_f < 0 || curr_f > 399) {
            obj->frame_id1 = 0;
            m_world.is_object_exists[i] = 0;
            continue;
        }

        if (obj->file->type == TYPE_CHARACTER && obj->hp < 1 &&
            (curr_f < 12 || curr_f == 110 || curr_f == 111)) {
            obj->frame_id1 = 186;
            obj->y_velocity = -3.0;
            obj->y_accl = -3.0;
            obj->y_position = -1.0;
            obj->y = -1;
            curr_f = 186;
        }

        if (obj->file->type == TYPE_CHARACTER && obj->y == 0 &&
            obj->y_position == 0.0 && obj->y_velocity == 0.0 && obj->y_accl == 0.0 &&
            ((curr_f > 179 && curr_f < 190 && curr_f != 184) || (curr_f > 211 && curr_f < 215))) {
            obj->frame_id1 = 186;
            obj->y_velocity = -3.0;
            obj->y_accl = -3.0;
            obj->y_position = -1.0;
            obj->y = -1;
            curr_f = 186;
        }

        const frame_t& cf = obj->file->frames[obj->frame_id1];
        if (cf.opoint.kind > 0 && cf.opoint.oid > 0 && obj->wait_counter == 0 &&
            !(obj->shaking != 0 && obj->file->type == TYPE_CHARACTER)) {
            int count = 1;
            int face_mode = static_cast<int>(cf.opoint.facing);
            if (face_mode > 10) {
                count = face_mode / 10;
                face_mode = face_mode % 10;
            }
            int32_t spawned_slots[16]{};
            int spawned_count = 0;

            for (int k = 0; k < count && spawned_count < 16; ++k) {
                int32_t ns = find_free_dynamic_slot();
                file_t* of = find_loaded_file(cf.opoint.oid);
                if (ns == -1 || !of) break;

                spawned_slots[spawned_count++] = ns;
                object_t* no = m_world.objects[ns];
                object_init(no);
                no->file = of;
                no->weapon_hp = of->weapon_hp;
                no->owner = obj->owner;
                clear_vrest_for_slot(ns);
                m_world.is_object_exists[ns] = 1;

                no->x = (obj->facing == FACING_RIGHT)
                    ? ((obj->x - cf.centerx) + cf.opoint.x)
                    : ((cf.centerx - cf.opoint.x) + obj->x);
                no->y = (obj->y - cf.centery) + cf.opoint.y;
                no->team = obj->team;
                no->z_position = obj->z_position + 1.0;
                no->y_position = static_cast<double>(no->y);
                no->x_position = static_cast<double>(no->x);
                no->z = static_cast<int32_t>(no->z_position);
                no->frame_id1 = cf.opoint.action;
                no->y_velocity = static_cast<double>(cf.opoint.dvy);
                no->z_velocity = 0.0;

                if (no->frame_id1 < MAX_FRAMES) {
                    uint32_t nstate = of->frames[no->frame_id1].state;
                    if ((nstate == 3000 || nstate == 1002 || nstate == 3006) &&
                        of->id != FIRZEN_BALL_DAT && of->id != BAT_BALL_DAT) {
                        if (obj->click_up != 0 && obj->click_down == 0) no->z_velocity = -2.5;
                        else if (obj->click_down != 0) no->z_velocity = 2.5;
                        if (of->id == FIREN_FLAME_DAT) no->z_velocity *= 0.25;
                    }
                }

                if (of->type == TYPE_CHARACTER) {
                    no->clone = (obj->clone < 0) ? static_cast<int32_t>(i) : obj->clone;
                    no->blink_time = obj->blink_time;
                }

                if (face_mode == 0) no->facing = obj->facing;
                else if (face_mode == 1) no->facing = static_cast<uint8_t>(1U - obj->facing);
                else no->facing = FACING_RIGHT;

                no->x_velocity = (no->facing == FACING_RIGHT)
                    ? static_cast<double>(cf.opoint.dvx)
                    : -static_cast<double>(cf.opoint.dvx);

                if (count > 1) {
                    double spread = (static_cast<double>(k) * 10.0) / (static_cast<double>(count) - 1.0) - 5.0;
                    no->z_velocity += spread;
                    if (no->x_velocity > 0.0 && spread > 0.0) no->x_velocity -= spread;
                    else if (no->x_velocity < 0.0 && spread < 0.0) no->x_velocity -= spread;
                    else no->x_velocity += spread;
                }

                if (obj->file->type == TYPE_ATTACK && obj->frame_id1 < MAX_FRAMES &&
                    obj->file->frames[obj->frame_id1].state == 3003) {
                    no->vrest_of_objects[i] = 10;
                }

                if (of->id == RUDOLF_DAT || of->id == JULIAN_DAT) {
                    no->hp = 10;
                    no->max_hp = 10;
                    no->dark_hp = 10;
                    no->mp = 5;
                }

                if (cf.opoint.kind == 2) {
                    obj->weapon_type = 1;
                    no->weapon_type = -1;
                    obj->weapon_id = ns;
                    no->holder_id = static_cast<int32_t>(i);
                    no->team = obj->team;
                }
            }

            if (spawned_count > 1) {
                for (int a = 0; a < spawned_count; ++a) {
                    int32_t sid = spawned_slots[a];
                    if ((spawned_count & 1) == 0) {
                        if (a < spawned_count / 2 - 1) m_world.objects[sid]->arest = (spawned_count / 2 - a) * 2 - 2;
                        else if (a > spawned_count / 2) m_world.objects[sid]->arest = (a - spawned_count / 2) * 2;
                    } else {
                        if (a < spawned_count / 2) m_world.objects[sid]->arest = (spawned_count / 2 - a) * 2;
                        else if (a > spawned_count / 2) m_world.objects[sid]->arest = (a - spawned_count / 2) * 2;
                    }
                    for (int b = 0; b < a; ++b) {
                        int32_t prev_sid = spawned_slots[b];
                        m_world.objects[sid]->vrest_of_objects[prev_sid] = 40;
                        m_world.objects[prev_sid]->vrest_of_objects[sid] = 40;
                    }
                }
            }
        } else if ((obj->file->type == TYPE_LIGHT_WEAPON || obj->file->type == TYPE_HEAVY_WEAPON ||
                    obj->file->type == TYPE_THROW_WEAPON || obj->file->type == TYPE_DRINK) &&
                   obj->weapon_hp < 0) {
            obj->weapon_hp = 0;
            uint32_t wid = obj->file->id;
            int pieces = 0;
            if (wid == HOE_DAT || wid == LOUIS_ARMOUR_DAT) pieces = 7;
            else if (wid == STICK_DAT || wid == ICE_SWORD_DAT || wid == LOUIS_WRISTER_DAT) pieces = 5;
            else if (wid == HENRY_ARROW1_DAT || wid == KNIFE_DAT || wid == BOOMERANG_DAT) pieces = 3;
            else if (wid == STONE_DAT) pieces = 13;
            else if (wid == WOODEN_BOX_DAT) pieces = 15;
            else if (wid == BASEBALL_DAT) pieces = 4;
            else if (wid == MILK_DAT || wid == BEER_DAT) pieces = 9;

            if (obj->file->weapon_broken_sound_id >= 0) {
                get_audio_system().queue_item_sound(obj->x, m_camera.x, obj->file->weapon_broken_sound_id);
            }
            file_t* bw = find_loaded_file(BROKEN_WEAPON_DAT);
            if (bw) {
                for (int p = 0; p < pieces; ++p) {
                    int32_t s = find_free_dynamic_slot();
                    if (s == -1) break;
                    object_t* sh = m_world.objects[s];
                    object_init(sh);
                    sh->file = bw;
                    sh->weapon_hp = bw->weapon_hp;
                    sh->x = obj->x + lf2_random(0, 7) - 3;
                    sh->y = obj->y + lf2_random(0, 7) - 3;
                    sh->z = obj->z;
                    sh->x_position = static_cast<double>(sh->x);
                    sh->y_position = static_cast<double>(sh->y);
                    sh->z_position = static_cast<double>(sh->z);
                    sh->x_velocity = static_cast<double>(lf2_random(0, 11)) - 5.0;
                    if (wid == STONE_DAT || wid == WOODEN_BOX_DAT || wid == ICE_SWORD_DAT) {
                        sh->y_velocity = -static_cast<double>(lf2_random(0, 11) / 2) - 8.0;
                    } else {
                        sh->y_velocity = -static_cast<double>(lf2_random(0, 11) / 2) - 6.0;
                    }
                    if (wid == STONE_DAT) sh->frame_id1 = (p < 5) ? static_cast<uint32_t>(lf2_random(0, 4)) : static_cast<uint32_t>(lf2_random(0, 4) + 4);
                    else if (wid == STICK_DAT) sh->frame_id1 = (p < 2) ? static_cast<uint32_t>(lf2_random(0, 4) + 10) : static_cast<uint32_t>(lf2_random(0, 4) + 14);
                    else if (wid == ICE_SWORD_DAT) sh->frame_id1 = (p < 2) ? static_cast<uint32_t>(lf2_random(0, 4) + 150) : static_cast<uint32_t>(lf2_random(0, 4) + 154);
                    else if (wid == HOE_DAT) sh->frame_id1 = (p < 5) ? static_cast<uint32_t>(lf2_random(0, 2) * 4 + 20 + lf2_random(0, 2)) : static_cast<uint32_t>(lf2_random(0, 2) + 30);
                    else if (wid == WOODEN_BOX_DAT) {
                        if (p < 2) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 40);
                        else if (p < 5) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 44);
                        else if (p < 8) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 50);
                        else sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 54);
                    } else if (wid == KNIFE_DAT) {
                        sh->frame_id1 = (p < 2) ? static_cast<uint32_t>(lf2_random(0, 2) + 54) : static_cast<uint32_t>(lf2_random(0, 2) + 30);
                    } else if (wid == BOOMERANG_DAT) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 2) + 170);
                    else if (wid == BASEBALL_DAT) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 60);
                    else if (wid == MILK_DAT) {
                        if (p < 1) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 70);
                        else if (p < 3) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 80);
                        else { sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 74); sh->y_velocity = -static_cast<double>(lf2_random(0, 11) / 2) - 4.0; }
                    } else if (wid == BEER_DAT) {
                        if (p < 1) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 160);
                        else if (p < 3) sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 164);
                        else { sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 74); sh->y_velocity = -static_cast<double>(lf2_random(0, 11) / 2) - 4.0; }
                    } else if (wid == LOUIS_WRISTER_DAT || wid == LOUIS_ARMOUR_DAT) {
                        sh->frame_id1 = static_cast<uint32_t>(lf2_random(0, 4) + 174);
                    }
                    m_world.is_object_exists[s] = 1;
                }
            }
            m_world.is_object_exists[i] = 0;
        } else if (i < 10 && obj->hp > 0 && obj->file->type == TYPE_CHARACTER) {
            int32_t cmd = 0;
            if (obj->input_history[1] == 9) {
                if (obj->input_history[2] == 0 && obj->input_history[3] == 9 && obj->input_history[4] == 0) cmd = 100;
                else if (obj->input_history[2] == 9 && obj->input_history[3] == 9 && obj->input_history[4] == 9) cmd = 102;
                else if (obj->input_history[2] == 5 && obj->input_history[3] == 9 && obj->input_history[4] == 5) cmd = 104;
            }
            if (cmd != 0) {
                std::memset(obj->input_history, 0, sizeof(obj->input_history));
                int32_t ms = find_free_dynamic_slot();
                file_t* ef = find_loaded_file(ETC_DAT);
                if (ms != -1 && ef) {
                    object_t* m = m_world.objects[ms];
                    object_init(m);
                    m->file = ef;
                    m->weapon_hp = ef->weapon_hp;
                    m->x = obj->x; m->y = 0; m->z = obj->z;
                    m->frame_id1 = static_cast<uint32_t>(cmd - 100);
                    m->x_position = static_cast<double>(m->x);
                    m->y_position = 0.0;
                    m->z_position = static_cast<double>(m->z);
                    m->x_velocity = 0.0; m->y_velocity = 0.0;
                    m_world.is_object_exists[ms] = 1;
                    for (uint32_t t = 0; t < MAX_OBJECTS; ++t) {
                        if (m_world.is_object_exists[t] && m_world.objects[t] &&
                            m_world.objects[t]->hp > 0 && m_world.objects[t]->file &&
                            m_world.objects[t]->file->type == TYPE_CHARACTER &&
                            m_world.objects[t]->team == obj->team) {
                            if (cmd == 100) {
                                m_world.objects[t]->ai_target_x = m->x + lf2_random(0, 81) - 40;
                                m_world.objects[t]->ai_target_z = m->z + lf2_random(0, 81) - 40;
                            } else if (cmd == 102) {
                                m_world.objects[t]->follow_order = 1;
                            } else if (cmd == 104) {
                                m_world.objects[t]->follow_order = 0;
                            }
                        }
                    }
                }
            }
        }

        // Ice shatter (data/066.wav) & fire smoke FX comparing frame_id3 (previous) vs frame_id1 (current)
        uint32_t pf = obj->frame_id3;
        if (pf < MAX_FRAMES) {
            uint32_t pstate = obj->file->frames[pf].state;
            uint32_t cstate = obj->file->frames[obj->frame_id1].state;
            if ((pstate == STATE_ICE || pf == 200) && cstate != STATE_ICE && obj->frame_id1 != 200) {
                get_audio_system().queue_fixed_sound(obj->x, m_camera.x, 15);
                file_t* bw = find_loaded_file(BROKEN_WEAPON_DAT);
                if (bw) {
                    for (int k = 0; k < 15; ++k) {
                        int32_t s = find_free_dynamic_slot();
                        if (s == -1) break;
                        object_t* sh = m_world.objects[s];
                        object_init(sh);
                        sh->file = bw;
                        sh->weapon_hp = bw->weapon_hp;
                        sh->x = obj->x; sh->y = obj->y; sh->z = obj->z;
                        sh->x_position = static_cast<double>(lf2_random(200, 39) - 19) + obj->x_position;
                        sh->y_position = obj->y_position - static_cast<double>(lf2_random(199, 29));
                        sh->z_position = obj->z_position;
                        sh->y_velocity = -static_cast<double>(lf2_random(201, 20) / 2) - 8.0;
                        sh->x_velocity = obj->pic_x_gain * 0.5 + (static_cast<double>(lf2_random(202, 11)) - 5.0);
                        if (k < 2) sh->frame_id1 = 120;
                        else if (k < 5) sh->frame_id1 = 130;
                        else if (k < 9) sh->frame_id1 = 125;
                        else sh->frame_id1 = 135;
                        m_world.is_object_exists[s] = 1;
                    }
                }
            }
            if (pstate == STATE_BURNING || pstate == STATE_FIRE || pstate == 19) {
                int puffs = 0;
                if (cstate == STATE_BURNING || cstate == STATE_FIRE || cstate == 19) {
                    if (lf2_random(0, 4) == 0) puffs = 1;
                } else {
                    puffs = 7;
                }
                if (puffs > 0) {
                    file_t* bw = find_loaded_file(BROKEN_WEAPON_DAT);
                    if (bw) {
                        for (int k = 0; k < puffs; ++k) {
                            int32_t s = find_free_dynamic_slot();
                            if (s == -1) break;
                            object_t* sm = m_world.objects[s];
                            object_init(sm);
                            sm->file = bw;
                            sm->weapon_hp = bw->weapon_hp;
                            sm->x = obj->x; sm->y = obj->y; sm->z = obj->z;
                            sm->x_position = static_cast<double>(lf2_random(0xcd, 59) - 29) + obj->x_position;
                            sm->y_position = obj->y_position - static_cast<double>(lf2_random(0xcc, 29));
                            sm->z_position = obj->z_position;
                            sm->y_velocity = -1.0;
                            sm->x_velocity = (static_cast<double>(lf2_random(0xce, 11)) - 5.0) + obj->x_velocity;
                            sm->frame_id1 = static_cast<uint32_t>(lf2_random(0xcf, 2) + 140);
                            m_world.is_object_exists[s] = 1;
                        }
                    }
                }
            }
        }
        obj->frame_id3 = obj->frame_id1;
    }

    // 10. F8 sky weapon fill
    if (m_sky_weapon_cmd == 1) {
        for (uint32_t f = 0; f < MAX_FILES; ++f) {
            file_t* wf = m_world.files[f] ? m_world.files[f] : m_loaded_files[f];
            if (!wf) continue;
            if (wf->id >= 100 && wf->id < 200 && (wf->id != MILK_DAT || lf2_random(0, 2) != 0)) {
                int32_t s = find_free_dynamic_slot();
                if (s == -1) break;
                object_t* w = m_world.objects[s];
                int32_t sx = lf2_random(0xd2, 30) + 30 + lf2_random(0xd1, 30) * ((stage_w - 60) / 30);
                int32_t zw = (z_max > z_min + 60) ? (z_max - z_min - 60) : 60;
                int32_t sz = lf2_random(0xd4, 30) + z_min + 30 + lf2_random(0xd3, 30) * (zw / 30);
                object_init(w);
                w->file = wf;
                w->weapon_hp = wf->weapon_hp;
                w->x = sx; w->y = -500; w->z = sz;
                w->x_position = static_cast<double>(sx);
                w->y_position = -500.0;
                w->z_position = static_cast<double>(sz);
                w->x_velocity = 0.0; w->y_velocity = 0.0; w->z_velocity = 0.0;
                if (wf->id == MILK_DAT) w->hp = 200;
                m_world.is_object_exists[s] = 1;
                clear_vrest_for_slot(s);
            }
        }
    }

    // 11. Per-object Loop 4: F9 destroy, F7 recover, state 1700 self-heal, Jan heal & distance reset
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!m_world.is_object_exists[i] || !m_world.objects[i] || !m_world.objects[i]->file) continue;
        object_t* obj = m_world.objects[i];

        if (m_sky_weapon_cmd == 2) {
            uint32_t t = obj->file->type;
            if (t == TYPE_LIGHT_WEAPON || t == TYPE_HEAVY_WEAPON || t == TYPE_THROW_WEAPON || t == TYPE_DRINK) {
                obj->weapon_hp = -1;
            } else if (m_selected_mode == MODE_STAGE && obj->team == 5 &&
                       t == TYPE_CHARACTER && obj->file->id != CRIMINAL_DAT) {
                obj->hp = 0;
                obj->mp = 0;
            }
        }

        if (m_recover_cmd == 1 && (m_selected_mode != MODE_STAGE || (i < 8 && obj->team == 1))) {
            if (obj->max_hp < 500) obj->max_hp = 500;
            obj->dark_hp = obj->max_hp;
            obj->hp = obj->dark_hp;
            obj->mp = 500;
            get_bgm_manager().stop();
        }

        if (obj->curing_hp / 1000 == 1 && obj->hp > 0) {
            obj->curing_hp--;
            if (obj->curing_hp % 8 == 0) {
                if (obj->hp < obj->dark_hp) {
                    obj->hp = (obj->hp < obj->dark_hp - 8) ? (obj->hp + 8) : obj->dark_hp;
                } else {
                    obj->curing_hp = 0;
                }
            }
            if (obj->curing_hp % 1000 == 0) obj->curing_hp = 0;
        }

        if (obj->heal_timer > 0 && obj->hp > 0) {
            obj->heal_timer--;
            if (obj->heal_timer % 8 == 0 && obj->hp < obj->dark_hp) {
                obj->hp += 8;
                if (obj->hp > obj->dark_hp) {
                    obj->hp = obj->dark_hp;
                    obj->heal_timer = 0;
                }
            }
        }

        if (obj->frame_id1 < MAX_FRAMES && obj->file->frames[obj->frame_id1].state == 1700) {
            obj->curing_hp = 1100;
        }

        obj->attackable_distance = 1000;
        obj->vulnerable_distance = 1000;
        obj->successful_attacks = 0;
        obj->flag_eb = 0;
    }

    m_recover_cmd = 0;
    m_sky_weapon_cmd = 0;

    if (m_round_counter < 100) {
        m_battle_elapsed++;
    }
    if (m_round_counter == 101 && m_replay_recorder.is_recording() && !m_has_playback_replay) {
        m_replay_recorder.finish_recording();
    }

    // 12. Update camera & flush spatialized battle sounds
    if (m_replay_panning) {
        m_camera.update_target(m_replay_cam_x);
    } else if (m_world.is_object_exists[0] && m_world.objects[0]) {
        m_camera.update_target(m_world.objects[0]->x);
    } else if (m_num_fighters > 0) {
        m_camera.update_target(m_fighters[0].x);
    }
    get_audio_system().set_camera_x(m_camera.x);
    get_audio_system().flush_queued_sounds();
}

void app_t::update_battle() {
    if (is_key_just_pressed(VK_LF2_ESCAPE)) {
        return_to_menu();
        return;
    }
    step_battle_frame();
}

void app_t::render_battle() {
    SDL_SetRenderDrawColor(m_renderer, 10, 10, 16, 255);
    SDL_RenderClear(m_renderer);

    if (m_stage_loaded) {
        m_graphics.draw_background(&m_background, m_camera.x, m_camera.y);
    }

    // Pass 1: Draw all active object shadows first, and collect active indices for Z-sorting (0x0041A5A0)
    std::vector<uint32_t> active_indices;
    active_indices.reserve(MAX_OBJECTS);

    SDL_Texture* shadow_tex = nullptr;
    if (m_stage_loaded && !m_background.shadow_path.empty()) {
        shadow_tex = m_graphics.load_texture(m_background.shadow_path, true);
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        const object_t* obj = m_world.objects[i];
        if (!obj || !obj->file) continue;

        if (shadow_tex) {
            m_graphics.draw_shadow(shadow_tex, obj->x, obj->z, m_camera.x, m_camera.y,
                                   m_background.shadow_w, m_background.shadow_h);
        }
        active_indices.push_back(i);
    }

    // Pass 2: Z-sort active objects ascending by z coordinate so deeper (smaller z) objects render behind closer ones
    std::stable_sort(active_indices.begin(), active_indices.end(), [this](uint32_t a, uint32_t b) {
        return m_world.objects[a]->z < m_world.objects[b]->z;
    });

    for (uint32_t idx : active_indices) {
        const object_t* obj = m_world.objects[idx];
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

    if (m_volume_display_timer > 0) {
        m_volume_display_timer--;
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

    // Authentic Volume HUD Overlay (0x004028A0): "Volume: " + 20 vertical bars
    if (m_volume_display_timer > 0) {
        m_graphics.draw_rect(300, 505, 195, 24, 10, 20, 55, 220, true);
        m_graphics.draw_rect(300, 505, 195, 24, 140, 180, 255, 255, false);
        m_graphics.draw_text("Volume: ", 308, 509, 255, 255, 255, 1);
        for (int i = 0; i < 20; ++i) {
            bool active_bar = (i * 50 < m_volume_level);
            uint8_t r = active_bar ? 120 : 40;
            uint8_t g = active_bar ? 210 : 50;
            uint8_t b = active_bar ? 255 : 80;
            m_graphics.draw_rect(370 + i * 6, 510, 4, 14, r, g, b, 255, true);
        }
    }

    SDL_RenderPresent(m_renderer);
}

void app_t::run() {
    uint32_t last_time = SDL_GetTicks();
    m_running = true;

    while (m_running) {
        process_events();
        if (!m_running) break;

        const uint32_t step = (m_in_battle && m_fast_forward) ? TICK_STEP_MENU_MS : TICK_STEP_BATTLE_MS;

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
