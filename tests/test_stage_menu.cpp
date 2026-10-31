#include <iostream>
#include <cassert>
#include <cstring>
#include "app/menu.h"
#include "app/stage.h"
#include "gameplay/entity.h"

using namespace lf2;

void test_battle_setup_characters()
{
    std::cout << "[+] Testing 1:1 Battle Setup Parameters & Vitals (0x00436900)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    std::vector<player_slot_t> slots(2);
    // Player 1: Davis, Team 1
    slots[0].active = true;
    slots[0].char_id = DAVIS_DAT;
    slots[0].team = 1;
    slots[0].is_human = true;

    // Player 2: Dennis, Team 2
    slots[1].active = true;
    slots[1].char_id = DENNIS_DAT;
    slots[1].team = 2;
    slots[1].is_human = false;

    setup_battle_characters(&world, slots, 100, 500, 150, 350);

    // Verify Player 1
    assert(world.is_object_exists[0] == 1);
    object_t* p1 = world.objects[0];
    assert(p1 != nullptr);
    assert(p1->hp == 500);
    assert(p1->dark_hp == 500);
    assert(p1->max_hp == 500);
    assert(p1->mp == 500);
    assert(p1->invincible_time == 75);
    assert(p1->team == 1);
    assert(p1->x >= 100 && p1->x <= 500);
    assert(p1->y == 0);
    assert(p1->z >= 150 && p1->z <= 350);

    // Verify Player 2
    assert(world.is_object_exists[1] == 1);
    object_t* p2 = world.objects[1];
    assert(p2 != nullptr);
    assert(p2->hp == 500);
    assert(p2->dark_hp == 500);
    assert(p2->max_hp == 500);
    assert(p2->mp == 500);
    assert(p2->invincible_time == 75);
    assert(p2->team == 2);

    // Clean up allocated objects
    delete p1; world.objects[0] = nullptr;
    delete p2; world.objects[1] = nullptr;

    std::cout << "    Starting vitals (500 HP/MP, 75 invincibility) and spawn bounds verified!" << std::endl;
}

void test_stage_parser_and_progression()
{
    std::cout << "[+] Testing Stage Script Parser & Phase Progression..." << std::endl;

    std::string script = R"(
<stage> id: 1
    <phase> bound: 1000
        music: bgm\stage1.wma
        id: 30 hp: 60 times: 2 # bandit
    <phase_end>

    <phase> bound: 2000
        music: bgm\stage2.wma
        id: 31 hp: 120 times: 1 boss: 1 # hunter boss
    <phase_end>
<stage_end>
)";

    stage_manager_t stage_mgr;
    bool ok = stage_mgr.parse_stage_text(script);
    assert(ok == true);
    assert(stage_mgr.get_stage_count() == 1);

    const stage_definition_t* stage = stage_mgr.get_stage(1);
    assert(stage != nullptr);
    assert(stage->phases.size() == 2);
    assert(stage->phases[0].bound == 1000);
    assert(stage->phases[0].enemies.size() == 1);
    assert(stage->phases[0].enemies[0].id == 30);
    assert(stage->phases[0].enemies[0].times == 2);

    // Test stage initialization in game world
    global_t world;
    std::memset(&world, 0, sizeof(world));

    // Player 1 in slot 0
    object_t player;
    object_init(&player);
    player.hp = 500;
    player.team = 1;
    world.objects[0] = &player;
    world.is_object_exists[0] = 1;

    stage_mgr.start_stage(1, &world);
    assert(stage_mgr.get_current_phase_index() == 0);

    // Verify 2 enemies spawned on team 5 in slots 10 and 11
    assert(world.is_object_exists[10] == 1);
    assert(world.is_object_exists[11] == 1);
    assert(world.objects[10]->team == 5);
    assert(world.objects[11]->team == 5);
    assert(world.objects[10]->hp == 60);

    // Defeat 1 enemy: phase should not advance yet
    world.objects[10]->hp = 0;
    stage_mgr.update_stage(&world, 500);
    assert(stage_mgr.get_current_phase_index() == 0);
    assert(stage_mgr.is_stage_cleared() == false);

    // Defeat second enemy: phase should advance to phase 1 (boss phase)
    world.objects[11]->hp = 0;
    stage_mgr.update_stage(&world, 500);
    assert(stage_mgr.get_current_phase_index() == 1);

    // Verify boss spawned in slot 12
    assert(world.is_object_exists[12] == 1);
    assert(world.objects[12]->hp == 120);

    // Defeat boss: stage should be cleared!
    world.objects[12]->hp = 0;
    stage_mgr.update_stage(&world, 1000);
    assert(stage_mgr.is_stage_cleared() == true);
    assert(stage_mgr.is_stage_failed() == false);

    // Clean up allocated objects
    for (uint32_t i = 10; i < 15; ++i) {
        if (world.objects[i]) {
            delete world.objects[i];
            world.objects[i] = nullptr;
        }
    }

    std::cout << "    Stage phase transitions, enemy wave spawning, and clearance verified!" << std::endl;
}

void test_authentic_stage_dat_loading()
{
    std::cout << "[+] Testing Authentic Little Fighter 2 stage.dat Decryption & Parsing..." << std::endl;
    stage_manager_t stage_mgr;
    bool ok = stage_mgr.load_stages(".legacy/data/stage.dat");
    if (ok) {
        assert(stage_mgr.get_stage_count() > 0);
        const stage_definition_t* s50 = stage_mgr.get_stage(50); // Survival Stage
        assert(s50 != nullptr);
        assert(!s50->phases.empty());
        std::cout << "    Authentic stage.dat loaded " << stage_mgr.get_stage_count()
                  << " stages (Stage 50 has " << s50->phases.size() << " phases)!" << std::endl;
    } else {
        std::cout << "    (Authentic stage.dat skipped: not found in path)" << std::endl;
    }
}

int main()
{
    std::cout << "=== Little Fighter 2 Stage Mode & Menu Management Tests ===" << std::endl;
    test_battle_setup_characters();
    test_stage_parser_and_progression();
    test_authentic_stage_dat_loading();
    std::cout << "[SUCCESS] All Stage Mode & Menu Management tests passed with 100% precision!" << std::endl;
    return 0;
}

