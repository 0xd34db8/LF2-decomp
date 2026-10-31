#include "app.h"
#include <iostream>
#include <cstring>

namespace lf2 {

app_t::app_t()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_width(WINDOW_WIDTH)
    , m_height(WINDOW_HEIGHT)
    , m_fullscreen(false)
    , m_running(false)
    , m_in_battle(true) // Default to battle mode (33 ms fixed step)
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
{
    reset_input();
    std::memset(&m_world, 0, sizeof(m_world));
}

app_t::~app_t() {
    shutdown();
}

void app_t::reset_input() {
    // Authentic WinMain 0x0043cf40 behavior:
    // memset(&DAT_00455378, 0x75, 0x100) -> 256 bytes set to 'u' (0x75 = up)
    std::memset(m_key_states, 0x75, sizeof(m_key_states));
    m_mouse_lbutton = 0;
    m_mouse_rbutton = 0;
}

bool app_t::init(int width, int height, bool fullscreen) {
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;

    // Initialize SDL2 video, audio, timer, and event subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
        std::cerr << "[LF2] SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    uint32_t window_flags = SDL_WINDOW_SHOWN;
    if (m_fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN;
    }

    // Window Creation matching 0x00401b00: Title "Little Fighter 2", resolution 794x550
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

    // Hardware accelerated renderer with VSync
    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!m_renderer) {
        // Fallback to software renderer if accelerated is unavailable
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
        if (!m_renderer) {
            std::cerr << "[LF2] SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
            SDL_Quit();
            return false;
        }
    }

    // Preserve authentic 794x550 logical viewport even when resized or in fullscreen
    SDL_RenderSetLogicalSize(m_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    reset_input();
    m_running = true;
    return true;
}

void app_t::shutdown() {
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
    // Map SDL_Keycode to authentic LF2 Win32 Virtual Key Codes
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
    case SDLK_KP_PERIOD:   return VK_LF2_OEM_PERIOD; // 0xBE

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
    m_key_states[vk] = 'd'; // 0x64 = down

    // -------------------------------------------------------------
    // Secret Cheat Code 1: "lf2.net" (0x0043b565 - 0x0043b610)
    // Keys: 'L' -> 'F' -> '2' -> '.' -> 'N' -> 'E' -> 'T'
    // -------------------------------------------------------------
    switch (m_cheat_lf2net_idx) {
    case 0:
        if (vk == 'L') m_cheat_lf2net_idx = 1;
        break;
    case 1:
        if (vk == 'F') m_cheat_lf2net_idx = 2;
        else if (vk != 'L') m_cheat_lf2net_idx = 0;
        break;
    case 2:
        if (vk == '2') m_cheat_lf2net_idx = 3;
        else if (vk == 'L') m_cheat_lf2net_idx = 1;
        else m_cheat_lf2net_idx = 0;
        break;
    case 3:
        if (vk == VK_LF2_OEM_PERIOD || vk == 0xBE || vk == '.') m_cheat_lf2net_idx = 4;
        else if (vk == 'L') m_cheat_lf2net_idx = 1;
        else m_cheat_lf2net_idx = 0;
        break;
    case 4:
        if (vk == 'N') m_cheat_lf2net_idx = 5;
        else if (vk == 'L') m_cheat_lf2net_idx = 1;
        else m_cheat_lf2net_idx = 0;
        break;
    case 5:
        if (vk == 'E') m_cheat_lf2net_idx = 6;
        else if (vk == 'L') m_cheat_lf2net_idx = 1;
        else m_cheat_lf2net_idx = 0;
        break;
    case 6:
        if (vk == 'T') {
            m_cheat_lf2net = 'd'; // Unlocks Julian, Firzen, LouisEX (DAT_00455471 = 'd')
        }
        if (vk == 'L') m_cheat_lf2net_idx = 1;
        else m_cheat_lf2net_idx = 0;
        break;
    default:
        m_cheat_lf2net_idx = 0;
        break;
    }

    // -------------------------------------------------------------
    // Secret Cheat Code 2: "herofighter.com" (0x0043b61a - 0x0043b794)
    // Keys: 'H','E','R','O','F','I','G','H','T','E','R','.','C','O','M'
    // -------------------------------------------------------------
    switch (m_cheat_herofighter_idx) {
    case 0:
        if (vk == 'H') m_cheat_herofighter_idx = 1;
        break;
    case 1:
        if (vk == 'E') m_cheat_herofighter_idx = 2;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 2:
        if (vk == 'R') m_cheat_herofighter_idx = 3;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 3:
        if (vk == 'O') m_cheat_herofighter_idx = 4;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 4:
        if (vk == 'F') m_cheat_herofighter_idx = 5;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 5:
        if (vk == 'I') m_cheat_herofighter_idx = 6;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 6:
        if (vk == 'G') m_cheat_herofighter_idx = 7;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 7:
        if (vk == 'H') m_cheat_herofighter_idx = 8;
        else m_cheat_herofighter_idx = 0;
        break;
    case 8:
        if (vk == 'T') m_cheat_herofighter_idx = 9;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 9:
        if (vk == 'E') m_cheat_herofighter_idx = 10;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 10:
        if (vk == 'R') m_cheat_herofighter_idx = 11;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 11:
        if (vk == VK_LF2_OEM_PERIOD || vk == 0xBE || vk == '.') m_cheat_herofighter_idx = 12;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 12:
        if (vk == 'C') m_cheat_herofighter_idx = 13;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 13:
        if (vk == 'O') m_cheat_herofighter_idx = 14;
        else if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    case 14:
        if (vk == 'M') {
            m_cheat_herofighter = 'd'; // DAT_00455470 = 'd'
        }
        if (vk == 'H') m_cheat_herofighter_idx = 1;
        else m_cheat_herofighter_idx = 0;
        break;
    default:
        m_cheat_herofighter_idx = 0;
        break;
    }

    // -------------------------------------------------------------
    // Secret Developer Mode Cheat: "A-B-C" (0x0043e9a0)
    // Sets DAT_00450bec = 1, enabling dev/editing modes
    // -------------------------------------------------------------
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
    m_key_states[vk] = 'u'; // 0x75 = up
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
            // Check for Alt+Enter fullscreen toggle
            if (event.key.keysym.sym == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
                toggle_fullscreen();
                break;
            }
            // Check for Escape to quit if requested
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                // Allows graceful exit during testing
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

void app_t::update() {
    // Game tick execution
    // (In later subsystems, this invokes global_t / game mode manager 0x0043e9a0)
}

void app_t::render() {
    if (!m_renderer) return;

    // Classic LF2 backdrop color (#0A0A10 dark stage ambiance)
    SDL_SetRenderDrawColor(m_renderer, 10, 10, 16, 255);
    SDL_RenderClear(m_renderer);

    // Present buffer
    SDL_RenderPresent(m_renderer);
}

void app_t::run() {
    // Exact mathematical translation of func_0043cf40 (WinMain) timing loop:
    // Uses timeGetTime() semantics via SDL_GetTicks()
    uint32_t last_time = SDL_GetTicks();
    m_running = true;

    while (m_running) {
        process_events();
        if (!m_running) break;

        // In battle: tick step = 33 ms (0x21, ~30.3 FPS)
        // In menu / loading: tick step = 3 ms
        const uint32_t step = m_in_battle ? TICK_STEP_BATTLE_MS : TICK_STEP_MENU_MS;

        uint32_t now = SDL_GetTicks();
        if (now - last_time > step) {
            now = SDL_GetTicks();
            // Spiral of death prevention: clamp lag to at most 100 ms
            if (now - last_time > MAX_ACCUMULATOR_LAG_MS) {
                last_time = SDL_GetTicks() - MAX_ACCUMULATOR_LAG_MS;
            }
            last_time += step;

            update();
            render();
        }

        // Sleep / CPU yield quantum (5 ms chunks)
        now = SDL_GetTicks();
        int32_t remaining = static_cast<int32_t>((last_time - now) + step);
        if (remaining > 0) {
            if (remaining > static_cast<int32_t>(MAX_SLEEP_CHUNK_MS)) {
                remaining = static_cast<int32_t>(MAX_SLEEP_CHUNK_MS);
            }
            SDL_Delay(static_cast<uint32_t>(remaining));
        }

        // Modulo 60 tick counter (DAT_00458580)
        m_frame_counter = (m_frame_counter + 1) % FRAME_COUNTER_MODULO;
        m_total_ticks++;
    }
}

} // namespace lf2

