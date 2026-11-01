#include <iostream>
#include <cassert>
#include <cstring>
#include "core/global.h"
#include "gameplay/entity.h"
#include "gameplay/grapple.h"
#include "gameplay/weapon.h"

using namespace lf2;

void test_grapple_initiate_and_sync()
{
    std::cout << "[+] Testing Grapple Catch Initiation & Anchor Sync (0x004068B0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t catcher_file;
    std::memset(&catcher_file, 0, sizeof(catcher_file));
    catcher_file.id = DAVIS_DAT;
    catcher_file.type = TYPE_CHARACTER;

    // Frame 120: Holding victim (State 9)
    frame_t& c_frame = catcher_file.frames[120];
    c_frame.state = STATE_CATCHING;
    c_frame.centerx = 40;
    c_frame.centery = 40;
    c_frame.cpoint.kind = 1;
    c_frame.cpoint.x = 65;
    c_frame.cpoint.y = 40;
    c_frame.cpoint.v_action = 230;

    file_t victim_file;
    std::memset(&victim_file, 0, sizeof(victim_file));
    victim_file.id = DENNIS_DAT;
    victim_file.type = TYPE_CHARACTER;
    frame_t& v_frame = victim_file.frames[0];
    v_frame.state = STATE_STANDING;
    v_frame.centerx = 40;
    v_frame.centery = 40;

    object_t catcher;
    object_init(&catcher);
    catcher.file = &catcher_file;
    catcher.frame_id1 = 120;
    catcher.frame_id4 = 120;
    catcher.x = 200;
    catcher.y = 0;
    catcher.z = 150;
    catcher.facing = FACING_RIGHT;

    object_t victim;
    object_init(&victim);
    victim.file = &victim_file;
    victim.frame_id1 = 0;
    victim.frame_id4 = 0;
    victim.x = 220;
    victim.y = 0;
    victim.z = 150;
    victim.facing = FACING_LEFT;

    world.objects[0] = &catcher;
    world.is_object_exists[0] = 1;
    world.objects[1] = &victim;
    world.is_object_exists[1] = 1;

    bool caught = initiate_grapple(&world, 0, 1);
    assert(caught == true);
    assert(catcher.cpoint_catcher == 1);
    assert(victim.cpoint_timer == 0); // 0 is catcher_id
    assert(victim.frame_id1 == 230); // Caught frame

    // Execute synchronization tick
    process_grapple_sync(&world, 0);

    // Verify victim position anchored to catcher's cpoint
    // x = catcher.x + (cpoint.x - centerx) = 200 + (65 - 40) = 225
    assert(victim.x == 225);
    assert(victim.y == 0);
    assert(victim.z == 150);
    assert(victim.facing == FACING_LEFT);
    assert(victim.fall == 0);

    std::cout << "    Grapple initiation and anchor synchronization verified!" << std::endl;
}

void test_grapple_throw_execution()
{
    std::cout << "[+] Testing Grapple Throw Execution & Launch Arc..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t catcher_file;
    std::memset(&catcher_file, 0, sizeof(catcher_file));
    frame_t& throw_frame = catcher_file.frames[125];
    throw_frame.state = STATE_CATCHING;
    throw_frame.centerx = 40;
    throw_frame.centery = 40;
    throw_frame.cpoint.kind = 1;
    throw_frame.cpoint.throwv_x = 15;
    throw_frame.cpoint.throwv_y = -9;
    throw_frame.cpoint.throw_injury = 40;

    file_t victim_file;
    std::memset(&victim_file, 0, sizeof(victim_file));

    object_t catcher;
    object_init(&catcher);
    catcher.file = &catcher_file;
    catcher.frame_id1 = 125;
    catcher.frame_id4 = 125;
    catcher.x = 200;
    catcher.y = 0;
    catcher.z = 150;
    catcher.facing = FACING_RIGHT;

    object_t victim;
    object_init(&victim);
    victim.file = &victim_file;
    victim.frame_id1 = 230;
    victim.frame_id4 = 230;
    victim.x = 225;
    victim.y = 0;
    victim.z = 150;

    world.objects[0] = &catcher;
    world.is_object_exists[0] = 1;
    world.objects[1] = &victim;
    world.is_object_exists[1] = 1;

    catcher.cpoint_catcher = 1;
    victim.cpoint_timer = 0;

    // Trigger throw sync
    process_grapple_sync(&world, 0);

    // Verify throw launch parameters
    assert(victim.x_velocity == 15.0);
    assert(victim.y_velocity == -9.0);
    assert(victim.fall == 80);        // Knockdown
    assert(victim.frame_id1 == 180);  // Falling frame
    assert(victim.hp == 500 - 40);
    assert(catcher.total_attack == 40);

    // Verify grapple link severed
    assert(catcher.cpoint_catcher == 0);

    std::cout << "    Throw launch velocities, knockdown (fall 80), and injury verified!" << std::endl;
}

void test_weapon_pickup_and_sync()
{
    std::cout << "[+] Testing Weapon Pickup & wpoint Synchronization (0x00408CE0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    char_file.id = DAVIS_DAT;
    char_file.type = TYPE_CHARACTER;
    frame_t& swing_frame = char_file.frames[65]; // Weapon swing frame
    swing_frame.state = STATE_ATTACKING;
    swing_frame.centerx = 40;
    swing_frame.centery = 40;
    swing_frame.wpoint.kind = 1;
    swing_frame.wpoint.x = 55;
    swing_frame.wpoint.y = 30;
    swing_frame.wpoint.weaponact = 3; // Swing frame of weapon

    file_t bat_file;
    std::memset(&bat_file, 0, sizeof(bat_file));
    bat_file.id = 100; // Baseball bat
    bat_file.type = TYPE_LIGHT_WEAPON;

    object_t player;
    object_init(&player);
    player.file = &char_file;
    player.frame_id1 = 0;
    player.frame_id4 = 0;
    player.x = 100;
    player.y = 0;
    player.z = 200;
    player.facing = FACING_RIGHT;

    object_t bat;
    object_init(&bat);
    bat.file = &bat_file;
    bat.frame_id1 = 0;
    bat.frame_id4 = 0;
    bat.x = 115;
    bat.y = 0;
    bat.z = 200;
    bat.holder_id = 0; // Dropped on floor

    world.objects[0] = &player;
    world.is_object_exists[0] = 1;
    world.objects[1] = &bat;
    world.is_object_exists[1] = 1;

    // 1. Pickup test
    bool picked = try_pickup_weapon(&world, 0);
    assert(picked == true);
    assert(player.weapon_type == 1);
    assert(player.weapon_id == 1);
    assert(bat.holder_id == 0);
    assert(player.frame_id1 == 115); // Pickup frame

    // 2. Synchronization test
    player.frame_id1 = 65;
    player.frame_id4 = 65;
    process_weapon_sync(&world, 0);

    // Verify bat anchored to hand: x = 100 + (55 - 40) = 115, y = 0 + (30 - 40) = -10
    assert(bat.x == 115);
    assert(bat.y == -10);
    assert(bat.z == 200);
    assert(bat.frame_id1 == 3); // Weapon animation sync

    std::cout << "    Weapon pickup and hand anchor synchronization verified!" << std::endl;
}

void test_weapon_drop_and_throw()
{
    std::cout << "[+] Testing Weapon Drop upon Damage & Weapon Throw..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    file_t bat_file;
    std::memset(&bat_file, 0, sizeof(bat_file));
    bat_file.type = TYPE_LIGHT_WEAPON;

    object_t player;
    object_init(&player);
    player.file = &char_file;
    player.weapon_type = 1;
    player.weapon_id = 1;
    player.x = 100;
    player.facing = FACING_RIGHT;

    object_t bat;
    object_init(&bat);
    bat.file = &bat_file;
    bat.holder_id = 0;
    bat.weapon_type = static_cast<uint32_t>(-1);

    world.objects[0] = &player;
    world.is_object_exists[0] = 1;
    world.objects[1] = &bat;
    world.is_object_exists[1] = 1;

    // 1. Drop test (character knocked down)
    player.fall = 80;
    process_weapon_sync(&world, 0);

    assert(player.weapon_type == 0);
    assert(player.weapon_id == 0);
    assert(bat.holder_id == 0);
    assert(bat.y_velocity == -4.0); // Dropped bounce impulse

    // 2. Throw test
    player.weapon_type = 1;
    player.weapon_id = 1;
    bat.holder_id = 0;
    throw_weapon(&world, 0);

    assert(player.weapon_type == 0);
    assert(bat.holder_id == 0);
    assert(bat.x_velocity == 12.0); // Forward throw
    assert(bat.thrown_injury == 35);

    std::cout << "    Weapon drop upon damage and throw impulse verified!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Grapple, Throw & Weapon Mechanics Tests ===" << std::endl;
    test_grapple_initiate_and_sync();
    test_grapple_throw_execution();
    test_weapon_pickup_and_sync();
    test_weapon_drop_and_throw();
    std::cout << "[SUCCESS] All Grapple, Throw & Weapon Mechanics tests passed with 100% precision!" << std::endl;
    return 0;
}

