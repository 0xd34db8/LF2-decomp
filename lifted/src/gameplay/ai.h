#pragma once

#include <cstdint>
#include "core/global.h"
#include "gameplay/entity.h"

namespace lf2 {

enum ai_difficulty_t : uint32_t {
    AI_EASY   = 0,
    AI_NORMAL = 1,
    AI_CRAZY  = 2
};

// 1:1 Lift of 0x00406BA0: AI Decision Tree & Behavior Synthesis
// Finds the nearest living enemy on an opposing team
uint32_t ai_find_nearest_target(const global_t* world, uint32_t ai_id);

// Evaluates tactical combat situation and synthesizes virtual key inputs
input_state_t ai_evaluate_behavior(const global_t* world, uint32_t ai_id, ai_difficulty_t difficulty);

// Executes a full AI decision tick and feeds inputs to entity state machine
void ai_tick(global_t* world, uint32_t ai_id, ai_difficulty_t difficulty);

} // namespace lf2

