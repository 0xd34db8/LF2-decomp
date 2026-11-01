#include "app.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
    std::cout << "==================================================" << std::endl;
    std::cout << " Little Fighter 2 - Modern C++ Source Lift" << std::endl;
    std::cout << " Authentic 1:1 Logic & SDL2 Modern Execution Core" << std::endl;
    std::cout << "==================================================" << std::endl;

    bool fullscreen = false;
    bool test_mode = false;
    int test_frames = 120; // 4 seconds at 30 FPS

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--fullscreen" || arg == "-f") {
            fullscreen = true;
        } else if (arg == "--test" || arg == "-t") {
            test_mode = true;
        } else if (arg == "--frames" && i + 1 < argc) {
            test_frames = std::stoi(argv[++i]);
            test_mode = true;
        }
    }

    auto app = std::make_unique<lf2::app_t>();

    std::cout << "[LF2] Initializing Application Core (" 
              << lf2::WINDOW_WIDTH << "x" << lf2::WINDOW_HEIGHT << ")..." << std::endl;

    if (!app->init(lf2::WINDOW_WIDTH, lf2::WINDOW_HEIGHT, fullscreen, test_mode)) {
        std::cerr << "[LF2] Failed to initialize application!" << std::endl;
        return 1;
    }

    std::cout << "[LF2] Window & Renderer initialized successfully." << std::endl;
    std::cout << "[LF2] Fixed frame pacing: 33 ms (~30.3 FPS), 100 ms lag clamp." << std::endl;
    std::cout << "[LF2] Input mapping: 256-byte Win32-compatible key state table." << std::endl;

    if (test_mode) {
        std::cout << "[LF2] Running in automated verification test mode for " 
                  << test_frames << " frames..." << std::endl;

        // Verify initial input states
        for (int k = 0; k < 256; ++k) {
            if (app->get_key_state(static_cast<uint8_t>(k)) != 'u') {
                std::cerr << "[LF2 TEST ERROR] Key " << k << " state is not 'u'!" << std::endl;
                return 2;
            }
        }

        // Test cheat sequence "lf2.net" simulation
        const uint8_t cheat_keys[] = { 'L', 'F', '2', lf2::VK_LF2_OEM_PERIOD, 'N', 'E', 'T' };
        for (uint8_t key : cheat_keys) {
            SDL_Event down_event;
            down_event.type = SDL_KEYDOWN;
            if (key >= 'A' && key <= 'Z') {
                down_event.key.keysym.sym = SDLK_a + (key - 'A');
            } else if (key >= '0' && key <= '9') {
                down_event.key.keysym.sym = SDLK_0 + (key - '0');
            } else if (key == lf2::VK_LF2_OEM_PERIOD) {
                down_event.key.keysym.sym = SDLK_PERIOD;
            } else {
                down_event.key.keysym.sym = key;
            }
            down_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&down_event);

            SDL_Event up_event;
            up_event.type = SDL_KEYUP;
            up_event.key.keysym.sym = down_event.key.keysym.sym;
            up_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&up_event);
        }

        // Test cheat sequence "herofighter.com" simulation
        const uint8_t hero_keys[] = { 'H', 'E', 'R', 'O', 'F', 'I', 'G', 'H', 'T', 'E', 'R', lf2::VK_LF2_OEM_PERIOD, 'C', 'O', 'M' };
        for (uint8_t key : hero_keys) {
            SDL_Event down_event;
            down_event.type = SDL_KEYDOWN;
            if (key >= 'A' && key <= 'Z') {
                down_event.key.keysym.sym = SDLK_a + (key - 'A');
            } else if (key == lf2::VK_LF2_OEM_PERIOD) {
                down_event.key.keysym.sym = SDLK_PERIOD;
            } else {
                down_event.key.keysym.sym = key;
            }
            down_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&down_event);

            SDL_Event up_event;
            up_event.type = SDL_KEYUP;
            up_event.key.keysym.sym = down_event.key.keysym.sym;
            up_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&up_event);
        }

        // Test developer sequence "ABC"
        const uint8_t dev_keys[] = { 'A', 'B', 'C' };
        for (uint8_t key : dev_keys) {
            SDL_Event down_event;
            down_event.type = SDL_KEYDOWN;
            down_event.key.keysym.sym = SDLK_a + (key - 'A');
            down_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&down_event);

            SDL_Event up_event;
            up_event.type = SDL_KEYUP;
            up_event.key.keysym.sym = down_event.key.keysym.sym;
            up_event.key.keysym.scancode = SDL_SCANCODE_UNKNOWN;
            SDL_PushEvent(&up_event);
        }

        // Run for test_frames ticks
        uint32_t ticks_run = 0;
        uint32_t last_time = SDL_GetTicks();
        while (ticks_run < static_cast<uint32_t>(test_frames)) {
            app->process_events();

            uint32_t now = SDL_GetTicks();
            if (now - last_time >= lf2::TICK_STEP_BATTLE_MS) {
                last_time += lf2::TICK_STEP_BATTLE_MS;
                app->update();
                app->render();
                ticks_run++;
            }
            SDL_Delay(1);
        }

        if (!app->is_lf2net_unlocked()) {
            std::cerr << "[LF2 TEST ERROR] 'lf2.net' cheat was not triggered correctly!" << std::endl;
            return 3;
        }

        if (!app->is_herofighter_unlocked()) {
            std::cerr << "[LF2 TEST ERROR] 'herofighter.com' cheat was not triggered correctly!" << std::endl;
            return 4;
        }

        if (!app->is_dev_mode_enabled()) {
            std::cerr << "[LF2 TEST ERROR] 'ABC' developer mode cheat was not triggered correctly!" << std::endl;
            return 5;
        }

        std::cout << "[LF2 TEST SUCCESS] 'lf2.net' cheat successfully detected and unlocked!" << std::endl;
        std::cout << "[LF2 TEST SUCCESS] 'herofighter.com' cheat successfully detected and unlocked!" << std::endl;
        std::cout << "[LF2 TEST SUCCESS] 'ABC' developer mode cheat successfully detected and unlocked!" << std::endl;
        std::cout << "[LF2 TEST SUCCESS] Frame pacing and event loop executed " 
                  << ticks_run << " frames cleanly." << std::endl;

        app->shutdown();
        return 0;
    }

    std::cout << "[LF2] Starting game loop (Press Alt+Enter for Fullscreen, Close window to exit)..." << std::endl;
    app->run();

    std::cout << "[LF2] Shutting down application cleanly." << std::endl;
    app->shutdown();
    return 0;
}
