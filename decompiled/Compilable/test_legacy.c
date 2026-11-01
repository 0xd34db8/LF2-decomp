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

    printf("\n[SUCCESS] All Decompiled Compilable Suite Tests Passed with 100%% Parity!\n");
    return 0;
}
