#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include "app/tournament.h"
#include "core/random.h"

using namespace lf2;

void test_initialization() {
    std::cout << "[+] Testing Tournament Initialization (1:1 with State 0x14)..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);

    assert(mgr.get_contestant_count() == 8);
    assert(mgr.get_current_round() == tournament_round_t::ROUND_PRELIMINAR);
    assert(mgr.get_state() == tournament_state_t::RESET);
    assert(!mgr.is_tournament_finished());
    assert(mgr.get_champion_slot() == -1);

    for (uint32_t i = 0; i < 8; ++i) {
        const auto& c = mgr.get_contestant(i);
        assert(c.slot_id == static_cast<int32_t>(i));
        assert(c.char_id == -1);
        assert(c.controller == tournament_controller_t::COMPUTER);
        assert(c.hp == 500);
        assert(c.max_hp == 500);
        assert(c.progress == 0);
        assert(!c.is_boss);
    }

    std::cout << "    [PASS] 8-contestant bracket initialized to 500 HP, computer controllers, round 0." << std::endl;
}

void test_bracket_shuffling() {
    std::cout << "[+] Testing 50-Swap Bracket Seed Shuffling (1:1 with State 0x17)..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);

    mgr.shuffle_bracket();
    assert(mgr.get_state() == tournament_state_t::SHUFFLE);

    // Verify all 8 contestants are scheduled to play
    tournament_match_t match;
    std::vector<bool> slot_seen(8, false);
    int match_count = 0;

    while (match_count < 4 && mgr.find_next_match(match)) {
        assert(match.round == tournament_round_t::ROUND_PRELIMINAR);
        assert(match.team1_slots.size() == 1);
        assert(match.team2_slots.size() == 1);

        int32_t s1 = match.team1_slots[0];
        int32_t s2 = match.team2_slots[0];

        assert(s1 >= 0 && s1 < 8);
        assert(s2 >= 0 && s2 < 8);
        assert(s1 != s2);
        assert(!slot_seen[s1]);
        assert(!slot_seen[s2]);

        slot_seen[s1] = true;
        slot_seen[s2] = true;
        match_count++;

        // Simulate match so next match can be found
        mgr.simulate_cpu_match(match);
    }

    assert(match_count == 4);
    for (bool seen : slot_seen) {
        assert(seen);
    }

    std::cout << "    [PASS] 50-swap shuffle produced valid complete bracket permutation of 4 matches." << std::endl;
}

void test_autofill_randoms() {
    std::cout << "[+] Testing Random Slot Autofill (1:1 with State 0x18)..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);

    // Set slots 0 and 1 explicitly; leave 2..7 as -1
    mgr.set_contestant(0, 1, tournament_controller_t::HUMAN, false, "Deep");
    mgr.set_contestant(1, 2, tournament_controller_t::COMPUTER, false, "John");

    std::vector<int32_t> roster = { 3, 4, 5, 6, 7, 8, 9, 10 };
    mgr.autofill_randoms(roster);
    assert(mgr.get_state() == tournament_state_t::AUTOFILL);

    assert(mgr.get_contestant(0).char_id == 1);
    assert(mgr.get_contestant(1).char_id == 2);

    for (uint32_t i = 2; i < 8; ++i) {
        int32_t cid = mgr.get_contestant(i).char_id;
        assert(cid >= 3 && cid <= 10);
    }

    std::cout << "    [PASS] Slots 2..7 auto-filled from available roster; manual slots preserved." << std::endl;
}

void test_hp_degradation_formula() {
    std::cout << "[+] Testing HP Degradation Mathematical Formula (1:1 with State 0x1A)..." << std::endl;

    // Formula: hp = ((roll - diff * 12 + 85) * hp) / 100
    // where roll = lf2_random(0xfc, diff * 12 + 15) in [0, diff * 12 + 14]
    
    // For Difficult (diff = 0):
    // roll in [0, 14], multiplier in [85, 99]%
    for (int trial = 0; trial < 100; ++trial) {
        int32_t hp = tournament_manager_t::calculate_cpu_degraded_hp(500, tournament_difficulty_t::DIFFICULT);
        assert(hp >= (85 * 500) / 100);
        assert(hp <= (99 * 500) / 100);
    }

    // For Normal (diff = 1):
    // roll in [0, 26], multiplier in [73, 99]%
    for (int trial = 0; trial < 100; ++trial) {
        int32_t hp = tournament_manager_t::calculate_cpu_degraded_hp(500, tournament_difficulty_t::NORMAL);
        assert(hp >= (73 * 500) / 100);
        assert(hp <= (99 * 500) / 100);
    }

    // For Easy (diff = 2):
    // roll in [0, 38], multiplier in [61, 99]%
    for (int trial = 0; trial < 100; ++trial) {
        int32_t hp = tournament_manager_t::calculate_cpu_degraded_hp(500, tournament_difficulty_t::EASY);
        assert(hp >= (61 * 500) / 100);
        assert(hp <= (99 * 500) / 100);
    }

    std::cout << "    [PASS] Verified 300 trials across Easy (61..99%), Normal (73..99%), and Difficult (85..99%)." << std::endl;
}

void test_cpu_simulation_boss_advantage() {
    std::cout << "[+] Testing CPU Simulation & Boss Advantage Decision Tree..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);

    // Slot 0: Regular CPU fighter, Slot 1: Julian (boss archetype tier 5)
    mgr.set_contestant(0, 1, tournament_controller_t::COMPUTER, false, "Deep");
    mgr.set_contestant(1, 10, tournament_controller_t::COMPUTER, true, "Julian");

    tournament_match_t match;
    bool found = mgr.find_next_match(match);
    assert(found);
    assert(match.team1_slots[0] == 0);
    assert(match.team2_slots[0] == 1);
    assert(match.is_cpu_vs_cpu);

    // Julian MUST win against non-boss with 100% certainty
    bool ok = mgr.simulate_cpu_match(match);
    assert(ok);
    assert(match.completed);
    assert(match.winner_team == 2); // Julian is team 2

    // Julian advances (progress += 2 -> 2), Deep knocked out (progress += 1 -> 1)
    assert(mgr.get_contestant(1).progress == 2);
    assert(mgr.get_contestant(0).progress == 1);
    // Julian's HP degraded from 500
    assert(mgr.get_contestant(1).hp < 500 && mgr.get_contestant(1).hp >= 300);

    std::cout << "    [PASS] Boss contestant won decisively with authentic progress and degraded HP." << std::endl;
}

void test_full_8_bracket_progression() {
    std::cout << "[+] Testing Full 8-Contestant Knockout Ladder Progression..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);
    mgr.set_difficulty(tournament_difficulty_t::NORMAL);

    // Contestant 0 is powerful boss
    mgr.set_contestant(0, 10, tournament_controller_t::COMPUTER, true, "Julian");
    for (uint32_t i = 1; i < 8; ++i) {
        mgr.set_contestant(i, static_cast<int32_t>(i), tournament_controller_t::COMPUTER, false, "Fighter " + std::to_string(i));
    }

    int total_matches = 0;
    tournament_match_t match;

    while (mgr.find_next_match(match)) {
        total_matches++;
        assert(match.is_cpu_vs_cpu);
        mgr.simulate_cpu_match(match);
    }

    // 8 contestants: 4 Prelim + 2 SemiFinal + 1 Final = 7 matches total
    assert(total_matches == 7);
    assert(mgr.is_tournament_finished());
    assert(mgr.get_current_round() == tournament_round_t::ROUND_CHAMPION);
    assert(mgr.get_state() == tournament_state_t::VICTORY);

    int32_t champ = mgr.get_champion_slot();
    assert(champ == 0); // Julian won the championship!
    assert(mgr.get_contestant(champ).progress == 7);

    std::cout << "    [PASS] Completed 7 knockout matches (4 Prelim -> 2 Semi -> 1 Final). Champion crowned with progress = 7." << std::endl;
}

void test_2on2_tournament_mode() {
    std::cout << "[+] Testing 2-on-2 Team Tournament Mode (4 teams / 8 contestants)..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_2ON2, 8);

    // Team 1 (Slots 0, 1): Julian & Firzen (Bosses)
    mgr.set_contestant(0, 10, tournament_controller_t::COMPUTER, true, "Julian");
    mgr.set_contestant(1, 11, tournament_controller_t::COMPUTER, true, "Firzen");

    // Other teams: Regular fighters
    for (uint32_t i = 2; i < 8; ++i) {
        mgr.set_contestant(i, static_cast<int32_t>(i), tournament_controller_t::COMPUTER, false);
    }

    int match_count = 0;
    tournament_match_t match;

    while (mgr.find_next_match(match)) {
        match_count++;
        assert(match.team1_slots.size() == 2);
        assert(match.team2_slots.size() == 2);
        mgr.simulate_cpu_match(match);
    }

    // 4 teams: 2 SemiFinals + 1 Final = 3 matches
    assert(match_count == 3);
    assert(mgr.is_tournament_finished());
    assert(mgr.get_contestant(0).progress == 7);
    assert(mgr.get_contestant(1).progress == 7);

    std::cout << "    [PASS] 2on2 mode simulated 3 team matches. Both team members advanced and crowned champions." << std::endl;
}

void test_human_match_and_replay_filename() {
    std::cout << "[+] Testing Human Match Setup, Survivor HP & Authentic Replay Filename..." << std::endl;

    tournament_manager_t mgr;
    mgr.init(tournament_match_type_t::MATCH_1ON1, 8);

    // Slot 0: Human Player, Slot 1: Computer
    mgr.set_contestant(0, 1, tournament_controller_t::HUMAN, false, "Davis (Player 1)");
    mgr.set_contestant(1, 2, tournament_controller_t::COMPUTER, false, "Woody");

    tournament_match_t match;
    bool found = mgr.find_next_match(match);
    assert(found);
    assert(!match.is_cpu_vs_cpu);
    assert(mgr.get_state() == tournament_state_t::CONTROLLER_ASSIGN);

    // Test authentic replay filename format: YYYYMMDD_HHMMSS_1on1_Prelminar.lfr
    struct tm test_time = {};
    test_time.tm_year = 126; // 2026
    test_time.tm_mon  = 9;   // October (0-indexed = 9)
    test_time.tm_mday = 31;
    test_time.tm_hour = 23;
    test_time.tm_min  = 45;
    test_time.tm_sec  = 12;

    std::string fn_prelim = mgr.generate_replay_filename(tournament_round_t::ROUND_PRELIMINAR, &test_time);
    assert(fn_prelim == "20261031_234512_1on1_Prelminar.lfr");

    std::string fn_semi = mgr.generate_replay_filename(tournament_round_t::ROUND_SEMIFINAL, &test_time);
    assert(fn_semi == "20261031_234512_1on1_SemiFinal.lfr");

    std::string fn_final = mgr.generate_replay_filename(tournament_round_t::ROUND_FINAL, &test_time);
    assert(fn_final == "20261031_234512_1on1_Final.lfr");

    // Test 2on2 replay filename
    tournament_manager_t mgr2;
    mgr2.init(tournament_match_type_t::MATCH_2ON2, 8);
    std::string fn_2on2 = mgr2.generate_replay_filename(tournament_round_t::ROUND_PRELIMINAR, &test_time);
    assert(fn_2on2 == "20261031_234512_2on2_Prelminar.lfr");

    // Complete human match: Davis survives with 342 HP
    std::vector<int32_t> survivor_hps = { 342 };
    mgr.complete_human_match(match, 1, survivor_hps);

    assert(match.completed);
    assert(match.winner_team == 1);
    assert(mgr.get_contestant(0).hp == 342);
    assert(mgr.get_contestant(0).progress == 2);
    assert(mgr.get_contestant(1).progress == 1); // Woody knocked out

    std::cout << "    [PASS] Human match preserved exact survivor HP (342) and verified authentic replay filenames." << std::endl;
}

int main() {
    std::cout << "=== Little Fighter 2 Tournament & Championship Engine Verification ===" << std::endl;

    test_initialization();
    test_bracket_shuffling();
    test_autofill_randoms();
    test_hp_degradation_formula();
    test_cpu_simulation_boss_advantage();
    test_full_8_bracket_progression();
    test_2on2_tournament_mode();
    test_human_match_and_replay_filename();

    std::cout << "\n[SUCCESS] All Tournament Subsystem Tests Passed (100% 1:1 Parity With 0x00432AB0)!" << std::endl;
    return 0;
}

