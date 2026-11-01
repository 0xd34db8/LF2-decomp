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

    // Reset velocities and accelerations (offsets 0x28 - 0x58)
    obj->pic_x_gain = 0.0;
    obj->y_accl = 0.0;
    obj->z_accl = 0.0;
    obj->x_velocity = 0.0;
    obj->y_velocity = 0.0;
    obj->z_velocity = 0.0;

    // Continuous positions (offsets 0x58 - 0x70)
    obj->x_position = 0.0;
    obj->y_position = 0.0;
    obj->z_position = 0.0;

    // Discrete coordinates (offsets 0x10 - 0x1C)
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;

    // Counters and flags (offsets 0x00 - 0x0C)
    obj->move_counter = 0;
    obj->run_counter = 0;
    obj->invincible_time = 0;

    // Frame states (offsets 0x70 - 0x88)
    obj->frame_id1 = 0;
    obj->frame_id2 = 0;
    obj->frame_id3 = 0;
    obj->frame_id4 = 0;
    obj->facing = FACING_RIGHT;
    obj->wait_counter = 0;

    // Weapon & holding states (offsets 0x8C - 0xB8)
    obj->cpoint_catcher = 0;
    obj->cpoint_timer = 0;
    obj->weapon_type = 0;
    obj->weapon_id = 0;
    obj->holder_id = 0;
    obj->fall = 0;
    obj->shaking = 0;
    obj->bdefend = 0;

    // Input state bitfields
    obj->holding_up = 0;
    obj->holding_down = 0;
    obj->holding_left = 0;
    obj->holding_right = 0;
    obj->holding_attack = 0;
    obj->holding_jump = 0;
    obj->holding_defend = 0;
    obj->click_up = 0;
    obj->click_down = 0;
    obj->click_left = 0;
    obj->click_right = 0;
    obj->click_attack = 0;
    obj->click_jump = 0;
    obj->click_defend = 0;
    obj->defense_breaking = 0;

    // Combat tracking arrays
    memset(obj->vrest_of_objects, 0, sizeof(obj->vrest_of_objects));
    memset(obj->injured_of_attack, 0, sizeof(obj->injured_of_attack));
    memset(obj->itr_of_attack, 0, sizeof(obj->itr_of_attack));
    obj->successful_attacks = 0;
    obj->attackable_distance = 0;
    obj->vulnerable_distance = 0;
    obj->clone = 0;

    // Health, MP, and scoring
    obj->hp = 0;
    obj->dark_hp = 0;
    obj->max_hp = 0;
    obj->mp = 0;
    obj->pic_no_gain = 0;
    obj->drink_hp = 0;
    obj->thrown_injury = 0;
    obj->firen_counter = 0;
    obj->armor_multiplier = 0;
    obj->total_attack = 0;
    obj->hp_lost = 0;
    obj->mp_used = 0;
    obj->owner = 0;
    obj->kills = 0;
    obj->get_weapon_counter = 0;
    obj->enemy = 0;
    obj->team = 0;
    obj->file = NULL;
}

// MSVC __thiscall bridge for FUN_004061d0
void FUN_004061d0(void)
{
    lf2_object_init((object_t *)in_ECX);
}
