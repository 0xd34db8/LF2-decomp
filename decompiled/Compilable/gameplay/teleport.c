#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00403270
 * Function: lf2_teleport / Rudolf teleportation targeting logic
 * Calling Convention: __thiscall (ECX = global_t*)
 *
 * Parameters:
 *   global: Pointer to global world state
 *   teleported_id: Object index of the teleporting Rudolf
 *   teleport_to: 1 = Teleport behind nearest enemy
 *                2 = Teleport behind furthest teammate
 *
 * Math & Physics Parity:
 *   Enemy teleport: Places Rudolf 120px behind nearest target (z + 1).
 *   Teammate teleport: Places Rudolf 60px behind furthest teammate (z + 1).
 *   Velocities are zeroed and positions are synchronized.
 */

void lf2_teleport(global_t *global, int teleported_id, int teleport_to)
{
    if (!global || teleported_id < 0 || teleported_id >= MAX_OBJECTS) return;
    object_t *self = global->objects[teleported_id];
    if (!self) return;

    if (teleport_to == 1) { // Teleport to nearest enemy
        int closest_id = -1;
        int min_dist = 10000;

        for (int i = 0; i < MAX_OBJECTS; ++i) {
            if (i == teleported_id || !global->is_object_exists[i]) continue;
            object_t *other = global->objects[i];
            if (!other || !other->file) continue;

            // Target must be a character (type 0), different team, alive (hp > 0)
            if (other->file->type == TYPE_CHARACTER &&
                other->team != self->team &&
                other->hp > 0)
            {
                int dist = lf2_abs(other->z - self->z) + lf2_abs(other->x - self->x);
                if (dist < min_dist) {
                    closest_id = i;
                    min_dist = dist;
                }
            }
        }

        if (closest_id == -1) {
            self->y = 0;
            self->y_position = (double)self->y;
        } else {
            object_t *target = global->objects[closest_id];
            self->y = 0;
            self->z = target->z + 1;
            self->x = target->x + (self->facing == FACING_RIGHT ? -120 : 120);
            self->x_position = (double)self->x;
            self->y_position = (double)self->y;
            self->z_position = (double)self->z;
        }
        self->z_velocity = 0.0;
        self->x_velocity = 0.0;
        self->y_velocity = 0.0;
    }
    else if (teleport_to == 2) { // Teleport to furthest teammate
        int furthest_id = -1;
        int max_dist = -1;

        for (int i = 0; i < MAX_OBJECTS; ++i) {
            if (i == teleported_id || !global->is_object_exists[i]) continue;
            object_t *other = global->objects[i];
            if (!other || !other->file) continue;

            // Target must be a character (type 0), same team, alive (hp > 0)
            if (other->file->type == TYPE_CHARACTER &&
                other->team == self->team &&
                other->hp > 0)
            {
                int dist = lf2_abs(other->z - self->z) + lf2_abs(other->x - self->x);
                if (dist > max_dist) {
                    furthest_id = i;
                    max_dist = dist;
                }
            }
        }

        if (furthest_id == -1) {
            self->y = 0;
            self->y_position = (double)self->y;
        } else {
            object_t *target = global->objects[furthest_id];
            self->y = 0;
            self->z = target->z + 1;
            self->x = target->x + (self->facing == FACING_RIGHT ? -60 : 60);
            self->x_position = (double)self->x;
            self->y_position = (double)self->y;
            self->z_position = (double)self->z;
        }
        self->z_velocity = 0.0;
        self->x_velocity = 0.0;
        self->y_velocity = 0.0;
    }
}

// MSVC __thiscall symbol bridge for FUN_00403270
void FUN_00403270(int param_1, int *param_2)
{
    global_t *global = (global_t *)in_ECX;
    int teleport_to = (int)(intptr_t)param_2;
    lf2_teleport(global, param_1, teleport_to);
}
