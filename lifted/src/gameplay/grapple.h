#pragma once

#include <cstdint>
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x004187B0 & 0x00418C30: Grapple & Caught Target Synchronization
// Synchronizes position, facing, and state transitions of caught entity to cpoint
void process_grapple_sync(global_t* world, uint32_t catcher_id);

// 1:1 Lift of 0x004064D0: Firen + Freeze = Firzen Fusion & Defusion
void process_firzen_fusion(global_t* world, uint32_t obj_id);

// Initiates a grapple hold between catcher and victim
bool initiate_grapple(global_t* world, uint32_t catcher_id, uint32_t victim_id);

// Executes a throw launch based on active cpoint throw vectors
void execute_throw(global_t* world, uint32_t catcher_id);

// Releases the grapple hold (e.g., hold timeout or catcher damage)
void release_grapple(global_t* world, uint32_t catcher_id);

} // namespace lf2

