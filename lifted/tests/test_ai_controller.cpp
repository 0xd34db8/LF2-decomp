#include <iostream>
#include <cassert>
#include <cstring>
#include "core/global.h"
#include "gameplay/entity.h"
#include "gameplay/ai.h"

using namespace lf2;

void test_ai_target_selection()
{
    std::cout << "[+] Testing AI target selection & team filtering (0x00406BA0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    char_file.type = TYPE_CHARACTER;

    object_t ai_bot;
    object_init(&ai_bot);
    ai_bot.file = &char_file;
    ai_bot.x = 100;
    ai_bot.y = 0;
    ai_bot.z = 200;
    ai_bot.team = 1;

    // Teammate (should be ignored)
    object_t teammate;
    object_init(&teammate);
    teammate.file = &char_file;
    teammate.x = 110;
    teammate.y = 0;
    teammate.z = 200;
    teammate.team = 1;

    // Distant enemy
    object_t distant_enemy;
    object_init(&distant_enemy);
    distant_enemy.file = &char_file;
    distant_enemy.x = 400;
    distant_enemy.y = 0;
    distant_enemy.z = 200;
    distant_enemy.team = 2;

    // Close enemy
    object_t close_enemy;
    object_init(&close_enemy);
    close_enemy.file = &char_file;
    close_enemy.x = 180;
    close_enemy.y = 0;
    close_enemy.z = 200;
    close_enemy.team = 2;

    world.objects[0] = &ai_bot;
    world.is_object_exists[0] = 1;
    world.objects[1] = &teammate;
    world.is_object_exists[1] = 1;
    world.objects[2] = &distant_enemy;
    world.is_object_exists[2] = 1;
    world.objects[3] = &close_enemy;
    world.is_object_exists[3] = 1;

    uint32_t target = ai_find_nearest_target(&world, 0);
    assert(target == 3); // Must pick close enemy (slot 3), not teammate (slot 1) or distant enemy (slot 2)

    std::cout << "    AI successfully targeted closest enemy (slot 3) ignoring teammates!" << std::endl;
}

void test_ai_approach_movement()
{
    std::cout << "[+] Testing AI tracking & approach movement generation..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    char_file.type = TYPE_CHARACTER;

    object_t ai_bot;
    object_init(&ai_bot);
    ai_bot.file = &char_file;
    ai_bot.x = 100;
    ai_bot.y = 0;
    ai_bot.z = 200;
    ai_bot.team = 1;

    object_t enemy;
    object_init(&enemy);
    enemy.file = &char_file;
    enemy.x = 300; // Far to the right
    enemy.y = 0;
    enemy.z = 250; // Downwards in Z depth
    enemy.team = 2;

    world.objects[0] = &ai_bot;
    world.is_object_exists[0] = 1;
    world.objects[1] = &enemy;
    world.is_object_exists[1] = 1;

    input_state_t input = ai_evaluate_behavior(&world, 0, AI_NORMAL);
    assert(input.right == true);
    assert(input.down == true);
    assert(input.left == false);
    assert(input.up == false);
    assert(ai_bot.facing == FACING_RIGHT);

    std::cout << "    AI correctly synthesized Right + Down approach vector!" << std::endl;
}

void test_ai_melee_engagement()
{
    std::cout << "[+] Testing AI melee range attack synthesis..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    char_file.type = TYPE_CHARACTER;

    object_t ai_bot;
    object_init(&ai_bot);
    ai_bot.file = &char_file;
    ai_bot.x = 100;
    ai_bot.y = 0;
    ai_bot.z = 200;
    ai_bot.team = 1;

    object_t enemy;
    object_init(&enemy);
    enemy.file = &char_file;
    enemy.x = 130; // Within melee distance (30 pixels)
    enemy.y = 0;
    enemy.z = 200;
    enemy.team = 2;

    world.objects[0] = &ai_bot;
    world.is_object_exists[0] = 1;
    world.objects[1] = &enemy;
    world.is_object_exists[1] = 1;

    bool got_attack = false;
    for (int t = 0; t < 32; ++t) {
        input_state_t input = ai_evaluate_behavior(&world, 0, AI_NORMAL);
        if (input.attack) {
            got_attack = true;
            assert(ai_bot.facing == FACING_RIGHT);
            break;
        }
    }
    assert(got_attack == true);

    // Apply tick and verify state transition to attacking (punch 1 or punch 2: (r + 12) * 5)
    bool entered_punch = false;
    for (int t = 0; t < 32; ++t) {
        ai_bot.frame_id1 = 0;
        ai_bot.wait_counter = 0;
        ai_bot.x = 100;
        ai_bot.y = 0;
        ai_bot.y_position = 0.0;
        ai_bot.facing = FACING_RIGHT;
        ai_tick(&world, 0, AI_NORMAL);
        if (ai_bot.frame_id1 == 60 || ai_bot.frame_id1 == 65) {
            entered_punch = true;
            break;
        }
    }
    assert(entered_punch == true);

    std::cout << "    AI successfully triggered melee attack and transitioned to punch frame " << ai_bot.frame_id1 << "!" << std::endl;
}

void test_ai_combat_dodge()
{
    std::cout << "[+] Testing AI combat dodge & evasive roll (0x004034F0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t char_file;
    std::memset(&char_file, 0, sizeof(char_file));
    char_file.type = TYPE_CHARACTER;
    char_file.id = DAVIS_DAT;

    object_t ai_bot;
    object_init(&ai_bot);
    ai_bot.file = &char_file;
    ai_bot.x = 100;
    ai_bot.y = 0;
    ai_bot.z = 200;
    ai_bot.team = 1;
    ai_bot.facing = FACING_RIGHT;
    ai_bot.frame_id1 = 110; // Guard / defend stance

    object_t enemy;
    object_init(&enemy);
    enemy.file = &char_file;
    enemy.x = 250; // Approaching enemy at range dx = 150
    enemy.y = 0;
    enemy.z = 200;
    enemy.team = 2;

    world.objects[0] = &ai_bot;
    world.is_object_exists[0] = 1;
    world.objects[1] = &enemy;
    world.is_object_exists[1] = 1;

    input_state_t input;
    bool dodged = ai_evaluate_dodge(&world, 0, 1, input, AI_CRAZY);
    assert(dodged == true);
    assert(input.right == true);
    assert(input.attack == true);

    std::cout << "    AI successfully evaluated dodge roll maneuver towards oncoming target!" << std::endl;
}

void test_ai_control_object_behaviors()
{
    std::cout << "[+] Testing 1:1 ai_control_object (0x4094B0): GO, waypoints, ball defend, weapon pickup, flame hazard & cancel..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t firen_file{}, john_ball_file{}, stick_file{}, flame_file{}, dennis_file{};
    firen_file.id = FIREN_DAT; firen_file.type = TYPE_CHARACTER;
    dennis_file.id = DENNIS_DAT; dennis_file.type = TYPE_CHARACTER;
    john_ball_file.id = JOHN_BALL_DAT; john_ball_file.type = 3;
    john_ball_file.frames[0].state = 3000;
    stick_file.id = STICK_DAT; stick_file.type = 1;
    stick_file.frames[0].state = 1004;
    flame_file.id = FIREN_FLAME_DAT; flame_file.type = 3;
    flame_file.frames[0].state = STATE_BURNING;

    object_t ai_bot, enemy, obj50;
    object_init(&ai_bot);
    ai_bot.file = &firen_file; ai_bot.team = 1; ai_bot.hp = 500;
    ai_bot.x = 200; ai_bot.z = 200; ai_bot.facing = FACING_RIGHT;
    world.objects[0] = &ai_bot; world.is_object_exists[0] = 1;

    ai_world_params_t params{};
    params.difficulty = -1; // CRAZY! -> skill == 0

    // 1. Stage GO scroll override & blocked_right obstacle punch
    params.mode = 1;
    params.stage_last_phase = 1;
    ai_bot.blocked_right = 1;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_right == 1 && ai_bot.holding_right == 0 && ai_bot.click_attack == 1);
    params.mode = 0; params.stage_last_phase = 0; ai_bot.blocked_right = 0;

    // 2. Waypoint order: approach & arrival clear
    ai_bot.ai_target_x = 500; ai_bot.ai_target_z = 200;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_right == 1 && ai_bot.ai_target_x == 500);
    ai_bot.ai_target_x = 220; ai_bot.ai_target_z = 200;
    ai_control_object(&world, 0, params);
    assert(ai_bot.ai_target_x == -1000 && ai_bot.ai_target_z == -1000);

    // 3. Defend oncoming flying ball (state 3000)
    object_init(&obj50);
    obj50.file = &john_ball_file; obj50.team = 2; obj50.hp = 500;
    obj50.x = 300; obj50.z = 200; obj50.x_velocity = -10.0;
    world.objects[50] = &obj50; world.is_object_exists[50] = 1;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_defend == 1);

    // 4. Ground weapon pickup when closer than enemy (enemy off Z-axis so close_target == 0)
    object_init(&enemy);
    enemy.file = &dennis_file; enemy.team = 2; enemy.hp = 500;
    enemy.x = 700; enemy.z = 250;
    world.objects[1] = &enemy; world.is_object_exists[1] = 1;
    object_init(&obj50);
    obj50.file = &stick_file; obj50.x = 320; obj50.z = 250;
    world.objects[50] = &obj50; world.is_object_exists[50] = 1;
    ai_bot.x = 200; ai_bot.z = 200; ai_bot.weapon_type = 0;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_right == 1 && ai_bot.click_down == 1);

    // 5. Firen flame hazard avoidance (blocks click_down toward enemy when deeper == 1)
    object_init(&obj50);
    obj50.file = &flame_file; obj50.x = 240; obj50.z = 230;
    world.objects[50] = &obj50; world.is_object_exists[50] = 1;
    ai_bot.x = 200; ai_bot.z = 200;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_down == 0);
    world.is_object_exists[50] = 0;

    // 6. No-target Firen frame 255..261 cancel
    world.is_object_exists[1] = 0;
    ai_bot.frame_id1 = 257; ai_bot.click_defend = 0;
    ai_control_object(&world, 0, params);
    assert(ai_bot.click_defend == 1);

    std::cout << "    1:1 ai_control_object behaviors verified 100%!" << std::endl;
}

void test_ai_character_specials_and_weapons()
{
    std::cout << "[+] Testing 1:1 ai_evaluate_character_special (0x403A40) & ai_evaluate_weapon_decision (0x408CB0)..." << std::endl;
    global_t world;
    std::memset(&world, 0, sizeof(world));

    file_t john_file{}, firen_file{}, jan_file{}, firzen_file{}, julian_file{}, dennis_file{},
           stick_file{}, milk_file{};
    john_file.id = JOHN_DAT; john_file.type = TYPE_CHARACTER;
    firen_file.id = FIREN_DAT; firen_file.type = TYPE_CHARACTER;
    jan_file.id = JAN_DAT; jan_file.type = TYPE_CHARACTER;
    firzen_file.id = FIRZEN_DAT; firzen_file.type = TYPE_CHARACTER;
    julian_file.id = JULIAN_DAT; julian_file.type = TYPE_CHARACTER;
    dennis_file.id = DENNIS_DAT; dennis_file.type = TYPE_CHARACTER;
    stick_file.id = STICK_DAT; stick_file.type = 1;
    milk_file.id = MILK_DAT; milk_file.type = 2;

    object_t self, target, ally, weapon;
    object_init(&self);
    object_init(&target);
    object_init(&ally);
    object_init(&weapon);

    target.file = &dennis_file; target.team = 2; target.hp = 500;
    target.x = 300; target.z = 200;
    world.objects[0] = &self; world.is_object_exists[0] = 1;
    world.objects[1] = &target; world.is_object_exists[1] = 1;

    // 1. John low HP self-heal (click_DDJ == 3)
    self.file = &john_file; self.team = 1; self.hp = 80; self.dark_hp = 500; self.mp = 400;
    self.x = 200; self.z = 200; self.facing = FACING_RIGHT;
    bool john_heal = false;
    for (int t = 0; t < 48; ++t) {
        self.click_DDJ = 0;
        if (ai_evaluate_character_special(&world, 1, 0, 0, 0, 0, 100, 0, 800, 0, 0) == 1 &&
            self.click_DDJ == 3) {
            john_heal = true;
            break;
        }
    }
    assert(john_heal == true);

    // 2. Firen blaze cancel (deterministic)
    self.file = &firen_file; self.frame_id1 = 257; self.x = 400; target.x = 200;
    self.facing = FACING_RIGHT; self.click_defend = 0;
    assert(ai_evaluate_character_special(&world, 1, 0, 0, 0, 0, 200, 0, 800, 0, 0) == 1 &&
           self.click_defend == 1);

    // 3. Firzen cannon cancel (deterministic)
    self.file = &firzen_file; self.frame_id1 = 270;
    self.x = 200; target.x = 300; target.z = 230; self.click_defend = 0;
    assert(ai_evaluate_character_special(&world, 1, 0, 0, 0, 0, 200, 0, 800, 0, 0) == 1 &&
           self.click_defend == 1);

    // 4. Jan angel blessing on injured ally
    self.file = &jan_file; self.frame_id1 = 0; self.mp = 300; target.z = 200;
    ally.file = &dennis_file; ally.team = 1; ally.hp = 100; ally.dark_hp = 400;
    world.objects[2] = &ally; world.is_object_exists[2] = 1;
    bool jan_heal = false;
    for (int t = 0; t < 48; ++t) {
        self.click_DUJ = 0;
        if (ai_evaluate_character_special(&world, 1, 0, 0, 0, 0, 200, 0, 800, 0, 0) == 1 &&
            self.click_DUJ == 3) {
            jan_heal = true;
            break;
        }
    }
    assert(jan_heal == true);
    world.is_object_exists[2] = 0;

    // 5. Julian specials (click_DRA / DJA / DUJ)
    self.file = &julian_file; self.frame_id1 = 0; self.mp = 400;
    self.x = 200; target.x = 280; target.z = 200;
    bool julian_spec = false;
    for (int t = 0; t < 48; ++t) {
        self.click_DRA = 0; self.click_DUJ = 0; self.click_DJA = 0; self.click_DRJ = 0;
        if (ai_evaluate_character_special(&world, 1, 0, 0, 3, 0, 80, 0, 800, 0, 0) == 1) {
            if (self.click_DRA == 3 || self.click_DUJ == 3 || self.click_DJA == 3 || self.click_DRJ == 3) {
                julian_spec = true;
                break;
            }
        }
    }
    assert(julian_spec == true);

    // 6. Weapon decisions (0x408CB0): stick velocity lead, ally_in_line, milk corner flee & John shield
    ai_world_params_t params{};
    params.difficulty = -1; params.stage_width = 800; params.zboundary_min = 0; params.zboundary_max = 400;
    self.file = &john_file; self.weapon_type = 1; self.weapon_id = 3;
    weapon.file = &stick_file;
    world.objects[3] = &weapon; world.is_object_exists[3] = 1;

    self.x = 400; self.z = 220; self.x_velocity = 10.0;
    target.x = 500; target.z = 220; target.team = 2;
    bool stick_atk = false;
    for (int t = 0; t < 48; ++t) {
        self.click_attack = 0;
        ai_evaluate_weapon_decision(&world, 1, 0, 0, 0, 0, 0, 800, 0, 0, 0, 0, params);
        if (self.click_attack == 1) { stick_atk = true; break; }
    }
    assert(stick_atk == true);

    // ally_in_line running jump-over (target->team == self->team per 0x00408D46)
    target.team = 1; target.x = 600; target.z = 200;
    self.x = 200; self.z = 200; self.x_velocity = 0.0;
    ally.team = 1; ally.hp = 500; ally.x = 400; ally.z = 200;
    world.objects[2] = &ally; world.is_object_exists[2] = 1;
    bool jump_over = false;
    for (int t = 0; t < 64; ++t) {
        self.click_jump = 0;
        ai_evaluate_weapon_decision(&world, 1, 0, STATE_RUNNING, 0, 0, 0, 800, 0, 0, 0, 0, params);
        if (self.click_jump == 1) { jump_over = true; break; }
    }
    assert(jump_over == true);
    world.is_object_exists[2] = 0;

    // Milk corner flee & John shield before drinking
    weapon.file = &milk_file;
    target.team = 2;
    self.x = 50; self.z = 200; target.x = 150; target.z = 200;
    ai_evaluate_weapon_decision(&world, 1, 0, 0, 0, 0, 0, 800, 0, 0, 0, 0, params);
    assert(self.click_right == 1 && self.click_up == 1);

    self.x = 200; self.z = 200; target.x = 750; target.z = 200; self.mp = 300;
    bool john_shield = false;
    for (int t = 0; t < 64; ++t) {
        self.click_DRJ = 0;
        if (ai_evaluate_weapon_decision(&world, 1, 0, 0, 0, 0, 0, 800, 0, 0, 0, 0, params) == 1 &&
            self.click_DRJ == 3) {
            john_shield = true;
            break;
        }
    }
    assert(john_shield == true);

    std::cout << "    1:1 character specials (John/Firen/Firzen/Jan/Julian) & weapon decisions verified 100%!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Artificial Intelligence Controller Tests ===" << std::endl;
    test_ai_target_selection();
    test_ai_approach_movement();
    test_ai_melee_engagement();
    test_ai_combat_dodge();
    test_ai_control_object_behaviors();
    test_ai_character_specials_and_weapons();
    std::cout << "[SUCCESS] All AI Controller tests passed with 100% precision!" << std::endl;
    return 0;
}

