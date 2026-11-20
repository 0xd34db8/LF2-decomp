#pragma once

#include <cstdint>
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x00418C30: World-wide cpoint chain combos, decrease/breakout, throw launch, Rudolf transform, dircontrol & orphan release
void world_process_cpoint_chain(global_t* world);

// 1:1 Lift of 0x004187B0: World-wide cpoint catch anchor synchronization, once-per-frame cpoint.injury & cover facing/depth
void world_process_cpoint_sync(global_t* world);

// 1:1 Lift of 0x004064D0: World-wide Firen + Freeze -> Firzen fusion & timer-0 defusion
void world_process_firzen_fusion(global_t* world, int32_t unlock_chars = 0);

// Runs cpoint chain (0x00418C30) + cpoint catch sync (0x004187B0) for a single catcher/caught entity
void process_grapple_sync(global_t* world, uint32_t catcher_id);

// Delegates to world_process_firzen_fusion (0x004064D0)
void process_firzen_fusion(global_t* world, uint32_t obj_id);

// Initiates a grapple hold between catcher and victim
bool initiate_grapple(global_t* world, uint32_t catcher_id, uint32_t victim_id);

// Executes a throw launch based on active cpoint throw vectors
void execute_throw(global_t* world, uint32_t catcher_id);

// Releases an active grapple hold cleanly
void release_grapple(global_t* world, uint32_t catcher_id);

} // namespace lf2
