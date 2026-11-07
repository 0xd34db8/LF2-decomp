#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x004061D0
 * Function: lf2_object_init / object_reset
 * Calling Convention: __thiscall (ECX = object_t*)
 *
 * Description:
 *   Resets all spatial, motion, frame, combat, and attachment states
 *   of an object instance in the game world.
 */

void lf2_object_init(object_t *obj)
{
    if (!obj) return;

    memset(obj, 0, sizeof(object_t));

    // Exact initial constants from FUN_004061d0 (0x004061D0)
    // IEEE-754 0x3fb999999999999a == 0.1
    obj->pic_x_gain = 0.1;
    obj->y_accl = 0.1;
    obj->z_accl = 0.1;
    obj->x_velocity = 0.1;
    obj->y_velocity = 0.1;
    obj->z_velocity = 0.1;

    obj->x_position = 0.0;
    obj->y_position = 0.0;
    obj->z_position = 0.0;

    obj->facing = FACING_RIGHT;

    // Combat tracking defaults (0x2E8 - 0x2F8)
    obj->successful_attacks = 0;
    obj->attackable_distance = 1000;
    obj->vulnerable_distance = 1000;
    obj->_unknown29 = 1000;
    obj->clone = -1;
    obj->weapon_throw_injury = -1;

    // Health and MP defaults (0x2FC - 0x308)
    obj->hp = 500;
    obj->dark_hp = 500;
    obj->max_hp = 500;
    obj->mp = 500;

    // Ownership and identity defaults (0x324 - 0x364)
    obj->uid = -1;
    obj->_unknown34_rest[0] = -1;
    obj->_unknown34_rest[1] = -1;
    obj->_unknown39 = -1;
    obj->owner = 99;
    obj->enemy = -1;
    obj->team = 0;

    // AI target defaults (0x3F8 - 0x400)
    *((int32_t *)&obj->ai_target_x - 1) = -1;
    obj->ai_target_x = -1000;
    obj->ai_target_z = -1000;
}

// MSVC __thiscall bridge for FUN_004061d0
void FUN_004061d0(void)
{
    lf2_object_init((object_t *)in_ECX);
}
