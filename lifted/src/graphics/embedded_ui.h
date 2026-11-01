#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

namespace lf2 {

struct embedded_asset_t {
    const char* name;
    const uint8_t* data;
    size_t size;
};

// Look up embedded UI asset by identifier or path (e.g. "MENU_BACK1", "MENU_BACK1.bmp", "data/ui/MENU_BACK1.bmp")
const embedded_asset_t* find_embedded_ui_asset(const std::string& name);

} // namespace lf2

