#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <memory>
#include "core/global.h"
#include "gameplay/entity.h"
#include "gameplay/grapple.h"
#include "gameplay/weapon.h"

using namespace lf2;

void test_grapple_initiate_and_sync()
{
    std::cout << "[+] Testing Grapple Catch Initiation & Anchor Sync (0x004187B0)..." << std::endl;
    global_t world{};

    auto catcher_file = std::make_unique<file_t>();
    catcher_file->id = DAVIS_DAT;
    catcher_file->type = TYPE_CHARACTER;

    frame_t& c_frame = catcher_file->frames[120];
    c_frame.state = STATE_CATCHING;
    c_frame.centerx = 40;
    c_frame.centery = 40;
    c_frame.cpoint.kind = 1;
    c_frame.cpoint.x = 65;
    c_frame.cpoint.y = 40;
    c_frame.cpoint.v_action = 230;

    auto victim_file = std::make_unique<file_t>();
    victim_file->id = DENNIS_DAT;
    victim_file->type = TYPE_CHARACTER;
    frame_t& v_frame = victim_file->frames[230];
    v_frame.state = STATE_PICKED_CAUGHT;
    v_frame.centerx = 40;
    v_frame.centery = 40;
    v_frame.cpoint.kind = 2;
    v_frame.cpoint.x = 40;
    v_frame.cpoint.y = 40;

    object_t catcher;
    object_init(&catcher);
    catcher.file = catcher_file.get();
    catcher.frame_id1 = 120;
    catcher.frame_id4 = 120;
    catcher.x = 200;
    catcher.y = 0;
    catcher.z = 150;
    catcher.facing = FACING_RIGHT;

    object_t victim;
    object_init(&victim);
    victim.file = victim_file.get();
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
    assert(victim.cpoint_caught == 0);
    assert(catcher.cpoint_hold_timer == 300);
    assert(victim.frame_id1 == 230);

    process_grapple_sync(&world, 0);

    // cover == 0 -> victim.z = catcher.z - 1 = 149, victim.y = +1
    assert(victim.x == 225);
    assert(victim.y == 1);
    assert(victim.z == 149);
    assert(victim.facing == FACING_LEFT);
    assert(victim.fall == 0);

    std::cout << "    Grapple initiation and dual-anchor synchronization verified!" << std::endl;
}

void test_grapple_throw_execution()
{
    std::cout << "[+] Testing Grapple Throw Execution & Launch Arc (0x00418C30)..." << std::endl;
    global_t world{};

    auto catcher_file = std::make_unique<file_t>();
    frame_t& throw_frame = catcher_file->frames[125];
    throw_frame.state = STATE_CATCHING;
    throw_frame.centerx = 40;
    throw_frame.centery = 40;
    throw_frame.next = 0;
    throw_frame.cpoint.kind = 1;
    throw_frame.cpoint.x = 65;
    throw_frame.cpoint.y = 30;
    throw_frame.cpoint.v_action = 180;
    throw_frame.cpoint.throwv_x = 15;
    throw_frame.cpoint.throwv_y = -9;
    throw_frame.cpoint.throw_injury = 40;

    auto victim_file = std::make_unique<file_t>();
    victim_file->frames[230].cpoint.kind = 2;

    object_t catcher;
    object_init(&catcher);
    catcher.file = catcher_file.get();
    catcher.frame_id1 = 125;
    catcher.frame_id4 = 125;
    catcher.x = 200;
    catcher.y = 0;
    catcher.z = 150;
    catcher.facing = FACING_RIGHT;

    object_t victim;
    object_init(&victim);
    victim.file = victim_file.get();
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
    victim.cpoint_caught = 0;

    process_grapple_sync(&world, 0);

    assert(victim.x_velocity == 15.0);
    assert(victim.y_velocity == -9.0);
    assert(victim.thrown_injury == 40);
    assert(victim.frame_id1 == 180);
    assert(catcher.frame_id1 == 0);
    assert(catcher.wait_counter == 0);

    std::cout << "    Throw launch velocities, thrown_injury, and frame advance verified!" << std::endl;
}

void test_weapon_pickup_and_sync()
{
    std::cout << "[+] Testing Weapon Pickup & Dual-Anchor wpoint Sync (0x00417F80)..." << std::endl;
    global_t world{};

    auto char_file = std::make_unique<file_t>();
    char_file->id = DAVIS_DAT;
    char_file->type = TYPE_CHARACTER;
    frame_t& swing_frame = char_file->frames[65];
    swing_frame.state = STATE_ATTACKING;
    swing_frame.centerx = 40;
    swing_frame.centery = 40;
    swing_frame.wpoint.kind = 1;
    swing_frame.wpoint.x = 55;
    swing_frame.wpoint.y = 30;
    swing_frame.wpoint.weaponact = 3;

    auto bat_file = std::make_unique<file_t>();
    bat_file->id = STICK_DAT;
    bat_file->type = TYPE_LIGHT_WEAPON;
    bat_file->frames[3].centerx = 20;
    bat_file->frames[3].centery = 20;
    bat_file->frames[3].wpoint.x = 20;
    bat_file->frames[3].wpoint.y = 20;

    object_t player;
    object_init(&player);
    player.file = char_file.get();
    player.x = 100;
    player.y = 0;
    player.z = 200;
    player.facing = FACING_RIGHT;

    object_t bat;
    object_init(&bat);
    bat.file = bat_file.get();
    bat.x = 115;
    bat.y = 0;
    bat.z = 200;

    world.objects[0] = &player;
    world.is_object_exists[0] = 1;
    world.objects[1] = &bat;
    world.is_object_exists[1] = 1;

    bool picked = try_pickup_weapon(&world, 0);
    assert(picked == true);
    assert(player.weapon_type == 1);
    assert(bat.weapon_type == -1);
    assert(player.weapon_id == 1);
    assert(bat.holder_id == 0);
    assert(player.frame_id1 == 115);

    player.frame_id1 = 65;
    player.frame_id4 = 65;
    process_weapon_sync(&world, 0);

    // cover == 0 -> z + 1 (201), y - 1 (-11)
    assert(bat.x == 115);
    assert(bat.y == -11);
    assert(bat.z == 201);
    assert(bat.frame_id1 == 3);

    std::cout << "    Weapon pickup and dual-anchor wpoint synchronization verified!" << std::endl;
}

void test_weapon_drop_and_throw()
{
    std::cout << "[+] Testing Weapon Drop on STATE_FALLING & wp.dvx Throw (0x00417F80)..." << std::endl;
    global_t world{};

    auto char_file = std::make_unique<file_t>();
    char_file->type = TYPE_CHARACTER;
    char_file->frames[12].state = STATE_FALLING;
    char_file->frames[13].state = STATE_ATTACKING;
    char_file->frames[13].wpoint.kind = 1;
    char_file->frames[13].wpoint.weaponact = 3;
    char_file->frames[13].wpoint.dvx = 12;
    char_file->frames[13].wpoint.dvy = -3;
    char_file->frames[13].wpoint.dvz = 2;

    auto bat_file = std::make_unique<file_t>();
    bat_file->id = STICK_DAT;
    bat_file->type = TYPE_LIGHT_WEAPON;

    object_t player;
    object_init(&player);
    player.file = char_file.get();
    player.weapon_type = 1;
    player.weapon_id = 1;
    player.x = 100;
    player.y = 40;
    player.x_velocity = 9.0;
    player.y_velocity = -4.0;
    player.facing = FACING_RIGHT;
    player.frame_id1 = 12;

    object_t bat;
    object_init(&bat);
    bat.file = bat_file.get();
    bat.holder_id = 0;
    bat.weapon_type = -1;

    world.objects[0] = &player;
    world.is_object_exists[0] = 1;
    world.objects[1] = &bat;
    world.is_object_exists[1] = 1;

    process_weapon_sync(&world, 0);

    assert(player.weapon_type == 0);
    assert(bat.weapon_type == 0);
    assert(bat.x_velocity == 3.0);
    assert(bat.y_velocity == -4.0);
    assert(bat.y_position == -2.0);

    player.y = 0;
    player.weapon_type = 1;
    bat.weapon_type = -1;
    player.frame_id1 = 13;
    player.click_up = 1;
    player.click_down = 0;
    process_weapon_sync(&world, 0);

    assert(player.weapon_type == 0);
    assert(bat.weapon_type == 0);
    assert(bat.frame_id1 == 40);
    assert(bat.x_velocity == 12.0);
    assert(bat.y_velocity == -3.0);
    assert(bat.z_velocity == -2.0);
    assert(bat.weapon_throw_injury == 0);

    std::cout << "    Falling weapon drop (-2.0 clamp) and throw impulse verified!" << std::endl;
}

void test_milk_and_beer_drinking()
{
    std::cout << "[+] Testing Milk & Beer Drinking and Empty Bottle Toss (0x00417F80)..." << std::endl;
    global_t world{};

    auto char_file = std::make_unique<file_t>();
    char_file->type = TYPE_CHARACTER;
    char_file->frames[10].state = STATE_DRINKING;
    char_file->frames[10].wpoint.kind = 1;
    char_file->frames[10].wpoint.weaponact = 2;

    auto milk_file = std::make_unique<file_t>();
    milk_file->id = MILK_DAT;
    milk_file->type = TYPE_DRINK;

    auto beer_file = std::make_unique<file_t>();
    beer_file->id = BEER_DAT;
    beer_file->type = TYPE_DRINK;

    object_t holder, milk, beer;
    object_init(&holder);
    object_init(&milk);
    object_init(&beer);

    holder.file = char_file.get();
    holder.hp = 400;
    holder.dark_hp = 450;
    holder.max_hp = 500;
    holder.mp = 100;
    holder.frame_id1 = 10;
    holder.weapon_type = 6;
    holder.weapon_id = 1;

    milk.file = milk_file.get();
    milk.weapon_type = -6;
    milk.holder_id = 0;
    milk.hp = 11;

    world.objects[0] = &holder; world.is_object_exists[0] = 1;
    world.objects[1] = &milk;   world.is_object_exists[1] = 1;

    world_process_weapons(&world);
    assert(milk.hp == 10);
    assert(holder.dark_hp == 452);
    assert(holder.hp == 404);

    milk.hp = 1;
    world_process_weapons(&world);
    assert(milk.hp == 0);
    assert(holder.weapon_type == 0 && milk.weapon_type == 0);
    assert(holder.weapon_id == 0 && milk.holder_id == 0);
    assert(holder.frame_id1 == 0 && milk.weapon_hp == 0);
    assert(milk.y_velocity == -8.0);
    world.is_object_exists[1] = 0;

    beer.file = beer_file.get();
    beer.weapon_type = -6;
    beer.holder_id = 0;
    beer.hp = 2;
    world.objects[2] = &beer; world.is_object_exists[2] = 1;

    holder.weapon_type = 6;
    holder.weapon_id = 2;
    holder.frame_id1 = 10;
    holder.mp = 499;
    world_process_weapons(&world);
    assert(holder.mp == 500);
    assert(beer.hp == 0);
    assert(beer.y_velocity == -8.0);
    assert(holder.weapon_type == 0 && beer.weapon_type == 0);

    std::cout << "    Milk & Beer drinking effects and empty bottle toss verified!" << std::endl;
}

void test_wpoint_kind3_drop_and_holder_validation()
{
    std::cout << "[+] Testing wp.kind == 3 Drop (/ 5.0 Z-vel) & Holder Validation..." << std::endl;
    global_t world{};

    auto char_file = std::make_unique<file_t>();
    char_file->type = TYPE_CHARACTER;
    char_file->frames[14].state = STATE_STANDING;
    char_file->frames[14].wpoint.kind = 3;

    auto bat_file = std::make_unique<file_t>();
    bat_file->id = STICK_DAT;
    bat_file->type = TYPE_LIGHT_WEAPON;

    object_t holder, bat;
    object_init(&holder);
    object_init(&bat);
    holder.file = char_file.get();
    holder.weapon_type = 1;
    holder.weapon_id = 1;
    holder.frame_id1 = 14;
    bat.file = bat_file.get();
    bat.weapon_type = -1;
    bat.holder_id = 0;

    world.objects[0] = &holder; world.is_object_exists[0] = 1;
    world.objects[1] = &bat;    world.is_object_exists[1] = 1;

    world_process_weapons(&world);
    assert(holder.weapon_type == 0 && bat.weapon_type == 0);
    assert(std::fabs(bat.z_velocity) <= 0.4 + 1e-9);

    holder.weapon_type = 1;
    bat.holder_id = 5;
    world_validate_weapon_holders(&world);
    assert(holder.weapon_type == 0);

    std::cout << "    wpoint kind == 3 drop and holder mismatch clearing verified!" << std::endl;
}

void test_cpoint_injury_chain_transform_and_orphan()
{
    std::cout << "[+] Testing Cpoint Injury, Chains, Breakout, Rudolf Transform & Orphan Release..." << std::endl;
    global_t world{};

    auto cfile = std::make_unique<file_t>();
    auto vfile = std::make_unique<file_t>();
    cfile->id = RUDOLF_DAT; cfile->type = TYPE_CHARACTER;
    vfile->id = DENNIS_DAT; vfile->type = TYPE_CHARACTER;

    cfile->frames[120].state = STATE_CATCHING;
    cfile->frames[120].centerx = 40; cfile->frames[120].centery = 40;
    cfile->frames[120].cpoint.kind = 1;
    cfile->frames[120].cpoint.x = 60; cfile->frames[120].cpoint.y = 35;
    cfile->frames[120].cpoint.injury = 30;
    cfile->frames[120].cpoint.cover = 21;
    cfile->frames[120].cpoint.vaction = 230;
    cfile->frames[120].cpoint.aaction = 121;
    cfile->frames[120].cpoint.taction = 122;
    cfile->frames[120].cpoint.jaction = 123;
    cfile->frames[120].cpoint.hurtable = 1;
    cfile->frames[120].cpoint.decrease = -10;
    cfile->frames[120].cpoint.dircontrol = 1;

    cfile->frames[121].cpoint.kind = 1; cfile->frames[121].cpoint.vaction = 231;
    cfile->frames[122].cpoint.kind = 1; cfile->frames[122].cpoint.vaction = 232;
    cfile->frames[123].cpoint.kind = 1; cfile->frames[123].cpoint.vaction = 233;

    cfile->frames[126].state = STATE_CATCHING;
    cfile->frames[126].centerx = 40; cfile->frames[126].centery = 40;
    cfile->frames[126].next = 0;
    cfile->frames[126].cpoint.kind = 1;
    cfile->frames[126].cpoint.vaction = 180;
    cfile->frames[126].cpoint.throwvx = 10;
    cfile->frames[126].cpoint.throwinjury = -1;

    for (int f = 230; f <= 233; ++f) {
        vfile->frames[f].centerx = 30;
        vfile->frames[f].centery = 40;
        vfile->frames[f].cpoint.kind = 2;
        vfile->frames[f].cpoint.x = 30;
        vfile->frames[f].cpoint.y = 40;
    }

    object_t catcher, victim, clone_obj;
    object_init(&catcher);
    object_init(&victim);
    object_init(&clone_obj);

    catcher.file = cfile.get();
    catcher.owner = 0;
    catcher.x = 200; catcher.z = 150;
    catcher.facing = FACING_RIGHT;
    catcher.frame_id1 = 120; catcher.frame_id4 = 120;
    catcher.cpoint_catcher = 1;
    catcher.cpoint_hold_timer = 300;
    catcher.wait_counter = 0;

    victim.file = vfile.get();
    victim.x = 220; victim.z = 150;
    victim.facing = FACING_RIGHT;
    victim.frame_id1 = 230; victim.frame_id4 = 230;
    victim.cpoint_caught = 0;

    clone_obj.file = cfile.get();
    clone_obj.clone = 0;

    world.objects[0] = &catcher;   world.is_object_exists[0] = 1;
    world.objects[1] = &victim;    world.is_object_exists[1] = 1;
    world.objects[2] = &clone_obj; world.is_object_exists[2] = 1;

    // Once-per-frame injury (wait_counter 0 -> 1), cover 21 facing/depth
    world_process_cpoint_sync(&world);
    assert(victim.hp == 470 && victim.dark_hp == 490);
    assert(catcher.wait_counter == 1);
    assert(catcher.shaking == 2 && victim.shaking == -3);
    assert(catcher.total_attack == 30);
    assert(victim.z == 151);
    assert(victim.facing == FACING_LEFT);

    victim.shaking = 0;
    world_process_cpoint_sync(&world);
    assert(victim.hp == 470);

    // dircontrol at wait_counter == 2
    catcher.shaking = 0;
    catcher.wait_counter = 2;
    catcher.click_left = 1;
    world_process_cpoint_chain(&world);
    assert(catcher.facing == FACING_LEFT);

    // aaction / taction / jaction
    catcher.click_left = 0; catcher.click_attack = 1; catcher.attack_press = 1;
    catcher.cpoint_hold_timer = 300;
    world_process_cpoint_chain(&world);
    assert(catcher.frame_id1 == 121 && victim.frame_id1 == 231);
    assert(catcher.wait_counter == 0 && victim.wait_counter == 0);

    catcher.frame_id1 = 120; catcher.frame_id4 = 120;
    catcher.click_left = 1; catcher.cpoint_hold_timer = 300;
    world_process_cpoint_chain(&world);
    assert(catcher.frame_id1 == 122 && victim.frame_id1 == 232);

    catcher.frame_id1 = 120; catcher.frame_id4 = 120;
    catcher.click_attack = 0; catcher.click_jump = 1; catcher.jump_press = 1;
    catcher.cpoint_hold_timer = 300;
    world_process_cpoint_chain(&world);
    assert(catcher.frame_id1 == 123 && victim.frame_id1 == 233);

    // Breakout (cpoint_hold_timer + decrease < 0 -> frame 181)
    catcher.frame_id1 = 120; catcher.frame_id4 = 120;
    victim.frame_id1 = 230; victim.frame_id4 = 230;
    catcher.click_jump = 0; catcher.click_left = 0;
    catcher.cpoint_hold_timer = 5;
    world_process_cpoint_chain(&world);
    assert(catcher.frame_id1 == 0 && victim.frame_id1 == 181);
    assert(victim.attacks == 1 && victim.y_accl == -3.0 && victim.pic_x_gain == 4.0);

    // Rudolf transform + clone propagation
    catcher.frame_id1 = 126; catcher.frame_id4 = 126;
    victim.frame_id1 = 230; victim.frame_id4 = 230;
    world_process_cpoint_chain(&world);
    assert(catcher.file == vfile.get());
    assert(catcher.uid == static_cast<int32_t>(RUDOLF_DAT));
    assert(catcher.transformed_to_id == static_cast<int32_t>(DENNIS_DAT));
    assert(clone_obj.file == vfile.get());

    // Orphan victim release -> 212
    catcher.file = cfile.get();
    catcher.frame_id1 = 0; catcher.frame_id4 = 0;
    victim.frame_id1 = 230; victim.frame_id4 = 230;
    victim.y_position = 0.0; victim.y_velocity = 0.0;
    world_process_cpoint_chain(&world);
    assert(victim.frame_id1 == 212 && victim.y_velocity == -3.0 && victim.y_position == -2.0);

    std::cout << "    Cpoint injury, chain combos, breakout, Rudolf transform & orphan release verified!" << std::endl;
}

void test_firzen_fusion_and_defusion()
{
    std::cout << "[+] Testing Firen + Freeze -> Firzen Fusion & Defusion (0x004064D0)..." << std::endl;
    global_t world{};

    auto firen_file = std::make_unique<file_t>();
    auto freeze_file = std::make_unique<file_t>();
    auto firzen_file = std::make_unique<file_t>();
    firen_file->id = FIREN_DAT;   firen_file->type = TYPE_CHARACTER;
    freeze_file->id = FREEZE_DAT; freeze_file->type = TYPE_CHARACTER;
    firzen_file->id = FIRZEN_DAT; firzen_file->type = TYPE_CHARACTER;
    firen_file->frames[9].state = STATE_RUNNING;
    freeze_file->frames[9].state = STATE_RUNNING;

    world.files[0] = firen_file.get();
    world.files[1] = freeze_file.get();
    world.files[2] = firzen_file.get();

    object_t firen, freeze;
    object_init(&firen);
    object_init(&freeze);
    firen.file = firen_file.get();   firen.hp = 150;  firen.frame_id1 = 9;  firen.x = 120; firen.z = 200; firen.team = 1;
    freeze.file = freeze_file.get(); freeze.hp = 140; freeze.frame_id1 = 9; freeze.x = 100; freeze.z = 200; freeze.team = 1;

    world.objects[0] = &firen;  world.is_object_exists[0] = 1;
    world.objects[1] = &freeze; world.is_object_exists[1] = 1;

    world_process_firzen_fusion(&world, 0);
    assert(firen.file == firzen_file.get());
    assert(firen.frame_id1 == 290);
    assert(firen.hp == 290);
    assert(firen.mp == 500);
    assert(firen.firen_counter == 4500);
    assert(firen.fusion_state == 1);
    assert(world.is_object_exists[1] == 0);

    firen.frame_id1 = 0;
    firen.firen_counter = 1;
    world_process_firzen_fusion(&world, 0);
    assert(firen.fusion_state == -1);
    assert(firen.file == firen_file.get() && freeze.file == freeze_file.get());
    assert(world.is_object_exists[1] == 1);
    assert(firen.hp == 145 && freeze.hp == 145);
    assert(firen.frame_id1 == 112 && freeze.frame_id1 == 112);
    assert(firen.mp == 0 && freeze.mp == 0);
    assert(firen.firen_counter == 900);
    assert(freeze.facing == static_cast<uint8_t>(1U - firen.facing));

    std::cout << "    Firzen fusion & timer-0 defusion split verified!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Grapple, Throw & Weapon Mechanics Tests ===" << std::endl;
    test_grapple_initiate_and_sync();
    test_grapple_throw_execution();
    test_weapon_pickup_and_sync();
    test_weapon_drop_and_throw();
    test_milk_and_beer_drinking();
    test_wpoint_kind3_drop_and_holder_validation();
    test_cpoint_injury_chain_transform_and_orphan();
    test_firzen_fusion_and_defusion();
    std::cout << "[SUCCESS] All Grapple, Throw & Weapon Mechanics tests passed with 100% precision!" << std::endl;
    return 0;
}
