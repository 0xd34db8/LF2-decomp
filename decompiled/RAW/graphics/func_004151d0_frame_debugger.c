/* Function: FUN_004151d0 */
/* Address: 0x004151d0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004151d0(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar13;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int *piVar14;
  int iVar15;
  bool bVar16;
  undefined8 uVar17;
  undefined4 local_150;
  int *local_14c;
  int local_148;
  int local_144;
  int local_140;
  char local_13c [300];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00445dee;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_150;
  uVar4 = DAT_0044eea4 ^ (uint)(local_13c + -0x24);
  ExceptionList = &local_c;
  local_148 = param_2;
  DAT_0044f874 = DAT_0044f874 + 1 & 0x80000001;
  local_140 = param_3;
  local_144 = param_4;
  if ((int)DAT_0044f874 < 0) {
    DAT_0044f874 = (DAT_0044f874 - 1 | 0xfffffffe) + 1;
  }
  if (DAT_0044d01c == 1) {
    DAT_0044d01c = 0;
    local_14c = operator_new(0x1f50);
    local_4 = 0;
    if (local_14c == (int *)0x0) {
      DAT_0044f824 = 0;
    }
    else {
      DAT_0044f824 = FUN_0043ee50(0x40,"LF2_CURSOR2",0);
    }
    local_4 = 0xffffffff;
    pvVar5 = operator_new(0x420);
    if (pvVar5 == (void *)0x0) {
      pvVar5 = (void *)0x0;
    }
    else {
      FUN_004061d0();
      *(int *)((int)pvVar5 + 0x368) = param_1;
    }
    DAT_0044f870 = pvVar5;
  }
  iVar6 = FUN_00415140(0x22,uVar4);
  if (iVar6 != 0) {
    do {
      DAT_0044f86c = DAT_0044f86c + 1;
      if (399 < DAT_0044f86c) {
        DAT_0044f86c = 0;
      }
      iVar6 = FUN_0040d940(DAT_0044f86c);
    } while (iVar6 == 0);
  }
  iVar6 = FUN_00415140(0x21,uVar4);
  if (iVar6 != 0) {
    do {
      DAT_0044f86c = DAT_0044f86c + -1;
      if (DAT_0044f86c < 0) {
        DAT_0044f86c = 399;
      }
      iVar6 = FUN_0040d940(DAT_0044f86c);
    } while (iVar6 == 0);
  }
  iVar6 = FUN_00415140(0x41);
  if (iVar6 != 0) {
    DAT_0044f868 = (DAT_0044f868 + 1) % 3;
  }
  iVar6 = FUN_00415140(0x53);
  if (iVar6 != 0) {
    FUN_0040d0a0(param_6);
  }
  iVar6 = FUN_00415140(0x4d);
  if (iVar6 != 0) {
    DAT_0044f864 = 1 - DAT_0044f864;
  }
  iVar6 = FUN_00415140(0x4e);
  if (iVar6 != 0) {
    DAT_0044f860 = (DAT_0044f860 + 1) % 5;
  }
  iVar6 = FUN_00415140(0xd);
  pvVar5 = DAT_0044f870;
  if (iVar6 != 0) {
    *(int *)((int)DAT_0044f870 + 0x70) = DAT_0044f86c;
    *(undefined4 *)((int)pvVar5 + 0x88) = 0;
  }
  FUN_0040d960(0,0);
  iVar6 = DAT_0044f86c;
  if (DAT_0044f860 == 0) {
    iVar7 = FUN_00415140(0x26);
    if (iVar7 != 0) {
      piVar14 = (int *)(iVar6 * 0x178 + 0x7f8 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    iVar7 = FUN_00415140(0x28);
    if (iVar7 != 0) {
      piVar14 = (int *)(iVar6 * 0x178 + 0x7f8 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    iVar7 = FUN_00415140(0x25);
    if (iVar7 != 0) {
      piVar14 = (int *)(iVar6 * 0x178 + 0x7f4 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    iVar7 = FUN_00415140(0x27);
    if (iVar7 != 0) {
      piVar14 = (int *)(iVar6 * 0x178 + 0x7f4 + param_1);
      *piVar14 = *piVar14 + -1;
    }
  }
  else if (DAT_0044f860 == 1) {
    iVar7 = FUN_00415140(0x43);
    if (iVar7 != 0) {
      *(int *)(iVar6 * 0x178 + 0x82c + param_1) =
           (*(int *)(iVar6 * 0x178 + 0x82c + param_1) + 1) % 3;
    }
    if (DAT_0045539e == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x834 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_004553a0 == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x834 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    if (DAT_0045539d == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x830 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_0045539f == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x830 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    iVar7 = FUN_00415140(0xdb);
    if (iVar7 != 0) {
      iVar7 = iVar6 * 0x178;
      piVar14 = (int *)(iVar7 + 0x840 + param_1);
      *piVar14 = *piVar14 + -1;
      if (*(int *)(iVar7 + 0x840 + param_1) < 0x82) {
        *(undefined4 *)(iVar7 + 0x840 + param_1) = 0x90;
      }
    }
    iVar7 = FUN_00415140(0xdd);
    if (iVar7 != 0) {
      iVar7 = iVar6 * 0x178;
      piVar14 = (int *)(iVar7 + 0x840 + param_1);
      *piVar14 = *piVar14 + 1;
      if (0x90 < *(int *)(iVar7 + 0x840 + param_1)) {
        *(undefined4 *)(iVar7 + 0x840 + param_1) = 0x82;
      }
    }
  }
  else if (DAT_0044f860 == 2) {
    iVar7 = FUN_00415140(0x57);
    if (iVar7 != 0) {
      *(int *)(iVar6 * 0x178 + 0x87c + param_1) =
           (*(int *)(iVar6 * 0x178 + 0x87c + param_1) + 1) % 3;
    }
    iVar7 = iVar6 * 0x178 + param_1;
    if (((*(int *)(iVar6 * 0x178 + 0x880 + param_1) == 0) && (*(int *)(iVar7 + 0x884) == 0)) &&
       (0 < iVar6)) {
      *(undefined4 *)(iVar7 + 0x880) = *(undefined4 *)(iVar7 + 0x708);
      *(undefined4 *)(iVar7 + 0x884) = *(undefined4 *)(iVar7 + 0x70c);
      *(undefined4 *)(iVar7 + 0x888) = *(undefined4 *)(iVar7 + 0x710);
    }
    if (DAT_0045539e == 'd') {
      *(int *)(iVar7 + 0x884) = *(int *)(iVar7 + 0x884) + -1;
    }
    if (DAT_004553a0 == 'd') {
      *(int *)(iVar7 + 0x884) = *(int *)(iVar7 + 0x884) + 1;
    }
    if (DAT_0045539d == 'd') {
      *(int *)(iVar7 + 0x880) = *(int *)(iVar7 + 0x880) + -1;
    }
    if (DAT_0045539f == 'd') {
      *(int *)(iVar7 + 0x880) = *(int *)(iVar7 + 0x880) + 1;
    }
    iVar13 = FUN_00415140(0xdb);
    iVar7 = DAT_0044f868;
    if (iVar13 != 0) {
      *(int *)(extraout_ECX + 0x888) = *(int *)(extraout_ECX + 0x888) + -1;
      if (iVar7 == 1) {
        *(undefined4 *)(extraout_ECX + 0x888) = 10;
      }
      else if ((iVar7 == 0) && (*(int *)(extraout_ECX + 0x888) < 0x14)) {
        *(undefined4 *)(extraout_ECX + 0x888) = 0x23;
      }
    }
    uVar17 = FUN_00415140(0xdd);
    iVar7 = (int)((ulonglong)uVar17 >> 0x20);
    if ((int)uVar17 != 0) {
      *(int *)(extraout_ECX_00 + 0x888) = *(int *)(extraout_ECX_00 + 0x888) + 1;
      if (iVar7 == 1) {
        *(undefined4 *)(extraout_ECX_00 + 0x888) = 10;
      }
      else if ((iVar7 == 0) && (0x23 < *(int *)(extraout_ECX_00 + 0x888))) {
        *(undefined4 *)(extraout_ECX_00 + 0x888) = 0x14;
      }
    }
  }
  else if (DAT_0044f860 == 3) {
    if (DAT_0045539e == 'd') {
      piVar14 = (int *)(DAT_0044f86c * 0x178 + 0x804 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_004553a0 == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x804 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    if (DAT_0045539d == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x800 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_0045539f == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x800 + param_1);
      *piVar14 = *piVar14 + 1;
    }
  }
  else if (DAT_0044f860 == 4) {
    if (DAT_0045539e == 'd') {
      piVar14 = (int *)(DAT_0044f86c * 0x178 + 0x828 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_004553a0 == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x828 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    if (DAT_0045539d == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x824 + param_1);
      *piVar14 = *piVar14 + -1;
    }
    if (DAT_0045539f == 'd') {
      piVar14 = (int *)(iVar6 * 0x178 + 0x824 + param_1);
      *piVar14 = *piVar14 + 1;
    }
    iVar7 = FUN_00415140(0x42);
    if (iVar7 != 0) {
      iVar7 = iVar6 * 0x178 + param_1;
      if (*(int *)(iVar6 * 0x178 + 0x824 + param_1) == 0) {
        *(undefined4 *)(iVar7 + 0x824) = 1;
        if ((0 < iVar6) && (0 < *(int *)(iVar7 + 0x6ac))) {
          *(int *)(iVar7 + 0x824) = *(int *)(iVar7 + 0x6ac);
          *(undefined4 *)(iVar7 + 0x828) = *(undefined4 *)(iVar7 + 0x6b0);
        }
      }
      else {
        *(undefined4 *)(iVar7 + 0x824) = 0;
      }
    }
  }
  iVar7 = FUN_00415140(0x6b);
  if (iVar7 != 0) {
    piVar14 = (int *)(iVar6 * 0x178 + 0x7b0 + param_1);
    *piVar14 = *piVar14 + 1;
  }
  iVar7 = FUN_00415140(0x6d);
  if (iVar7 != 0) {
    piVar14 = (int *)(iVar6 * 0x178 + 0x7b0 + param_1);
    *piVar14 = *piVar14 + -1;
    if (*piVar14 == 0) {
      *(undefined4 *)(iVar6 * 0x178 + 0x7b0 + param_1) = 0;
    }
  }
  if (DAT_0044f864 == 0) {
    iVar7 = FUN_00415140(0x2d);
    if (iVar7 != 0) {
      iVar7 = iVar6 * 0x178 + param_1;
      *(int *)(iVar7 + 0x8cc) = *(int *)(iVar7 + 0x8cc) + 1;
      if (*(int *)(iVar7 + 0x8cc) == 1) {
        pvVar5 = malloc(400);
        *(void **)(iVar7 + 0x8d4) = pvVar5;
      }
      puVar8 = (undefined4 *)(*(int *)(iVar7 + 0x8cc) * 0x50 + -0x50 + *(int *)(iVar7 + 0x8d4));
      puVar8[5] = 0;
      puVar8[6] = 0;
      puVar8[7] = 0;
      puVar8[8] = 0;
      puVar8[9] = 0;
      puVar8[10] = 0;
      puVar8[0xb] = 0;
      puVar8[0xc] = 0;
      puVar8[0xd] = 0;
      puVar8[0xe] = 0;
      puVar8[0xf] = 0;
      puVar8[0x10] = 0;
      puVar8[0x11] = 0;
      puVar8[0x12] = 0;
      puVar8[0x13] = 0;
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0;
      puVar8[4] = 10;
      puVar8[3] = 10;
      DAT_0044f85c = (int *)(*(int *)(iVar7 + 0x8cc) + -1);
    }
    piVar14 = DAT_0044f85c;
    iVar7 = FUN_00415140(0x2e);
    if (iVar7 != 0) {
      iVar7 = *(int *)(iVar6 * 0x178 + 0x8cc + param_1);
      iVar13 = iVar6 * 0x178 + param_1;
      if (0 < iVar7) {
        if ((int)piVar14 < iVar7 + -1) {
          local_150 = piVar14;
          if ((int)piVar14 < iVar7) {
            iVar7 = (int)piVar14 * 0x50;
            do {
              puVar8 = (undefined4 *)(*(int *)(iVar13 + 0x8d4) + iVar7);
              *puVar8 = puVar8[0x14];
              puVar8[1] = puVar8[0x15];
              puVar8[2] = puVar8[0x16];
              puVar8[3] = puVar8[0x17];
              puVar8[4] = puVar8[0x18];
              puVar8[5] = puVar8[0x19];
              puVar8[6] = puVar8[0x1a];
              puVar8[7] = puVar8[0x1b];
              puVar8[8] = puVar8[0x1c];
              puVar8[9] = puVar8[0x1d];
              puVar8[10] = puVar8[0x1e];
              puVar8[0xb] = puVar8[0x1f];
              puVar8[0xc] = puVar8[0x20];
              puVar8[0xd] = puVar8[0x21];
              puVar8[0xe] = puVar8[0x22];
              puVar8[0xf] = puVar8[0x23];
              puVar8[0x10] = puVar8[0x24];
              puVar8[0x11] = puVar8[0x25];
              puVar8[0x12] = puVar8[0x26];
              puVar8[0x13] = puVar8[0x27];
              local_150 = (int *)((int)local_150 + 1);
              iVar7 = iVar7 + 0x50;
            } while ((int)local_150 < *(int *)(iVar13 + 0x8cc));
          }
        }
        else {
          piVar14 = (int *)((int)piVar14 + -1);
          DAT_0044f85c = piVar14;
        }
        *(int *)(iVar13 + 0x8cc) = *(int *)(iVar13 + 0x8cc) + -1;
      }
    }
    iVar7 = FUN_00415140(0x4b);
    if ((iVar7 != 0) && (iVar7 = iVar6 * 0x178 + param_1, 0 < *(int *)(iVar7 + 0x8cc))) {
      piVar14 = (int *)((int)piVar14 * 0x50 + *(int *)(iVar7 + 0x8d4));
      *piVar14 = (*piVar14 + 1) % 7;
    }
  }
  else if (DAT_0044f864 == 1) {
    iVar7 = FUN_00415140(0x2d);
    if (iVar7 != 0) {
      iVar7 = (iVar6 + 6) * 0x178;
      *(int *)(iVar7 + param_1) = *(int *)(iVar7 + param_1) + 1;
      if (*(int *)(iVar7 + param_1) == 1) {
        pvVar5 = malloc(200);
        *(void **)(iVar6 * 0x178 + 0x8d8 + param_1) = pvVar5;
      }
      puVar8 = (undefined4 *)
               (*(int *)(iVar6 * 0x178 + 0x8d8 + param_1) + -0x28 + *(int *)(iVar7 + param_1) * 0x28
               );
      puVar8[5] = 0;
      puVar8[6] = 0;
      puVar8[7] = 0;
      puVar8[8] = 0;
      puVar8[9] = 0;
      puVar8[4] = 10;
      puVar8[3] = 10;
      puVar8[2] = 0;
      puVar8[1] = 0;
      *puVar8 = 0;
      DAT_0044f858 = *(int *)(iVar7 + param_1) + -1;
    }
    iVar7 = FUN_00415140(0x2e);
    if (iVar7 != 0) {
      local_150 = (int *)((iVar6 + 6) * 0x178 + param_1);
      iVar7 = *local_150;
      if (0 < iVar7) {
        if (extraout_ECX_01 < iVar7 + -1) {
          if (extraout_ECX_01 < iVar7) {
            local_14c = (int *)(iVar6 * 0x178 + 0x8d8 + param_1);
            iVar7 = extraout_ECX_01 * 0x28;
            iVar13 = extraout_ECX_01;
            do {
              puVar8 = (undefined4 *)(*local_14c + iVar7);
              *puVar8 = *(undefined4 *)(*local_14c + 0x28 + iVar7);
              puVar8[1] = puVar8[0xb];
              puVar8[2] = puVar8[0xc];
              puVar8[3] = puVar8[0xd];
              puVar8[4] = puVar8[0xe];
              puVar8[5] = puVar8[0xf];
              puVar8[6] = puVar8[0x10];
              puVar8[7] = puVar8[0x11];
              puVar8[8] = puVar8[0x12];
              puVar8[9] = puVar8[0x13];
              iVar13 = iVar13 + 1;
              iVar7 = iVar7 + 0x28;
            } while (iVar13 < *local_150);
          }
        }
        else {
          DAT_0044f858 = extraout_ECX_01 + -1;
        }
        *local_150 = *local_150 + -1;
      }
    }
    iVar7 = FUN_00415140(0x4b);
    if ((iVar7 != 0) && (0 < *(int *)((iVar6 + 6) * 0x178 + param_1))) {
      puVar1 = (uint *)(*(int *)(iVar6 * 0x178 + 0x8d8 + param_1) + extraout_ECX_02 * 0x28);
      uVar4 = *puVar1 + 1 & 0x80000003;
      if ((int)uVar4 < 0) {
        uVar4 = (uVar4 - 1 | 0xfffffffc) + 1;
      }
      *puVar1 = uVar4;
    }
  }
  iVar7 = iVar6 * 0x178 + param_1;
  if ((*(int *)(iVar6 * 0x178 + 0x7f4 + param_1) == 0) && (*(int *)(iVar7 + 0x7f8) == 0)) {
    iVar7 = FUN_0040bf30(iVar6);
    iVar6 = DAT_0044f86c;
    *(int *)(DAT_0044f86c * 0x178 + 0x7f4 + param_1) = iVar7 / 2;
    iVar7 = iVar6 * 0x178 + param_1;
    uVar9 = FUN_0040bfb0(iVar6);
    iVar6 = DAT_0044f86c;
    *(undefined4 *)(iVar7 + 0x7f8) = uVar9;
  }
  FUN_0040be70(200 - *(int *)(iVar7 + 0x7f4),200 - *(int *)(iVar7 + 0x7f8),iVar6,0,0,0,DAT_00455608)
  ;
  sprintf(local_13c,"%d   %s",DAT_0044f86c,DAT_0044f86c * 0x178 + 0x900 + param_1);
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  FUN_00401290(DAT_00455608,local_13c,0,0xffffff,200 - *(int *)(iVar6 + 0x7f4),
               0xa6 - *(int *)(iVar6 + 0x7f8));
  sprintf(local_13c,"wait: %d   next: %d",*(undefined4 *)(DAT_0044f86c * 0x178 + param_1 + 0x7b0),
          *(undefined4 *)(DAT_0044f86c * 0x178 + 0x7b4 + param_1));
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  FUN_00401290(DAT_00455608,local_13c,0,0xffffff,200 - *(int *)(iVar6 + 0x7f4),
               0xb7 - *(int *)(iVar6 + 0x7f8));
  iVar6 = *(int *)((int)DAT_0044f870 + 0x70) * 0x178 + param_1;
  FUN_0040be70(400 - *(int *)(iVar6 + 0x7f4),200 - *(int *)(iVar6 + 0x7f8),
               *(int *)((int)DAT_0044f870 + 0x70),0,0,0,DAT_00455608);
  iVar13 = DAT_0044f86c;
  iVar7 = *(int *)(DAT_0044f86c * 0x178 + 0x8cc + param_1);
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  if ((0 < iVar7) && (DAT_0044f864 == 0)) {
    if ((DAT_004527e4 == 1) && (DAT_0044f854 == 0)) {
      DAT_0044f85c = (int *)(((int)DAT_0044f85c + 1) % iVar7);
    }
    if (DAT_00457580 == 1) {
      if (DAT_0044f850 == 0) {
        DAT_0044f84c = DAT_004546f0;
        DAT_0044f848 = DAT_00453cdc;
      }
      else if (DAT_0044f850 == 1) {
        _DAT_0044f844 = DAT_004546f0;
        _DAT_0044f840 = DAT_00453cdc;
        if (DAT_004546f0 < DAT_0044f84c) {
          local_150 = (int *)(DAT_0044f84c - DAT_004546f0);
          iVar7 = DAT_004546f0;
        }
        else {
          local_150 = (int *)(DAT_004546f0 - DAT_0044f84c);
          iVar7 = DAT_0044f84c;
        }
        if (DAT_00453cdc < DAT_0044f848) {
          local_14c = (int *)(DAT_0044f848 - DAT_00453cdc);
          iVar15 = DAT_00453cdc;
        }
        else {
          local_14c = (int *)(DAT_00453cdc - DAT_0044f848);
          iVar15 = DAT_0044f848;
        }
        iVar10 = (int)DAT_0044f85c * 0x50 + *(int *)(iVar6 + 0x8d4);
        *(int *)(iVar10 + 4) = *(int *)(iVar6 + 0x7f4) + -200 + iVar7;
        *(int *)(iVar10 + 8) = *(int *)(iVar6 + 0x7f8) + -200 + iVar15;
        *(int *)(iVar10 + 0xc) = (int)local_150 + 1;
        *(int *)(iVar10 + 0x10) = (int)local_14c + 1;
      }
    }
    DAT_0044f850 = DAT_00457580;
    DAT_0044f854 = DAT_004527e4;
  }
  iVar7 = *(int *)((iVar13 + 6) * 0x178 + param_1);
  if ((iVar7 < 1) || (DAT_0044f864 != 1)) {
    if (DAT_0044f864 != 0) goto LAB_00416263;
    if (DAT_0044f860 != 2) {
      if (DAT_0044f860 != 4) {
        local_150 = (int *)0x0;
        if (0 < iVar7) {
          iVar6 = 0;
          do {
            iVar7 = iVar13 * 0x178 + param_1;
            iVar15 = *(int *)(iVar13 * 0x178 + 0x8d8 + param_1) + iVar6;
            if (0 < (int)DAT_0044f874) {
              FUN_00415160((*(int *)(iVar15 + 4) - *(int *)(iVar7 + 0x7f4)) + 200,
                           (*(int *)(iVar15 + 8) - *(int *)(iVar7 + 0x7f8)) + 200,
                           *(undefined4 *)(iVar15 + 0xc),*(undefined4 *)(iVar15 + 0x10),0xff);
              if (0 < (int)DAT_0044f874) {
                FUN_00415160((*(int *)(iVar15 + 4) -
                             *(int *)(DAT_0044f86c * 0x178 + 0x7f4 + param_1)) + 0xc9,
                             (*(int *)(iVar15 + 8) -
                             *(int *)(DAT_0044f86c * 0x178 + 0x7f8 + param_1)) + 0xc9,
                             *(int *)(iVar15 + 0xc) + -2,*(int *)(iVar15 + 0x10) + -2,0x90);
              }
              iVar13 = DAT_0044f86c;
            }
            local_150 = (int *)((int)local_150 + 1);
            iVar6 = iVar6 + 0x28;
          } while ((int)local_150 < *(int *)((iVar13 + 6) * 0x178 + param_1));
        }
        if ((0 < *(int *)((iVar13 + 6) * 0x178 + param_1)) && (DAT_0044f864 == 1)) {
          if (DAT_0044f860 == 2) goto LAB_00416359;
          iVar7 = iVar13 * 0x178 + param_1;
          iVar6 = *(int *)(iVar13 * 0x178 + 0x8d8 + param_1) + DAT_0044f858 * 0x28;
          if (0 < (int)DAT_0044f874) {
            FUN_00415160((*(int *)(iVar6 + 4) - *(int *)(iVar7 + 0x7f4)) + 200,
                         (*(int *)(iVar6 + 8) - *(int *)(iVar7 + 0x7f8)) + 200,
                         *(undefined4 *)(iVar6 + 0xc),*(undefined4 *)(iVar6 + 0x10),0xffffff);
            if (0 < (int)DAT_0044f874) {
              FUN_00415160((*(int *)(iVar6 + 4) - *(int *)(DAT_0044f86c * 0x178 + 0x7f4 + param_1))
                           + 0xc9,(*(int *)(iVar6 + 8) -
                                  *(int *)(DAT_0044f86c * 0x178 + 0x7f8 + param_1)) + 0xc9,
                           *(int *)(iVar6 + 0xc) + -2,*(int *)(iVar6 + 0x10) + -2,200);
            }
            iVar13 = DAT_0044f86c;
          }
        }
      }
      goto LAB_00416263;
    }
  }
  else {
    if ((DAT_004527e4 == 1) && (DAT_0044f83c == 0)) {
      DAT_0044f858 = (DAT_0044f858 + 1) % iVar7;
    }
    if (DAT_00457580 == 1) {
      if (DAT_0044f838 == 0) {
        DAT_0044f834 = DAT_004546f0;
        DAT_0044f830 = DAT_00453cdc;
      }
      else if (DAT_0044f838 == 1) {
        _DAT_0044f82c = DAT_004546f0;
        _DAT_0044f828 = DAT_00453cdc;
        if (DAT_004546f0 < DAT_0044f834) {
          local_14c = (int *)(DAT_0044f834 - DAT_004546f0);
          iVar7 = DAT_004546f0;
        }
        else {
          local_14c = (int *)(DAT_004546f0 - DAT_0044f834);
          iVar7 = DAT_0044f834;
        }
        if (DAT_00453cdc < DAT_0044f830) {
          local_150 = (int *)(DAT_0044f830 - DAT_00453cdc);
          iVar15 = DAT_00453cdc;
        }
        else {
          local_150 = (int *)(DAT_00453cdc - DAT_0044f830);
          iVar15 = DAT_0044f830;
        }
        iVar10 = *(int *)(iVar6 + 0x8d8) + DAT_0044f858 * 0x28;
        *(int *)(iVar10 + 4) = *(int *)(iVar6 + 0x7f4) + -200 + iVar7;
        *(int *)(iVar10 + 8) = *(int *)(iVar6 + 0x7f8) + -200 + iVar15;
        *(int *)(iVar10 + 0xc) = (int)local_14c + 1;
        *(int *)(iVar10 + 0x10) = (int)local_150 + 1;
      }
    }
    DAT_0044f838 = DAT_00457580;
    DAT_0044f83c = DAT_004527e4;
LAB_00416263:
    if ((DAT_0044f860 != 2) && (DAT_0044f860 != 4)) {
      iVar7 = 0;
      iVar6 = iVar13 * 0x178 + param_1;
      if (0 < *(int *)(iVar6 + 0x8cc)) {
        local_150 = (int *)0x0;
        do {
          piVar14 = local_150;
          iVar15 = *(int *)(iVar6 + 0x8d4);
          if (0 < (int)DAT_0044f874) {
            FUN_00415160((*(int *)((int)local_150 + iVar15 + 4) - *(int *)(iVar6 + 0x7f4)) + 200,
                         (*(int *)((int)local_150 + iVar15 + 8) - *(int *)(iVar6 + 0x7f8)) + 200,
                         *(undefined4 *)((int)local_150 + iVar15 + 0xc),
                         *(undefined4 *)((int)local_150 + iVar15 + 0x10),0xff0000);
            if (0 < (int)DAT_0044f874) {
              FUN_00415160((*(int *)((int)piVar14 + iVar15 + 4) -
                           *(int *)(DAT_0044f86c * 0x178 + 0x7f4 + param_1)) + 0xc9,
                           (*(int *)((int)piVar14 + iVar15 + 8) -
                           *(int *)(DAT_0044f86c * 0x178 + 0x7f8 + param_1)) + 0xc9,
                           *(int *)((int)piVar14 + iVar15 + 0xc) + -2,
                           *(int *)((int)piVar14 + iVar15 + 0x10) + -2,0x900000);
            }
            iVar13 = DAT_0044f86c;
          }
          local_150 = local_150 + 0x14;
          iVar7 = iVar7 + 1;
          iVar6 = iVar13 * 0x178 + param_1;
        } while (iVar7 < *(int *)(iVar6 + 0x8cc));
      }
    }
  }
LAB_00416359:
  iVar6 = iVar13 * 0x178 + param_1;
  if ((0 < *(int *)(iVar13 * 0x178 + 0x8cc + param_1)) && (DAT_0044f864 == 0)) {
    if ((DAT_0044f860 == 2) ||
       ((DAT_0044f860 == 4 ||
        (iVar7 = (int)DAT_0044f85c * 0x50 + *(int *)(iVar6 + 0x8d4), (int)DAT_0044f874 < 1))))
    goto LAB_0041662e;
    FUN_00415160((*(int *)(iVar7 + 4) - *(int *)(iVar6 + 0x7f4)) + 200,
                 (*(int *)(iVar7 + 8) - *(int *)(iVar6 + 0x7f8)) + 200,*(undefined4 *)(iVar7 + 0xc),
                 *(undefined4 *)(iVar7 + 0x10),0xffffff);
    if (0 < (int)DAT_0044f874) {
      iVar6 = DAT_0044f86c * 0x178 + param_1;
      FUN_00415160((*(int *)(iVar7 + 4) - *(int *)(iVar6 + 0x7f4)) + 0xc9,
                   (*(int *)(iVar7 + 8) - *(int *)(iVar6 + 0x7f8)) + 0xc9,*(int *)(iVar7 + 0xc) + -2
                   ,*(int *)(iVar7 + 0x10) + -2,0xc80000);
    }
    iVar13 = DAT_0044f86c;
  }
  if (((DAT_0044f864 == 1) && (DAT_0044f860 != 2)) && (DAT_0044f860 != 4)) {
    local_150 = (int *)0x0;
    if (0 < *(int *)((iVar13 + 6) * 0x178 + param_1)) {
      iVar6 = 0;
      do {
        iVar7 = iVar13 * 0x178 + param_1;
        iVar15 = *(int *)(iVar13 * 0x178 + 0x8d8 + param_1) + iVar6;
        if (0 < (int)DAT_0044f874) {
          FUN_00415160((*(int *)(iVar15 + 4) - *(int *)(iVar7 + 0x7f4)) + 200,
                       (*(int *)(iVar15 + 8) - *(int *)(iVar7 + 0x7f8)) + 200,
                       *(undefined4 *)(iVar15 + 0xc),*(undefined4 *)(iVar15 + 0x10),0xff);
          if (0 < (int)DAT_0044f874) {
            iVar7 = DAT_0044f86c * 0x178 + param_1;
            FUN_00415160((*(int *)(iVar15 + 4) - *(int *)(iVar7 + 0x7f4)) + 0xc9,
                         (*(int *)(iVar15 + 8) - *(int *)(iVar7 + 0x7f8)) + 0xc9,
                         *(int *)(iVar15 + 0xc) + -2,*(int *)(iVar15 + 0x10) + -2,0x90);
          }
          iVar13 = DAT_0044f86c;
        }
        local_150 = (int *)((int)local_150 + 1);
        iVar6 = iVar6 + 0x28;
      } while ((int)local_150 < *(int *)((iVar13 + 6) * 0x178 + param_1));
    }
    if ((0 < *(int *)((iVar13 + 6) * 0x178 + param_1)) && (DAT_0044f864 == 1)) {
      iVar7 = iVar13 * 0x178 + param_1;
      iVar6 = *(int *)(iVar13 * 0x178 + 0x8d8 + param_1) + DAT_0044f858 * 0x28;
      if ((0 < (int)DAT_0044f874) &&
         (FUN_00415160((*(int *)(iVar6 + 4) - *(int *)(iVar7 + 0x7f4)) + 200,
                       (*(int *)(iVar6 + 8) - *(int *)(iVar7 + 0x7f8)) + 200,
                       *(undefined4 *)(iVar6 + 0xc),*(undefined4 *)(iVar6 + 0x10),0xffffff),
         0 < (int)DAT_0044f874)) {
        FUN_00415160((*(int *)(iVar6 + 4) - *(int *)(DAT_0044f86c * 0x178 + 0x7f4 + param_1)) + 0xc9
                     ,(*(int *)(iVar6 + 8) - *(int *)(DAT_0044f86c * 0x178 + 0x7f8 + param_1)) +
                      0xc9,*(int *)(iVar6 + 0xc) + -2,*(int *)(iVar6 + 0x10) + -2,200);
      }
    }
  }
LAB_0041662e:
  FUN_0043f010(DAT_004546f0 + -10,DAT_00453cdc + -10,0xffffffff,1,0,DAT_00455608);
  if (DAT_0044f864 == 0) {
    iVar6 = *(int *)(DAT_0044f86c * 0x178 + 0x8cc + param_1);
    if (0 < iVar6) {
      sprintf(local_13c,"itr mode   no: %d   kind: %d",iVar6,
              *(undefined4 *)
               (*(int *)(DAT_0044f86c * 0x178 + param_1 + 0x8d4) + (int)DAT_0044f85c * 0x50));
    }
  }
  else {
    iVar6 = *(int *)((DAT_0044f86c + 6) * 0x178 + param_1);
    if (0 < iVar6) {
      sprintf(local_13c,"bdy mode   no: %d   kind: %d",iVar6,
              *(undefined4 *)
               (*(int *)(DAT_0044f86c * 0x178 + 0x8d8 + param_1) + DAT_0044f858 * 0x28));
    }
  }
  FUN_00401290(DAT_00455608,local_13c,0,0xffffff,0,0x32);
  if (DAT_0044f860 == 1) {
    sprintf(local_13c,"cpoint: %d  ",*(undefined4 *)(DAT_0044f86c * 0x178 + 0x82c + param_1));
    FUN_00401290(DAT_00455608,local_13c,0,0xffffff,0,0x46);
  }
  if (DAT_0044f860 == 2) {
    sprintf(local_13c,"wpoint: %d  %d",*(undefined4 *)(DAT_0044f86c * 0x178 + param_1 + 0x87c),
            *(undefined4 *)(DAT_0044f86c * 0x178 + 0x888 + param_1));
    FUN_00401290(DAT_00455608,local_13c,0,0xffffff,0,0x46);
  }
  if (DAT_0044f860 == 3) {
    sprintf(local_13c,"opoint: %d    ",*(undefined4 *)(DAT_0044f86c * 0x178 + 0x7fc + param_1));
    FUN_00401290(DAT_00455608,local_13c,0,0xffffff,0,0x46);
  }
  if (DAT_0044f860 == 4) {
    sprintf(local_13c,"bpoint: %d  %d",*(undefined4 *)(DAT_0044f86c * 0x178 + 0x824 + param_1),
            *(undefined4 *)(DAT_0044f86c * 0x178 + 0x828 + param_1));
    FUN_00401290(DAT_00455608,local_13c,0,0xffffff,0,0x46);
  }
  FUN_00415160(0xc2,200,0xd,1,0xa514);
  FUN_00415160(200,0xc2,1,0xd,0xa514);
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  if (*(int *)(iVar6 + 0x7fc) != 0) {
    FUN_00415160((*(int *)(iVar6 + 0x800) - *(int *)(iVar6 + 0x7f4)) + 0xc2,
                 (*(int *)(iVar6 + 0x804) - *(int *)(iVar6 + 0x7f8)) + 200,0xd,1,0xf800);
    iVar6 = DAT_0044f86c * 0x178;
    FUN_00415160((*(int *)(iVar6 + 0x800 + param_1) - *(int *)(iVar6 + 0x7f4 + param_1)) + 200,
                 (*(int *)(iVar6 + 0x804 + param_1) - *(int *)(iVar6 + 0x7f8 + param_1)) + 0xc2,1,
                 0xd,0xf800);
  }
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  if (*(int *)(iVar6 + 0x82c) != 0) {
    FUN_00415160((*(int *)(iVar6 + 0x830) - *(int *)(iVar6 + 0x7f4)) + 0xc2,
                 (*(int *)(iVar6 + 0x834) - *(int *)(iVar6 + 0x7f8)) + 200,0xd,1,0x7e0);
    iVar7 = DAT_0044f86c * 0x178;
    FUN_00415160((*(int *)(iVar7 + 0x830 + param_1) - *(int *)(iVar7 + 0x7f4 + param_1)) + 200,
                 (*(int *)(iVar7 + 0x834 + param_1) - *(int *)(iVar7 + 0x7f8 + param_1)) + 0xc2,1,
                 0xd,0x7e0);
    if (*(int *)(*(int *)(iVar6 + 0x840) * 0x178 + 0x82c + param_1) == 2) {
      bVar16 = *(int *)(iVar6 + 0x83c) / 10 != 1;
      iVar7 = DAT_0044f86c * 0x178 + param_1;
      if (bVar16) {
        iVar13 = *(int *)(iVar7 + 0x830);
        iVar15 = *(int *)(iVar7 + 0x834);
        iVar10 = *(int *)(iVar7 + 0x7f4);
        iVar2 = *(int *)(iVar7 + 0x7f8);
        iVar12 = FUN_0040bf30(*(undefined4 *)(iVar6 + 0x840));
        iVar7 = *(int *)(iVar6 + 0x840);
        iVar12 = (*(int *)(*(int *)(iVar6 + 0x840) * 0x178 + 0x830 + param_1) +
                 (iVar13 - iVar10) + 200) - iVar12;
        iVar6 = ((iVar15 - iVar2) + 200) - *(int *)(iVar7 * 0x178 + 0x834 + param_1);
      }
      else {
        iVar13 = *(int *)(iVar7 + 0x830);
        iVar15 = *(int *)(iVar7 + 0x834);
        iVar10 = *(int *)(iVar7 + 0x7f4);
        iVar2 = *(int *)(iVar7 + 0x7f8);
        iVar11 = FUN_0040bf30(*(undefined4 *)(iVar6 + 0x840));
        iVar3 = *(int *)(*(int *)(iVar6 + 0x840) * 0x178 + 0x830 + param_1);
        iVar12 = FUN_0040bf30(*(undefined4 *)(iVar6 + 0x840));
        iVar7 = *(int *)(iVar6 + 0x840);
        iVar12 = iVar12 + ((((iVar13 - iVar10) + 200) - iVar3) - iVar11);
        iVar6 = ((iVar15 - iVar2) + 200) - *(int *)(iVar7 * 0x178 + 0x834 + param_1);
      }
      FUN_0040be70(iVar12,iVar6,iVar7,1,bVar16,0,DAT_00455608);
    }
  }
  iVar6 = DAT_0044f86c * 0x178 + param_1;
  if (*(int *)(iVar6 + 0x87c) != 0) {
    if (*(int *)(iVar6 + 0x87c) == 2) {
      FUN_00415160((*(int *)(iVar6 + 0x880) - *(int *)(iVar6 + 0x7f4)) + 0xc2,
                   (*(int *)(iVar6 + 0x884) - *(int *)(iVar6 + 0x7f8)) + 200,0xd,1,0x1f);
      iVar7 = DAT_0044f86c * 0x178;
      FUN_00415160((*(int *)(iVar7 + 0x880 + param_1) - *(int *)(iVar7 + 0x7f4 + param_1)) + 200,
                   (*(int *)(iVar7 + 0x884 + param_1) - *(int *)(iVar7 + 0x7f8 + param_1)) + 0xc2,1,
                   0xd,0x1f);
    }
    iVar7 = DAT_0044f86c * 0x178 + param_1;
    if (*(int *)(iVar7 + 0x87c) == 1) {
      if (DAT_0044f868 == 0) {
        iVar13 = local_148;
      }
      else {
        iVar13 = local_140;
        if (DAT_0044f868 != 1) {
          iVar13 = local_144;
        }
      }
      iVar15 = *(int *)(iVar6 + 0x888) * 0x178;
      FUN_0040be70(((*(int *)(iVar7 + 0x880) - *(int *)(iVar15 + iVar13 + 0x880)) -
                   *(int *)(iVar7 + 0x7f4)) + 200,
                   ((*(int *)(iVar7 + 0x884) - *(int *)(iVar15 + 0x884 + iVar13)) -
                   *(int *)(iVar7 + 0x7f8)) + 200,*(int *)(iVar6 + 0x888),1,0,0,DAT_00455608);
    }
  }
  param_1 = param_1 + DAT_0044f86c * 0x178;
  if (*(int *)(param_1 + 0x824) != 0) {
    FUN_00415160((*(int *)(param_1 + 0x824) - *(int *)(param_1 + 0x7f4)) + 200,
                 (*(int *)(param_1 + 0x828) - *(int *)(param_1 + 0x7f8)) + 200,1,3,0xf800);
  }
  FUN_0043e940(DAT_00458348);
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_150);
  return;
}
