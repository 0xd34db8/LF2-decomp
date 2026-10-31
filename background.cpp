#include "background.h"
#include "cipher.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace lf2 {

bool background_t::load_from_file(const std::string& dat_path) {
    std::string text;
    // Check if cipher encrypted (header size check)
    if (cipher_t::decrypt_file(dat_path, text)) {
        return parse_content(text);
    }

    // Try reading directly as plaintext
    std::ifstream file(dat_path);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return parse_content(buffer.str());
}

bool background_t::parse_content(const std::string& content) {
    std::istringstream stream(content);
    std::string token;

    layers.clear();

    while (stream >> token) {
        if (!token.empty() && token[0] == '#') {
            std::string dummy;
            std::getline(stream, dummy);
            continue;
        }

        if (token == "name:") {
            stream >> name;
        } else if (token == "width:") {
            stream >> width;
        } else if (token == "zboundary:") {
            stream >> zboundary_min >> zboundary_max;
        } else if (token == "shadow:") {
            stream >> shadow_path;
        } else if (token == "shadowsize:") {
            stream >> shadow_w >> shadow_h;
        } else if (token == "layer:") {
            bg_layer_t layer;
            // The first token inside layer: is typically the layer texture path
            if (stream >> layer.path) {
                while (stream >> token && token != "layer_end") {
                    if (!token.empty() && token[0] == '#') {
                        std::string dummy;
                        std::getline(stream, dummy);
                        continue;
                    }

                    if (token == "transparency:") {
                        stream >> layer.transparency;
                    } else if (token == "width:") {
                        stream >> layer.width;
                    } else if (token == "height:") {
                        stream >> layer.height;
                    } else if (token == "x:") {
                        stream >> layer.x;
                    } else if (token == "y:") {
                        stream >> layer.y;
                    } else if (token == "loop:") {
                        stream >> layer.loop;
                    } else if (token == "cc:") {
                        stream >> layer.cc;
                    } else if (token == "c1:") {
                        stream >> layer.c1;
                    } else if (token == "c2:") {
                        stream >> layer.c2;
                    } else if (token == "rect:") {
                        // In some bg.dat: rect: <id> x: <x> y: <y> width: <w> height: <h>
                        std::string rect_id;
                        stream >> rect_id;
                        layer.has_rect = true;
                    }
                }
                layers.push_back(layer);
            }
        }
    }

    return true;
}

int32_t background_t::calculate_layer_x(size_t layer_idx, int32_t camera_x) const {
    if (layer_idx >= layers.size()) return 0;
    const auto& layer = layers[layer_idx];

    // Screen width authentic to LF2 (0x31a = 794)
    constexpr int32_t SCREEN_W = 794;

    if (width <= SCREEN_W) {
        return layer.x;
    }

    // Exact mathematical translation from lf2.exe disassembly (0x0041a302 - 0x0041a320):
    // eax = layer.width - 794;
    // eax = eax * camera_x;
    // ebp = total_width - 794;
    // eax = eax / ebp;
    // eax = -eax;
    // draw_x = layer.x + eax;
    int32_t layer_w_diff = layer.width - SCREEN_W;
    int32_t total_w_diff = width - SCREEN_W;

    if (total_w_diff == 0) {
        return layer.x;
    }

    int64_t numerator = static_cast<int64_t>(layer_w_diff) * camera_x;
    int32_t offset = -static_cast<int32_t>(numerator / total_w_diff);

    return layer.x + offset;
}

} // namespace lf2

