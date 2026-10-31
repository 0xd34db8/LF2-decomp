#include "app/battle.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

using namespace lf2;

static void test_squad_quota_math() {
    std::cout << "[+] Running Test 1: Squad Allocation & Ratio Distribution Math (0x00438B40)...\n";

    int32_t active = 0;
    int32_t reserve = 0;

    // Normal case: base 3 active, 9 total, scale factor 3
    // scaled_total = 9*3/3 = 9, scaled_active = 3*3/3 = 3 -> active = 3, reserve = 6
    calculate_squad_quota(3, 9, 3, active, reserve);
    assert(active == 3);
    assert(reserve == 6);
    assert(active + reserve == 9);

    // Clamping to 1 active when total > 0 but scaled_active < 1:
    // base_active = 1, base_total = 3, scale = 1:
    // scaled_total = 3*1/3 = 1, scaled_active = 1*1/3 = 0 -> clamped to active = 1, reserve = 0
    calculate_squad_quota(1, 3, 1, active, reserve);
    assert(active == 1);
    assert(reserve == 0);

    // Zero quota
    calculate_squad_quota(0, 0, 3, active, reserve);
    assert(active == 0);
    assert(reserve == 0);

    std::cout << "    [PASSED] Squad quota calculation and active clamping verified.\n";
}

static void test_archetype_presets() {
    std::cout << "[+] Running Test 2: Archetype Preset Configurations...\n";

    battle_army_t army;

    // Archetype: NONE
    apply_archetype_preset(army, battle_archetype_t::NONE, 10);
    assert(army.get_total_troops() == 0);
    assert(army.get_total_active() == 0);
    assert(army.get_total_reserve() == 0);
    assert(army.is_annihilated());

    // Archetype: INFERIOR (Bandits & Hunters)
    apply_archetype_preset(army, battle_archetype_t::INFERIOR, 10);
    assert(army.archetype == battle_archetype_t::INFERIOR);
    assert(army.slots.size() == 10);
    assert(army.slots[0].active_count == 6);
    assert(army.slots[0].reserve_count == 12);
    assert(army.slots[0].unit_hp == 300);
    assert(army.get_total_troops() == 180);
    assert(!army.is_annihilated());

    // Archetype: BALANCED (Standard Martial Artists)
    apply_archetype_preset(army, battle_archetype_t::BALANCED, 10);
    assert(army.slots[0].active_count == 3);
    assert(army.slots[0].reserve_count == 6);
    assert(army.slots[0].unit_hp == 500);
    assert(army.get_total_troops() == 90);

    // Archetype: HEAVY_GIANT (Knights & Bosses)
    apply_archetype_preset(army, battle_archetype_t::HEAVY_GIANT, 10);
    assert(army.slots[0].active_count == 2);
    assert(army.slots[0].reserve_count == 4);
    assert(army.slots[0].unit_hp == 1000);
    assert(army.get_total_troops() == 60);

    // Archetype: CUSTOM_ALL_OUT (1:1 with 0x00438B40 lines 1885-1927)
    apply_archetype_preset(army, battle_archetype_t::CUSTOM_ALL_OUT, 10);
    assert(army.slots[0].active_count == 2);
    assert(army.slots[0].reserve_count == 30);
    assert(army.slots[1].active_count == 1);
    assert(army.slots[1].reserve_count == 15);
    assert(army.slots[3].active_count == 3);
    assert(army.slots[3].reserve_count == 3);

    std::cout << "    [PASSED] All archetype presets matched Ghidra specification.\n";
}

static void test_multiplier_scaling_and_cycling() {
    std::cout << "[+] Running Test 3: Army Roster Multiplier Scaling & Cycling...\n";

    // Format tests matching 0x00438B40 "x %d.%d"
    assert(format_battle_multiplier(100) == "x 1.0");
    assert(format_battle_multiplier(150) == "x 1.5");
    assert(format_battle_multiplier(200) == "x 2.0");
    assert(format_battle_multiplier(250) == "x 2.5");
    assert(format_battle_multiplier(300) == "x 3.0");

    // Cycling forward (Next)
    int32_t mult = 100;
    mult = cycle_battle_multiplier_next(mult); assert(mult == 150);
    mult = cycle_battle_multiplier_next(mult); assert(mult == 200);
    mult = cycle_battle_multiplier_next(mult); assert(mult == 250);
    mult = cycle_battle_multiplier_next(mult); assert(mult == 300);
    mult = cycle_battle_multiplier_next(mult); assert(mult == 100); // Wrap

    // Cycling backward (Prev)
    mult = cycle_battle_multiplier_prev(mult); assert(mult == 300); // Wrap
    mult = cycle_battle_multiplier_prev(mult); assert(mult == 250);
    mult = cycle_battle_multiplier_prev(mult); assert(mult == 200);
    mult = cycle_battle_multiplier_prev(mult); assert(mult == 150);
    mult = cycle_battle_multiplier_prev(mult); assert(mult == 100);

    // Multiplier effect on army troop generation
    battle_army_t army_1x;
    army_1x.multiplier = 100;
    apply_archetype_preset(army_1x, battle_archetype_t::BALANCED, 10);

    battle_army_t army_2x;
    army_2x.multiplier = 200;
    apply_archetype_preset(army_2x, battle_archetype_t::BALANCED, 10);

    assert(army_2x.get_total_troops() == army_1x.get_total_troops() * 2);
    assert(army_2x.slots[0].active_count == army_1x.slots[0].active_count * 2);
    assert(army_2x.slots[0].reserve_count == army_1x.slots[0].reserve_count * 2);

    std::cout << "    [PASSED] Multipliers scale troop quotas and wrap correctly.\n";
}

static void test_reinforcement_replenishment() {
    std::cout << "[+] Running Test 4: Battlefield Reinforcement Replenishment (0x00437860)...\n";

    battle_skirmish_simulator_t sim;
    battle_army_t army;
    army.team_id = 1;
    army.target_max_active = 10;
    apply_archetype_preset(army, battle_archetype_t::BALANCED, 10);
    // At Balanced 1x: 10 slots each with 3 active and 6 reserve -> total active = 30, reserve = 60
    // Let's set initial active to 8, reserve to 20
    army.slots.resize(2);
    army.slots[0].active_count = 4;
    army.slots[0].reserve_count = 10;
    army.slots[1].active_count = 4;
    army.slots[1].reserve_count = 10;
    // Current total active: 8, target_max_active: 10
    sim.add_army(army);

    // Initial replenishment should deploy 2 units to reach max 10
    int32_t spawned = sim.replenish_reinforcements(0);
    assert(spawned == 2);
    assert(sim.get_armies()[0].get_total_active() == 10);
    assert(sim.get_armies()[0].get_total_reserve() == 18);

    // No further spawn when already at max capacity
    assert(sim.replenish_reinforcements(0) == 0);

    // Record 4 casualties on slot 0
    sim.record_casualty(0, 0);
    sim.record_casualty(0, 0);
    sim.record_casualty(0, 0);
    sim.record_casualty(0, 0);

    // Casualties immediately trigger replenishment from reserve back up to target_max_active
    assert(sim.get_armies()[0].casualties == 4);
    assert(sim.get_armies()[0].get_total_active() == 10);
    assert(sim.get_armies()[0].get_total_reserve() == 14);

    // Deplete all reserves
    for (auto& s : sim.get_armies()[0].slots) {
        s.reserve_count = 0;
    }
    assert(sim.get_armies()[0].get_total_reserve() == 0);

    // Now when units die, reserve cannot replenish
    sim.record_casualty(0, 0);
    assert(sim.get_armies()[0].get_total_active() == 9);
    assert(sim.get_armies()[0].casualties == 5);

    std::cout << "    [PASSED] Reinforcement replenishment and casualty mechanics verified.\n";
}

static void test_skirmish_annihilation_victory() {
    std::cout << "[+] Running Test 5: Multi-Team Skirmish Resolution & Annihilation...\n";

    battle_skirmish_simulator_t sim;

    // Team 1 (Blue)
    battle_army_t blue_army;
    blue_army.army_id = 0;
    blue_army.team_id = 1;
    apply_archetype_preset(blue_army, battle_archetype_t::BALANCED, 2);

    // Team 2 (Red)
    battle_army_t red_army;
    red_army.army_id = 1;
    red_army.team_id = 2;
    apply_archetype_preset(red_army, battle_archetype_t::HEAVY_GIANT, 2);

    // Team 3 (Green)
    battle_army_t green_army;
    green_army.army_id = 2;
    green_army.team_id = 3;
    apply_archetype_preset(green_army, battle_archetype_t::INFERIOR, 2);

    sim.add_army(blue_army);
    sim.add_army(red_army);
    sim.add_army(green_army);

    sim.step_simulation();
    assert(!sim.is_battle_over());
    assert(sim.get_winning_team() == -1);

    // Annihilate Team 3 (Green)
    for (auto& s : sim.get_armies()[2].slots) {
        s.active_count = 0;
        s.reserve_count = 0;
    }
    assert(sim.get_armies()[2].is_annihilated());

    sim.step_simulation();
    assert(!sim.is_battle_over()); // Teams 1 and 2 still alive

    // Annihilate Team 2 (Red)
    for (auto& s : sim.get_armies()[1].slots) {
        s.active_count = 0;
        s.reserve_count = 0;
    }
    assert(sim.get_armies()[1].is_annihilated());

    sim.step_simulation();
    assert(sim.is_battle_over());
    assert(sim.get_winning_team() == 1); // Team 1 (Blue) is victorious!

    // Mutual annihilation case
    for (auto& s : sim.get_armies()[0].slots) {
        s.active_count = 0;
        s.reserve_count = 0;
    }
    sim.reset();
    sim.add_army(blue_army); // Dead
    for (auto& s : sim.get_armies()[0].slots) {
        s.active_count = 0;
        s.reserve_count = 0;
    }
    sim.step_simulation();
    assert(sim.is_battle_over());
    assert(sim.get_winning_team() == -1); // Tie / total mutual destruction

    std::cout << "    [PASSED] Multi-team victory and annihilation condition verified.\n";
}

static void test_hud_and_replay_formatting() {
    std::cout << "[+] Running Test 6: In-Game HUD & Battle Replay Filename Formatting...\n";

    // 1:1 with 0x00437860 sprintf format strings
    // With reserve > 0: "Man: %3d      HP: %4d     Reserve: %3d"
    std::string hud_with_res = format_battle_status_hud(12, 4500, 35);
    assert(hud_with_res == "Man:  12      HP: 4500     Reserve:  35");

    // With reserve == 0: "Man: %3d      HP: %4d"
    std::string hud_no_res = format_battle_status_hud(8, 2400, 0);
    assert(hud_no_res == "Man:   8      HP: 2400");

    // Stage format: STAGE %d-%d
    assert(format_stage_hud(42) == "STAGE 5-3");
    assert(format_stage_hud(0) == "STAGE 1-1");
    assert(format_stage_hud(19) == "STAGE 2-10");

    // Survival stage format: Survival Stage: %d
    assert(format_survival_stage_hud(5) == "Survival Stage: 5");

    // Battle replay filename format: %4d%02d%02d_%02d%02d%02d_Battle.lfr
    std::string replay_fn = format_battle_replay_filename(2026, 11, 1, 14, 30, 0);
    assert(replay_fn == "20261101_143000_Battle.lfr");

    std::cout << "    [PASSED] In-game HUD strings and authentic .lfr filename match.\n";
}

int main() {
    std::cout << "=== Little Fighter 2 Battle Mode & Skirmish Simulator Test Suite ===\n";

    test_squad_quota_math();
    test_archetype_presets();
    test_multiplier_scaling_and_cycling();
    test_reinforcement_replenishment();
    test_skirmish_annihilation_victory();
    test_hud_and_replay_formatting();

    std::cout << "\n[SUCCESS] All 6 Battle Mode test suites passed with 100% precision!\n";
    return 0;
}

