/* Function: FUN_00406ba0 */
/* Address: 0x00406ba0 */

void FUN_00406ba0(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  double dVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int in_ECX;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar8;
  int iVar9;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  undefined8 uVar13;
  int *local_6a8;
  int local_6a4;
  int *local_6a0;
  int *local_69c;
  int *local_698;
  int local_694;
  int local_690;
  int *local_68c;
  int local_688;
  int local_684;
  undefined4 auStack_680 [415];
  
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar9 = *(int *)(*(int *)(iVar8 + 0x70) * 0x178 + 0x7d4 + *(int *)(iVar8 + 0x368));
  if (iVar9 == 0xb) {
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x6d,*(undefined4 *)(iVar8 + 0x364),
                 *(undefined4 *)(iVar8 + 0x10),*(undefined4 *)(iVar8 + 0x14),
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),
                 (int)*(char *)(iVar8 + 0x80));
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xdd,*(undefined4 *)(iVar8 + 0x354),0x51,*(undefined4 *)(iVar8 + 0x364),
                 *(undefined4 *)(iVar8 + 0x10),*(int *)(iVar8 + 0x14) + -100,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),
                 (int)*(char *)(iVar8 + 0x80));
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + 0x50,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(double *)(iVar8 + 0x50) - 7.0,0);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + 100,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),0);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + 0x50,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(double *)(iVar8 + 0x50) + 7.0,0);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + -0x50,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(double *)(iVar8 + 0x50) - 7.0,1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + -100,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd4,*(undefined4 *)(iVar8 + 0x354),100,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + -0x50,*(int *)(iVar8 + 0x14) + -3,
                 *(undefined4 *)(iVar8 + 0x18),*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(double *)(iVar8 + 0x50) + 7.0,1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + -0x1e,*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + -5,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + 0x1e,*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + -5,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + -0x1e,*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + 2,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),0);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(int *)(iVar8 + 0x10) + 0x1e,*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + 2,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),0);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(undefined4 *)(iVar8 + 0x10),*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + -9,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),1);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    FUN_00406a20(0xd3,*(undefined4 *)(iVar8 + 0x354),0x32,*(undefined4 *)(iVar8 + 0x364),
                 *(undefined4 *)(iVar8 + 0x10),*(int *)(iVar8 + 0x14) + -1,
                 *(int *)(iVar8 + 0x18) + 6,*(undefined8 *)(iVar8 + 0x40),
                 *(undefined8 *)(iVar8 + 0x48),*(undefined8 *)(iVar8 + 0x50),0);
    *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
  }
  else {
    if (iVar9 == 8) {
      local_6a8 = (int *)(in_ECX + 0x198);
      iVar9 = 0;
      pcVar4 = (char *)(in_ECX + 5);
      do {
        if ((((pcVar4[-1] != '\0') && (*(int *)(*(int *)(local_6a8[-1] + 0x368) + 0x6f8) == 0)) &&
            (*(int *)(local_6a8[-1] + 0x364) != *(int *)(iVar8 + 0x364))) &&
           (0 < *(int *)(local_6a8[-1] + 0x2fc))) {
          auStack_680[iVar9] = pcVar4 + (-5 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if (((*pcVar4 != '\0') && (*(int *)(*(int *)(*local_6a8 + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(*local_6a8 + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(*local_6a8 + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-4 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if (((pcVar4[1] != '\0') && (*(int *)(*(int *)(local_6a8[1] + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(local_6a8[1] + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(local_6a8[1] + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-3 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if ((((pcVar4[2] != '\0') && (*(int *)(*(int *)(local_6a8[2] + 0x368) + 0x6f8) == 0)) &&
            (*(int *)(local_6a8[2] + 0x364) != *(int *)(iVar8 + 0x364))) &&
           (0 < *(int *)(local_6a8[2] + 0x2fc))) {
          auStack_680[iVar9] = pcVar4 + (-2 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if (((pcVar4[3] != '\0') && (*(int *)(*(int *)(local_6a8[3] + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(local_6a8[3] + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(local_6a8[3] + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-1 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        local_6a8 = local_6a8 + 5;
        pcVar4 = pcVar4 + 5;
      } while ((int)(pcVar4 + (-5 - in_ECX)) < 400);
      local_698 = (int *)0x3;
      if (4 < iVar9) {
        local_698 = (int *)((iVar9 + -3) / 2 + 3);
      }
      if (0 < (int)local_698) {
        do {
          iVar8 = -1;
          iVar5 = 0x32;
          do {
            if (*(char *)(iVar5 + 4 + in_ECX) == '\0') {
              iVar8 = iVar5;
              break;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 < 400);
          if (iVar8 != -1) {
            piVar1 = *(int **)(in_ECX + 0x7d4);
            iVar5 = 0;
            if (0 < piVar1[0x13608e0]) {
              local_69c = piVar1;
              do {
                if (*(int *)(*local_69c + 0x6f4) == 0xe1) {
                  if (iVar5 != -1) {
                    iVar5 = piVar1[iVar5];
                    iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    FUN_004061d0();
                    *(int *)(iVar6 + 0x368) = iVar5;
                    uVar2 = *(undefined4 *)(iVar5 + 0x90);
                    *(undefined8 *)(iVar6 + 0x58) = 0x4082200000000000;
                    *(undefined4 *)(iVar6 + 0x31c) = uVar2;
                    *(undefined8 *)(iVar6 + 0x60) = 0xc069000000000000;
                    *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x14) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x18) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x60) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x60);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x68) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0;
                    iVar5 = FUN_00417170();
                    *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) =
                         (double)(iVar5 + -0xb);
                    iVar5 = FUN_00417170();
                    *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x48) =
                         3.0 - (double)iVar5 * 0.25;
                    iVar5 = FUN_00417170();
                    *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x50) =
                         3.0 - (double)iVar5 * 0.25;
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) =
                         *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80);
                    if (iVar9 == 0) {
                      *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x3f8) = param_1;
                    }
                    else {
                      iVar5 = FUN_00417170();
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x3f8) =
                           auStack_680[iVar5];
                    }
                    *(undefined1 *)(iVar8 + 4 + in_ECX) = 1;
                  }
                  break;
                }
                local_69c = local_69c + 1;
                iVar5 = iVar5 + 1;
              } while (iVar5 < piVar1[0x13608e0]);
            }
          }
          local_698 = (int *)((int)local_698 + -1);
        } while (local_698 != (int *)0x0);
      }
      *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
      return;
    }
    if (iVar9 == 0xd) {
      local_6a8 = (int *)(in_ECX + 0x198);
      iVar9 = 0;
      pcVar4 = (char *)(in_ECX + 5);
      do {
        if (((pcVar4[-1] != '\0') && (*(int *)(*(int *)(local_6a8[-1] + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(local_6a8[-1] + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(local_6a8[-1] + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-5 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if ((((*pcVar4 != '\0') && (*(int *)(*(int *)(*local_6a8 + 0x368) + 0x6f8) == 0)) &&
            (*(int *)(*local_6a8 + 0x364) != *(int *)(iVar8 + 0x364))) &&
           (0 < *(int *)(*local_6a8 + 0x2fc))) {
          auStack_680[iVar9] = pcVar4 + (-4 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if (((pcVar4[1] != '\0') && (*(int *)(*(int *)(local_6a8[1] + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(local_6a8[1] + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(local_6a8[1] + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-3 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if (((pcVar4[2] != '\0') && (*(int *)(*(int *)(local_6a8[2] + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(local_6a8[2] + 0x364) != *(int *)(iVar8 + 0x364) &&
            (0 < *(int *)(local_6a8[2] + 0x2fc))))) {
          auStack_680[iVar9] = pcVar4 + (-2 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        if ((((pcVar4[3] != '\0') && (*(int *)(*(int *)(local_6a8[3] + 0x368) + 0x6f8) == 0)) &&
            (*(int *)(local_6a8[3] + 0x364) != *(int *)(iVar8 + 0x364))) &&
           (0 < *(int *)(local_6a8[3] + 0x2fc))) {
          auStack_680[iVar9] = pcVar4 + (-1 - in_ECX);
          iVar9 = iVar9 + 1;
        }
        local_6a8 = local_6a8 + 5;
        pcVar4 = pcVar4 + 5;
      } while ((int)(pcVar4 + (-5 - in_ECX)) < 400);
      iVar8 = -1;
      iVar5 = 0x32;
      do {
        if (*(char *)(iVar5 + 4 + in_ECX) == '\0') {
          iVar8 = iVar5;
          break;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 400);
      if (iVar8 != -1) {
        local_698 = *(int **)(in_ECX + 0x7d4);
        piVar1 = local_698 + 0x13608e0;
        iVar5 = 0;
        if (0 < *piVar1) {
          while (*(int *)(*local_698 + 0x6f4) != 0xe4) {
            iVar5 = iVar5 + 1;
            local_698 = local_698 + 1;
            if (*piVar1 <= iVar5) {
              *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
              return;
            }
          }
          if (iVar5 != -1) {
            iVar5 = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar5 * 4);
            iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            FUN_004061d0();
            *(int *)(iVar6 + 0x368) = iVar5;
            uVar2 = *(undefined4 *)(iVar5 + 0x90);
            *(undefined8 *)(iVar6 + 0x58) = 0x4082200000000000;
            *(undefined4 *)(iVar6 + 0x31c) = uVar2;
            *(undefined8 *)(iVar6 + 0x60) = 0xc069000000000000;
            *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                 *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) =
                 *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
            iVar5 = FUN_00417170();
            *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x14) =
                 iVar5 + -3 + *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x18) =
                 *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                 *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
            *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                 *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58);
            *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x60) =
                 *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x60);
            *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x68) =
                 *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68);
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0;
            *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) =
                 *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40);
            iVar5 = FUN_00417170();
            *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x50) =
                 (3.0 - (double)iVar5 * 0.25) +
                 *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x50);
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) =
                 *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80);
            if (iVar9 == 0) {
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x3f8) = param_1;
              *(undefined1 *)(iVar8 + 4 + in_ECX) = 1;
              *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
              return;
            }
            iVar9 = FUN_00417170();
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x3f8) = auStack_680[iVar9];
            *(undefined1 *)(iVar8 + 4 + in_ECX) = 1;
          }
        }
      }
      *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
      return;
    }
    if (iVar9 == 5) {
      local_69c = (int *)(in_ECX + 0x194);
      local_694 = 0;
      do {
        if (((*(char *)(local_694 + 4 + in_ECX) == '\x01') &&
            (iVar8 = *local_69c, *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
           ((*(int *)(iVar8 + 0x364) == *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364) &&
            (0 < *(int *)(iVar8 + 0x2fc))))) {
          iVar8 = -1;
          iVar9 = 0x32;
          do {
            if (*(char *)(iVar9 + 4 + in_ECX) == '\0') {
              iVar8 = iVar9;
              break;
            }
            iVar9 = iVar9 + 1;
          } while (iVar9 < 400);
          if (iVar8 != -1) {
            piVar1 = *(int **)(in_ECX + 0x7d4);
            iVar9 = 0;
            if (0 < piVar1[0x13608e0]) {
              local_6a0 = piVar1;
              do {
                if (*(int *)(*local_6a0 + 0x6f4) == 0xdb) {
                  if (iVar9 != -1) {
                    iVar9 = piVar1[iVar9];
                    iVar5 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    FUN_004061d0();
                    *(int *)(iVar5 + 0x368) = iVar9;
                    uVar2 = *(undefined4 *)(iVar9 + 0x90);
                    *(undefined8 *)(iVar5 + 0x58) = 0x4082200000000000;
                    *(undefined4 *)(iVar5 + 0x31c) = uVar2;
                    *(undefined8 *)(iVar5 + 0x60) = 0xc069000000000000;
                    *(undefined8 *)(iVar5 + 0x68) = 0x4072c00000000000;
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x14) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x18) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x60) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x60);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x68) =
                         *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0;
                    iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    *(double *)(iVar9 + 0x40) =
                         (double)((*(int *)(*local_69c + 0x10) - *(int *)(iVar9 + 0x10)) / 0x32);
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x48) = 0;
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x50) = 0;
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) = 0;
                    *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x3f8) = local_694;
                    *(undefined1 *)(iVar8 + 4 + in_ECX) = 1;
                  }
                  break;
                }
                local_6a0 = local_6a0 + 1;
                iVar9 = iVar9 + 1;
              } while (iVar9 < piVar1[0x13608e0]);
            }
          }
        }
        local_69c = local_69c + 1;
        local_694 = local_694 + 1;
        if (399 < local_694) {
          *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
          return;
        }
      } while( true );
    }
    if ((iVar9 == 6) || (iVar9 == 9)) {
      local_684 = 0;
      if (iVar9 == 9) {
        local_684 = 4;
      }
      local_69c = (int *)0x0;
      local_698 = (int *)0xa;
      if (iVar9 == 6) {
        local_698 = (int *)0x7;
      }
      local_688 = 0;
      do {
        local_68c = (int *)(in_ECX + 0x194);
        local_694 = 0;
        do {
          if ((((*(char *)(local_694 + 4 + in_ECX) == '\x01') &&
               (iVar8 = *local_68c, *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
              (*(int *)(iVar8 + 0x364) != *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364)))
             && ((0 < *(int *)(iVar8 + 0x2fc) && (((int)local_69c < local_684 || (local_688 == 0))))
                )) {
            local_69c = (int *)((int)local_69c + 1);
            local_690 = -1;
            iVar8 = 0x32;
            do {
              if (*(char *)(iVar8 + 4 + in_ECX) == '\0') {
                local_690 = iVar8;
                break;
              }
              iVar8 = iVar8 + 1;
            } while (iVar8 < 400);
            if (local_690 != -1) {
              if (iVar9 == 6) {
                local_6a4 = 0xdc;
              }
              else if (iVar9 == 9) {
                iVar8 = FUN_00417170();
                local_6a4 = iVar8 + 0xdd;
              }
              local_6a0 = *(int **)(in_ECX + 0x7d4);
              piVar1 = local_6a0 + 0x13608e0;
              iVar8 = 0;
              if (0 < *piVar1) {
                do {
                  if (*(int *)(*local_6a0 + 0x6f4) == local_6a4) {
                    if (iVar8 != -1) {
                      iVar8 = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar8 * 4);
                      iVar5 = *(int *)(in_ECX + 0x194 + local_690 * 4);
                      FUN_004061d0();
                      *(int *)(iVar5 + 0x368) = iVar8;
                      uVar2 = *(undefined4 *)(iVar8 + 0x90);
                      *(undefined8 *)(iVar5 + 0x58) = 0x4082200000000000;
                      *(undefined4 *)(iVar5 + 0x31c) = uVar2;
                      *(undefined8 *)(iVar5 + 0x60) = 0xc069000000000000;
                      *(undefined8 *)(iVar5 + 0x68) = 0x4072c00000000000;
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x354) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x10) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x14) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x18) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x364) =
                           *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                      *(undefined8 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x58) =
                           *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58);
                      *(undefined8 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x60) =
                           *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x60);
                      *(undefined8 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x68) =
                           *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x70) = 0;
                      if (iVar9 == 6) {
                        iVar8 = *(int *)(in_ECX + 0x194 + local_690 * 4);
                        *(double *)(iVar8 + 0x40) =
                             (double)((*(int *)(*local_68c + 0x10) - *(int *)(iVar8 + 0x10)) / 0x32)
                        ;
                        iVar8 = FUN_00417170();
                        *(double *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x48) =
                             (double)(-4 - iVar8);
                      }
                      else if (iVar9 == 9) {
                        iVar8 = FUN_00417170();
                        *(double *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x40) =
                             (double)(iVar8 + -0xb);
                        iVar8 = FUN_00417170();
                        *(double *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x48) =
                             -2.0 - (double)iVar8 / 6.0;
                      }
                      *(undefined8 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x50) = 0;
                      *(undefined1 *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x80) = 0;
                      *(int *)(*(int *)(in_ECX + 0x194 + local_690 * 4) + 0x3f8) = local_694;
                      *(undefined1 *)(local_690 + 4 + in_ECX) = 1;
                    }
                    break;
                  }
                  local_6a0 = local_6a0 + 1;
                  iVar8 = iVar8 + 1;
                } while (iVar8 < *piVar1);
              }
            }
            if ((int)local_698 <= (int)local_69c) break;
          }
          local_694 = local_694 + 1;
          local_68c = local_68c + 1;
        } while (local_694 < 400);
        local_688 = local_688 + 1;
        if (((local_684 <= (int)local_69c) || (local_69c == (int *)0x0)) ||
           ((local_690 == -1 || ((int)local_698 <= (int)local_69c)))) {
          *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
          return;
        }
      } while( true );
    }
    if (iVar9 == 7) {
      iVar5 = -1;
      iVar6 = 0x32;
      do {
        if (*(char *)(iVar6 + 4 + in_ECX) == '\0') {
          iVar5 = iVar6;
          break;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < 400);
      if (iVar5 != -1) {
        iVar6 = *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380);
        iVar7 = 0;
        if (0 < iVar6) {
          local_6a0 = *(int **)(in_ECX + 0x7d4);
          do {
            if (*(int *)(*local_6a0 + 0x6f4) == *(int *)(*(int *)(iVar8 + 0x368) + 0x6f4)) {
              if (iVar7 != -1) {
                iVar8 = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar7 * 4);
                iVar6 = *(int *)(in_ECX + 0x194 + iVar5 * 4);
                FUN_004061d0();
                *(int *)(iVar6 + 0x368) = iVar8;
                uVar2 = *(undefined4 *)(iVar8 + 0x90);
                *(undefined8 *)(iVar6 + 0x58) = 0x4082200000000000;
                *(undefined4 *)(iVar6 + 0x31c) = uVar2;
                *(undefined8 *)(iVar6 + 0x60) = 0xc069000000000000;
                *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x354) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x14) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x58) =
                     *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58);
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x60) =
                     *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x60);
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x68) =
                     *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x70) = 0x28;
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x40) = 0;
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x48) = 0;
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x50) = 0;
                *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x80) = 0;
                *(undefined1 *)(iVar5 + 4 + in_ECX) = 1;
              }
              break;
            }
            local_6a0 = local_6a0 + 1;
            iVar7 = iVar7 + 1;
          } while (iVar7 < iVar6);
        }
      }
    }
    else if (iVar9 == 10) {
      fVar10 = (float10)0;
      if (fVar10 <= (float10)*(double *)(iVar8 + 0x40)) {
        dVar3 = *(double *)(iVar8 + 0x40) + 1.1;
      }
      else {
        dVar3 = *(double *)(iVar8 + 0x40) - 1.1;
      }
      *(double *)(iVar8 + 0x40) = dVar3;
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (30.0 < *(double *)(iVar8 + 0x40)) {
        *(undefined8 *)(iVar8 + 0x40) = 0x403e000000000000;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(double *)(iVar8 + 0x40) < -30.0) {
        *(undefined8 *)(iVar8 + 0x40) = 0xc03e000000000000;
      }
      dVar3 = 3.0;
      goto LAB_00407f86;
    }
  }
  fVar10 = (float10)0;
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar5 = *(int *)(iVar8 + 0x2f8);
  local_698 = (int *)0x2710;
  local_6a0 = (int *)0xffffffff;
  if ((-1 < iVar5) && (*(char *)(iVar5 + 4 + in_ECX) == '\x01')) {
    local_6a0 = *(int **)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x364);
  }
  if ((((iVar9 != 4) && (iVar9 != 5)) && (iVar9 != 6)) && (iVar9 != 7)) {
    iVar8 = *(int *)(iVar8 + 0x3f8);
    if (((iVar8 != -1) && (*(char *)(iVar8 + 4 + in_ECX) != '\0')) &&
       ((iVar5 = *(int *)(in_ECX + 0x194 + iVar8 * 4), 0 < *(int *)(iVar5 + 0x2fc) &&
        (iVar8 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
        *(int *)(*(int *)(iVar8 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar8 + 0x368)) != 0xe)))) {
      uVar13 = FUN_004034e0(*(undefined4 *)(iVar5 + 8));
      iVar8 = (int)((ulonglong)uVar13 >> 0x20);
      fVar10 = extraout_ST0;
      if ((((int)uVar13 < 3) && (*(int *)(extraout_ECX + 0x364) != *(int *)(iVar8 + 0x364))) &&
         (local_6a0 != (int *)*(int *)(extraout_ECX + 0x364))) goto LAB_00407fcf;
    }
    local_69c = (int *)(in_ECX + 0x194);
    local_694 = 0;
    do {
      if ((local_694 != param_1) && (*(char *)(local_694 + 4 + in_ECX) != '\0')) {
        iVar8 = *local_69c;
        if (*(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0) {
          iVar5 = *(int *)(in_ECX + 0x194 + param_1 * 4);
          if ((*(int *)(iVar8 + 0x364) != *(int *)(iVar5 + 0x364)) &&
             (local_6a0 != (int *)*(int *)(iVar8 + 0x364))) {
            if (*(int *)(*(int *)(*local_69c + 0x70) * 0x178 + 0x7ac + *(int *)(*local_69c + 0x368))
                == 0xe) {
LAB_004071a0:
              if (*(int *)(iVar5 + 0x3f8) != -1) goto LAB_004071e5;
            }
            else {
              uVar13 = FUN_004034e0(*(undefined4 *)(iVar8 + 8));
              iVar5 = (int)((ulonglong)uVar13 >> 0x20);
              fVar10 = extraout_ST0_00;
              if (2 < (int)uVar13) goto LAB_004071a0;
            }
            if (0 < *(int *)(iVar8 + 0x2fc)) {
              FUN_004034e0(*(int *)(iVar8 + 0x18) - *(int *)(iVar5 + 0x18));
              uVar13 = FUN_004034e0();
              iVar8 = extraout_ECX_00 + (int)uVar13;
              fVar10 = extraout_ST0_01;
              if (iVar8 < (int)local_698) {
                *(int *)((int)((ulonglong)uVar13 >> 0x20) + 0x3f8) = local_694;
                local_698 = (int *)iVar8;
              }
            }
          }
        }
      }
LAB_004071e5:
      local_69c = local_69c + 1;
      local_694 = local_694 + 1;
    } while (local_694 < 400);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(iVar8 + 0x3f8) == -1) {
      *(undefined4 *)(iVar8 + 0x2fc) = 0;
      return;
    }
  }
LAB_00407fcf:
  iVar5 = *(int *)(iVar8 + 0x3f8);
  if (iVar9 == 1) {
    if (*(int *)(iVar8 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10)) {
      *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) + 0.85;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10) < *(int *)(iVar8 + 0x10)) {
      *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) - 0.85;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(iVar8 + 0x18) + 7 < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18)) {
      *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) + 0.3;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18) < *(int *)(iVar8 + 0x18) + -7) {
      *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) - 0.3;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    *(double *)(iVar8 + 0x48) = *(double *)(iVar8 + 0x48) / 1.4;
    iVar8 = *(int *)(in_ECX + 0x194 + iVar5 * 4);
    if (*(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0) {
      iVar9 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(double *)(iVar9 + 0x60) + 10.0 < *(double *)(iVar8 + 0x60)) {
        *(double *)(iVar9 + 0x60) = *(double *)(iVar9 + 0x60) + 1.2;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(double *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x60) <
          *(double *)(iVar8 + 0x60) + 10.0) {
        *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x60) - 1.2;
      }
    }
    else {
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (fVar10 < (float10)*(double *)(iVar8 + 0x60)) {
        *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x60) + 1.0;
      }
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (13.0 < *(double *)(iVar8 + 0x40)) {
      *(undefined8 *)(iVar8 + 0x40) = 0x402a000000000000;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(double *)(iVar8 + 0x40) < -13.0) {
      *(undefined8 *)(iVar8 + 0x40) = 0xc02a000000000000;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (2.0 < *(double *)(iVar8 + 0x50)) {
      *(undefined8 *)(iVar8 + 0x50) = 0x4000000000000000;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (-2.0 <= *(double *)(iVar8 + 0x50)) {
      dVar3 = 1.0;
    }
    else {
      *(undefined8 *)(iVar8 + 0x50) = 0xc000000000000000;
      dVar3 = 1.0;
    }
LAB_00407f86:
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (dVar3 < *(double *)(iVar8 + 0x60)) {
      *(double *)(iVar8 + 0x60) = dVar3;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if ((float10)*(double *)(iVar8 + 0x40) <= fVar10) {
      *(undefined1 *)(iVar8 + 0x80) = 1;
      return;
    }
    *(undefined1 *)(iVar8 + 0x80) = 0;
    return;
  }
  if (iVar9 == 4) {
    iVar6 = *(int *)(in_ECX + 0x194 + iVar5 * 4);
    if (0 < *(int *)(iVar6 + 0x2fc)) {
      iVar6 = *(int *)(iVar6 + 0x10);
      if ((iVar6 + -0x1e < *(int *)(iVar8 + 0x10)) && (*(int *)(iVar8 + 0x10) < iVar6 + 0x1e)) {
        iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x14);
        if ((iVar6 + -0x50 < *(int *)(iVar8 + 0x14)) && (*(int *)(iVar8 + 0x14) < iVar6)) {
          iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18);
          if ((iVar6 + -10 < *(int *)(iVar8 + 0x18)) && (*(int *)(iVar8 + 0x18) < iVar6 + 10)) {
            *(double *)(iVar8 + 0x40) = (double)fVar10;
            *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = (double)fVar10;
            *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x50) = (double)fVar10;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x3c;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0xe4) = 100;
            return;
          }
        }
      }
    }
LAB_00408263:
    if ((0 < *(int *)(iVar8 + 0x2fc)) && (*(char *)(param_1 + 4 + in_ECX) == '\x01')) {
      if (*(int *)(iVar8 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10)) {
        *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) + 0.7;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10) < *(int *)(iVar8 + 0x10)) {
        *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) - 0.7;
      }
      if (iVar9 == 7) {
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        if (*(int *)(iVar8 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10)) {
          *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) + 0.7;
        }
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10) < *(int *)(iVar8 + 0x10)) {
          *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) - 0.7;
        }
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(int *)(iVar8 + 0x18) + 5 < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18)) {
        *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) + 0.4;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18) < *(int *)(iVar8 + 0x18) + -5) {
        *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) - 0.4;
      }
      if (((iVar9 == 2) || (iVar9 == 4)) || (iVar9 == 0xc)) {
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        *(double *)(iVar8 + 0x48) = *(double *)(iVar8 + 0x48) / 1.4;
        iVar8 = *(int *)(in_ECX + 0x194 + iVar5 * 4);
        if (*(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0) {
          iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
          if (*(double *)(iVar6 + 0x60) + 40.0 < *(double *)(iVar8 + 0x60)) {
            *(double *)(iVar6 + 0x60) = *(double *)(iVar6 + 0x60) + 1.0;
          }
          iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
          if (*(double *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x60) <
              *(double *)(iVar8 + 0x60) + 40.0) {
            *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x60) - 1.0;
          }
        }
        else {
          iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
          if (fVar10 < (float10)*(double *)(iVar8 + 0x60)) {
            *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x60) + 1.0;
          }
        }
      }
      else if (iVar9 == 7) {
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        if (*(double *)(iVar8 + 0x48) < 4.0) {
          *(double *)(iVar8 + 0x48) = *(double *)(iVar8 + 0x48) + 0.4;
        }
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x48) + *(double *)(iVar8 + 0x60);
        iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
        if (-0x19 < *(int *)(iVar8 + 0x14)) {
          *(undefined4 *)(iVar8 + 0x70) = 0x3c;
          *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x50) = (double)fVar10;
          *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar10;
          *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = (double)fVar10;
        }
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      fVar11 = (float10)14.0;
      if (fVar11 < (float10)*(double *)(iVar8 + 0x40)) {
        *(double *)(iVar8 + 0x40) = (double)fVar11;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(double *)(iVar8 + 0x40) < -14.0) {
        *(undefined8 *)(iVar8 + 0x40) = 0xc02c000000000000;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (1.4 < *(double *)(iVar8 + 0x60)) {
        *(undefined8 *)(iVar8 + 0x60) = 0x3ff6666666666666;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (iVar9 == 0xe) {
        if (1.5 < *(double *)(iVar8 + 0x50)) {
          *(undefined8 *)(iVar8 + 0x50) = 0x3ff8000000000000;
        }
        dVar3 = -1.5;
      }
      else if (*(double *)(iVar8 + 0x50) <= 2.2) {
        dVar3 = -2.2;
      }
      else {
        *(undefined8 *)(iVar8 + 0x50) = 0x400199999999999a;
        dVar3 = -2.2;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if (*(double *)(iVar8 + 0x50) < dVar3) {
        *(double *)(iVar8 + 0x50) = dVar3;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      if ((float10)*(double *)(iVar8 + 0x40) <= fVar10) {
        *(undefined1 *)(iVar8 + 0x80) = 1;
      }
      else {
        *(undefined1 *)(iVar8 + 0x80) = 0;
      }
      iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      fVar12 = (float10)*(double *)(iVar8 + 0x40);
      if (fVar12 < fVar10) {
        fVar12 = -fVar12;
      }
      if (iVar9 != 2) {
        if (iVar9 != 0xe) {
          return;
        }
        if ((float10)8.0 <= fVar12) {
          if (*(int *)(iVar8 + 0x70) < 0x29) {
            return;
          }
          *(int *)(iVar8 + 0x70) = *(int *)(iVar8 + 0x70) + -0x32;
          return;
        }
        if (*(int *)(iVar8 + 0x70) < 10) {
          *(int *)(iVar8 + 0x70) = *(int *)(iVar8 + 0x70) + 0x32;
          return;
        }
        return;
      }
      if (fVar12 <= fVar11) goto LAB_004085bb;
      goto LAB_00408594;
    }
  }
  else if ((((iVar9 == 0xe) || (iVar9 == 0xc)) || (iVar9 == 2)) || (iVar9 == 7)) goto LAB_00408263;
  if (((((iVar9 != 0xe) && (iVar9 != 0xc)) && (iVar9 != 2)) && ((iVar9 != 4 && (iVar9 != 7)))) ||
     ((0 < *(int *)(iVar8 + 0x2fc) && (*(char *)(param_1 + 4 + in_ECX) != '\0')))) {
    if (iVar9 != 3) {
      return;
    }
    if (*(int *)(iVar8 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10)) {
      *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) + 0.7;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x10) < *(int *)(iVar8 + 0x10)) {
      *(double *)(iVar8 + 0x40) = *(double *)(iVar8 + 0x40) - 0.7;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(iVar8 + 0x18) + 10 < *(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18)) {
      *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) + 0.17;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(int *)(*(int *)(in_ECX + 0x194 + iVar5 * 4) + 0x18) < *(int *)(iVar8 + 0x18) + -10) {
      *(double *)(iVar8 + 0x50) = *(double *)(iVar8 + 0x50) - 0.17;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (16.0 < *(double *)(iVar8 + 0x40)) {
      *(undefined8 *)(iVar8 + 0x40) = 0x4030000000000000;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(double *)(iVar8 + 0x40) < -16.0) {
      *(undefined8 *)(iVar8 + 0x40) = 0xc030000000000000;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (2.4 < *(double *)(iVar8 + 0x50)) {
      *(undefined8 *)(iVar8 + 0x50) = 0x4003333333333333;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(double *)(iVar8 + 0x50) < -2.4) {
      *(undefined8 *)(iVar8 + 0x50) = 0xc003333333333333;
      return;
    }
    return;
  }
  if (fVar10 <= (float10)*(double *)(iVar8 + 0x40)) {
    dVar3 = *(double *)(iVar8 + 0x40) + 2.0;
  }
  else {
    dVar3 = *(double *)(iVar8 + 0x40) - 2.0;
  }
  *(double *)(iVar8 + 0x40) = dVar3;
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  if (17.0 < *(double *)(iVar8 + 0x40)) {
    *(undefined8 *)(iVar8 + 0x40) = 0x4031000000000000;
  }
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  if (*(double *)(iVar8 + 0x40) < -17.0) {
    *(undefined8 *)(iVar8 + 0x40) = 0xc031000000000000;
  }
  if (((iVar9 == 2) || (iVar9 == 4)) || ((iVar9 == 0xe || (iVar9 == 0xc)))) {
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (1.4 < *(double *)(iVar8 + 0x60)) {
      *(undefined8 *)(iVar8 + 0x60) = 0x3ff6666666666666;
    }
  }
  else if (iVar9 == 7) {
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (*(double *)(iVar8 + 0x48) < 4.0) {
      *(double *)(iVar8 + 0x48) = *(double *)(iVar8 + 0x48) + 0.4;
    }
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    *(double *)(iVar8 + 0x60) = *(double *)(iVar8 + 0x48) + *(double *)(iVar8 + 0x60);
    iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    if (-0x19 < *(int *)(iVar8 + 0x14)) {
      *(undefined4 *)(iVar8 + 0x70) = 0x3c;
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) = 0xffffffe7;
      *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x50) = (double)fVar10;
      *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar10;
      *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = (double)fVar10;
    }
  }
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  if ((float10)*(double *)(iVar8 + 0x40) <= fVar10) {
    *(undefined1 *)(iVar8 + 0x80) = 1;
  }
  else {
    *(undefined1 *)(iVar8 + 0x80) = 0;
  }
  iVar8 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  fVar12 = (float10)*(double *)(iVar8 + 0x40);
  if (fVar12 < fVar10) {
    fVar12 = -fVar12;
  }
  if (iVar9 != 2) {
    return;
  }
  if (fVar12 <= (float10)14.0) {
LAB_004085bb:
    iVar9 = *(int *)(iVar8 + 0x70);
    if (fVar12 <= (float10)7.0) {
      if (iVar9 == 1) {
        return;
      }
      if (iVar9 == 2) {
        return;
      }
      *(undefined4 *)(iVar8 + 0x70) = 1;
      return;
    }
    if (iVar9 == 3) {
      return;
    }
    if (iVar9 == 4) {
      return;
    }
    *(undefined4 *)(iVar8 + 0x70) = 3;
    return;
  }
LAB_00408594:
  if ((*(int *)(iVar8 + 0x70) == 5) || (*(int *)(iVar8 + 0x70) == 6)) {
    return;
  }
  *(undefined4 *)(iVar8 + 0x70) = 5;
  return;
}
