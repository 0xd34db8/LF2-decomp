#include "global.h"
#include <cstdlib>

namespace lf2 {

// func_00403270: Teleport entity to closest enemy (1) or farthest teammate (2)
// ECX: global_t* this
// param_1: teleported_id
// param_2: teleport_to
void global_t::teleport(uint32_t teleported_id, uint32_t teleport_to) {
    if (teleported_id >= MAX_OBJECTS || !is_object_exists[teleported_id]) {
        return;
    }

    object_t* teleported = objects[teleported_id];
    if (!teleported) {
        return;
    }

    int32_t target_id = -1;

    if (teleport_to == TELEPORT_TO_ENEMY) {
        int32_t min_distance = 10000;

        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (i == teleported_id || !is_object_exists[i]) {
                continue;
            }

            object_t* target = objects[i];
            if (!target || !target->file) {
                continue;
            }

            // Must be character type (0), different team, and alive (hp > 0)
            if (target->file->type == TYPE_CHARACTER &&
                target->team != teleported->team &&
                target->hp > 0) {
                
                int32_t dist_z = std::abs(target->z - teleported->z);
                int32_t dist_x = std::abs(target->x - teleported->x);
                int32_t dist = dist_z + dist_x;

                if (dist < min_distance) {
                    target_id = static_cast<int32_t>(i);
                    min_distance = dist;
                }
            }
        }

        if (target_id == -1) {
            teleported->y = 0;
            teleported->y_position = static_cast<double>(teleported->y);
            teleported->z_velocity = 0.0;
            teleported->y_velocity = 0.0;
            teleported->x_velocity = 0.0;
            return;
        }

        object_t* target = objects[target_id];
        teleported->y = 0;
        teleported->z = target->z + 1;

        // Facing right (0): x - 120 (-0x78); Facing left (1): x + 120 (+0x78)
        if (teleported->facing == FACING_RIGHT) {
            teleported->x = target->x - 120;
        } else {
            teleported->x = target->x + 120;
        }

    } else if (teleport_to == TELEPORT_TO_TEAM) {
        int32_t max_distance = -1;

        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (i == teleported_id || !is_object_exists[i]) {
                continue;
            }

            object_t* target = objects[i];
            if (!target || !target->file) {
                continue;
            }

            // Must be character type (0), same team, and alive (hp > 0)
            if (target->file->type == TYPE_CHARACTER &&
                target->team == teleported->team &&
                target->hp > 0) {
                
                int32_t dist_z = std::abs(target->z - teleported->z);
                int32_t dist_x = std::abs(target->x - teleported->x);
                int32_t dist = dist_z + dist_x;

                if (dist > max_distance) {
                    target_id = static_cast<int32_t>(i);
                    max_distance = dist;
                }
            }
        }

        if (target_id == -1) {
            teleported->y = 0;
            teleported->y_position = static_cast<double>(teleported->y);
            teleported->z_velocity = 0.0;
            teleported->y_velocity = 0.0;
            teleported->x_velocity = 0.0;
            return;
        }

        object_t* target = objects[target_id];
        teleported->y = 0;
        teleported->z = target->z + 1;

        // Facing right (0): x - 60 (-0x3C); Facing left (1): x + 60 (+0x3C)
        if (teleported->facing == FACING_RIGHT) {
            teleported->x = target->x - 60;
        } else {
            teleported->x = target->x + 60;
        }

    } else {
        return;
    }

    // Sync floating-point positions to integer coordinates
    teleported->x_position = static_cast<double>(teleported->x);
    teleported->y_position = static_cast<double>(teleported->y);
    teleported->z_position = static_cast<double>(teleported->z);

    // Zero velocities
    teleported->z_velocity = 0.0;
    teleported->y_velocity = 0.0;
    teleported->x_velocity = 0.0;
}

} // namespace lf2

