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

    input_state_t input = ai_evaluate_behavior(&world, 0, AI_NORMAL);
    assert(input.attack == true);
    assert(ai_bot.facing == FACING_RIGHT);

    // Apply tick and verify state transition to attacking
    ai_tick(&world, 0, AI_NORMAL);
    assert(ai_bot.frame_id1 == 60); // Punch attack frame

    std::cout << "    AI successfully triggered melee attack and transitioned to punch frame 60!" << std::endl;
}

int main()
{
    std::cout << "=== Little Fighter 2 Artificial Intelligence Controller Tests ===" << std::endl;
    test_ai_target_selection();
    test_ai_approach_movement();
    test_ai_melee_engagement();
    std::cout << "[SUCCESS] All AI Controller tests passed with 100% precision!" << std::endl;
    return 0;
}

