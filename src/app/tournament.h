#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <ctime>
#include "core/global.h"

namespace lf2 {

// Tournament battle configuration
enum class tournament_match_type_t : uint32_t {
    MATCH_1ON1 = 0,
    MATCH_2ON2 = 1
};

// Bracket progression round levels (1:1 with DAT_0044d318 / DAT_00451384)
enum class tournament_round_t : int32_t {
    ROUND_PRELIMINAR = 0, // Prelminar (4 matches in 8-bracket)
    ROUND_SEMIFINAL  = 2, // SemiFinal (2 matches in 8-bracket)
    ROUND_FINAL      = 4, // Final (1 match in 8-bracket)
    ROUND_CHAMPION   = 7  // Champion crowned!
};

// Tournament AI match difficulty setting (1:1 with _DAT_00450c30)
enum class tournament_difficulty_t : int32_t {
    DIFFICULT = 0, // 0: Difficult (HP degraded to 85..99%)
    NORMAL    = 1, // 1: Normal    (HP degraded to 73..99%)
    EASY      = 2  // 2: Easy      (HP degraded to 61..99%)
};

// Participant controller type (1:1 with DAT_00451364)
enum class tournament_controller_t : int32_t {
    COMPUTER = 0,
    HUMAN    = 1
};

// Internal state machine states (1:1 with 0x00432AB0 state switches)
enum class tournament_state_t : int32_t {
    IDLE              = 0x00,
    RESET             = 0x14, // State 20: Reset 8 bracket slots
    SELECT            = 0x15, // State 21: Character & Human/CPU selection
    CONFIRM           = 0x16, // State 22: Bracket layout confirmation
    SHUFFLE           = 0x17, // State 23: 50-swap random seed shuffle
    AUTOFILL          = 0x18, // State 24: Autofill random slots
    LADDER            = 0x19, // State 25: Ladder view & difficulty select
    MATCH_SELECT      = 0x1A, // State 26: Match selector & CPU vs CPU sim
    CONTROLLER_ASSIGN = 0x1B, // State 27: Controller setup for human match
    MATCH_COMPLETE    = 0x1C, // State 28: Save survivor HP & advance winner
    VICTORY           = 0x1D  // State 29: Champion podium victory
};

// Participant slot entry in the tournament ladder
struct tournament_contestant_t {
    int32_t slot_id = 0;
    int32_t char_id = -1; // -1 = Random
    tournament_controller_t controller = tournament_controller_t::COMPUTER;
    int32_t hp = 500;
    int32_t max_hp = 500;
    int32_t progress = 0; // 0=Prelim, 1=Prelim Out, 2=Semi, 3=Semi Out, 4=Final, 5=Runner-up, 7=Champion
    bool is_boss = false; // Tier 5 archetype (Julian / Firzen advantage)
    std::string name;
};

// Single match setup in the bracket
struct tournament_match_t {
    int32_t match_id = 0;
    tournament_round_t round = tournament_round_t::ROUND_PRELIMINAR;
    std::vector<int32_t> team1_slots; // Bracket slots
    std::vector<int32_t> team2_slots; // Bracket slots
    bool is_cpu_vs_cpu = true;
    bool completed = false;
    int32_t winner_team = -1; // 1 or 2
    std::string replay_filename;
};

// 1:1 Lift of LF2 Championship Tournament Mode (0x00432AB0)
class tournament_manager_t {
public:
    tournament_manager_t();

    // Initialize tournament bracket (8 or 16 slots, 1on1 or 2on2)
    void init(tournament_match_type_t match_type = tournament_match_type_t::MATCH_1ON1,
              uint32_t contestant_count = 8);

    // Contestant configuration
    void set_contestant(uint32_t slot, int32_t char_id, tournament_controller_t controller, bool is_boss = false, const std::string& name = "");
    const tournament_contestant_t& get_contestant(uint32_t slot) const;
    tournament_contestant_t& get_contestant(uint32_t slot);
    uint32_t get_contestant_count() const { return static_cast<uint32_t>(m_contestants.size()); }

    // Difficulty settings
    void set_difficulty(tournament_difficulty_t diff) { m_difficulty = diff; }
    tournament_difficulty_t get_difficulty() const { return m_difficulty; }

    // Bracket shuffling: 1:1 lift of State 0x17 (50 random slot swaps via PRNG)
    void shuffle_bracket();

    // Auto-fill unassigned/random character slots: 1:1 lift of State 0x18
    void autofill_randoms(const std::vector<int32_t>& available_character_ids);

    // Match scheduling & queries
    bool find_next_match(tournament_match_t& out_match);
    
    // CPU vs CPU match simulation: 1:1 lift of State 0x1A boss advantage + HP degradation
    bool simulate_cpu_match(tournament_match_t& match);

    // Human match completion handler: 1:1 lift of State 0x1C (saves survivor HP)
    void complete_human_match(tournament_match_t& match, int32_t winner_team, const std::vector<int32_t>& survivor_hps);

    // State & status queries
    tournament_state_t get_state() const { return m_state; }
    void set_state(tournament_state_t state) { m_state = state; }
    tournament_round_t get_current_round() const { return m_current_round; }
    int32_t get_champion_slot() const;
    bool is_tournament_finished() const;

    // Authentic replay filename generator matching 0x00432AB0:
    // Format: "YYYYMMDD_HHMMSS_<1on1|2on2>_<Prelminar|SemiFinal|Final>.lfr"
    std::string generate_replay_filename(tournament_round_t round, const struct tm* timeinfo = nullptr) const;

    // 1:1 HP degradation mathematical formula:
    // hp = ((lf2_random(0xfc, diff * 12 + 15) - diff * 12 + 85) * hp) / 100
    static int32_t calculate_cpu_degraded_hp(int32_t current_hp, tournament_difficulty_t difficulty);

private:
    void advance_round_if_needed();

    tournament_state_t        m_state = tournament_state_t::IDLE;
    tournament_match_type_t   m_match_type = tournament_match_type_t::MATCH_1ON1;
    tournament_difficulty_t   m_difficulty = tournament_difficulty_t::NORMAL;
    tournament_round_t        m_current_round = tournament_round_t::ROUND_PRELIMINAR;

    std::vector<tournament_contestant_t> m_contestants;
    std::vector<int32_t>                 m_seed_order; // Slot index mapping (DAT_0044d0e0)
    std::vector<tournament_match_t>      m_match_history;
};

} // namespace lf2

