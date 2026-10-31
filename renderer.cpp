#include "renderer.h"
#include <algorithm>
#include <iostream>
#include <filesystem>

namespace lf2 {

// -------------------------------------------------------------
// Authentic Software Clipping from lf2.exe (0x0043ef70)
// -------------------------------------------------------------
extern "C" int lf2_clip_rect(int *dst_x1, int *dst_y1, int *dst_x2, int *dst_y2,
                             int *src_x1, int *src_y1, int *src_x2, int *src_y2,
                             int screen_w, int screen_h)
{
    // Completely off-screen rejection
    if (*dst_x1 < 0 && *dst_x2 < 0) return 0;
    if (*dst_x1 > screen_w && *dst_x2 > screen_w) return 0;
    if (*dst_y1 < 0 && *dst_y2 < 0) return 0;
    if (*dst_y1 > screen_h && *dst_y2 > screen_h) return 0;

    // Left clipping
    if (*dst_x1 < 0) {
        int clip = -(*dst_x1);
        *src_x1 += clip;
        *dst_x1 = 0;
    }

    // Top clipping
    if (*dst_y1 < 0) {
        int clip = -(*dst_y1);
        *src_y1 += clip;
        *dst_y1 = 0;
    }

    // Right clipping
    if (*dst_x2 > screen_w) {
        int clip = *dst_x2 - screen_w;
        *src_x2 -= clip;
        *dst_x2 = screen_w;
    }

    // Bottom clipping
    if (*dst_y2 > screen_h) {
        int clip = *dst_y2 - screen_h;
        *src_y2 -= clip;
        *dst_y2 = screen_h;
    }

    return 1;
}

// -------------------------------------------------------------
// Renderer Implementation
// -------------------------------------------------------------
renderer_t::renderer_t(SDL_Renderer* renderer)
    : m_renderer(renderer)
{
}

renderer_t::~renderer_t() {
    clear_textures();
}

void renderer_t::clear_textures() {
    for (auto& pair : m_textures) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    m_textures.clear();
}

std::string renderer_t::normalize_path(const std::string& path) const {
    std::string norm = path;
    for (char& c : norm) {
        if (c == '\\') c = '/';
    }

    // Check if directly exists
    if (std::filesystem::exists(norm)) {
        return norm;
    }

    // Check with .legacy/ prefix
    std::string legacy_path = ".legacy/" + norm;
    if (std::filesystem::exists(legacy_path)) {
        return legacy_path;
    }

    return norm;
}

SDL_Texture* renderer_t::load_texture(const std::string& path, bool color_key) {
    if (!m_renderer || path.empty()) return nullptr;

    std::string norm = normalize_path(path);
    auto it = m_textures.find(norm);
    if (it != m_textures.end()) {
        return it->second;
    }

    SDL_Surface* surface = SDL_LoadBMP(norm.c_str());
    if (!surface) {
        // Return nullptr if asset not on disk
        return nullptr;
    }

    // Authentic DirectDraw Color Key (0x0043ee50): Pure Black RGB(0,0,0) is keyed out
    if (color_key) {
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (texture) {
        m_textures[norm] = texture;
    }

    return texture;
}

SDL_Texture* renderer_t::get_texture(const std::string& path) const {
    std::string norm = normalize_path(path);
    auto it = m_textures.find(norm);
    if (it != m_textures.end()) {
        return it->second;
    }
    return nullptr;
}

bool renderer_t::get_sprite_rect(const file_t* file, uint32_t pic, int& out_sheet_idx, SDL_Rect& out_src_rect) const {
    if (!file) return false;

    // Authentic lookup algorithm decompiled from 0x0040be70
    for (int i = 0; i < file->bmp_count && i < 10; ++i) {
        int frames_per_row = file->sheet_row[i];
        int num_rows = file->sheet_col[i];
        int total_frames = frames_per_row * num_rows;
        if (total_frames <= 0) continue;

        int start = file->sheet_start[i];
        int pic_val = static_cast<int32_t>(pic);
        if (pic_val >= start && pic_val < start + total_frames) {
            int sub_idx = pic_val - start;
            int col_idx = sub_idx % frames_per_row;
            int row_idx = sub_idx / frames_per_row;

            int w = file->sheet_w[i];
            int h = file->sheet_h[i];

            out_sheet_idx = i;
            // Authentic 1-pixel separator gutter math: col_idx * (w + 1), row_idx * (h + 1)
            out_src_rect.x = col_idx * (w + 1);
            out_src_rect.y = row_idx * (h + 1);
            out_src_rect.w = w;
            out_src_rect.h = h;
            return true;
        }
    }
    return false;
}

void renderer_t::draw_sprite(SDL_Texture* tex, const SDL_Rect* src_rect, int32_t dst_x, int32_t dst_y,
                             bool flip_horizontal, uint8_t alpha) {
    if (!m_renderer || !tex) return;

    SDL_Rect full_src;
    if (!src_rect) {
        full_src.x = 0;
        full_src.y = 0;
        SDL_QueryTexture(tex, nullptr, nullptr, &full_src.w, &full_src.h);
        src_rect = &full_src;
    }

    int dst_x1 = dst_x;
    int dst_y1 = dst_y;
    int dst_x2 = dst_x + src_rect->w;
    int dst_y2 = dst_y + src_rect->h;

    int src_x1 = src_rect->x;
    int src_y1 = src_rect->y;
    int src_x2 = src_rect->x + src_rect->w;
    int src_y2 = src_rect->y + src_rect->h;

    // Authentic software clipping from 0x0043ef70 against 794x550
    if (!lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                       &src_x1, &src_y1, &src_x2, &src_y2,
                       794, 550)) {
        return; // Rejected / culled completely offscreen
    }

    SDL_Rect clipped_dst = { dst_x1, dst_y1, dst_x2 - dst_x1, dst_y2 - dst_y1 };
    SDL_Rect clipped_src = { src_x1, src_y1, src_x2 - src_x1, src_y2 - src_y1 };

    if (alpha != 255) {
        SDL_SetTextureAlphaMod(tex, alpha);
    }

    SDL_RendererFlip flip = flip_horizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(m_renderer, tex, &clipped_src, &clipped_dst, 0.0, nullptr, flip);

    if (alpha != 255) {
        SDL_SetTextureAlphaMod(tex, 255);
    }
}

void renderer_t::draw_frame(const file_t* file, uint32_t frame_id,
                            int32_t world_x, int32_t world_y, int32_t world_z,
                            uint8_t facing, int32_t camera_x, int32_t camera_y,
                            int32_t pic_offset) {
    if (!file || frame_id >= MAX_FRAMES) return;
    const frame_t& f = file->frames[frame_id];
    if (f.present == 0) return;

    int sheet_idx = -1;
    SDL_Rect src_rect;
    if (!get_sprite_rect(file, f.pic + pic_offset, sheet_idx, src_rect)) {
        return;
    }

    if (sheet_idx < 0 || sheet_idx >= file->bmp_count) return;

    std::string path = file->bmp_paths[sheet_idx];
    SDL_Texture* tex = load_texture(path, true);
    if (!tex) return;

    // Exact mathematical translation from 0x00415d00 / 0x0040be70:
    // Screen X:
    //   Facing right (0): world_x - camera_x - centerx
    //   Facing left  (1): world_x - camera_x - (frame_w - centerx)
    // Screen Y:
    //   world_y + world_z - camera_y - centery
    int32_t screen_x = 0;
    if (facing == FACING_RIGHT) {
        screen_x = world_x - camera_x - f.centerx;
    } else {
        screen_x = world_x - camera_x - (src_rect.w - f.centerx);
    }
    int32_t screen_y = world_y + world_z - camera_y - f.centery;

    draw_sprite(tex, &src_rect, screen_x, screen_y, facing == FACING_LEFT);
}

void renderer_t::draw_character(const file_t* file, const object_t* obj,
                                int32_t camera_x, int32_t camera_y, int32_t pic_offset) {
    if (!file || !obj) return;
    draw_frame(file, obj->frame_id1, obj->x, obj->y, obj->z, obj->facing, camera_x, camera_y, pic_offset);
}

void renderer_t::draw_shadow(SDL_Texture* shadow_texture, int32_t world_x, int32_t world_z,
                             int32_t camera_x, int32_t camera_y,
                             int32_t shadow_w, int32_t shadow_h) {
    if (!m_renderer || !shadow_texture) return;

    // Centered at world coordinate (world_x, world_z) on ground plane (y = 0)
    int32_t screen_x = world_x - camera_x - (shadow_w / 2);
    int32_t screen_y = world_z - camera_y - (shadow_h / 2);

    draw_sprite(shadow_texture, nullptr, screen_x, screen_y, false, 180);
}

void renderer_t::draw_background(const background_t* bg, int32_t camera_x, int32_t camera_y) {
    if (!m_renderer || !bg) return;

    for (size_t i = 0; i < bg->layers.size(); ++i) {
        const auto& layer = bg->layers[i];
        SDL_Texture* tex = load_texture(layer.path, layer.transparency != 0);
        if (!tex) continue;

        int32_t draw_x = bg->calculate_layer_x(i, camera_x);
        int32_t draw_y = layer.y - camera_y;

        SDL_Rect src;
        SDL_Rect* p_src = nullptr;
        if (layer.has_rect && layer.rect_w > 0 && layer.rect_h > 0) {
            src.x = layer.rect_x;
            src.y = layer.rect_y;
            src.w = layer.rect_w;
            src.h = layer.rect_h;
            p_src = &src;
        }

        draw_sprite(tex, p_src, draw_x, draw_y, false);
    }
}

void renderer_t::draw_hud(int32_t player_idx, int32_t hp, int32_t max_hp, int32_t mp, int32_t max_mp,
                          SDL_Texture* face_texture) {
    if (!m_renderer) return;

    int32_t base_x = 10 + player_idx * 195;
    int32_t base_y = 10;

    // 1. Portrait Frame (36x36)
    SDL_Rect portrait_rect = { base_x, base_y, 36, 36 };
    if (face_texture) {
        SDL_RenderCopy(m_renderer, face_texture, nullptr, &portrait_rect);
    } else {
        SDL_SetRenderDrawColor(m_renderer, 40, 40, 50, 255);
        SDL_RenderFillRect(m_renderer, &portrait_rect);
    }
    SDL_SetRenderDrawColor(m_renderer, 180, 180, 180, 255);
    SDL_RenderDrawRect(m_renderer, &portrait_rect);

    // 2. HP Bar (Red base, Yellow/Orange fill)
    int32_t bar_x = base_x + 42;
    int32_t hp_bar_y = base_y + 4;
    int32_t max_bar_w = 140;
    int32_t hp_bar_h = 11;

    SDL_Rect hp_bg = { bar_x, hp_bar_y, max_bar_w, hp_bar_h };
    SDL_SetRenderDrawColor(m_renderer, 80, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, &hp_bg);

    if (max_hp > 0 && hp > 0) {
        int32_t cur_hp_w = std::min(max_bar_w, (hp * max_bar_w) / max_hp);
        SDL_Rect hp_fill = { bar_x, hp_bar_y, cur_hp_w, hp_bar_h };
        SDL_SetRenderDrawColor(m_renderer, 255, 170, 0, 255);
        SDL_RenderFillRect(m_renderer, &hp_fill);
    }
    SDL_SetRenderDrawColor(m_renderer, 220, 220, 220, 255);
    SDL_RenderDrawRect(m_renderer, &hp_bg);

    // 3. MP Bar (Dark blue base, Cyan/Blue fill)
    int32_t mp_bar_y = base_y + 19;
    int32_t mp_bar_h = 8;

    SDL_Rect mp_bg = { bar_x, mp_bar_y, max_bar_w, mp_bar_h };
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 80, 255);
    SDL_RenderFillRect(m_renderer, &mp_bg);

    if (max_mp > 0 && mp > 0) {
        int32_t cur_mp_w = std::min(max_bar_w, (mp * max_bar_w) / max_mp);
        SDL_Rect mp_fill = { bar_x, mp_bar_y, cur_mp_w, mp_bar_h };
        SDL_SetRenderDrawColor(m_renderer, 0, 180, 255, 255);
        SDL_RenderFillRect(m_renderer, &mp_fill);
    }
    SDL_SetRenderDrawColor(m_renderer, 160, 160, 180, 255);
    SDL_RenderDrawRect(m_renderer, &mp_bg);
}

} // namespace lf2

