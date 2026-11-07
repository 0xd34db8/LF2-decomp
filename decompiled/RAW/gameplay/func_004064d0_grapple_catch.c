/*
 * Procedure: FUN_004064d0
 * Address: 0x004064d0 - 0x00406a1f (Length: 1360 bytes)
 * Purpose: Grapple/caught handling, object holder synchronization and position updating
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



void FUN_004064d0(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int in_ECX;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar10;
  undefined8 uVar11;
  int local_10;
  int local_c;
  
  fVar10 = (float10)0;
  local_c = 0;
  piVar9 = (int *)(in_ECX + 0x194);
  do {
    if (0 < *(int *)(*piVar9 + 0x338)) {
      piVar6 = (int *)(*piVar9 + 0x338);
      *piVar6 = *piVar6 + -1;
    }
    if (*(char *)(local_c + 4 + in_ECX) == '\x01') {
      iVar8 = *piVar9;
      iVar2 = *(int *)(*(int *)(iVar8 + 0x368) + 0x6f4);
      if (((((iVar2 == 7) || (iVar2 == 8)) && (0 < *(int *)(iVar8 + 0x2fc))) &&
          ((*(int *)(*(int *)(iVar8 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar8 + 0x368)) == 2 &&
           (*(int *)(iVar8 + 0x338) == 0)))) &&
         ((*(int *)(iVar8 + 0x2fc) < 0xb1 || (DAT_00458428 == 1)))) {
        local_10 = 0;
        piVar6 = (int *)(in_ECX + 0x194);
        do {
          if (*(char *)(local_10 + 4 + in_ECX) == '\x01') {
            iVar8 = *piVar6;
            if (((((*(int *)(*(int *)(iVar8 + 0x368) + 0x6f4) ==
                    0xf - *(int *)(*(int *)(*piVar9 + 0x368) + 0x6f4)) &&
                  (iVar2 = *(int *)(iVar8 + 0x2fc), 0 < iVar2)) &&
                 (*(int *)(*piVar9 + 0x364) == *(int *)(iVar8 + 0x364))) &&
                ((*(int *)(iVar8 + 0x338) == 0 && ((iVar2 < 0xb1 || (DAT_00458428 == 1)))))) &&
               (((iVar3 = *(int *)(iVar8 + 0x70), -1 < iVar3 && (iVar3 < 400)) &&
                ((iVar3 = *(int *)(iVar3 * 0x178 + 0x7ac + *(int *)(iVar8 + 0x368)), iVar3 == 2 ||
                 (((iVar3 != 0xe && (*(int *)(iVar8 + 0x14) == 0)) && (9 < local_10)))))))) {
              iVar3 = *(int *)(*piVar9 + 0x10);
              iVar8 = *(int *)(iVar8 + 0x10);
              uVar11 = FUN_004034e0(iVar3 - iVar8);
              piVar6 = extraout_ECX;
              fVar10 = extraout_ST0;
              if ((((int)uVar11 < 0x32) &&
                  (iVar5 = FUN_004034e0(*(int *)(*piVar9 + 0x18) -
                                        *(int *)((int)((ulonglong)uVar11 >> 0x20) + 0x18)),
                  piVar6 = extraout_ECX_00, fVar10 = extraout_ST0_00, iVar5 < 8)) &&
                 (((iVar8 < iVar3 || (9 < local_10)) && (local_c < 10)))) {
                piVar7 = *(int **)(in_ECX + 0x7d4);
                piVar1 = piVar7 + 0x13608e0;
                iVar8 = 0;
                if (0 < *piVar1) {
                  do {
                    if (*(int *)(*piVar7 + 0x6f4) == 0x33) {
                      *(int *)(*piVar9 + 0x2fc) = *(int *)(*piVar9 + 0x2fc) + iVar2;
                      *(int *)(*piVar9 + 0x300) =
                           *(int *)(*piVar9 + 0x300) + *(int *)(*extraout_ECX_00 + 0x300);
                      iVar2 = *piVar9;
                      if (*(int *)(iVar2 + 0x304) < *(int *)(iVar2 + 0x300)) {
                        *(undefined4 *)(iVar2 + 0x300) = *(undefined4 *)(iVar2 + 0x304);
                      }
                      iVar2 = *piVar9;
                      if (*(int *)(iVar2 + 0x300) < *(int *)(iVar2 + 0x2fc)) {
                        *(undefined4 *)(iVar2 + 0x2fc) = *(undefined4 *)(iVar2 + 0x300);
                      }
                      *(undefined4 *)(*piVar9 + 0x70) = 0x122;
                      *(undefined4 *)(*piVar9 + 0x328) = 1;
                      *(double *)(*piVar9 + 0x40) = (double)extraout_ST0_00;
                      *(double *)(*extraout_ECX_00 + 0x48) = (double)extraout_ST0_00;
                      *(int *)(*piVar9 + 0x10) =
                           (*(int *)(*extraout_ECX_00 + 0x10) + *(int *)(*piVar9 + 0x10)) / 2;
                      *(int *)(*piVar9 + 0x18) =
                           (*(int *)(*extraout_ECX_00 + 0x18) + *(int *)(*piVar9 + 0x18)) / 2;
                      *(double *)(*piVar9 + 0x58) = (double)*(int *)(*piVar9 + 0x10);
                      *(double *)(*piVar9 + 0x68) = (double)*(int *)(*piVar9 + 0x18);
                      *(int *)(*piVar9 + 0x32c) = local_10;
                      *(undefined4 *)(*piVar9 + 0x338) = 0x1194;
                      *(undefined4 *)(*piVar9 + 0x330) =
                           *(undefined4 *)(*(int *)(*piVar9 + 0x368) + 0x6f4);
                      *(undefined4 *)(*piVar9 + 0x334) =
                           *(undefined4 *)(*(int *)(*extraout_ECX_00 + 0x368) + 0x6f4);
                      *(undefined4 *)(*piVar9 + 0x368) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar8 * 4);
                      *(undefined4 *)(*piVar9 + 0x308) = 500;
                      *(undefined1 *)(local_10 + 4 + in_ECX) = 0;
                      break;
                    }
                    iVar8 = iVar8 + 1;
                    piVar7 = piVar7 + 1;
                  } while (iVar8 < *piVar1);
                }
              }
            }
          }
          local_10 = local_10 + 1;
          piVar6 = piVar6 + 1;
        } while (local_10 < 0x14);
      }
      else {
        iVar8 = *piVar9;
        if ((((*(int *)(*(int *)(iVar8 + 0x368) + 0x6f4) == 0x33) && (*(int *)(iVar8 + 0x328) == 1))
            && ((*(int *)(iVar8 + 0x70) < 9 || (0x104 < *(int *)(iVar8 + 0x70))))) &&
           (*(int *)(iVar8 + 0x338) < 1)) {
          iVar2 = *(int *)(iVar8 + 0x32c);
          *(undefined4 *)(iVar8 + 0x328) = 0xffffffff;
          *(undefined4 *)(*piVar9 + 0x338) = 900;
          iVar8 = *(int *)(in_ECX + 0x7d4);
          local_10 = 0;
          if (0 < *(int *)(iVar8 + 0x4d82380)) {
            do {
              iVar8 = *(int *)(iVar8 + local_10 * 4);
              iVar3 = *piVar9;
              if (*(int *)(iVar8 + 0x6f4) == *(int *)(iVar3 + 0x330)) {
                *(int *)(iVar3 + 0x368) = iVar8;
              }
              else if (*(int *)(iVar8 + 0x6f4) == *(int *)(iVar3 + 0x334)) {
                iVar3 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
                FUN_004061d0();
                *(int *)(iVar3 + 0x368) = iVar8;
                uVar4 = *(undefined4 *)(iVar8 + 0x90);
                *(undefined8 *)(iVar3 + 0x58) = 0x4082200000000000;
                *(undefined4 *)(iVar3 + 0x31c) = uVar4;
                *(undefined8 *)(iVar3 + 0x60) = 0xc069000000000000;
                *(undefined8 *)(iVar3 + 0x68) = 0x4072c00000000000;
                *(undefined1 *)(iVar2 + 4 + in_ECX) = 1;
                fVar10 = (float10)0;
              }
              iVar8 = *(int *)(in_ECX + 0x7d4);
              local_10 = local_10 + 1;
            } while (local_10 < *(int *)(iVar8 + 0x4d82380));
          }
          *(int *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x2fc) = *(int *)(*piVar9 + 0x2fc) / 2;
          *(int *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x300) = *(int *)(*piVar9 + 0x300) / 2;
          *(int *)(*piVar9 + 0x2fc) = *(int *)(*piVar9 + 0x2fc) / 2;
          *(int *)(*piVar9 + 0x300) = *(int *)(*piVar9 + 0x300) / 2;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x10) =
               *(undefined4 *)(*piVar9 + 0x10);
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x18) =
               *(undefined4 *)(*piVar9 + 0x18);
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x14) = 0;
          iVar8 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
          *(double *)(iVar8 + 0x58) = (double)*(int *)(iVar8 + 0x10);
          iVar8 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
          *(double *)(iVar8 + 0x68) = (double)*(int *)(iVar8 + 0x18);
          *(double *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x60) = (double)fVar10;
          *(double *)(*piVar9 + 0x40) = (double)fVar10;
          *(double *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x40) = (double)fVar10;
          *(char *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x80) =
               '\x01' - *(char *)(*piVar9 + 0x80);
          *(undefined4 *)(*piVar9 + 0x70) = 0x70;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x70) = 0x70;
          *(undefined4 *)(*piVar9 + 0x308) = 0;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x308) = 0;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x364) =
               *(undefined4 *)(*piVar9 + 0x364);
        }
      }
    }
    local_c = local_c + 1;
    piVar9 = piVar9 + 1;
    if (0x13 < local_c) {
      return;
    }
  } while( true );
}

