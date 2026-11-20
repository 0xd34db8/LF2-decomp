#include <iostream>
#include <cassert>
#include <cstring>
#include <memory>
#include "core/global.h"
#include "gameplay/entity.h"

using namespace lf2;

void test_attack_damage_and_flinch()
{
    std::cout << "[+] Testing 1:1 combat damage, dark_hp (-dmg/3), 4 fall tiers & sparks (0x0042E100)..." << std::endl;
    global_t world{};

    auto attacker_file = std::make_unique<file_t>();
    attacker_file->id = DAVIS_DAT;
    attacker_file->type = TYPE_CHARACTER;

    frame_t& a_frame = attacker_file->frames[60];
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

    auto victim_file = std::make_unique<file_t>();
    victim_file->id = DENNIS_DAT;
    victim_file->type = TYPE_CHARACTER;

    frame_t& v_frame = victim_file->frames[0];
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

    victim_file->frames[220].bdys_size = 1;
    victim_file->frames[220].bdys = &v_bdy;
    victim_file->frames[220].centerx = 40;
    victim_file->frames[220].centery = 40;
    victim_file->frames[222].bdys_size = 1;
    victim_file->frames[222].bdys = &v_bdy;
    victim_file->frames[222].centerx = 40;
    victim_file->frames[222].centery = 40;

    object_t attacker, victim;
    object_init(&attacker);
    attacker.file = attacker_file.get();
    attacker.frame_id1 = 60;
    attacker.frame_id4 = 60;
    attacker.x = 100;
    attacker.z = 200;
    attacker.facing = FACING_RIGHT;
    attacker.team = 0;

    object_init(&victim);
    victim.file = victim_file.get();
    victim.frame_id1 = 0;
    victim.frame_id4 = 0;
    victim.x = 130;
    victim.z = 200;
    victim.facing = FACING_LEFT;
    victim.team = 1;

    world.objects[0] = &attacker; world.is_object_exists[0] = 1;
    world.objects[1] = &victim;   world.is_object_exists[1] = 1;

    world.process_all_attacks();

    // Hit 1: fall = 20 -> frame 220, dark_hp = 500 - 25/3 = 492
    assert(victim.hp == 475);
    assert(victim.dark_hp == 492);
    assert(victim.hp_lost == 25);
    assert(attacker.total_attack == 25);
    assert(victim.fall == 20);
    assert(victim.frame_id1 == 220);
    assert(victim.pic_x_gain == 4.0);
    assert(victim.attacks == 1);
    assert(victim.shaking == -3);
    assert(attacker.shaking == 3);
    assert(victim.vrest_of_objects[0] == 10);
    assert(victim.spark_count == 1);

    victim.shaking = 0;
    world_average_velocities(&world);
    assert(victim.x_velocity == 4.0);
    assert(victim.attacks == 0 && victim.pic_x_gain == 0.0);

    // Hit 2: fall = 20 + 20 -> 40 -> frame 222 (front hurt)
    victim.vrest_of_objects[0] = 0;
    attacker.arest = 0;
    world.process_all_attacks();
    assert(victim.fall == 40);
    assert(victim.frame_id1 == 222);

    // Hit 3: fall = 40 + 20 -> 60 -> frame 226 (heavy stagger)
    victim.vrest_of_objects[0] = 0;
    attacker.arest = 0;
    world.process_all_attacks();
    assert(victim.fall == 60);
    assert(victim.frame_id1 == 226);

    std::cout << "    Damage (25 HP), dark_hp (-dmg/3), fall tiers 220/222/226 & impulse averaging verified!" << std::endl;
}

void test_knockdown_fall_state()
{
    std::cout << "[+] Testing knockdown arc & fall=0 reset after 80 (0x0042E100)..." << std::endl;
    global_t world{};

    auto attacker_file = std::make_unique<file_t>();
    frame_t& a_frame = attacker_file->frames[70];
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
    a_itr.fall = 70;
    a_itr.arest = 15;
    a_itr.dvx = 8;
    a_itr.dvy = -9;
    a_frame.itrs_size = 1;
    a_frame.itrs = &a_itr;

    auto victim_file = std::make_unique<file_t>();
    frame_t& v_frame = victim_file->frames[0];
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

    object_t attacker, victim;
    object_init(&attacker);
    attacker.file = attacker_file.get();
    attacker.frame_id1 = 70;
    attacker.frame_id4 = 70;
    attacker.x = 100;
    attacker.z = 200;
    attacker.facing = FACING_RIGHT;
    attacker.team = 0;

    object_init(&victim);
    victim.file = victim_file.get();
    victim.frame_id1 = 0;
    victim.frame_id4 = 0;
    victim.x = 120;
    victim.z = 200;
    victim.facing = FACING_LEFT;
    victim.team = 1;

    world.objects[0] = &attacker; world.is_object_exists[0] = 1;
    world.objects[1] = &victim;   world.is_object_exists[1] = 1;

    world.process_all_attacks();

    // Knockdown resets fall to 0 after queuing 180 and accumulates impulse into pic_x_gain/y_accl
    assert(victim.fall == 0);
    assert(victim.frame_id1 == 180);
    assert(victim.pic_x_gain == 8.0);
    assert(victim.y_accl == -9.0);
    assert(victim.attacks == 1);

    victim.shaking = 0;
    world_average_velocities(&world);
    assert(victim.x_velocity == 8.0);
    assert(victim.y_velocity == -9.0);

    std::cout << "    Knockdown frame 180, fall reset, and velocity averaging verified!" << std::endl;
}

void test_projectile_spawning()
{
    std::cout << "[+] Testing projectile instantiation into world object table..." << std::endl;
    global_t world{};

    auto ball_file = std::make_unique<file_t>();
    ball_file->id = DAVIS_BALL_DAT;
    ball_file->type = TYPE_ATTACK;
    world.files[0] = ball_file.get();

    int32_t slot = world.spawn_projectile(0, DAVIS_BALL_DAT, 150, -20, 200, 10.0, 0.0, FACING_RIGHT);
    assert(slot >= 10);
    assert(world.is_object_exists[slot] == 1);

    object_t* ball = world.objects[slot];
    assert(ball != nullptr);
    assert(ball->file == ball_file.get());
    assert(ball->x == 150 && ball->y == -20 && ball->z == 200);
    assert(ball->x_velocity == 10.0);
    assert(ball->owner == 0);

    delete ball;
    world.objects[slot] = nullptr;

    std::cout << "    Projectile spawned cleanly into slot " << slot << " with correct velocity!" << std::endl;
}

void test_defend_and_armor()
{
    std::cout << "[+] Testing Defend (1/10 dmg, 111/112) & Knight Armor (0x0042E100)..." << std::endl;
    global_t world{};

    auto att_file = std::make_unique<file_t>();
    att_file->id = DAVIS_DAT;
    att_file->type = TYPE_CHARACTER;
    static itr_t phys_itr{};
    phys_itr.kind = ITR_NORMAL_ATTACK;
    phys_itr.x = 0; phys_itr.y = 0; phys_itr.w = 80; phys_itr.h = 80;
    phys_itr.injury = 50; phys_itr.bdefend = 20; phys_itr.dvx = 6; phys_itr.vrest = 5;
    att_file->frames[60].state = STATE_ATTACKING;
    att_file->frames[60].itrs_size = 1;
    att_file->frames[60].itrs = &phys_itr;

    static itr_t fire_itr = phys_itr;
    fire_itr.effect = EFFECT_FIRE;
    att_file->frames[61].state = STATE_ATTACKING;
    att_file->frames[61].itrs_size = 1;
    att_file->frames[61].itrs = &fire_itr;

    auto vic_file = std::make_unique<file_t>();
    vic_file->id = DENNIS_DAT;
    vic_file->type = TYPE_CHARACTER;
    static bdy_t bdy{};
    bdy.x = 0; bdy.y = 0; bdy.w = 80; bdy.h = 80;
    vic_file->frames[110].state = STATE_DEFEND;
    vic_file->frames[110].bdys_size = 1;
    vic_file->frames[110].bdys = &bdy;
    vic_file->frames[111].state = STATE_DEFEND;
    vic_file->frames[111].bdys_size = 1;
    vic_file->frames[111].bdys = &bdy;

    object_t att, vic;
    object_init(&att);
    object_init(&vic);
    att.file = att_file.get(); att.frame_id1 = 60; att.x = 100; att.z = 200; att.facing = FACING_RIGHT; att.team = 0;
    vic.file = vic_file.get(); vic.frame_id1 = 110; vic.x = 110; vic.z = 200; vic.facing = FACING_LEFT;  vic.team = 1;

    world.objects[0] = &att; world.is_object_exists[0] = 1;
    world.objects[1] = &vic; world.is_object_exists[1] = 1;

    world.process_all_attacks();
    assert(vic.hp == 495); // 50 / 10 = 5
    assert(vic.dark_hp == 499);
    assert(vic.bdefend == 20);
    assert(vic.frame_id1 == 111);
    assert(vic.pic_x_gain == 3.0);

    vic.vrest_of_objects[0] = 0;
    att.arest = 0;
    world.process_all_attacks();
    assert(vic.bdefend == 40);
    assert(vic.frame_id1 == 112);

    // Knight armor (id 37): blocks physical at 1/10th, burned by FIRE
    auto knight_file = std::make_unique<file_t>();
    knight_file->id = KNIGHT_DAT;
    knight_file->type = TYPE_CHARACTER;
    knight_file->frames[0].state = STATE_STANDING;
    knight_file->frames[0].bdys_size = 1;
    knight_file->frames[0].bdys = &bdy;

    object_init(&vic);
    vic.file = knight_file.get();
    vic.frame_id1 = 0;
    vic.x = 110; vic.z = 200; vic.facing = FACING_LEFT; vic.team = 1;
    att.arest = 0;
    world.process_all_attacks();
    assert(vic.hp == 495); // Armor blocked physical

    vic.vrest_of_objects[0] = 0;
    att.arest = 0;
    att.frame_id1 = 61; // EFFECT_FIRE bypasses Knight armor
    world.process_all_attacks();
    assert(vic.hp == 445);
    assert(vic.frame_id1 == 203);

    std::cout << "    Defend 1/10th damage, guard break 112, and Knight armor verified!" << std::endl;
}

void test_weapon_strength_pickup_and_catch_itrs()
{
    std::cout << "[+] Testing ITR kinds 2 (pickup), 3 (catch), and 5 (weapon_strength)..." << std::endl;
    global_t world{};

    static bdy_t bdy{};
    bdy.x = 0; bdy.y = 0; bdy.w = 80; bdy.h = 80;

    auto fighter_file = std::make_unique<file_t>();
    fighter_file->id = DAVIS_DAT;
    fighter_file->type = TYPE_CHARACTER;
    fighter_file->frames[0].bdys_size = 1;
    fighter_file->frames[0].bdys = &bdy;
    fighter_file->frames[20].wpoint.attacking = 1;

    static itr_t pickup_itr{};
    pickup_itr.kind = ITR_PICK_UP_WEAPON;
    pickup_itr.x = 0; pickup_itr.y = 0; pickup_itr.w = 80; pickup_itr.h = 80;
    fighter_file->frames[10].state = 1004;
    fighter_file->frames[10].itrs_size = 1;
    fighter_file->frames[10].itrs = &pickup_itr;

    static itr_t catch_itr{};
    catch_itr.kind = ITR_CATCH;
    catch_itr.x = 0; catch_itr.y = 0; catch_itr.w = 80; catch_itr.h = 80;
    catch_itr.catching_act_1 = 120;
    catch_itr.caught_act_1 = 230;
    fighter_file->frames[11].state = STATE_ATTACKING;
    fighter_file->frames[11].itrs_size = 1;
    fighter_file->frames[11].itrs = &catch_itr;

    auto bat_file = std::make_unique<file_t>();
    bat_file->id = STICK_DAT;
    bat_file->type = TYPE_LIGHT_WEAPON;
    bat_file->frames[0].state = 1004;
    bat_file->frames[0].bdys_size = 1;
    bat_file->frames[0].bdys = &bdy;
    static itr_t ws_itr{};
    ws_itr.kind = ITR_WEAPON_STRENGTH;
    ws_itr.x = 0; ws_itr.y = 0; ws_itr.w = 80; ws_itr.h = 80;
    bat_file->frames[5].state = STATE_ATTACKING;
    bat_file->frames[5].itrs_size = 1;
    bat_file->frames[5].itrs = &ws_itr;
    bat_file->attacking_itrs[1].injury = 65;
    bat_file->attacking_itrs[1].dvx = 9;
    bat_file->attacking_itrs[1].fall = 30;
    bat_file->attacking_itrs[1].vrest = 8;

    object_t att, vic, bat;
    object_init(&att);
    object_init(&vic);
    object_init(&bat);

    att.file = fighter_file.get(); att.x = 100; att.z = 200; att.team = 0;
    vic.file = fighter_file.get(); vic.x = 110; vic.z = 200; vic.team = 1;
    bat.file = bat_file.get();     bat.x = 100; bat.z = 200;

    world.objects[0] = &att; world.is_object_exists[0] = 1;
    world.objects[1] = &vic; world.is_object_exists[1] = 1;
    world.objects[2] = &bat; world.is_object_exists[2] = 1;

    // 1. ITR_PICK_UP_WEAPON (kind 2)
    att.frame_id1 = 10;
    att.click_attack = 1;
    att.holding_attack = 0;
    world.process_all_attacks();
    assert(att.frame_id1 == 115);
    assert(att.weapon_type == 1 && bat.weapon_type == -1);
    assert(att.weapon_id == 2 && bat.holder_id == 0);

    // 2. ITR_WEAPON_STRENGTH (kind 5 -> bat->attacking_itrs[1])
    att.frame_id1 = 20; // wpoint.attacking = 1
    bat.frame_id1 = 5;
    att.click_attack = 0;
    world.process_all_attacks();
    assert(vic.hp == 435);
    assert(vic.fall == 40);

    // 3. ITR_CATCH (kind 3)
    att.weapon_type = 0;
    bat.weapon_type = 0;
    att.frame_id1 = 11;
    att.arest = 0;
    vic.frame_id1 = 0;
    vic.vrest_of_objects[0] = 0;
    world.process_all_attacks();
    assert(att.cpoint_catcher == 1);
    assert(vic.cpoint_caught == 0);
    assert(att.cpoint_hold_timer == 300);
    assert(att.frame_id1 == 120 && vic.frame_id1 == 230);

    std::cout << "    ITR kinds 2, 3, and 5 resolved identically to binary!" << std::endl;
}

void test_special_itrs_and_criminal_rescue()
{
    std::cout << "[+] Testing ITR kinds 8, 9, 14, 15, 16 & Criminal Hostage Rescue..." << std::endl;
    global_t world{};

    static bdy_t bdy{};
    bdy.x = 0; bdy.y = 0; bdy.w = 80; bdy.h = 80;

    auto att_file = std::make_unique<file_t>();
    auto vic_file = std::make_unique<file_t>();
    att_file->id = JAN_DAT; att_file->type = TYPE_ATTACK;
    vic_file->id = DENNIS_DAT; vic_file->type = TYPE_CHARACTER;
    vic_file->frames[0].state = STATE_STANDING;
    vic_file->frames[0].bdys_size = 1;
    vic_file->frames[0].bdys = &bdy;

    static itr_t sp_itr{};
    sp_itr.x = 0; sp_itr.y = 0; sp_itr.w = 80; sp_itr.h = 80;

    att_file->frames[0].itrs_size = 1;
    att_file->frames[0].itrs = &sp_itr;

    object_t att, vic;
    object_init(&att);
    object_init(&vic);
    att.file = att_file.get(); att.x = 130; att.z = 200; att.team = 1; att.owner = 0;
    vic.file = vic_file.get(); vic.x = 100; vic.z = 200; vic.team = 2;

    world.objects[0] = &att; world.is_object_exists[0] = 1;
    world.objects[1] = &vic; world.is_object_exists[1] = 1;

    // 1. ITR_HEAL (kind 8)
    sp_itr.kind = ITR_HEAL;
    sp_itr.injury = 150;
    sp_itr.dvx = 12;
    world.process_all_attacks();
    assert(vic.curing_hp == 1150);
    assert(att.frame_id1 == 12);
    att.frame_id1 = 0;

    // 2. ITR_FORCEFIELD (kind 9) reflects enemy projectile
    auto proj_file = std::make_unique<file_t>();
    proj_file->id = DENNIS_BALL_DAT;
    proj_file->type = TYPE_ATTACK;
    proj_file->frames[0].state = 3000;
    proj_file->frames[0].bdys_size = 1;
    proj_file->frames[0].bdys = &bdy;

    object_t proj;
    object_init(&proj);
    proj.file = proj_file.get();
    proj.x = 130; proj.z = 200; proj.team = 2; proj.x_velocity = 8.0;
    world.objects[1] = &proj;
    sp_itr.kind = ITR_FORCEFIELD;
    world.process_all_attacks();
    assert(proj.team == 1 && proj.frame_id1 == 30 && proj.flag_eb == 1 && proj.x_velocity == 0.0);

    // 3. ITR_FREEZE (kind 14) obstacle blocking
    world.objects[1] = &vic;
    att.arest = 0;
    vic.vrest_of_objects[0] = 0;
    vic.x_velocity = 5.0;
    sp_itr.kind = ITR_FREEZE;
    world.process_all_attacks();
    assert(vic.blocked_right == 1);

    // 4. ITR_WHIRLWIND_ICE (kind 15) pull + lift
    att.arest = 0;
    vic.vrest_of_objects[0] = 0;
    vic.y_velocity = 0.0;
    sp_itr.kind = ITR_WHIRLWIND_ICE;
    world.process_all_attacks();
    assert(vic.frame_id1 == 182 && vic.y_velocity < 0.0 && vic.x_velocity > 5.0);

    // 5. ITR_WHIRLWIND_WIND (kind 16) freeze + damage
    att.arest = 0;
    vic.vrest_of_objects[0] = 0;
    vic.frame_id1 = 0;
    sp_itr.kind = ITR_WHIRLWIND_WIND;
    sp_itr.injury = 40;
    world.process_all_attacks();
    assert(vic.frame_id1 == 200 && vic.hp == 460);

    // 6. Criminal hostage rescue (id 300, bdy.kind 1050)
    auto crim_file = std::make_unique<file_t>();
    crim_file->id = CRIMINAL_DAT;
    crim_file->type = TYPE_CHARACTER;
    static bdy_t hostage_bdy = bdy;
    hostage_bdy.kind = 1050;
    crim_file->frames[0].bdys_size = 1;
    crim_file->frames[0].bdys = &hostage_bdy;

    object_t crim;
    object_init(&crim);
    crim.file = crim_file.get();
    crim.x = 130; crim.z = 200; crim.team = 5;
    att_file->type = TYPE_CHARACTER;
    sp_itr.kind = ITR_NORMAL_ATTACK;
    world.objects[1] = &crim;
    world.process_all_attacks();
    assert(crim.team == 1 && crim.frame_id1 == 50 && crim.hp == 500);

    std::cout << "    ITR kinds 8, 9, 14, 15, 16 & Criminal hostage rescue verified!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Combat Engine & Action Dispatcher Tests ===" << std::endl;
    test_attack_damage_and_flinch();
    test_knockdown_fall_state();
    test_projectile_spawning();
    test_defend_and_armor();
    test_weapon_strength_pickup_and_catch_itrs();
    test_special_itrs_and_criminal_rescue();
    std::cout << "[SUCCESS] All Combat Engine & Action Dispatcher tests passed with 100% precision!" << std::endl;
    return 0;
}
