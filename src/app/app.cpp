#include "app.h"
#include "menu.h"
#include "gameplay/ai.h"
#include <iostream>
#include <cstring>
#include <algorithm>

namespace lf2 {

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

bool app_t::init(int width, int height, bool fullscreen) {
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;

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
    case SDLK_PERIOD:
    case SDLK_KP_PERIOD:   return VK_LF2_OEM_PERIOD;

    case SDLK_LSHIFT:
    case SDLK_RSHIFT:      return VK_LF2_SHIFT;
    case SDLK_LCTRL:
    case SDLK_RCTRL:       return VK_LF2_CONTROL;
    case SDLK_LALT:
    case SDLK_RALT:        return VK_LF2_MENU;

    case SDLK_KP_0:        return VK_LF2_NUMPAD0;
    case SDLK_KP_1:        return VK_LF2_NUMPAD1;
    case SDLK_KP_2:        return VK_LF2_NUMPAD2;
    case SDLK_KP_3:        return VK_LF2_NUMPAD3;
    case SDLK_KP_4:        return VK_LF2_NUMPAD4;
    case SDLK_KP_5:        return VK_LF2_NUMPAD5;
    case SDLK_KP_6:        return VK_LF2_NUMPAD6;
    case SDLK_KP_7:        return VK_LF2_NUMPAD7;
    case SDLK_KP_8:        return VK_LF2_NUMPAD8;
    case SDLK_KP_9:        return VK_LF2_NUMPAD9;

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

void app_t::change_scene(scene_t next_scene) {
    m_scene = next_scene;
    m_in_battle = (m_scene == scene_t::BATTLE);

    if (m_scene == scene_t::TITLE) {
        m_menu_bg_idx = 1 + (std::rand() % 13);
    } else if (m_scene == scene_t::CHAR_SELECT) {
        for (int i = 0; i < 8; ++i) {
            m_slots[i].joined = (i == 0);
            m_slots[i].is_ready = false;
            m_slots[i].is_human = (i == 0);
            m_slots[i].roster_idx = (i == 0) ? 1 : 0; // P1 default Davis, others Random
            m_slots[i].team = (i == 0) ? 1 : 2;
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
    if (is_key_just_pressed(VK_LF2_UP) || is_key_just_pressed('W')) {
        m_title_cursor = (m_title_cursor + 4) % 5;
    } else if (is_key_just_pressed(VK_LF2_DOWN) || is_key_just_pressed('S')) {
        m_title_cursor = (m_title_cursor + 1) % 5;
    }

    if (is_key_just_pressed(VK_LF2_RETURN) || is_key_just_pressed(VK_LF2_SPACE) ||
        is_key_just_pressed('J') || is_key_just_pressed('Z')) {
        if (m_title_cursor == 0) {
            change_scene(scene_t::MODE_SELECT);
        }
    }

    if (is_key_just_pressed(VK_LF2_ESCAPE)) {
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

    for (int i = 0; i < 5; ++i) {
        int y = 220 + i * 32;
        if (i == m_title_cursor) {
            m_graphics.draw_rect(265, y - 4, 310, 26, 45, 75, 165, 180, true);
            m_graphics.draw_rect(265, y - 4, 310, 26, 150, 190, 255, 255, false);
            m_graphics.draw_text(title_items[i], 285, y, 255, 255, 255, 1, false);
        } else {
            m_graphics.draw_text(title_items[i], 285, y, 140, 165, 220, 1);
        }
    }

    m_graphics.draw_text("by Marti Wong, Starsky Wong", 540, 475, 120, 160, 220, 1);
    m_graphics.draw_text("1999-2008, all rights reserved", 540, 492, 120, 160, 220, 1);
    m_graphics.draw_text("http://www.LittleFighter.com", 540, 509, 120, 160, 220, 1);
}

void app_t::update_mode_select() {
    if (is_key_just_pressed(VK_LF2_UP) || is_key_just_pressed('W')) {
        m_mode_cursor = (m_mode_cursor + 7) % 8;
    } else if (is_key_just_pressed(VK_LF2_DOWN) || is_key_just_pressed('S')) {
        m_mode_cursor = (m_mode_cursor + 1) % 8;
    }

    if (is_key_just_pressed(VK_LF2_RETURN) || is_key_just_pressed(VK_LF2_SPACE) ||
        is_key_just_pressed('J') || is_key_just_pressed('Z')) {
        if (m_mode_cursor == 7) {
            change_scene(scene_t::TITLE);
        } else {
            m_selected_mode = static_cast<game_mode_t>(m_mode_cursor);
            change_scene(scene_t::CHAR_SELECT);
        }
    }

    if (is_key_just_pressed(VK_LF2_ESCAPE) || is_key_just_pressed(VK_LF2_BACKSPACE)) {
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

    if (m_modal_cpu_open) {
        if (is_key_just_pressed(VK_LF2_LEFT) || is_key_just_pressed('A')) {
            m_cpu_count = (m_cpu_count > 0) ? (m_cpu_count - 1) : 0;
        } else if (is_key_just_pressed(VK_LF2_RIGHT) || is_key_just_pressed('D')) {
            m_cpu_count = (m_cpu_count < 7) ? (m_cpu_count + 1) : 7;
        }

        if (is_key_just_pressed(VK_LF2_RETURN) || is_key_just_pressed(VK_LF2_SPACE) ||
            is_key_just_pressed('J') || is_key_just_pressed('Z')) {
            for (int i = 1; i <= m_cpu_count && i < 8; ++i) {
                m_slots[i].joined = true;
                m_slots[i].is_human = false;
                m_slots[i].is_ready = true;
                m_slots[i].roster_idx = (i % (roster_count - 1)) + 1;
                m_slots[i].team = (i % 2 == 1) ? 2 : 1;
            }
            change_scene(scene_t::LOADING);
        }

        if (is_key_just_pressed(VK_LF2_ESCAPE) || is_key_just_pressed('K') || is_key_just_pressed('X') ||
            is_key_just_pressed('L') || is_key_just_pressed('C') || is_key_just_pressed(VK_LF2_BACKSPACE)) {
            m_modal_cpu_open = false;
            m_slots[0].is_ready = false;
            m_slots[0].countdown = 5;
            m_slots[0].countdown_timer = 0;
        }
        return;
    }

    // P1 Slot 0 Navigation
    if (!m_slots[0].joined) {
        if (is_key_just_pressed('J') || is_key_just_pressed('Z') || is_key_just_pressed(VK_LF2_RETURN)) {
            m_slots[0].joined = true;
            m_slots[0].is_ready = false;
            m_slots[0].countdown = 5;
            m_slots[0].countdown_timer = 0;
        }
        if (is_key_just_pressed(VK_LF2_ESCAPE)) {
            change_scene(scene_t::MODE_SELECT);
        }
        return;
    }

    if (!m_slots[0].is_ready) {
        if (is_key_just_pressed(VK_LF2_LEFT) || is_key_just_pressed('A')) {
            m_slots[0].roster_idx = (m_slots[0].roster_idx + roster_count - 1) % roster_count;
        } else if (is_key_just_pressed(VK_LF2_RIGHT) || is_key_just_pressed('D')) {
            m_slots[0].roster_idx = (m_slots[0].roster_idx + 1) % roster_count;
        }

        if (is_key_just_pressed(VK_LF2_UP) || is_key_just_pressed('W')) {
            m_slots[0].team = (m_slots[0].team % 4) + 1;
        } else if (is_key_just_pressed(VK_LF2_DOWN) || is_key_just_pressed('S')) {
            m_slots[0].team = (m_slots[0].team == 1) ? 4 : (m_slots[0].team - 1);
        }

        // Lock in selection (Attack button) -> start 5-second countdown
        if (is_key_just_pressed('J') || is_key_just_pressed('Z') || is_key_just_pressed(VK_LF2_RETURN)) {
            m_slots[0].is_ready = true;
            m_slots[0].countdown = 5;
            m_slots[0].countdown_timer = 0;
        }

        // Cancel / Unjoin (Defend or Esc)
        if (is_key_just_pressed('L') || is_key_just_pressed('C') || is_key_just_pressed(VK_LF2_BACKSPACE) ||
            is_key_just_pressed(VK_LF2_ESCAPE)) {
            m_slots[0].joined = false;
        }
    } else {
        // Player is ready and locked in!
        // Authentic Mechanic from docs: pressing Jump speeds up countdown!
        if (is_key_just_pressed('K') || is_key_just_pressed('X') || is_key_just_pressed(VK_LF2_SPACE)) {
            m_slots[0].countdown = 0;
        }

        // Cancel ready state (Defend / Backspace / Esc)
        if (is_key_just_pressed('L') || is_key_just_pressed('C') || is_key_just_pressed(VK_LF2_BACKSPACE) ||
            is_key_just_pressed(VK_LF2_ESCAPE)) {
            m_slots[0].is_ready = false;
            m_slots[0].countdown = 5;
            m_slots[0].countdown_timer = 0;
            return;
        }

        // Countdown progression (~25 frames = 1 second)
        m_slots[0].countdown_timer++;
        if (m_slots[0].countdown_timer >= 25) {
            m_slots[0].countdown_timer = 0;
            if (m_slots[0].countdown > 0) {
                m_slots[0].countdown--;
            }
        }

        // When countdown finishes, open CPU selection prompt
        if (m_slots[0].countdown <= 0) {
            m_modal_cpu_open = true;
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
        ".legacy/bg/sys/hkc/bg.dat",
        "bg/template/1/bg.dat",
        ".legacy/bg/template/1/bg.dat"
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
            r_idx = 1; // Default Davis if random
        }

        const auto& entry = roster[r_idx];
        const std::string char_candidates[] = {
            entry.dat_file,
            ".legacy/" + entry.dat_file
        };

        file_t* loaded_file = new file_t();
        bool file_ok = false;
        for (const auto& cp : char_candidates) {
            if (dat_loader_t::load_file(loaded_file, cp, entry.id, TYPE_CHARACTER)) {
                file_ok = true;
                break;
            }
        }
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
    }

    if (m_battle_paused) {
        if (!is_key_just_pressed(VK_LF2_F2)) {
            return;
        }
    }

    // Player 1 human controls (Slot 0)
    if (m_num_fighters > 0 && m_fighters[0].file) {
        input_state_t input;
        input.left   = is_key_down(VK_LF2_LEFT) || is_key_down('A');
        input.right  = is_key_down(VK_LF2_RIGHT) || is_key_down('D');
        input.up     = is_key_down(VK_LF2_UP) || is_key_down('W');
        input.down   = is_key_down(VK_LF2_DOWN) || is_key_down('S');
        input.attack = is_key_down('J') || is_key_down('Z');
        input.jump   = is_key_down('K') || is_key_down('X') || is_key_down(VK_LF2_SPACE);
        input.defend = is_key_down('L') || is_key_down('C');

        object_handle_input(&m_fighters[0], input);
    }

    // Computer AI (Slots 1..N)
    for (uint32_t i = 1; i < m_num_fighters; ++i) {
        if (m_world.objects[i] && m_fighters[i].file) {
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
    }

    SDL_RenderPresent(m_renderer);
}

void app_t::run() {
    uint32_t last_time = SDL_GetTicks();
    m_running = true;

    while (m_running) {
        process_events();
        if (!m_running) break;

        const uint32_t step = m_in_battle ? TICK_STEP_BATTLE_MS : TICK_STEP_MENU_MS;

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

} // namespace lf2
