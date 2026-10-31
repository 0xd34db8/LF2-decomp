#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "core/global.h"

namespace lf2 {

enum game_mode_t : uint32_t {
    MODE_VS       = 0,
    MODE_STAGE    = 1,
    MODE_1ON1     = 2,
    MODE_2ON2     = 3,
    MODE_BATTLE   = 4,
    MODE_DEMO     = 5
};

struct player_slot_t {
    bool     active = false;
    bool     is_human = true;
    bool     is_ready = false;
    uint32_t char_id = 0;
    uint32_t team = 1; // Team 1..4
    int32_t  cursor_x = 0;
    int32_t  cursor_y = 0;
};

// 1:1 Lift of 0x00436900: Battle setup & entity instantiation
void setup_battle_characters(global_t* world, const std::vector<player_slot_t>& slots,
                             int32_t stage_min_x = 100, int32_t stage_max_x = 500,
                             int32_t stage_min_z = 150, int32_t stage_max_z = 350);

} // namespace lf2

