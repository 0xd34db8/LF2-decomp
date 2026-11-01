#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "app/stage.h"
#include "core/global.h"

namespace lf2 {

// Survival mode difficulty levels (1:1 with _DAT_00450c30)
enum class survival_difficulty_t : int32_t {
    DIFFICULT = 0, // Difficult: +100 HP per wave clear
    NORMAL    = 1, // Normal:    +150 HP per wave clear
    EASY      = 2  // Easy:      +200 HP per wave clear
};

// Enemy spawn wave specifications for endless survival
struct survival_wave_spec_t {
    uint32_t wave_number = 1;
    bool is_boss_wave = false;
    std::string bgm = "bgm\\stage1.wma";
    std::vector<stage_enemy_spawn_t> spawns;
    int32_t total_enemies = 0;
};

// Endless Survival Mode Manager & Difficulty Scaling Engine
class survival_manager_t {
public:
    survival_manager_t(survival_difficulty_t difficulty = survival_difficulty_t::NORMAL);

    void reset();
    void set_difficulty(survival_difficulty_t difficulty) { m_difficulty = difficulty; }
    survival_difficulty_t get_difficulty() const { return m_difficulty; }

    uint32_t get_current_wave() const { return m_current_wave; }
    void advance_wave();

    // 1:1 with 0x00436FC0 player vitals recovery formula: (difficulty + 2) * 50
    int32_t calculate_heal_amount() const;

    // Apply round clearance rewards to players (1:1 with 0x00436FC0 & 0x00437860)
    // Revives dead players with 5 HP and restores MP to 500
    void apply_wave_clear_vitals(std::vector<object_t*>& players);

    // Procedural wave generation & scaling formula (incremental counts, HP multipliers, boss tiers)
    survival_wave_spec_t generate_wave(uint32_t wave_number) const;

    // Milestone evaluation (every 10 waves is a boss milestone)
    static bool is_boss_milestone(uint32_t wave_number) {
        return (wave_number > 0 && wave_number % 10 == 0);
    }
    static std::string get_milestone_bgm(uint32_t wave_number);

    // HUD and replay formatters
    std::string format_hud() const;
    std::string generate_replay_filename() const;

    // Survival game over & transition curtain state machine (1:1 with 0x00437220)
    int32_t get_curtain_state() const { return m_curtain_state; }
    int32_t get_curtain_wipe() const { return m_curtain_wipe; }
    bool is_curtain_finished() const { return m_curtain_state == 5; }
    void update_curtain_step(bool action_key_pressed);

private:
    uint32_t m_current_wave = 1;
    survival_difficulty_t m_difficulty = survival_difficulty_t::NORMAL;

    // Transition curtain state variables (1:1 with DAT_00451b28, DAT_00451b24, DAT_00451b20)
    int32_t m_curtain_state = 0; // DAT_00451b28
    int32_t m_curtain_wipe = 0;  // DAT_00451b24
    int32_t m_curtain_wait = 0;  // DAT_00451b20
    int32_t m_anim_tick = 0;     // DAT_00451b2c
};

} // namespace lf2

