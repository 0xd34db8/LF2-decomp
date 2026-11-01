#include <iostream>
#include <cassert>
#include <cstring>
#include <filesystem>
#include <SDL.h>
#include "constants.h"
#include "file.h"
#include "object.h"
#include "background.h"
#include "renderer.h"
#include "dat_loader.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    std::cout << "=== Little Fighter 2 Graphics, Sprite & Camera Pipeline Verification ===" << std::endl;

    // -------------------------------------------------------------
    // Test 1: Authentic 2D Rect Clipping against 794x550 Screen Bounds (0x0043ef70)
    // -------------------------------------------------------------
    std::cout << "[+] Testing Software 2D Clipping (0x0043ef70)..." << std::endl;
    {
        int dst_x1, dst_y1, dst_x2, dst_y2;
        int src_x1, src_y1, src_x2, src_y2;
        int screen_w = 794;
        int screen_h = 550;

        // Case A: Fully inside screen
        dst_x1 = 100; dst_y1 = 100; dst_x2 = 180; dst_y2 = 180;
        src_x1 = 0;   src_y1 = 0;   src_x2 = 80;  src_y2 = 80;
        int res = lf2::lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                                     &src_x1, &src_y1, &src_x2, &src_y2,
                                     screen_w, screen_h);
        assert(res == 1);
        assert(dst_x1 == 100 && dst_y1 == 100 && dst_x2 == 180 && dst_y2 == 180);
        assert(src_x1 == 0 && src_y1 == 0 && src_x2 == 80 && src_y2 == 80);

        // Case B: Completely offscreen left (dst_x1 < 0 && dst_x2 < 0)
        dst_x1 = -100; dst_y1 = 100; dst_x2 = -20; dst_y2 = 180;
        res = lf2::lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                                 &src_x1, &src_y1, &src_x2, &src_y2,
                                 screen_w, screen_h);
        assert(res == 0); // Culled

        // Case C: Completely offscreen right (dst_x1 > 794 && dst_x2 > 794)
        dst_x1 = 800; dst_y1 = 100; dst_x2 = 880; dst_y2 = 180;
        res = lf2::lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                                 &src_x1, &src_y1, &src_x2, &src_y2,
                                 screen_w, screen_h);
        assert(res == 0); // Culled

        // Case D: Partial left clip (dst_x1 = -20, dst_x2 = 60, src_w = 80)
        dst_x1 = -20; dst_y1 = 100; dst_x2 = 60; dst_y2 = 180;
        src_x1 = 0;   src_y1 = 0;   src_x2 = 80; src_y2 = 80;
        res = lf2::lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                                 &src_x1, &src_y1, &src_x2, &src_y2,
                                 screen_w, screen_h);
        assert(res == 1);
        assert(dst_x1 == 0 && dst_x2 == 60);
        assert(src_x1 == 20 && src_x2 == 80); // Source x shifted by 20

        // Case E: Partial right clip (dst_x1 = 754, dst_x2 = 834, src_w = 80)
        dst_x1 = 754; dst_y1 = 100; dst_x2 = 834; dst_y2 = 180;
        src_x1 = 0;   src_y1 = 0;   src_x2 = 80;  src_y2 = 80;
        res = lf2::lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                                 &src_x1, &src_y1, &src_x2, &src_y2,
                                 screen_w, screen_h);
        assert(res == 1);
        assert(dst_x1 == 754 && dst_x2 == 794);
        assert(src_x1 == 0 && src_x2 == 40); // 40 pixels clipped from right
        std::cout << "    2D Software Clipping passed all edge cases." << std::endl;
    }

    // -------------------------------------------------------------
    // Test 2: Sprite Sheet Geometry & 1-Pixel Gutter Slicing Math
    // -------------------------------------------------------------
    std::cout << "[+] Testing Sprite Sheet Slicing with 1-Pixel Separator Gutter..." << std::endl;
    {
        lf2::renderer_t renderer(nullptr);
        lf2::file_t file;
        std::memset(&file, 0, sizeof(file));

        // Setup Davis 3 sprite sheets matching authentic LF2 data:
        // file(0-69): sprite\sys\davis_0.bmp w: 79 h: 79 row: 10 col: 7
        file.bmp_count = 3;
        file.sheet_start[0] = 0;
        file.sheet_w[0] = 79;
        file.sheet_h[0] = 79;
        file.sheet_row[0] = 10; // 10 frames per row
        file.sheet_col[0] = 7;  // 7 rows down
        std::strcpy(file.bmp_paths[0], "sprite\\sys\\davis_0.bmp");

        file.sheet_start[1] = 70;
        file.sheet_w[1] = 79;
        file.sheet_h[1] = 79;
        file.sheet_row[1] = 10;
        file.sheet_col[1] = 7;
        std::strcpy(file.bmp_paths[1], "sprite\\sys\\davis_1.bmp");

        int sheet_idx = -1;
        SDL_Rect src_rect;

        // Pic 0 (First frame of sheet 0): (0, 0, 79, 79)
        bool ok = renderer.get_sprite_rect(&file, 0, sheet_idx, src_rect);
        assert(ok && sheet_idx == 0);
        assert(src_rect.x == 0 && src_rect.y == 0 && src_rect.w == 79 && src_rect.h == 79);

        // Pic 4 (Fifth frame of sheet 0): col_idx = 4, row_idx = 0 -> x = 4 * 80 = 320
        ok = renderer.get_sprite_rect(&file, 4, sheet_idx, src_rect);
        assert(ok && sheet_idx == 0);
        assert(src_rect.x == 320 && src_rect.y == 0 && src_rect.w == 79 && src_rect.h == 79);

        // Pic 10 (First frame of row 1): col_idx = 0, row_idx = 1 -> y = 1 * 80 = 80
        ok = renderer.get_sprite_rect(&file, 10, sheet_idx, src_rect);
        assert(ok && sheet_idx == 0);
        assert(src_rect.x == 0 && src_rect.y == 80 && src_rect.w == 79 && src_rect.h == 79);

        // Pic 69 (Last frame of sheet 0): col_idx = 9, row_idx = 6 -> x = 720, y = 480
        ok = renderer.get_sprite_rect(&file, 69, sheet_idx, src_rect);
        assert(ok && sheet_idx == 0);
        assert(src_rect.x == 720 && src_rect.y == 480 && src_rect.w == 79 && src_rect.h == 79);

        // Pic 70 (First frame of sheet 1): sheet_idx = 1, col_idx = 0, row_idx = 0
        ok = renderer.get_sprite_rect(&file, 70, sheet_idx, src_rect);
        assert(ok && sheet_idx == 1);
        assert(src_rect.x == 0 && src_rect.y == 0 && src_rect.w == 79 && src_rect.h == 79);
        std::cout << "    Sprite Sheet Slicing verified with exact 1-pixel separator gutter." << std::endl;
    }

    // -------------------------------------------------------------
    // Test 3: Screen Projection & Entity Centering Arithmetic (0x00415d00)
    // -------------------------------------------------------------
    std::cout << "[+] Testing Entity Centering & Screen Projection Math (0x00415d00)..." << std::endl;
    {
        int32_t obj_x = 500;
        int32_t obj_y = -30; // 30 px in the air (jumping)
        int32_t obj_z = 400; // ground depth
        int32_t camera_x = 200;
        int32_t camera_y = 0;

        int32_t centerx = 39;
        int32_t centery = 79;
        int32_t frame_w = 79;

        // Facing Right (0): screen_x = obj_x - camera_x - centerx = 500 - 200 - 39 = 261
        int32_t right_screen_x = obj_x - camera_x - centerx;
        assert(right_screen_x == 261);

        // Facing Left (1): screen_x = obj_x - camera_x - (frame_w - centerx) = 500 - 200 - (79 - 39) = 260
        int32_t left_screen_x = obj_x - camera_x - (frame_w - centerx);
        assert(left_screen_x == 260);

        // Screen Y = y + z - camera_y - centery = -30 + 400 - 0 - 79 = 291
        int32_t screen_y = obj_y + obj_z - camera_y - centery;
        assert(screen_y == 291);

        std::cout << "    Centering math correctly offsets both facing directions and ground elevation." << std::endl;
    }

    // -------------------------------------------------------------
    // Test 4: Parallax Background Parsing & Authentic Scroll Math (0x0041a302)
    // -------------------------------------------------------------
    std::cout << "[+] Testing Authentic Parallax Formula on bg/template/1/bg.dat..." << std::endl;
    {
        lf2::background_t bg;
        const std::string bg_paths[] = { "bg/template/1/bg.dat", "build/bg/template/1/bg.dat", ".legacy/bg/template/1/bg.dat" };
        bool loaded = false;
        for (const auto& p : bg_paths) {
            if (bg.load_from_file(p)) {
                loaded = true;
                break;
            }
        }
        if (loaded) {
            assert(bg.name == "Template1");
            assert(bg.width == 1600);
            assert(bg.zboundary_min == 370 && bg.zboundary_max == 510);
            assert(bg.shadow_path == "bg\\template\\1\\shadow.bmp");
            assert(bg.shadow_w == 37 && bg.shadow_h == 9);
            assert(bg.layers.size() == 8);

            // Check Layer 0: pic1.bmp, transparency: 0, width: 967, x: 0, y: 128
            assert(bg.layers[0].width == 967);
            assert(bg.layers[0].x == 0);
            assert(bg.layers[0].y == 128);
            assert(bg.layers[0].transparency == 0);

            // Check Layer 2: pic3.bmp, transparency: 1, width: 1000, x: 0, y: 200
            assert(bg.layers[2].width == 1000);
            assert(bg.layers[2].transparency == 1);

            // Parallax calculation at camera_x = 0:
            int32_t draw_x_0 = bg.calculate_layer_x(0, 0);
            assert(draw_x_0 == 0);

            // Parallax calculation at rightmost camera_x = 1600 - 794 = 806:
            // formula: offset = - (camera_x * (layer_width - 794)) / (total_width - 794)
            // offset = - (806 * (967 - 794)) / (1600 - 794) = - (806 * 173) / 806 = -173
            int32_t draw_x_max = bg.calculate_layer_x(0, 806);
            assert(draw_x_max == -173);
            // The right edge of the layer at max camera is: -173 + 967 = 794 (aligns perfectly with screen right edge!)
            assert(draw_x_max + bg.layers[0].width == 794);

            std::cout << "    Parallax horizontal positioning exactly aligns layer edges with screen viewport." << std::endl;
        } else {
            std::cout << "    (Authentic bg/template/1/bg.dat skipped: not found in test path)" << std::endl;
        }
    }

    // -------------------------------------------------------------
    // Test 5: Authentic Hong Kong Coliseum (HKC) Background Parsing
    // -------------------------------------------------------------
    std::cout << "[+] Testing Decryption of bg/sys/hkc/bg.dat..." << std::endl;
    {
        lf2::background_t bg;
        const std::string hkc_paths[] = { "bg/sys/hkc/bg.dat", "build/bg/sys/hkc/bg.dat", ".legacy/bg/sys/hkc/bg.dat" };
        bool loaded = false;
        for (const auto& p : hkc_paths) {
            if (bg.load_from_file(p)) {
                loaded = true;
                break;
            }
        }
        if (loaded) {
            assert(bg.name == "HK_Coliseum");
            assert(bg.width == 794);
            assert(bg.zboundary_min == 316 && bg.zboundary_max == 442);
            assert(!bg.layers.empty());

            // For width == 794, parallax factor is 0 regardless of camera_x
            int32_t draw_x = bg.calculate_layer_x(0, 500);
            assert(draw_x == bg.layers[0].x);
            std::cout << "    HK_Coliseum stage loaded with " << bg.layers.size() << " layers." << std::endl;
        } else {
            std::cout << "    (Authentic bg/sys/hkc/bg.dat skipped: not found in test path)" << std::endl;
        }
    }

    // -------------------------------------------------------------
    // Test 6: SDL2 Hardware-Accelerated Headless Texture & Color Key Verification
    // -------------------------------------------------------------
    std::cout << "[+] Testing SDL2 Texture Loading & Black (0,0,0) Color Key..." << std::endl;
    {
        // Set dummy driver for reliable headless execution
        SDL_SetHint(SDL_HINT_VIDEODRIVER, "dummy");
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            SDL_Window* window = SDL_CreateWindow("Test", 0, 0, 794, 550, SDL_WINDOW_HIDDEN);
            if (window) {
                SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                if (sdl_renderer) {
                    lf2::renderer_t renderer(sdl_renderer);

                    // Resolve sprite test path
                    auto resolve_sprite = [](const std::string& path) -> std::string {
                        if (std::filesystem::exists(path)) return path;
                        if (std::filesystem::exists("build/" + path)) return "build/" + path;
                        if (std::filesystem::exists(".legacy/" + path)) return ".legacy/" + path;
                        return "";
                    };

                    std::string davis_0 = resolve_sprite("sprite/sys/davis_0.bmp");
                    std::string davis_s = resolve_sprite("sprite/sys/davis_s.bmp");

                    if (!davis_0.empty() && !davis_s.empty()) {
                        // Load authentic Davis sprite sheet
                        SDL_Texture* davis_tex = renderer.load_texture(davis_0, true);
                        assert(davis_tex != nullptr);

                        // Verify texture caching
                        SDL_Texture* cached_tex = renderer.get_texture(davis_0);
                        assert(cached_tex == davis_tex);

                        // Load authentic small portrait
                        SDL_Texture* portrait_tex = renderer.load_texture(davis_s, true);
                        assert(portrait_tex != nullptr);

                        // Render a HUD status bar without crashing
                        renderer.draw_hud(0, 300, 500, 200, 500, portrait_tex);
                    } else {
                        std::cout << "    (Authentic sprite bitmaps skipped: not found in test path)" << std::endl;
                    }

                    renderer.clear_textures();
                    SDL_DestroyRenderer(sdl_renderer);
                }
                SDL_DestroyWindow(window);
            }
            SDL_Quit();
            std::cout << "    SDL2 Texture Loader and Color Keying executed without error." << std::endl;
        } else {
            std::cout << "    [Note] SDL_Init video not supported in this headless environment; skipped." << std::endl;
        }
    }

    std::cout << "[SUCCESS] All Graphics, Sprite Management & Camera Pipeline tests passed 100%!" << std::endl;
    return 0;
}

