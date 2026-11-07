#include "app/survival.h"
#include "gameplay/entity.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace lf2;

static void test_vitals_recovery_math() {
    std::cout << "[+] Running Test 1: Difficulty-Based Player Vitals Recovery (0x00436FC0)...\n";

    survival_manager_t mgr_easy(survival_difficulty_t::EASY);
    assert(mgr_easy.calculate_heal_amount() == 200); // (2 + 2) * 50

    survival_manager_t mgr_norm(survival_difficulty_t::NORMAL);
    assert(mgr_norm.calculate_heal_amount() == 150); // (1 + 2) * 50

    survival_manager_t mgr_diff(survival_difficulty_t::DIFFICULT);
    assert(mgr_diff.calculate_heal_amount() == 100); // (0 + 2) * 50

    // Test player vitals application
    object_t p1; // Alive player
    object_init(&p1);
    p1.hp = 300;
    p1.dark_hp = 300;
    p1.max_hp = 500;
    p1.mp = 120;
    p1.frame_id1 = 10; // Knockdown frame (8 < frame < 12)

    object_t p2; // Dead player
    object_init(&p2);
    p2.hp = 0;
    p2.dark_hp = 0;
    p2.max_hp = 500;
    p2.mp = 0;

    object_t p3; // High HP player (test max clamp)
    object_init(&p3);
    p3.hp = 480;
    p3.dark_hp = 480;
    p3.max_hp = 500;
    p3.mp = 200;

    std::vector<object_t*> players = { &p1, &p2, &p3 };
    mgr_norm.apply_wave_clear_vitals(players);

    // p1: 300 + 150 = 450, MP = 500, state reset from 10 to 0
    assert(p1.hp == 450);
    assert(p1.dark_hp == 450);
    assert(p1.mp == 500);
    assert(p1.frame_id1 == 0);

    // p2: Revived with 5 HP and 500 MP (1:1 with 0x00437860)
    assert(p2.hp == 5);
    assert(p2.dark_hp == 5);
    assert(p2.mp == 500);

    // p3: 480 + 150 clamped to max_hp (500)
    assert(p3.hp == 500);
    assert(p3.dark_hp == 500);
    assert(p3.mp == 500);

    std::cout << "    [PASSED] Vitals recovery, dead player revival, and knockdown reset verified.\n";
}

static void test_wave_scaling_math() {
    std::cout << "[+] Running Test 2: Endless Wave Generation & Scaling Mathematics...\n";

    survival_manager_t mgr;

    // Wave 1: Baseline fodder
    survival_wave_spec_t w1 = mgr.generate_wave(1);
    assert(w1.wave_number == 1);
    assert(!w1.is_boss_wave);
    assert(w1.spawns.size() == 2); // Bandits & Hunters
    assert(w1.spawns[0].id == 30);
    assert(w1.spawns[0].hp == 60);
    assert(w1.spawns[0].times == 2);
    assert(w1.spawns[1].id == 31);
    assert(w1.spawns[1].hp == 75);

    // Wave 5: Scaled HP (+20%) and bonus fodder
    survival_wave_spec_t w5 = mgr.generate_wave(5);
    assert(w5.wave_number == 5);
    assert(w5.spawns[0].hp == 72); // 60 * 1.20
    assert(w5.spawns[0].times == 3); // 2 + (5/5)
    assert(w5.spawns.size() >= 3); // Martial artist added

    // Wave 15: Heavy knights included, high HP
    survival_wave_spec_t w15 = mgr.generate_wave(15);
    assert(w15.spawns.size() >= 4); // Bandits, Hunters, Martial Artist, Knight
    assert(w15.spawns[0].hp == 102); // 60 * (1 + 14 * 0.05 = 1.70)
    assert(w15.total_enemies > w1.total_enemies);

    std::cout << "    [PASSED] Procedural wave growth and HP scaling math verified.\n";
}

static void test_milestone_boss_progression() {
    std::cout << "[+] Running Test 3: Milestone Boss Waves & Boss Tier Progression...\n";

    survival_manager_t mgr;

    // Check milestone detector
    for (uint32_t w = 1; w < 10; ++w) {
        assert(!survival_manager_t::is_boss_milestone(w));
    }
    assert(survival_manager_t::is_boss_milestone(10));
    assert(survival_manager_t::is_boss_milestone(20));
    assert(survival_manager_t::is_boss_milestone(30));
    assert(survival_manager_t::is_boss_milestone(40));
    assert(survival_manager_t::is_boss_milestone(50));

    // Boss Wave 10: Firzen
    survival_wave_spec_t w10 = mgr.generate_wave(10);
    assert(w10.is_boss_wave);
    assert(w10.bgm == "bgm\\boss1.wma");
    bool found_boss = false;
    for (const auto& sp : w10.spawns) {
        if (sp.is_boss) {
            found_boss = true;
            assert(sp.id == FIRZEN_DAT); // Firzen (51)
            assert(sp.hp > 500);
        }
    }
    assert(found_boss);

    // Boss Wave 20: LouisEX
    survival_wave_spec_t w20 = mgr.generate_wave(20);
    assert(w20.is_boss_wave);
    assert(w20.bgm == "bgm\\boss2.wma");
    found_boss = false;
    for (const auto& sp : w20.spawns) {
        if (sp.is_boss) {
            found_boss = true;
            assert(sp.id == LOUISE_EX_DAT); // LouisEX (50)
        }
    }
    assert(found_boss);

    // Boss Wave 50: Julian Master Boss
    survival_wave_spec_t w50 = mgr.generate_wave(50);
    assert(w50.is_boss_wave);
    assert(w50.bgm == "bgm\\boss2.wma");
    found_boss = false;
    for (const auto& sp : w50.spawns) {
        if (sp.is_boss) {
            found_boss = true;
            assert(sp.id == JULIAN_DAT); // Julian (52)
            assert(sp.hp >= 3000);
        }
    }
    assert(found_boss);

    std::cout << "    [PASSED] Milestone boss tiers, BGM transitions, and boss scaling verified.\n";
}

static void test_hud_and_replay_formatting() {
    std::cout << "[+] Running Test 4: Survival HUD & Replay Filename Formatting...\n";

    survival_manager_t mgr;
    assert(mgr.format_hud() == "Survival Stage: 1");

    mgr.advance_wave();
    assert(mgr.format_hud() == "Survival Stage: 2");

    mgr.advance_wave();
    mgr.advance_wave();
    assert(mgr.format_hud() == "Survival Stage: 4");

    std::string replay_fn = mgr.generate_replay_filename();
    assert(replay_fn.find("_Survival.lfr") != std::string::npos);

    std::cout << "    [PASSED] HUD strings and .lfr replay filenames verified.\n";
}

static void test_curtain_state_machine() {
    std::cout << "[+] Running Test 5: Transition Curtain & Game Over State Machine (0x00437220)...\n";

    // Test Difficult mode: 0 immediately transitions to screen 1
    survival_manager_t mgr_diff(survival_difficulty_t::DIFFICULT);
    mgr_diff.update_curtain_step(false);
    assert(mgr_diff.get_curtain_state() == 1);

    // Test Normal mode: screen 0 displays first, then screen 1 is skipped to 2
    survival_manager_t mgr(survival_difficulty_t::NORMAL);
    mgr.update_curtain_step(false);
    assert(mgr.get_curtain_state() == 0);

    // Progress wipe steps until 13
    for (int i = 0; i < 15; ++i) {
        mgr.update_curtain_step(false);
    }
    assert(mgr.get_curtain_wipe() == 13);

    // Action key press triggers transition wait
    mgr.update_curtain_step(true);

    // Wait sequence steps
    for (int i = 0; i < 15; ++i) {
        mgr.update_curtain_step(false);
    }

    // Advance to state 5 (curtain finished -> return to main menu)
    while (!mgr.is_curtain_finished()) {
        mgr.update_curtain_step(true);
        for (int i = 0; i < 15; ++i) {
            mgr.update_curtain_step(false);
        }
    }
    assert(mgr.is_curtain_finished());

    std::cout << "    [PASSED] 0x00437220 curtain state transitions and menu handoff verified.\n";
}

int main() {
    std::cout << "=== Little Fighter 2 Endless Survival Mode Scaling Test Suite ===\n";

    test_vitals_recovery_math();
    test_wave_scaling_math();
    test_milestone_boss_progression();
    test_hud_and_replay_formatting();
    test_curtain_state_machine();

    std::cout << "\n[SUCCESS] All 5 Survival Mode test suites passed with 100% precision!\n";
    return 0;
}
