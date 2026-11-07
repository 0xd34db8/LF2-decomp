/* Function: FUN_00417f80 */
/* Address: 0x00417f80 */

void FUN_00417f80(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int in_ECX;
  int iVar9;
  int *piVar10;
  float10 fVar11;
  float10 fVar12;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 extraout_ST1;
  int local_4;
  
  iVar9 = 0;
  piVar10 = (int *)(in_ECX + 0x194);
  do {
    if ((*(char *)(iVar9 + 4 + in_ECX) != '\0') &&
       (iVar3 = *piVar10, *(int *)(*(int *)(iVar3 + 0x368) + 0x6f8) == 0)) {
      dVar5 = (double)*(int *)(DAT_0044d024 * 0x990 + 0x4d45db4 + *(int *)(in_ECX + 0x7d4));
      if (*(double *)(iVar3 + 0x68) < dVar5) {
        *(double *)(iVar3 + 0x68) = dVar5;
      }
      dVar5 = (double)*(int *)(DAT_0044d024 * 0x990 + 0x4d45db8 + *(int *)(in_ECX + 0x7d4));
      if (dVar5 < *(double *)(*piVar10 + 0x68)) {
        *(double *)(*piVar10 + 0x68) = dVar5;
      }
      iVar3 = *piVar10;
      uVar6 = FUN_004450d0();
      *(undefined4 *)(iVar3 + 0x18) = uVar6;
    }
    iVar9 = iVar9 + 1;
    piVar10 = piVar10 + 1;
  } while (iVar9 < 400);
  fVar11 = (float10)-8.0;
  fVar12 = (float10)3.0;
  local_4 = 0;
  piVar10 = (int *)(in_ECX + 0x194);
  do {
    if ((*(char *)(local_4 + 4 + in_ECX) != '\0') && (iVar9 = *piVar10, *(int *)(iVar9 + 0x98) < 0))
    {
      uVar4 = *(uint *)(iVar9 + 0xa0);
      if ((uVar4 < 400) &&
         ((*(char *)(uVar4 + 4 + in_ECX) != '\0' &&
          (iVar3 = *(int *)(in_ECX + 0x194 + uVar4 * 4), local_4 == *(int *)(iVar3 + 0x9c))))) {
        if (*(int *)(*(int *)(iVar3 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar3 + 0x368)) == 0x11) {
          if ((*(int *)(*(int *)(iVar9 + 0x368) + 0x6f4) == 0x7a) && (0 < *(int *)(iVar9 + 0x2fc)))
          {
            *(int *)(iVar9 + 0x2fc) = *(int *)(iVar9 + 0x2fc) + -1;
            if (*(int *)(*piVar10 + 0x2fc) % 5 == 0) {
              piVar2 = (int *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x300);
              *piVar2 = *piVar2 + 2;
              piVar2 = (int *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x2fc);
              *piVar2 = *piVar2 + 4;
              iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
              if (*(int *)(iVar9 + 0x304) < *(int *)(iVar9 + 0x300)) {
                *(undefined4 *)(iVar9 + 0x300) = *(undefined4 *)(iVar9 + 0x304);
              }
              iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
              if (*(int *)(iVar9 + 0x300) < *(int *)(iVar9 + 0x2fc)) {
                *(undefined4 *)(iVar9 + 0x2fc) = *(undefined4 *)(iVar9 + 0x300);
              }
            }
            if (*(int *)(*piVar10 + 0x2fc) % 6 == 0) {
              piVar2 = (int *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x308);
              *piVar2 = *piVar2 + 5;
              iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
              if (500 < *(int *)(iVar9 + 0x308)) {
                *(undefined4 *)(iVar9 + 0x308) = 500;
              }
            }
            iVar9 = *piVar10;
            if (*(int *)(iVar9 + 0x2fc) < 1) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
              *(undefined4 *)(*piVar10 + 0x98) = 0;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x9c) = 0;
              *(undefined4 *)(*piVar10 + 0xa0) = 0;
              *(undefined4 *)(*piVar10 + 0x70) = 0;
              *(double *)(*piVar10 + 0x48) = (double)fVar11;
              iVar9 = FUN_00417170(0x88,7);
              *(double *)(*piVar10 + 0x40) = (double)(iVar9 + -3);
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x70) = 0;
              *(undefined4 *)(*piVar10 + 0x31c) = 0;
              fVar11 = extraout_ST0;
              goto LAB_004181f9;
            }
          }
          if ((*(int *)(*(int *)(iVar9 + 0x368) + 0x6f4) == 0x7b) && (0 < *(int *)(iVar9 + 0x2fc)))
          {
            *(int *)(*piVar10 + 0x2fc) = *(int *)(*piVar10 + 0x2fc) + -2;
            piVar2 = (int *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x308);
            *piVar2 = *piVar2 + 3;
            iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
            if (500 < *(int *)(iVar9 + 0x308)) {
              *(undefined4 *)(iVar9 + 0x308) = 500;
            }
            if ((-1 < *(int *)(*piVar10 + 0x2f4)) && (0x96 < *(int *)(*piVar10 + 0x308))) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x308) = 0x96;
            }
            if (*(int *)(*piVar10 + 0x2fc) < 1) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
              *(undefined4 *)(*piVar10 + 0x98) = 0;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x9c) = 0;
              *(undefined4 *)(*piVar10 + 0xa0) = 0;
              *(undefined4 *)(*piVar10 + 0x70) = 0;
              *(double *)(*piVar10 + 0x48) = (double)fVar11;
              iVar9 = FUN_00417170(0x89,7);
              *(double *)(*piVar10 + 0x40) = (double)(iVar9 + -3);
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x70) = 0;
              *(undefined4 *)(*piVar10 + 0x31c) = 0;
              fVar11 = extraout_ST0_00;
              goto LAB_004181f9;
            }
          }
        }
        iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
        piVar2 = (int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x87c + *(int *)(iVar9 + 0x368));
        *(int *)(*piVar10 + 0x70) = piVar2[3];
        *(undefined1 *)(*piVar10 + 0x80) =
             *(undefined1 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x80);
        *(undefined4 *)(*piVar10 + 0xb4) =
             *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0xb4);
        iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
        iVar7 = *(int *)(iVar9 + 0x70) * 0x178;
        iVar3 = *(int *)(iVar9 + 0x368);
        if (*(char *)(iVar9 + 0x80) == '\0') {
          iVar8 = (*(int *)(iVar9 + 0x10) - *(int *)(iVar3 + iVar7 + 0x7f4)) + piVar2[1];
        }
        else {
          iVar8 = (*(int *)(iVar3 + iVar7 + 0x7f4) - piVar2[1]) + *(int *)(iVar9 + 0x10);
        }
        iVar7 = (*(int *)(iVar9 + 0x14) - *(int *)(iVar3 + iVar7 + 0x7f8)) + piVar2[2];
        iVar9 = *(int *)(*piVar10 + 0x70) * 0x178 + 0x87c + *(int *)(*piVar10 + 0x368);
        iVar3 = *piVar10;
        if (*(char *)(iVar3 + 0x80) == '\0') {
          *(int *)(*piVar10 + 0x10) =
               (*(int *)(*(int *)(iVar3 + 0x70) * 0x178 + 0x7f4 + *(int *)(iVar3 + 0x368)) -
               *(int *)(iVar9 + 4)) + iVar8;
          *(int *)(*piVar10 + 0x14) =
               (*(int *)(*(int *)(*piVar10 + 0x70) * 0x178 + 0x7f8 + *(int *)(*piVar10 + 0x368)) -
               *(int *)(iVar9 + 8)) + iVar7;
        }
        else {
          *(int *)(*piVar10 + 0x10) =
               (*(int *)(iVar9 + 4) -
               *(int *)(*(int *)(*piVar10 + 0x70) * 0x178 + 0x7f4 + *(int *)(*piVar10 + 0x368))) +
               iVar8;
          iVar3 = *piVar10;
          *(int *)(iVar3 + 0x14) =
               (*(int *)(*(int *)(iVar3 + 0x70) * 0x178 + 0x7f8 + *(int *)(iVar3 + 0x368)) -
               *(int *)(iVar9 + 8)) + iVar7;
        }
        *(undefined4 *)(*piVar10 + 0x18) =
             *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x18);
        if (piVar2[5] == 0) {
          piVar1 = (int *)(*piVar10 + 0x18);
          *piVar1 = *piVar1 + 1;
          *(int *)(*piVar10 + 0x14) = *(int *)(*piVar10 + 0x14) + -1;
        }
        else {
          piVar1 = (int *)(*piVar10 + 0x18);
          *piVar1 = *piVar1 + -1;
          *(int *)(*piVar10 + 0x14) = *(int *)(*piVar10 + 0x14) + 1;
        }
        *(double *)(*piVar10 + 0x68) = (double)*(int *)(*piVar10 + 0x18);
        *(double *)(*piVar10 + 0x58) = (double)*(int *)(*piVar10 + 0x10);
        *(double *)(*piVar10 + 0x60) = (double)*(int *)(*piVar10 + 0x14);
        iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
        if ((*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) == 0xc) ||
           (iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4),
           *(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) == 10)) {
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
          *(undefined4 *)(*piVar10 + 0x98) = 0;
          uVar6 = FUN_00417170(0x8a,0x10);
          *(undefined4 *)(*piVar10 + 0x70) = uVar6;
          iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
          if (*(int *)(iVar9 + 0x20) == 1) {
            *(undefined8 *)(*piVar10 + 0x48) = *(undefined8 *)(iVar9 + 0x30);
            *(double *)(*piVar10 + 0x40) =
                 (double)((float10)*(double *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x28) / fVar12
                         );
          }
          else {
            *(undefined8 *)(*piVar10 + 0x48) = *(undefined8 *)(iVar9 + 0x48);
            *(double *)(*piVar10 + 0x40) =
                 (double)((float10)*(double *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x40) / fVar12
                         );
          }
          if (extraout_ST1 < (float10)*(double *)(*piVar10 + 0x60)) {
            *(double *)(*piVar10 + 0x60) = (double)extraout_ST1;
          }
        }
        if (piVar2[6] != 0) {
          iVar9 = *(int *)(*(int *)(*piVar10 + 0x368) + 0x6f8);
          if (((iVar9 == 1) || (iVar9 == 4)) || (iVar9 == 6)) {
            *(uint *)(*piVar10 + 0x2f8) = uVar4;
            *(undefined4 *)(*piVar10 + 0x70) = 0x28;
            if (*(char *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x80) == '\0') {
              iVar9 = piVar2[6];
            }
            else {
              iVar9 = -piVar2[6];
            }
            *(double *)(*piVar10 + 0x40) = (double)iVar9;
            *(double *)(*piVar10 + 0x48) = (double)piVar2[7];
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
            *(undefined4 *)(*piVar10 + 0x98) = 0;
            iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
            if (*(char *)(iVar9 + 0xcd) == '\0') {
LAB_0041862e:
              if (*(char *)(iVar9 + 0xce) != '\0') {
                *(double *)(*piVar10 + 0x50) = (double)piVar2[8];
              }
            }
            else if (*(char *)(iVar9 + 0xce) == '\0') {
              *(double *)(*piVar10 + 0x50) = (double)-piVar2[8];
            }
            else if (*(char *)(iVar9 + 0xcd) == '\0') goto LAB_0041862e;
          }
          if ((piVar2[6] != 0) && (*(int *)(*(int *)(*piVar10 + 0x368) + 0x6f8) == 2)) {
            uVar6 = FUN_00417170(0x8b,6);
            *(undefined4 *)(*piVar10 + 0x70) = uVar6;
            if (*(char *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x80) == '\0') {
              iVar9 = piVar2[6];
            }
            else {
              iVar9 = -piVar2[6];
            }
            *(double *)(*piVar10 + 0x40) = (double)iVar9;
            *(double *)(*piVar10 + 0x48) = (double)piVar2[7];
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
            *(undefined4 *)(*piVar10 + 0x98) = 0;
            iVar9 = *(int *)(in_ECX + 0x194 + uVar4 * 4);
            if ((*(char *)(iVar9 + 0xcd) == '\0') || (*(char *)(iVar9 + 0xce) != '\0')) {
              if ((*(char *)(iVar9 + 0xcd) == '\0') && (*(char *)(iVar9 + 0xce) != '\0')) {
                *(double *)(*piVar10 + 0x50) = (double)piVar2[8];
              }
            }
            else {
              *(double *)(*piVar10 + 0x50) = (double)-piVar2[8];
            }
          }
        }
        if (*piVar2 == 3) {
          *(undefined4 *)(*piVar10 + 0x98) = 0;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + uVar4 * 4) + 0x98) = 0;
          uVar6 = FUN_00417170(0x8c,6);
          *(undefined4 *)(*piVar10 + 0x70) = uVar6;
          iVar9 = FUN_00417170(0x8d,7);
          *(double *)(*piVar10 + 0x40) = (double)(iVar9 + -3);
          iVar9 = FUN_00417170(0x8e,4);
          *(double *)(*piVar10 + 0x48) = (double)-iVar9;
          iVar9 = FUN_00417170(0x8f,5);
          *(double *)(*piVar10 + 0x50) = (double)((float10)(iVar9 + -2) / extraout_ST0_01);
        }
      }
      else {
        *(undefined4 *)(iVar9 + 0x98) = 0;
      }
    }
LAB_004181f9:
    local_4 = local_4 + 1;
    piVar10 = piVar10 + 1;
    if (399 < local_4) {
      return;
    }
  } while( true );
}
