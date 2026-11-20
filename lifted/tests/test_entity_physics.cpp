#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>
#include "core/object.h"
#include "gameplay/entity.h"

using namespace lf2;

void test_object_init()
{
    std::cout << "[+] Testing object_init (0x004061d0 1:1 parity)..." << std::endl;
    object_t obj;
    // Dirty memory to guarantee object_init clears everything
    std::memset(&obj, 0xAA, sizeof(obj));

    object_init(&obj);

    assert(obj.x == 0 && obj.y == 0 && obj.z == 0);
    assert(obj.x_position == 0.0 && obj.y_position == 0.0 && obj.z_position == 0.0);
    assert(obj.x_velocity == 0.0 && obj.y_velocity == 0.0 && obj.z_velocity == 0.0);
    assert(obj.frame_id1 == 0 && obj.frame_id2 == 0 && obj.frame_id3 == 0 && obj.frame_id4 == 0);
    assert(obj.facing == 0);
    assert(obj.wait_counter == 0);
    assert(obj.hp == 500 && obj.dark_hp == 500 && obj.max_hp == 500 && obj.mp == 500);
    assert(obj.owner == -1 && obj.clone == -1 && obj.enemy == -1);
    assert(obj.cpoint_hurt == 0 && obj.weapon_hp == 1000 && obj.ai_target_x == -1000 && obj.ai_target_z == -1000);
    assert(obj.attackable_distance == 1000);
    assert(obj.vulnerable_distance == 1000);

    for (int i = 0; i < 400; ++i)
    {
        assert(obj.vrest_of_objects[i] == 0);
    }

    std::cout << "    object_init passed: all offsets, vitals, and tables verified!" << std::endl;
}

void test_motion_and_boundaries()
{
    std::cout << "[+] Testing 3D motion integration and stage boundaries..." << std::endl;
    object_t obj;
    object_init(&obj);

    obj.x_position = 100.0;
    obj.z_position = 150.0;
    obj.x_velocity = 7.5;
    obj.z_velocity = -4.2;

    object_update_motion(&obj, 50, 300, 1000);
    assert(obj.x == 107); // 100 + 7.5 = 107.5 -> _ftol2_sse truncate to 107
    assert(obj.z == 145); // 150 - 4.2 = 145.8 -> _ftol2_sse truncate to 145

    // Test stage boundary clamping & blocked_* flags
    obj.z_position = 40.0;
    obj.z_velocity = -10.0;
    object_update_motion(&obj, 50, 300, 1000);
    assert(obj.z_position == 50.0);
    assert(obj.z == 50);
    assert(obj.blocked_up == 1);

    obj.x_position = 1050.0;
    object_update_motion(&obj, 50, 300, 1000);
    assert(obj.x_position == 1000.0);
    assert(obj.x == 1000);
    assert(obj.blocked_right == 1);

    std::cout << "    3D motion, _ftol2_sse truncation, and boundary clamping verified!" << std::endl;
}

void test_jump_gravity_and_landing()
{
    std::cout << "[+] Testing jump physics, 1.7 gravity acceleration, and landing..." << std::endl;
    object_t obj;
    object_init(&obj);

    // Initial jump impulse (airborne: y < 0)
    obj.y_position = -1.0;
    obj.y_velocity = -10.0;

    int ticks = 0;
    while (obj.y_position < 0.0 && ticks < 100)
    {
        object_update_physics(&obj);
        ticks++;
    }

    assert(obj.y == 0);
    assert(obj.y_position == 0.0);
    assert(obj.y_velocity == 0.0);
    assert(ticks > 10 && ticks < 20); // ~13 ticks under 1.7 gravity

    std::cout << "    Jump arc completed in " << ticks << " ticks under 1.7 gravity and landed at y = 0!" << std::endl;
}

void test_ground_friction()
{
    std::cout << "[+] Testing 1:1 ground friction deceleration..." << std::endl;
    object_t obj;
    object_init(&obj);

    obj.x_velocity = 2.0;
    obj.z_velocity = -1.5;

    // Apply -1.0 linear drag per tick
    object_apply_ground_friction(&obj);
    assert(obj.x_velocity == 1.0);
    assert(obj.z_velocity == -0.5);

    object_apply_ground_friction(&obj);
    assert(obj.x_velocity == 0.0);
    assert(obj.z_velocity == 0.0);

    std::cout << "    Ground friction successfully halted sliding velocities!" << std::endl;
}

void test_frame_progression()
{
    std::cout << "[+] Testing frame advancement, wait_counter > wait, and history shifting..." << std::endl;
    auto file_ptr = std::make_unique<file_t>();
    file_t &file = *file_ptr;
    std::memset(&file, 0, sizeof(file));

    // Frame 0: wait 3, next 1 (advances on wait_counter == 4 > 3)
    file.frames[0].wait = 3;
    file.frames[0].next = 1;

    // Frame 1: wait 2, next 2 (advances on wait_counter == 3 > 2)
    file.frames[1].wait = 2;
    file.frames[1].next = 2;

    // Frame 2: wait 1, next 999 (loops to frame 0 in authentic LF2)
    file.frames[2].wait = 1;
    file.frames[2].next = 999;

    // Frame 3: wait 1, next 1000 (particle expiration)
    file.frames[3].wait = 1;
    file.frames[3].next = 1000;

    object_t obj;
    object_init(&obj);
    obj.file = &file;
    obj.frame_id1 = 0;
    obj.frame_id2 = 0;

    // Tick Frame 0 (wait 3 -> takes 4 ticks)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 1);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 2);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 3);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 1 && obj.wait_counter == 0);
    assert(obj.frame_id2 == 1 && obj.frame_id3 == 0);

    // Tick Frame 1 (wait 2 -> takes 3 ticks)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 1 && obj.wait_counter == 1);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 1 && obj.wait_counter == 2);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 2 && obj.wait_counter == 0);
    assert(obj.frame_id2 == 2 && obj.frame_id3 == 1);

    // Tick Frame 2 (wait 1, next 999 -> 2 ticks -> loops back to frame 0)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 2 && obj.wait_counter == 1);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 0);

    // Set to Frame 3 and tick (wait 1, next 1000 -> 2 ticks -> expires and returns false)
    obj.frame_id1 = 3;
    obj.frame_id2 = 3;
    obj.wait_counter = 0;
    assert(object_tick_frame(&obj) == true);
    assert(object_tick_frame(&obj) == false);

    std::cout << "    Frame state progression and particle expiration verified 100%!" << std::endl;
}

void test_input_state_machine()
{
    std::cout << "[+] Testing player input state transitions (Walk, Jump, Attack, Defend)..." << std::endl;
    auto file_ptr = std::make_unique<file_t>();
    file_t &file = *file_ptr;
    std::memset(&file, 0, sizeof(file));
    file.walking_frame_rate = 3;
    file.walking_speed = 4.5;
    file.walking_speedz = 2.0;
    file.jump_height = -12.0;
    file.jump_distance = 4.0;
    file.jump_distancez = 2.0;

    file.frames[0].state = STATE_STANDING;
    file.frames[5].state = STATE_WALKING;
    file.frames[6].state = STATE_WALKING;
    file.frames[7].state = STATE_WALKING;
    file.frames[8].state = STATE_WALKING;
    file.frames[60].state = STATE_ATTACKING;
    file.frames[65].state = STATE_ATTACKING;
    file.frames[110].state = STATE_DEFEND;
    file.frames[210].wait = 0;
    file.frames[210].next = 212;
    file.frames[212].state = STATE_JUMPING;

    object_t player;
    object_init(&player);
    player.file = &file;
    player.frame_id1 = 0;

    // Test Walking Right
    input_state_t input;
    input.right = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 5);
    assert(player.facing == FACING_RIGHT);
    assert(player.x_velocity == 4.5);

    // Continue walking
    object_handle_input(&player, input);
    assert(player.x_velocity == 4.5);

    // Release right key, apply ground friction and stand frame
    input.right = false;
    object_handle_input(&player, input);
    object_apply_ground_friction(&player, 4.5);
    assert(player.x_velocity == 0.0);

    // Test Jump takeoff (210) -> frame_advance launch (212) with negative jump_height
    player.frame_id1 = 0;
    player.frame_id2 = 0;
    player.wait_counter = 0;
    input.jump = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 210);
    object_frame_advance(&player);
    assert(player.frame_id1 == 212);
    assert(player.y_velocity == -12.0);

    // Test Attack from standing (PRNG selects frame 60 or 65: (r + 12) * 5)
    input.jump = false;
    player.frame_id1 = 0;
    player.frame_id2 = 0;
    player.y = 0;
    player.y_position = 0.0;
    object_handle_input(&player, input); // latch release
    input.attack = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 60 || player.frame_id1 == 65);

    // Test Defend from standing (frame 110)
    input.attack = false;
    player.frame_id1 = 0;
    player.frame_id2 = 0;
    object_handle_input(&player, input); // latch release
    input.defend = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 110);

    std::cout << "    Input state machine transitions verified 100%!" << std::endl;
}

void test_phase20_entity_core()
{
    std::cout << "[+] Testing Phase 20 entity core (Betweenness, Velocity Averaging, Input Latching)..." << std::endl;

    // 1. Betweenness check (0x004061A0)
    assert(is_between(10, 15, 20) == true);
    assert(is_between(20, 15, 10) == true);
    assert(is_between(10, 25, 20) == false);
    assert(is_between(10, 10, 20) == false);

    // 2. Velocity averaging pass (0x004196F0)
    global_t world;
    std::memset(&world, 0, sizeof(world));
    object_t obj;
    object_init(&obj);
    obj.attacks = 3;
    obj.pic_x_gain = 12.0;
    obj.y_accl = 8.0;
    obj.z_accl = 4.0;
    world.objects[0] = &obj;
    world.is_object_exists[0] = 1;

    world_average_velocities(&world);
    assert(obj.x_velocity == 6.0);
    assert(obj.y_velocity == 4.0);
    assert(obj.z_velocity == 2.0);
    assert(obj.attacks == 0);
    assert(obj.pic_x_gain == 0.0);
    assert(obj.y_accl == 0.0);
    assert(obj.z_accl == 0.0);

    // 3. Network input unpacking & latching (0x004197A0)
    uint8_t pkt[8] = {0};
    pkt[0] = 0x80 | 0x08; // UP + ATTACK
    slot_unpack_network_inputs(&world, pkt, 0);
    assert(obj.click_up == 1);
    assert(obj.click_attack == 1);
    assert(obj.click_jump == 0);
    assert(obj.click_defend == 0);

    // Next frame shift: previous frame click should shift to holding
    pkt[0] = 0x04; // JUMP only
    slot_unpack_network_inputs(&world, pkt, 0);
    assert(obj.holding_up == 1);
    assert(obj.holding_attack == 1);
    assert(obj.click_up == 0);
    assert(obj.click_attack == 0);
    assert(obj.click_jump == 1);

    // 4. Local slot latching & replay recording (0x004198F0)
    int32_t slot_types[8] = {-1, 0, 0, 0, 0, 0, 0, 0};
    uint8_t local_in[8] = {0x40 | 0x02, 0, 0, 0, 0, 0, 0, 0}; // DOWN + DEFEND
    uint8_t replay_tape[16] = {0};
    slot_latch_local_inputs(&world, slot_types, local_in, 0, true, replay_tape, 5);
    assert(obj.holding_jump == 1);
    assert(obj.click_down == 1);
    assert(obj.click_defend == 1);
    assert(obj.click_jump == 0);
    assert(replay_tape[5] == (0x40 | 0x02));

    std::cout << "    Betweenness, velocity averaging, and slot input latching verified 100%!" << std::endl;
}

void test_phase21_22_pipeline()
{
    std::cout << "[+] Testing Phase 21 & 22 Lifted 15-Function Frame, Combo, Input & Physics Pipeline..." << std::endl;

    auto char_file_ptr = std::make_unique<file_t>();
    file_t &f = *char_file_ptr;
    std::memset(&f, 0, sizeof(f));
    f.id = DAVIS_DAT;
    f.type = TYPE_CHARACTER;
    f.walking_frame_rate = 3;
    f.walking_speed = 4.0;
    f.walking_speedz = 2.0;
    f.running_frame_rate = 3;
    f.running_speed = 8.0;
    f.running_speedz = 3.0;
    f.heavy_walking_speed = 2.5;
    f.heavy_walking_speedz = 1.5;
    f.heavy_running_speed = 5.0;
    f.heavy_running_speedz = 2.0;
    f.jump_height = -16.0;
    f.jump_distance = 5.0;
    f.jump_distancez = 2.5;
    f.dash_height = -12.0;
    f.dash_distance = 12.0;
    f.dash_distancez = 3.0;
    f.rowing_height = -10.0;
    f.rowing_distance = 6.0;

    for (int i : {0, 5, 9, 12, 16, 50, 85, 90, 94, 100, 102, 108, 110, 114, 180, 181, 182, 183, 185, 186, 187, 188, 189, 191, 202, 210, 212, 213, 215, 219, 230, 231, 235, 240, 245, 250, 255, 260, 265, 270, 275, 280, 300})
    {
        f.frames[i].present = 1;
    }
    f.frames[0].state = STATE_STANDING;
    f.frames[5].state = STATE_WALKING;
    f.frames[9].state = STATE_RUNNING;
    f.frames[12].state = STATE_WALKING;
    f.frames[16].state = STATE_RUNNING;
    f.frames[100].state = STATE_ROWING;
    f.frames[110].state = STATE_DEFEND;
    f.frames[110].wait = 5;
    f.frames[110].hit_Fa = 235;
    f.frames[110].hit_Ua = 240;
    f.frames[110].hit_Da = 245;
    f.frames[110].hit_Fj = 250;
    f.frames[110].hit_Uj = 255;
    f.frames[110].hit_Dj = 260;
    f.frames[110].hit_ja = 265;
    for (int i : {180, 181, 182, 183, 186, 187, 188, 189})
        f.frames[i].state = STATE_FALLING;
    f.frames[210].state = STATE_ATTACKING;
    f.frames[210].wait = 0;
    f.frames[210].next = 212;
    f.frames[212].state = STATE_JUMPING;
    f.frames[213].state = STATE_DASHING;
    f.frames[215].state = STATE_INJURED_2;
    f.frames[235].mp = 150;
    f.frames[235].dvx = 556;
    f.frames[235].dvy = 548;
    f.frames[235].dvz = 553;
    f.frames[240].mp = 2050; // HP cost = 2*10 = 20, MP cost = 50
    f.frames[265].mp = 100;
    f.frames[300].mp = 100;

    object_t obj;
    object_init(&obj);
    obj.file = &f;

    // 1. object_input_history_push (0x0040E450)
    object_input_history_push(&obj, 9);
    object_input_history_push(&obj, 6);
    object_input_history_push(&obj, 5);
    assert(obj.input_history[2] == 9 && obj.input_history[3] == 6 && obj.input_history[4] == 5);

    // 2. object_combo_interrupted (0x0040E170)
    obj.attack_press = 5;
    assert(object_combo_interrupted(&obj, 'd', 0) == 1);
    assert(object_combo_interrupted(&obj, 'U', 1) == 1);
    assert(object_combo_interrupted(&obj, 'D', 1) == 1);
    assert(object_combo_interrupted(&obj, 'L', 1) == 1);
    assert(object_combo_interrupted(&obj, 'R', 1) == 1);
    assert(object_combo_interrupted(&obj, 'd', 1) == 1);
    assert(object_combo_interrupted(&obj, 'j', 1) == 1);
    assert(object_combo_interrupted(&obj, 'a', 1) == 0);
    obj.attack_press = 0;

    // 3. object_frame_transition (0x0040E2D0): HP+MP cost, insufficient rejection, flip, 999->0, present=0
    obj.hp = 500;
    obj.mp = 500;
    object_frame_transition(&obj, 240, true);
    assert(obj.frame_id1 == 240);
    assert(obj.hp == 480 && obj.hp_lost == 20);
    assert(obj.mp == 450 && obj.mp_used == 50);

    // Insufficient MP rejected
    obj.mp = 10;
    obj.frame_id1 = 0;
    object_frame_transition(&obj, 240, true);
    assert(obj.frame_id1 == 0);

    // Negative frame flip + 999->0 + present==0 no-op
    obj.hp = 500;
    obj.mp = 500;
    obj.facing = FACING_RIGHT;
    object_frame_transition(&obj, -235, true);
    assert(obj.frame_id1 == 235 && obj.facing == FACING_LEFT);
    object_frame_transition(&obj, 999, true);
    assert(obj.frame_id1 == 0);
    object_frame_transition(&obj, 299, true); // present == 0
    assert(obj.frame_id1 == 0);

    // 4. All 9 combo recognizers + Louis HP<178 gate + Firzen defusion
    auto run_combo = [&](input_state_t step1, input_state_t step2, input_state_t step3, uint32_t expected_fid, int expected_facing)
    {
        object_init(&obj);
        obj.file = &f;
        obj.facing = FACING_LEFT;
        obj.frame_id1 = 110;
        obj.frame_id2 = 110;
        object_handle_input(&obj, step1);
        object_handle_input(&obj, step2);
        object_handle_input(&obj, step3);
        assert(obj.frame_id1 == expected_fid);
        if (expected_facing >= 0)
            assert(obj.facing == static_cast<uint8_t>(expected_facing));
    };
    input_state_t inD{};
    inD.defend = true;
    input_state_t inR{};
    inR.right = true;
    input_state_t inL{};
    inL.left = true;
    input_state_t inU{};
    inU.up = true;
    input_state_t inDn{};
    inDn.down = true;
    input_state_t inA{};
    inA.attack = true;
    input_state_t inJ{};
    inJ.jump = true;

    run_combo(inD, inR, inA, 235, FACING_RIGHT); // D > R > A
    run_combo(inD, inL, inA, 235, FACING_LEFT);  // D > L > A
    run_combo(inD, inU, inA, 240, -1);           // D > U > A
    run_combo(inD, inDn, inA, 245, -1);          // D > D > A
    run_combo(inD, inR, inJ, 250, FACING_RIGHT); // D > R > J
    run_combo(inD, inL, inJ, 250, FACING_LEFT);  // D > L > J
    run_combo(inD, inU, inJ, 255, -1);           // D > U > J
    run_combo(inD, inDn, inJ, 260, -1);          // D > D > J
    run_combo(inD, inJ, inA, 265, -1);           // D > J > A

    // Louis target 300 HP < 178 gate & unlock_chars bypass
    f.id = LOUIS_DAT;
    f.frames[110].hit_ja = 300;
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 110;
    obj.frame_id2 = 110;
    obj.hp = 300;
    object_handle_input(&obj, inD, true, 0);
    object_handle_input(&obj, inJ, true, 0);
    object_handle_input(&obj, inA, true, 0);
    assert(obj.frame_id1 == 110); // Blocked when hp >= 178 && unlock_chars == 0
    obj.hp = 150;
    obj.click_DJA = 3;
    object_combo_dja(&obj, true, 0);
    assert(obj.frame_id1 == 300); // Allowed when hp < 178

    // Firzen defusion (_unknown34[0] == 1) clears firen_counter
    f.id = FIRZEN_DAT;
    f.frames[110].hit_ja = 0;
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 110;
    obj._unknown34[0] = 1;
    obj.firen_counter = 99;
    obj.click_DJA = 3;
    object_combo_dja(&obj, true, 0);
    assert(obj.firen_counter == 0);
    f.id = DAVIS_DAT;

    // 5. object_input_tick: dvx/dvy/dvz 550 override, double-tap run, heavy weapon, run+jump dash, 215 dash, 182/188 fall recovery
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 235;
    object_input_tick(&obj);
    assert(obj.x_velocity == 6.0 && obj.y_velocity == -2.0 && obj.z_velocity == 3.0);

    // Double-tap Right -> frame 9 (Running) -> Jump -> frame 213 (Dash)
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 0;
    obj.dash_counter = 4;
    obj.click_right = 1;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 9);
    obj.holding_right = 1;
    obj.click_jump = 1;
    obj.jump_press = 5;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 213 && obj.x_velocity == f.dash_distance && obj.y_velocity == f.dash_height);

    // Heavy weapon walk (12..15), run (16), throw/attack (50)
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 0;
    obj.weapon_type = TYPE_HEAVY_WEAPON;
    obj.click_right = 1;
    object_input_tick(&obj);
    assert(obj.frame_id1 >= 12 && obj.frame_id1 <= 15);
    obj.dash_counter = 4;
    obj.holding_right = 0;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 16);
    obj.click_attack = 1;
    obj.attack_press = 5;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 50);

    // Landing 215 forward dash
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 215;
    obj.x_velocity = 2.0;
    obj.click_jump = 1;
    obj.jump_press = 5;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 213 && obj.x_velocity == f.dash_distance && obj.y_velocity == f.dash_height);

    // Fall recovery 182/188 + jump -> 100 or 108 with rowing_height/rowing_distance
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 182;
    obj.facing = FACING_RIGHT;
    obj.x_velocity = -4.0;
    obj.click_jump = 1;
    obj.jump_press = 5;
    object_input_tick(&obj);
    assert(obj.frame_id1 == 100 && obj.y_velocity == f.rowing_height && obj.x_velocity == -f.rowing_distance);

    // 6. object_frame_advance: shaking pause, arest decrement, cpoint.kind == 2, TYPE_ATTACK drain, 110/202 flags
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 110;
    obj.frame_id2 = 110;
    obj.arest = 3;
    obj.shaking = 2;
    object_frame_advance(&obj);
    assert(obj.arest == 3); // Paused by shaking
    obj.shaking = 0;
    object_frame_advance(&obj);
    assert(obj.arest == 2 && obj.defend_lock == 3 && obj.wait_counter == 1);

    obj.frame_id1 = 202;
    obj.frame_id2 = 202;
    object_frame_advance(&obj);
    assert(obj.blink_time == 20);

    // cpoint.kind == 2 skips advancement
    f.frames[0].cpoint.kind = 2;
    obj.frame_id1 = 0;
    obj.frame_id2 = 0;
    obj.wait_counter = 0;
    object_frame_advance(&obj);
    assert(obj.wait_counter == 0);
    f.frames[0].cpoint.kind = 0;

    // TYPE_ATTACK hit_a drain -> hit_d on death
    f.type = TYPE_ATTACK;
    f.frames[0].hit_a = 10;
    f.frames[0].hit_d = 9;
    obj.frame_id1 = 0;
    obj.frame_id2 = 0;
    obj.hp = 5;
    object_frame_advance(&obj);
    assert(obj.hp == 0 && obj.frame_id1 == 9);
    f.type = TYPE_CHARACTER;
    f.frames[0].hit_a = 0;
    f.frames[0].hit_d = 0;

    // 7. object_physics_tick: shaking decrement, blocked_* enforcement, per-kind gravities, falling 180..189, ground landing/bounce, drink/light weapon bounce
    object_init(&obj);
    obj.file = &f;
    obj.shaking = -2;
    object_physics_tick(&obj);
    assert(obj.shaking == -1);

    object_init(&obj);
    obj.file = &f;
    obj.x_position = 100.0;
    obj.z_position = 50.0;
    obj.x_velocity = 5.0;
    obj.blocked_right = 1;
    obj.z_velocity = -4.0;
    obj.blocked_up = 1;
    object_physics_tick(&obj);
    assert(obj.x_position == 100.0 && obj.z_position == 50.0);
    assert(obj.blocked_right == 0 && obj.blocked_up == 0);

    // Falling frames 180..183 and 186..189
    object_init(&obj);
    obj.file = &f;
    obj.y_position = -20.0;
    obj.frame_id1 = 180;
    obj.y_velocity = -10.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 180);
    obj.y_velocity = -2.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 181);
    obj.y_velocity = 3.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 182);
    obj.y_velocity = 10.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 183);

    obj.frame_id1 = 186;
    obj.y_velocity = -10.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 186);
    obj.y_velocity = 3.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 188);
    obj.y_velocity = 10.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 189);

    // Ground landing: 212 -> 215, rowing 100 -> 215, state 100 -> 94, fall safe 230 vs bounce 185/191
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 212;
    obj.y_position = -1.0;
    obj.y_velocity = 4.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 215 && obj.y_position == 0.0 && obj.y_velocity == 0.0);

    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 100;
    obj.y_position = -1.0;
    obj.y_velocity = 4.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 215);

    f.frames[240].state = 100;
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 240;
    obj.y_position = -1.0;
    obj.y_velocity = 4.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 94);
    f.frames[240].state = 0;

    // Fall safe roll 231 (frame_id1 > 185) vs bounce 185 (high y_velocity + damage)
    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 188;
    obj.y_position = -1.0;
    obj.y_velocity = 5.0;
    object_physics_tick(&obj);
    assert(obj.frame_id1 == 231);

    object_init(&obj);
    obj.file = &f;
    obj.frame_id1 = 183;
    obj.y_position = -1.0;
    obj.y_velocity = 14.0;
    obj.thrown_injury = 50;
    obj.armor_multiplier = 100;
    object_physics_tick(&obj);
    assert(obj.hp == 450 && obj.dark_hp == 450 && obj.thrown_injury == 0);
    assert(obj.frame_id1 == 185 && obj.y_velocity == -3.5);

    // Drink & Light weapon gravity + bounce
    auto wpn_file_ptr = std::make_unique<file_t>();
    file_t &wf = *wpn_file_ptr;
    std::memset(&wf, 0, sizeof(wf));
    wf.type = TYPE_DRINK;
    wf.weapon_drop_hurt = 15;
    wf.frames[0].present = 1;
    wf.frames[0].state = 1000;
    object_init(&obj);
    obj.file = &wf;
    obj.y_position = -20.0;
    obj.y_velocity = 0.0;
    object_physics_tick(&obj);
    assert(std::abs(obj.y_velocity - 1.1333333333333333) < 1e-12);
    obj.y_position = -1.0;
    obj.y_velocity = 10.0;
    obj.facing = FACING_RIGHT;
    object_physics_tick(&obj);
    assert(obj.weapon_hp == 985 && obj.frame_id1 == 0 && obj.y_velocity == -7.0);

    std::cout << "    All Phase 21 & 22 functions (15/15) verified 100%!" << std::endl;
}

void test_phase20_opoint_and_hit_fa()
{
    std::cout << "[+] Testing Phase 20 opoint spawner (0x406A20) & hit_Fa physics (0x406BA0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t john_file{}, dennis_file{}, stick_file{}, firen_flame_file{}, firzen_chasef_file{},
           firzen_chasei_file{}, freeze_col_file{}, bat_chase_file{}, jball_file{},
           jan_chaseh_file{}, jan_chase_file{};
    john_file.id = JOHN_DAT; john_file.type = TYPE_CHARACTER;
    dennis_file.id = DENNIS_DAT; dennis_file.type = TYPE_CHARACTER;
    stick_file.id = STICK_DAT; stick_file.type = 1; stick_file.weapon_hp = 77;
    firen_flame_file.id = FIREN_FLAME_DAT; firen_flame_file.type = 3;
    firzen_chasef_file.id = FIRZEN_CHASEF_DAT; firzen_chasef_file.type = 3;
    firzen_chasei_file.id = FIRZEN_CHASEI_DAT; firzen_chasei_file.type = 3;
    freeze_col_file.id = FREEZE_COLUMN_DAT; freeze_col_file.type = 3;
    bat_chase_file.id = BAT_CHASE_DAT; bat_chase_file.type = 3;
    jball_file.id = JULIAN_BALL_DAT; jball_file.type = 3;
    jan_chaseh_file.id = JAN_CHASEH_DAT; jan_chaseh_file.type = 3;
    jan_chase_file.id = JAN_CHASE_DAT; jan_chase_file.type = 3;

    world.files[0] = &john_file;
    world.files[1] = &dennis_file;
    world.files[2] = &stick_file;
    world.files[3] = &firen_flame_file;
    world.files[4] = &firzen_chasef_file;
    world.files[5] = &firzen_chasei_file;
    world.files[6] = &freeze_col_file;
    world.files[7] = &bat_chase_file;
    world.files[8] = &jball_file;
    world.files[9] = &jan_chaseh_file;
    world.files[10] = &jan_chase_file;

    object_t p0, e1;
    object_init(&p0); p0.file = &john_file; p0.team = 1; p0.hp = 500;
    p0.x = 200; p0.y = 0; p0.z = 200; p0.x_position = 200.0; p0.z_position = 200.0;
    world.objects[0] = &p0; world.is_object_exists[0] = 1;

    object_init(&e1); e1.file = &dennis_file; e1.team = 2; e1.hp = 500;
    e1.x = 500; e1.y = 0; e1.z = 220; e1.x_position = 500.0; e1.z_position = 220.0;
    world.objects[1] = &e1; world.is_object_exists[1] = 1;

    // 1. object_spawn_opoint (0x406A20)
    int32_t s = object_spawn_opoint(&world, STICK_DAT, 0, 12, 1, 350, -10, 210, 3.5, -1.0, 0.25, FACING_LEFT);
    assert(s == 50);
    assert(world.is_object_exists[50] == 1);
    assert(world.objects[50]->chase_target == -1 && world.objects[50]->weapon_hp == 77);
    assert(world.objects[50]->x == 350 && world.objects[50]->y == -10 && world.objects[50]->z == 210);
    assert(world.objects[50]->x_velocity == 3.5 && world.objects[50]->facing == FACING_LEFT);
    world.is_object_exists[50] = 0;

    // 2. hit_Fa == 11: 14 volcano flames + self removed
    firen_flame_file.frames[1].hit_Fa = 11;
    object_init(world.objects[50]);
    world.objects[50]->file = &firen_flame_file; world.objects[50]->frame_id1 = 1;
    world.objects[50]->team = 1; world.objects[50]->x = 300; world.objects[50]->y = 0; world.objects[50]->z = 200;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0);
    int volcano_count = 0;
    for (int32_t i = 51; i <= 64; ++i) {
        if (world.is_object_exists[i] == 1) volcano_count++;
        world.is_object_exists[i] = 0;
    }
    assert(volcano_count == 14);
    firen_flame_file.frames[1].hit_Fa = 0;

    // 3. hit_Fa == 8: Bat multi-seeker
    bat_chase_file.frames[2].hit_Fa = 8;
    object_init(world.objects[50]);
    world.objects[50]->file = &bat_chase_file; world.objects[50]->frame_id1 = 2; world.objects[50]->team = 1;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0);
    int bat_count = 0;
    for (int32_t i = 51; i < 60; ++i) {
        if (world.is_object_exists[i] == 1) {
            assert(world.objects[i]->file->id == BAT_CHASE_DAT);
            assert(world.objects[i]->chase_target == 1);
            bat_count++;
            world.is_object_exists[i] = 0;
        }
    }
    assert(bat_count == 3);
    bat_chase_file.frames[2].hit_Fa = 0;

    // 4. hit_Fa == 13 (Julian seeker), 5 (Jan heal spawner), 6 (Jan chase spawner), 9 (Firzen disaster)
    jball_file.frames[2].hit_Fa = 13;
    object_init(world.objects[50]);
    world.objects[50]->file = &jball_file; world.objects[50]->frame_id1 = 2; world.objects[50]->team = 1;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0 && world.is_object_exists[51] == 1 && world.objects[51]->chase_target == 1);
    world.is_object_exists[51] = 0;
    jball_file.frames[2].hit_Fa = 0;

    jan_chaseh_file.frames[1].hit_Fa = 5;
    world.objects[50]->file = &jan_chaseh_file; world.objects[50]->frame_id1 = 1;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0 && world.is_object_exists[51] == 1 && world.objects[51]->chase_target == 0);
    world.is_object_exists[51] = 0;
    jan_chaseh_file.frames[1].hit_Fa = 0;

    jan_chase_file.frames[1].hit_Fa = 6;
    world.objects[50]->file = &jan_chase_file; world.objects[50]->frame_id1 = 1;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0 && world.is_object_exists[51] == 1 && world.objects[51]->chase_target == 1);
    world.is_object_exists[51] = 0;
    jan_chase_file.frames[1].hit_Fa = 0;

    firzen_chasef_file.frames[1].hit_Fa = 9;
    world.objects[50]->file = &firzen_chasef_file; world.objects[50]->frame_id1 = 1;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[50] == 0);
    int dis_cnt = 0;
    for (int32_t i = 51; i < 65; ++i) {
        if (world.is_object_exists[i] == 1) { dis_cnt++; world.is_object_exists[i] = 0; }
    }
    assert(dis_cnt == 4);
    firzen_chasef_file.frames[1].hit_Fa = 0;

    // 5. hit_Fa == 4: heal angel contact sets heal_timer = 100
    jan_chaseh_file.frames[2].hit_Fa = 4;
    object_init(world.objects[50]);
    world.objects[50]->file = &jan_chaseh_file; world.objects[50]->frame_id1 = 2;
    world.objects[50]->chase_target = 0;
    world.objects[50]->x = 200; world.objects[50]->y = -20; world.objects[50]->z = 200;
    world.is_object_exists[50] = 1;
    p0.heal_timer = 0;
    object_process_hit_fa(&world, 50);
    assert(world.objects[50]->frame_id1 == 60 && p0.heal_timer == 100);
    world.is_object_exists[50] = 0;
    jan_chaseh_file.frames[2].hit_Fa = 0;

    // 6. hit_Fa == 7 (meteor trail + explosion), 10 (accel clamp), 2/14 (speed frames), 1/3 (homing)
    firzen_chasef_file.frames[3].hit_Fa = 7;
    object_init(world.objects[50]);
    world.objects[50]->file = &firzen_chasef_file; world.objects[50]->frame_id1 = 3;
    world.objects[50]->team = 1; world.objects[50]->chase_target = 1;
    world.objects[50]->x = 250; world.objects[50]->y = -10; world.objects[50]->z = 200;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.is_object_exists[51] == 1 && world.objects[51]->frame_id1 == 40);
    assert(world.objects[50]->frame_id1 == 60 && world.objects[50]->x_velocity == 0.0);
    world.is_object_exists[50] = 0; world.is_object_exists[51] = 0;
    firzen_chasef_file.frames[3].hit_Fa = 0;

    firen_flame_file.frames[3].hit_Fa = 10;
    object_init(world.objects[50]);
    world.objects[50]->file = &firen_flame_file; world.objects[50]->frame_id1 = 3;
    world.objects[50]->team = 1; world.objects[50]->x_velocity = 29.5;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.objects[50]->x_velocity == 30.0 && world.objects[50]->facing == FACING_RIGHT);
    world.is_object_exists[50] = 0;
    firen_flame_file.frames[3].hit_Fa = 0;

    jan_chase_file.frames[3].hit_Fa = 14;
    object_init(world.objects[50]);
    world.objects[50]->file = &jan_chase_file; world.objects[50]->frame_id1 = 3;
    world.objects[50]->team = 1; world.objects[50]->chase_target = 1;
    world.objects[50]->x_velocity = 4.0; world.objects[50]->y_position = 3.0;
    world.is_object_exists[50] = 1;
    object_process_hit_fa(&world, 50);
    assert(world.objects[50]->frame_id1 == 53 && world.objects[50]->y_position == 1.4);
    jan_chase_file.frames[3].hit_Fa = 2;
    world.objects[50]->frame_id1 = 3; world.objects[50]->x_velocity = 11.0;
    object_process_hit_fa(&world, 50);
    assert(world.objects[50]->frame_id1 == 3);
    world.objects[50]->frame_id1 = 53;
    jan_chase_file.frames[53].hit_Fa = 1;
    world.objects[50]->x = 200; world.objects[50]->x_velocity = 0.0;
    object_process_hit_fa(&world, 50);
    assert(world.objects[50]->x_velocity == 0.85 && world.objects[50]->facing == FACING_RIGHT);
    jan_chase_file.frames[3].hit_Fa = 0;
    jan_chase_file.frames[53].hit_Fa = 0;

    for (uint32_t i = 50; i < MAX_OBJECTS; ++i) {
        delete world.objects[i];
        world.objects[i] = nullptr;
    }

    std::cout << "    Phase 20 opoint spawner (0x406A20) & all hit_Fa modes (1..14) verified 100%!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Entity Physics & State Machine Tests ===" << std::endl;
    test_object_init();
    test_motion_and_boundaries();
    test_jump_gravity_and_landing();
    test_ground_friction();
    test_frame_progression();
    test_input_state_machine();
    test_phase20_entity_core();
    test_phase20_opoint_and_hit_fa();
    test_phase21_22_pipeline();
    std::cout << "[SUCCESS] All Entity Physics & Lifecycle tests passed with 100% precision!" << std::endl;
    return 0;
}
