#pragma once

#include <cstdint>
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x00408CE0 & Weapon Interaction System
// Checks for nearby dropped weapons and picks up light or heavy weapons
bool try_pickup_weapon(global_t* world, uint32_t char_id);

// Synchronizes held weapon's world coordinates, facing, and animation frame to wpoint_t
void process_weapon_sync(global_t* world, uint32_t char_id);

// Drops the currently held weapon when damaged or knocked down
void drop_weapon(global_t* world, uint32_t char_id);

// Throws the currently held weapon using wpoint velocity vectors
void throw_weapon(global_t* world, uint32_t char_id);

} // namespace lf2

