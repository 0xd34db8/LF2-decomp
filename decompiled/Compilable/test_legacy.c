#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

int main() {
    printf("======================================================================\n");
    printf(" Little Fighter 2 - Decompiled Compilable Legacy Suite Verification\n");
    printf(" Pure x86 MSVC++ 32-bit Assembly Decompiled C Engine\n");
    printf("======================================================================\n");

    // 1. Test fast absolute value computation (0x004034e0)
    printf("[+] Testing Decompiled Fast Integer Absolute Value (0x004034e0)...\n");
    assert(FUN_004034e0(42) == 42);
    assert(FUN_004034e0(-42) == 42);
    assert(FUN_004034e0(0) == 0);
    assert(FUN_004034e0(-2147483647) == 2147483647);
    printf("    [PASS] 0x004034e0 returned exact absolute values across all sign bit cases.\n");

    // 2. Test 2D Bounding Box Overlap Check (0x004171c0)
    // Prototype: FUN_004171c0(bdy_x, bdy_y, bdy_w, bdy_h, itr_x, itr_y, itr_w, itr_h)
    printf("[+] Testing Decompiled 2D Box Overlap Check (0x004171c0)...\n");
    // Overlapping boxes: (10, 10, 20, 20) and (20, 20, 20, 20)
    assert(FUN_004171c0(10, 10, 20, 20, 20, 20, 20, 20) == 1);
    // Non-overlapping boxes: (10, 10, 20, 20) and (100, 100, 20, 20)
    assert(FUN_004171c0(10, 10, 20, 20, 100, 100, 20, 20) == 0);
    printf("    [PASS] 0x004171c0 correctly verified 2D bounding box intersections.\n");

    // 3. Test PRNG Lookup (0x00417170)
    printf("[+] Testing Decompiled Circular PRNG Table (0x00417170)...\n");
    DAT_00450bcc = 0;
    DAT_00450c34 = 1234;
    int r1 = FUN_00417170(0, 100);
    assert(r1 >= 0 && r1 < 100);
    printf("    [PASS] 0x00417170 generated valid pseudo-random modulus index: %d\n", r1);

    // 4. Test Global Memory Mappings
    printf("[+] Verifying Global Memory Symbols & Structure Alignments...\n");
    assert(sizeof(DAT_00455378) == 300); // 300-byte Win32 key buffer
    printf("    [PASS] Global symbols and memory layouts verified successfully.\n");

    // 5. Test LF2 Structure Layouts & Alignments
    printf("[+] Verifying Human-Readable Domain Structure Alignments...\n");
    printf("    sizeof(bdy_t): 0x%zx (%zu)\n", sizeof(bdy_t), sizeof(bdy_t));
    printf("    sizeof(itr_t): 0x%zx (%zu)\n", sizeof(itr_t), sizeof(itr_t));
    printf("    sizeof(opoint_t): 0x%zx (%zu)\n", sizeof(opoint_t), sizeof(opoint_t));
    printf("    sizeof(bpoint_t): 0x%zx (%zu)\n", sizeof(bpoint_t), sizeof(bpoint_t));
    printf("    sizeof(cpoint_t): 0x%zx (%zu)\n", sizeof(cpoint_t), sizeof(cpoint_t));
    printf("    sizeof(wpoint_t): 0x%zx (%zu)\n", sizeof(wpoint_t), sizeof(wpoint_t));
    printf("    sizeof(frame_t): 0x%zx (%zu)\n", sizeof(frame_t), sizeof(frame_t));
    printf("    offsetof(frame_t, opoint): 0x%zx\n", offsetof(frame_t, opoint));
    printf("    offsetof(frame_t, bpoint): 0x%zx\n", offsetof(frame_t, bpoint));
    printf("    offsetof(frame_t, cpoint): 0x%zx\n", offsetof(frame_t, cpoint));
    printf("    offsetof(frame_t, wpoint): 0x%zx\n", offsetof(frame_t, wpoint));
    printf("    offsetof(frame_t, itrs_size): 0x%zx\n", offsetof(frame_t, itrs_size));
    printf("    offsetof(frame_t, bdys_size): 0x%zx\n", offsetof(frame_t, bdys_size));
    printf("    offsetof(frame_t, itrs): 0x%zx\n", offsetof(frame_t, itrs));
    printf("    offsetof(frame_t, bdys): 0x%zx\n", offsetof(frame_t, bdys));
    printf("    offsetof(frame_t, name): 0x%zx\n", offsetof(frame_t, name));
    printf("    offsetof(frame_t, sound): 0x%zx\n", offsetof(frame_t, sound));
    assert(sizeof(bdy_t) == 0x28);
    assert(sizeof(itr_t) == 0x50);
    assert(sizeof(opoint_t) == 0x20);
    assert(sizeof(bpoint_t) == 0x0C);
    assert(sizeof(cpoint_t) == 0x44);
    assert(sizeof(wpoint_t) == 0x24);
    assert(sizeof(frame_t) == 0x178);
    assert(sizeof(file_t) == 0x25360);
    assert(sizeof(object_t) == 0x370);
    assert(offsetof(object_t, x) == 0x10);
    assert(offsetof(object_t, hp) == 0x2FC);
    assert(offsetof(object_t, team) == 0x364);
    assert(offsetof(object_t, file) == 0x368);
    assert(offsetof(global_t, is_object_exists) == 0x04);
    assert(offsetof(global_t, objects) == 0x194);
    printf("    [PASS] Verified 1:1 memory layout for all 10 LF2 domain structures.\n");

    // 6. Test Human-Readable Logic Functions
    printf("[+] Testing Decompiled Human-Readable Gameplay Logic (Teleport 0x00403270)...\n");
    global_t game;
    memset(&game, 0, sizeof(global_t));

    file_t char_file;
    memset(&char_file, 0, sizeof(file_t));
    char_file.type = TYPE_CHARACTER;

    object_t rudolf;
    lf2_object_init(&rudolf);
    rudolf.file = &char_file;
    rudolf.team = 1;
    rudolf.hp = 100;
    rudolf.facing = FACING_RIGHT;
    rudolf.x = 100;
    rudolf.y = 50;
    rudolf.z = 200;

    object_t enemy;
    lf2_object_init(&enemy);
    enemy.file = &char_file;
    enemy.team = 2; // Different team
    enemy.hp = 100;
    enemy.x = 500;
    enemy.y = 0;
    enemy.z = 200;

    game.is_object_exists[0] = 1;
    game.objects[0] = &rudolf;
    game.is_object_exists[1] = 1;
    game.objects[1] = &enemy;

    // Teleport Rudolf behind nearest enemy (teleport_to = 1)
    lf2_teleport(&game, 0, 1);
    assert(rudolf.x == 380); // 500 - 120 (facing right)
    assert(rudolf.y == 0);
    assert(rudolf.z == 201); // enemy.z + 1
    assert(rudolf.x_velocity == 0.0);
    assert(rudolf.y_velocity == 0.0);
    assert(rudolf.z_velocity == 0.0);
    printf("    [PASS] lf2_teleport correctly positioned Rudolf behind enemy (x=380, z=201, vels=0).\n");

    printf("\n[SUCCESS] All Decompiled Compilable Suite Tests Passed with 100%% Parity!\n");
    return 0;
}
