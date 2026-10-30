
void FUN_0042e100(int param_1)

{
  int iVar1;
  double dVar2;
  char cVar3;
  float10 fVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int in_ECX;
  int iVar9;
  int iVar10;
  int iVar11;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 extraout_ST0_01;
  float10 fVar12;
  undefined4 uVar13;
  int *local_74;
  int local_70;
  int *local_68;
  int local_64;
  int local_5c;
  int local_58 [4];
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar1 = *(int *)(iVar10 + 0x7c) * 0x178 + 0x7a4 + *(int *)(iVar10 + 0x368);
  local_5c = 0;
  if (0 < *(int *)(iVar10 + 0x2e4)) {
    fVar12 = (float10)0;
    while( true ) {
      iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar9 = (int)*(char *)(iVar10 + 0x2d0 + local_5c);
      if (*(int *)(iVar1 + 0x128) + -1 < iVar9) break;
      iVar8 = *(int *)(iVar10 + 0x280 + local_5c * 4);
      iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
      iVar10 = *(int *)(iVar6 + 0x7c) * 0x178 + 0x7a4 + *(int *)(iVar6 + 0x368);
      if (*(char *)(iVar6 + 0xf0 + param_1) < '\x01') {
        if ((*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xeb) != '\0') &&
           (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 0)) {
          return;
        }
        iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
        if (((*(int *)(*(int *)(iVar6 + 0x7c) * 0x178 + 0x82c + *(int *)(iVar6 + 0x368)) != 2) ||
            (iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
            *(int *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar6 + 0x90) * 4) + 0x8c) != iVar8)) ||
           (iVar6 = *(int *)(in_ECX + 0x194 + *(int *)(iVar6 + 0x90) * 4),
           *(int *)(*(int *)(iVar6 + 0x7c) * 0x178 + 0x858 + *(int *)(iVar6 + 0x368)) != 0)) {
          local_74 = (int *)(iVar9 * 0x50 + *(int *)(iVar1 + 0x130));
          if ((*local_74 == 0) && (local_74[0xb] == 0x15)) {
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            if (*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) == 0x12)
            {
              return;
            }
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            if (*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) == 0x13)
            {
              return;
            }
          }
          if ((*local_74 == 5) &&
             (iVar9 = *(int *)(in_ECX + 0x194 + param_1 * 4), *(int *)(iVar9 + 0x98) < 0)) {
            iVar9 = *(int *)(iVar9 + 0xa0);
            iVar6 = *(int *)(in_ECX + 0x194 + iVar9 * 4);
            if (*(int *)(iVar6 + 0x9c) != param_1) goto LAB_0042e37e;
            iVar6 = *(int *)(*(int *)(iVar6 + 0x7c) * 0x178 + 0x88c + *(int *)(iVar6 + 0x368));
            if ((0 < iVar6) && (iVar9 != iVar8)) {
              local_58[1] = local_74[1];
              local_58[2] = local_74[2];
              local_48 = local_74[4];
              local_58[3] = local_74[3];
              iVar9 = 5;
              piVar7 = (int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 200 +
                              iVar6 * 0x50);
              do {
                local_58[iVar9] = piVar7[-1];
                local_58[iVar9 + 1] = *piVar7;
                local_58[iVar9 + 2] = piVar7[1];
                local_58[iVar9 + 3] = piVar7[2];
                local_58[iVar9 + 4] = piVar7[3];
                iVar9 = iVar9 + 5;
                piVar7 = piVar7 + 5;
              } while (iVar9 < 0x14);
              local_58[0] = 0;
              goto LAB_0042e409;
            }
          }
          else {
LAB_0042e37e:
            local_58[0] = *local_74;
            local_58[1] = local_74[1];
            local_58[2] = local_74[2];
            local_58[3] = local_74[3];
            local_48 = local_74[4];
            local_44 = local_74[5];
            local_40 = local_74[6];
            local_3c = local_74[7];
            local_38 = local_74[8];
            local_34 = local_74[9];
            local_30 = local_74[10];
            local_2c = local_74[0xb];
            local_28 = local_74[0xc];
            local_24 = local_74[0xd];
            local_20 = local_74[0xe];
            local_1c = local_74[0xf];
            local_18 = local_74[0x10];
            local_14 = local_74[0x11];
            local_10 = local_74[0x12];
            local_c = local_74[0x13];
LAB_0042e409:
            local_74 = local_58;
          }
          if ((0 < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 800)) && (*local_74 == 4)) {
            *local_74 = 0;
            iVar9 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            if (((fVar12 < (float10)*(double *)(iVar9 + 0x40)) &&
                (*(char *)(iVar9 + 0x80) == '\x01')) ||
               (((float10)*(double *)(iVar9 + 0x40) < fVar12 && (*(char *)(iVar9 + 0x80) == '\0'))))
            {
              local_74[5] = -local_74[5];
            }
          }
          iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
          if ((((*(int *)(iVar9 + 0x98) == 2) && (*local_74 == 0)) &&
              (iVar9 = *(int *)(in_ECX + 0x194 + *(int *)(iVar9 + 0x9c) * 4),
              *(int *)(iVar9 + 0xa0) == iVar8)) && (*(int *)(iVar9 + 0x98) == -2)) {
            *(undefined1 *)
             (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) + 0xf0 +
             *(int *)(in_ECX + 0x194 + param_1 * 4)) = 0x2d;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0;
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            *(undefined1 *)(*(int *)(iVar9 + 0x9c) + 0xf0 + iVar9) = 0x1e;
            *(undefined4 *)
             (*(int *)(in_ECX + 0x194 + *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) +
             0x98) = 0;
            uVar5 = FUN_00417170(0xec,6);
            *(undefined4 *)
             (*(int *)(in_ECX + 0x194 + *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) +
             0x70) = uVar5;
            *(undefined8 *)
             (*(int *)(in_ECX + 0x194 + *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) +
             0x48) = 0xbff0000000000000;
            fVar12 = (float10)0;
          }
          if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 2) {
            local_74[5] = local_74[5] / 2;
            local_74[6] = local_74[6] / 2;
          }
          local_64 = 0;
          if ((*local_74 == 9) &&
             (((iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
               *(int *)(*(int *)(iVar9 + 0x368) + 0x6f8) == 0 ||
               (*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) == 0x3ea)
               ) || (iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                    *(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) ==
                    2000)))) {
            *local_74 = 0;
            if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 0) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc) = 0;
              goto LAB_0042e60e;
            }
LAB_0042e61c:
            if ((((local_74[0x10] == 100) || (iVar9 = *(int *)(iVar10 + 8), iVar9 == 8)) ||
                ((iVar9 == 0xb || (((iVar9 == 0xc || (iVar9 == 0xd)) || (iVar9 == 0xe)))))) ||
               ((iVar9 == 0x10 || (iVar9 == 0x12)))) {
LAB_0042e812:
              if ((((*(int *)(iVar10 + 8) == 7) && (local_74[0x10] < 0x3d)) &&
                  ((iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                   *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) !=
                   *(char *)(iVar9 + 0x80) ||
                   ((((local_74[5] < 0 ||
                      (iVar6 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) +
                                       0x6f4), iVar6 == 0x7c)) || (iVar6 == 0xdc)) ||
                    ((iVar6 == 0xdd || (iVar6 == 0xde)))))))) && (0 < *(int *)(iVar9 + 0x2fc)))
              goto LAB_0042fdf2;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb8) = 0x2d;
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f4) == 300) {
                if (*(int *)((*(int *)(iVar10 + 0x70) + 6) * 0x178 + *(int *)(iVar10 + 0x368)) < 1)
                {
                  return;
                }
                iVar1 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (**(int **)(*(int *)(iVar1 + 0x70) * 0x178 + 0x8d8 + *(int *)(iVar1 + 0x368)) <
                    0x3e9) {
                  return;
                }
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) = 1;
                iVar1 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(int *)(iVar1 + 0x70) =
                     **(int **)(*(int *)(iVar1 + 0x368) + 0x8d8 + *(int *)(iVar1 + 0x70) * 0x178) +
                     -1000;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xb4) = 3;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb4) = 0xfffffffd;
                return;
              }
              iVar9 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8);
              if (iVar9 != 6) {
                iVar6 = local_74[0x11];
                if (0 < *(int *)(iVar10 + 0x340)) {
                  iVar6 = (iVar6 * 100) / *(int *)(iVar10 + 0x340);
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                iVar11 = *(int *)(iVar10 + 0x2fc);
                if (((0 < iVar11) && (iVar11 <= iVar6)) &&
                   ((iVar9 == 0 && (*(int *)(iVar10 + 0x2f4) == -1)))) {
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                           *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354)
                                           * 4) + 0x358);
                  *piVar7 = *piVar7 + 1;
                  iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                  if ((0 < iVar10) && (iVar10 < 3)) {
                    *(int *)(&DAT_00451b60 +
                            *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344) * 4) =
                         *(int *)(&DAT_00451b60 +
                                 *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344) * 4) + 1;
                  }
                }
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2fc);
                *piVar7 = *piVar7 - iVar6;
                iVar10 = (int)((ulonglong)((longlong)iVar6 * 0x55555555) >> 0x20) - iVar6;
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x300);
                *piVar7 = *piVar7 + ((iVar10 >> 1) - (iVar10 >> 0x1f));
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x34c);
                *piVar7 = *piVar7 + iVar6;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0) &&
                   (*(int *)(iVar10 + 0x2f4) == -1)) {
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                           *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354)
                                           * 4) + 0x348);
                  *piVar7 = *piVar7 + iVar6;
                }
                iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                if ((0 < iVar10) && (iVar10 < 3)) {
                  (&DAT_00451b68)[*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344)] =
                       (&DAT_00451b68)[*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344)] +
                       iVar6;
                }
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if ((*(int *)(iVar10 + 0x2fc) < 1) || (local_74[0xb] == 4)) {
                *(undefined4 *)(iVar10 + 0xb0) = 0x50;
              }
              iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8);
              if (((((iVar10 == 1) || (iVar10 == 2)) || (iVar10 == 4)) || (iVar10 == 6)) &&
                 (piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c),
                 *piVar7 = *piVar7 - local_74[0x11], local_74[0x10] == 100)) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c) = 0xffffffff;
              }
              if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) != 2) ||
                 (0x28 < local_74[7])) {
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x20);
                *piVar7 = *piVar7 + 1;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (local_74[7] == 0) {
                piVar7 = (int *)(iVar10 + 0xb0);
                *piVar7 = *piVar7 + 0x14;
              }
              else {
                piVar7 = (int *)(iVar10 + 0xb0);
                *piVar7 = *piVar7 + local_74[7];
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (((*(int *)(*(int *)(iVar10 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    0xd) || (*(int *)(*(int *)(iVar10 + 0x7c) * 0x178 + 0x7ac +
                                     *(int *)(iVar10 + 0x368)) == 0xc)) ||
                 ((iVar10 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8), iVar10 == 1 ||
                  (((iVar10 == 4 || (iVar10 == 6)) || (iVar10 == 2)))))) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0x50;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(iVar10 + 0xb0);
              if ((iVar9 < 0x3d) || (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 3)) {
                if ((iVar9 < 0x29) || (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 3)) {
                  if ((iVar9 < 0x15) || (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 3)) {
                    if ((0 < iVar9) && (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) != 3)) {
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0xdc;
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0x14;
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      if (*(int *)(iVar10 + 0x14) < 0) {
                        *(uint *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) =
                             (uint)(*(char *)(iVar10 + 0x80) ==
                                   *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80)) * 2 +
                             0xde;
                      }
                    }
                  }
                  else {
                    *(uint *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) =
                         (uint)(*(char *)(iVar10 + 0x80) ==
                               *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80)) * 2 + 0xde;
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0x28;
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    if (*(int *)(iVar10 + 0x14) < 0) {
                      *(undefined4 *)(iVar10 + 0xb0) = 0x50;
                    }
                  }
                }
                else {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0xe2;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0x3c;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar10 + 0x14) < 0) {
                    *(undefined4 *)(iVar10 + 0xb0) = 0x50;
                  }
                }
              }
              else {
                *(undefined4 *)(iVar10 + 0xb0) = 0x50;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              iVar9 = *(int *)(iVar10 + 0x368);
              if ((*(int *)(iVar9 + 0x6f8) == 3) && (iVar9 = *(int *)(iVar9 + 0xac), -1 < iVar9)) {
                FUN_00416fb0(*(undefined4 *)(iVar10 + 0x10),iVar9);
                fVar12 = (float10)0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8);
              if (iVar9 == 0) {
                if (local_74[0xb] == 0) {
                  if (*(int *)(iVar10 + 0xb0) == 0x50) {
                    uVar13 = *(undefined4 *)(iVar10 + 0x10);
                    uVar5 = 2;
                  }
                  else {
                    uVar5 = 0;
                    if (*(int *)(iVar10 + 0xb0) == 0x3c) {
                      uVar13 = *(undefined4 *)(iVar10 + 0x10);
                    }
                    else {
                      uVar13 = *(undefined4 *)(iVar10 + 0x10);
                    }
                  }
                  FUN_00417090(uVar13,uVar5);
                  fVar12 = (float10)0;
                }
                if (local_74[0xb] == 1) {
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  uVar5 = *(undefined4 *)(iVar10 + 0x10);
                  local_64 = 1;
                  if (*(int *)(iVar10 + 0xb0) == 0x50) {
                    FUN_00417090(uVar5,0xc);
                    uVar5 = 2;
                  }
                  else {
                    FUN_00417090(uVar5,0xb);
                    uVar5 = 0;
                  }
                  FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),uVar5);
                  goto LAB_0042ed75;
                }
              }
              else if ((0 < iVar9) && (-1 < *(int *)(*(int *)(iVar10 + 0x368) + 0xa4))) {
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                FUN_00416fb0(*(undefined4 *)(iVar10 + 0x10),
                             *(undefined4 *)(*(int *)(iVar10 + 0x368) + 0xa4));
LAB_0042ed75:
                fVar12 = (float10)0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if ((((*(int *)(iVar10 + 0xb0) != 0x50) || (5.0 <= *(double *)(iVar10 + 0x40))) ||
                  (*(double *)(iVar10 + 0x40) <= -5.0)) || (local_74[5] != 0)) {
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    2000) {
                  iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar10 + 0x10) < *(int *)(iVar9 + 0x10)) {
                    dVar2 = (double)local_74[5];
LAB_0042ee5b:
                    *(double *)(iVar9 + 0x28) = dVar2 + *(double *)(iVar9 + 0x28);
                  }
                  else {
                    *(double *)(iVar9 + 0x28) = *(double *)(iVar9 + 0x28) - (double)local_74[5];
                  }
                }
                else {
                  iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  iVar6 = *(int *)(*(int *)(iVar9 + 0x368) + 0x6f8);
                  if ((iVar6 == 4) || (iVar6 == 6)) {
                    iVar6 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    dVar2 = *(double *)(iVar6 + 0x40) * 0.55;
                    if ((float10)*(double *)(iVar6 + 0x40) < fVar12) {
                      dVar2 = -(*(double *)(iVar9 + 0x40) * 0.55);
                    }
                    if (((dVar2 < (double)local_74[5]) ||
                        ((cVar3 = *(char *)(iVar10 + 0x80), cVar3 == '\0' &&
                         (fVar12 < (float10)*(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28)
                         )))) || ((cVar3 == '\x01' &&
                                  ((float10)*(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28)
                                   < fVar12)))) {
                      if (*(char *)(iVar10 + 0x80) == '\0') {
                        iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                        *(double *)(iVar10 + 0x28) =
                             (double)local_74[5] + *(double *)(iVar10 + 0x28);
                      }
                      if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\x01') {
                        iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                        *(double *)(iVar10 + 0x28) =
                             *(double *)(iVar10 + 0x28) - (double)local_74[5];
                      }
                    }
                    else if (((cVar3 == '\x01') &&
                             (fVar12 < (float10)*(double *)
                                                 (*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40))) ||
                            ((cVar3 == '\0' &&
                             ((float10)*(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) <
                              fVar12)))) {
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      *(double *)(iVar10 + 0x28) = -(*(double *)(iVar10 + 0x40) * 0.55);
                    }
                    iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                    if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f4) == 100) &&
                       (*(int *)(iVar10 + 0x98) < 0)) {
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) * 2.5;
                      FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0xd)
                      ;
                      fVar12 = (float10)0;
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      if ((fVar12 < (float10)*(double *)(iVar10 + 0x28)) &&
                         (*(double *)(iVar10 + 0x28) < 10.0)) {
                        *(undefined8 *)(iVar10 + 0x28) = 0x4024000000000000;
                      }
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      if (((float10)*(double *)(iVar10 + 0x28) < fVar12) &&
                         (-10.0 < *(double *)(iVar10 + 0x28))) {
                        *(undefined8 *)(iVar10 + 0x28) = 0xc024000000000000;
                      }
                    }
                  }
                  else if ((local_74[0xb] == 0x16) || (local_74[0xb] == 0x17)) {
                    dVar2 = (double)local_74[5];
                    iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    if (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) <=
                        *(int *)(iVar10 + 0x10)) goto LAB_0042ee5b;
                    *(double *)(iVar9 + 0x28) = *(double *)(iVar9 + 0x28) - dVar2;
                  }
                  else {
                    if (*(char *)(iVar10 + 0x80) == '\0') {
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      *(double *)(iVar10 + 0x28) = (double)local_74[5] + *(double *)(iVar10 + 0x28);
                    }
                    if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\x01') {
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) - (double)local_74[5];
                    }
                  }
                }
              }
              else {
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    2000) {
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) + 5.0;
                }
                else {
                  iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(double *)(iVar9 + 0x28) =
                       (double)(*(char *)(iVar10 + 0x80) * -2 + 1) * 5.0 + *(double *)(iVar9 + 0x28)
                  ;
                }
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if ((*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                   3000) &&
                 (((iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368),
                   *(int *)(iVar9 + 0x6f8) == 0 ||
                   (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f4) != 0xd1)) ||
                  ((((iVar9 = *(int *)(iVar9 + 0x6f4), iVar9 != 200 &&
                     (((iVar9 != 0xcb && (iVar9 != 0xcd)) && (iVar9 != 0xce)))) &&
                    (((iVar9 != 0xcf && (iVar9 != 0xd7)) && (iVar9 != 0xd8)))) &&
                   ((iVar9 != 0xd1 ||
                    (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) != 0x28)))))))) {
                *(undefined4 *)(iVar10 + 0x70) = 10;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x88) = 0;
                *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar12;
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                *(double *)(iVar10 + 0x50) =
                     (double)*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7bc +
                                     *(int *)(iVar10 + 0x368));
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(iVar10 + 0xb0) == 0x50) {
                iVar10 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8);
                if (local_74[6] == 0) {
                  if (((iVar10 != 2) && (iVar10 != 3)) || (0x28 < local_74[7])) {
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    *(double *)(iVar10 + 0x30) = *(double *)(iVar10 + 0x30) - 7.0;
                  }
                }
                else {
                  if (((iVar10 != 2) && (iVar10 != 3)) || (0x28 < local_74[7])) {
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    *(double *)(iVar10 + 0x30) = (double)local_74[6] + *(double *)(iVar10 + 0x30);
                  }
                  iVar10 = FUN_004450d0();
                  fVar12 = extraout_ST0;
                  if (0 < iVar10) {
                    *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x30) =
                         0x4028000000000000;
                  }
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (((*(char *)(iVar10 + 0x80) == '\0') &&
                    ((float10)*(double *)(iVar10 + 0x28) <= fVar12)) ||
                   ((*(char *)(iVar10 + 0x80) == '\x01' &&
                    (fVar4 = (float10)*(double *)(iVar10 + 0x28),
                    (!NAN(fVar12) && !NAN(fVar4)) && fVar12 < fVar4 != (fVar12 == fVar4))))) {
                  *(undefined4 *)(iVar10 + 0x70) = 0xb4;
                }
                else {
                  *(undefined4 *)(iVar10 + 0x70) = 0xba;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if ((0 < *(int *)(iVar10 + 0x98)) &&
                   (iVar8 == *(int *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0x9c) * 4) + 0xa0)
                   )) {
                  *(undefined1 *)
                   (*(int *)(iVar10 + 0x9c) + 0xf0 + *(int *)(in_ECX + 0x194 + param_1 * 4)) = 0x2d;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(undefined1 *)(*(int *)(iVar10 + 0x9c) + 0xf0 + iVar10) = 0x1e;
                }
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (-1 < *(int *)(iVar10 + 0xb4)) {
                *(undefined4 *)(iVar10 + 0xb4) = 3;
              }
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb4) = 0xfffffffd;
              if ((local_74[8] < 4) && (local_74[9] == 0)) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xec) = 4;
              }
              else {
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xec) = local_74[8];
              }
              if (0 < local_74[9]) {
                *(char *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xf0 + param_1) = (char)local_74[9]
                ;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if ((((*(int *)(*(int *)(iVar10 + 0x7c) * 0x178 + 0x82c + *(int *)(iVar10 + 0x368)) ==
                     2) && (iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                           *(int *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0x90) * 4) + 0x8c)
                           == iVar8)) && (*(int *)(iVar10 + 0xb0) != 0x50)) &&
                 (*(int *)(*(int *)(iVar10 + 0x7c) * 0x178 + 0x838 + *(int *)(iVar10 + 0x368)) != 0)
                 ) {
                if (*(char *)(iVar10 + 0x80) ==
                    *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80)) {
                  *(undefined4 *)(iVar10 + 0x70) =
                       *(undefined4 *)
                        (*(int *)(iVar10 + 0x7c) * 0x178 + 0x83c + *(int *)(iVar10 + 0x368));
                }
                else {
                  *(undefined4 *)(iVar10 + 0x70) =
                       *(undefined4 *)
                        (*(int *)(iVar10 + 0x7c) * 0x178 + 0x838 + *(int *)(iVar10 + 0x368));
                }
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(iVar10 + 0xb0) == 0x50) {
                *(undefined4 *)(iVar10 + 0xb0) = 0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (*(int *)(iVar10 + 0x98) < 0) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4) + 0xb4) =
                     *(undefined4 *)(iVar10 + 0xb4);
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                  0x3ea) {
                uVar5 = FUN_00417170(0xee,0x10);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = uVar5;
                *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) =
                     -(*(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28) * 0.5);
                *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = 0xc010000000000000;
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 4) &&
                   (iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                   *(int *)(*(int *)(iVar9 + 0x368) + 0x6f8) == 4)) {
                  *(double *)(iVar10 + 0x28) = -*(double *)(iVar9 + 0x28);
                }
                fVar12 = (float10)0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 1) {
                *(undefined1 *)(iVar10 + 0xeb) = 1;
                uVar5 = FUN_00417170(0xef,0x10);
                fVar12 = (float10)0;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = uVar5;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
              }
              iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8);
              if ((iVar10 == 4) || (iVar10 == 6)) {
                *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xf0 + iVar8) = 0x1e;
                *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xeb) = 1;
                uVar5 = FUN_00417170(0xf0,0x10);
                fVar12 = (float10)0;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = uVar5;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 2) {
                *(undefined1 *)(iVar10 + 0xeb) = 1;
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(iVar10 + 0x98) == -2) {
                  if ((local_74[7] < 0x29) && (local_74[0xb] != 4)) {
                    *(undefined1 *)
                     (*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4) + 0xf0 + iVar8) = 3;
                  }
                  else {
                    *(undefined1 *)
                     (*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4) + 0xf0 + iVar8) = 0x13;
                  }
                }
                else if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) != 2) {
                  if ((local_74[7] < 0x29) && (local_74[0xb] != 4)) {
                    *(undefined1 *)(iVar10 + 0xf0 + iVar8) = 3;
                  }
                  else {
                    *(undefined1 *)(iVar10 + 0xf0 + iVar8) = 0x13;
                  }
                }
                *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) =
                     *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80);
                if (((local_74[7] < 0x29) &&
                    (iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4), -1 < *(int *)(iVar10 + 0x14)))
                   && (local_74[0xb] != 4)) {
                  *(undefined4 *)(iVar10 + 0x70) = 0x14;
                }
                else {
                  uVar5 = FUN_00417170(0xf1,6);
                  fVar12 = (float10)0;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = uVar5;
                }
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
              }
              if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x6f4) ==
                   0xc9) &&
                 (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 0)) {
                *(undefined1 *)(param_1 + 4 + in_ECX) = 0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f4) == 0xd6) &&
                 (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 0)) {
                *(undefined4 *)(iVar10 + 0x2fc) = 0;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 3) {
                if ((*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                     0xbbd) &&
                   ((iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                    *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                    0xbbe || (iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                             *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac +
                                     *(int *)(iVar10 + 0x368)) == 0xbbd)))) {
                  iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                  if (*(int *)(iVar10 + 0x98) < 0) {
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                         *(undefined4 *)
                          (*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4) + 0x364);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                         *(undefined4 *)
                          (*(int *)(in_ECX + 0x194 +
                                   *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xa0) * 4) +
                          0x354);
                  }
                  else {
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                         *(undefined4 *)(iVar10 + 0x364);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                  }
                  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xeb) = 1;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x30) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x38) = (double)fVar12;
                  iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                  if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f4) == 0xd1) &&
                     ((((iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) +
                                         0x6f4), iVar9 == 200 || (iVar9 == 0xcb)) || (iVar9 == 0xcd)
                       ) || (((iVar9 == 0xce || (iVar9 == 0xcf)) ||
                             ((iVar9 == 0xd7 || (iVar9 == 0xd8)))))))) {
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                         *(undefined4 *)(iVar10 + 0x364);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) =
                         *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368);
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x28;
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x74) = 0x28;
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x78) = 0x28;
                  }
                  else if (((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0) ||
                           (*(int *)(iVar10 + 0x98) < 0)) &&
                          ((local_74[0xb] != 2 && (local_74[0xb] != 0x14)))) {
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x1e;
                    if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x6f4)
                         == 8) &&
                       ((((((iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368
                                                       ) + 0x6f4), iVar10 == 200 || (iVar10 == 0xcb)
                            ) || (iVar10 == 0xcd)) || ((iVar10 == 0xce || (iVar10 == 0xcf)))) ||
                         (iVar10 == 0xd7)) || (iVar10 == 0xd8)))) {
                      local_68 = *(int **)(in_ECX + 0x7d4);
                      piVar7 = local_68 + 0x13608e0;
                      iVar10 = 0;
                      if (0 < *piVar7) {
                        do {
                          if (*(int *)(*local_68 + 0x6f4) == 0xd1) {
                            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) =
                                 *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar10 * 4);
                            iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                            *(undefined4 *)(iVar10 + 0x74) = *(undefined4 *)(iVar10 + 0x70);
                            iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                            *(undefined4 *)(iVar10 + 0x78) = *(undefined4 *)(iVar10 + 0x70);
                            break;
                          }
                          iVar10 = iVar10 + 1;
                          local_68 = local_68 + 1;
                        } while (iVar10 < *piVar7);
                      }
                    }
                  }
                  else {
                    *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x14;
                  }
                  iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                  piVar7 = *(int **)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar10 + 0x98) < 0) {
                    *piVar7 = *(int *)(iVar10 + 0xa0);
                    if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x6f4)
                         == 0xd5) &&
                       ((((iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368)
                                            + 0x6f4), iVar10 == 200 || (iVar10 == 0xcb)) ||
                         ((iVar10 == 0xcd ||
                          (((iVar10 == 0xce || (iVar10 == 0xcf)) || (iVar10 == 0xd7)))))) ||
                        (iVar10 == 0xd8)))) {
                      local_68 = *(int **)(in_ECX + 0x7d4);
                      piVar7 = local_68 + 0x13608e0;
                      iVar10 = 0;
                      if (0 < *piVar7) {
                        do {
                          if (*(int *)(*local_68 + 0x6f4) == 0xd1) {
                            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) =
                                 *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar10 * 4);
                            iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                            *(undefined4 *)(iVar10 + 0x74) = *(undefined4 *)(iVar10 + 0x70);
                            iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                            *(undefined4 *)(iVar10 + 0x78) = *(undefined4 *)(iVar10 + 0x70);
                            break;
                          }
                          iVar10 = iVar10 + 1;
                          local_68 = local_68 + 1;
                        } while (iVar10 < *piVar7);
                      }
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                           *(undefined4 *)
                            (*(int *)(in_ECX + 0x194 +
                                     *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xa0) * 4) +
                            0x364);
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                           *(undefined4 *)
                            (*(int *)(in_ECX + 0x194 +
                                     *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xa0) * 4) +
                            0x354);
                    }
                  }
                  else {
                    *piVar7 = param_1;
                  }
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (((*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368))
                      == 0xbbd) &&
                    (iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                    *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    0xbbd)) ||
                   ((iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                    *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    0xbbe && (iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                             *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac +
                                     *(int *)(iVar10 + 0x368)) == 0xbbe)))) {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x14;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x30) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x38) = (double)fVar12;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x14;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x88) = 0;
                  *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x30) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x28) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x38) = (double)fVar12;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(iVar10 + 0x98) < 0) {
                  iVar10 = *(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4);
                  if (0 < *(int *)(iVar10 + 0xb4)) {
                    *(int *)(iVar10 + 0xb4) = -*(int *)(iVar10 + 0xb4);
                  }
                }
                else if (0 < *(int *)(iVar10 + 0xb4)) {
                  *(int *)(iVar10 + 0xb4) = -*(int *)(iVar10 + 0xb4);
                }
              }
              if (((local_74[0xb] == 3) || (local_74[0xb] == 0x1e)) &&
                 ((iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                  *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0 &&
                  (*(int *)(*(int *)(iVar10 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                   0xd)))) {
                *(undefined4 *)(iVar10 + 0x70) = 200;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0xe);
                fVar12 = (float10)0;
              }
              iVar10 = local_74[0xb];
              if (((((iVar10 == 2) || (iVar10 == 0x15)) || (iVar10 == 0x16)) ||
                  ((iVar10 == 0x14 &&
                   (iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                   *(int *)(*(int *)(iVar10 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                   0x12)))) &&
                 (iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4),
                 *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0)) {
                *(undefined4 *)(iVar10 + 0x70) = 0xcb;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0x10);
                fVar12 = (float10)0;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                fVar4 = (float10)*(double *)(iVar10 + 0x28);
                if ((NAN(fVar12) || NAN(fVar4)) || fVar12 < fVar4 == (fVar12 == fVar4)) {
                  *(undefined1 *)(iVar10 + 0x80) = 0;
                }
                else {
                  *(undefined1 *)(iVar10 + 0x80) = 1;
                }
              }
              if (local_74[0xb] == 0x17) {
                FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0x10);
                fVar12 = (float10)0;
              }
              goto LAB_0043187a;
            }
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            iVar6 = *(int *)(*(int *)(iVar9 + 0x368) + 0x6f4);
            if ((iVar6 == 0x25) && (*(int *)(iVar9 + 0xb8) < 0x10)) {
              iVar9 = local_74[0xb];
              if (((iVar9 / 10 == 2) || (iVar9 / 10 == 3)) ||
                 ((iVar9 == 2 ||
                  (((iVar9 == 3 ||
                    (iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) +
                                     0x6f4), iVar9 == 0xd6)) || (iVar9 == 0xd0))))))
              goto LAB_0042e6ec;
            }
            else {
LAB_0042e6ec:
              if ((iVar6 == 6) && (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb8) < 2)) {
                iVar9 = local_74[0xb];
                if ((iVar9 / 10 != 2) &&
                   ((((iVar9 / 10 != 3 && (iVar9 != 2)) &&
                     ((iVar9 != 3 &&
                      ((iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) +
                                        0x6f4), iVar9 != 0xd6 && (iVar9 != 0xd0)))))) &&
                    ((iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4), *(int *)(iVar9 + 0x70) < 0x14 ||
                     (((*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368))
                        == 5 || (*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac +
                                         *(int *)(iVar9 + 0x368)) == 4)) ||
                      (*(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) ==
                       7)))))))) goto LAB_0042fdf2;
              }
              if (((iVar6 != 0x34) || (0xf < *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb8)))
                 || ((iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) +
                                      0x6f4), iVar9 == 0xd6 || (iVar9 == 0xd0)))) goto LAB_0042e812;
            }
LAB_0042fdf2:
            iVar9 = *local_74;
            if ((iVar9 != 0) ||
               (iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368),
               *(int *)(iVar6 + 0x6f8) != 0)) goto LAB_0043056e;
            iVar9 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            iVar11 = *(int *)(iVar9 + 0x368);
            if (*(int *)(iVar11 + 0x6f8) == 3) {
              iVar6 = *(int *)(iVar11 + 0xac);
              if (-1 < iVar6) {
                FUN_00416fb0(*(undefined4 *)(iVar9 + 0x10),iVar6);
                goto LAB_0042fe80;
              }
            }
            else {
              iVar9 = *(int *)(iVar6 + 0x6f4);
              if ((iVar9 == 0x25) || (iVar9 == 6)) {
                FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0x11);
              }
              else {
                FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),1);
              }
LAB_0042fe80:
              fVar12 = (float10)0;
            }
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            iVar6 = *(int *)(*(int *)(iVar9 + 0x368) + 0x6f8);
            if (iVar6 != 6) {
              iVar9 = *(int *)(iVar9 + 0x340);
              iVar11 = local_74[0x11];
              if (0 < iVar9) {
                iVar11 = (iVar11 * 100) / iVar9;
              }
              iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2fc);
              if ((((0 < iVar9) && (iVar9 <= iVar11 / 10)) && (iVar6 == 0)) &&
                 (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2f4) == -1)) {
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354) *
                                         4) + 0x358);
                *piVar7 = *piVar7 + 1;
                iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                if ((0 < iVar9) && (iVar9 < 3)) {
                  *(int *)(&DAT_00451b60 +
                          *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344) * 4) =
                       *(int *)(&DAT_00451b60 +
                               *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344) * 4) + 1;
                }
              }
              iVar11 = iVar11 / 10;
              piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2fc);
              *piVar7 = *piVar7 - iVar11;
              iVar9 = (int)((ulonglong)((longlong)iVar11 * 0x55555555) >> 0x20) - iVar11;
              piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x300);
              *piVar7 = *piVar7 + ((iVar9 >> 1) - (iVar9 >> 0x1f));
              piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x34c);
              *piVar7 = *piVar7 + iVar11;
              iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if ((*(int *)(*(int *)(iVar9 + 0x368) + 0x6f8) == 0) &&
                 (*(int *)(iVar9 + 0x2f4) == -1)) {
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354) *
                                         4) + 0x348);
                *piVar7 = *piVar7 + iVar11;
              }
              iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
              if ((0 < iVar9) && (iVar9 < 3)) {
                (&DAT_00451b68)[*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344)] =
                     (&DAT_00451b68)[*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344)] +
                     iVar11;
              }
            }
            iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8);
            if (((((iVar9 == 1) || (iVar9 == 2)) || (iVar9 == 4)) || (iVar9 == 6)) &&
               (piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c),
               *piVar7 = *piVar7 - local_74[0x11], local_74[0x10] == 100)) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c) = 0xffffffff;
            }
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            if (*(int *)(iVar9 + 0x2fc) < 1) {
              *(undefined4 *)(iVar9 + 0xb0) = 0x50;
            }
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
            piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb8);
            *piVar7 = *piVar7 + local_74[0x10];
            piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x20);
            *piVar7 = *piVar7 + 1;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xb4) = 3;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb4) = 0xfffffffb;
            iVar9 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
            if (*(int *)(iVar9 + 0x14) == 0) {
              if ((*(int *)(iVar9 + 0xb8) < 0x1f) || (*(int *)(iVar10 + 8) != 7)) {
                if (*(int *)(iVar9 + 0x70) == 0x6e) {
                  *(undefined4 *)(iVar9 + 0x70) = 0x6f;
                }
              }
              else {
                *(undefined4 *)(iVar9 + 0x70) = 0x70;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (((*(int *)(iVar10 + 0xb0) != 0x50) || (3.0 <= *(double *)(iVar10 + 0x40))) ||
                 ((*(double *)(iVar10 + 0x40) <= -3.0 || (local_74[5] != 0)))) {
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    2000) {
                  dVar2 = (double)local_74[5];
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar10 + 0x10) <=
                      *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) goto LAB_0043037d;
                  *(double *)(iVar10 + 0x28) = dVar2 + *(double *)(iVar10 + 0x28);
                }
                else if ((local_74[0xb] == 0x16) || (local_74[0xb] == 0x17)) {
                  dVar2 = (double)local_74[5];
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) <=
                      *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) goto LAB_0043027b;
                  *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) - dVar2;
                }
                else {
                  if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\0') {
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    *(double *)(iVar10 + 0x28) =
                         (double)(local_74[5] / 2) + *(double *)(iVar10 + 0x28);
                  }
                  if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\x01') {
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    dVar2 = (double)-(local_74[5] / 2);
LAB_0043027b:
                    *(double *)(iVar10 + 0x28) = dVar2 + *(double *)(iVar10 + 0x28);
                  }
                }
              }
              else {
                iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                iVar9 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    2000) {
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar9 + 0x10) < *(int *)(iVar10 + 0x10)) {
                    *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) + 6.0;
                  }
                  else {
                    *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) - 6.0;
                  }
                }
                else {
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(double *)(iVar10 + 0x28) =
                       (double)(*(char *)(iVar9 + 0x80) * -2 + 1) * 3.0 + *(double *)(iVar10 + 0x28)
                  ;
                }
              }
            }
            else {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if ((((*(int *)(iVar10 + 0xb0) != 0x50) || (6.0 <= *(double *)(iVar10 + 0x40))) ||
                  (*(double *)(iVar10 + 0x40) <= -6.0)) || (5 < local_74[5])) {
                if ((local_74[0xb] != 0x16) && (local_74[0xb] != 0x17)) {
                  if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\0') {
                    *(double *)(iVar10 + 0x28) = (double)local_74[5] + *(double *)(iVar10 + 0x28);
                  }
                  if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\x01') {
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                    dVar2 = (double)local_74[5];
LAB_0043037d:
                    *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x28) - dVar2;
                  }
                  goto LAB_0043030f;
                }
                dVar2 = (double)local_74[5];
                if (*(int *)(iVar10 + 0x10) <=
                    *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) goto LAB_00430309;
                dVar2 = *(double *)(iVar10 + 0x28) - dVar2;
              }
              else {
                dVar2 = (double)(*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) * -2 + 1)
                        * 6.0;
LAB_00430309:
                dVar2 = dVar2 + *(double *)(iVar10 + 0x28);
              }
              *(double *)(iVar10 + 0x28) = dVar2;
            }
LAB_0043030f:
            if ((local_74[8] < 4) && (local_74[9] == 0)) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xec) = 4;
            }
            else {
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xec) = local_74[8];
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (0xc < *(int *)(iVar10 + 0xec)) {
                *(undefined4 *)(iVar10 + 0xec) = 0xc;
              }
            }
            if (0 < local_74[9]) {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (local_74[9] < 5) {
                *(undefined1 *)(iVar10 + 0xf0 + param_1) = 4;
              }
              else {
                *(char *)(iVar10 + 0xf0 + param_1) = (char)local_74[9];
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if ('\f' < *(char *)(iVar10 + 0xf0 + param_1)) {
                  *(undefined1 *)(iVar10 + 0xf0 + param_1) = 0xc;
                }
              }
            }
            iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            if (*(int *)(iVar10 + 0x98) < 0) {
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar10 + 0xa0) * 4) + 0xb4) =
                   *(undefined4 *)(iVar10 + 0xb4);
            }
            iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                0x3ea) {
              uVar5 = FUN_00417170(0xf3,0x10);
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = uVar5;
              *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) =
                   -(*(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28) * 0.5);
              *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = 0xc010000000000000;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar10 + 0x50) = *(double *)(iVar10 + 0x50) / -1.5;
              fVar12 = (float10)0;
            }
            iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) == 2000
               ) {
              iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10);
              iVar6 = *(int *)(iVar10 + 0x10);
              iVar11 = iVar6 - iVar9;
              if (iVar9 < iVar6) {
                if (fVar12 <= (float10)*(double *)(iVar10 + 0x40)) {
                  iVar6 = *(int *)(iVar10 + 0x10);
                  iVar11 = iVar6 - iVar9;
                  goto LAB_004304f7;
                }
              }
              else {
LAB_004304f7:
                if ((SBORROW4(iVar6,iVar9) == iVar11 < 0) ||
                   ((float10)*(double *)(iVar10 + 0x40) <= fVar12)) goto LAB_00430520;
              }
              *(double *)(iVar10 + 0x40) = *(double *)(iVar10 + 0x40) / 2.5;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar10 + 0x50) = *(double *)(iVar10 + 0x50) / 2.5;
            }
LAB_00430520:
            iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            if (*(int *)(*(int *)(iVar10 + 0x368) + 0x7ac + *(int *)(iVar10 + 0x70) * 0x178) == 3000
               ) {
              *(undefined4 *)(iVar10 + 0x70) = 10;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x88) = 0;
              *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar12;
            }
          }
          else {
LAB_0042e60e:
            iVar9 = *local_74;
            if (iVar9 == 0) goto LAB_0042e61c;
LAB_0043056e:
            if (iVar9 == 6) {
              *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xea) = 3;
            }
            else if (iVar9 == 1) {
              *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) = (double)fVar12;
              *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar12;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(bool *)(iVar10 + 0x80) =
                   *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) < *(int *)(iVar10 + 0x10);
              *(char *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) =
                   '\x01' - *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80);
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = local_74[0xc];
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = local_74[0xe];
              iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x830 +
                               local_74[0xc] * 0x178);
              iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x830 +
                              local_74[0xe] * 0x178);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar6 + 0x58) = (double)*(int *)(iVar6 + 0x10);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar6 + 0x60) = (double)*(int *)(iVar6 + 0x14);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (*(char *)(iVar6 + 0x80) == '\0') {
                *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                     (double)(((*(int *)(iVar6 + 0x10) -
                               *(int *)(local_74[0xc] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368))) -
                              *(int *)(local_74[0xe] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368))) +
                              iVar9 + iVar10);
                iVar10 = (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x7f8 +
                                  local_74[0xe] * 0x178) -
                         *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x7f8 +
                                 local_74[0xc] * 0x178)) +
                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
              }
              else {
                *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                     (double)(((*(int *)(local_74[0xc] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368)) +
                                *(int *)(local_74[0xe] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368)) +
                               *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) - iVar9) -
                             iVar10);
                iVar10 = (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x7f8 +
                                  local_74[0xe] * 0x178) -
                         *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x7f8 +
                                 local_74[0xc] * 0x178)) +
                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
              }
              *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x60) = (double)iVar10;
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              dVar2 = ((double)*(int *)(iVar10 + 0x10) - *(double *)(iVar10 + 0x58)) * 0.5;
              *(double *)(iVar10 + 0x58) = *(double *)(iVar10 + 0x58) + dVar2;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar10 + 0x58) = dVar2 + *(double *)(iVar10 + 0x58);
              uVar5 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) = uVar5;
              uVar5 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) = uVar5;
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x8c) = iVar8;
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x90) = param_1;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x94) = 300;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0;
              fVar12 = extraout_ST0_00;
            }
            else if ((iVar9 == 7) &&
                    (iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4), *(int *)(iVar10 + 0x98) == 0))
            {
              *(undefined4 *)(iVar10 + 0x98) = 1;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0xffffffff;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                   *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x9c) = iVar8;
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xa0) = param_1;
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) = param_1;
              piVar7 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x35c);
              *piVar7 = *piVar7 + 1;
              iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f4);
              if ((iVar10 == 0x78) || (iVar10 == 0x7c)) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 0x65;
              }
              if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 4) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 4;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0xfffffffc;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 6) {
                if (*(int *)(iVar10 + 0x2fc) < 1) {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 4;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c) = 0;
                }
                else {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 6;
                }
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) =
                     -*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98);
              }
            }
            else if (iVar9 == 2) {
              if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 1) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x73;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 1;
                iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f4);
                if ((iVar10 == 0x78) || (iVar10 == 0x7c)) {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 0x65;
                }
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0xffffffff;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x9c) = iVar8;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xa0) = param_1;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) = param_1;
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x35c);
                *piVar7 = *piVar7 + 1;
              }
              if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 4) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x73;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 4;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0xfffffffc;
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x9c) = iVar8;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xa0) = param_1;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) = param_1;
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x35c);
                *piVar7 = *piVar7 + 1;
              }
              if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 6) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x73;
                if (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2fc) < 1) {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 4;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x31c) = 0;
                }
                else {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 6;
                }
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) =
                     -*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98);
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x9c) = iVar8;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xa0) = param_1;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) = param_1;
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x35c);
                *piVar7 = *piVar7 + 1;
              }
              if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x6f8) == 2) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = 0x74;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) = 2;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0xfffffffe;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x9c) = iVar8;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xa0) = param_1;
                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) = param_1;
                piVar7 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x35c);
                *piVar7 = *piVar7 + 1;
              }
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x88) = 0;
            }
            else if (iVar9 == 8) {
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xe0) = local_74[0x11] + 1000;
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = local_74[5];
              *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x58) =
                   *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58);
              *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x68) =
                   *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x68) + 1.0;
            }
            else if (iVar9 == 9) {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(iVar10 + 0x368);
              iVar6 = *(int *)(iVar9 + 0x6f8);
              if (iVar6 == 3) {
                iVar9 = *(int *)(iVar9 + 0xac);
                if (-1 < iVar9) {
                  FUN_00416fb0(*(undefined4 *)(iVar10 + 0x10),iVar9);
                  fVar12 = (float10)0;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) ==
                    0xbbd) {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xb4) = 0xfffffffd;
                  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xeb) = 1;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x28;
                }
                else {
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xb4) = 0xfffffffd;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x364) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364);
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xeb) = 1;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x354) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354);
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0x1e;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x30) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x48) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x28) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x38) = (double)fVar12;
                  *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x50) = (double)fVar12;
                  **(int **)(in_ECX + 0x194 + iVar8 * 4) = param_1;
                }
              }
              else if (iVar6 == 0) {
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc) = 0;
              }
            }
            else if ((iVar9 == 10) ||
                    ((iVar9 == 0xb && (*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 800) < 0))))
            {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8);
              if (iVar9 == 0) {
                *(undefined4 *)(iVar10 + 800) = 0xffffffec;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0) &&
                    (*(int *)(iVar10 + 0x2f4) == -1)) && (DAT_00450bd0 == 0)) {
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                           *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354)
                                           * 4) + 0x348);
                  *piVar7 = *piVar7 + 0xb;
                }
                iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                if ((0 < iVar10) && (iVar10 < 3)) {
                  (&DAT_00451b68)[iVar10] = (&DAT_00451b68)[iVar10] + 0xb;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x40) / 1.07;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(undefined8 *)(iVar10 + 0x40) = *(undefined8 *)(iVar10 + 0x28);
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(double *)(iVar10 + 0x38) = *(double *)(iVar10 + 0x50) / 1.07;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(undefined8 *)(iVar10 + 0x50) = *(undefined8 *)(iVar10 + 0x38);
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 0xb6;
LAB_00431517:
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (-3 < *(int *)(iVar10 + 0x14)) {
                  *(undefined4 *)(iVar10 + 0x14) = 0xfffffffe;
                  *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x48) = 0xc018000000000000;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (*(double *)(iVar10 + 0x48) <= -6.0) goto LAB_0043187a;
                dVar2 = *(double *)(iVar10 + 0x48) - 3.0;
              }
              else {
                if ((((iVar9 == 1) || (iVar9 == 4)) || (iVar9 == 6)) &&
                   ((iVar6 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f4), iVar6 != 0xc9 &&
                    (iVar6 != 0xca)))) {
                  if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368))
                      != 1000) {
                    *(undefined4 *)(iVar10 + 0x70) = 0;
                  }
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x40) / 1.07;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(undefined8 *)(iVar10 + 0x40) = *(undefined8 *)(iVar10 + 0x28);
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  dVar2 = *(double *)(iVar10 + 0x50) / 1.07;
LAB_00431507:
                  *(double *)(iVar10 + 0x38) = dVar2;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(undefined8 *)(iVar10 + 0x50) = *(undefined8 *)(iVar10 + 0x38);
                  goto LAB_00431517;
                }
                if (iVar9 != 2) goto LAB_0043187a;
                if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                    2000) {
                  *(undefined4 *)(iVar10 + 0x70) = 0;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(double *)(iVar10 + 0x28) = *(double *)(iVar10 + 0x40) / 1.07;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(undefined8 *)(iVar10 + 0x40) = *(undefined8 *)(iVar10 + 0x28);
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                dVar2 = *(double *)(iVar10 + 0x50) / 1.07;
LAB_00431816:
                *(double *)(iVar10 + 0x38) = dVar2;
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                *(undefined8 *)(iVar10 + 0x50) = *(undefined8 *)(iVar10 + 0x38);
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (-3 < *(int *)(iVar10 + 0x14)) {
                  *(undefined4 *)(iVar10 + 0x14) = 0xfffffffe;
                  *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x48) = 0xc018000000000000;
                }
                iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                if (*(double *)(iVar10 + 0x48) <= -6.0) goto LAB_0043187a;
                dVar2 = *(double *)(iVar10 + 0x48) - 2.3;
              }
              *(double *)(iVar10 + 0x48) = dVar2;
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              *(undefined8 *)(iVar10 + 0x30) = *(undefined8 *)(iVar10 + 0x48);
            }
            else if (iVar9 == 3) {
              *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x40) = (double)fVar12;
              *(double *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = (double)fVar12;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(bool *)(iVar10 + 0x80) =
                   *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) < *(int *)(iVar10 + 0x10);
              *(char *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x80) =
                   '\x01' - *(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80);
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) = local_74[0xc];
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = local_74[0xe];
              iVar10 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x830 +
                               local_74[0xc] * 0x178);
              iVar9 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x830 +
                              local_74[0xe] * 0x178);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar6 + 0x58) = (double)*(int *)(iVar6 + 0x10);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar6 + 0x60) = (double)*(int *)(iVar6 + 0x14);
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (*(char *)(iVar6 + 0x80) == '\0') {
                *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                     (double)(((*(int *)(iVar6 + 0x10) -
                               *(int *)(local_74[0xc] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368))) -
                              *(int *)(local_74[0xe] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368))) +
                              iVar9 + iVar10);
                iVar10 = (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x7f8 +
                                  local_74[0xe] * 0x178) -
                         *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x7f8 +
                                 local_74[0xc] * 0x178)) +
                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
              }
              else {
                *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x58) =
                     (double)(((*(int *)(local_74[0xc] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368)) +
                                *(int *)(local_74[0xe] * 0x178 + 0x7f4 + *(int *)(iVar6 + 0x368)) +
                               *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) - iVar9) -
                             iVar10);
                iVar10 = (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x368) + 0x7f8 +
                                  local_74[0xe] * 0x178) -
                         *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x7f8 +
                                 local_74[0xc] * 0x178)) +
                         *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14);
              }
              *(double *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x60) = (double)iVar10;
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              dVar2 = ((double)*(int *)(iVar10 + 0x10) - *(double *)(iVar10 + 0x58)) * 0.5;
              *(double *)(iVar10 + 0x58) = *(double *)(iVar10 + 0x58) + dVar2;
              iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              *(double *)(iVar10 + 0x58) = dVar2 + *(double *)(iVar10 + 0x58);
              uVar5 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10) = uVar5;
              uVar5 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) = uVar5;
              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x8c) = iVar8;
              *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x90) = param_1;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x94) = 300;
              *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xb0) = 0;
              fVar12 = extraout_ST0_01;
            }
            else if (iVar9 == 0xe) {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
              if ((iVar9 <= *(int *)(iVar10 + 0x10) + 5) ||
                 (((float10)*(double *)(iVar10 + 0x40) <= fVar12 &&
                  ((float10)*(double *)(iVar10 + 0x28) <= fVar12)))) {
                if ((iVar9 < *(int *)(iVar10 + 0x10) + -5) &&
                   (((float10)*(double *)(iVar10 + 0x40) < fVar12 ||
                    ((float10)*(double *)(iVar10 + 0x28) < fVar12)))) {
                  *(undefined4 *)(iVar10 + 0x3f0) = 1;
                }
              }
              else {
                *(undefined4 *)(iVar10 + 0x3f4) = 1;
              }
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
              if ((iVar9 <= *(int *)(iVar10 + 0x18) + 2) ||
                 (((float10)*(double *)(iVar10 + 0x50) <= fVar12 &&
                  ((float10)*(double *)(iVar10 + 0x38) <= fVar12)))) {
                if ((iVar9 < *(int *)(iVar10 + 0x18) + -2) &&
                   (((float10)*(double *)(iVar10 + 0x50) < fVar12 ||
                    ((float10)*(double *)(iVar10 + 0x38) < fVar12)))) {
                  *(undefined4 *)(iVar10 + 1000) = 1;
                }
              }
              else {
                *(undefined4 *)(iVar10 + 0x3ec) = 1;
              }
            }
            else if ((iVar9 == 0xf) || (iVar9 == 0x10)) {
              iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
              iVar6 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f8);
              if (iVar6 == 0) {
                if (iVar9 == 0x10) {
                  iVar9 = local_74[0x11];
                  if (0 < *(int *)(iVar10 + 0x340)) {
                    iVar9 = (iVar9 * 100) / *(int *)(iVar10 + 0x340);
                    iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  }
                  if (((0 < *(int *)(iVar10 + 0x2fc)) && (*(int *)(iVar10 + 0x2fc) <= iVar9)) &&
                     (*(int *)(iVar10 + 0x2f4) == -1)) {
                    piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                             *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354
                                                     ) * 4) + 0x358);
                    *piVar7 = *piVar7 + 1;
                    iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                    if ((0 < iVar10) && (iVar10 < 3)) {
                      *(int *)(&DAT_00451b60 + iVar10 * 4) =
                           *(int *)(&DAT_00451b60 + iVar10 * 4) + 1;
                    }
                  }
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x2fc);
                  *piVar7 = *piVar7 - iVar9;
                  iVar10 = (int)((ulonglong)((longlong)iVar9 * 0x55555555) >> 0x20) - iVar9;
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x300);
                  *piVar7 = *piVar7 + ((iVar10 >> 1) - (iVar10 >> 0x1f));
                  piVar7 = (int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x34c);
                  *piVar7 = *piVar7 + iVar9;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if ((*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0) &&
                     (*(int *)(iVar10 + 0x2f4) == -1)) {
                    piVar7 = (int *)(*(int *)(in_ECX + 0x194 +
                                             *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x354
                                                     ) * 4) + 0x348);
                    *piVar7 = *piVar7 + iVar9;
                  }
                  iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x344);
                  if ((0 < iVar10) && (iVar10 < 3)) {
                    (&DAT_00451b68)[iVar10] = (&DAT_00451b68)[iVar10] + iVar9;
                  }
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x70) = 200;
                  *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x88) = 0;
                  FUN_00417090(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10),0xe);
                  if (0 < local_74[9]) {
                    *(char *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0xf0 + param_1) =
                         (char)local_74[9];
                  }
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(iVar10 + 0x98) == 2) {
                    iVar10 = *(int *)(iVar10 + 0x9c);
                    iVar9 = *(int *)(in_ECX + 0x194 + iVar10 * 4);
                    if ((*(int *)(iVar9 + 0xa0) == iVar8) && (*(int *)(iVar9 + 0x98) == -2)) {
                      *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xf0 + iVar10) = 0x2d
                      ;
                      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x98) = 0;
                      iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                      *(undefined1 *)(*(int *)(iVar10 + 0x9c) + 0xf0 + iVar10) = 0x1e;
                      *(undefined4 *)
                       (*(int *)(in_ECX + 0x194 +
                                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) + 0x98) =
                           0;
                      uVar5 = FUN_00417170(0xf4,6);
                      *(undefined4 *)
                       (*(int *)(in_ECX + 0x194 +
                                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) + 0x70) =
                           uVar5;
                      *(undefined8 *)
                       (*(int *)(in_ECX + 0x194 +
                                *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x9c) * 4) + 0x48) =
                           0xbff0000000000000;
                    }
                  }
                  fVar12 = (float10)0;
                }
                if (*local_74 == 0xf) {
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  dVar2 = *(double *)(iVar10 + 0x40);
                  if (*(int *)(iVar10 + 0x10) <=
                      *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) goto LAB_004314ca;
                  dVar2 = dVar2 - 1.0;
                  goto LAB_004314d0;
                }
              }
              else {
                if ((((iVar6 == 1) || (iVar6 == 4)) || (iVar6 == 6)) &&
                   ((iVar9 = *(int *)(*(int *)(iVar10 + 0x368) + 0x6f4), iVar9 != 0xc9 &&
                    (iVar9 != 0xca)))) {
                  if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368))
                      != 1000) {
                    *(undefined4 *)(iVar10 + 0x70) = 0;
                  }
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  dVar2 = *(double *)(iVar10 + 0x40);
                  if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) <
                      *(int *)(iVar10 + 0x10)) {
                    dVar2 = dVar2 - 1.0;
                  }
                  else {
LAB_004314ca:
                    dVar2 = dVar2 + 1.0;
                  }
LAB_004314d0:
                  *(double *)(iVar10 + 0x28) = dVar2;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(undefined8 *)(iVar10 + 0x40) = *(undefined8 *)(iVar10 + 0x28);
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) <
                      *(int *)(iVar10 + 0x18)) {
                    dVar2 = *(double *)(iVar10 + 0x50) - 0.5;
                  }
                  else {
                    dVar2 = *(double *)(iVar10 + 0x50) + 0.5;
                  }
                  goto LAB_00431507;
                }
                if (iVar6 == 2) {
                  if (*(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368))
                      != 2000) {
                    *(undefined4 *)(iVar10 + 0x70) = 0;
                  }
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) <
                      *(int *)(iVar10 + 0x10)) {
                    dVar2 = *(double *)(iVar10 + 0x40) - 1.0;
                  }
                  else {
                    dVar2 = *(double *)(iVar10 + 0x40) + 1.0;
                  }
                  *(double *)(iVar10 + 0x28) = dVar2;
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  *(undefined8 *)(iVar10 + 0x40) = *(undefined8 *)(iVar10 + 0x28);
                  iVar10 = *(int *)(in_ECX + 0x194 + iVar8 * 4);
                  if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) <
                      *(int *)(iVar10 + 0x18)) {
                    dVar2 = *(double *)(iVar10 + 0x50) - 0.5;
                  }
                  else {
                    dVar2 = *(double *)(iVar10 + 0x50) + 0.5;
                  }
                  goto LAB_00431816;
                }
              }
            }
          }
LAB_0043187a:
          if (*local_74 == 0) {
            iVar10 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x18);
            iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
            local_70 = iVar8;
            if ((iVar10 <= iVar9) && (*(char *)(param_1 + 4 + in_ECX) != '\0')) {
              if (iVar10 < iVar9) {
                local_70 = param_1;
              }
              else if (iVar8 < param_1) {
                local_70 = param_1;
              }
            }
            iVar10 = *(int *)(in_ECX + 0x194 + local_70 * 4);
            iVar9 = *(int *)(iVar10 + 0x36c);
            if (iVar9 < 10) {
              *(int *)(iVar10 + 0x36c) = iVar9 + 1;
              iVar10 = *(int *)(in_ECX + 0x194 + local_70 * 4);
              iVar9 = *(int *)(iVar10 + 0x36c) + -1;
              if (local_74[7] < 0x3d) {
                local_64 = local_64 * 0x14 + 10;
              }
              else {
                local_64 = local_64 * 0x14;
              }
              *(int *)(iVar10 + 0x3c0 + iVar9 * 4) = local_64;
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              iVar10 = iVar9 * 4 + 0x370;
              iVar11 = *(int *)(iVar6 + 0x70) * 0x178;
              if (*(char *)(iVar6 + 0x80) == '\0') {
                *(int *)(iVar10 + *(int *)(in_ECX + 0x194 + local_70 * 4)) =
                     (*(int *)(iVar6 + 0x10) - *(int *)(iVar11 + 0x7f4 + *(int *)(iVar6 + 0x368))) +
                     local_74[3] + local_74[1];
                piVar7 = (int *)(iVar10 + *(int *)(in_ECX + 0x194 + local_70 * 4));
                iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10);
                if (iVar6 < *piVar7) goto LAB_004319da;
              }
              else {
                *(int *)(iVar10 + *(int *)(in_ECX + 0x194 + local_70 * 4)) =
                     ((*(int *)(iVar11 + 0x7f4 + *(int *)(iVar6 + 0x368)) - local_74[3]) -
                     local_74[1]) + *(int *)(iVar6 + 0x10);
                piVar7 = (int *)(iVar10 + *(int *)(in_ECX + 0x194 + local_70 * 4));
                iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x10);
                if (*piVar7 < iVar6) {
LAB_004319da:
                  *piVar7 = iVar6;
                }
              }
              iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              iVar11 = *(int *)(*(int *)(iVar6 + 0x70) * 0x178 + 0x7f8 + *(int *)(iVar6 + 0x368));
              iVar8 = *(int *)(*(int *)(in_ECX + 0x194 + iVar8 * 4) + 0x14);
              local_64 = (local_74[4] / 2 + *(int *)(iVar6 + 0x14) + local_74[2]) - iVar11;
              iVar11 = iVar8 - iVar11;
              if ((local_64 < iVar11) || (iVar11 = iVar8, iVar8 < local_64)) {
                local_64 = (local_64 + iVar11) / 2;
              }
              iVar8 = rand();
              *(int *)(*(int *)(in_ECX + 0x194 + local_70 * 4) + 0x398 + iVar9 * 4) =
                   iVar8 % 9 + *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) + -4 +
                   local_64;
              piVar7 = (int *)(*(int *)(in_ECX + 0x194 + local_70 * 4) + iVar10);
              iVar10 = rand();
              fVar12 = (float10)0;
              *piVar7 = *piVar7 + iVar10 % 9 + -4;
            }
          }
        }
      }
      local_5c = local_5c + 1;
      if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2e4) <= local_5c) {
        return;
      }
    }
  }
  return;
}

