#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lf2 {

// Single layer descriptor within a background
struct bg_layer_t {
    std::string path;
    int32_t     transparency{0}; // 0 = opaque, 1 = transparent (color key 0,0,0)
    int32_t     width{794};      // Width for parallax factor
    int32_t     height{550};
    int32_t     x{0};            // Base horizontal position
    int32_t     y{0};            // Base vertical position
    int32_t     loop{0};
    int32_t     rect_x{0};
    int32_t     rect_y{0};
    int32_t     rect_w{0};
    int32_t     rect_h{0};
    int32_t     rect_color{0};
    bool        has_rect{false};
    bool        is_rect{false};
    int32_t     cc{0};
    int32_t     c1{0};
    int32_t     c2{0};
};

// Stage background definition loaded from bg.dat
struct background_t {
    std::string             name;
    int32_t                 width{794};
    int32_t                 zboundary_min{370};
    int32_t                 zboundary_max{510};
    std::string             shadow_path{"bg\\sys\\hkc\\s.bmp"};
    int32_t                 shadow_w{37};
    int32_t                 shadow_h{9};
    std::vector<bg_layer_t> layers;

    // Load and decrypt bg.dat from disk (supports encrypted or plaintext)
    bool load_from_file(const std::string& dat_path);

    // Parse decrypted content string
    bool parse_content(const std::string& content);

    // Calculate authentic parallax horizontal position for layer (0x0041a302 - 0x0041a320)
    int32_t calculate_layer_x(size_t layer_idx, int32_t camera_x) const;
};

} // namespace lf2

