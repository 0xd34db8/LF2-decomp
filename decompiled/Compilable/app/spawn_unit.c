#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

void FUN_00437400(int *param_1, int param_2)
{
    int *piVar1;
    int *piVar2;
    int iVar3;
    int iVar4;
    char *in_ecx = (char *)in_ECX;
    int iVar5;
    undefined4 uVar6;
    int *local_4;

    piVar2 = param_1;
    iVar5 = 0x14;
    while ((*(char *)(in_ecx + 4 + iVar5) != '\0' || ((&DAT_004514e0)[iVar5] != 0))) {
        iVar5 = iVar5 + 1;
        if (399 < iVar5) goto LAB_00437430;
    }
    piVar1 = param_1 + 0x2d;
    iVar3 = param_1[0x2b];
    param_1 = (int *)*piVar1;
    if (((_DAT_00450c30 == -1) || (_DAT_00450c30 == 2)) && (iVar3 != 300)) {
        param_1 = (int *)FUN_004450d0();
    }
    if (iVar3 == 1000) {
        if ((DAT_0044d34c == 10) || (DAT_0044d34c == -1)) {
            local_4 = (int *)0x32;
            do {
                iVar3 = FUN_00417170(0x10f, 10);
                iVar4 = FUN_00417170(0x110, 10);
                uVar6 = (&DAT_0044d324)[iVar3];
                local_4 = (int *)((int)(uintptr_t)local_4 - 1);
                (&DAT_0044d324)[iVar3] = (&DAT_0044d324)[iVar4];
                (&DAT_0044d324)[iVar4] = uVar6;
            } while (local_4 != (int *)0x0);
            DAT_0044d34c = 0;
        }
        iVar3 = (&DAT_0044d324)[DAT_0044d34c];
        DAT_0044d34c = DAT_0044d34c + 1;
    }
    else {
        if (iVar3 == 3000) {
            uVar6 = 0x111;
        }
        else {
            if (iVar3 != 0xbb9) goto LAB_00437558;
            iVar3 = FUN_00417170(0x112, 7);
            if (iVar3 == 0) {
                iVar3 = 0x20;
                param_1 = (int *)((uintptr_t)param_1 * 4);
                goto LAB_00437558;
            }
            uVar6 = 0x113;
        }
        iVar3 = FUN_00417170(uVar6, 2);
        iVar3 = iVar3 + 0x1e;
    }
LAB_00437558:
    local_4 = *(int **)(in_ecx + 0x7d4);
    piVar1 = local_4 + 0x13608e0;
    iVar4 = 0;
    if (0 < *piVar1) {
        do {
            if (*(int *)(uintptr_t)(*local_4 + 0x6f4) == iVar3) {
                piVar2[param_2 + 3] = iVar5;
                *(undefined1 *)(iVar5 + 4 + (uintptr_t)in_ecx) = 1;
                iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                iVar4 = *(int *)(*(int *)(in_ecx + 0x7d4) + iVar4 * 4);
                FUN_004061d0();
                *(int *)(uintptr_t)(iVar3 + 0x368) = iVar4;
                uVar6 = *(undefined4 *)(uintptr_t)(iVar4 + 0x90);
                *(undefined8 *)(uintptr_t)(iVar3 + 0x58) = 0x4075e00000000000ULL;
                *(undefined4 *)(uintptr_t)(iVar3 + 0x31c) = uVar6;
                *(undefined8 *)(uintptr_t)(iVar3 + 0x60) = 0;
                *(undefined8 *)(uintptr_t)(iVar3 + 0x68) = 0x4072c00000000000ULL;
                iVar3 = FUN_00417170(0x114, *(int *)(*(int *)(in_ecx + 0x7d4) + 0x4d45db8 +
                                                   DAT_0044d024 * 0x990) -
                                           *(int *)(*(int *)(in_ecx + 0x7d4) + 0x4d45db4 +
                                                   DAT_0044d024 * 0x990));
                *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x18) =
                     iVar3 + *(int *)(DAT_0044d024 * 0x990 + 0x4d45db4 + *(int *)(in_ecx + 0x7d4));
                if (piVar2[0x2c] == -1000) {
                    iVar3 = FUN_00417170(0x116, 2);
                    if (iVar3 == 0) {
                        iVar3 = FUN_00417170(0x117, 300);
                        *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x10) = iVar3 + 0x96 + DAT_00450bb4;
                    }
                    else {
                        iVar3 = FUN_00417170(0x118, 300);
                        *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x10) = -0x96 - iVar3;
                    }
                }
                else {
                    iVar3 = FUN_00417170(0x115, 300);
                    *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x10) = iVar3 + piVar2[0x2c];
                }
                *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x30c) = piVar2[0x2f];
                *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x314) = piVar2[0x30];
                *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x310) = piVar2[0x31];
                iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                *(double *)(uintptr_t)(iVar3 + 0x58) = (double)*(int *)(uintptr_t)(iVar3 + 0x10);
                iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                *(double *)(uintptr_t)(iVar3 + 0x68) = (double)*(int *)(uintptr_t)(iVar3 + 0x18);
                *(undefined4 *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x308) = 500;
                *(int **)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x300) = param_1;
                *(int **)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x2fc) = param_1;
                *(int **)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x304) = param_1;
                *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x354) = iVar5;
                iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                iVar4 = *(int *)(*(int *)(uintptr_t)(iVar3 + 0x368) + 0x6f8);
                if ((iVar4 == 0) || (iVar4 == 5)) {
                    *(undefined4 *)(uintptr_t)(iVar3 + 8) = 0x14;
                    iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                    *(bool *)(uintptr_t)(iVar3 + 0x80) = DAT_00450bb4 - 0x31a < *(int *)(uintptr_t)(iVar3 + 0x10);
                    *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x70) = piVar2[0x32];
                    *(undefined4 *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x364) = 5;
                    *(int *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x14) = piVar2[0x33];
                    iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                    *(double *)(uintptr_t)(iVar3 + 0x60) = (double)*(int *)(uintptr_t)(iVar3 + 0x14);
                    *(undefined8 *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x48) = 0;
                }
                else {
                    *(undefined4 *)(uintptr_t)(iVar3 + 8) = 0;
                    *(undefined4 *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x364) = 0;
                    *(undefined4 *)(*(int *)(in_ecx + 0x194 + iVar5 * 4) + 0x14) = 0xfffffed4;
                    iVar3 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                    *(double *)(uintptr_t)(iVar3 + 0x60) = (double)*(int *)(uintptr_t)(iVar3 + 0x14);
                }
                iVar5 = *(int *)(in_ecx + 0x194 + iVar5 * 4);
                if (*(int *)(*(int *)(uintptr_t)(iVar5 + 0x368) + 0x6f4) == 0x7a) {
                    *(undefined4 *)(uintptr_t)(iVar5 + 0x2fc) = 200;
                }
                *piVar2 = *piVar2 + 1;
                return;
            }
            iVar4 = iVar4 + 1;
            local_4 = local_4 + 1;
        } while (iVar4 < *piVar1);
        piVar2[param_2 + 3] = -1;
        return;
    }
LAB_00437430:
    piVar2[param_2 + 3] = -1;
    return;
}

