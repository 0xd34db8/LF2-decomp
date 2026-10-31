#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include "constants.h"
#include "file.h"
#include "object.h"
#include "background.h"

namespace lf2 {

// Authentic software clipping routine decompiled from 0x0043ef70
extern "C" int lf2_clip_rect(int *dst_x1, int *dst_y1, int *dst_x2, int *dst_y2,
                             int *src_x1, int *src_y1, int *src_x2, int *src_y2,
                             int screen_w, int screen_h);

// 2D Camera tracker and stage boundary enforcer
struct camera_t {
    int32_t x{0};
    int32_t y{0};
    int32_t bounds_min_x{0};
    int32_t bounds_max_x{0}; // total_stage_width - 794
    int32_t bounds_min_y{0};
    int32_t bounds_max_y{0};

    void set_stage_width(int32_t stage_width) {
        bounds_min_x = 0;
        bounds_max_x = (stage_width > 794) ? (stage_width - 794) : 0;
    }

    void update_target(int32_t target_world_x, int32_t target_world_y = 0) {
        // Authentic screen center is 397 (794 / 2)
        x = target_world_x - 397;
        if (x < bounds_min_x) x = bounds_min_x;
        if (x > bounds_max_x) x = bounds_max_x;

        y = target_world_y;
        if (y < bounds_min_y) y = bounds_min_y;
        if (y > bounds_max_y) y = bounds_max_y;
    }
};

// Modern SDL2 Hardware-Accelerated Rendering Core with DirectDraw Fidelity
class renderer_t {
public:
    explicit renderer_t(SDL_Renderer* renderer = nullptr);
    ~renderer_t();

    void set_sdl_renderer(SDL_Renderer* renderer) { m_renderer = renderer; }
    SDL_Renderer* get_sdl_renderer() const { return m_renderer; }

    // Texture loading & cache management with pure black (0,0,0) color keying
    SDL_Texture* load_texture(const std::string& path, bool color_key = true);
    SDL_Texture* get_texture(const std::string& path) const;
    void clear_textures();

    // Sprite sheet frame slicing (Authentic 1-pixel separator gutter math)
    bool get_sprite_rect(const file_t* file, uint32_t pic, int& out_sheet_idx, SDL_Rect& out_src_rect) const;

    // Direct blit with authentic clipping & flipping
    void draw_sprite(SDL_Texture* tex, const SDL_Rect* src_rect, int32_t dst_x, int32_t dst_y,
                     bool flip_horizontal = false, uint8_t alpha = 255);

    // Frame blitting using exact screen projection math (0x00415d00 / 0x0040be70)
    void draw_frame(const file_t* file, uint32_t frame_id,
                    int32_t world_x, int32_t world_y, int32_t world_z,
                    uint8_t facing, int32_t camera_x, int32_t camera_y,
                    int32_t pic_offset = 0);

    // Blit an active entity object
    void draw_character(const file_t* file, const object_t* obj,
                        int32_t camera_x, int32_t camera_y, int32_t pic_offset = 0);

    // Ground shadow blitting at y = 0
    void draw_shadow(SDL_Texture* shadow_texture, int32_t world_x, int32_t world_z,
                     int32_t camera_x, int32_t camera_y,
                     int32_t shadow_w = 37, int32_t shadow_h = 9);

    // Multi-layer parallax background rendering (0x0041a302 - 0x0041a320)
    void draw_background(const background_t* bg, int32_t camera_x, int32_t camera_y);

    // Authentic HUD status bars (HP / MP / Portrait)
    void draw_hud(int32_t player_idx, int32_t hp, int32_t max_hp, int32_t mp, int32_t max_mp,
                  SDL_Texture* face_texture = nullptr);

private:
    std::string normalize_path(const std::string& path) const;

private:
    SDL_Renderer* m_renderer{nullptr};
    std::unordered_map<std::string, SDL_Texture*> m_textures;
};

} // namespace lf2

