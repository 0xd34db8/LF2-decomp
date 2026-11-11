#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
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
    assert(obj.in_sky == 1 && obj.weapon_hp == 1000 && obj.ai_target_x == -1000 && obj.ai_target_z == -1000);
    assert(obj.attackable_distance == 1000);
    assert(obj.vulnerable_distance == 1000);

    for (int i = 0; i < 400; ++i) {
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
    assert(obj.x == 108); // 100 + 7.5 = 107.5 -> round to 108
    assert(obj.z == 146); // 150 - 4.2 = 145.8 -> round to 146

    // Test stage boundary clamping
    obj.z_position = 40.0;
    obj.z_velocity = -10.0;
    object_update_motion(&obj, 50, 300, 1000);
    assert(obj.z_position == 50.0);
    assert(obj.z == 50);

    obj.x_position = 1050.0;
    object_update_motion(&obj, 50, 300, 1000);
    assert(obj.x_position == 1000.0);
    assert(obj.x == 1000);

    std::cout << "    3D motion and boundary clamping verified!" << std::endl;
}

void test_jump_gravity_and_landing()
{
    std::cout << "[+] Testing jump physics, gravitational acceleration, and landing..." << std::endl;
    object_t obj;
    object_init(&obj);

    // Initial jump impulse (airborne: y < 0)
    obj.y_position = -1.0;
    obj.y_velocity = -10.0;

    int ticks = 0;
    while (obj.y_position < 0.0 && ticks < 100) {
        object_update_physics(&obj);
        object_update_motion(&obj);
        ticks++;
    }

    assert(obj.y == 0);
    assert(obj.y_position == 0.0);
    assert(obj.y_velocity == 0.0);
    assert(ticks > 15 && ticks < 30); // ~21 ticks for full jump arc

    std::cout << "    Jump arc completed in " << ticks << " ticks and landed cleanly at y = 0!" << std::endl;
}

void test_ground_friction()
{
    std::cout << "[+] Testing ground friction deceleration..." << std::endl;
    object_t obj;
    object_init(&obj);

    obj.x_velocity = 2.0;
    obj.z_velocity = -1.5;

    // Apply friction over several ticks
    for (int i = 0; i < 5; ++i) {
        object_apply_ground_friction(&obj, 0.6);
    }

    assert(obj.x_velocity == 0.0);
    assert(obj.z_velocity == 0.0);

    std::cout << "    Ground friction successfully halted sliding velocities!" << std::endl;
}

void test_frame_progression()
{
    std::cout << "[+] Testing frame advancement, wait counters, and history shifting..." << std::endl;
    file_t file;
    std::memset(&file, 0, sizeof(file));

    // Frame 0: wait 3, next 1
    file.frames[0].wait = 3;
    file.frames[0].next = 1;

    // Frame 1: wait 2, next 2
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

    // Tick Frame 0 (wait 3)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 1);
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0 && obj.wait_counter == 2);
    assert(object_tick_frame(&obj) == true);
    // Transition to Frame 1
    assert(obj.frame_id1 == 1 && obj.wait_counter == 0);
    assert(obj.frame_id2 == 0); // Previous frame shifted into history

    // Tick Frame 1 (wait 2)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 1 && obj.wait_counter == 1);
    assert(object_tick_frame(&obj) == true);
    // Transition to Frame 2
    assert(obj.frame_id1 == 2 && obj.wait_counter == 0);
    assert(obj.frame_id2 == 1 && obj.frame_id3 == 0);

    // Tick Frame 2 (wait 1, next 999 -> loops back to frame 0)
    assert(object_tick_frame(&obj) == true);
    assert(obj.frame_id1 == 0);

    // Set to Frame 3 and tick (wait 1, next 1000 -> expires and returns false)
    obj.frame_id1 = 3;
    obj.wait_counter = 0;
    bool alive = object_tick_frame(&obj);
    assert(alive == false);

    std::cout << "    Frame state progression and particle expiration verified 100%!" << std::endl;
}

void test_input_state_machine()
{
    std::cout << "[+] Testing player input state transitions (Walk, Jump, Attack, Defend)..." << std::endl;
    file_t file;
    std::memset(&file, 0, sizeof(file));
    file.walking_speed = 4.5;
    file.walking_speedz = 2.0;
    file.jump_height = 12.0;

    file.frames[0].state = STATE_STANDING;
    file.frames[5].state = STATE_WALKING;
    file.frames[60].state = STATE_ATTACKING;
    file.frames[110].state = STATE_DEFEND;
    file.frames[210].state = STATE_JUMPING;

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

    // Continue walking
    object_handle_input(&player, input);
    assert(player.x_velocity == 4.5);

    // Release keys -> Returns to standing
    input.right = false;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 0);
    assert(player.x_velocity == 0.0);

    // Test Jump
    input.jump = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 210);
    assert(player.y_velocity == -12.0);

    // Test Attack from standing
    input.jump = false;
    player.frame_id1 = 0;
    player.y = 0;
    player.y_position = 0.0;
    input.attack = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 60);

    // Test Defend from standing
    input.attack = false;
    player.frame_id1 = 0;
    input.defend = true;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 110);

    // Release defend -> returns to 0
    input.defend = false;
    object_handle_input(&player, input);
    assert(player.frame_id1 == 0);

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
    std::cout << "[SUCCESS] All Entity Physics & Lifecycle tests passed with 100% precision!" << std::endl;
    return 0;
}
