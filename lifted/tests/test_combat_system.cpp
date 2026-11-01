#include <iostream>
#include <cassert>
#include <cstring>
#include "core/global.h"
#include "gameplay/entity.h"

using namespace lf2;

void test_attack_damage_and_flinch()
{
    std::cout << "[+] Testing 1:1 combat damage calculation and flinch response (0x0042E100)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t attacker_file;
    std::memset(&attacker_file, 0, sizeof(attacker_file));
    attacker_file.id = DAVIS_DAT;
    attacker_file.type = TYPE_CHARACTER;

    // Attacker punch frame (frame 60) with 1 active itr
    frame_t& a_frame = attacker_file.frames[60];
    a_frame.state = STATE_ATTACKING;
    a_frame.centerx = 40;
    a_frame.centery = 40;
    static itr_t a_itr;
    std::memset(&a_itr, 0, sizeof(a_itr));
    a_itr.x = 10;
    a_itr.y = 10;
    a_itr.w = 50;
    a_itr.h = 50;
    a_itr.injury = 25;
    a_itr.fall = 20;
    a_itr.arest = 10;
    a_itr.dvx = 4;
    a_itr.dvy = 0;
    a_itr.vrest = 10;
    a_frame.itrs_size = 1;
    a_frame.itrs = &a_itr;

    file_t victim_file;
    std::memset(&victim_file, 0, sizeof(victim_file));
    victim_file.id = DENNIS_DAT;
    victim_file.type = TYPE_CHARACTER;

    // Victim standing frame (frame 0) with 1 active bdy
    frame_t& v_frame = victim_file.frames[0];
    v_frame.state = STATE_STANDING;
    v_frame.centerx = 40;
    v_frame.centery = 40;
    static bdy_t v_bdy;
    std::memset(&v_bdy, 0, sizeof(v_bdy));
    v_bdy.x = 10;
    v_bdy.y = 10;
    v_bdy.w = 50;
    v_bdy.h = 60;
    v_frame.bdys_size = 1;
    v_frame.bdys = &v_bdy;

    object_t attacker;
    object_init(&attacker);
    attacker.file = &attacker_file;
    attacker.frame_id1 = 60;
    attacker.frame_id4 = 60;
    attacker.x = 100;
    attacker.y = 0;
    attacker.z = 200;
    attacker.facing = FACING_RIGHT;
    attacker.team = 0;

    object_t victim;
    object_init(&victim);
    victim.file = &victim_file;
    victim.frame_id1 = 0;
    victim.frame_id4 = 0;
    victim.x = 130;
    victim.y = 0;
    victim.z = 200;
    victim.facing = FACING_LEFT;
    victim.team = 1; // Enemy team

    world.objects[0] = &attacker;
    world.is_object_exists[0] = 1;

    world.objects[1] = &victim;
    world.is_object_exists[1] = 1;

    // Execute combat tick
    world.process_all_attacks();

    // Verify victim damage
    assert(victim.hp == 500 - 25);
    assert(victim.hp_lost == 25);
    assert(attacker.total_attack == 25);

    // Verify victim flinch state & knockback
    assert(victim.fall == 20);
    assert(victim.frame_id1 == 222); // Front hurt frame
    assert(victim.x_velocity > 0.0);  // Knocked rightwards away from attacker
    assert(victim.vrest_of_objects[0] == 10); // Protected against multi-hits for 10 ticks

    std::cout << "    Damage (25 HP), front flinch frame 222, and vrest protection verified!" << std::endl;
}

void test_knockdown_fall_state()
{
    std::cout << "[+] Testing knockdown fall state and airborne arc (fall >= 60)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t attacker_file;
    std::memset(&attacker_file, 0, sizeof(attacker_file));
    frame_t& a_frame = attacker_file.frames[70]; // Super punch frame
    a_frame.state = STATE_ATTACKING;
    a_frame.centerx = 40;
    a_frame.centery = 40;
    static itr_t a_itr;
    std::memset(&a_itr, 0, sizeof(a_itr));
    a_itr.x = 10;
    a_itr.y = 10;
    a_itr.w = 50;
    a_itr.h = 50;
    a_itr.injury = 60;
    a_itr.fall = 70; // Guaranteed knockdown (>60)
    a_itr.arest = 15;
    a_itr.dvx = 8;
    a_itr.dvy = -9;
    a_frame.itrs_size = 1;
    a_frame.itrs = &a_itr;

    file_t victim_file;
    std::memset(&victim_file, 0, sizeof(victim_file));
    frame_t& v_frame = victim_file.frames[0];
    v_frame.state = STATE_STANDING;
    v_frame.centerx = 40;
    v_frame.centery = 40;
    static bdy_t v_bdy;
    std::memset(&v_bdy, 0, sizeof(v_bdy));
    v_bdy.x = 10;
    v_bdy.y = 10;
    v_bdy.w = 50;
    v_bdy.h = 60;
    v_frame.bdys_size = 1;
    v_frame.bdys = &v_bdy;

    object_t attacker;
    object_init(&attacker);
    attacker.file = &attacker_file;
    attacker.frame_id1 = 70;
    attacker.frame_id4 = 70;
    attacker.x = 100;
    attacker.y = 0;
    attacker.z = 200;
    attacker.facing = FACING_RIGHT;
    attacker.team = 0;

    object_t victim;
    object_init(&victim);
    victim.file = &victim_file;
    victim.frame_id1 = 0;
    victim.frame_id4 = 0;
    victim.x = 120;
    victim.y = 0;
    victim.z = 200;
    victim.facing = FACING_LEFT;
    victim.team = 1;

    world.objects[0] = &attacker;
    world.is_object_exists[0] = 1;

    world.objects[1] = &victim;
    world.is_object_exists[1] = 1;

    world.process_all_attacks();

    // Verify knockdown
    assert(victim.fall == 80); // Knockdown flag
    assert(victim.frame_id1 == 180); // Falling frame
    assert(victim.y_velocity < 0.0); // Airborne upward launch
    assert(victim.x_velocity == 8.0); // Backward knockback

    std::cout << "    Knockdown fall state 80, falling frame 180, and trajectory verified!" << std::endl;
}

void test_projectile_spawning()
{
    std::cout << "[+] Testing projectile instantiation into world object table..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t ball_file;
    std::memset(&ball_file, 0, sizeof(ball_file));
    ball_file.id = DAVIS_BALL_DAT;
    ball_file.type = TYPE_ATTACK;

    world.files[0] = &ball_file;

    int32_t slot = world.spawn_projectile(0, DAVIS_BALL_DAT, 150, -20, 200, 10.0, 0.0, FACING_RIGHT);
    assert(slot >= 10);
    assert(world.is_object_exists[slot] == 1);

    object_t* ball = world.objects[slot];
    assert(ball != nullptr);
    assert(ball->file == &ball_file);
    assert(ball->x == 150);
    assert(ball->y == -20);
    assert(ball->z == 200);
    assert(ball->x_velocity == 10.0);
    assert(ball->owner == 0);

    // Clean up allocated slot
    delete ball;
    world.objects[slot] = nullptr;

    std::cout << "    Projectile spawned cleanly into slot " << slot << " with correct velocity!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Combat Engine & Action Dispatcher Tests ===" << std::endl;
    test_attack_damage_and_flinch();
    test_knockdown_fall_state();
    test_projectile_spawning();
    std::cout << "[SUCCESS] All Combat Engine & Action Dispatcher tests passed with 100% precision!" << std::endl;
    return 0;
}
