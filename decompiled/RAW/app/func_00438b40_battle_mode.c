
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00438b40(undefined4 param_1,int *param_2,int *param_3,int *param_4,int *param_5,
                 int *param_6,int param_7)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  int iVar10;
  int *piVar11;
  undefined4 *puVar12;
  bool bVar13;
  undefined4 uVar14;
  char *pcVar15;
  undefined4 uVar16;
  int local_a3c;
  undefined1 *local_a38;
  int *local_a34;
  int *local_a30;
  undefined4 local_a2c;
  int local_a28;
  undefined1 *local_a24;
  int *local_a20;
  int *local_a1c;
  int *local_a18;
  int *local_a14;
  _SYSTEMTIME local_a10;
  int aiStack_a00 [500];
  char local_230 [12];
  char local_224 [12];
  char local_218 [20];
  char local_204 [500];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0044619c;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_a3c;
  ExceptionList = &local_c;
  local_a34 = param_2;
  local_a18 = param_3;
  local_a2c = param_1;
  local_a1c = param_4;
  local_a20 = param_6;
  FUN_00431b70(DAT_0044eea4 ^ (uint)(aiStack_a00 + -0x13));
  piVar8 = DAT_0044d37c;
  iVar6 = 0;
  if (DAT_0044d774 == 1) {
    if (-1 < (int)DAT_0044d37c) {
      do {
        iVar7 = 0;
        if (0 < (int)piVar8) {
          iVar10 = iVar6 * 4;
          do {
            iVar1 = (int)(&DAT_0044d468)[iVar7] / 3;
            if ((iVar1 < 1) && (0 < (int)(&DAT_0044d388)[iVar7] / 3)) {
              iVar1 = 1;
            }
            iVar2 = (int)(&DAT_0044d388)[iVar7] / 3 - iVar1;
            *(int *)((int)&DAT_0044d5f8 + iVar10) = iVar1;
            *(int *)((int)&DAT_0044d650 + iVar10) = iVar2;
            if (iVar2 < 0) {
              *(undefined4 *)((int)&DAT_0044d650 + iVar10) = 0;
            }
            iVar7 = iVar7 + 1;
            iVar10 = iVar10 + 4;
          } while (iVar7 < (int)piVar8);
        }
        iVar6 = iVar6 + (int)piVar8;
      } while (iVar6 <= (int)piVar8);
    }
    local_a24 = operator_new(0x1f50);
    local_4 = 0;
    if (local_a24 == (void *)0x0) {
      DAT_00451bb0 = 0;
    }
    else {
      DAT_00451bb0 = FUN_0043ee50(0x40,"BATTLEMODE",0);
    }
    local_4 = 0xffffffff;
    local_a24 = operator_new(0x1f50);
    local_4 = 1;
    if (local_a24 == (void *)0x0) {
      DAT_00451bac = 0;
    }
    else {
      DAT_00451bac = FUN_0043ee50(0x40,"BATTLETROOPS",0);
    }
    piVar8 = DAT_0044d37c;
    iVar6 = 0;
    local_4 = 0xffffffff;
    if (0 < (int)DAT_0044d37c) {
      do {
        iVar7 = *(int *)(local_a28 + 0x7d4);
        iVar10 = 0;
        if (0 < *(int *)(iVar7 + 0x4d82380)) {
          do {
            iVar7 = *(int *)(iVar7 + iVar10 * 4);
            if (*(int *)(iVar7 + 0x6f4) == (&DAT_0044d350)[iVar6]) {
              (&DAT_00451b38)[iVar6] = iVar7;
            }
            iVar7 = *(int *)(local_a28 + 0x7d4);
            iVar10 = iVar10 + 1;
          } while (iVar10 < *(int *)(iVar7 + 0x4d82380));
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < (int)piVar8);
    }
    iVar6 = DAT_00451bb0;
    *(undefined4 *)(DAT_00451bb0 + 0x10) = 0;
    *(undefined4 *)(iVar6 + 0x7e0) = 0;
    *(undefined4 *)(iVar6 + 0x1780) = 400;
    *(undefined4 *)(iVar6 + 0xfb0) = 0x2c1;
    *(undefined4 *)(iVar6 + 0x14) = 0;
    *(undefined4 *)(iVar6 + 0x7e4) = 0x1d7;
    *(undefined4 *)(iVar6 + 0xfb4) = 0x2c1;
    *(undefined4 *)(iVar6 + 0x1784) = 0x10;
    *(undefined4 *)(iVar6 + 0xc) = 2;
    param_1 = local_a2c;
LAB_00438d85:
    DAT_0044d770 = 6;
    DAT_0044d76c = (undefined1 *)0x2;
    DAT_00451ba8 = 0;
    DAT_0044d774 = 0;
  }
  else if (DAT_0044d774 == -1) goto LAB_00438d85;
  DAT_00451b68 = 0;
  DAT_00451b64 = 0;
  DAT_00451b70 = 0;
  DAT_00451b6c = 0;
  iVar6 = *local_a34;
  if (iVar6 < 0xc9) {
    if (0xd1 < iVar6) goto LAB_00438e13;
LAB_00438e2c:
    uVar14 = 0xffffffff;
    iVar6 = 0x21;
    DAT_0044d768 = 0x21;
  }
  else {
    if (iVar6 < 0xd2) {
      DAT_0044d768 = 0x50;
      uVar14 = 0x50;
    }
    else {
LAB_00438e13:
      if (0xdb < iVar6) goto LAB_00438e2c;
      DAT_0044d768 = 0x3c;
      uVar14 = 0x3c;
    }
    FUN_0043f010(DAT_0044d764,uVar14,0,0,0,param_1);
    uVar14 = 1;
    iVar6 = DAT_0044d768 + 400;
  }
  FUN_0043f010(DAT_0044d764,iVar6,uVar14,0,0,param_1);
  _DAT_00451ba0 = DAT_0044d764 + 0xb3;
  _DAT_00451ba4 = DAT_0044d764 + 0x20e;
  iVar6 = 0;
  piVar11 = (int *)(local_a28 + 0x194);
  piVar8 = piVar11;
  do {
    if ((((param_5[iVar6] == 3) || (param_5[iVar6] == 0xd)) && (0 < *(int *)(*piVar8 + 0x364))) &&
       (*(int *)(*piVar8 + 0x364) < 3)) {
      (&DAT_00451b9c)[*(int *)(*piVar8 + 0x364)] =
           (&DAT_00451b9c)[*(int *)(*piVar8 + 0x364)] + -0x14;
    }
    iVar6 = iVar6 + 1;
    piVar8 = piVar8 + 1;
  } while (iVar6 < 8);
  local_a24 = (undefined1 *)(param_7 - (int)local_a20);
  local_a30 = (int *)((int)local_a20 - (int)param_5);
  local_a3c = 0;
  piVar5 = param_5;
  piVar8 = local_a1c;
  local_a14 = piVar11;
  do {
    iVar6 = DAT_0044d768;
    if ((*piVar5 == 3) || (*piVar5 == 0xd)) {
      iVar7 = *(int *)(*piVar11 + 0x364);
      iVar10 = DAT_0044d768 + 0x56;
      if ((0 < iVar7) && (iVar7 < 3)) {
        iVar7 = *(int *)(*piVar11 + 0x364);
        piVar8 = (int *)(&DAT_00451b9c)[iVar7];
        (&DAT_00451b9c)[iVar7] = piVar8 + 10;
      }
      if ((*(int *)(local_a24 + (int)local_a30 + (int)piVar5) == 0) ||
         ((200 < *local_a34 && (*local_a34 < 0xd2)))) {
        uVar14 = 0xffffffff;
      }
      else {
        uVar14 = 1;
      }
      FUN_0043f010(piVar8,iVar10,uVar14,0,0,DAT_00455608);
      local_224[1] = 0;
      if (*piVar5 == 3) {
        local_224[0] = (char)local_a3c + '1';
      }
      else {
        local_224[0] = 'C';
      }
      if (*(int *)(*piVar11 + 0x364) == 1) {
        uVar14 = 0xff9b4f;
      }
      else {
        uVar14 = 0x4f4fff;
      }
      FUN_00401290(DAT_00455608,local_224,0x8f472f,uVar14,(int)piVar8 + 0xf,iVar6 + 0x83);
    }
    local_a3c = local_a3c + 1;
    piVar5 = piVar5 + 1;
    piVar11 = piVar11 + 1;
  } while (local_a3c < 8);
  iVar6 = 0;
  piVar8 = &DAT_0044d758;
  do {
    sprintf(local_218,"x %d.%d",*piVar8 / 100,(*piVar8 % 100) / 10);
    FUN_00401290(DAT_00455608,local_218,0,0xffffff,iVar6 + 0xf0 + DAT_0044d764,DAT_0044d768 + 0x9a);
    piVar8 = piVar8 + 1;
    iVar6 = iVar6 + 0x15b;
  } while ((int)piVar8 < 0x44d760);
  _DAT_00451ba0 = DAT_0044d764 + 0x27;
  _DAT_00451ba4 = DAT_0044d764 + 0x182;
  local_a38 = (undefined1 *)0x0;
  local_a3c = 0;
  piVar8 = DAT_0044d37c;
  do {
    iVar6 = 0;
    if (0 < (int)piVar8) {
      local_a30 = (int *)0x0;
      do {
        if (iVar6 < 6) {
          iVar7 = *(int *)(&DAT_00451ba0 + (int)local_a38 * 4);
          iVar10 = DAT_0044d768 + 0xd7;
        }
        else {
          iVar7 = *(int *)(&DAT_00451ba0 + (int)local_a38 * 4) + -0x108;
          iVar10 = DAT_0044d768 + 0x132;
        }
        iVar7 = iVar7 + (int)local_a30;
        uVar14 = local_a2c;
        if (iVar6 == (int)piVar8 + -1) {
          uVar16 = 0x16;
        }
        else if (iVar6 == (int)piVar8 + -2) {
          uVar16 = 0x17;
        }
        else {
          uVar16 = 0xffffffff;
          uVar14 = DAT_00455608;
        }
        FUN_0043f010(iVar7,iVar10,uVar16,0,0,uVar14);
        iVar1 = iVar10 + 0x2e;
        FUN_00415160(iVar7 + 3,iVar1,0x22,0x10,0);
        iVar10 = iVar10 + 0x40;
        FUN_00415160(iVar7 + 3,iVar10,0x22,0x10,0);
        if ((&DAT_0044d5f8)[(int)DAT_0044d37c * (int)local_a38 + iVar6] == 0) {
          sprintf(local_230,"%d",0);
          FUN_00401290(DAT_00455608,local_230,0,0x9a4d32,iVar7 + 10,iVar1);
          sprintf(local_230,"--");
          FUN_00401290(DAT_00455608,local_230,0,0x9a4d32,iVar7 + 10,iVar10);
        }
        else {
          sprintf(local_230,"%d",(&DAT_0044d5f8)[(int)DAT_0044d37c * (int)local_a38 + iVar6]);
          FUN_00401290(DAT_00455608,local_230,0,0xffffff,iVar7 + 10,iVar1);
          puVar3 = local_a38;
          sprintf(local_230,"%d",(&DAT_0044d650)[(int)DAT_0044d37c * (int)local_a38 + iVar6]);
          if ((&DAT_0044d650)[(int)DAT_0044d37c * (int)puVar3 + iVar6] == 0) {
            uVar14 = 0x9a4d32;
          }
          else {
            uVar14 = 0xffffff;
          }
          FUN_00401290(DAT_00455608,local_230,0,uVar14,iVar7 + 10,iVar10);
        }
        local_a30 = local_a30 + 0xc;
        iVar6 = iVar6 + 1;
        piVar8 = DAT_0044d37c;
      } while (iVar6 < (int)DAT_0044d37c);
    }
    uVar14 = local_a2c;
    puVar3 = local_a38;
    iVar7 = local_a3c;
    iVar6 = (&DAT_0044d380)[(int)local_a38];
    if (iVar6 != -1) {
      if ((iVar6 == 0) || (iVar6 == 6)) {
        iVar10 = iVar6 + 0x12;
        iVar6 = (local_a3c - *(int *)(DAT_004511a0 + 0xff8 + iVar6 * 4)) + 0x159 + DAT_0044d764;
      }
      else {
        iVar1 = *(int *)(DAT_004511a0 + 0xfec + (&DAT_00451b74)[(int)local_a38] * 4);
        FUN_0043f010(((local_a3c - *(int *)(DAT_004511a0 + 0xff8 + iVar6 * 4)) - iVar1) + 0x159 +
                     DAT_0044d764,DAT_0044d768 + 0xc0,iVar6 + 0x12,1,0,local_a2c);
        iVar10 = (&DAT_00451b74)[(int)puVar3] + 0xf;
        iVar6 = DAT_0044d764 + 0x159 + (iVar7 - iVar1);
      }
      FUN_0043f010(iVar6,DAT_0044d768 + 0xc0,iVar10,1,0,uVar14);
      piVar8 = DAT_0044d37c;
    }
    local_a3c = local_a3c + 0x15b;
    local_a38 = puVar3 + 1;
  } while ((int)local_a38 < 2);
  iVar6 = DAT_00451ba8;
  if (*local_a34 == 200) {
    if (DAT_004513a4 == 0) {
      if (DAT_004513a8 != 0) {
        DAT_0044d770 = DAT_0044d770 + 1;
      }
    }
    else {
      DAT_0044d770 = DAT_0044d770 + -1;
    }
    if (DAT_0044d770 < 7) {
      if (-1 < DAT_0044d770) {
        if (DAT_0044d770 == 0) goto LAB_00439425;
        goto LAB_004394e6;
      }
      DAT_0044d770 = 6;
    }
    else {
      DAT_0044d770 = 0;
LAB_00439425:
      FUN_004389a0(DAT_00451ba8 * 0x15b + 0x50 + DAT_0044d764,DAT_0044d768 + 0x96,0xd0,0x19,0xffffff
                  );
      if ((DAT_004513b0 != 0) || (DAT_004513ac != 0)) {
        DAT_00451ba8 = 1 - DAT_00451ba8;
      }
      iVar6 = DAT_00451ba8;
      if ((DAT_004513b4 != 0) &&
         ((&DAT_0044d758)[DAT_00451ba8] = (&DAT_0044d758)[DAT_00451ba8] + 0x32,
         300 < (int)(&DAT_0044d758)[iVar6])) {
        (&DAT_0044d758)[iVar6] = 100;
      }
      if ((DAT_004513b8 != 0) &&
         ((&DAT_0044d758)[iVar6] = (&DAT_0044d758)[iVar6] + -0x32, (int)(&DAT_0044d758)[iVar6] < 100
         )) {
        (&DAT_0044d758)[iVar6] = 300;
      }
      piVar8 = DAT_0044d37c;
LAB_004394e6:
      iVar10 = DAT_004513b4;
      iVar7 = DAT_0044d770;
      if ((0 < DAT_0044d770) && (DAT_0044d770 < 5)) {
        local_a38 = (undefined1 *)((DAT_0044d770 < 3) + 4);
        if (DAT_004513b0 != 0) {
          DAT_0044d76c = DAT_0044d76c + 1;
          if ((int)local_a38 < (int)DAT_0044d76c) {
            iVar6 = 1 - iVar6;
            DAT_0044d76c = (undefined1 *)0x0;
            DAT_00451ba8 = iVar6;
          }
        }
        if (DAT_004513ac != 0) {
          puVar3 = DAT_0044d76c;
          if ((int)local_a38 < (int)DAT_0044d76c) {
            puVar3 = local_a38;
          }
          DAT_0044d76c = puVar3 + -1;
          if ((int)(puVar3 + -1) < 0) {
            iVar6 = 1 - iVar6;
            DAT_0044d76c = local_a38;
            DAT_00451ba8 = iVar6;
          }
        }
        puVar3 = DAT_0044d76c;
        if (((DAT_004513b4 != 0) || (DAT_004513b8 != 0)) || (DAT_004513bc != 0)) {
          bVar13 = DAT_0044d770 == 1;
          (&DAT_0044d380)[iVar6] = 0xffffffff;
          (&DAT_00451b74)[iVar6] = 0xffffffff;
          if (bVar13) {
            piVar8 = &DAT_0044d5f8 + (int)(puVar3 + iVar6 * (int)piVar8);
            piVar11 = (int *)0xa;
          }
          else if (iVar7 == 2) {
            piVar8 = &DAT_0044d650 + (int)(puVar3 + iVar6 * (int)piVar8);
            piVar11 = (int *)0x1e;
          }
          else if (iVar7 == 3) {
            if ((int)puVar3 < 4) {
              piVar8 = (int *)((int)(puVar3 + iVar6 * (int)piVar8) * 4 + 0x44d610);
              piVar11 = (int *)0xa;
            }
            else {
              piVar8 = &DAT_0044d620 + iVar6 * (int)piVar8;
              piVar11 = (int *)0xa;
            }
          }
          else if (iVar7 == 4) {
            if ((int)puVar3 < 4) {
              piVar8 = (int *)((int)(puVar3 + iVar6 * (int)piVar8) * 4 + 0x44d668);
              piVar11 = (int *)0x1e;
            }
            else {
              piVar8 = &DAT_0044d678 + iVar6 * (int)piVar8;
              piVar11 = (int *)0x1e;
            }
          }
          else {
            piVar8 = local_a1c;
            piVar11 = local_a1c;
          }
          if (iVar10 != 0) {
            *piVar8 = *piVar8 + 1;
          }
          if (DAT_004513bc != 0) {
            *piVar8 = *piVar8 + 5;
            if (((int)piVar11 < *piVar8) && (*piVar8 < (int)piVar11 + 5)) {
              *piVar8 = (int)piVar11;
            }
          }
          if (DAT_004513b8 != 0) {
            *piVar8 = *piVar8 + -1;
          }
          if (*piVar8 < 0) {
            *piVar8 = (int)piVar11;
          }
          else if ((int)piVar11 < *piVar8) {
            *piVar8 = 0;
          }
        }
        if ((int)local_a38 < (int)puVar3) {
          puVar3 = local_a38;
        }
        if (iVar7 < 3) {
          iVar10 = DAT_0044d768 + 0xf3 + iVar7 * 0x12;
          iVar7 = (int)puVar3 * 0x30 + 0x2a;
        }
        else {
          iVar10 = DAT_0044d768 + 0x12a + iVar7 * 0x12;
          iVar7 = (int)puVar3 * 0x30 + 0x42;
        }
        FUN_004389a0(iVar7 + iVar6 * 0x15b + DAT_0044d764,iVar10,0x22,0x10,0xffffff);
        iVar6 = DAT_00451ba8;
      }
      if (DAT_0044d770 == 5) {
        FUN_004389a0(iVar6 * 0x15b + 0x2b + DAT_0044d764,DAT_0044d768 + 0x18c,0x110,0x19,0xffffff);
        if ((DAT_004513b0 != 0) || (DAT_004513ac != 0)) {
          DAT_00451ba8 = 1 - DAT_00451ba8;
        }
        iVar6 = DAT_00451ba8;
        if (DAT_004513b4 != 0) {
          *local_a34 = 0xd2;
          piVar8 = DAT_0044d37c;
          DAT_0044d760 = 10;
          DAT_004513b4 = 0;
          if (0 < (int)DAT_0044d37c * 2) {
            puVar9 = &DAT_0044d650;
            puVar12 = &DAT_0044d5a0;
            for (iVar7 = ((uint)DAT_0044d37c & 0x1fffffff) << 1; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar12 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar12 = puVar12 + 1;
            }
            puVar9 = &DAT_0044d5f8;
            puVar12 = &DAT_0044d548;
            for (iVar7 = ((uint)piVar8 & 0x1fffffff) << 1; iVar7 != 0; iVar7 = iVar7 + -1) {
              *puVar12 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar12 = puVar12 + 1;
            }
          }
          DAT_00451b8c = *(undefined4 *)(iVar6 * 4 + 0x451b98);
          DAT_00451b88 = *(undefined4 *)(iVar6 * 4 + 0x451b90);
        }
      }
      piVar8 = local_a34;
      if (DAT_0044d770 != 6) goto LAB_0043986a;
    }
    piVar8 = local_a34;
    FUN_004389a0(DAT_0044d764 + 0x12d,DAT_0044d768 + 0x1b9,0x6a,0x18,0xffffff);
    if (DAT_004513b4 != 0) {
      *piVar8 = 0xca;
      DAT_00451b84 = 2;
      DAT_004513b4 = 0;
      FUN_00401a30(0);
    }
    if (DAT_004513ac == 0) {
      if (DAT_004513b0 != 0) {
        DAT_0044d770 = DAT_0044d770 + -1;
        DAT_00451ba8 = 1;
      }
    }
    else {
      DAT_0044d770 = DAT_0044d770 + -1;
      DAT_00451ba8 = 0;
    }
    iVar6 = DAT_00451ba8;
    if (DAT_004513b8 != 0) {
      *piVar8 = 3;
      *local_a1c = 0;
    }
  }
  else {
    piVar8 = local_a34;
  }
LAB_0043986a:
  piVar11 = local_a20;
  uVar14 = local_a2c;
  iVar7 = *piVar8;
  if (iVar7 == 0xc9) {
    local_a30 = local_a14;
    local_a38 = (undefined1 *)0x8;
    iVar6 = local_a28;
    do {
      piVar8 = local_a20;
      if (*(int *)((int)local_a20 + (int)local_a24) == 1) {
        piVar5 = *(int **)(iVar6 + 0x7d4);
        iVar7 = piVar5[0x13608e0];
        iVar10 = 1;
        local_a3c = 0;
        if (1 < iVar7) {
          iVar6 = *piVar11;
          do {
            piVar5 = piVar5 + 1;
            if (((*(int *)(*piVar5 + 0x6f8) == 0) &&
                (piVar11[7] != iVar10 &&
                 (piVar11[6] != iVar10 &&
                 (piVar11[5] != iVar10 &&
                 (piVar11[4] != iVar10 &&
                 (piVar11[3] != iVar10 &&
                 (piVar11[2] != iVar10 && (piVar11[1] != iVar10 && iVar6 != iVar10)))))))) &&
               (*(int *)(*piVar5 + 0x6f4) < 0x1e)) {
              aiStack_a00[local_a3c] = iVar10;
              local_a3c = local_a3c + 1;
            }
            iVar10 = iVar10 + 1;
          } while (iVar10 < iVar7);
          iVar6 = local_a28;
        }
        iVar7 = FUN_00417170(0x122,local_a3c);
        iVar7 = aiStack_a00[iVar7];
        *piVar8 = iVar7;
        *(undefined4 *)(*local_a30 + 0x368) = *(undefined4 *)(*(int *)(iVar6 + 0x7d4) + iVar7 * 4);
      }
      local_a30 = local_a30 + 1;
      local_a20 = piVar8 + 1;
      local_a38 = (undefined1 *)((int)local_a38 + -1);
    } while (local_a38 != (undefined1 *)0x0);
    *local_a34 = 0xca;
    DAT_00451b84 = 2;
    local_a38 = (undefined1 *)0x0;
    uVar14 = local_a2c;
LAB_00439f93:
    FUN_00402130(*local_a18,DAT_004513ac,DAT_004513b0,uVar14);
    FUN_0043f010(3,3,8,0,0,uVar14);
    FUN_0043f010(3,0x9f,0xf,1,0,uVar14);
    if (DAT_00451b84 == 0) {
      FUN_0043f010(0x5c,0x10,9,0,0,uVar14);
    }
    if (DAT_00451b84 == 1) {
      FUN_0043f010(0x40,0x27,10,0,0,uVar14);
    }
    if (DAT_00451b84 == 2) {
      FUN_0043f010(0x28,0x40,0xb,0,0,uVar14);
    }
    if (DAT_00451b84 == 3) {
      FUN_0043f010(0xf,0x57,0xc,0,0,uVar14);
    }
    if (DAT_00451b84 == 4) {
      FUN_0043f010(0x25,0x6f,0xd,0,0,uVar14);
    }
    if (DAT_00451b84 == 5) {
      FUN_0043f010(0x65,0x89,0xe,0,0,uVar14);
    }
    if (DAT_0044d028 == 1) {
      DAT_0044d024 = 100;
    }
    FUN_00401290(DAT_00455608,DAT_0044d024 * 0x990 + 0x4d4617c + *(int *)(iVar6 + 0x7d4),0,0xff9b9b,
                 0xae,0x5b);
    if (_DAT_00450c30 == 2) {
      pcVar15 = "Easy";
LAB_0043a152:
      FUN_00401290(DAT_00455608,pcVar15,0,0xff9b9b,0xae,0x73);
    }
    else {
      if (_DAT_00450c30 == 1) {
        pcVar15 = "Normal";
        goto LAB_0043a152;
      }
      if (_DAT_00450c30 == 0) {
        pcVar15 = "Difficult";
        goto LAB_0043a152;
      }
      if (_DAT_00450c30 == -1) {
        pcVar15 = "Difficult";
        goto LAB_0043a152;
      }
    }
    if ((DAT_004513a4 != 0) && (DAT_00451b84 = DAT_00451b84 + -1, DAT_00451b84 == -1)) {
      DAT_00451b84 = 5;
    }
    if (DAT_004513a8 != 0) {
      DAT_00451b84 = (DAT_00451b84 + 1) % 6;
    }
    if (DAT_004513b8 != 0) {
      *local_a34 = 200;
      goto LAB_00439e78;
    }
    if (DAT_004513b4 != 0) {
      iVar7 = (int)DAT_0044d37c * 2;
      iVar10 = 0;
      if (0 < iVar7) {
        do {
          iVar1 = (&DAT_0044d5f8)[iVar10];
          if (iVar1 < 1) {
            (&DAT_0044d6a8)[iVar10] = 0;
          }
          else {
            (&DAT_0044d6a8)[iVar10] = (&DAT_0044d650)[iVar10] + iVar1;
          }
          (&DAT_0044d700)[iVar10] = iVar1;
          iVar10 = iVar10 + 1;
        } while (iVar10 < iVar7);
      }
      DAT_004513b4 = 0;
      FUN_00401a30(0);
      if (DAT_00451b84 == 0) {
        DAT_00450bb0 = 0;
        DAT_00450bb4 = 0;
        *local_a34 = 0;
        GetLocalTime(&local_a10);
        sprintf(local_204,"%4d%02d%02d_%02d%02d%02d_Battle",(uint)local_a10.wYear,
                (uint)local_a10.wMonth,(uint)local_a10.wDay,(uint)local_a10.wHour,
                (uint)local_a10.wMinute,(uint)local_a10.wSecond);
        sprintf(&DAT_0044fd98,"%s.lfr",local_204);
        DAT_00450b6c = 0;
        if (DAT_00450be4 != 0) {
          DAT_00450b70 = 1;
        }
        puVar3 = (undefined1 *)(iVar6 + 4);
        local_a24 = puVar3;
        memset(puVar3,0,400);
        if ((DAT_0044d028 == 1) &&
           (DAT_0044d024 = FUN_00417170(0x123,*(int *)(*(int *)(iVar6 + 0x7d4) + 0x4d82384) + -2),
           DAT_0044d024 == *(int *)(*(int *)(iVar6 + 0x7d4) + 0x4d82384) + -3)) {
          DAT_0044d024 = 99;
        }
        local_a3c = DAT_0044d024;
        iVar7 = 10;
        piVar8 = (int *)(iVar6 + 0x198);
        iVar10 = 0x50;
        do {
          if ((*(char *)(iVar6 + -6 + iVar7) != '\0') && (*(int *)(piVar8[-1] + 0x364) == 0)) {
            *(int *)(piVar8[-1] + 0x364) = iVar7;
          }
          if ((*(char *)(iVar6 + -5 + iVar7) != '\0') && (*(int *)(*piVar8 + 0x364) == 0)) {
            *(int *)(*piVar8 + 0x364) = iVar7 + 1;
          }
          if ((*(char *)(iVar6 + -4 + iVar7) != '\0') && (*(int *)(piVar8[1] + 0x364) == 0)) {
            *(int *)(piVar8[1] + 0x364) = iVar7 + 2;
          }
          if ((*(char *)(iVar6 + -3 + iVar7) != '\0') && (*(int *)(piVar8[2] + 0x364) == 0)) {
            *(int *)(piVar8[2] + 0x364) = iVar7 + 3;
          }
          if ((*(char *)(iVar6 + -2 + iVar7) != '\0') && (*(int *)(piVar8[3] + 0x364) == 0)) {
            *(int *)(piVar8[3] + 0x364) = iVar7 + 4;
          }
          piVar8 = piVar8 + 5;
          iVar7 = iVar7 + 5;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        DAT_00450c24 = 0;
        DAT_00450c20 = 0;
        DAT_00450c1c = 0;
        DAT_00450c18 = 0;
        _DAT_00450c14 = 0;
        _DAT_00450c10 = 0;
        _DAT_00450c0c = 0;
        _DAT_00450c08 = 0;
        _DAT_00450c04 = 0;
        DAT_00450c28 = 0;
        if (0 < *(int *)(*(int *)(iVar6 + 0x7d4) + 0x4d82384)) {
          iVar7 = 0;
          do {
            FUN_0040c0e0(iVar7);
            iVar7 = iVar7 + 1;
          } while (iVar7 < *(int *)(*(int *)(iVar6 + 0x7d4) + 0x4d82384));
        }
        if (DAT_0044d024 != 99) {
          FUN_0040c030(DAT_0044d024);
        }
        local_a1c = (int *)(6 - iVar6);
        local_a30 = (int *)0x0;
        piVar8 = local_a14;
        local_a38 = puVar3;
        do {
          if (param_5[(int)local_a30] < 0xb) {
            if (0 < param_5[(int)local_a30]) {
              iVar6 = *piVar8;
              uVar14 = *(undefined4 *)(iVar6 + 0x364);
              iVar7 = *(int *)(iVar6 + 0x368);
              FUN_004061d0();
              iVar10 = local_a28;
              *(int *)(iVar6 + 0x368) = iVar7;
              uVar16 = *(undefined4 *)(iVar7 + 0x90);
              *(undefined8 *)(iVar6 + 0x58) = 0x4079000000000000;
              *(undefined4 *)(iVar6 + 0x31c) = uVar16;
              *(undefined8 *)(iVar6 + 0x60) = 0xc049000000000000;
              *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
              *(undefined4 *)(*piVar8 + 0x364) = uVar14;
              *(undefined4 *)(*piVar8 + 0x344) = uVar14;
              *local_a38 = 1;
              *(undefined4 *)(*piVar8 + 8) = 0x4b;
              iVar6 = *piVar8;
              if (*(int *)(iVar6 + 0x364) == 1) {
                *(undefined4 *)(iVar6 + 0x10) = 100;
              }
              else {
                *(int *)(iVar6 + 0x10) =
                     *(int *)(local_a3c * 0x990 + 0x4d45db0 + *(int *)(local_a28 + 0x7d4)) + -100;
              }
              iVar7 = local_a3c * 0x990;
              iVar6 = FUN_00417170(0x127,*(int *)(*(int *)(local_a28 + 0x7d4) + 0x4d45db8 + iVar7) -
                                         *(int *)(*(int *)(local_a28 + 0x7d4) + 0x4d45db4 + iVar7));
              *(int *)(*piVar8 + 0x18) =
                   iVar6 + *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db4 + iVar7);
              *(undefined4 *)(*piVar8 + 0x14) = 0;
              *(double *)(*piVar8 + 0x58) = (double)*(int *)(*piVar8 + 0x10);
              *(double *)(*piVar8 + 0x68) = (double)*(int *)(*piVar8 + 0x18);
              *(undefined8 *)(*piVar8 + 0x60) = 0;
              *(undefined4 *)(*piVar8 + 0x308) = 200;
              if (*local_a18 == 1) {
                *(undefined4 *)(*piVar8 + 0x308) = 500;
              }
              *(int **)(*piVar8 + 0x354) = local_a30;
              *(undefined4 *)(*piVar8 + 0x340) =
                   *(undefined4 *)(&DAT_0044d754 + *(int *)(*piVar8 + 0x364) * 4);
              goto LAB_0043a6ea;
            }
          }
          else {
            iVar6 = piVar8[10];
            uVar14 = *(undefined4 *)(*piVar8 + 0x364);
            iVar7 = *(int *)(*piVar8 + 0x368);
            FUN_004061d0();
            iVar10 = local_a28;
            *(int *)(iVar6 + 0x368) = iVar7;
            uVar16 = *(undefined4 *)(iVar7 + 0x90);
            *(undefined8 *)(iVar6 + 0x58) = 0x4075e00000000000;
            *(undefined4 *)(iVar6 + 0x31c) = uVar16;
            *(undefined8 *)(iVar6 + 0x60) = 0;
            *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
            *(undefined4 *)(piVar8[10] + 0x364) = uVar14;
            *(undefined4 *)(piVar8[10] + 0x344) = uVar14;
            *(undefined1 *)(local_a28 + 0xe + (int)local_a30) = 1;
            *(undefined4 *)(piVar8[10] + 8) = 0x4b;
            iVar6 = piVar8[10];
            if (*(int *)(iVar6 + 0x364) == 1) {
              *(undefined4 *)(iVar6 + 0x10) = 100;
            }
            else {
              *(int *)(iVar6 + 0x10) =
                   *(int *)(local_a3c * 0x990 + 0x4d45db0 + *(int *)(local_a28 + 0x7d4)) + -100;
            }
            iVar7 = local_a3c * 0x990;
            iVar6 = FUN_00417170(0x125,*(int *)(*(int *)(local_a28 + 0x7d4) + 0x4d45db8 + iVar7) -
                                       *(int *)(*(int *)(local_a28 + 0x7d4) + 0x4d45db4 + iVar7));
            *(int *)(piVar8[10] + 0x18) =
                 iVar6 + *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db4 + iVar7);
            *(double *)(piVar8[10] + 0x58) = (double)*(int *)(piVar8[10] + 0x10);
            *(double *)(piVar8[10] + 0x68) = (double)*(int *)(piVar8[10] + 0x18);
            *(undefined4 *)(piVar8[10] + 0x308) = 200;
            if (*local_a18 == 1) {
              *(undefined4 *)(piVar8[10] + 0x308) = 500;
            }
            *(undefined1 **)(piVar8[10] + 0x354) = local_a38 + (int)local_a1c;
            *(undefined4 *)(piVar8[10] + 0x340) =
                 *(undefined4 *)(&DAT_0044d754 + *(int *)(piVar8[10] + 0x364) * 4);
LAB_0043a6ea:
            puVar3 = local_a24;
          }
          local_a38 = local_a38 + 1;
          local_a30 = (int *)((int)local_a30 + 1);
          piVar8 = piVar8 + 1;
        } while ((int)local_a30 < 8);
        DAT_0044d034 = 1;
        DAT_00450bbc = 0;
        DAT_00450bdc = 0;
        FUN_004025b0();
        iVar6 = 0x14;
        do {
          if (puVar3[iVar6] == '\0') {
            FUN_004061d0();
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 400);
        FUN_00431c70();
        FUN_0043d2c0(*local_a18,puVar3,local_a14);
      }
      else if (DAT_00451b84 == 1) {
        *local_a1c = 0;
        *local_a34 = 3;
LAB_0043a7f0:
        DAT_0044d024 = 100;
        DAT_0044d028 = 1;
      }
      else if (DAT_00451b84 == 2) {
        *local_a34 = 0xc9;
      }
      else if (DAT_00451b84 == 3) {
        FUN_00401a30(0);
        DAT_0044d028 = 0;
        if (DAT_0044d024 == 100) {
          DAT_0044d024 = 99;
        }
        else if (DAT_0044d024 == 99) {
          DAT_0044d024 = 0;
        }
        else {
          DAT_0044d024 = DAT_0044d024 + 1;
          if (DAT_0044d024 == *(int *)(*(int *)(iVar6 + 0x7d4) + 0x4d82384)) goto LAB_0043a7f0;
        }
      }
      else if (DAT_00451b84 == 4) {
        _DAT_00450c30 = _DAT_00450c30 + -1;
        if (_DAT_00450c30 < 0) {
          _DAT_00450c30 = 2;
        }
        FUN_00401a30(0);
      }
      else if (DAT_00451b84 == 5) {
        *local_a34 = 10;
        FUN_00431c70();
        DAT_00457580 = 0;
      }
      goto LAB_00439e78;
    }
LAB_00439e80:
    if (DAT_004513bc == 0) goto LAB_00439e93;
  }
  else {
    if ((iVar7 < 0xd2) || (0xdb < iVar7)) {
LAB_00439f7f:
      if (*local_a34 == 0xca) {
        iVar6 = local_a28;
        goto LAB_00439f93;
      }
    }
    else {
      iVar6 = iVar6 * -0x113;
      FUN_0043f010(iVar6 + 0x19a,0x41,0xffffffff,0,0,local_a2c);
      iVar7 = DAT_00451ba8;
      piVar8 = DAT_0044d37c;
      if (DAT_004513b8 != 0) {
        if (0 < (int)DAT_0044d37c * 2) {
          puVar9 = &DAT_0044d5a0;
          puVar12 = &DAT_0044d650;
          for (iVar10 = ((uint)DAT_0044d37c & 0x1fffffff) << 1; iVar10 != 0; iVar10 = iVar10 + -1) {
            *puVar12 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar12 = puVar12 + 1;
          }
          puVar9 = &DAT_0044d548;
          puVar12 = &DAT_0044d5f8;
          for (iVar10 = ((uint)piVar8 & 0x1fffffff) << 1; iVar10 != 0; iVar10 = iVar10 + -1) {
            *puVar12 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar12 = puVar12 + 1;
          }
          uVar14 = local_a2c;
        }
        uVar16 = DAT_00451b88;
        *(undefined4 *)(iVar7 * 4 + 0x451b98) = DAT_00451b8c;
        *(undefined4 *)(iVar7 * 4 + 0x451b90) = uVar16;
        *local_a34 = 200;
      }
      iVar10 = *(int *)(iVar7 * 4 + 0x451b98);
      if (iVar10 != -1) {
        FUN_00438ad0(iVar6 + 0x1c8,iVar10 * 0x16 + 0xa8,0xa1,0x13,0xa7a7ff);
        iVar7 = DAT_00451ba8;
      }
      iVar7 = *(int *)(iVar7 * 4 + 0x451b90);
      if (iVar7 != -1) {
        FUN_00438ad0(iVar6 + 0x1c8,iVar7 * 0x16 + 0x130,0xa1,0x13,0xa7a7ff);
      }
      if (DAT_0044d760 < 10) {
        if ((int)DAT_0044d760 < 5) {
          FUN_004389a0(iVar6 + 0x1c6,DAT_0044d760 * 0x16 + 0x90,0xa5,0x17,0xffffff);
          iVar6 = DAT_00451ba8;
          uVar4 = DAT_0044d760;
          piVar8 = DAT_0044d37c;
          if (DAT_004513b4 != 0) {
            if (DAT_0044d760 - 1 < 3) {
              iVar7 = DAT_00451ba8 * 4;
              *(uint *)(DAT_00451ba8 * 4 + 0x451b98) = DAT_0044d760 - 1;
              if (*(int *)(iVar7 + 0x451b90) == -1) {
                *(undefined4 *)(iVar6 * 4 + 0x451b90) = 0;
              }
              if (0 < (int)piVar8) {
                iVar7 = *(int *)(iVar6 * 4 + 0x451b90) * (int)piVar8 * 4;
                local_a24 = (undefined1 *)(iVar6 * (int)piVar8 * 4);
                local_a20 = piVar8;
                do {
                  iVar10 = (int)(*(int *)((int)&DAT_0044d388 + iVar7) * uVar4) / 3;
                  iVar1 = (int)(*(int *)((int)&DAT_0044d468 + iVar7) * uVar4) / 3;
                  if ((iVar1 < 1) && (0 < iVar10)) {
                    iVar1 = 1;
                  }
                  iVar10 = iVar10 - iVar1;
                  *(int *)(local_a24 + 0x44d5f8) = iVar1;
                  *(int *)(local_a24 + 0x44d650) = iVar10;
                  if (iVar10 < 0) {
                    *(undefined4 *)(local_a24 + 0x44d650) = 0;
                  }
                  local_a24 = local_a24 + 4;
                  iVar7 = iVar7 + 4;
                  local_a20 = (int *)((int)local_a20 + -1);
                } while (local_a20 != (int *)0x0);
              }
              (&DAT_00451b74)[iVar6] = DAT_0044d760 - 1;
              (&DAT_0044d380)[iVar6] = *(int *)(iVar6 * 4 + 0x451b90) + 1;
            }
            if (DAT_0044d760 == 0) {
              *(undefined4 *)(iVar6 * 4 + 0x451b98) = 0xffffffff;
              *(undefined4 *)(iVar6 * 4 + 0x451b90) = 0xffffffff;
              if (0 < (int)piVar8) {
                puVar9 = &DAT_0044d650 + iVar6 * (int)piVar8;
                for (uVar4 = (uint)piVar8 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar9 = 0;
                  puVar9 = puVar9 + 1;
                }
                puVar9 = &DAT_0044d5f8 + iVar6 * (int)piVar8;
                for (uVar4 = (uint)piVar8 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar9 = 0;
                  puVar9 = puVar9 + 1;
                }
              }
              (&DAT_0044d380)[iVar6] = 0;
            }
            else if (DAT_0044d760 == 4) {
              iVar7 = iVar6 * (int)piVar8;
              *(undefined4 *)(iVar6 * 4 + 0x451b98) = 0xffffffff;
              *(undefined4 *)(iVar6 * 4 + 0x451b90) = 0xffffffff;
              if (0 < (int)piVar8) {
                puVar9 = &DAT_0044d650 + iVar7;
                for (uVar4 = (uint)piVar8 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar9 = 0x1e;
                  puVar9 = puVar9 + 1;
                }
                puVar9 = &DAT_0044d5f8 + iVar7;
                for (uVar4 = (uint)piVar8 & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar9 = 2;
                  puVar9 = puVar9 + 1;
                }
              }
              *(undefined4 *)(iVar7 * 4 + 0x44d614) = 1;
              *(undefined4 *)(iVar7 * 4 + 0x44d66c) = 0xf;
              *(undefined4 *)(iVar7 * 4 + 0x44d61c) = 3;
              (&DAT_0044d620)[iVar7] = 3;
              (&DAT_0044d380)[iVar6] = 6;
            }
          }
        }
        else {
          FUN_004389a0(iVar6 + 0x1c6,DAT_0044d760 * 0x16 + 0xc0,0xa5,0x17,0xffffff);
          iVar6 = DAT_00451ba8;
          if (DAT_004513b4 != 0) {
            if (*(int *)(DAT_00451ba8 * 4 + 0x451b98) == -1) {
              *(undefined4 *)(DAT_00451ba8 * 4 + 0x451b98) = 0;
            }
            uVar4 = DAT_0044d760;
            (&DAT_0044d380)[iVar6] = DAT_0044d760 - 4;
            iVar7 = *(int *)(iVar6 * 4 + 0x451b98);
            (&DAT_00451b74)[iVar6] = iVar7;
            piVar8 = DAT_0044d37c;
            iVar7 = iVar7 + 1;
            *(uint *)(iVar6 * 4 + 0x451b90) = uVar4 - 5;
            if (0 < (int)piVar8) {
              iVar10 = (uVar4 - 5) * (int)piVar8 * 4;
              iVar6 = iVar6 * (int)piVar8 * 4;
              do {
                iVar1 = (*(int *)((int)&DAT_0044d388 + iVar10) * iVar7) / 3;
                iVar2 = (*(int *)((int)&DAT_0044d468 + iVar10) * iVar7) / 3;
                if ((iVar2 < 1) && (0 < iVar1)) {
                  iVar2 = 1;
                }
                iVar1 = iVar1 - iVar2;
                *(int *)((int)&DAT_0044d5f8 + iVar6) = iVar2;
                *(int *)((int)&DAT_0044d650 + iVar6) = iVar1;
                if (iVar1 < 0) {
                  *(undefined4 *)((int)&DAT_0044d650 + iVar6) = 0;
                }
                iVar10 = iVar10 + 4;
                iVar6 = iVar6 + 4;
                piVar8 = (int *)((int)piVar8 + -1);
              } while (piVar8 != (int *)0x0);
            }
          }
        }
        if (DAT_004513a4 != 0) {
          DAT_0044d760 = DAT_0044d760 - 1;
        }
        if (DAT_004513a8 != 0) {
          DAT_0044d760 = DAT_0044d760 + 1;
        }
        uVar14 = local_a2c;
        if ((int)DAT_0044d760 < 0) {
          DAT_0044d760 = 10;
        }
        goto LAB_00439f7f;
      }
      if (DAT_0044d760 != 10) {
        if (DAT_0044d760 == 0xb) {
          FUN_004389a0(iVar6 + 0x214,0x1b1,0x6a,0x18,0xffffff);
          piVar8 = DAT_0044d37c;
          if (DAT_004513a4 != 0) {
            DAT_0044d760 = DAT_0044d760 - 2;
          }
          if (DAT_004513a8 != 0) {
            DAT_0044d760 = 0;
          }
          if (DAT_004513ac != 0) {
            DAT_0044d760 = DAT_0044d760 - 1;
          }
          if (DAT_004513b4 != 0) {
            if (0 < (int)DAT_0044d37c * 2) {
              puVar9 = &DAT_0044d5a0;
              puVar12 = &DAT_0044d650;
              for (iVar6 = ((uint)DAT_0044d37c & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
                *puVar12 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar12 = puVar12 + 1;
              }
              puVar9 = &DAT_0044d548;
              puVar12 = &DAT_0044d5f8;
              for (iVar6 = ((uint)piVar8 & 0x1fffffff) << 1; iVar6 != 0; iVar6 = iVar6 + -1) {
                *puVar12 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar12 = puVar12 + 1;
              }
              uVar14 = local_a2c;
            }
            *local_a34 = 200;
            DAT_004513b4 = 0;
            FUN_00401a30(0);
          }
        }
        goto LAB_00439f7f;
      }
      FUN_004389a0(iVar6 + 0x1b0,0x1b1,0x53,0x18,0xffffff);
      if (DAT_004513b0 != 0) {
        DAT_0044d760 = DAT_0044d760 + 1;
      }
      if (DAT_004513a4 != 0) {
        DAT_0044d760 = DAT_0044d760 - 1;
      }
      if (DAT_004513a8 != 0) {
        DAT_0044d760 = 0;
      }
      if (DAT_004513b4 == 0) goto LAB_00439f7f;
      *local_a34 = 200;
    }
LAB_00439e78:
    if (DAT_004513b4 == 0) goto LAB_00439e80;
  }
  FUN_00401a30(0);
LAB_00439e93:
  if (DAT_004513b8 != 0) {
    FUN_00401a30(0);
  }
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_a3c);
  return;
}

