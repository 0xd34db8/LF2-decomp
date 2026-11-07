#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <ctime>

namespace lf2 {

// Battle mode troop archetypes (1:1 with 0x00438B40 archetype selection)
enum class battle_archetype_t : int32_t {
    NONE            = 0, // Cleared/empty quota
    INFERIOR        = 1, // Bandits, Hunters & light fodder
    BALANCED        = 2, // Davis, Woody, Dennis, martial artists
    HEAVY_GIANT     = 3, // Knights, Golems, Julian, heavy armored bosses
    CUSTOM_ALL_OUT  = 4, // 30-Troop full custom army
    MELEE_DOMINANT  = 5, // Close-quarters brawlers
    RANGED_DOMINANT = 6, // Archers & projectile casters
    RANDOM_ARMY     = 7  // Randomized roster
};

// Battle Mode roster scale multipliers (1:1 with DAT_0044d758)
enum class battle_multiplier_t : int32_t {
    SCALE_1_0X = 100, // x 1.0
    SCALE_1_5X = 150, // x 1.5
    SCALE_2_0X = 200, // x 2.0
    SCALE_2_5X = 250, // x 2.5
    SCALE_3_0X = 300  // x 3.0
};

constexpr int32_t BATTLE_MULTIPLIER_MIN  = 100;
constexpr int32_t BATTLE_MULTIPLIER_MAX  = 300;
constexpr int32_t BATTLE_MULTIPLIER_STEP = 50;

// Multiplier formatting and cycling matching 0x00438B40
std::string format_battle_multiplier(int32_t multiplier);
int32_t cycle_battle_multiplier_next(int32_t current);
int32_t cycle_battle_multiplier_prev(int32_t current);

// Per-unit-type deployment slot in an army (1:1 with DAT_0044d5f8, DAT_0044d650, DAT_0044d6a8)
struct battle_unit_slot_t {
    int32_t unit_id        = 0;
    int32_t active_count   = 0; // "Man" currently deployed on battlefield (DAT_0044d5f8)
    int32_t reserve_count  = 0; // Reinforcement pool waiting in reserve (DAT_0044d650)
    int32_t total_quota    = 0; // Total army squad allocation (DAT_0044d6a8)
    int32_t unit_hp        = 500; // Base unit HP
};

// Quota distribution math (1:1 with 0x00438B40)
void calculate_squad_quota(int32_t base_active, int32_t base_total, int32_t scale_or_mult,
                           int32_t& out_active, int32_t& out_reserve);

// Battle army container
struct battle_army_t {
    int32_t army_id                  = 0;
    int32_t team_id                  = 1;   // Team affiliation (1..4)
    int32_t multiplier               = 100; // 100 = 1.0x, 150 = 1.5x, ..., 300 = 3.0x
    battle_archetype_t archetype     = battle_archetype_t::BALANCED;
    std::vector<battle_unit_slot_t> slots;

    int32_t casualties               = 0;   // Dead units
    int32_t target_max_active        = 10;  // Maximum live frontline units permitted

    // Calculations
    int32_t get_total_active() const;
    int32_t get_total_reserve() const;
    int32_t get_total_troops() const;
    int32_t get_total_hp() const;

    // Victory/Defeat state
    bool is_annihilated() const;
};

// Archetype preset configuration
void apply_archetype_preset(battle_army_t& army, battle_archetype_t archetype,
                            int32_t unit_type_count = 10);

// 1:1 with 0x00438B40: Authentic Battle Mode preset tables (500 HP per unit, (base * scale_factor) / 3)
void apply_authentic_battle_preset(battle_army_t& army, int32_t preset_id, int32_t scale_factor = 3);

// Status HUD string formatters (1:1 with 0x00437860 sprintf format strings)
std::string format_battle_status_hud(int32_t man_count, int32_t hp, int32_t reserve_count);
std::string format_stage_hud(int32_t stage_code);
std::string format_survival_stage_hud(int32_t survival_stage);

// Authentic replay filename generation (1:1 with 0x00438B40)
std::string format_battle_replay_filename(int32_t year, int32_t month, int32_t day,
                                          int32_t hour, int32_t minute, int32_t second);
std::string format_current_battle_replay_filename();

// Battle Skirmish & Annihilation Simulator
class battle_skirmish_simulator_t {
public:
    battle_skirmish_simulator_t() = default;

    void reset();
    void add_army(const battle_army_t& army);

    const std::vector<battle_army_t>& get_armies() const { return m_armies; }
    std::vector<battle_army_t>& get_armies() { return m_armies; }

    // Reinforcement logic (1:1 with 0x00437860)
    // When frontline slots fall below capacity, units are deployed from reserve
    int32_t replenish_reinforcements(size_t army_idx);

    // Casualty processing: an active unit dies
    void record_casualty(size_t army_idx, size_t slot_idx);

    // Annihilation & victory evaluation
    bool is_battle_over() const;
    int32_t get_winning_team() const; // -1 if ongoing or tie, team_id if victor

    // Complete simulation tick
    void step_simulation();

private:
    std::vector<battle_army_t> m_armies;
    bool m_battle_over = false;
    int32_t m_winning_team = -1;
};

} // namespace lf2

