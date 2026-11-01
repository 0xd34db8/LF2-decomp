#pragma once

#include <cstdint>
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x004068B0: Grapple & Caught Target Synchronization
// Synchronizes position, facing, and state transitions of caught entity to cpoint
void process_grapple_sync(global_t* world, uint32_t catcher_id);

// Initiates a grapple hold between catcher and victim
bool initiate_grapple(global_t* world, uint32_t catcher_id, uint32_t victim_id);

// Executes a throw launch based on active cpoint throw vectors
void execute_throw(global_t* world, uint32_t catcher_id);

// Releases the grapple hold (e.g., hold timeout or catcher damage)
void release_grapple(global_t* world, uint32_t catcher_id);

} // namespace lf2

