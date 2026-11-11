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

// 1:1 Lift of 0x004094B0, 0x00403A40, 0x00408CB0: AI Decision Tree & Behavior Synthesis
// Finds the nearest living enemy on an opposing team
uint32_t ai_find_nearest_target(const global_t* world, uint32_t ai_id);

// 1:1 Lift of 0x00403A40: Character-specific special move evaluation
bool ai_evaluate_character_special(object_t* self, const object_t* target, input_state_t& out_input);

// 1:1 Lift of 0x00408CB0: Held weapon / drink AI decision
bool ai_evaluate_weapon_decision(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input);

// 1:1 Lift of 0x004034F0: AI Combat Dodge / Evasive Maneuver & Roll
bool ai_evaluate_dodge(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input, ai_difficulty_t difficulty);

// Evaluates tactical combat situation and synthesizes virtual key inputs (0x004094B0)
input_state_t ai_evaluate_behavior(const global_t* world, uint32_t ai_id, ai_difficulty_t difficulty);

// Executes a full AI decision tick and feeds inputs to entity state machine
void ai_tick(global_t* world, uint32_t ai_id, ai_difficulty_t difficulty);

} // namespace lf2

