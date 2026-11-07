/* Function: FUN_0041a5a0 */
/* Address: 0x0041a5a0 */

void FUN_0041a5a0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int in_ECX;
  int iVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 local_674;
  char *local_670;
  int local_66c;
  int local_668;
  undefined4 local_664;
  int local_660;
  int local_65c;
  int aiStack_658 [399];
  char cStack_19;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_674;
  iVar7 = 0;
  local_664 = param_1;
  iVar1 = 0;
  do {
    if (*(char *)(in_ECX + 4 + iVar1) != '\0') {
      aiStack_658[iVar7] = iVar1;
      iVar7 = iVar7 + 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 400);
  local_668 = iVar7;
  if (0 < iVar7) {
    local_66c = iVar7 + -1;
    while (-1 < local_66c) {
      iVar1 = 0;
      if (0 < local_66c) {
        do {
          iVar7 = aiStack_658[iVar1];
          if (*(int *)(*(int *)(in_ECX + 0x194 + aiStack_658[iVar1 + 1] * 4) + 0x18) <
              *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x18)) {
            aiStack_658[iVar1] = aiStack_658[iVar1 + 1];
            aiStack_658[iVar1 + 1] = iVar7;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < local_66c);
        iVar7 = local_668;
      }
      local_66c = local_66c + -1;
    }
  }
  local_65c = DAT_0044d024;
  local_66c = 0;
  if (0 < iVar7) {
    do {
      iVar7 = aiStack_658[local_66c];
      iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      local_674 = *(char **)(iVar1 + 8);
      local_670 = local_674;
      if ((int)local_674 < 0) {
        local_670 = (char *)-(int)local_674;
      }
      if (((((-1 < *(int *)(iVar1 + 0x98)) &&
            (*(int *)(*(int *)(iVar1 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar1 + 0x368)) != 0xbbd))
           && (*(int *)(*(int *)(iVar1 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar1 + 0x368)) != 0x270d)
           ) && ((iVar1 = *(int *)(*(int *)(iVar1 + 0x368) + 0x6f4), iVar1 != 0xdf &&
                 (iVar1 != 0xe0)))) && (-0x46 < (int)local_674)) {
        uVar8 = (uint)local_670 & 0x80000003;
        if ((int)uVar8 < 0) {
          uVar8 = (uVar8 - 1 | 0xfffffffc) + 1;
        }
        if ((int)uVar8 < 2) {
          iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
          iVar5 = *(int *)(in_ECX + 0x7d4) + local_65c * 0x990;
          FUN_0043f010(((*(int *)(iVar1 + 0x1c) - *(int *)(iVar5 + 0x4d45dc4) / 2) +
                       *(int *)(iVar1 + 0x10)) - DAT_00450bc4,
                       *(int *)(iVar1 + 0x18) - *(int *)(iVar5 + 0x4d45dc8) / 2,0xffffffff,1,0,
                       param_1);
        }
      }
      uVar8 = (uint)local_670 & 0x80000003;
      if ((int)uVar8 < 0) {
        uVar8 = (uVar8 - 1 | 0xfffffffc) + 1;
      }
      if (((int)uVar8 < 2) && (-0x19 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 8))) {
        FUN_0040de30(DAT_00450bc4,param_1,param_2);
      }
      iVar1 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x30c);
      if (1 < iVar1) {
        if (iVar1 < 10) {
          local_674 = (char *)0x2078;
          cVar6 = (char)(iVar1 % 10);
        }
        else {
          iVar1 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x30c);
          cVar6 = (char)((iVar1 / 10) % 10);
          local_674 = (char *)(uint)CONCAT12((char)(iVar1 % 10) + '0',0x2078);
        }
        pcVar2 = (char *)&local_674;
        local_674._0_2_ = CONCAT11(cVar6 + '0',(char)local_674);
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        iVar5 = ((*(int *)(iVar1 + 0x1c) - ((uint)(((int)pcVar2 - ((int)&local_674 + 1)) * 9) >> 1))
                + *(int *)(iVar1 + 0x10)) - DAT_00450bc4;
        pcVar2 = (char *)&local_674;
        local_670 = (char *)((*(int *)(iVar1 + 0x18) -
                             *(int *)(*(int *)(iVar1 + 0x70) * 0x178 + 0x7f8 +
                                     *(int *)(iVar1 + 0x368))) + -7 + *(int *)(iVar1 + 0x14));
        iVar1 = 0;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        if (0 < (int)pcVar2 - ((int)&local_674 + 1)) {
          do {
            FUN_0043f010(iVar5,local_670,(int)*(char *)((int)aiStack_658 + iVar1 + -0x1c),1,0,
                         DAT_00455608);
            pcVar2 = (char *)&local_674;
            iVar5 = iVar5 + 9;
            iVar1 = iVar1 + 1;
            do {
              cVar6 = *pcVar2;
              pcVar2 = pcVar2 + 1;
            } while (cVar6 != '\0');
          } while (iVar1 < (int)pcVar2 - ((int)&local_674 + 1));
        }
      }
      if (((iVar7 < 0x14) ||
          ((iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4), *(int *)(iVar1 + 0x364) != 5 &&
           (*(int *)(*(int *)(iVar1 + 0x368) + 0x6f8) == 0)))) &&
         (iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4), -0x19 < *(int *)(iVar1 + 8))) {
        local_18 = 0x6d6f43;
        local_14 = 0;
        local_10 = 0;
        local_c = 0;
        local_8 = 0;
        if (iVar7 < 10) {
          local_674 = &DAT_0044fcc0 + iVar7 * 0xb;
        }
        else {
          local_674 = (char *)&local_18;
        }
        if ((iVar7 < 10) && ((&DAT_00450b4c)[iVar7] == -1)) {
          local_18 = 0x6d005b;
          pcVar2 = local_674;
          do {
            cVar6 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar6 != '\0');
          pcVar11 = &cStack_19;
          do {
            pcVar10 = pcVar11 + 1;
            pcVar11 = pcVar11 + 1;
          } while (*pcVar10 != '\0');
          pcVar10 = local_674;
          for (uVar8 = (uint)((int)pcVar2 - (int)local_674) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
            pcVar10 = pcVar10 + 4;
            pcVar11 = pcVar11 + 4;
          }
          for (uVar8 = (int)pcVar2 - (int)local_674 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pcVar11 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            pcVar11 = pcVar11 + 1;
          }
          pcVar2 = &cStack_19;
          do {
            pcVar11 = pcVar2 + 1;
            pcVar2 = pcVar2 + 1;
          } while (*pcVar11 != '\0');
          pcVar2[0] = ']';
          pcVar2[1] = '\0';
          local_674 = (char *)&local_18;
        }
        pcVar2 = local_674;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        iVar5 = ((*(int *)(iVar1 + 0x1c) - ((uint)(((int)pcVar2 - (int)(local_674 + 1)) * 9) >> 1))
                + *(int *)(iVar1 + 0x10)) - DAT_00450bc4;
        local_670 = (char *)(*(int *)(iVar1 + 0x18) + 3);
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        pcVar2 = local_674;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        if (((int)pcVar2 - (int)(local_674 + 1)) * -9 + 0x31a < iVar5) {
          pcVar2 = local_674;
          do {
            cVar6 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar6 != '\0');
          iVar5 = ((int)pcVar2 - (int)(local_674 + 1)) * -9 + 0x31a;
        }
        iVar1 = 0;
        pcVar2 = local_674;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        if (0 < (int)pcVar2 - (int)(local_674 + 1)) {
          do {
            iVar3 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x364);
            if (iVar3 == 1) {
              iVar3 = (int)local_674[iVar1];
            }
            else if (iVar3 == 2) {
              cVar6 = local_674[iVar1];
LAB_0041ab1b:
              iVar3 = (int)cVar6;
            }
            else if (iVar3 == 3) {
              iVar3 = (int)local_674[iVar1];
            }
            else {
              if (iVar3 != 4) {
                cVar6 = local_674[iVar1];
                goto LAB_0041ab1b;
              }
              iVar3 = (int)local_674[iVar1];
            }
            FUN_0043f010(iVar5,local_670,iVar3,1,0,DAT_00455608);
            iVar5 = iVar5 + 9;
            iVar1 = iVar1 + 1;
            pcVar2 = local_674;
            do {
              cVar6 = *pcVar2;
              pcVar2 = pcVar2 + 1;
            } while (cVar6 != '\0');
          } while (iVar1 < (int)pcVar2 - (int)(local_674 + 1));
        }
      }
      else if (((((0x13 < iVar7) && (-0x19 < *(int *)(iVar1 + 8))) &&
                (*(int *)(*(int *)(iVar1 + 0x368) + 0x6f8) == 0)) && (*(int *)(iVar1 + 0x364) == 5))
              && (((iVar1 = *(int *)(*(int *)(iVar1 + 0x368) + 0x6f4), iVar1 < 0x1e ||
                   (0x31 < iVar1)) || (iVar1 == 0x26)))) {
        pcVar2 = (char *)&local_674;
        local_674 = &Rsrc_Bitmap_MENU_CLIP7_404.field_0x28567;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        iVar5 = ((*(int *)(iVar1 + 0x1c) - ((uint)(((int)pcVar2 - ((int)&local_674 + 1)) * 9) >> 1))
                + *(int *)(iVar1 + 0x10)) - DAT_00450bc4;
        local_660 = *(int *)(iVar1 + 0x18) + 3;
        if (iVar5 < 0) {
          iVar5 = 0;
        }
        pcVar2 = (char *)&local_674;
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        if (((int)pcVar2 - ((int)&local_674 + 1)) * -9 + 0x31a < iVar5) {
          pcVar2 = (char *)&local_674;
          do {
            cVar6 = *pcVar2;
            pcVar2 = pcVar2 + 1;
          } while (cVar6 != '\0');
          iVar5 = ((int)pcVar2 - ((int)&local_674 + 1)) * -9 + 0x31a;
        }
        pcVar2 = (char *)&local_674;
        iVar1 = 0;
        local_670 = (char *)((int)&local_674 + 1);
        do {
          cVar6 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar6 != '\0');
        if (0 < (int)pcVar2 - ((int)&local_674 + 1)) {
          do {
            FUN_0043f010(iVar5,local_660,(int)*(char *)((int)aiStack_658 + iVar1 + -0x1c),1,0,
                         DAT_00455608);
            pcVar2 = (char *)&local_674;
            iVar5 = iVar5 + 9;
            iVar1 = iVar1 + 1;
            do {
              cVar6 = *pcVar2;
              pcVar2 = pcVar2 + 1;
            } while (cVar6 != '\0');
          } while (iVar1 < (int)pcVar2 - ((int)&local_674 + 1));
        }
      }
      param_1 = local_664;
      iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      iVar5 = *(int *)(iVar1 + 0x36c);
      if ((0 < iVar5) && (local_670 = (char *)0x0, 0 < iVar5)) {
        iVar3 = 0x3c0;
        do {
          iVar1 = *(int *)(iVar1 + iVar3);
          if (iVar1 < 5) {
            iVar5 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
            iVar1 = *(int *)(iVar5 + iVar3);
            iVar9 = *(int *)(iVar5 + -0x28 + iVar3) + -0x28;
            iVar5 = ((*(int *)(iVar5 + -0x50 + iVar3) + *(int *)(iVar5 + 0x1c)) - DAT_00450bc4) +
                    -0x33;
LAB_0041ad15:
            FUN_0043f010(iVar5,iVar9,iVar1,1,0,param_1);
            piVar4 = (int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + iVar3);
            *piVar4 = *piVar4 + 1;
          }
          else {
            if ((9 < iVar1) && (iVar1 < 0xf)) {
              iVar5 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
              iVar1 = *(int *)(iVar5 + iVar3) + -5;
              iVar9 = *(int *)(iVar5 + -0x28 + iVar3) + -0x18;
              iVar5 = ((*(int *)(iVar5 + -0x50 + iVar3) + *(int *)(iVar5 + 0x1c)) - DAT_00450bc4) +
                      -0x1e;
              goto LAB_0041ad15;
            }
            if ((iVar1 < 0x14) || (0x1c < iVar1)) {
              if ((iVar1 < 0x1e) || (0x26 < iVar1)) {
                if (local_670 == (char *)(iVar5 + -1)) {
                  piVar4 = (int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x36c);
                  *piVar4 = *piVar4 + -1;
                }
              }
              else {
                iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
                FUN_0043f010(((*(int *)(iVar1 + -0x50 + iVar3) + *(int *)(iVar1 + 0x1c)) -
                             DAT_00450bc4) + -0x1e,*(int *)(iVar1 + -0x28 + iVar3) + -0x18,
                             (*(int *)(iVar1 + iVar3) + -0x1e) / 2 + 0xf,1,0,param_1);
                piVar4 = (int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + iVar3);
                *piVar4 = *piVar4 + 1;
              }
            }
            else {
              iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
              FUN_0043f010(((*(int *)(iVar1 + -0x50 + iVar3) + *(int *)(iVar1 + 0x1c)) -
                           DAT_00450bc4) + -0x33,*(int *)(iVar1 + -0x28 + iVar3) + -0x28,
                           (*(int *)(iVar1 + iVar3) + -0x14) / 2 + 10,1,0,param_1);
              piVar4 = (int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + iVar3);
              *piVar4 = *piVar4 + 1;
            }
          }
          iVar1 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
          iVar5 = *(int *)(iVar1 + 0x36c);
          local_670 = local_670 + 1;
          iVar3 = iVar3 + 4;
        } while ((int)local_670 < iVar5);
      }
      local_66c = local_66c + 1;
    } while (local_66c < local_668);
  }
  __security_check_cookie(local_4 ^ (uint)&local_674);
  return;
}
