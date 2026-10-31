#include "app/menu.h"
#include "gameplay/entity.h"
#include "core/random.h"
#include <cstring>

namespace lf2 {

void setup_battle_characters(global_t* world, const std::vector<player_slot_t>& slots,
                             int32_t stage_min_x, int32_t stage_max_x,
                             int32_t stage_min_z, int32_t stage_max_z)
{
    if (!world) return;

    int32_t width = (stage_max_x > stage_min_x) ? (stage_max_x - stage_min_x) : 200;
    int32_t depth = (stage_max_z > stage_min_z) ? (stage_max_z - stage_min_z) : 150;

    for (size_t i = 0; i < slots.size() && i < MAX_OBJECTS; ++i) {
        const auto& slot = slots[i];
        if (!slot.active) continue;

        object_t* obj = world->objects[i];
        if (!obj) {
            obj = new object_t();
            world->objects[i] = obj;
        }

        object_init(obj);

        // 1:1 Parity with 0x00436900
        obj->hp = 500;
        obj->dark_hp = 500;
        obj->max_hp = 500;
        obj->mp = 500;
        obj->invincible_time = 75; // 0x4B
        obj->team = slot.team;

        // Randomized initial spawn placement within stage bounds
        obj->x = stage_min_x + static_cast<int32_t>(lf2_random(0x10A + static_cast<uint32_t>(i), width));
        obj->y = 0;
        obj->z = stage_min_z + static_cast<int32_t>(lf2_random(0x10B + static_cast<uint32_t>(i), depth));
        obj->x_position = static_cast<double>(obj->x);
        obj->y_position = static_cast<double>(obj->y);
        obj->z_position = static_cast<double>(obj->z);

        // Orient facing towards stage center
        int32_t center_x = (stage_min_x + stage_max_x) / 2;
        obj->facing = (obj->x < center_x) ? FACING_RIGHT : FACING_LEFT;

        world->is_object_exists[i] = 1;
    }
}

} // namespace lf2

