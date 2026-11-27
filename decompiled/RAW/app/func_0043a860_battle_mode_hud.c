/* Function: FUN_0043a860 */
/* Address: 0x0043a860 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043a860(void)

{
  char *pcVar1;
  int iVar2;
  char *pcVar3;
  int in_ECX;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  int *piVar12;
  undefined4 *puVar13;
  undefined1 auStack_a4 [4];
  int local_a0;
  int local_9c;
  int *local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80 [29];
  uint local_c;
  
  local_c = DAT_0044eea4 ^ (uint)auStack_a4;
  local_98 = (int *)(in_ECX + 0x194);
  local_80[2] = 0;
  local_80[3] = 0;
  local_80[4] = 0;
  local_80[5] = 0;
  local_80[6] = 0;
  local_80[7] = 0;
  local_80[8] = 0;
  local_80[9] = 0;
  local_80[10] = 0;
  local_80[0xb] = 0;
  local_80[0xc] = 0;
  local_80[0xd] = 0;
  local_80[0xe] = 0;
  local_80[0xf] = 0;
  local_80[0x10] = 0;
  local_80[0x11] = 0;
  local_80[0x12] = 0;
  local_80[0x13] = 0;
  local_80[0x14] = 0;
  local_80[0x15] = 0;
  local_80[0x16] = 0;
  local_80[0x17] = 0;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80[0] = 0;
  local_80[1] = 0;
  local_a0 = 0;
  do {
    if (*(char *)(in_ECX + 4 + local_a0) != '\0') {
      iVar11 = *local_98;
      if (((0 < *(int *)(iVar11 + 0x344)) && (*(int *)(iVar11 + 0x344) < 3)) && (0x13 < local_a0)) {
        iVar7 = *(int *)(*local_98 + 0x344);
        iVar2 = *(int *)(*(int *)(*local_98 + 0x368) + 0x6f4);
        if ((((iVar2 - 0x1eU < 10) && (iVar2 != 0x26)) || ((iVar2 == 0x7a || (iVar2 == 0x7b)))) &&
           (iVar4 = 0, 0 < DAT_0044d37c)) {
          do {
            if ((&DAT_0044d350)[iVar4] == iVar2) {
              local_80[(iVar7 + -1) * DAT_0044d37c + iVar4 + 2] =
                   local_80[(iVar7 + -1) * DAT_0044d37c + iVar4 + 2] + 1;
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < DAT_0044d37c);
        }
      }
      if ((*(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0) &&
         (iVar7 = *(int *)(iVar11 + 0x2fc), 0 < iVar7)) {
        if (*(int *)(iVar11 + 0x364) == 1) {
          local_90 = local_90 + 1;
          local_88 = local_88 + iVar7;
        }
        else {
          local_8c = local_8c + 1;
          local_84 = local_84 + iVar7;
        }
      }
    }
    local_98 = local_98 + 1;
    local_a0 = local_a0 + 1;
  } while (local_a0 < 400);
  local_a0 = 0;
  if (-1 < DAT_0044d37c) {
    do {
      local_98 = (int *)0x0;
      if (0 < DAT_0044d37c) {
        local_9c = local_a0 * 4;
LAB_0043aa31:
        if ((0 < *(int *)((int)&DAT_0044d6a8 + local_9c)) &&
           (*(int *)((int)local_80 + local_9c + 8) < *(int *)((int)&DAT_0044d700 + local_9c))) {
          iVar11 = 0x14;
          do {
            if (*(char *)(in_ECX + 4 + iVar11) == '\0') {
              piVar12 = *(int **)(in_ECX + 0x7d4);
              piVar9 = piVar12 + 0x13608e0;
              iVar7 = 0;
              if (0 < *piVar9) {
                goto LAB_0043aa90;
              }
              break;
            }
            iVar11 = iVar11 + 1;
          } while (iVar11 < 400);
        }
        goto LAB_0043adcc;
      }
LAB_0043adea:
      local_a0 = local_a0 + DAT_0044d37c;
    } while (local_a0 <= DAT_0044d37c);
  }
  local_94 = DAT_0044d37c * 4;
  piVar12 = &DAT_0044d6a8;
  piVar9 = local_80;
  local_9c = 2;
  do {
    if (0 < DAT_0044d37c + -2) {
      iVar11 = *piVar9;
      piVar5 = piVar12;
      iVar7 = DAT_0044d37c + -2;
      do {
        iVar11 = iVar11 + *piVar5;
        piVar5 = piVar5 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *piVar9 = iVar11;
    }
    iVar11 = local_80[1];
    piVar12 = piVar12 + DAT_0044d37c;
    piVar9 = piVar9 + 1;
    local_9c = local_9c + -1;
  } while (local_9c != 0);
  DAT_00451b7c = 1;
  if ((0 < local_80[0]) && (0 < local_80[1])) {
    DAT_00451b7c = 0;
  }
  if ((0 < local_90) && (0 < local_8c)) {
    DAT_00451b7c = 0;
  }
  sprintf((char *)(local_80 + 2),"Man: %3d     HP: %4d     Reserve: %3d     Die: %3d",local_90,
          local_88,local_80[0],DAT_00451b64);
  FUN_00401290(DAT_00455608,local_80 + 2,0,0xffb294,10,0x6e);
  sprintf((char *)(local_80 + 2),"Man: %3d     HP: %4d     Reserve: %3d     Die: %3d",local_8c,
          local_84,iVar11,DAT_00451b68);
  FUN_00401290(DAT_00455608,local_80 + 2,0,0xada6ff,0x1c2,0x6e);
  iVar11 = DAT_0044d380;
  _DAT_00451c80 = _DAT_00451c80 & 0xffffff00;
  if (DAT_0044d380 == 0) {
    _DAT_00451c80 = 0x6f72655a;
    ram0x00451c84 = (uint)_DAT_00451c85 << 8;
    goto LAB_0043b094;
  }
  if (DAT_0044d380 == 1) {
    DAT_00451c80 = 'B';
    DAT_00451c81._0_1_ = 'a';
    DAT_00451c81._1_1_ = 'l';
    DAT_00451c81._2_1_ = 'a';
    DAT_00451c81._3_1_ = 'n';
    DAT_00451c85 = 'c';
    DAT_00451c81_4._1_1_ = 'e';
    DAT_00451c81_4._2_1_ = 'd';
    _DAT_00451c88 = (uint)DAT_00451c88_1 << 8;
LAB_0043b032:
    if (DAT_00451b74 == 0) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        pcVar1 = (char *)((int)puVar13 + 1);
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      } while (*pcVar1 != '\0');
      uVar8 = 0x295328;
LAB_0043b092:
      *puVar13 = uVar8;
    }
    else if (DAT_00451b74 == 1) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        pcVar1 = (char *)((int)puVar13 + 1);
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      } while (*pcVar1 != '\0');
      *puVar13 = 0x294d28;
    }
    else if (DAT_00451b74 == 2) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        pcVar1 = (char *)((int)puVar13 + 1);
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      } while (*pcVar1 != '\0');
      uVar8 = 0x294c28;
      goto LAB_0043b092;
    }
  }
  else {
    if (DAT_0044d380 == 2) {
      DAT_00451c80 = 'I';
      DAT_00451c81._0_1_ = 'n';
      DAT_00451c81._1_1_ = 'f';
      DAT_00451c81._2_1_ = 'e';
      DAT_00451c81._3_1_ = 'r';
      DAT_00451c85 = 'i';
      DAT_00451c81_4._1_1_ = 'o';
      DAT_00451c81_4._2_1_ = 'r';
      _DAT_00451c88 = (uint)DAT_00451c88_1 << 8;
      goto LAB_0043b032;
    }
    if (DAT_0044d380 == 3) {
      DAT_00451c80 = 'R';
      DAT_00451c81._0_1_ = 'a';
      DAT_00451c81._1_1_ = 'n';
      DAT_00451c81._2_1_ = 'g';
      DAT_00451c81._3_1_ = 'e';
      DAT_00451c85 = 'd';
      DAT_00451c81_4._1_1_ = ' ';
      DAT_00451c81_4._2_1_ = 'a';
      DAT_00451c88 = 't';
      DAT_00451c88_1._0_1_ = 't';
      DAT_00451c88_1._1_1_ = 'a';
      DAT_00451c88_1._2_1_ = 'c';
      _DAT_00451c8c = 0x6b;
      goto LAB_0043b032;
    }
    if (DAT_0044d380 == 4) {
      DAT_00451c80 = 'M';
      DAT_00451c81._0_1_ = 'e';
      DAT_00451c81._1_1_ = 'l';
      DAT_00451c81._2_1_ = 'e';
      DAT_00451c81._3_1_ = 'e';
      DAT_00451c85 = ' ';
      DAT_00451c81_4._1_1_ = 'a';
      DAT_00451c81_4._2_1_ = 't';
      DAT_00451c88 = 't';
      DAT_00451c88_1._0_1_ = 'a';
      DAT_00451c88_1._1_1_ = 'c';
      DAT_00451c88_1._2_1_ = 'k';
      _DAT_00451c8c = _DAT_00451c8c & 0xff00;
      goto LAB_0043b032;
    }
    if (DAT_0044d380 == 5) {
      DAT_00451c80 = 'G';
      DAT_00451c81._0_1_ = 'i';
      DAT_00451c81._1_1_ = 'a';
      DAT_00451c81._2_1_ = 'n';
      ram0x00451c84 = CONCAT22(DAT_00451c81_4._1_2_,0x74);
      goto LAB_0043b032;
    }
    if (DAT_0044d380 == 6) {
      _DAT_00451c80 = 0x6c6c7546;
      ram0x00451c84 = (uint)_DAT_00451c85 << 8;
    }
    else if ((0 < DAT_0044d380) && (DAT_0044d380 < 6)) goto LAB_0043b032;
  }
LAB_0043b094:
  iVar7 = DAT_0044d758;
  if (DAT_0044d758 != 100) {
    if (iVar11 != -1) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        puVar10 = puVar13;
        puVar13 = (undefined4 *)((int)puVar10 + 1);
      } while (*(char *)((int)puVar10 + 1) != '\0');
      *(undefined4 *)((int)puVar10 + 1) = 0x20202020;
      *(undefined1 *)((int)puVar10 + 5) = 0;
    }
    sprintf((char *)&DAT_00451bb8,"Defense: %d.%d",iVar7 / 100,(iVar7 % 100) / 10);
    pcVar1 = (char *)&DAT_00451bb8;
    do {
      pcVar3 = pcVar1;
      pcVar1 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    puVar13 = (undefined4 *)&DAT_00451c7f;
    do {
      pcVar1 = (char *)((int)puVar13 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    } while (*pcVar1 != '\0');
    puVar10 = &DAT_00451bb8;
    for (uVar6 = (uint)(pcVar3 + -0x451bb7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    for (uVar6 = (uint)(pcVar3 + -0x451bb7) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar13 = *(undefined1 *)puVar10;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    }
  }
  FUN_00423a70(&DAT_00451c80,10,0x85,0x40,4,1,0);
  iVar11 = DAT_0044d384;
  _DAT_00451c80 = _DAT_00451c80 & 0xffffff00;
  if (DAT_0044d384 == 0) {
    _DAT_00451c80 = 0x6f72655a;
    ram0x00451c84 = (uint)_DAT_00451c85 << 8;
    goto LAB_0043b2e2;
  }
  if (DAT_0044d384 == 1) {
    DAT_00451c80 = 'B';
    DAT_00451c81._0_1_ = 'a';
    DAT_00451c81._1_1_ = 'l';
    DAT_00451c81._2_1_ = 'a';
    DAT_00451c81._3_1_ = 'n';
    DAT_00451c85 = 'c';
    DAT_00451c81_4._1_1_ = 'e';
    DAT_00451c81_4._2_1_ = 'd';
    _DAT_00451c88 = (uint)DAT_00451c88_1 << 8;
  }
  else if (DAT_0044d384 == 2) {
    DAT_00451c80 = 'I';
    DAT_00451c81._0_1_ = 'n';
    DAT_00451c81._1_1_ = 'f';
    DAT_00451c81._2_1_ = 'e';
    DAT_00451c81._3_1_ = 'r';
    DAT_00451c85 = 'i';
    DAT_00451c81_4._1_1_ = 'o';
    DAT_00451c81_4._2_1_ = 'r';
    _DAT_00451c88 = (uint)DAT_00451c88_1 << 8;
  }
  else if (DAT_0044d384 == 3) {
    DAT_00451c80 = 'R';
    DAT_00451c81._0_1_ = 'a';
    DAT_00451c81._1_1_ = 'n';
    DAT_00451c81._2_1_ = 'g';
    DAT_00451c81._3_1_ = 'e';
    DAT_00451c85 = 'd';
    DAT_00451c81_4._1_1_ = ' ';
    DAT_00451c81_4._2_1_ = 'a';
    DAT_00451c88 = 't';
    DAT_00451c88_1._0_1_ = 't';
    DAT_00451c88_1._1_1_ = 'a';
    DAT_00451c88_1._2_1_ = 'c';
    _DAT_00451c8c = 0x6b;
  }
  else if (DAT_0044d384 == 4) {
    DAT_00451c80 = 'M';
    DAT_00451c81._0_1_ = 'e';
    DAT_00451c81._1_1_ = 'l';
    DAT_00451c81._2_1_ = 'e';
    DAT_00451c81._3_1_ = 'e';
    DAT_00451c85 = ' ';
    DAT_00451c81_4._1_1_ = 'a';
    DAT_00451c81_4._2_1_ = 't';
    DAT_00451c88 = 't';
    DAT_00451c88_1._0_1_ = 'a';
    DAT_00451c88_1._1_1_ = 'c';
    DAT_00451c88_1._2_1_ = 'k';
    _DAT_00451c8c = _DAT_00451c8c & 0xff00;
  }
  else if (DAT_0044d384 == 5) {
    DAT_00451c80 = 'G';
    DAT_00451c81._0_1_ = 'i';
    DAT_00451c81._1_1_ = 'a';
    DAT_00451c81._2_1_ = 'n';
    ram0x00451c84 = CONCAT22(DAT_00451c81_4._1_2_,0x74);
  }
  else {
    if (DAT_0044d384 == 6) {
      _DAT_00451c80 = 0x6c6c7546;
      ram0x00451c84 = (uint)_DAT_00451c85 << 8;
      goto LAB_0043b2e2;
    }
    if ((DAT_0044d384 < 1) || (5 < DAT_0044d384)) goto LAB_0043b2e2;
  }
  if (DAT_00451b78 == 0) {
    puVar13 = (undefined4 *)&DAT_00451c7f;
    do {
      pcVar1 = (char *)((int)puVar13 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    } while (*pcVar1 != '\0');
    uVar8 = 0x295328;
  }
  else {
    if (DAT_00451b78 == 1) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        pcVar1 = (char *)((int)puVar13 + 1);
        puVar13 = (undefined4 *)((int)puVar13 + 1);
      } while (*pcVar1 != '\0');
      *puVar13 = 0x294d28;
      goto LAB_0043b2e2;
    }
    if (DAT_00451b78 != 2) goto LAB_0043b2e2;
    puVar13 = (undefined4 *)&DAT_00451c7f;
    do {
      pcVar1 = (char *)((int)puVar13 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    } while (*pcVar1 != '\0');
    uVar8 = 0x294c28;
  }
  *puVar13 = uVar8;
LAB_0043b2e2:
  iVar7 = DAT_0044d75c;
  if (DAT_0044d75c != 100) {
    if (iVar11 != -1) {
      puVar13 = (undefined4 *)&DAT_00451c7f;
      do {
        puVar10 = puVar13;
        puVar13 = (undefined4 *)((int)puVar10 + 1);
      } while (*(char *)((int)puVar10 + 1) != '\0');
      *(undefined4 *)((int)puVar10 + 1) = 0x20202020;
      *(undefined1 *)((int)puVar10 + 5) = 0;
    }
    sprintf((char *)&DAT_00451bb8,"Defense: %d.%d",iVar7 / 100,(iVar7 % 100) / 10);
    pcVar1 = (char *)&DAT_00451bb8;
    do {
      pcVar3 = pcVar1;
      pcVar1 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    puVar13 = (undefined4 *)&DAT_00451c7f;
    do {
      pcVar1 = (char *)((int)puVar13 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    } while (*pcVar1 != '\0');
    puVar10 = &DAT_00451bb8;
    for (uVar6 = (uint)(pcVar3 + -0x451bb7) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    for (uVar6 = (uint)(pcVar3 + -0x451bb7) & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined1 *)puVar13 = *(undefined1 *)puVar10;
      puVar10 = (undefined4 *)((int)puVar10 + 1);
      puVar13 = (undefined4 *)((int)puVar13 + 1);
    }
  }
  pcVar1 = &DAT_00451c80;
  do {
    pcVar3 = pcVar1;
    pcVar1 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  FUN_00423a70(&DAT_00451c80,(int)(pcVar3 + -0x451c80) * -8 + 0x311,0x85,0x40,4,2,0);
  __security_check_cookie(local_c ^ (uint)auStack_a4);
  return;
  while( true ) {
    iVar7 = iVar7 + 1;
    piVar12 = piVar12 + 1;
    if (*piVar9 <= iVar7) break;
LAB_0043aa90:
    if (*(int *)(*piVar12 + 0x6f4) == (&DAT_0044d350)[(int)local_98]) {
      *(undefined1 *)(in_ECX + 4 + iVar11) = 1;
      local_94 = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar7 * 4);
      iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
      FUN_004061d0();
      *(int *)(iVar7 + 0x368) = local_94;
      uVar8 = *(undefined4 *)(local_94 + 0x90);
      *(undefined8 *)(iVar7 + 0x58) = 0x4075e00000000000;
      *(undefined4 *)(iVar7 + 0x31c) = uVar8;
      *(undefined8 *)(iVar7 + 0x60) = 0;
      *(undefined8 *)(iVar7 + 0x68) = 0x4072c00000000000;
      iVar7 = DAT_0044d024 * 0x990 + *(int *)(in_ECX + 0x7d4);
      iVar7 = FUN_00417170(0x128,*(int *)(iVar7 + 0x4d45db8) - *(int *)(iVar7 + 0x4d45db4));
      *(int *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x18) =
           iVar7 + *(int *)(DAT_0044d024 * 0x990 + 0x4d45db4 + *(int *)(in_ECX + 0x7d4));
      iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
      if (local_a0 == 0) {
        *(uint *)(iVar7 + 0x10) =
             (-(uint)(*(int *)(*(int *)(iVar7 + 0x368) + 0x6f8) != 0) & 0x96) - 100;
      }
      else if (*(int *)(*(int *)(iVar7 + 0x368) + 0x6f8) == 0) {
        *(int *)(iVar7 + 0x10) =
             *(int *)(DAT_0044d024 * 0x990 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + 100;
      }
      else {
        *(int *)(iVar7 + 0x10) =
             *(int *)(DAT_0044d024 * 0x990 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + -0x32;
      }
      iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
      *(double *)(iVar7 + 0x58) = (double)*(int *)(iVar7 + 0x10);
      iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
      *(double *)(iVar7 + 0x68) = (double)*(int *)(iVar7 + 0x18);
      iVar7 = (&DAT_0044d350)[(int)local_98];
      uVar8 = 500;
      if (((local_a0 == 0) &&
          (iVar2 = *(int *)(in_ECX + 0x194 + iVar11 * 4),
          *(int *)(*(int *)(iVar2 + 0x368) + 0x6f8) == 0)) &&
         (*(undefined4 *)(iVar2 + 0x318) = 0x8c, iVar7 == 0x25)) {
        *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x318) = 0x72;
LAB_0043ac43:
        uVar8 = 200;
LAB_0043ac48:
        if ((iVar7 == 0x27) || (iVar7 == 0x21)) {
          uVar8 = 0x96;
        }
        if (iVar7 == 0x22) {
          uVar8 = 100;
        }
        else {
          if ((iVar7 == 0x1f) || (iVar7 == 0x1e)) {
            uVar8 = 0x32;
          }
          if (iVar7 == 0x7a) {
            uVar8 = 200;
          }
        }
      }
      else {
        if (iVar7 != 0x24) {
          if (((iVar7 == 0x25) || (iVar7 == 0x23)) || (iVar7 == 0x20)) goto LAB_0043ac43;
          goto LAB_0043ac48;
        }
        uVar8 = 0xfa;
      }
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x308) = 500;
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x300) = uVar8;
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x2fc) = uVar8;
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x304) = uVar8;
      *(int *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x354) = iVar11;
      iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
      iVar2 = *(int *)(*(int *)(iVar7 + 0x368) + 0x6f8);
      if ((iVar2 == 0) || (iVar2 == 5)) {
        *(undefined4 *)(iVar7 + 8) = 0x14;
        iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
        *(bool *)(iVar7 + 0x80) =
             *(int *)(DAT_0044d024 * 0x990 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) / 2 <
             *(int *)(iVar7 + 0x10);
        *(int *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x364) = local_a0 / DAT_0044d37c + 1;
        *(int *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x344) = local_a0 / DAT_0044d37c + 1;
        *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x14) = 0xfffffed4;
        iVar7 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
        *(double *)(iVar7 + 0x60) = (double)*(int *)(iVar7 + 0x14);
        *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x48) = 0;
      }
      else {
        *(undefined4 *)(iVar7 + 8) = 0;
        *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x364) = 0;
        *(int *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x344) = local_a0 / DAT_0044d37c + 1;
        *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar11 * 4) + 0x14) = 0xfffffed4;
        iVar11 = *(int *)(in_ECX + 0x194 + iVar11 * 4);
        *(double *)(iVar11 + 0x60) = (double)*(int *)(iVar11 + 0x14);
      }
      *(int *)((int)&DAT_0044d6a8 + local_9c) = *(int *)((int)&DAT_0044d6a8 + local_9c) + -1;
      break;
    }
  }
LAB_0043adcc:
  local_98 = (int *)((int)local_98 + 1);
  local_9c = local_9c + 4;
  if (DAT_0044d37c <= (int)local_98) goto LAB_0043adea;
  goto LAB_0043aa31;
}

