#include <iostream>
#include <cassert>
#include <iomanip>
#include "constants.h"
#include "bdy.h"
#include "itr.h"
#include "frame.h"
#include "file.h"
#include "object.h"
#include "global.h"

using namespace lf2;

int main() {
    std::cout << "=== Little Fighter 2 Memory Map Verification ===" << std::endl;

    std::cout << "[+] bdy_t size:    0x" << std::hex << sizeof(bdy_t) << " (" << std::dec << sizeof(bdy_t) << " bytes)" << std::endl;
    std::cout << "[+] itr_t size:    0x" << std::hex << sizeof(itr_t) << " (" << std::dec << sizeof(itr_t) << " bytes)" << std::endl;
    std::cout << "[+] opoint_t size: 0x" << std::hex << sizeof(opoint_t) << " (" << std::dec << sizeof(opoint_t) << " bytes)" << std::endl;
    std::cout << "[+] bpoint_t size: 0x" << std::hex << sizeof(bpoint_t) << " (" << std::dec << sizeof(bpoint_t) << " bytes)" << std::endl;
    std::cout << "[+] cpoint_t size: 0x" << std::hex << sizeof(cpoint_t) << " (" << std::dec << sizeof(cpoint_t) << " bytes)" << std::endl;
    std::cout << "[+] wpoint_t size: 0x" << std::hex << sizeof(wpoint_t) << " (" << std::dec << sizeof(wpoint_t) << " bytes)" << std::endl;
    std::cout << "[+] frame_t size:  0x" << std::hex << sizeof(frame_t) << " (" << std::dec << sizeof(frame_t) << " bytes)" << std::endl;
    std::cout << "[+] file_t size:   0x" << std::hex << sizeof(file_t) << " (" << std::dec << sizeof(file_t) << " bytes)" << std::endl;
    std::cout << "[+] object_t size: 0x" << std::hex << sizeof(object_t) << " (" << std::dec << sizeof(object_t) << " bytes)" << std::endl;
    std::cout << "[+] global_t size: 0x" << std::hex << sizeof(global_t) << " (" << std::dec << sizeof(global_t) << " bytes)" << std::endl;

    // Verify sizes
    assert(sizeof(bdy_t) == 0x28);
    assert(sizeof(itr_t) == 0x50);
    assert(sizeof(opoint_t) == 0x20);
    assert(sizeof(bpoint_t) == 0x0C);
    assert(sizeof(cpoint_t) == 0x44);
    assert(sizeof(wpoint_t) == 0x24);
    assert(sizeof(frame_t) == 0x178);
    assert(sizeof(file_t) == 0x25360);
    assert(sizeof(object_t) == 0x370);
#if INTPTR_MAX == INT32_MAX
    assert(sizeof(global_t) == 0x8D8);
    assert(offsetof(global_t, files) == 0x7D4);
#endif

    // Verify critical offsets in global_t
    assert(offsetof(global_t, is_object_exists) == 0x004);
    assert(offsetof(global_t, objects) == 0x194);

    // Verify critical offsets in object_t
    assert(offsetof(object_t, x) == 0x010);
    assert(offsetof(object_t, y) == 0x014);
    assert(offsetof(object_t, z) == 0x018);
    assert(offsetof(object_t, x_velocity) == 0x040);
    assert(offsetof(object_t, y_velocity) == 0x048);
    assert(offsetof(object_t, z_velocity) == 0x050);
    assert(offsetof(object_t, x_position) == 0x058);
    assert(offsetof(object_t, y_position) == 0x060);
    assert(offsetof(object_t, z_position) == 0x068);
    assert(offsetof(object_t, facing) == 0x080);
    assert(offsetof(object_t, vrest_of_objects) == 0x0F0);
    assert(offsetof(object_t, injured_of_attack) == 0x280);
    assert(offsetof(object_t, itr_of_attack) == 0x2D0);
    assert(offsetof(object_t, hp) == 0x2FC);
    assert(offsetof(object_t, team) == 0x364);
    assert(offsetof(object_t, file) == 0x368);

    // Verify critical offsets in file_t
    assert(offsetof(file_t, attacking_itrs) == 0x0B0);
    assert(offsetof(file_t, attacking_itrs) + offsetof(itr_t, dvx) == 0x0C4);
    assert(offsetof(file_t, id) == 0x6F4);
    assert(offsetof(file_t, type) == 0x6F8);
    assert(offsetof(file_t, head_bmp_mgr) == 0x6FC);
    assert(offsetof(file_t, head) == 0x700);
    assert(offsetof(file_t, small_bmp_mgr) == 0x728);
    assert(offsetof(file_t, small) == 0x72C);
    assert(offsetof(file_t, bmp_mgrs) == 0x750);
    assert(offsetof(file_t, mirror_bmp_mgrs) == 0x778);
    assert(offsetof(file_t, frames) == 0x7A4);
    assert(offsetof(file_t, name) == 0x25324);

    // Test teleport logic
    std::cout << "\n[+] Testing 1:1 lifted teleport logic..." << std::endl;
    global_t game{};

    file_t char_file{};
    char_file.type = TYPE_CHARACTER;

    object_t rudolf{};
    rudolf.file = &char_file;
    rudolf.team = 1;
    rudolf.hp = 100;
    rudolf.facing = FACING_RIGHT; // Facing right (0)
    rudolf.x = 100;
    rudolf.y = 50;
    rudolf.z = 200;

    object_t enemy{};
    enemy.file = &char_file;
    enemy.team = 2; // Different team
    enemy.hp = 100;
    enemy.x = 500;
    enemy.y = 0;
    enemy.z = 220;

    game.is_object_exists[0] = 1;
    game.objects[0] = &rudolf;

    game.is_object_exists[1] = 1;
    game.objects[1] = &enemy;

    // Teleport Rudolf to enemy
    game.teleport(0, TELEPORT_TO_ENEMY);

    // Rudolf should appear at enemy.z + 1, enemy.x - 120 (since facing right), y = 0
    std::cout << "    Rudolf pos: (" << rudolf.x << ", " << rudolf.y << ", " << rudolf.z << ")" << std::endl;
    assert(rudolf.y == 0);
    assert(rudolf.z == enemy.z + 1); // 221
    assert(rudolf.x == enemy.x - 120); // 380
    assert(rudolf.x_position == 380.0);
    assert(rudolf.y_position == 0.0);
    assert(rudolf.z_position == 221.0);
    assert(rudolf.x_velocity == 0.0);
    assert(rudolf.y_velocity == 0.0);
    assert(rudolf.z_velocity == 0.0);

    // Test does_attack_success collision logic
    std::cout << "\n[+] Testing 1:1 lifted does_attack_success collision logic..." << std::endl;
    itr_t test_itr{};
    test_itr.kind = 0; // normal attack
    test_itr.x = 10;
    test_itr.y = 10;
    test_itr.w = 40;
    test_itr.h = 40;
    test_itr.zwidth = 15;
    test_itr.vrest = 5;

    bdy_t test_bdy{};
    test_bdy.kind = 0;
    test_bdy.x = 10;
    test_bdy.y = 10;
    test_bdy.w = 40;
    test_bdy.h = 40;

    char_file.frames[0].itrs_size = 1;
    char_file.frames[0].itrs = &test_itr;
    char_file.frames[0].bdys_size = 1;
    char_file.frames[0].bdys = &test_bdy;

    rudolf.frame_id4 = 0;
    rudolf.frame_id1 = 0;
    rudolf.frame_id3 = 0;
    rudolf.x = 100;
    rudolf.y = 50;
    rudolf.z = 100;
    rudolf.facing = FACING_RIGHT;
    rudolf.successful_attacks = 0;

    enemy.frame_id4 = 0;
    enemy.frame_id1 = 0;
    enemy.frame_id3 = 0;
    enemy.x = 110;
    enemy.y = 50;
    enemy.z = 102;
    enemy.facing = FACING_RIGHT;

    // Attacker and enemy overlap within zwidth (102 - 100 = 2 < 15) and 2D bounds
    game.does_attack_success(0, 1, 0);
    std::cout << "    Attacks registered: " << rudolf.successful_attacks << std::endl;
    assert(rudolf.successful_attacks == 1);
    assert(rudolf.injured_of_attack[0] == 1);
    assert(rudolf.itr_of_attack[0] == 0);

    // Test non-overlapping Z: enemy moved outside zwidth (z = 150, diff = 50 >= 15)
    rudolf.successful_attacks = 0;
    enemy.z = 150;
    game.does_attack_success(0, 1, 0);
    assert(rudolf.successful_attacks == 0);
    std::cout << "    Z-out-of-bounds correctly ignored: " << rudolf.successful_attacks << std::endl;

    std::cout << "\n[SUCCESS] All data structures, binary alignments, and lifted logic verified 100%!" << std::endl;
    return 0;
}

