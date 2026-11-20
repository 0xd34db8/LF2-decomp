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

// Stage & match parameters read by 0x004094B0 / 0x00408CB0 / 0x00403A40
struct ai_world_params_t {
    int32_t mode = 0;               // 0: VS, 1: Stage, 2: 1on1, 3: 2on2, 4: Battle, 5: Demo
    int32_t difficulty = 1;         // -1: CRAZY!, 0: Difficult, 1: Normal, 2: Easy
    int32_t stage_width = 2000;     // stage total width (DAT_00450bb4 / bg.width)
    int32_t zboundary_min = 0;      // top Z boundary (zboundary[1])
    int32_t zboundary_max = 400;    // bottom Z boundary (zboundary[2])
    int32_t stage_bound = 2000;     // current stage scroll bound
    int32_t stage_last_phase = 0;   // stage GO-arrow phase flag (DAT_00450bac)
    bool    random_game = false;    // demo / random flag (DAT_00450c2c)
    int32_t unlock_chars = 0;       // forwarded to object_input_tick
};

// 1:1 Lift of 0x004094B0, 0x00403A40, 0x00408CB0, 0x004034F0: AI Decision Tree & Behavior Synthesis

// Finds the nearest living enemy character on an opposing team (returns MAX_OBJECTS if none)
uint32_t ai_find_nearest_target(const global_t* world, uint32_t ai_id);

// 1:1 Lift of 0x00403A40: Character-specific special move evaluation across full roster
int32_t ai_evaluate_character_special(global_t* world, int32_t target_id, int32_t ai_id,
                                      int32_t self_state, int32_t target_state,
                                      int32_t incoming_proj, int32_t dist, int32_t z_close,
                                      int32_t width_limit, int32_t edge_flag, int32_t skill5);

// Compatibility wrapper for 3-argument special-move evaluation
bool ai_evaluate_character_special(object_t* self, const object_t* target, input_state_t& out_input);

// 1:1 Lift of 0x00408CB0: Held weapon / drink AI decision
int32_t ai_evaluate_weapon_decision(global_t* world, int32_t target_id, int32_t ai_id,
                                    int32_t self_state, int32_t target_state,
                                    int32_t z_close, int32_t incoming_proj,
                                    int32_t width_limit, int32_t edge_flag,
                                    int32_t skill3, int32_t skill5, int32_t skill15,
                                    const ai_world_params_t& params);

// Compatibility wrapper for 4-argument held weapon / drink evaluation
bool ai_evaluate_weapon_decision(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input);

// 1:1 Lift of 0x004034F0: AI Combat Dodge / Evasive Maneuver & Roll
int32_t ai_evaluate_dodge(global_t* world, int32_t target_id, int32_t ai_id,
                            int32_t target_state, int32_t hazard_right, int32_t hazard_left,
                            int32_t skill3, int32_t skill5);

// Compatibility wrapper for 5-argument dodge / roll evaluation
bool ai_evaluate_dodge(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input, ai_difficulty_t difficulty);

// 1:1 Lift of 0x004094B0: Master AI controller updating click_*, holding_*, combo_state[0..8], enemy & follow_order state
void ai_control_object(global_t* world, int32_t ai_id, const ai_world_params_t& params = ai_world_params_t{});

// Evaluates tactical combat situation and synthesizes virtual key inputs (0x004094B0)
input_state_t ai_evaluate_behavior(const global_t* world, uint32_t ai_id, ai_difficulty_t difficulty = AI_NORMAL);

// Executes a full AI decision tick and feeds inputs to entity state machine (0x004094B0 + 0x00413080)
void ai_tick(global_t* world, uint32_t ai_id, const ai_world_params_t& params);
void ai_tick(global_t* world, uint32_t ai_id, ai_difficulty_t difficulty = AI_NORMAL);

} // namespace lf2
