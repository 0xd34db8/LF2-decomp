#pragma once

#include <cstdint>
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x00417F80: World-wide carried weapon sync, Milk/Beer drinking, fall/caught drop, throw & kind==3 drop
void world_process_weapons(global_t* world);

// 1:1 Lift of 0x0041BC90: Clears stale holder->weapon_type if held weapon slot is invalid or mismatched
void world_validate_weapon_holders(global_t* world);

// Checks for nearby dropped weapons and picks up light, throw, drink, or heavy weapons
bool try_pickup_weapon(global_t* world, uint32_t char_id);

// Synchronizes a held weapon (by character or weapon slot) via wpoint_sync_single (0x00417F80)
void process_weapon_sync(global_t* world, uint32_t char_id);

// Drops the currently held weapon immediately
void drop_weapon(global_t* world, uint32_t char_id);

// Throws the currently held weapon using wpoint velocity vectors (or default light throw speed)
void throw_weapon(global_t* world, uint32_t char_id);

} // namespace lf2
