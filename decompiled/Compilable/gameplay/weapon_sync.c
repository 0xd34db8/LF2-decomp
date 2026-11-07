#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00408CE0
 * Function: lf2_weapon_sync / process_held_weapon
 * Class / Subsystem: object_t / Weapon Mechanics
 *
 * Description:
 *   Synchronizes the world position, orientation, and active display frame of
 *   a carried light or heavy weapon with the character's hand coordinates defined
 *   in wpoint_t. Handles weapon dropping upon damage and projectile throw impulses.
 */

void lf2_weapon_sync(global_t *global, uint32_t char_id)
{
    if (!global || char_id >= MAX_OBJECTS || !global->is_object_exists[char_id]) {
        return;
    }
    object_t *character = global->objects[char_id];
    if (!character || !character->file || character->weapon_type == 0) {
        return;
    }

    uint32_t weapon_id = character->weapon_id;
    if (weapon_id >= MAX_OBJECTS || !global->is_object_exists[weapon_id]) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    object_t *weapon = global->objects[weapon_id];
    if (!weapon || !weapon->file) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    // 1. If holder receives heavy damage or falls, drop the weapon
    if (character->fall > 0 || character->hp <= 0) {
        weapon->holder_id = 0;
        character->weapon_type = 0;
        character->weapon_id = 0;
        weapon->y_velocity = -4.0;
        weapon->x_velocity = (character->facing == FACING_LEFT) ? 2.0 : -2.0;
        return;
    }

    // 2. Retrieve holder's current frame and weapon attachment point (wpoint)
    frame_t *char_frame = &character->file->frames[character->frame_id1];
    wpoint_t *wpoint = &char_frame->wpoint;

    // 3. Anchor weapon to holder's hand coordinates
    int32_t hand_dx = wpoint->x - char_frame->centerx;
    int32_t hand_dy = wpoint->y - char_frame->centery;

    weapon->x = (character->facing == FACING_LEFT) ? character->x - hand_dx : character->x + hand_dx;
    weapon->y = character->y + hand_dy;
    weapon->z = character->z;
    weapon->x_position = (double)weapon->x;
    weapon->y_position = (double)weapon->y;
    weapon->z_position = (double)weapon->z;
    weapon->facing = character->facing;

    // Zero carried weapon velocities
    weapon->x_velocity = 0.0;
    weapon->y_velocity = 0.0;
    weapon->z_velocity = 0.0;

    // Update weapon active visual frame
    if (wpoint->weaponact != 0) {
        weapon->frame_id1 = wpoint->weaponact;
    }
}

// MSVC __thiscall bridge for FUN_00408cb0 / FUN_00408ce0
void FUN_00408cb0(void)
{
    lf2_weapon_sync((global_t *)in_ECX, (uint32_t)(uintptr_t)in_ECX);
}

void FUN_00408ce0(void)
{
    FUN_00408cb0();
}
