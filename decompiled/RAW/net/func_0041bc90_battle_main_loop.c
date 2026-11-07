/* Function: FUN_0041bc90 */
/* Address: 0x0041bc90 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041bc90(undefined4 param_1)

{
  char cVar1;
  double dVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int *piVar12;
  char *pcVar13;
  byte bVar14;
  char *in_ECX;
  int iVar15;
  uint extraout_ECX;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  uint extraout_ECX_03;
  uint extraout_ECX_04;
  uint extraout_ECX_05;
  int iVar16;
  int *piVar17;
  uint extraout_EDX;
  uint extraout_EDX_00;
  uint extraout_EDX_01;
  uint extraout_EDX_02;
  uint extraout_EDX_03;
  uint extraout_EDX_04;
  code *pcVar18;
  undefined4 *puVar19;
  int iVar20;
  char *pcVar21;
  bool bVar22;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  undefined8 uVar23;
  undefined1 *puVar24;
  undefined4 uVar25;
  undefined1 auStack_634 [2];
  undefined1 auStack_632 [34];
  int *local_610;
  char *local_60c;
  undefined4 local_608;
  int *local_604;
  char *local_600;
  int iStack_5fc;
  int local_5f8;
  void *local_5f4;
  char *local_5f0;
  char *local_5ec;
  char *local_5e8;
  int local_5e4;
  int local_5e0;
  undefined4 local_5dc;
  int iStack_5d8;
  int iStack_5d4;
  int local_5d0 [240];
  undefined1 local_210;
  undefined1 local_20f;
  undefined1 local_20e;
  undefined1 local_20d;
  undefined1 local_20c;
  undefined1 local_20b;
  undefined1 local_20a;
  undefined1 local_209;
  undefined1 local_208;
  undefined1 local_207;
  undefined1 local_204;
  undefined1 local_203;
  undefined1 local_202;
  undefined1 local_201;
  undefined1 local_200;
  undefined1 local_1ff;
  undefined1 local_1fe;
  undefined1 local_1fd;
  byte local_1fc;
  byte local_1fb;
  char acStack_1f8 [32];
  char acStack_1d8 [32];
  char acStack_1b8 [308];
  uint local_84;
  void *local_4c;
  undefined1 *puStack_48;
  undefined4 local_44;
  
  local_44 = 0xffffffff;
  puStack_48 = &LAB_00445eba;
  local_4c = ExceptionList;
  local_84 = DAT_0044eea4 ^ (uint)auStack_634;
  ExceptionList = &local_4c;
  DAT_00450b90 = DAT_00450b90 + 1 & 0x80000001;
  local_5dc = param_1;
  if ((int)DAT_00450b90 < 0) {
    DAT_00450b90 = (DAT_00450b90 - 1 | 0xfffffffe) + 1;
  }
  if (DAT_00450b90 == 0) {
    DAT_00450bfc = DAT_0044fb60;
    DAT_0044fb60 = DAT_0044fcb0;
  }
  local_60c = (char *)(uint)(DAT_00450bfc == 1);
  pcVar21 = (char *)(uint)(DAT_00450bfc == 1);
  if (DAT_00450b84 != 0) {
    if (DAT_004553ed == 'd') {
      DAT_0044d030 = 1 - DAT_0044d030;
      DAT_004553ed = 'u';
    }
    if ((DAT_0045539d == 'd') || (DAT_0045539f == 'd')) {
      if (DAT_00450b74 == 0) {
        DAT_00450b7c = DAT_00450bc4;
        DAT_00450b74 = 1;
        DAT_00450b78 = DAT_00450bc8;
      }
      if (DAT_0045539d == 'd') {
        DAT_00450b78 = DAT_00450b78 + -5;
      }
      if (DAT_0045539f == 'd') {
        DAT_00450b78 = DAT_00450b78 + 5;
      }
    }
    if (DAT_004553a0 == 'd') {
      DAT_00450b74 = 0;
    }
    else if (DAT_00450b74 != 0) {
      DAT_00450b7c = DAT_00450b7c + DAT_00450b78;
      DAT_00450b78 = (DAT_00450b78 * 6) / 7;
      goto LAB_0041bdce;
    }
    DAT_00450b78 = 0;
  }
LAB_0041bdce:
  local_210 = 0;
  local_20f = 0;
  local_20e = 0;
  local_20d = 0;
  local_20c = 0;
  local_20b = 0;
  local_20a = 0;
  local_209 = 0;
  local_208 = 0;
  local_207 = 0;
  local_204 = 0;
  local_203 = 0;
  local_202 = 0;
  local_201 = 0;
  local_200 = 0;
  local_1ff = 0;
  local_1fe = 0;
  local_1fd = 0;
  local_1fc = 0;
  local_1fb = 0;
  if ((DAT_00450b84 != 0) && (pcVar21 == (char *)0x0)) {
    FUN_0043dc50(&local_204,DAT_0044eea4 ^ (uint)(auStack_634 + -0xc));
  }
  if (DAT_0044d05c == 1) {
    FUN_0043f010(0,0,0xffffffff,0,0,param_1);
    puVar19 = &DAT_00457588;
    for (iVar15 = 400; iVar15 != 0; iVar15 = iVar15 + -1) {
      *puVar19 = 0;
      puVar19 = puVar19 + 1;
    }
    puVar19 = &DAT_00453e10;
    for (iVar15 = 0x50; iVar15 != 0; iVar15 = iVar15 + -1) {
      *puVar19 = 0;
      puVar19 = puVar19 + 1;
    }
    FUN_004014e0("data\\001.wav");
    FUN_004014e0("data\\002.wav");
    FUN_004014e0("data\\006.wav");
    FUN_004014e0("data\\010.wav");
    FUN_004014e0("data\\011.wav");
    FUN_004014e0("data\\004.wav");
    FUN_004014e0("data\\016.wav");
    FUN_004014e0("data\\017.wav");
    FUN_004014e0("data\\020.wav");
    FUN_004014e0("data\\021.wav");
    FUN_004014e0("data\\025.wav");
    FUN_004014e0("data\\032.wav");
    FUN_004014e0("data\\033.wav");
    FUN_004014e0("data\\039.wav");
    FUN_004014e0("data\\065.wav");
    FUN_004014e0("data\\066.wav");
    FUN_004014e0("data\\068.wav");
    FUN_004014e0("data\\085.wav");
    DAT_0045843c = 0x12;
    FUN_0043e940(DAT_00458348);
    local_5f4 = operator_new(0x4d823a8);
    local_44 = 0;
    if (local_5f4 == (void *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_004122f0();
    }
    *(undefined4 *)(in_ECX + 0x7d4) = uVar4;
    local_610 = (int *)(in_ECX + 0x194);
    local_44 = 0xffffffff;
    iVar15 = 0;
    do {
      pvVar5 = operator_new(0x420);
      if (pvVar5 == (void *)0x0) {
        pvVar5 = (void *)0x0;
      }
      else {
        local_600 = (char *)**(int **)(in_ECX + 0x7d4);
        FUN_004061d0();
        *(undefined8 *)((int)pvVar5 + 0x58) = 0x4069000000000000;
        *(char **)((int)pvVar5 + 0x368) = local_600;
        *(undefined8 *)((int)pvVar5 + 0x60) = 0;
        *(undefined8 *)((int)pvVar5 + 0x68) = 0x4072c00000000000;
      }
      *local_610 = (int)pvVar5;
      in_ECX[iVar15 + 4] = '\0';
      iVar15 = iVar15 + 1;
      local_610 = local_610 + 1;
    } while (iVar15 < 400);
    iVar15 = *(int *)(in_ECX + 0x194);
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x4069000000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x198);
    in_ECX[4] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x406a400000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x19c);
    in_ECX[5] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x406a400000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x1a0);
    in_ECX[6] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x406a400000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x1a4);
    in_ECX[7] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x4082200000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0xc069000000000000;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x1a8);
    in_ECX[8] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x4081d00000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x1ac);
    in_ECX[9] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x4082200000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0xc069000000000000;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    iVar15 = *(int *)(in_ECX + 0x1b0);
    in_ECX[10] = '\x01';
    iVar20 = **(int **)(in_ECX + 0x7d4);
    FUN_004061d0();
    *(int *)(iVar15 + 0x368) = iVar20;
    uVar4 = *(undefined4 *)(iVar20 + 0x90);
    *(undefined8 *)(iVar15 + 0x58) = 0x4081d00000000000;
    *(undefined4 *)(iVar15 + 0x31c) = uVar4;
    *(undefined8 *)(iVar15 + 0x60) = 0;
    *(undefined8 *)(iVar15 + 0x68) = 0x4072c00000000000;
    in_ECX[0xb] = '\x01';
    local_5f4 = operator_new(0x1f50);
    local_44 = 1;
    if (local_5f4 == (void *)0x0) {
      DAT_0044ff8c = 0;
    }
    else {
      DAT_0044ff8c = FUN_0043ee50(0x40,"PAUSE",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 2;
    if (local_5f4 == (void *)0x0) {
      DAT_0044f8f8 = 0;
    }
    else {
      DAT_0044f8f8 = FUN_0043ee50(0x40,&DAT_0044944c,0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 3;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fcb4 = 0;
    }
    else {
      DAT_0044fcb4 = FUN_0043ee50(0x40,"SCORE_BOARD1",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 4;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fd8c = 0;
    }
    else {
      DAT_0044fd8c = FUN_0043ee50(0x40,"SCORE_BOARD2",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 5;
    if (local_5f4 == (void *)0x0) {
      DAT_0044f88c = 0;
    }
    else {
      DAT_0044f88c = FUN_0043ee50(0x40,"SCORE_BOARD3",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 6;
    if (local_5f4 == (void *)0x0) {
      DAT_0044f87c = 0;
    }
    else {
      DAT_0044f87c = FUN_0043ee50(0x40,"SCORE_BOARD4",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 7;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fd90 = 0;
    }
    else {
      DAT_0044fd90 = FUN_0043ee50(0x40,"WIN_ALIVE",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 8;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fd94 = 0;
    }
    else {
      DAT_0044fd94 = FUN_0043ee50(0x40,"WIN_DEAD",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 9;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fb64 = 0;
    }
    else {
      DAT_0044fb64 = FUN_0043ee50(0x40,"LOSE_DEAD",0);
    }
    local_44 = 0xffffffff;
    local_5f4 = operator_new(0x1f50);
    local_44 = 10;
    if (local_5f4 == (void *)0x0) {
      DAT_0044fd7c = 0;
    }
    else {
      DAT_0044fd7c = FUN_0043ee50(0x40,&DAT_004493e0,0);
    }
    local_44 = 0xffffffff;
    DAT_0044d05c = 0;
    pcVar21 = local_60c;
  }
  _DAT_0044d040 = 0x1010101;
  _DAT_0044d044 = 0x1010101;
  _DAT_0044d048 = 0x1010101;
  _DAT_0044d04c = 0x1010101;
  _DAT_0044d050 = 0x1010101;
  DAT_0044d054 = 0;
  if (pcVar21 == (char *)0x0) {
    FUN_00419a60(DAT_00450b90,DAT_00451160,&local_210);
  }
  if (DAT_00450b90 == 0) {
    WSAAsyncSelect(DAT_0044f1b4,DAT_004546f4,0,0);
    WSAAsyncSelect(DAT_0044f46c,DAT_004546f4,0,0);
    ioctlsocket(DAT_0044f1b4,-0x7ffb9982,(u_long *)0x0);
    local_600 = (char *)0x0;
    ioctlsocket(DAT_0044f46c,-0x7ffb9982,(u_long *)&local_600);
    if (DAT_0044f1af == '\0') {
      if (DAT_00450b88 != 0) {
        if (DAT_004553eb == 'd') {
          FUN_00416cd0();
          FUN_00431c70();
        }
        if (DAT_004553ec == 'd') {
          DAT_004553ec = 'u';
          FUN_00416e30();
        }
        if ((local_1fb & 1) != 0) {
          FUN_00416c70(&local_210);
        }
        if ((local_1fb & 2) != 0) {
          FUN_00416ca0(&local_210);
        }
        if (DAT_004553e8 == 'd') {
          DAT_004553e8 = 'u';
          FUN_00416dd0(&DAT_0044d020);
        }
        if (DAT_004553e9 == 'd') {
          DAT_004553e9 = 'u';
          FUN_00416df0(&DAT_0044d020);
        }
        uVar6 = (uint)local_1fc;
        if ((local_1fc & 4) != 0) {
          FUN_00416e10();
          uVar6 = extraout_ECX;
        }
        if ((uVar6 & 0x10) != 0) {
          FUN_00416e60(&local_210,&DAT_0044d020,&DAT_00451160);
          uVar6 = (uint)local_1fc;
        }
        if ((uVar6 & 0x20) != 0) {
          FUN_00416eb0(&local_210,&DAT_0044d020,&DAT_00451160);
          uVar6 = (uint)local_1fc;
        }
        bVar14 = (byte)uVar6;
        if ((uVar6 & 0x40) != 0) {
          FUN_00416f10(&local_210,&DAT_0044d020,&DAT_00451160);
          bVar14 = local_1fc;
        }
        if ((char)bVar14 < '\0') {
          FUN_00416f60(&local_210,&DAT_0044d020,&DAT_00451160);
        }
        goto LAB_0041c986;
      }
      if (DAT_00455471 == 'd') {
        DAT_00455471 = 'u';
        FUN_00416c70(&local_210);
      }
      if (DAT_00455470 == 'd') {
        DAT_00455470 = 'u';
        FUN_00416ca0(&local_210);
      }
      if ((DAT_004553eb == 'd') && (DAT_0044d020 == 0)) {
        DAT_004553eb = 'u';
        FUN_00416cd0();
      }
      iVar15 = DAT_0044d020;
      if ((DAT_004553e8 == 'd') && (DAT_0044d020 == 0)) {
        DAT_004553e8 = 'u';
        FUN_00416dd0(&DAT_0044d020);
      }
      if ((DAT_004553e9 == 'd') && (iVar15 == 0)) {
        DAT_004553e9 = 'u';
        FUN_00416df0(&DAT_0044d020);
      }
      if ((DAT_004553ea == 'd') && (iVar15 == 0)) {
        DAT_004553ea = 'u';
        FUN_00416e10();
      }
      if ((DAT_004553ec == 'd') && (iVar15 == 0)) {
        DAT_004553ec = 'u';
        FUN_00416e30();
      }
      if (DAT_004553ed == 'd') {
        DAT_004553ed = 'u';
        FUN_00416e60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (DAT_004553ee == 'd') {
        DAT_004553ee = 'u';
        FUN_00416eb0(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (DAT_004553ef == 'd') {
        DAT_004553ef = 'u';
        FUN_00416f10(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (DAT_004553f0 == 'd') {
        DAT_004553f0 = 'u';
        FUN_00416f60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
    }
    else {
LAB_0041c986:
      iVar15 = DAT_0044d020;
    }
    if (DAT_0044f1af == '\x01') {
      if (DAT_00455471 == 'd') {
        DAT_0044d04c = DAT_0044d04c | 8;
        _DAT_0044d04c = (uint)DAT_0044d04c;
        DAT_00455471 = 'u';
      }
      if (DAT_00455470 == 'd') {
        DAT_0044d04c = DAT_0044d04c | 0x10;
        DAT_00455470 = 'u';
      }
      if ((DAT_004553e8 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x20000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553e8 = 'u';
      }
      if ((DAT_004553e9 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x400000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553e9 = 'u';
      }
      if ((DAT_004553ea == 'd') && (iVar15 == 0)) {
        DAT_0044d04c = DAT_0044d04c | 2;
        DAT_004553ea = 'u';
      }
      if ((DAT_004553eb == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x40000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553eb = 'u';
      }
      if ((DAT_004553ec == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x80000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ec = 'u';
      }
      if ((DAT_004553ed == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x100000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ed = 'u';
      }
      if ((DAT_004553ee == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x200000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ee = 'u';
      }
      if ((DAT_004553ef == 'd') && (iVar15 == 0)) {
        DAT_0044d04c = DAT_0044d04c | 4;
        DAT_004553ef = 'u';
      }
      if ((DAT_004553f0 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x800000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553f0 = 'u';
      }
      uVar6 = _DAT_0044d048;
      iVar15 = 0;
      piVar12 = (int *)(in_ECX + 0x198);
      iVar20 = 4;
      pcVar21 = in_ECX;
      do {
        if (pcVar21[4] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[-1] + 0x2fc);
        }
        if (pcVar21[5] == '\x01') {
          iVar15 = iVar15 + *(int *)(*piVar12 + 0x2fc);
        }
        if (pcVar21[6] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[1] + 0x2fc);
        }
        if (pcVar21[7] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[2] + 0x2fc);
        }
        if (pcVar21[8] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[3] + 0x2fc);
        }
        piVar12 = piVar12 + 5;
        iVar20 = iVar20 + -1;
        pcVar21 = pcVar21 + 5;
      } while (iVar20 != 0);
      DAT_00450bf4 = iVar15 + (iVar15 / 100) * -100 + 1;
      DAT_00450bf0 = (DAT_00450bf0 + 1) % 0x32;
      _DAT_0044d048 = CONCAT13((undefined1)DAT_0044d03c,_DAT_0044d048);
      _DAT_0044d04c = CONCAT11((char)DAT_00450bf4,DAT_0044d04c);
      DAT_0044d048 = (undefined1)uVar6;
      _DAT_0044d048 = CONCAT11((char)DAT_00450bf0,DAT_0044d048);
      _DAT_0044d04c =
           CONCAT13((char)(DAT_0044f620 + (DAT_0044f620 >> 0x1f & 0xffU) >> 8),
                    CONCAT12((char)DAT_0044f620,_DAT_0044d04c));
      send(DAT_0044f46c,&DAT_0044d040,0x16,0);
      uVar6 = recv(DAT_0044f46c,&DAT_0044f198,0x16,0);
      uVar7 = uVar6;
      pcVar18 = PostMessageA_exref;
      while ((PostMessageA_exref = pcVar18, uVar6 < 0x16 && (0 < (int)uVar7))) {
        uVar7 = recv(DAT_0044f46c,&DAT_0044f198 + uVar6,0x16 - uVar6,0);
        uVar6 = uVar6 + uVar7;
        pcVar18 = PostMessageA_exref;
      }
      if (DAT_0044f1a1 != DAT_00450bf0) {
        MessageBoxA((HWND)0x0,"Connection Lost!","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        pcVar18 = PostMessageA_exref;
        PostMessageA(DAT_004546f4,0x10,0,0);
      }
      if (DAT_0044f1a3 != DAT_0044d03c) {
        MessageBoxA((HWND)0x0,"Version not matched! ","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      if (DAT_0044f1a5 != DAT_00450bf4) {
        MessageBoxA((HWND)0x0,"Synchronisation Error!","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      if ((DAT_0044f1a6 != (char)DAT_0044f620) ||
         (DAT_0044f1a7 != (char)(DAT_0044f620 + (DAT_0044f620 >> 0x1f & 0xffU) >> 8))) {
        MessageBoxA((HWND)0x0,"Data Error! You and your opponent have different set of data files.",
                    "Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      uVar6 = (uint)DAT_0044f1a2;
      uVar7 = _DAT_0044d048 >> 0x10 & 0xff;
      if (((DAT_0044f1a2 & 2) != 0) || ((_DAT_0044d048 & 0x20000) != 0)) {
        FUN_00416dd0(&DAT_0044d020);
        uVar6 = extraout_ECX_00;
        uVar7 = extraout_EDX;
      }
      if (((uVar6 & 0x40) != 0) || ((uVar7 & 0x40) != 0)) {
        FUN_00416df0(&DAT_0044d020);
        uVar6 = extraout_ECX_01;
        uVar7 = extraout_EDX_00;
      }
      if (((uVar6 & 4) != 0) || ((uVar7 & 4) != 0)) {
        FUN_00416cd0();
      }
      if (((DAT_0044f1a2 & 8) != 0) || ((_DAT_0044d048 & 0x80000) != 0)) {
        FUN_00416e30();
      }
      uVar6 = (uint)DAT_0044f1a4;
      uVar7 = _DAT_0044d04c & 0xff;
      if (((DAT_0044f1a4 & 2) != 0) || ((_DAT_0044d04c & 2) != 0)) {
        FUN_00416e10();
        uVar6 = extraout_ECX_02;
        uVar7 = extraout_EDX_01;
      }
      if (((uVar6 & 8) != 0) || ((uVar7 & 8) != 0)) {
        FUN_00416c70(&local_210);
      }
      if (((DAT_0044f1a4 & 0x10) != 0) || ((_DAT_0044d04c & 0x10) != 0)) {
        FUN_00416ca0(&local_210);
      }
      if (((DAT_0044f1a2 & 0x10) != 0) || ((_DAT_0044d048 & 0x100000) != 0)) {
        FUN_00416e60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a2 & 0x20) != 0) || ((_DAT_0044d048 & 0x200000) != 0)) {
        FUN_00416eb0(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a4 & 4) != 0) || ((_DAT_0044d04c & 4) != 0)) {
        FUN_00416f10(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a2 & 0x80) != 0) || ((_DAT_0044d048 & 0x800000) != 0)) {
        FUN_00416f60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      iVar15 = DAT_0044d020;
    }
    if (DAT_0044f1af == '\x02') {
      if (DAT_00455471 == 'd') {
        DAT_0044d04c = DAT_0044d04c | 8;
        _DAT_0044d04c = (uint)DAT_0044d04c;
        DAT_00455471 = 'u';
      }
      if (DAT_00455470 == 'd') {
        DAT_0044d04c = DAT_0044d04c | 0x10;
        DAT_00455470 = 'u';
      }
      if ((DAT_004553e8 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x20000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553e8 = 'u';
      }
      if ((DAT_004553e9 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x400000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553e9 = 'u';
      }
      if ((DAT_004553ea == 'd') && (iVar15 == 0)) {
        DAT_0044d04c = DAT_0044d04c | 2;
        DAT_004553ea = 'u';
      }
      if ((DAT_004553eb == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x40000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553eb = 'u';
      }
      if ((DAT_004553ec == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x80000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ec = 'u';
      }
      if ((DAT_004553ed == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x100000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ed = 'u';
      }
      if ((DAT_004553ee == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x200000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553ee = 'u';
      }
      if ((DAT_004553ef == 'd') && (iVar15 == 0)) {
        DAT_0044d04c = DAT_0044d04c | 4;
        DAT_004553ef = 'u';
      }
      if ((DAT_004553f0 == 'd') && (iVar15 == 0)) {
        _DAT_0044d048 = (uint3)_DAT_0044d048 | 0x800000;
        _DAT_0044d048 = (uint)_DAT_0044d048;
        DAT_004553f0 = 'u';
      }
      uVar6 = _DAT_0044d048;
      iVar15 = 0;
      piVar12 = (int *)(in_ECX + 0x198);
      iVar20 = 4;
      pcVar21 = in_ECX;
      do {
        if (pcVar21[4] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[-1] + 0x2fc);
        }
        if (pcVar21[5] == '\x01') {
          iVar15 = iVar15 + *(int *)(*piVar12 + 0x2fc);
        }
        if (pcVar21[6] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[1] + 0x2fc);
        }
        if (pcVar21[7] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[2] + 0x2fc);
        }
        if (pcVar21[8] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[3] + 0x2fc);
        }
        piVar12 = piVar12 + 5;
        iVar20 = iVar20 + -1;
        pcVar21 = pcVar21 + 5;
      } while (iVar20 != 0);
      DAT_00450bf4 = iVar15 + (iVar15 / 100) * -100 + 1;
      DAT_00450bf0 = (DAT_00450bf0 + 1) % 0x32;
      _DAT_0044d048 = CONCAT13((undefined1)DAT_0044d03c,_DAT_0044d048);
      _DAT_0044d04c = CONCAT11((char)DAT_00450bf4,DAT_0044d04c);
      DAT_0044d048 = (undefined1)uVar6;
      _DAT_0044d048 = CONCAT11((char)DAT_00450bf0,DAT_0044d048);
      _DAT_0044d04c =
           CONCAT13((char)(DAT_0044f620 + (DAT_0044f620 >> 0x1f & 0xffU) >> 8),
                    CONCAT12((char)DAT_0044f620,_DAT_0044d04c));
      uVar6 = recv(DAT_0044f46c,&DAT_0044f198,0x16,0);
      uVar7 = uVar6;
      while ((uVar6 < 0x16 && (0 < (int)uVar7))) {
        uVar7 = recv(DAT_0044f46c,&DAT_0044f198 + uVar6,0x16 - uVar6,0);
        uVar6 = uVar6 + uVar7;
      }
      send(DAT_0044f46c,&DAT_0044d040,0x16,0);
      if (DAT_0044f1a1 == DAT_00450bf0) {
        pcVar18 = PostMessageA_exref;
      }
      else {
        MessageBoxA((HWND)0x0,"Connection Lost!","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        pcVar18 = PostMessageA_exref;
        PostMessageA(DAT_004546f4,0x10,0,0);
      }
      if (DAT_0044f1a3 != DAT_0044d03c) {
        MessageBoxA((HWND)0x0,"Version not matched!","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      if (DAT_0044f1a5 != DAT_00450bf4) {
        MessageBoxA((HWND)0x0,"Synchronisation Error!","Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      if ((DAT_0044f1a6 != (char)DAT_0044f620) ||
         (DAT_0044f1a7 != (char)(DAT_0044f620 + (DAT_0044f620 >> 0x1f & 0xffU) >> 8))) {
        MessageBoxA((HWND)0x0,"Data Error! You and your opponent have different set of data files.",
                    "Error",0);
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        (*pcVar18)();
      }
      uVar6 = (uint)DAT_0044f1a2;
      uVar7 = _DAT_0044d048 >> 0x10 & 0xff;
      if (((DAT_0044f1a2 & 2) != 0) || ((_DAT_0044d048 & 0x20000) != 0)) {
        FUN_00416dd0(&DAT_0044d020);
        uVar6 = extraout_ECX_03;
        uVar7 = extraout_EDX_02;
      }
      if (((uVar6 & 0x40) != 0) || ((uVar7 & 0x40) != 0)) {
        FUN_00416df0(&DAT_0044d020);
        uVar6 = extraout_ECX_04;
        uVar7 = extraout_EDX_03;
      }
      if (((uVar6 & 4) != 0) || ((uVar7 & 4) != 0)) {
        FUN_00416cd0();
      }
      if (((DAT_0044f1a2 & 8) != 0) || ((_DAT_0044d048 & 0x80000) != 0)) {
        FUN_00416e30();
      }
      uVar6 = (uint)DAT_0044f1a4;
      uVar7 = _DAT_0044d04c & 0xff;
      if (((DAT_0044f1a4 & 2) != 0) || ((_DAT_0044d04c & 2) != 0)) {
        FUN_00416e10();
        uVar6 = extraout_ECX_05;
        uVar7 = extraout_EDX_04;
      }
      if (((uVar6 & 8) != 0) || ((uVar7 & 8) != 0)) {
        FUN_00416c70(&local_210);
      }
      if (((DAT_0044f1a4 & 0x10) != 0) || ((_DAT_0044d04c & 0x10) != 0)) {
        FUN_00416ca0(&local_210);
      }
      if (((DAT_0044f1a2 & 0x10) != 0) || ((_DAT_0044d048 & 0x100000) != 0)) {
        FUN_00416e60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a2 & 0x20) != 0) || ((_DAT_0044d048 & 0x200000) != 0)) {
        FUN_00416eb0(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a4 & 4) != 0) || ((_DAT_0044d04c & 4) != 0)) {
        FUN_00416f10(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      if (((DAT_0044f1a2 & 0x80) != 0) || ((_DAT_0044d048 & 0x800000) != 0)) {
        FUN_00416f60(&local_210,&DAT_0044d020,&DAT_00451160);
      }
      goto LAB_0041d469;
    }
  }
  else {
LAB_0041d469:
    iVar15 = DAT_0044d020;
  }
  if (local_60c == (char *)0x0) {
    FUN_004198f0(&DAT_0044f198,DAT_00450b90,&local_210);
    if (DAT_00450b84 != 0) {
      FUN_004197a0();
      local_600 = (char *)(DAT_00450b8c / 0x96);
      if (DAT_00450b8c == (int)local_600 * 0x96) {
        iVar15 = 0;
        piVar12 = (int *)(in_ECX + 0x198);
        iVar20 = 4;
        pcVar21 = in_ECX;
        do {
          if (pcVar21[4] == '\x01') {
            iVar15 = iVar15 + *(int *)(piVar12[-1] + 0x2fc);
          }
          if (pcVar21[5] == '\x01') {
            iVar15 = iVar15 + *(int *)(*piVar12 + 0x2fc);
          }
          if (pcVar21[6] == '\x01') {
            iVar15 = iVar15 + *(int *)(piVar12[1] + 0x2fc);
          }
          if (pcVar21[7] == '\x01') {
            iVar15 = iVar15 + *(int *)(piVar12[2] + 0x2fc);
          }
          if (pcVar21[8] == '\x01') {
            iVar15 = iVar15 + *(int *)(piVar12[3] + 0x2fc);
          }
          piVar12 = piVar12 + 5;
          iVar20 = iVar20 + -1;
          pcVar21 = pcVar21 + 5;
        } while (iVar20 != 0);
        if (iVar15 != *(int *)(DAT_004588ac + 0x14b8 + (int)local_600 * 4)) {
          MessageBoxA((HWND)0x0,"Recording file error! Replaying canceled!",(LPCSTR)0x0,0);
          FUN_00431c70();
          iVar15 = DAT_0044d020;
          if ((DAT_00450b84 != 0) && (DAT_0044d020 != 10)) {
            DAT_00451160 = 6;
            if ((DAT_004588ac != 0) && (DAT_00450b88 != 0)) {
              FUN_0043df00();
              DAT_00458428 = *(int *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3f8 + DAT_004588ac);
              DAT_0045842c = *(undefined4 *)
                              (&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3fc + DAT_004588ac);
            }
            DAT_00450b88 = 0;
            DAT_00450b84 = 0;
            DAT_0044d020 = 10;
            iVar15 = 10;
          }
          goto LAB_0041d5db;
        }
      }
    }
    iVar15 = DAT_0044d020;
  }
LAB_0041d5db:
  if (DAT_00450b80 == 0) {
    if (local_60c == (char *)0x0) goto LAB_0041d6b9;
  }
  else if (local_60c == (char *)0x0) {
    if (DAT_00450b84 == 0) {
      puVar24 = &local_210;
    }
    else {
      puVar24 = &local_204;
    }
    FUN_0043db40(puVar24);
    if (DAT_00450b8c == (DAT_00450b8c / 0x96) * 0x96) {
      iVar15 = 0;
      piVar12 = (int *)(in_ECX + 0x198);
      local_610 = (int *)0x4;
      pcVar21 = in_ECX;
      do {
        if (pcVar21[4] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[-1] + 0x2fc);
        }
        if (pcVar21[5] == '\x01') {
          iVar15 = iVar15 + *(int *)(*piVar12 + 0x2fc);
        }
        if (pcVar21[6] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[1] + 0x2fc);
        }
        if (pcVar21[7] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[2] + 0x2fc);
        }
        if (pcVar21[8] == '\x01') {
          iVar15 = iVar15 + *(int *)(piVar12[3] + 0x2fc);
        }
        piVar12 = piVar12 + 5;
        local_610 = (int *)((int)local_610 + -1);
        pcVar21 = pcVar21 + 5;
      } while (local_610 != (int *)0x0);
      *(int *)(DAT_004588a8 + 0x14b8 + (DAT_00450b8c / 0x96) * 4) = iVar15;
      local_610 = (int *)0x0;
    }
    iVar15 = DAT_0044d020;
LAB_0041d6b9:
    if (DAT_00450b8c < 0x9e33f) {
      DAT_00450b8c = DAT_00450b8c + 1;
      if (0x9e33e < DAT_00450b8c) {
        DAT_00450b8c = 0x9e33f;
      }
    }
    else {
      DAT_00450b8c = 0x9e33f;
      if (DAT_00450b80 != 0) {
        DAT_00450b80 = 0;
        MessageBoxA((HWND)0x0,"Game play is too long (more than 3 hours), Recording canceled!",
                    (LPCSTR)0x0,0);
        iVar15 = DAT_0044d020;
      }
    }
  }
  uVar4 = local_5dc;
  _DAT_00450c00 = (uint)(DAT_00450bfc == 2);
  if (local_60c == (char *)0x0) {
    if (DAT_00450bfc == 2) {
      DAT_00450bfc = 1;
    }
    DAT_00450bd8 = 1 - DAT_00450bd8;
    DAT_00450bd0 = (DAT_00450bd0 + 1) % 0xc;
    local_5e0 = 0;
    DAT_00450bd4 = (DAT_00450bd4 + 1) % 3;
    if (DAT_00451160 == 1) {
      if (iVar15 == 0) {
        local_5e0 = 1;
        piVar12 = (int *)(in_ECX + 0x198);
        local_610 = (int *)0x50;
        pcVar21 = in_ECX;
        do {
          if (((((pcVar21[4] != '\0') && (iVar15 = piVar12[-1], 0 < *(int *)(iVar15 + 0x2fc))) &&
               (*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0)) &&
              ((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)))) && (iVar15 != 5)
             ) {
            local_5e0 = 0;
          }
          if (((pcVar21[5] != '\0') && (iVar15 = *piVar12, 0 < *(int *)(iVar15 + 0x2fc))) &&
             ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
              (((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)) && (iVar15 != 5))
              )))) {
            local_5e0 = 0;
          }
          if (((pcVar21[6] != '\0') && (iVar15 = piVar12[1], 0 < *(int *)(iVar15 + 0x2fc))) &&
             (((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
               ((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)))) &&
              (iVar15 != 5)))) {
            local_5e0 = 0;
          }
          if ((((pcVar21[7] != '\0') && (iVar15 = piVar12[2], 0 < *(int *)(iVar15 + 0x2fc))) &&
              (*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0)) &&
             (((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)) && (iVar15 != 5)))
             ) {
            local_5e0 = 0;
          }
          if (((pcVar21[8] != '\0') && (iVar15 = piVar12[3], 0 < *(int *)(iVar15 + 0x2fc))) &&
             ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
              (((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)) && (iVar15 != 5))
              )))) {
            local_5e0 = 0;
          }
          piVar12 = piVar12 + 5;
          local_610 = (int *)((int)local_610 + -1);
          pcVar21 = pcVar21 + 5;
        } while (local_610 != (int *)0x0);
        if (((local_5e0 == 1) || (0 < DAT_00450ba8)) &&
           ((DAT_00450bdc = DAT_00450bdc + 1, DAT_00450ba8 < 1 && (DAT_00450bdc == 0x50)))) {
          DAT_0044d02c = 1;
          FUN_00402100();
          goto LAB_0041dd38;
        }
      }
    }
    else {
      local_5d0[0] = 0;
      local_5d0[1] = 0;
      local_5d0[2] = 0;
      local_5d0[3] = 0;
      local_5d0[4] = 0;
      local_5d0[5] = 0;
      local_5d0[6] = 0;
      local_5d0[7] = 0;
      local_5d0[8] = 0;
      local_5d0[9] = 0;
      local_5d0[10] = 0;
      local_5d0[0xb] = 0;
      local_5d0[0xc] = 0;
      local_5d0[0xd] = 0;
      local_5d0[0xe] = 0;
      local_5d0[0xf] = 0;
      local_5d0[0x10] = 0;
      local_5d0[0x11] = 0;
      local_5d0[0x12] = 0;
      local_5d0[0x13] = 0;
      local_5d0[0x14] = 0;
      local_5d0[0x15] = 0;
      local_5d0[0x16] = 0;
      local_5d0[0x17] = 0;
      local_5d0[0x18] = 0;
      local_5d0[0x19] = 0;
      local_5d0[0x1a] = 0;
      local_5d0[0x1b] = 0;
      local_5d0[0x1c] = 0;
      local_5d0[0x1d] = 0;
      local_5d0[0x1e] = 0;
      local_5d0[0x1f] = 0;
      local_5d0[0x20] = 0;
      local_5d0[0x21] = 0;
      local_5d0[0x22] = 0;
      local_5d0[0x23] = 0;
      local_5d0[0x24] = 0;
      local_5d0[0x25] = 0;
      local_5d0[0x26] = 0;
      local_5d0[0x27] = 0;
      piVar12 = (int *)(in_ECX + 0x198);
      iVar15 = 0x50;
      pcVar21 = in_ECX;
      do {
        iVar20 = iVar15;
        if (((pcVar21[4] != '\0') && (iVar15 = piVar12[-1], 0 < *(int *)(iVar15 + 0x2fc))) &&
           ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
            (((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)) && (iVar15 != 5))))
           )) {
          local_5d0[*(int *)(piVar12[-1] + 0x364)] = local_5d0[*(int *)(piVar12[-1] + 0x364)] + 1;
        }
        if (((pcVar21[5] != '\0') && (iVar15 = *piVar12, 0 < *(int *)(iVar15 + 0x2fc))) &&
           (((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
             ((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)))) && (iVar15 != 5))
           )) {
          local_5d0[*(int *)(*piVar12 + 0x364)] = local_5d0[*(int *)(*piVar12 + 0x364)] + 1;
        }
        if (((((pcVar21[6] != '\0') && (iVar15 = piVar12[1], 0 < *(int *)(iVar15 + 0x2fc))) &&
             (*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0)) &&
            ((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)))) && (iVar15 != 5))
        {
          local_5d0[*(int *)(piVar12[1] + 0x364)] = local_5d0[*(int *)(piVar12[1] + 0x364)] + 1;
        }
        if (((pcVar21[7] != '\0') && (iVar15 = piVar12[2], 0 < *(int *)(iVar15 + 0x2fc))) &&
           ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
            (((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)) && (iVar15 != 5))))
           )) {
          local_5d0[*(int *)(piVar12[2] + 0x364)] = local_5d0[*(int *)(piVar12[2] + 0x364)] + 1;
        }
        if ((((pcVar21[8] != '\0') && (iVar15 = piVar12[3], 0 < *(int *)(iVar15 + 0x2fc))) &&
            ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f8) == 0 &&
             ((iVar15 = *(int *)(iVar15 + 0x364), 0 < iVar15 && (iVar15 < 0x28)))))) &&
           (iVar15 != 5)) {
          local_5d0[*(int *)(piVar12[3] + 0x364)] = local_5d0[*(int *)(piVar12[3] + 0x364)] + 1;
        }
        piVar12 = piVar12 + 5;
        iVar15 = iVar20 + -1;
        pcVar21 = pcVar21 + 5;
      } while (iVar15 != 0);
      iVar16 = 0;
      piVar12 = local_5d0 + 1;
      iVar15 = iVar20 + 1;
      do {
        if (0 < piVar12[-1]) {
          DAT_00450bf8 = iVar15 + -2;
          iVar16 = iVar16 + 1;
        }
        if (0 < *piVar12) {
          DAT_00450bf8 = iVar15 + -1;
          iVar16 = iVar16 + 1;
        }
        if (0 < piVar12[1]) {
          iVar16 = iVar16 + 1;
          DAT_00450bf8 = iVar15;
        }
        if (0 < piVar12[2]) {
          DAT_00450bf8 = iVar15 + 1;
          iVar16 = iVar16 + 1;
        }
        if (0 < piVar12[3]) {
          DAT_00450bf8 = iVar15 + 2;
          iVar16 = iVar16 + 1;
        }
        iVar20 = iVar15 + 3;
        piVar12 = piVar12 + 5;
        iVar15 = iVar15 + 5;
      } while (iVar20 < 0x28);
      if (((iVar16 < 2) && (DAT_0044d020 == 0)) && ((DAT_00451b7c == 1 || (DAT_00451160 != 4)))) {
        if (iVar16 == 0) {
          DAT_00450bf8 = -1;
        }
        DAT_00450bdc = DAT_00450bdc + 1;
        if (DAT_00450bdc == 0x50) {
          if ((((DAT_00451160 != 0) && (DAT_00451160 != 2)) && (DAT_00451160 != 3)) &&
             (DAT_00451160 != 4)) {
            if (DAT_00451160 == 5) goto LAB_0041dd38;
            FUN_00402100();
          }
          if (DAT_00451160 != 5) {
            DAT_0044d02c = 1;
          }
LAB_0041dd38:
          FUN_00401a30(0);
        }
      }
      else if ((DAT_00451160 != 2) && (DAT_00451160 != 3)) {
        DAT_00450bf8 = -1;
      }
    }
    if (DAT_00450bdc == 0x91) {
      if (DAT_00450c2c == 0) {
        DAT_00450bdc = 0x90;
      }
    }
    else if (0x15d < DAT_00450bdc) {
      local_610 = (int *)(in_ECX + 4);
      piVar12 = (int *)(in_ECX + 0x194);
      local_5e0 = 400;
      do {
        if ((char)*local_610 != '\0') {
          iVar15 = *piVar12;
          if (*(int *)(iVar15 + 0x324) < 0) {
            if ((*(int *)(*(int *)(iVar15 + 0x368) + 0x6f4) == 0x32) && (DAT_00458428 == 0)) {
              piVar8 = *(int **)(in_ECX + 0x7d4);
              iVar15 = 0;
              if (0 < piVar8[0x13608e0]) {
                piVar17 = piVar8;
                do {
                  if (*(int *)(*piVar17 + 0x6f4) == 6) {
                    *(int *)(*piVar12 + 0x368) = piVar8[iVar15];
                    break;
                  }
                  iVar15 = iVar15 + 1;
                  piVar17 = piVar17 + 1;
                } while (iVar15 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
              }
            }
            else if (-1 < *(int *)(iVar15 + 0x328)) {
              iVar20 = *(int *)(iVar15 + 0x32c);
              *(undefined4 *)(iVar15 + 0x328) = 0xffffffff;
              *(undefined4 *)(*piVar12 + 0x338) = 900;
              local_5f0 = (char *)0x0;
              if (0 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380)) {
                do {
                  local_5f8 = *(int *)(*(int *)(in_ECX + 0x7d4) + (int)local_5f0 * 4);
                  iVar15 = *piVar12;
                  if (*(int *)(local_5f8 + 0x6f4) == *(int *)(iVar15 + 0x330)) {
                    *(int *)(iVar15 + 0x368) = local_5f8;
                  }
                  else if (*(int *)(local_5f8 + 0x6f4) == *(int *)(iVar15 + 0x334)) {
                    local_600 = *(char **)(in_ECX + iVar20 * 4 + 0x194);
                    FUN_004061d0();
                    *(int *)(local_600 + 0x368) = local_5f8;
                    uVar4 = *(undefined4 *)(local_5f8 + 0x90);
                    local_600[0x58] = '\0';
                    local_600[0x59] = '\0';
                    local_600[0x5a] = '\0';
                    local_600[0x5b] = '\0';
                    local_600[0x5c] = '\0';
                    local_600[0x5d] = ' ';
                    local_600[0x5e] = -0x7e;
                    local_600[0x5f] = '@';
                    *(undefined4 *)(local_600 + 0x31c) = uVar4;
                    local_600[0x60] = '\0';
                    local_600[0x61] = '\0';
                    local_600[0x62] = '\0';
                    local_600[99] = '\0';
                    local_600[100] = '\0';
                    local_600[0x65] = '\0';
                    local_600[0x66] = 'i';
                    local_600[0x67] = -0x40;
                    local_600[0x68] = '\0';
                    local_600[0x69] = '\0';
                    local_600[0x6a] = '\0';
                    local_600[0x6b] = '\0';
                    local_600[0x6c] = '\0';
                    local_600[0x6d] = -0x40;
                    local_600[0x6e] = 'r';
                    local_600[0x6f] = '@';
                    in_ECX[iVar20 + 4] = '\x01';
                  }
                  local_5f0 = local_5f0 + 1;
                } while ((int)local_5f0 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
              }
              *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x2fc) =
                   *(int *)(*piVar12 + 0x2fc) / 2;
              *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x300) =
                   *(int *)(*piVar12 + 0x300) / 2;
              *(int *)(*piVar12 + 0x2fc) = *(int *)(*piVar12 + 0x2fc) / 2;
              *(int *)(*piVar12 + 0x300) = *(int *)(*piVar12 + 0x300) / 2;
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10) =
                   *(undefined4 *)(*piVar12 + 0x10);
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x18) =
                   *(undefined4 *)(*piVar12 + 0x18);
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14) = 0;
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x58) =
                   (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10);
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x68) =
                   (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x18);
              *(undefined8 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x60) = 0;
              *(undefined8 *)(*piVar12 + 0x40) = 0;
              *(undefined8 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x40) = 0;
              *(char *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x80) =
                   '\x01' - *(char *)(*piVar12 + 0x80);
              *(undefined4 *)(*piVar12 + 0x70) = 0x70;
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = 0x70;
              *(undefined4 *)(*piVar12 + 0x308) = 0;
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x308) = 0;
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x364) =
                   *(undefined4 *)(*piVar12 + 0x364);
            }
          }
          else {
            piVar8 = *(int **)(in_ECX + 0x7d4);
            iVar20 = 0;
            if (0 < piVar8[0x13608e0]) {
              do {
                if (*(int *)(*piVar8 + 0x6f4) == *(int *)(iVar15 + 0x324)) {
                  *(undefined4 *)(*piVar12 + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar20 * 4);
                  *(undefined4 *)(*piVar12 + 0x324) = 0xffffffff;
                  break;
                }
                iVar20 = iVar20 + 1;
                piVar8 = piVar8 + 1;
              } while (iVar20 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
            }
          }
        }
        local_610 = (int *)((int)local_610 + 1);
        piVar12 = piVar12 + 1;
        local_5e0 = local_5e0 + -1;
      } while (local_5e0 != 0);
      if (DAT_00451160 == 2) {
        DAT_0044d020 = 0x1c;
      }
      else if (DAT_00451160 == 3) {
        DAT_0044d020 = 0x80;
      }
      else {
        DAT_0044d020 = (-(uint)(DAT_00451160 != 4) & 0xffffff38) + 0xca;
      }
      DAT_00450bdc = 0;
      FUN_00431c70();
      if ((DAT_00450b88 != 0) && (DAT_0044d020 != 10)) {
        DAT_00451160 = 6;
        if (DAT_004588ac != 0) {
          FUN_0043df00();
          DAT_00458428 = *(int *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3f8 + DAT_004588ac);
          DAT_0045842c = *(undefined4 *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3fc + DAT_004588ac);
        }
        DAT_00450b88 = 0;
        DAT_00450b84 = 0;
        DAT_0044d020 = 10;
      }
      goto LAB_00422a95;
    }
    if (DAT_0044d020 == 0) {
      if (0x8f < DAT_00450bdc) {
        piVar12 = (int *)(in_ECX + 0x198);
        local_610 = (int *)0x2;
        iVar15 = DAT_00450b94;
        iVar20 = DAT_00450c2c;
        iVar16 = DAT_00450ba8;
        do {
          if ((*(char *)(piVar12[-1] + 0xd1) == '\x01') || (*(char *)(piVar12[-1] + 0xd2) == '\x01')
             ) {
            if (iVar20 == 0) {
              if (DAT_00451160 == 1) {
                if (iVar16 != 1) goto LAB_0041e199;
                iVar16 = 3;
                DAT_00450ba8 = 3;
                goto LAB_0041e1d0;
              }
            }
            else if (DAT_00451160 == 1) {
LAB_0041e199:
              if ((iVar16 != 2) && (iVar16 != 0)) goto LAB_0041e1d0;
            }
            iVar15 = (iVar15 / 10) * 10;
            iVar20 = 0;
            DAT_00450bdc = 0x15e;
            DAT_00450c2c = 0;
            DAT_00450b94 = iVar15;
          }
LAB_0041e1d0:
          if ((*(char *)(*piVar12 + 0xd1) == '\x01') || (*(char *)(*piVar12 + 0xd2) == '\x01')) {
            if (iVar20 == 0) {
              if (DAT_00451160 == 1) {
                if (iVar16 != 1) goto LAB_0041e20c;
                iVar16 = 3;
                DAT_00450ba8 = 3;
                goto LAB_0041e243;
              }
            }
            else if (DAT_00451160 == 1) {
LAB_0041e20c:
              if ((iVar16 != 2) && (iVar16 != 0)) goto LAB_0041e243;
            }
            iVar15 = (iVar15 / 10) * 10;
            iVar20 = 0;
            DAT_00450bdc = 0x15e;
            DAT_00450c2c = 0;
            DAT_00450b94 = iVar15;
          }
LAB_0041e243:
          if ((*(char *)(piVar12[1] + 0xd1) == '\x01') || (*(char *)(piVar12[1] + 0xd2) == '\x01'))
          {
            if (iVar20 == 0) {
              if (DAT_00451160 == 1) {
                if (iVar16 != 1) goto LAB_0041e280;
                iVar16 = 3;
                DAT_00450ba8 = 3;
                goto LAB_0041e2b7;
              }
            }
            else if (DAT_00451160 == 1) {
LAB_0041e280:
              if ((iVar16 != 2) && (iVar16 != 0)) goto LAB_0041e2b7;
            }
            iVar15 = (iVar15 / 10) * 10;
            iVar20 = 0;
            DAT_00450bdc = 0x15e;
            DAT_00450c2c = 0;
            DAT_00450b94 = iVar15;
          }
LAB_0041e2b7:
          if ((*(char *)(piVar12[2] + 0xd1) == '\x01') || (*(char *)(piVar12[2] + 0xd2) == '\x01'))
          {
            if (iVar20 == 0) {
              if (DAT_00451160 == 1) {
                if (iVar16 != 1) goto LAB_0041e2f4;
                iVar16 = 3;
                DAT_00450ba8 = 3;
                goto LAB_0041e32b;
              }
            }
            else if (DAT_00451160 == 1) {
LAB_0041e2f4:
              if ((iVar16 != 2) && (iVar16 != 0)) goto LAB_0041e32b;
            }
            iVar15 = (iVar15 / 10) * 10;
            iVar20 = 0;
            DAT_00450bdc = 0x15e;
            DAT_00450c2c = 0;
            DAT_00450b94 = iVar15;
          }
LAB_0041e32b:
          piVar12 = piVar12 + 4;
          local_610 = (int *)((int)local_610 + -1);
        } while (local_610 != (int *)0x0);
      }
      local_608 = (char *)0x0;
      piVar12 = (int *)(in_ECX + 0x194);
      do {
        if ((in_ECX + 4)[(int)local_608] != '\0') {
          FUN_00413080();
          if ((*(int *)(*(int *)(*piVar12 + 0x70) * 0x178 + 0x7ac + *(int *)(*piVar12 + 0x368)) ==
               400) && (DAT_00450bd8 == 0)) {
            FUN_00403270();
          }
          if ((*(int *)(*(int *)(*piVar12 + 0x70) * 0x178 + 0x7ac + *(int *)(*piVar12 + 0x368)) ==
               0x191) && (DAT_00450bd8 == 0)) {
            FUN_00403270();
          }
          iVar15 = *piVar12;
          if ((*(int *)(*(int *)(iVar15 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar15 + 0x368)) == 500)
             && ((*(int *)(iVar15 + 0x33c) == -1 || (-1 < *(int *)(iVar15 + 0x324))))) {
            *(undefined4 *)(iVar15 + 0x70) = 0;
          }
          iVar15 = *piVar12;
          if ((*(int *)(*(int *)(iVar15 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar15 + 0x368)) == 0x1f5
              ) && (-1 < *(int *)(iVar15 + 0x33c))) {
            piVar8 = *(int **)(in_ECX + 0x7d4);
            iVar20 = 0;
            if (0 < piVar8[0x13608e0]) {
LAB_0041e443:
              if (*(int *)(*piVar8 + 0x6f4) != *(int *)(iVar15 + 0x33c)) goto code_r0x0041e44d;
              *(undefined4 *)(*piVar12 + 0x324) =
                   *(undefined4 *)(*(int *)(*piVar12 + 0x368) + 0x6f4);
              *(undefined4 *)(*piVar12 + 0x368) =
                   *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar20 * 4);
              *(undefined4 *)(*piVar12 + 0x70) = 0;
              piVar8 = (int *)(in_ECX + 0x198);
              local_610 = (int *)0x50;
              pcVar21 = in_ECX;
              do {
                if (((pcVar21[4] != '\0') && (*(char **)(piVar8[-1] + 0x2f4) == local_608)) &&
                   (0 < *(int *)(piVar8[-1] + 0x2fc))) {
                  *(undefined4 *)(piVar8[-1] + 0x368) = *(undefined4 *)(*piVar12 + 0x368);
                  iVar15 = piVar8[-1];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((pcVar21[5] != '\0') && (*(char **)(*piVar8 + 0x2f4) == local_608)) &&
                   (0 < *(int *)(*piVar8 + 0x2fc))) {
                  *(undefined4 *)(*piVar8 + 0x368) = *(undefined4 *)(*piVar12 + 0x368);
                  iVar15 = *piVar8;
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((pcVar21[6] != '\0') && (*(char **)(piVar8[1] + 0x2f4) == local_608)) &&
                   (0 < *(int *)(piVar8[1] + 0x2fc))) {
                  *(undefined4 *)(piVar8[1] + 0x368) = *(undefined4 *)(*piVar12 + 0x368);
                  iVar15 = piVar8[1];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((pcVar21[7] != '\0') && (*(char **)(piVar8[2] + 0x2f4) == local_608)) &&
                   (0 < *(int *)(piVar8[2] + 0x2fc))) {
                  *(undefined4 *)(piVar8[2] + 0x368) = *(undefined4 *)(*piVar12 + 0x368);
                  iVar15 = piVar8[2];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((pcVar21[8] != '\0') && (*(char **)(piVar8[3] + 0x2f4) == local_608)) &&
                   (0 < *(int *)(piVar8[3] + 0x2fc))) {
                  *(undefined4 *)(piVar8[3] + 0x368) = *(undefined4 *)(*piVar12 + 0x368);
                  iVar15 = piVar8[3];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                piVar8 = piVar8 + 5;
                local_610 = (int *)((int)local_610 + -1);
                pcVar21 = pcVar21 + 5;
              } while (local_610 != (int *)0x0);
            }
          }
        }
LAB_0041e61a:
        local_608 = local_608 + 1;
        piVar12 = piVar12 + 1;
      } while ((int)local_608 < 400);
      pcVar21 = (char *)0x0;
      do {
        if ((in_ECX + 4)[(int)pcVar21] != '\0') {
          FUN_0040e490();
          if (*(int *)(*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) * 0x178 + 0x7ac
                      + *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x368)) == 0x270e) {
            (in_ECX + 4)[(int)pcVar21] = '\0';
          }
          iVar15 = *(int *)(in_ECX + (int)pcVar21 * 4 + 0x194);
          if (((((*(int *)(*(int *)(iVar15 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar15 + 0x368)) ==
                  0xe) && (*(int *)(iVar15 + 0x2fc) < 1)) &&
               ((-1 < *(int *)(iVar15 + 0x2f4) ||
                ((*(int *)(iVar15 + 0x364) == 5 || (0x13 < (int)pcVar21)))))) &&
              (0 < *(int *)(iVar15 + 8))) && (*(int *)(iVar15 + 8) < 5)) {
            if (*(int *)(iVar15 + 0x314) < 1) {
              if (*(int *)(iVar15 + 0x30c) < 2) {
                (in_ECX + 4)[(int)pcVar21] = '\0';
              }
              else {
                *(int *)(iVar15 + 0x30c) = *(int *)(iVar15 + 0x30c) + -1;
                local_610 = (int *)(-4 - (int)in_ECX);
                local_5f8 = -3 - (int)in_ECX;
                local_5f0 = (char *)(-2 - (int)in_ECX);
                local_5e4 = -1 - (int)in_ECX;
                iVar15 = 0;
                local_608 = in_ECX + 5;
                local_5ec = (char *)(-5 - (int)in_ECX);
                local_604 = (int *)0x0;
                local_60c = (char *)0x0;
                piVar12 = (int *)(in_ECX + 0x198);
                do {
                  if ((((local_608[-1] == '\x01') && (pcVar21 != local_5ec + (int)local_608)) &&
                      (*(int *)(*(int *)(piVar12[-1] + 0x368) + 0x6f8) == 0)) &&
                     (*(int *)(piVar12[-1] + 0x364) ==
                      *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364))) {
                    iVar15 = iVar15 + *(int *)(piVar12[-1] + 0x10);
                    local_60c = local_60c + *(int *)(piVar12[-1] + 0x18);
                    local_604 = (int *)((int)local_604 + 1);
                  }
                  if (((*local_608 == '\x01') &&
                      (pcVar21 != (char *)((int)local_610 + (int)local_608))) &&
                     ((*(int *)(*(int *)(*piVar12 + 0x368) + 0x6f8) == 0 &&
                      (*(int *)(*piVar12 + 0x364) ==
                       *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364))))) {
                    iVar15 = iVar15 + *(int *)(*piVar12 + 0x10);
                    local_60c = local_60c + *(int *)(*piVar12 + 0x18);
                    local_604 = (int *)((int)local_604 + 1);
                  }
                  if (((local_608[1] == '\x01') && (pcVar21 != local_608 + local_5f8)) &&
                     ((*(int *)(*(int *)(piVar12[1] + 0x368) + 0x6f8) == 0 &&
                      (*(int *)(piVar12[1] + 0x364) ==
                       *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364))))) {
                    iVar15 = iVar15 + *(int *)(piVar12[1] + 0x10);
                    local_60c = local_60c + *(int *)(piVar12[1] + 0x18);
                    local_604 = (int *)((int)local_604 + 1);
                  }
                  if ((((local_608[2] == '\x01') && (pcVar21 != local_5f0 + (int)local_608)) &&
                      (*(int *)(*(int *)(piVar12[2] + 0x368) + 0x6f8) == 0)) &&
                     (*(int *)(piVar12[2] + 0x364) ==
                      *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364))) {
                    iVar15 = iVar15 + *(int *)(piVar12[2] + 0x10);
                    local_60c = local_60c + *(int *)(piVar12[2] + 0x18);
                    local_604 = (int *)((int)local_604 + 1);
                  }
                  if (((local_608[3] == '\x01') && (pcVar21 != local_608 + local_5e4)) &&
                     ((*(int *)(*(int *)(piVar12[3] + 0x368) + 0x6f8) == 0 &&
                      (*(int *)(piVar12[3] + 0x364) ==
                       *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364))))) {
                    iVar15 = iVar15 + *(int *)(piVar12[3] + 0x10);
                    local_60c = local_60c + *(int *)(piVar12[3] + 0x18);
                    local_604 = (int *)((int)local_604 + 1);
                  }
                  local_608 = local_608 + 5;
                  piVar12 = piVar12 + 5;
                } while ((int)(local_5ec + (int)local_608) < 400);
                iVar20 = FUN_00417170();
                piVar12 = local_604;
                local_600 = (char *)(iVar15 / (int)local_604);
                *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x58) =
                     ((double)(int)local_600 + (double)iVar20) - 26.0;
                iVar15 = FUN_00417170();
                local_600 = (char *)((int)local_60c / (int)piVar12);
                *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x68) =
                     ((double)(int)local_600 + (double)iVar15) - 16.0;
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x308) = 500;
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x300) =
                     *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x304);
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x2fc) =
                     *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x300);
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 8) = 0x14;
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0xd4;
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14) = 0xfffffed4;
                *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x60) =
                     (double)*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14);
                *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x48) = 0;
              }
            }
            else {
              *(undefined4 *)(iVar15 + 0x30c) = *(undefined4 *)(iVar15 + 0x310);
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x308) = 0;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x304) =
                   *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x314);
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x300) =
                   *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x304);
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x2fc) =
                   *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x300);
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x314) = 0;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x310) = 0;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364) = 1;
              iVar15 = *(int *)(*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x368) +
                               0x6f4);
              if ((((iVar15 == 0x24) || (iVar15 == 0x23)) ||
                  ((iVar15 == 0x22 || (((iVar15 == 0x21 || (iVar15 == 0x20)) || (iVar15 == 0x1f)))))
                  ) || (iVar15 == 0x1e)) {
                *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x318) = 0x8c;
              }
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0xdb;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x88) = 0;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0xb4) = 10;
              iVar15 = -1;
              iVar20 = 0x32;
              do {
                if (in_ECX[iVar20 + 4] == '\0') {
                  iVar15 = iVar20;
                  break;
                }
                iVar20 = iVar20 + 1;
              } while (iVar20 < 400);
              if (iVar15 != -1) {
                piVar12 = *(int **)(in_ECX + 0x7d4);
                iVar20 = 0;
                if (0 < piVar12[0x13608e0]) {
                  do {
                    if (*(int *)(*piVar12 + 0x6f4) == 0x3e6) {
                      if (iVar20 != -1) {
                        local_600 = *(char **)(*(int *)(in_ECX + 0x7d4) + iVar20 * 4);
                        local_5e8 = *(char **)(in_ECX + iVar15 * 4 + 0x194);
                        FUN_004061d0();
                        *(char **)(local_5e8 + 0x368) = local_600;
                        uVar4 = *(undefined4 *)(local_600 + 0x90);
                        local_5e8[0x58] = '\0';
                        local_5e8[0x59] = '\0';
                        local_5e8[0x5a] = '\0';
                        local_5e8[0x5b] = '\0';
                        local_5e8[0x5c] = '\0';
                        local_5e8[0x5d] = ' ';
                        local_5e8[0x5e] = -0x7e;
                        local_5e8[0x5f] = '@';
                        *(undefined4 *)(local_5e8 + 0x31c) = uVar4;
                        local_5e8[0x60] = '\0';
                        local_5e8[0x61] = '\0';
                        local_5e8[0x62] = '\0';
                        local_5e8[99] = '\0';
                        local_5e8[100] = '\0';
                        local_5e8[0x65] = '\0';
                        local_5e8[0x66] = 'i';
                        local_5e8[0x67] = -0x40;
                        local_5e8[0x68] = '\0';
                        local_5e8[0x69] = '\0';
                        local_5e8[0x6a] = '\0';
                        local_5e8[0x6b] = '\0';
                        local_5e8[0x6c] = '\0';
                        local_5e8[0x6d] = -0x40;
                        local_5e8[0x6e] = 'r';
                        local_5e8[0x6f] = '@';
                        *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10) =
                             *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x10);
                        *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14) =
                             *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14);
                        *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18) =
                             *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x18) + 1;
                        *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x364) =
                             *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x364);
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x58) =
                             *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x58);
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x60) =
                             *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x60);
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x68) =
                             *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x68);
                        *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) = 6;
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x40) = 0;
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x48) = 0;
                        *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x50) = 0;
                        *(undefined1 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x80) = 0;
                        in_ECX[iVar15 + 4] = '\x01';
                      }
                      break;
                    }
                    iVar20 = iVar20 + 1;
                    piVar12 = piVar12 + 1;
                  } while (iVar20 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
                }
              }
            }
          }
          iVar15 = *(int *)(in_ECX + (int)pcVar21 * 4 + 0x194);
          if (((-1 < *(int *)(iVar15 + 0x324)) && (*(char *)(iVar15 + 0xdc) == '\x03')) &&
             ((*(int *)(iVar15 + 0x14) == 0 && (0 < *(int *)(iVar15 + 0x2fc))))) {
            *(undefined1 *)(iVar15 + 0xdc) = 0;
            piVar12 = *(int **)(in_ECX + 0x7d4);
            local_610 = (int *)0x0;
            if (0 < piVar12[0x13608e0]) {
              local_600 = *(char **)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x324);
              piVar8 = piVar12;
LAB_0041ecd3:
              piVar17 = local_610;
              if (*(char **)(*piVar8 + 0x6f4) != local_600) goto code_r0x0041ece5;
              *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x368) =
                   piVar12[(int)local_610];
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0xf5;
              local_60c = in_ECX + 5;
              *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x324) = 0xffffffff;
              piVar12 = (int *)(in_ECX + 0x198);
              local_610 = (int *)0x50;
              do {
                if (((local_60c[-1] != '\0') && (*(char **)(piVar12[-1] + 0x2f4) == pcVar21)) &&
                   (0 < *(int *)(piVar12[-1] + 0x2fc))) {
                  *(undefined4 *)(piVar12[-1] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + (int)piVar17 * 4);
                  iVar15 = piVar12[-1];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((*local_60c != '\0') && (*(char **)(*piVar12 + 0x2f4) == pcVar21)) &&
                   (0 < *(int *)(*piVar12 + 0x2fc))) {
                  *(undefined4 *)(*piVar12 + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + (int)piVar17 * 4);
                  iVar15 = *piVar12;
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((local_60c[1] != '\0') && (*(char **)(piVar12[1] + 0x2f4) == pcVar21)) &&
                   (0 < *(int *)(piVar12[1] + 0x2fc))) {
                  *(undefined4 *)(piVar12[1] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + (int)piVar17 * 4);
                  iVar15 = piVar12[1];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((local_60c[2] != '\0') && (*(char **)(piVar12[2] + 0x2f4) == pcVar21)) &&
                   (0 < *(int *)(piVar12[2] + 0x2fc))) {
                  *(undefined4 *)(piVar12[2] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + (int)piVar17 * 4);
                  iVar15 = piVar12[2];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                if (((local_60c[3] != '\0') && (*(char **)(piVar12[3] + 0x2f4) == pcVar21)) &&
                   (0 < *(int *)(piVar12[3] + 0x2fc))) {
                  *(undefined4 *)(piVar12[3] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + (int)piVar17 * 4);
                  iVar15 = piVar12[3];
                  if (*(int *)(iVar15 + 0x14) < 0) {
                    *(undefined4 *)(iVar15 + 0x70) = 0xd4;
                  }
                  else {
                    *(undefined4 *)(iVar15 + 0x70) = 0;
                  }
                }
                local_60c = local_60c + 5;
                piVar12 = piVar12 + 5;
                local_610 = (int *)((int)local_610 + -1);
              } while (local_610 != (int *)0x0);
            }
          }
        }
LAB_0041eec2:
        pcVar21 = pcVar21 + 1;
      } while ((int)pcVar21 < 400);
      FUN_00417f80();
      if (DAT_0044d05c == 2) {
        DAT_0044d05c = 0;
      }
      else {
        FUN_00419380(DAT_00451160);
      }
      iVar15 = 0;
      piVar12 = (int *)(in_ECX + 0x194);
      DAT_0045115c = 0;
      do {
        if (in_ECX[iVar15 + 4] != '\0') {
          iVar20 = *(int *)(*(int *)(*piVar12 + 0x368) + 0x6f8);
          if (((iVar20 == 1) || (iVar20 == 2)) || ((iVar20 == 4 || (iVar20 == 6)))) {
            DAT_0045115c = DAT_0045115c + 1;
          }
          if (iVar20 == 0) {
            FUN_0042e100(iVar15);
          }
        }
        iVar15 = iVar15 + 1;
        piVar12 = piVar12 + 1;
      } while (iVar15 < 400);
      if (DAT_0045115c < 4) {
        iVar20 = FUN_00417170();
        iVar15 = DAT_00451160;
        if (iVar20 == 0) {
          iVar20 = 0x32;
          do {
            if (in_ECX[iVar20 + 4] == '\0') {
              local_5f8 = iVar20;
              break;
            }
            iVar20 = iVar20 + 1;
          } while (iVar20 < 400);
          iVar20 = 0;
          local_610 = (int *)0x0;
          if (0 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380)) {
            do {
              iVar16 = *(int *)(*(int *)(*(int *)(in_ECX + 0x7d4) + iVar20 * 4) + 0x6f4);
              if (((99 < iVar16) && (iVar16 < 200)) &&
                 (((iVar16 != 0x7a && (iVar16 != 0x7b)) ||
                  ((((iVar16 = FUN_00417170(), iVar16 != 0 && (iVar15 != 2)) && (iVar15 != 3)) &&
                   ((iVar15 != 1 && (iVar15 != 4)))))))) {
                local_5d0[(int)(local_610 + 10)] = iVar20;
                local_610 = (int *)((int)local_610 + 1);
              }
              iVar20 = iVar20 + 1;
            } while (iVar20 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
          }
          iVar15 = DAT_0044d024;
          if (DAT_00450bb4 == 0) {
            iVar16 = FUN_00417170();
            iVar20 = *(int *)(iVar15 * 0x990 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4));
          }
          else {
            iVar16 = FUN_00417170();
            iVar20 = DAT_00450bb4;
          }
          iVar9 = FUN_00417170();
          iVar15 = iVar15 * 0x990;
          local_5f0 = (char *)(iVar9 + 0x1e + iVar16 * ((iVar20 + -0x3c) / 0x1e));
          local_600 = (char *)(*(int *)(in_ECX + 0x7d4) + iVar15);
          uVar25 = 0x1e;
          uVar4 = 0x98;
          iVar9 = FUN_00417170();
          iVar20 = *(int *)(local_600 + 0x4d45db8);
          iVar16 = *(int *)(local_600 + 0x4d45db4);
          uVar23 = CONCAT44(uVar4,0x1e);
          uVar4 = 0x99;
          iVar10 = FUN_00417170();
          local_600 = (char *)(iVar10 + *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d45db4 + iVar15) +
                               0x1e + iVar9 * (((iVar20 - iVar16) + -0x3c) / 0x1e));
          iVar20 = FUN_00417170(0x9a,local_610,uVar4,uVar23,uVar25);
          iVar15 = *(int *)(in_ECX + local_5f8 * 4 + 0x194);
          iVar20 = *(int *)(*(int *)(in_ECX + 0x7d4) + local_5d0[iVar20 + 0x28] * 4);
          FUN_004061d0();
          iVar16 = local_5f8;
          *(int *)(iVar15 + 0x368) = iVar20;
          uVar4 = *(undefined4 *)(iVar20 + 0x90);
          *(double *)(iVar15 + 0x58) = (double)(int)local_5f0;
          *(undefined8 *)(iVar15 + 0x60) = 0xc07f400000000000;
          *(undefined4 *)(iVar15 + 0x31c) = uVar4;
          piVar12 = (int *)(in_ECX + 0x198);
          *(double *)(iVar15 + 0x68) = (double)(int)local_600;
          in_ECX[local_5f8 + 4] = '\x01';
          iVar15 = 0x50;
          pcVar21 = in_ECX;
          do {
            if (pcVar21[4] != '\0') {
              *(undefined1 *)(piVar12[-1] + 0xf0 + local_5f8) = 0;
            }
            if (pcVar21[5] != '\0') {
              *(undefined1 *)(*piVar12 + 0xf0 + local_5f8) = 0;
            }
            if (pcVar21[6] != '\0') {
              *(undefined1 *)(piVar12[1] + 0xf0 + local_5f8) = 0;
            }
            if (pcVar21[7] != '\0') {
              *(undefined1 *)(piVar12[2] + 0xf0 + local_5f8) = 0;
            }
            if (pcVar21[8] != '\0') {
              *(undefined1 *)(piVar12[3] + 0xf0 + local_5f8) = 0;
            }
            piVar12 = piVar12 + 5;
            iVar15 = iVar15 + -1;
            pcVar21 = pcVar21 + 5;
          } while (iVar15 != 0);
          *(undefined8 *)(*(int *)(in_ECX + local_5f8 * 4 + 0x194) + 0x40) = 0;
          *(undefined8 *)(*(int *)(in_ECX + local_5f8 * 4 + 0x194) + 0x48) = 0;
          *(undefined8 *)(*(int *)(in_ECX + local_5f8 * 4 + 0x194) + 0x50) = 0;
          if (*(int *)(*(int *)(*(int *)(in_ECX + local_5f8 * 4 + 0x194) + 0x368) + 0x6f4) == 0x7a)
          {
            *(undefined4 *)(*(int *)(in_ECX + local_5f8 * 4 + 0x194) + 0x2fc) = 200;
          }
          iVar15 = *(int *)(in_ECX + local_5f8 * 4 + 0x194);
          uVar4 = FUN_004450d0();
          *(undefined4 *)(iVar15 + 0x10) = uVar4;
          iVar15 = *(int *)(in_ECX + iVar16 * 4 + 0x194);
          uVar4 = FUN_004450d0();
          *(undefined4 *)(iVar15 + 0x14) = uVar4;
          iVar15 = *(int *)(in_ECX + iVar16 * 4 + 0x194);
          uVar4 = FUN_004450d0();
          *(undefined4 *)(iVar15 + 0x18) = uVar4;
          *(undefined4 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x354) = 99;
        }
      }
      iVar15 = 0;
      piVar12 = (int *)(in_ECX + 0x194);
      do {
        if ((in_ECX[iVar15 + 4] != '\0') && (0 < *(int *)(*(int *)(*piVar12 + 0x368) + 0x6f8))) {
          FUN_0042e100(iVar15);
        }
        iVar15 = iVar15 + 1;
        piVar12 = piVar12 + 1;
      } while (iVar15 < 400);
      FUN_00418c30();
      FUN_004187b0();
      piVar12 = (int *)(in_ECX + 0x198);
      local_610 = (int *)(-4 - (int)in_ECX);
      local_5f8 = -3 - (int)in_ECX;
      local_5f0 = (char *)(-2 - (int)in_ECX);
      local_5e4 = -1 - (int)in_ECX;
      local_5ec = (char *)(-5 - (int)in_ECX);
      pcVar21 = in_ECX + 5;
      do {
        if (((pcVar21[-1] != '\0') && (iVar15 = piVar12[-1], 0 < *(int *)(iVar15 + 0x98))) &&
           ((iVar20 = *(int *)(iVar15 + 0x9c), iVar20 < 0 ||
            (((399 < iVar20 || (in_ECX[iVar20 + 4] == '\0')) ||
             (*(char **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) != local_5ec + (int)pcVar21))
            )))) {
          *(undefined4 *)(iVar15 + 0x98) = 0;
        }
        if (((*pcVar21 != '\0') && (iVar15 = *piVar12, 0 < *(int *)(iVar15 + 0x98))) &&
           (((iVar20 = *(int *)(iVar15 + 0x9c), iVar20 < 0 ||
             ((399 < iVar20 || (in_ECX[iVar20 + 4] == '\0')))) ||
            (*(char **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) !=
             (char *)((int)local_610 + (int)pcVar21))))) {
          *(undefined4 *)(iVar15 + 0x98) = 0;
        }
        if (((pcVar21[1] != '\0') && (iVar15 = piVar12[1], 0 < *(int *)(iVar15 + 0x98))) &&
           ((iVar20 = *(int *)(iVar15 + 0x9c), iVar20 < 0 ||
            (((399 < iVar20 || (in_ECX[iVar20 + 4] == '\0')) ||
             (*(char **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) != pcVar21 + local_5f8))))))
        {
          *(undefined4 *)(iVar15 + 0x98) = 0;
        }
        if (((pcVar21[2] != '\0') && (iVar15 = piVar12[2], 0 < *(int *)(iVar15 + 0x98))) &&
           (((iVar20 = *(int *)(iVar15 + 0x9c), iVar20 < 0 ||
             ((399 < iVar20 || (in_ECX[iVar20 + 4] == '\0')))) ||
            (*(char **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) != local_5f0 + (int)pcVar21)))
           ) {
          *(undefined4 *)(iVar15 + 0x98) = 0;
        }
        if (((pcVar21[3] != '\0') && (iVar15 = piVar12[3], 0 < *(int *)(iVar15 + 0x98))) &&
           ((iVar20 = *(int *)(iVar15 + 0x9c), iVar20 < 0 ||
            (((399 < iVar20 || (in_ECX[iVar20 + 4] == '\0')) ||
             (*(char **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) != pcVar21 + local_5e4))))))
        {
          *(undefined4 *)(iVar15 + 0x98) = 0;
        }
        pcVar21 = pcVar21 + 5;
        piVar12 = piVar12 + 5;
      } while ((int)(local_5ec + (int)pcVar21) < 400);
      FUN_00417f80();
      uVar4 = local_5dc;
      FUN_0041b5d0();
      FUN_0041a5a0(uVar4,DAT_00450bd8,DAT_00451160);
      if (DAT_00451160 == 1) {
        FUN_00437860();
      }
      if (DAT_00451160 == 4) {
        FUN_0043a860(uVar4);
      }
      iVar15 = *(int *)(in_ECX + 0x1bc);
      sprintf(acStack_1b8,"u%d d%d l%d r%d a%d d%d ",(int)*(char *)(iVar15 + 0xc4),
              (int)*(char *)(iVar15 + 0xc5),(int)*(char *)(iVar15 + 0xc3),
              (int)*(char *)(iVar15 + 0xc2),(int)*(char *)(iVar15 + 0xbe),
              (int)*(char *)(iVar15 + 0xc0));
      FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x1e);
      FUN_004196f0();
      iVar15 = 0;
LAB_0041f550:
      if (in_ECX[iVar15 + 4] != '\0') {
        iVar20 = *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368);
        if ((*(int *)(iVar20 + 0x6f8) == 0) &&
           (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) * 0x178 + 0x7ac + iVar20
                    ) == 0x270b)) {
          piVar12 = *(int **)(in_ECX + 0x7d4);
          iVar20 = 0;
          if (0 < piVar12[0x13608e0]) {
            piVar8 = piVar12;
            do {
              if (*(int *)(*piVar8 + 0x6f4) == 0x32) {
                *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) = piVar12[iVar20];
                break;
              }
              iVar20 = iVar20 + 1;
              piVar8 = piVar8 + 1;
            } while (iVar20 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
          }
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) = 0;
        }
        iVar20 = *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) * 0x178 + 0x7ac +
                         *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368));
        if ((7999 < iVar20) && (iVar20 < 9000)) {
          piVar12 = *(int **)(in_ECX + 0x7d4);
          iVar16 = 0;
          if (0 < piVar12[0x13608e0]) {
            do {
              if (*(int *)(*piVar12 + 0x6f4) == iVar20 + -8000) {
                *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) =
                     *(undefined4 *)(*(int *)(in_ECX + 0x7d4) + iVar16 * 4);
                break;
              }
              iVar16 = iVar16 + 1;
              piVar12 = piVar12 + 1;
            } while (iVar16 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
          }
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) = 0;
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x318) = 0x8c;
        }
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        if (((*(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0) &&
            (*(int *)(*(int *)(iVar20 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar20 + 0x368)) == 0x270c)
            ) && (*(int *)(iVar20 + 0x88) == 1)) {
          local_60c = (char *)0x0;
          do {
            pcVar21 = (char *)0x32;
            do {
              if ((in_ECX + 4)[(int)pcVar21] == '\0') {
                local_608 = pcVar21;
                break;
              }
              pcVar21 = pcVar21 + 1;
            } while ((int)pcVar21 < 400);
            if (pcVar21 == (char *)0x190) break;
            iVar20 = 0xd9;
            if (local_60c == (char *)0x4) {
              iVar20 = 0xda;
            }
            piVar12 = *(int **)(in_ECX + 0x7d4);
            iVar16 = 0;
            if (0 < piVar12[0x13608e0]) {
              local_610 = piVar12;
              do {
                if (*(int *)(*local_610 + 0x6f4) == iVar20) {
                  iStack_5d4 = iVar16;
                  break;
                }
                local_610 = local_610 + 1;
                iVar16 = iVar16 + 1;
              } while (iVar16 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
            }
            local_610 = (int *)piVar12[iStack_5d4];
            iVar20 = *(int *)(in_ECX + (int)local_608 * 4 + 0x194);
            FUN_004061d0();
            pcVar21 = local_608;
            *(int **)(iVar20 + 0x368) = local_610;
            uVar4 = *(undefined4 *)((int)local_610 + 0x90);
            *(undefined8 *)(iVar20 + 0x58) = 0x4082200000000000;
            *(undefined4 *)(iVar20 + 0x31c) = uVar4;
            *(undefined8 *)(iVar20 + 0x60) = 0xc069000000000000;
            uVar25 = 7;
            *(undefined8 *)(iVar20 + 0x68) = 0x4072c00000000000;
            (in_ECX + 4)[(int)local_608] = '\x01';
            uVar4 = 0x9b;
            iVar20 = FUN_00417170();
            uVar23 = CONCAT44(uVar4,7);
            *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x10) =
                 iVar20 + -3 + *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10);
            uVar4 = 0x9c;
            iVar20 = FUN_00417170();
            *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14) =
                 iVar20 + -9 + *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14);
            *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x18) =
                 *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18) + 1;
            *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x68) =
                 (double)*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x18);
            *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x60) =
                 (double)*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14);
            *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x58) =
                 (double)*(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x10);
            iVar20 = FUN_00417170(0x9d,0xf,uVar4,uVar23,uVar25);
            local_610 = (int *)-(iVar20 / 2);
            *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x48) =
                 (double)(int)local_610 - 5.0;
            *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0xec) = 6;
            if ((local_60c == (char *)0x0) || (local_60c == (char *)0x2)) {
              local_610 = (int *)FUN_00417170();
              *(double *)(*(int *)(in_ECX + (int)local_608 * 4 + 0x194) + 0x50) =
                   (double)(int)local_610 + 3.0;
              pcVar21 = local_608;
            }
            else if ((local_60c == (char *)0x1) || (local_60c == (char *)0x3)) {
              local_610 = (int *)FUN_00417170();
              *(double *)(*(int *)(in_ECX + (int)local_608 * 4 + 0x194) + 0x50) =
                   -3.0 - (double)(int)local_610;
              pcVar21 = local_608;
            }
            else {
              *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x50) =
                   0x3ff0000000000000;
            }
            if ((int)local_60c < 2) {
              local_610 = (int *)FUN_00417170();
              *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x40) =
                   -10.0 - (double)(int)local_610;
            }
            else if ((int)local_60c < 4) {
              local_610 = (int *)FUN_00417170();
              *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x40) =
                   (double)(int)local_610 + 10.0;
            }
            else {
              local_610 = (int *)FUN_00417170();
              *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x40) =
                   (double)(int)local_610 - 3.0;
            }
            uVar4 = FUN_00417170();
            *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = uVar4;
            uVar3 = FUN_00417170();
            *(undefined1 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x80) = uVar3;
            local_60c = local_60c + 1;
          } while ((int)local_60c < 5);
        }
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        if (*(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0) {
          if (((0 < *(int *)(iVar20 + 0x2fc)) &&
              (*(int *)(iVar20 + 0x2fc) < *(int *)(iVar20 + 0x300))) && (DAT_00450bd0 == 0)) {
            *(int *)(iVar20 + 0x2fc) = *(int *)(iVar20 + 0x2fc) + 1;
          }
          iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
          if ((*(int *)(iVar20 + 800) < 0) && (DAT_00450bd0 == 0)) {
            iVar16 = 9;
            if (0 < *(int *)(iVar20 + 0x340)) {
              iVar16 = (int)(900 / (longlong)*(int *)(iVar20 + 0x340));
            }
            *(int *)(iVar20 + 0x2fc) = *(int *)(iVar20 + 0x2fc) - iVar16;
            iVar16 = (int)((ulonglong)((longlong)iVar16 * 0x55555555) >> 0x20) - iVar16;
            *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x300) =
                 *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x300) +
                 ((iVar16 >> 1) - (iVar16 >> 0x1f));
            if (*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x2fc) < 0) {
              *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x2fc) = 0;
            }
            if (*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x300) < 0) {
              *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x300) = 0;
            }
            *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x34c) =
                 *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x34c) + 9;
          }
          iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
          if (((*(int *)(iVar20 + 0x2f4) == -1) || (*(int *)(iVar20 + 0x308) < 0x96)) &&
             ((*(int *)(iVar20 + 0x308) < 500 &&
              ((DAT_00450bd4 == 0 && (-1 < *(int *)(iVar20 + 8))))))) {
            iVar16 = *(int *)(iVar20 + 0x2fc);
            if (500 < iVar16) {
              iVar16 = 500;
            }
            iVar9 = *(int *)(*(int *)(iVar20 + 0x368) + 0x6f4);
            if ((iVar9 == 0x33) || (iVar9 == 0x34)) {
              iVar16 = iVar16 / 2;
            }
            *(int *)(iVar20 + 0x308) = *(int *)(iVar20 + 0x308) + (500 - iVar16) / 100 + 1;
          }
        }
        FUN_0040d960();
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        iVar16 = *(int *)(iVar20 + 0x70);
        if ((iVar16 / 100 == 0xb) || (iVar16 / 100 == 0xc)) {
          local_60c = in_ECX + 5;
          piVar12 = (int *)(in_ECX + 0x198);
          local_610 = (int *)0x50;
          do {
            if ((local_60c[-1] == '\x01') && (*(int *)(piVar12[-1] + 0x2f4) == iVar15)) {
              *(int *)(piVar12[-1] + 8) =
                   0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
            }
            if ((*local_60c == '\x01') && (*(int *)(*piVar12 + 0x2f4) == iVar15)) {
              *(int *)(*piVar12 + 8) =
                   0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
            }
            if ((local_60c[1] == '\x01') && (*(int *)(piVar12[1] + 0x2f4) == iVar15)) {
              *(int *)(piVar12[1] + 8) =
                   0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
            }
            if ((local_60c[2] == '\x01') && (*(int *)(piVar12[2] + 0x2f4) == iVar15)) {
              *(int *)(piVar12[2] + 8) =
                   0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
            }
            if ((local_60c[3] == '\x01') && (*(int *)(piVar12[3] + 0x2f4) == iVar15)) {
              *(int *)(piVar12[3] + 8) =
                   0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
            }
            local_60c = local_60c + 5;
            piVar12 = piVar12 + 5;
            local_610 = (int *)((int)local_610 + -1);
          } while (local_610 != (int *)0x0);
          *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 8) =
               0x44c - *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70) = 0;
          local_610 = (int *)0x0;
          goto LAB_004214c6;
        }
        if ((iVar16 < 0) || (399 < iVar16)) {
          *(undefined4 *)(iVar20 + 0x70) = 0;
          in_ECX[iVar15 + 4] = '\0';
          goto LAB_004214c6;
        }
        if (((*(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0) && (*(int *)(iVar20 + 0x2fc) < 1)) &&
           ((iVar16 < 0xc || ((iVar16 == 0x6e || (iVar16 == 0x6f)))))) {
          *(undefined4 *)(iVar20 + 0x70) = 0xba;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x48) = 0xc008000000000000;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x30) = 0xc008000000000000;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x60) = 0xbff0000000000000;
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14) = 0xffffffff;
        }
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        if (((((*(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0) && (*(int *)(iVar20 + 0x14) == 0))
             && (*(double *)(iVar20 + 0x60) == 0.0)) &&
            ((*(double *)(iVar20 + 0x48) == 0.0 && (*(double *)(iVar20 + 0x30) == 0.0)))) &&
           (((iVar16 = *(int *)(iVar20 + 0x70), 0xb3 < iVar16 &&
             ((iVar16 < 0xbe && (iVar16 != 0xb8)))) || ((0xd3 < iVar16 && (iVar16 < 0xd7)))))) {
          *(undefined4 *)(iVar20 + 0x70) = 0xba;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x48) = 0xc008000000000000;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x30) = 0xc008000000000000;
          *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x60) = 0xbff0000000000000;
          *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14) = 0xffffffff;
        }
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        iVar16 = *(int *)(iVar20 + 0x368);
        local_60c = (char *)(*(int *)(iVar20 + 0x70) * 0x178 + iVar16);
        if ((((*(int *)(local_60c + 0x7fc) < 1) || (*(int *)(local_60c + 0x814) < 1)) ||
            (*(int *)(iVar20 + 0x88) != 0)) ||
           ((*(int *)(iVar20 + 0xb4) != 0 && (*(int *)(iVar16 + 0x6f8) == 0)))) {
          iVar16 = *(int *)(iVar16 + 0x6f8);
          if ((((iVar16 == 1) || ((iVar16 == 2 || (iVar16 == 4)))) || (iVar16 == 6)) &&
             (*(int *)(iVar20 + 0x31c) < 0)) {
            iVar16 = 0;
            *(undefined4 *)(iVar20 + 0x31c) = 0;
            iVar20 = *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4);
            local_604 = (int *)0x0;
            if ((iVar20 == 0x65) || (iVar20 == 0xda)) {
              iVar16 = 7;
              local_604 = (int *)0x7;
            }
            if (((iVar20 == 100) || (iVar20 == 0xd5)) || (iVar20 == 0xd9)) {
              iVar16 = 5;
              local_604 = (int *)0x5;
            }
            if (iVar20 == 0xc9) {
              iVar16 = 3;
              local_604 = (int *)0x3;
            }
            if (iVar20 == 0x96) {
              iVar16 = 0xd;
              local_604 = (int *)0xd;
            }
            if (iVar20 == 0x97) {
              iVar16 = 0xf;
              local_604 = (int *)0xf;
            }
            if ((iVar20 == 0x78) || (iVar20 == 0x7c)) {
              iVar16 = 3;
              local_604 = (int *)0x3;
            }
            if (iVar20 == 0x79) {
              iVar16 = 4;
              local_604 = (int *)0x4;
            }
            if ((iVar20 == 0x7a) || (iVar20 == 0x7b)) {
              iVar16 = 9;
              local_604 = (int *)0x9;
            }
            if (-1 < *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0xac)) {
              FUN_00416fb0();
            }
            local_60c = (char *)0x0;
            if (iVar16 != 0) {
              iVar20 = local_5e4;
              do {
                iVar16 = 0x32;
                do {
                  if (in_ECX[iVar16 + 4] == '\0') {
                    iVar20 = iVar16;
                    break;
                  }
                  iVar16 = iVar16 + 1;
                } while (iVar16 < 400);
                if (iVar16 == 400) break;
                piVar12 = *(int **)(in_ECX + 0x7d4);
                iVar16 = 0;
                if (0 < piVar12[0x13608e0]) {
                  local_610 = piVar12;
                  do {
                    if (*(int *)(*local_610 + 0x6f4) == 999) {
                      iStack_5d8 = iVar16;
                      break;
                    }
                    local_610 = local_610 + 1;
                    iVar16 = iVar16 + 1;
                  } while (iVar16 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
                }
                iStack_5fc = piVar12[iStack_5d8];
                local_610 = *(int **)(in_ECX + iVar20 * 4 + 0x194);
                FUN_004061d0();
                local_610[0xda] = iStack_5fc;
                iVar16 = *(int *)(iStack_5fc + 0x90);
                local_610[0x16] = 0;
                local_610[0x17] = 0x40822000;
                local_610[0x18] = 0;
                local_610[0x19] = -0x3f970000;
                local_610[199] = iVar16;
                local_610[0x1a] = 0;
                local_610[0x1b] = 0x4072c000;
                in_ECX[iVar20 + 4] = '\x01';
                iVar16 = FUN_00417170();
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10) =
                     iVar16 + -3 + *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10);
                iVar16 = FUN_00417170();
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14) =
                     iVar16 + -3 + *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14);
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x18) =
                     *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18);
                *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x68) =
                     (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x18);
                *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x60) =
                     (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14);
                *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x58) =
                     (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10);
                iVar16 = *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4);
                if (((iVar16 == 0x96) || (iVar16 == 0x97)) || (iVar16 == 0xd5)) {
                  iVar16 = FUN_00417170();
                  iStack_5fc = -(iVar16 / 2);
                  *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x48) =
                       (double)iStack_5fc - 8.0;
                }
                iVar16 = *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4);
                if (((((iVar16 == 100) || (iVar16 == 0xc9)) ||
                     ((iVar16 == 0x65 || ((iVar16 == 0x78 || (iVar16 == 0x79)))))) ||
                    (iVar16 == 0x7a)) ||
                   ((((iVar16 == 0x7b || (iVar16 == 0x7c)) || (iVar16 == 0xd9)) || (iVar16 == 0xda))
                   )) {
                  iVar16 = FUN_00417170();
                  iStack_5fc = -(iVar16 / 2);
                  *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x48) =
                       (double)iStack_5fc - 6.0;
                }
                iStack_5fc = FUN_00417170();
                *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x40) = (double)iStack_5fc - 5.0
                ;
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x96) {
                  if ((int)local_60c < 5) {
                    uVar4 = FUN_00417170();
                    *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = uVar4;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 4;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) == 100
                   ) {
                  if ((int)local_60c < 2) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 10;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0xe;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0xd5) {
                  if ((int)local_60c < 2) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x96;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x9a;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x65) {
                  if ((int)local_60c < 5) {
                    iVar16 = FUN_00417170();
                    iStack_5fc = iVar16 * 4 + 0x14;
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + iStack_5fc;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x1e;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x97) {
                  if ((int)local_60c < 2) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x28;
                  }
                  else {
                    if ((int)local_60c < 5) {
                      iVar16 = FUN_00417170();
                      iVar16 = iVar16 + 0x2c;
                    }
                    else {
                      if ((int)local_60c < 8) {
                        iVar16 = FUN_00417170();
                        *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x32;
                        goto LAB_00420901;
                      }
                      iVar16 = FUN_00417170();
                      iVar16 = iVar16 + 0x36;
                    }
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16;
                  }
                }
LAB_00420901:
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x78) {
                  if ((int)local_60c < 2) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x36;
                  }
                  else if ((int)local_60c < 5) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x1e;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x7c) {
                  iVar16 = FUN_00417170();
                  *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0xaa;
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x79) {
                  iVar16 = FUN_00417170();
                  *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x3c;
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x7a) {
                  if ((int)local_60c < 1) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x46;
                  }
                  else if ((int)local_60c < 3) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x50;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x4a;
                    iVar16 = FUN_00417170();
                    iStack_5fc = -(iVar16 / 2);
                    *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x48) =
                         (double)iStack_5fc - 4.0;
                  }
                }
                if (*(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4) ==
                    0x7b) {
                  if ((int)local_60c < 1) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0xa0;
                  }
                  else if ((int)local_60c < 3) {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0xa4;
                  }
                  else {
                    iVar16 = FUN_00417170();
                    *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0x4a;
                    iVar16 = FUN_00417170();
                    iStack_5fc = -(iVar16 / 2);
                    *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x48) =
                         (double)iStack_5fc - 4.0;
                  }
                }
                iVar16 = *(int *)(*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x368) + 0x6f4);
                if ((iVar16 == 0xd9) || (iVar16 == 0xda)) {
                  iVar16 = FUN_00417170();
                  *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) = iVar16 + 0xae;
                }
                local_60c = local_60c + 1;
              } while ((int)local_60c < (int)local_604);
              local_5e4 = iVar20;
            }
            in_ECX[iVar15 + 4] = '\0';
          }
          else if (((iVar15 < 10) && (0 < *(int *)(iVar20 + 0x2fc))) && (iVar16 == 0)) {
            iVar16 = 0;
            local_60c = (char *)0x0;
            if (*(int *)(iVar20 + 0x40c) == 9) {
              if (((*(int *)(iVar20 + 0x410) == 0) && (*(int *)(iVar20 + 0x414) == 9)) &&
                 (*(int *)(iVar20 + 0x418) == 0)) {
                iVar16 = 100;
                local_60c = (char *)0x64;
              }
              if (((*(int *)(iVar20 + 0x410) == 9) && (*(int *)(iVar20 + 0x414) == 9)) &&
                 (*(int *)(iVar20 + 0x418) == 9)) {
                iVar16 = 0x66;
                local_60c = (char *)0x66;
              }
              if (((*(int *)(iVar20 + 0x410) != 5) || (*(int *)(iVar20 + 0x414) != 9)) ||
                 (*(int *)(iVar20 + 0x418) != 5)) goto LAB_00420c20;
              local_60c = (char *)0x68;
            }
            else {
LAB_00420c20:
              if (iVar16 == 0) goto LAB_00420e93;
            }
            iVar16 = -1;
            *(undefined4 *)(iVar20 + 0x418) = 0;
            *(undefined4 *)(iVar20 + 0x414) = 0;
            *(undefined4 *)(iVar20 + 0x410) = 0;
            *(undefined4 *)(iVar20 + 0x40c) = 0;
            *(undefined4 *)(iVar20 + 0x408) = 0;
            iStack_5fc = -1;
            iVar20 = 0x32;
            do {
              if (in_ECX[iVar20 + 4] == '\0') {
                iVar16 = iVar20;
                break;
              }
              iVar20 = iVar20 + 1;
            } while (iVar20 < 400);
            piVar12 = *(int **)(in_ECX + 0x7d4);
            iVar9 = 0;
            iVar20 = -1;
            if (0 < piVar12[0x13608e0]) {
              local_610 = piVar12;
              do {
                if (*(int *)(*local_610 + 0x6f4) == 0x3e6) {
                  iVar20 = iVar9;
                  goto LAB_00420caf;
                }
                local_610 = local_610 + 1;
                iVar9 = iVar9 + 1;
              } while (iVar9 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
              iVar20 = -1;
            }
LAB_00420caf:
            if ((iVar16 != -1) && (iVar20 != -1)) {
              iStack_5fc = piVar12[iVar20];
              local_610 = *(int **)(in_ECX + iVar16 * 4 + 0x194);
              FUN_004061d0();
              *(int *)((int)local_610 + 0x368) = iStack_5fc;
              uVar4 = *(undefined4 *)(iStack_5fc + 0x90);
              *(undefined8 *)((int)local_610 + 0x58) = 0x4082200000000000;
              *(undefined4 *)((int)local_610 + 0x31c) = uVar4;
              *(undefined8 *)((int)local_610 + 0x60) = 0xc069000000000000;
              *(undefined8 *)((int)local_610 + 0x68) = 0x4072c00000000000;
              in_ECX[iVar16 + 4] = '\x01';
              *(undefined4 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x10) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10);
              *(undefined4 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x14) = 0;
              *(undefined4 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x18) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18);
              *(char **)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x70) = local_60c + -100;
              local_610 = (int *)0x0;
              *(double *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x68) =
                   (double)*(int *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x18);
              *(double *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x60) =
                   (double)*(int *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x14);
              *(double *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x58) =
                   (double)*(int *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x10);
              *(undefined8 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x40) = 0;
              *(undefined8 *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x48) = 0;
              local_604 = (int *)(in_ECX + 0x194);
              do {
                if ((((*(char *)((int)(local_610 + 1) + (int)in_ECX) == '\x01') &&
                     (iVar20 = *local_604, 0 < *(int *)(iVar20 + 0x2fc))) &&
                    (*(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
                   (*(int *)(iVar20 + 0x364) ==
                    *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x364))) {
                  if (local_60c == (char *)0x64) {
                    iVar20 = FUN_00417170();
                    *(int *)(*local_604 + 0x3fc) =
                         iVar20 + -0x28 + *(int *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x10);
                    iVar20 = FUN_00417170();
                    *(int *)(*local_604 + 0x400) =
                         iVar20 + -0x28 + *(int *)(*(int *)(in_ECX + iVar16 * 4 + 0x194) + 0x18);
                  }
                  else if (local_60c == (char *)0x66) {
                    *(undefined4 *)(iVar20 + 0x404) = 1;
                  }
                  else if (local_60c == (char *)0x68) {
                    *(undefined4 *)(iVar20 + 0x404) = 0;
                  }
                }
                local_604 = local_604 + 1;
                local_610 = (int *)((int)local_610 + 1);
              } while ((int)local_610 < 400);
            }
          }
        }
        else {
          pcVar21 = *(char **)(local_60c + 0x818);
          local_5ec = (char *)0x1;
          local_5f0 = pcVar21;
          if (10 < (int)pcVar21) {
            local_5f0 = (char *)((int)pcVar21 % 10);
            local_5ec = (char *)((int)pcVar21 / 10);
          }
          local_604 = (int *)0x0;
          local_5f8 = 0;
          if (0 < (int)local_5ec) {
            do {
              iVar20 = -1;
              iStack_5fc = -1;
              iVar16 = 0x32;
              do {
                if (in_ECX[iVar16 + 4] == '\0') {
                  iVar20 = iVar16;
                  break;
                }
                iVar16 = iVar16 + 1;
              } while (iVar16 < 400);
              iVar9 = 0;
              iVar16 = -1;
              if (0 < (*(int **)(in_ECX + 0x7d4))[0x13608e0]) {
                local_610 = *(int **)(in_ECX + 0x7d4);
                do {
                  if (*(int *)(*local_610 + 0x6f4) == *(int *)(local_60c + 0x814)) {
                    iVar16 = iVar9;
                    goto LAB_0041fd5f;
                  }
                  local_610 = local_610 + 1;
                  iVar9 = iVar9 + 1;
                } while (iVar9 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
                iVar16 = -1;
              }
LAB_0041fd5f:
              if ((iVar20 == -1) || (iVar16 == -1)) break;
              local_5d0[(int)local_604] = iVar20;
              local_604 = (int *)((int)local_604 + 1);
              iStack_5fc = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar16 * 4);
              local_610 = *(int **)(in_ECX + iVar20 * 4 + 0x194);
              FUN_004061d0();
              piVar12 = local_610;
              *(int *)((int)local_610 + 0x368) = iStack_5fc;
              uVar4 = *(undefined4 *)(iStack_5fc + 0x90);
              *(undefined8 *)((int)local_610 + 0x58) = 0x4082200000000000;
              *(undefined4 *)((int)local_610 + 0x31c) = uVar4;
              *(undefined8 *)((int)local_610 + 0x60) = 0xc069000000000000;
              local_610 = (int *)0x50;
              *(undefined8 *)((int)piVar12 + 0x68) = 0x4072c00000000000;
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x354) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x354);
              piVar12 = (int *)(in_ECX + 0x198);
              pcVar21 = in_ECX;
              do {
                if (pcVar21[4] != '\0') {
                  *(undefined1 *)(piVar12[-1] + 0xf0 + iVar20) = 0;
                }
                if (pcVar21[5] != '\0') {
                  *(undefined1 *)(iVar20 + 0xf0 + *piVar12) = 0;
                }
                if (pcVar21[6] != '\0') {
                  *(undefined1 *)(piVar12[1] + 0xf0 + iVar20) = 0;
                }
                if (pcVar21[7] != '\0') {
                  *(undefined1 *)(piVar12[2] + 0xf0 + iVar20) = 0;
                }
                if (pcVar21[8] != '\0') {
                  *(undefined1 *)(piVar12[3] + 0xf0 + iVar20) = 0;
                }
                piVar12 = piVar12 + 5;
                local_610 = (int *)((int)local_610 + -1);
                pcVar21 = pcVar21 + 5;
              } while (local_610 != (int *)0x0);
              in_ECX[iVar20 + 4] = '\x01';
              iVar16 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
              iStack_5fc = *(int *)(iVar16 + 0x368) + *(int *)(iVar16 + 0x70) * 0x178;
              iVar9 = *(int *)(iVar16 + 0x14) - *(int *)(iStack_5fc + 0x7f8);
              if (*(char *)(iVar16 + 0x80) == '\0') {
                iVar10 = *(int *)(local_60c + 0x804);
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10) =
                     (*(int *)(iVar16 + 0x10) - *(int *)(iStack_5fc + 0x7f4)) +
                     *(int *)(local_60c + 0x800);
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14) = iVar9 + iVar10;
                local_610 = (int *)0x0;
              }
              else {
                local_610 = (int *)(iVar9 + *(int *)(local_60c + 0x804));
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10) =
                     (*(int *)(iStack_5fc + 0x7f4) - *(int *)(local_60c + 0x800)) +
                     *(int *)(iVar16 + 0x10);
                *(int **)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14) = local_610;
              }
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x364) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x364);
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x68) =
                   *(double *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x68) + 1.0;
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x60) =
                   (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14);
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x70) =
                   *(undefined4 *)(local_60c + 0x808);
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x48) =
                   (double)*(int *)(local_60c + 0x810);
              *(undefined8 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x50) = 0;
              iVar16 = *(int *)(in_ECX + iVar20 * 4 + 0x194);
              iVar9 = *(int *)(*(int *)(iVar16 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar16 + 0x368));
              if ((((iVar9 == 3000) || (iVar9 == 0x3ea)) || (iVar9 == 0xbbe)) &&
                 ((iVar9 = *(int *)(*(int *)(iVar16 + 0x368) + 0x6f4), iVar9 != 0xdf &&
                  (iVar9 != 0xe0)))) {
                iVar9 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
                if (*(char *)(iVar9 + 0xcd) == '\0') {
LAB_0041ffe6:
                  if (*(char *)(iVar9 + 0xce) != '\0') {
                    uVar23 = 0x4004000000000000;
LAB_0041fff5:
                    *(undefined8 *)(iVar16 + 0x50) = uVar23;
                  }
                }
                else {
                  if (*(char *)(iVar9 + 0xce) == '\0') {
                    uVar23 = 0xc004000000000000;
                    goto LAB_0041fff5;
                  }
                  if (*(char *)(iVar9 + 0xcd) == '\0') goto LAB_0041ffe6;
                }
                iVar16 = *(int *)(in_ECX + iVar20 * 4 + 0x194);
                if (*(int *)(*(int *)(iVar16 + 0x368) + 0x6f4) == 0xd3) {
                  *(double *)(iVar16 + 0x50) = *(double *)(iVar16 + 0x50) * 0.25;
                }
              }
              iVar16 = *(int *)(in_ECX + iVar20 * 4 + 0x194);
              if (*(int *)(*(int *)(iVar16 + 0x368) + 0x6f8) == 0) {
                if (*(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x2f4) < 0) {
                  *(int *)(iVar16 + 0x2f4) = iVar15;
                }
                else {
                  *(int *)(iVar16 + 0x2f4) = *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x2f4)
                  ;
                }
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 8) =
                     *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 8);
              }
              if (local_5f0 == (char *)0x0) {
                *(undefined1 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x80) =
                     *(undefined1 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x80);
              }
              else if (local_5f0 == (char *)0x1) {
                *(char *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x80) =
                     '\x01' - *(char *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x80);
              }
              else {
                *(undefined1 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x80) = 0;
              }
              if (*(char *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x80) == '\0') {
                dVar2 = (double)*(int *)(local_60c + 0x80c);
              }
              else {
                dVar2 = -(double)*(int *)(local_60c + 0x80c);
              }
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x40) = dVar2;
              *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x58) =
                   (double)*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10);
              if (1 < (int)local_5ec) {
                dVar2 = ((double)local_5f8 * 10.0) / ((double)(int)local_5ec - 1.0) - 5.0;
                *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x50) =
                     dVar2 + *(double *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x50);
                iVar16 = *(int *)(in_ECX + iVar20 * 4 + 0x194);
                if ((*(double *)(iVar16 + 0x40) <= 0.0) || (dVar2 <= 0.0)) {
                  if ((0.0 <= *(double *)(iVar16 + 0x40)) || (0.0 <= dVar2)) {
                    *(double *)(iVar16 + 0x40) = dVar2 + *(double *)(iVar16 + 0x40);
                  }
                  else {
                    *(double *)(iVar16 + 0x40) = -dVar2 + *(double *)(iVar16 + 0x40);
                  }
                }
                else {
                  *(double *)(iVar16 + 0x40) = -dVar2 + *(double *)(iVar16 + 0x40);
                }
              }
              piVar12 = *(int **)(in_ECX + iVar15 * 4 + 0x194);
              if ((*(int *)(piVar12[0xda] + 0x6f8) == 3) &&
                 (*(int *)(piVar12[0x1c] * 0x178 + 0x7ac + piVar12[0xda]) == 0xbbb)) {
                *(undefined1 *)(*(int *)(in_ECX + *piVar12 * 4 + 0x194) + 0xf0 + iVar20) = 10;
                *(undefined1 *)
                 (**(int **)(in_ECX + iVar15 * 4 + 0x194) + 0xf0 +
                 *(int *)(in_ECX + iVar20 * 4 + 0x194)) = 10;
              }
              iVar16 = *(int *)(*(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x368) + 0x6f4);
              if ((iVar16 == 5) || (iVar16 == 0x34)) {
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x2fc) = 10;
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x304) = 10;
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x300) = 10;
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x308) = 5;
              }
              uVar4 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x10) = uVar4;
              uVar4 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x14) = uVar4;
              uVar4 = FUN_004450d0();
              *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x18) = uVar4;
              if (*(int *)(local_60c + 0x7fc) == 2) {
                *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x98) = 1;
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x98) = 0xffffffff;
                *(int *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x9c) = iVar20;
                *(int *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0xa0) = iVar15;
                *(undefined4 *)(*(int *)(in_ECX + iVar20 * 4 + 0x194) + 0x364) =
                     *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x364);
              }
              local_5f8 = local_5f8 + 1;
            } while (local_5f8 < (int)local_5ec);
            if ((1 < (int)local_604) && (iVar20 = 0, 0 < (int)local_604)) {
              do {
                uVar6 = (uint)local_604 & 0x80000001;
                if ((int)uVar6 < 0) {
                  uVar6 = (uVar6 - 1 | 0xfffffffe) + 1;
                }
                if (uVar6 == 0) {
                  if (iVar20 < (int)local_604 / 2 + -1) {
                    iVar16 = ((int)local_604 / 2 - iVar20) * 2 + -2;
                    goto LAB_0042033b;
                  }
LAB_00420350:
                  if ((int)local_604 / 2 < iVar20) {
                    *(int *)(*(int *)(in_ECX + local_5d0[iVar20] * 4 + 0x194) + 0xec) =
                         (iVar20 - (int)local_604 / 2) * 2;
                  }
                }
                else if (uVar6 == 1) {
                  if ((int)local_604 / 2 <= iVar20) goto LAB_00420350;
                  iVar16 = ((int)local_604 / 2 - iVar20) * 2;
LAB_0042033b:
                  *(int *)(*(int *)(in_ECX + local_5d0[iVar20] * 4 + 0x194) + 0xec) = iVar16;
                }
                iVar16 = 0;
                if (0 < iVar20) {
                  iVar9 = local_5d0[iVar20];
                  do {
                    iVar10 = local_5d0[iVar16];
                    *(undefined1 *)(iVar10 + 0xf0 + *(int *)(in_ECX + iVar9 * 4 + 0x194)) = 0x28;
                    iVar9 = local_5d0[iVar20];
                    iVar16 = iVar16 + 1;
                    *(undefined1 *)(*(int *)(in_ECX + iVar10 * 4 + 0x194) + 0xf0 + iVar9) = 0x28;
                  } while (iVar16 < iVar20);
                }
                iVar20 = iVar20 + 1;
              } while (iVar20 < (int)local_604);
            }
          }
        }
LAB_00420e93:
        iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
        if (*(int *)(*(int *)(iVar20 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar20 + 0x368)) == 0xd) {
LAB_00420ec1:
          if (*(int *)(*(int *)(iVar20 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar20 + 0x368)) != 0xd) {
            if (*(int *)(iVar20 + 0x70) != 200) {
              FUN_00417090();
              piVar12 = *(int **)(in_ECX + 0x7d4);
              iVar20 = 0;
              if (0 < piVar12[0x13608e0]) {
                do {
                  if (*(int *)(*piVar12 + 0x6f4) == 999) {
                    iStack_5fc = iVar20;
                    if (-1 < iVar20) {
                      local_5ec = (char *)0x0;
                      pcVar21 = local_5e8;
                      goto LAB_00420f4c;
                    }
                    break;
                  }
                  iVar20 = iVar20 + 1;
                  piVar12 = piVar12 + 1;
                } while (iVar20 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
              }
            }
          }
        }
        else if (*(int *)(iVar20 + 0x78) == 200) goto LAB_00420ec1;
        goto LAB_0042113f;
      }
      goto LAB_004214c6;
    }
    FUN_00429730(local_5dc,&DAT_0044d020,&DAT_00451160);
    if ((0 < DAT_0044d058) && ('\0' < DAT_0044f1af)) {
      FUN_00415160(0,0,0x31a,0x226,0);
      FUN_0043f010(0xe6,0xdd,0,0,0,DAT_00455608);
      FUN_00401290(DAT_00455608,"Waiting for opponent...",0x652512,0xd8775a,0x10f,0x127);
      DAT_0044d058 = DAT_0044d058 + -1;
    }
    FUN_004028a0(DAT_00455608);
    FUN_0043e940();
    if (DAT_0044d020 == 0) {
      _DAT_00451158 = 0;
      _DAT_00451154 = timeGetTime();
    }
    goto LAB_00422a95;
  }
  DAT_0044d02c = 1;
  FUN_0041a250(local_5dc);
  FUN_0041a5a0(uVar4,DAT_00450bd8,DAT_00451160);
  FUN_0041ae60(uVar4);
  FUN_0043f010(0x168,0x120,0xffffffff,1,0,DAT_00455608);
  if (DAT_00450b84 != 0) {
    goto LAB_00422952;
  }
  goto LAB_00422994;
code_r0x0041e44d:
  iVar20 = iVar20 + 1;
  piVar8 = piVar8 + 1;
  if (*(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380) <= iVar20) goto LAB_0041e61a;
  goto LAB_0041e443;
code_r0x0041ece5:
  local_610 = (int *)((int)local_610 + 1);
  piVar8 = piVar8 + 1;
  if (*(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380) <= (int)local_610) goto LAB_0041eec2;
  goto LAB_0041ecd3;
  while( true ) {
    local_5e8 = *(char **)(*(int *)(in_ECX + 0x7d4) + iStack_5fc * 4);
    local_610 = *(int **)(in_ECX + (int)pcVar21 * 4 + 0x194);
    FUN_004061d0();
    local_610[0xda] = (int)local_5e8;
    iVar20 = *(int *)((int)local_5e8 + 0x90);
    local_610[0x16] = 0;
    local_610[0x17] = 0x40822000;
    local_610[199] = iVar20;
    local_610[0x18] = 0;
    local_610[0x19] = -0x3f970000;
    uVar25 = 0x1d;
    local_610[0x1a] = 0;
    local_610[0x1b] = 0x4072c000;
    (pcVar21 + 4)[(int)in_ECX] = '\x01';
    *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x10) =
         *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10);
    *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14) =
         *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14);
    *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x18) =
         *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18);
    *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x68) =
         *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x68);
    uVar4 = 199;
    local_5e8 = (char *)FUN_00417170();
    uVar23 = CONCAT44(uVar4,0x27);
    *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x60) =
         (double)(extraout_ST0 - (float10)(int)local_5e8);
    uVar4 = 200;
    iVar20 = FUN_00417170();
    local_5e8 = (char *)(iVar20 + -0x13);
    *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x58) =
         (double)(int)local_5e8 + *(double *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x58);
    iVar20 = FUN_00417170(0xc9,0x14,uVar4,uVar23,uVar25);
    local_5e8 = (char *)-(iVar20 / 2);
    *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x48) = (double)(int)local_5e8 - 8.0;
    iVar20 = FUN_00417170(0xca,0xb);
    *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x40) =
         *(double *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x28) * 0.5 + ((double)iVar20 - 5.0);
    if ((int)local_5ec < 2) {
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0x78;
    }
    else if ((int)local_5ec < 5) {
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0x82;
    }
    else if ((int)local_5ec < 9) {
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0x7d;
    }
    else if ((int)local_5ec < 0xf) {
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = 0x87;
    }
    local_5ec = local_5ec + 1;
    if (0xe < (int)local_5ec) break;
LAB_00420f4c:
    pcVar11 = (char *)0x32;
    do {
      if ((pcVar11 + 4)[(int)in_ECX] == '\0') {
        pcVar21 = pcVar11;
        break;
      }
      pcVar11 = pcVar11 + 1;
    } while ((int)pcVar11 < 400);
    if (pcVar11 == (char *)0x190) break;
  }
  local_5e8 = pcVar21;
LAB_0042113f:
  iVar20 = *(int *)(in_ECX + iVar15 * 4 + 0x194);
  iVar16 = *(int *)(*(int *)(iVar20 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar20 + 0x368));
  if ((iVar16 != 0x12) && (iVar16 != 0x13)) goto LAB_00421397;
  iVar20 = *(int *)(*(int *)(iVar20 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar20 + 0x368));
  iVar16 = 0;
  local_5f8 = 0;
  if ((iVar20 == 0x12) || (iVar20 == 0x13)) {
    iVar20 = FUN_00417170();
    if (iVar20 == 0) {
      iVar16 = 1;
      goto LAB_004211a9;
    }
  }
  else {
    iVar16 = 7;
LAB_004211a9:
    local_5f8 = iVar16;
  }
  local_5f0 = (char *)0x0;
  if (iVar16 != 0) {
    pcVar21 = local_600;
    do {
      pcVar11 = (char *)0x32;
      do {
        if (in_ECX[(int)(pcVar11 + 4)] == '\0') {
          pcVar21 = pcVar11;
          break;
        }
        pcVar11 = pcVar11 + 1;
      } while ((int)pcVar11 < 400);
      if (pcVar11 == (char *)0x190) break;
      piVar12 = *(int **)(in_ECX + 0x7d4);
      pvVar5 = (void *)0x0;
      if (0 < piVar12[0x13608e0]) {
        local_610 = piVar12;
        do {
          if (*(int *)(*local_610 + 0x6f4) == 999) {
            local_5f4 = pvVar5;
            break;
          }
          local_610 = local_610 + 1;
          pvVar5 = (void *)((int)pvVar5 + 1);
        } while ((int)pvVar5 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
      }
      iStack_5fc = piVar12[(int)local_5f4];
      local_600 = *(char **)(in_ECX + (int)pcVar21 * 4 + 0x194);
      FUN_004061d0();
      *(int *)(local_600 + 0x368) = iStack_5fc;
      uVar4 = *(undefined4 *)(iStack_5fc + 0x90);
      local_600[0x58] = '\0';
      local_600[0x59] = '\0';
      local_600[0x5a] = '\0';
      local_600[0x5b] = '\0';
      local_600[0x5c] = '\0';
      local_600[0x5d] = ' ';
      local_600[0x5e] = -0x7e;
      local_600[0x5f] = '@';
      *(undefined4 *)(local_600 + 0x31c) = uVar4;
      local_600[0x60] = '\0';
      local_600[0x61] = '\0';
      local_600[0x62] = '\0';
      local_600[99] = '\0';
      local_600[100] = '\0';
      local_600[0x65] = '\0';
      local_600[0x66] = 'i';
      local_600[0x67] = -0x40;
      uVar25 = 0x1d;
      local_600[0x68] = '\0';
      local_600[0x69] = '\0';
      local_600[0x6a] = '\0';
      local_600[0x6b] = '\0';
      local_600[0x6c] = '\0';
      local_600[0x6d] = -0x40;
      local_600[0x6e] = 'r';
      local_600[0x6f] = '@';
      in_ECX[(int)(pcVar21 + 4)] = '\x01';
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x10) =
           *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x10);
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x14) =
           *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x14);
      *(undefined4 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x18) =
           *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x18);
      *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x68) =
           *(undefined8 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x68);
      uVar4 = 0xcc;
      iStack_5fc = FUN_00417170();
      uVar23 = CONCAT44(uVar4,0x3b);
      *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x60) =
           (double)(extraout_ST0_00 - (float10)iStack_5fc);
      uVar4 = 0xcd;
      iStack_5fc = FUN_00417170();
      iStack_5fc = iStack_5fc + -0x1d;
      *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x58) =
           (double)iStack_5fc + *(double *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x58);
      *(undefined8 *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x48) = 0xbff0000000000000;
      iStack_5fc = FUN_00417170(0xce,0xb,uVar4,uVar23,uVar25);
      *(double *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x40) =
           ((double)iStack_5fc - 5.0) + *(double *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x40);
      iVar20 = FUN_00417170(0xcf,1);
      *(int *)(*(int *)(in_ECX + (int)pcVar21 * 4 + 0x194) + 0x70) = iVar20 + 0x8c;
      local_5f0 = local_5f0 + 1;
    } while ((int)local_5f0 < local_5f8);
    local_600 = pcVar21;
  }
LAB_00421397:
  *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x78) =
       *(undefined4 *)(*(int *)(in_ECX + iVar15 * 4 + 0x194) + 0x70);
LAB_004214c6:
  iVar15 = iVar15 + 1;
  if (399 < iVar15) goto code_r0x004214d5;
  goto LAB_0041f550;
code_r0x004214d5:
  pcVar21 = (char *)0x0;
  if (DAT_00450bb8 == 1) {
    iVar15 = 0;
    local_600 = (char *)0x0;
    if (0 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380)) {
      do {
        iVar20 = *(int *)(*(int *)(*(int *)(in_ECX + 0x7d4) + iVar15 * 4) + 0x6f4);
        if (((99 < iVar20) && (iVar20 < 200)) &&
           ((iVar20 != 0x7a || (iVar20 = FUN_00417170(), iVar20 != 0)))) {
          local_5d0[(int)(pcVar21 + 0x28)] = iVar15;
          pcVar21 = pcVar21 + 1;
        }
        iVar15 = iVar15 + 1;
      } while (iVar15 < *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d82380));
      local_600 = pcVar21;
    }
    local_5f8 = 0;
    if (0 < (int)local_600) {
      do {
        piVar12 = (int *)0x32;
        do {
          if (*(char *)((int)(piVar12 + 1) + (int)in_ECX) == '\0') {
            local_610 = piVar12;
            break;
          }
          piVar12 = (int *)((int)piVar12 + 1);
        } while ((int)piVar12 < 400);
        uVar25 = 0x1e;
        iVar10 = DAT_0044d024 * 0x990;
        uVar4 = 0xd1;
        iVar20 = FUN_00417170();
        iVar15 = *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d45db0 + iVar10);
        uVar23 = CONCAT44(uVar4,0x1e);
        uVar4 = 0xd2;
        iVar16 = FUN_00417170();
        iStack_5d8 = iVar16 + 0x1e + iVar20 * ((iVar15 + -0x3c) / 0x1e);
        local_5f4 = (void *)(*(int *)(in_ECX + 0x7d4) + iVar10);
        iVar16 = FUN_00417170(0xd3,0x1e,uVar4,uVar23,uVar25);
        iVar15 = *(int *)((int)local_5f4 + 0x4d45db8);
        iVar20 = *(int *)((int)local_5f4 + 0x4d45db4);
        local_5f4 = *(void **)(in_ECX + 0x7d4);
        iVar9 = FUN_00417170(0xd4,0x1e);
        pvVar5 = local_5f4;
        local_5f4 = (void *)(iVar9 + *(int *)(iVar10 + 0x4d45db4 + (int)local_5f4) + 0x1e +
                            iVar16 * (((iVar15 - iVar20) + -0x3c) / 0x1e));
        iVar15 = *(int *)(in_ECX + (int)local_610 * 4 + 0x194);
        iVar20 = *(int *)((int)pvVar5 + local_5d0[local_5f8 + 0x28] * 4);
        FUN_004061d0();
        piVar8 = local_610;
        *(int *)(iVar15 + 0x368) = iVar20;
        uVar4 = *(undefined4 *)(iVar20 + 0x90);
        *(double *)(iVar15 + 0x58) = (double)iStack_5d8;
        *(undefined4 *)(iVar15 + 0x31c) = uVar4;
        *(undefined8 *)(iVar15 + 0x60) = 0xc07f400000000000;
        iVar20 = 0x50;
        *(double *)(iVar15 + 0x68) = (double)(int)local_5f4;
        *(char *)((int)(local_610 + 1) + (int)in_ECX) = '\x01';
        piVar12 = (int *)(in_ECX + 0x198);
        pcVar21 = in_ECX;
        do {
          if (pcVar21[4] != '\0') {
            *(char *)(piVar12[-1] + 0xf0 + (int)local_610) = '\0';
          }
          if (pcVar21[5] != '\0') {
            *(char *)((int)local_610 + *piVar12 + 0xf0) = '\0';
          }
          if (pcVar21[6] != '\0') {
            *(char *)(piVar12[1] + 0xf0 + (int)local_610) = '\0';
          }
          if (pcVar21[7] != '\0') {
            *(char *)(piVar12[2] + 0xf0 + (int)local_610) = '\0';
          }
          if (pcVar21[8] != '\0') {
            *(char *)(piVar12[3] + 0xf0 + (int)local_610) = '\0';
          }
          piVar12 = piVar12 + 5;
          iVar20 = iVar20 + -1;
          pcVar21 = pcVar21 + 5;
        } while (iVar20 != 0);
        *(undefined8 *)(*(int *)(in_ECX + (int)local_610 * 4 + 0x194) + 0x40) = 0;
        *(undefined8 *)(*(int *)(in_ECX + (int)local_610 * 4 + 0x194) + 0x48) = 0;
        *(undefined8 *)(*(int *)(in_ECX + (int)local_610 * 4 + 0x194) + 0x50) = 0;
        if (*(int *)(*(int *)(*(int *)(in_ECX + (int)local_610 * 4 + 0x194) + 0x368) + 0x6f4) ==
            0x7a) {
          *(undefined4 *)(*(int *)(in_ECX + (int)local_610 * 4 + 0x194) + 0x2fc) = 200;
        }
        iVar15 = *(int *)(in_ECX + (int)local_610 * 4 + 0x194);
        uVar4 = FUN_004450d0();
        *(undefined4 *)(iVar15 + 0x10) = uVar4;
        iVar15 = *(int *)(in_ECX + (int)piVar8 * 4 + 0x194);
        uVar4 = FUN_004450d0();
        *(undefined4 *)(iVar15 + 0x14) = uVar4;
        iVar15 = *(int *)(in_ECX + (int)piVar8 * 4 + 0x194);
        uVar4 = FUN_004450d0();
        *(undefined4 *)(iVar15 + 0x18) = uVar4;
        local_5f8 = local_5f8 + 1;
      } while (local_5f8 < (int)local_600);
    }
  }
  local_608 = (char *)0x0;
  piVar12 = (int *)(in_ECX + 0x194);
  do {
    if (in_ECX[(int)local_608 + 4] != '\0') {
      if (DAT_00450bb8 == 2) {
        iVar15 = *piVar12;
        iVar20 = *(int *)(*(int *)(iVar15 + 0x368) + 0x6f8);
        if ((((iVar20 == 1) || (iVar20 == 2)) || (iVar20 == 4)) || (iVar20 == 6)) {
          *(undefined4 *)(iVar15 + 0x31c) = 0xffffffff;
        }
        else if (((DAT_00451160 == 1) && (*(int *)(iVar15 + 0x364) == 5)) &&
                ((iVar20 == 0 && (*(int *)(*(int *)(iVar15 + 0x368) + 0x6f4) != 300)))) {
          *(undefined4 *)(iVar15 + 0x2fc) = 0;
          *(undefined4 *)(*piVar12 + 0x308) = 0;
        }
      }
      if ((DAT_00450bc0 == 1) &&
         ((DAT_00451160 != 1 || (((int)local_608 < 8 && (*(int *)(*piVar12 + 0x364) == 1)))))) {
        if (*(int *)(*piVar12 + 0x304) < 500) {
          *(undefined4 *)(*piVar12 + 0x304) = 500;
        }
        *(undefined4 *)(*piVar12 + 0x300) = *(undefined4 *)(*piVar12 + 0x304);
        *(undefined4 *)(*piVar12 + 0x2fc) = *(undefined4 *)(*piVar12 + 0x300);
        *(undefined4 *)(*piVar12 + 0x308) = 500;
        FUN_00402000();
      }
      iVar15 = *piVar12;
      if ((*(int *)(iVar15 + 0xe0) / 1000 == 1) && (0 < *(int *)(iVar15 + 0x2fc))) {
        *(int *)(iVar15 + 0xe0) = *(int *)(iVar15 + 0xe0) + -1;
        iVar15 = *piVar12;
        uVar6 = *(uint *)(iVar15 + 0xe0) & 0x80000007;
        bVar22 = uVar6 == 0;
        if ((int)uVar6 < 0) {
          bVar22 = (uVar6 - 1 | 0xfffffff8) == 0xffffffff;
        }
        if (bVar22) {
          if (*(int *)(iVar15 + 0x2fc) < *(int *)(iVar15 + 0x300)) {
            if (*(int *)(iVar15 + 0x2fc) < *(int *)(iVar15 + 0x300) + -8) {
              *(int *)(iVar15 + 0x2fc) = *(int *)(iVar15 + 0x2fc) + 8;
            }
            else {
              *(undefined4 *)(iVar15 + 0x2fc) = *(undefined4 *)(iVar15 + 0x300);
            }
          }
          else {
            *(undefined4 *)(iVar15 + 0xe0) = 0;
          }
        }
        if (*(int *)(*piVar12 + 0xe0) % 1000 == 0) {
          *(undefined4 *)(*piVar12 + 0xe0) = 0;
        }
      }
      iVar15 = *piVar12;
      if ((0 < *(int *)(iVar15 + 0xe4)) && (0 < *(int *)(iVar15 + 0x2fc))) {
        *(int *)(iVar15 + 0xe4) = *(int *)(iVar15 + 0xe4) + -1;
        iVar15 = *piVar12;
        uVar6 = *(uint *)(iVar15 + 0xe4) & 0x80000007;
        bVar22 = uVar6 == 0;
        if ((int)uVar6 < 0) {
          bVar22 = (uVar6 - 1 | 0xfffffff8) == 0xffffffff;
        }
        if ((bVar22) && (*(int *)(iVar15 + 0x2fc) < *(int *)(iVar15 + 0x300))) {
          *(int *)(iVar15 + 0x2fc) = *(int *)(iVar15 + 0x2fc) + 8;
          iVar15 = *piVar12;
          if (*(int *)(iVar15 + 0x300) < *(int *)(iVar15 + 0x2fc)) {
            *(undefined4 *)(iVar15 + 0x2fc) = *(undefined4 *)(iVar15 + 0x300);
            *(undefined4 *)(*piVar12 + 0xe4) = 0;
          }
        }
      }
      iVar15 = *piVar12;
      if (*(int *)(*(int *)(iVar15 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar15 + 0x368)) == 0x6a4) {
        *(undefined4 *)(iVar15 + 0xe0) = 0x44c;
      }
      if (in_ECX[(int)local_608 + 4] != '\0') {
        iVar15 = *piVar12;
        *(undefined4 *)(iVar15 + 0x2e8) = 1000;
        *(undefined4 *)(iVar15 + 0x2ec) = 1000;
        *(undefined4 *)(iVar15 + 0x2f0) = 1000;
        *(undefined4 *)(iVar15 + 0x2e4) = 0;
        *(undefined1 *)(iVar15 + 0xeb) = 0;
      }
    }
    local_608 = (char *)((int)local_608 + 1);
    piVar12 = piVar12 + 1;
  } while ((int)local_608 < 400);
  DAT_00450bc0 = 0;
  DAT_00450bb8 = 0;
  FUN_0041ae60(local_5dc);
  if (DAT_00450bec != 0) {
    iVar15 = *(int *)(in_ECX + 0x194);
    sprintf(acStack_1b8,"%2.3f %2.4f %d",*(undefined8 *)(iVar15 + 0x48),
            *(undefined8 *)(iVar15 + 0x60),*(undefined4 *)(iVar15 + 0x14));
    FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0);
    sprintf(acStack_1b8,"%d %d %d %d %d %d %d %d",(int)DAT_0044d040,(int)DAT_0044d041,
            (int)DAT_0044d042,(int)DAT_0044d043,(int)DAT_0044d044,(int)DAT_0044d045,
            (int)DAT_0044d046,(int)DAT_0044d047);
    FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x1e);
    sprintf(acStack_1b8,"%c %d",(int)DAT_004553e8,DAT_00450bfc);
    FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x3c);
  }
  if (DAT_00450c2c == 1) {
    FUN_00401290(DAT_00455608,"Press F4 or \'Attack\' to exit",0,0x7d7d7d,0x262,0x6e);
    pcVar21 = "huvs:01zwx0OiuvoeGkjhugu.dqp";
    pcVar11 = acStack_1d8;
    for (iVar15 = 7; iVar15 != 0; iVar15 = iVar15 + -1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar21;
      pcVar21 = pcVar21 + 4;
      pcVar11 = pcVar11 + 4;
    }
    pcVar13 = acStack_1d8;
    *pcVar11 = *pcVar21;
    uVar6 = 0;
    do {
      cVar1 = *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (cVar1 != '\0');
    if (pcVar13 != acStack_1d8 + 1) {
      do {
        uVar7 = uVar6 & 0x80000003;
        if ((int)uVar7 < 0) {
          uVar7 = (uVar7 - 1 | 0xfffffffc) + 1;
        }
        acStack_1d8[uVar6] = acStack_1d8[uVar6] - (char)uVar7;
        pcVar21 = acStack_1d8;
        uVar6 = uVar6 + 1;
        do {
          cVar1 = *pcVar21;
          pcVar21 = pcVar21 + 1;
        } while (cVar1 != '\0');
      } while (uVar6 < (uint)((int)pcVar21 - (int)(acStack_1d8 + 1)));
    }
    FUN_00401290(DAT_00455608,acStack_1d8,0,0xc8c8c8,5,0x6e);
    FUN_0043f010(0x168,0x120,0xffffffff,1,0,DAT_00455608);
  }
  else if (DAT_00450c28 == 1) {
    sprintf(acStack_1b8,
            "Function Keys Used:    F6: %d time(s)    F7: %d time(s)    F8: %d time(s)    F9: %d time(s)"
           );
    if (DAT_00451160 == 1) {
      FUN_00415160(0,0x80,0x31a,0x15,0);
      FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x81);
    }
    else {
      FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x6d);
    }
  }
  else if (DAT_00450c28 == 2) {
    sprintf(acStack_1b8,"Function Keys Locked");
    FUN_00401290(DAT_00455608,acStack_1b8,0,0xffffff,0,0x6d);
  }
  if (DAT_00450bdc < 100) {
    DAT_00450bbc = DAT_00450bbc + 1;
  }
  if (DAT_00450bdc - 0x65U < 0xf9) {
    if (DAT_00450bdc == 0x65) {
      if (((DAT_00450be4 != 0) && (DAT_00450b80 != 0)) && (DAT_00450b84 == 0)) {
        local_5e8 = in_ECX + 4;
        local_5f4 = (void *)(6 - (int)in_ECX);
        local_610 = (int *)0x0;
        local_600 = (char *)0x0;
        iVar15 = 0x14;
        do {
          if (*local_5e8 == '\0') {
            if ((local_600 + 0xe)[(int)in_ECX] != '\0') {
              iVar20 = iVar15 + 0x14;
              pcVar21 = (char *)((int)local_5f4 + (int)local_5e8);
              goto LAB_00421d7a;
            }
            *(undefined4 *)(iVar15 + DAT_004588a8) = 0xffffffff;
          }
          else {
            iVar20 = iVar15 + -0x14;
            pcVar21 = local_600;
LAB_00421d7a:
            if (-1 < (int)pcVar21) {
              *(undefined4 *)(iVar15 + 0x20 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x368) + 0x6f4);
              *(undefined4 *)(iVar15 + DAT_004588a8) = 0;
              if ((int)pcVar21 < 10) {
                *(undefined4 *)(iVar15 + DAT_004588a8) = 1;
              }
              *(undefined4 *)(iVar15 + 0x40 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x364);
              *(undefined4 *)(iVar15 + 0x60 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x358);
              *(undefined4 *)(iVar15 + 0x80 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x348);
              *(undefined4 *)(iVar15 + 0xa0 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x34c);
              *(undefined4 *)(iVar15 + 0xc0 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x350);
              *(undefined4 *)(iVar15 + 0xe0 + DAT_004588a8) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x35c);
              if (DAT_00451160 == 1) {
                if (local_5e0 == 1) {
                  *(undefined4 *)(iVar15 + 0x100 + DAT_004588a8) = 0xffffffff;
                }
                else {
                  *(uint *)(iVar15 + 0x100 + DAT_004588a8) =
                       (0 < *(int *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x2fc)) + 1;
                }
              }
              else if (-1 < DAT_00450bf8) {
                if (DAT_00450bf8 == *(int *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x364)) {
                  *(uint *)(iVar15 + 0x100 + DAT_004588a8) =
                       (0 < *(int *)(*(int *)(in_ECX + iVar20 + 0x194) + 0x2fc)) + 1;
                }
                else {
                  *(undefined4 *)(iVar15 + 0x100 + DAT_004588a8) = 0xffffffff;
                }
              }
            }
            local_610 = (int *)((int)local_610 + 1);
          }
          local_600 = local_600 + 1;
          iVar15 = iVar15 + 4;
          local_5e8 = local_5e8 + 1;
        } while (iVar15 < 0x34);
        *(int **)(DAT_004588a8 + 0x10) = local_610;
        if (DAT_00451160 == 4) {
          *(undefined4 *)(DAT_004588a8 + 0x134) = DAT_00451b64;
          *(undefined4 *)(DAT_004588a8 + 0x138) = DAT_00451b68;
          *(undefined4 *)(DAT_004588a8 + 0x13c) = DAT_00451b6c;
          *(undefined4 *)(DAT_004588a8 + 0x140) = DAT_00451b70;
        }
        *(int *)(DAT_004588a8 + 0x144) = DAT_00450bbc;
        DAT_00450b6c = 0;
        DAT_00450b70 = 2;
        if ((DAT_004588ac != 0) && (DAT_00450b88 != 0)) {
          FUN_0043df00();
          DAT_00458428 = *(int *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3f8 + DAT_004588ac);
          DAT_0045842c = *(undefined4 *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3fc + DAT_004588ac);
        }
        *(undefined4 *)(DAT_004588a8 + 0x8ac) = DAT_0044fb6c;
        *(undefined4 *)(DAT_004588a8 + 0x8b0) = DAT_00450c18;
        *(undefined4 *)(DAT_004588a8 + 0x8b4) = DAT_00450c1c;
        *(undefined4 *)(DAT_004588a8 + 0x8b8) = DAT_00450c20;
        *(undefined4 *)(DAT_004588a8 + 0x8bc) = DAT_00450c24;
        piVar12 = (int *)(in_ECX + 0x198);
        iVar15 = 0;
        local_600 = (char *)0x50;
        pcVar21 = in_ECX;
        do {
          if (((pcVar21[4] != '\0') &&
              (iVar20 = piVar12[-1], *(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
             ((*(int *)(iVar20 + 0x364) == 5 && (0 < *(int *)(iVar20 + 0x2fc))))) {
            iVar15 = iVar15 + 1;
          }
          if ((((pcVar21[5] != '\0') &&
               (iVar20 = *piVar12, *(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
              (*(int *)(iVar20 + 0x364) == 5)) && (0 < *(int *)(iVar20 + 0x2fc))) {
            iVar15 = iVar15 + 1;
          }
          if (((pcVar21[6] != '\0') &&
              (iVar20 = piVar12[1], *(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
             ((*(int *)(iVar20 + 0x364) == 5 && (0 < *(int *)(iVar20 + 0x2fc))))) {
            iVar15 = iVar15 + 1;
          }
          if (((pcVar21[7] != '\0') &&
              (iVar20 = piVar12[2], *(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
             ((*(int *)(iVar20 + 0x364) == 5 && (0 < *(int *)(iVar20 + 0x2fc))))) {
            iVar15 = iVar15 + 1;
          }
          if ((((pcVar21[8] != '\0') &&
               (iVar20 = piVar12[3], *(int *)(*(int *)(iVar20 + 0x368) + 0x6f8) == 0)) &&
              (*(int *)(iVar20 + 0x364) == 5)) && (0 < *(int *)(iVar20 + 0x2fc))) {
            iVar15 = iVar15 + 1;
          }
          piVar12 = piVar12 + 5;
          local_600 = local_600 + -1;
          pcVar21 = pcVar21 + 5;
        } while (local_600 != (char *)0x0);
        if (DAT_00451160 == 1) {
          uVar6 = (uint)(iVar15 < 1);
LAB_004221ea:
          *(uint *)(DAT_004588a8 + 0x8c0) = uVar6;
        }
        else if (DAT_00451160 == 4) {
          uVar6 = (DAT_0044d75c % 100) / 10 +
                  (DAT_0044d75c / 100 +
                  (DAT_00451b78 + 0x1adbb +
                  (DAT_0044d384 +
                  ((DAT_0044d758 % 100) / 10 +
                  (DAT_0044d758 / 100 + (DAT_00451b74 + DAT_0044d380 * 10) * 10) * 10) * 10) * 10) *
                  10) * 10;
          goto LAB_004221ea;
        }
        FUN_0043dd60();
        DAT_00450b80 = 0;
        if (DAT_00450bdc != 0x65) goto LAB_00422218;
      }
      DAT_00450b84 = 0;
    }
LAB_00422218:
    iVar15 = 0;
    if ((in_ECX[4] != '\0') || (in_ECX[0xe] != '\0')) {
      iVar15 = 1;
    }
    if ((in_ECX[5] != '\0') || (in_ECX[0xf] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[6] != '\0') || (in_ECX[0x10] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[7] != '\0') || (in_ECX[0x11] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[8] != '\0') || (in_ECX[0x12] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[9] != '\0') || (in_ECX[0x13] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[10] != '\0') || (in_ECX[0x14] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    if ((in_ECX[0xb] != '\0') || (in_ECX[0x15] != '\0')) {
      iVar15 = iVar15 + 1;
    }
    local_610 = (int *)(iVar15 * 0x2d);
    pcVar21 = (char *)((int)local_610 + 0x5d);
    if (DAT_00451160 == 4) {
      pcVar21 = (char *)((int)local_610 + 0x8a);
    }
    iVar15 = (0x212 - (int)pcVar21) / 2;
    local_5f8 = iVar15;
    FUN_0043f010(0x96,iVar15,0xffffffff,0,0,DAT_00455608);
    local_5e4 = iVar15 + 0x10;
    local_5f4 = (void *)(10 - (int)(in_ECX + 4));
    local_608 = "\x02";
    local_5f0 = (char *)0x0;
    do {
      pcVar11 = local_5f0;
      pcVar21 = local_5f0 + 4;
      if (((local_5f0 + 4)[(int)in_ECX] != '\0') || ((local_5f0 + 0xe)[(int)in_ECX] != '\0')) {
        local_5e4 = local_5e4 + 0x2d;
        FUN_0043f010(0x96,local_5e4,0xffffffff,0,0,DAT_00455608);
        if (pcVar21[(int)in_ECX] == '\0') {
          if ((pcVar11 + 0xe)[(int)in_ECX] == '\0') goto LAB_004226c5;
          local_5ec = (char *)((int)local_5f4 + (int)(pcVar21 + (int)in_ECX));
          iVar15 = (int)local_5f0 * 4 + 0x28;
        }
        else {
          local_5ec = local_5f0;
          iVar15 = (int)local_5f0 * 4;
        }
        if (-1 < (int)local_5ec) {
          FUN_0043f010(0xa5,local_5e4,0xffffffff,0,0,DAT_00455608);
          local_608 = "\x02";
          if ((int)local_5ec < 10) {
            local_608 = (char *)(uint)CONCAT12(0x20,CONCAT11((char)local_5ec + '1',0x50));
          }
          local_60c = (char *)0xce;
          iVar20 = local_5e4 + 0xf;
          local_604 = (int *)0x0;
          do {
            iVar16 = *(int *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x364);
            if (iVar16 == 1) {
              uVar23 = CONCAT44((int)*(char *)((int)&local_608 + (int)local_604),iVar20);
            }
            else if (iVar16 == 2) {
              cVar1 = *(char *)((int)&local_608 + (int)local_604);
LAB_0042249c:
              uVar23 = CONCAT44((int)cVar1,iVar20);
            }
            else if (iVar16 == 3) {
              uVar23 = CONCAT44((int)*(char *)((int)&local_608 + (int)local_604),iVar20);
            }
            else {
              if (iVar16 != 4) {
                cVar1 = *(char *)((int)&local_608 + (int)local_604);
                goto LAB_0042249c;
              }
              uVar23 = CONCAT44((int)*(char *)((int)&local_608 + (int)local_604),iVar20);
            }
            FUN_0043f010(local_60c,uVar23,1,DAT_00455608);
            local_60c = local_60c + 9;
            local_604 = (int *)((int)local_604 + 1);
          } while ((int)local_604 < 3);
          sprintf(acStack_1f8,"%d",*(undefined4 *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x358));
          FUN_00401290(DAT_00455608,acStack_1f8,0,0xaaaaff,0x10f);
          sprintf(acStack_1f8,"%d",*(undefined4 *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x348));
          FUN_00401290(DAT_00455608,acStack_1f8,0,0xaaaaff,0x146,iVar20);
          sprintf(acStack_1f8,"%d",*(undefined4 *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x34c));
          FUN_00401290(DAT_00455608,acStack_1f8,0,0xaaf0f0,0x186);
          sprintf(acStack_1f8,"%d",*(undefined4 *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x350));
          FUN_00401290(DAT_00455608,acStack_1f8,0,0xaaf0f0,0x1c6,iVar20);
          sprintf(acStack_1f8,"%d",*(undefined4 *)(*(int *)(in_ECX + iVar15 + 0x194) + 0x35c));
          FUN_00401290(DAT_00455608,acStack_1f8,0,0xaaf5aa);
          if ((DAT_00451160 == 1) || (-1 < DAT_00450bf8)) {
            FUN_0043f010(0x23b,iVar20,0xffffffff,0,0,DAT_00455608);
          }
        }
      }
LAB_004226c5:
      local_5f0 = local_5f0 + 1;
    } while ((int)local_5f0 < 8);
    if (DAT_00451160 == 4) {
      pcVar21 = (char *)(local_5f8 + 0x3d + (int)local_610);
      FUN_0043f010(0x96,pcVar21,0xffffffff,0,0,DAT_00455608);
      FUN_0043f010(0x96,pcVar21 + 0x2d,0xffffffff,0,0,DAT_00455608);
      pcVar18 = sprintf_exref;
      sprintf(acStack_1f8,"%d",DAT_00451b64);
      pcVar21 = pcVar21 + 0x17;
      FUN_00401290(DAT_00455608,acStack_1f8,0,0xffafaf,0xf3,pcVar21);
      sprintf(acStack_1f8,"%d",DAT_00451b68);
      FUN_00401290(DAT_00455608,acStack_1f8,0,0xafafff,0x1e3,pcVar21);
      sprintf(acStack_1f8,"%d",DAT_00451b6c);
      FUN_00401290(DAT_00455608,acStack_1f8,0,0xffafaf,0x143,pcVar21);
      sprintf(acStack_1f8,"%d",DAT_00451b70);
      FUN_00401290(DAT_00455608,acStack_1f8,0,0xafafff,0x233,pcVar21);
    }
    else {
      FUN_0043f010(0x96,(char *)(local_5f8 + 0x3d + (int)local_610),0xffffffff,0,0,DAT_00455608);
      pcVar18 = sprintf_exref;
    }
    iVar15 = (DAT_00450bbc + 0xf) / 0x1e;
    if (iVar15 < 0xe10) {
      (*pcVar18)();
    }
    else {
      (*pcVar18)(acStack_1f8,"%02d : %02d : %02d",iVar15 / 0xe10,(iVar15 % 0xe10) / 0x3c,
                 (iVar15 % 0xe10) % 0x3c);
    }
    if (DAT_00451160 == 4) {
      iVar15 = local_5f8 + 0x70;
    }
    else {
      iVar15 = local_5f8 + 0x43;
    }
    FUN_00401290(DAT_00455608,acStack_1f8,0x24400ffffff,(char *)(iVar15 + (int)local_610));
  }
  if (DAT_00450b84 != 0) {
    uVar4 = local_5dc;
LAB_00422952:
    FUN_0043f010(0x43,0x216,0x18,0,0,uVar4);
    if (DAT_0044d030 != 0) {
      FUN_0041b390(DAT_00451160,*(undefined4 *)(DAT_004588ac + 0x144),DAT_00450bbc);
    }
  }
LAB_00422994:
  FUN_0041b130();
  FUN_004028a0(DAT_00455608);
  FUN_0043e940();
  FUN_00419e60();
LAB_00422a95:
  ExceptionList = local_4c;
  __security_check_cookie(local_84 ^ (uint)auStack_634);
  return;
}
