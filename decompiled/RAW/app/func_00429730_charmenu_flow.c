/*
 * Procedure: FUN_00429730
 * Address: 0x00429730 - 0x0042e0c6 (Length: 18839 bytes)
 * Purpose: Character select menu flow, replay filename formatting, mode initialization and game loop transitions
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00429730(undefined4 param_1,int *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  size_t _Size;
  char cVar4;
  int in_ECX;
  int iVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  char *pcVar10;
  uint uVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  ushort *puVar15;
  uint uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  int local_a90;
  int *local_a8c;
  int *local_a88;
  int *local_a84;
  undefined4 local_a80;
  int local_a7c;
  uint local_a78;
  int *local_a74;
  int *local_a70;
  int *local_a6c;
  int local_a68;
  int *local_a64;
  int aiStack_a60 [500];
  _SYSTEMTIME local_290;
  int local_280;
  char local_27c [20];
  ushort local_268 [2];
  char local_264 [95];
  char cStack_205;
  char local_204 [500];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0044614a;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_a90;
  ExceptionList = &local_c;
  local_a80 = param_1;
  local_a64 = param_2;
  local_a88 = param_3;
  local_a90 = in_ECX;
  if ((DAT_004512cc != 10) && (*param_2 == 10)) {
    FUN_00402020(&DAT_00447744,DAT_0044eea4 ^ (uint)(aiStack_a60 + -0x10));
  }
  DAT_004512cc = *param_2;
  local_a70 = (int *)0x0;
  local_a84 = (int *)0x0;
  local_a6c = (int *)0x0;
  local_a7c = 0;
  local_a68 = DAT_004512c8;
  if (DAT_0044d07c != 0) {
    local_a8c = operator_new(0x1f50);
    local_4 = 0;
    if (local_a8c == (void *)0x0) {
      DAT_004512c4 = 0;
    }
    else {
      DAT_004512c4 = FUN_0043ee50(0x40,"CHARMENU",0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 1;
    if (local_a8c == (void *)0x0) {
      _DAT_004512b0 = 0;
    }
    else {
      _DAT_004512b0 = FUN_0043ee50(0x40,&DAT_00449acc,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 2;
    if (local_a8c == (void *)0x0) {
      _DAT_004512b4 = 0;
    }
    else {
      _DAT_004512b4 = FUN_0043ee50(0x40,&DAT_00449ac8,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 3;
    if (local_a8c == (void *)0x0) {
      _DAT_004512b8 = 0;
    }
    else {
      _DAT_004512b8 = FUN_0043ee50(0x40,&DAT_00449ac4,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 4;
    if (local_a8c == (void *)0x0) {
      _DAT_004512bc = 0;
    }
    else {
      _DAT_004512bc = FUN_0043ee50(0x40,&DAT_00449ac0,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 5;
    if (local_a8c == (void *)0x0) {
      _DAT_004512c0 = 0;
    }
    else {
      _DAT_004512c0 = FUN_0043ee50(0x40,&DAT_00449abc,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 6;
    if (local_a8c == (void *)0x0) {
      DAT_004512ac = 0;
    }
    else {
      DAT_004512ac = FUN_0043ee50(0x40,&DAT_00449ab8,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 7;
    if (local_a8c == (void *)0x0) {
      DAT_004512a8 = 0;
    }
    else {
      DAT_004512a8 = FUN_0043ee50(0x40,&DAT_00449ab0,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 8;
    if (local_a8c == (void *)0x0) {
      DAT_0044fd88 = 0;
    }
    else {
      DAT_0044fd88 = FUN_0043ee50(0x40,&DAT_00449aac,0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 9;
    if (local_a8c == (void *)0x0) {
      DAT_0044fd84 = 0;
    }
    else {
      DAT_0044fd84 = FUN_0043ee50(0x40,"RFACE",0);
    }
    local_4 = 0xffffffff;
    local_a8c = operator_new(0x1f50);
    local_4 = 10;
    if (local_a8c == (int *)0x0) {
      DAT_0044f8fc = 0;
    }
    else {
      DAT_0044f8fc = FUN_0043ee50(0x40,"SPARK",0);
    }
    DAT_00451288 = 0;
    DAT_00451268 = 0;
    DAT_00451248 = -1;
    DAT_0045128c = 0;
    DAT_0045126c = 0;
    DAT_0045124c = -1;
    DAT_00451290 = 0;
    _DAT_00451270 = 0;
    DAT_00451250 = -1;
    DAT_00451294 = 0;
    _DAT_00451274 = 0;
    DAT_00451254 = -1;
    DAT_00451298 = 0;
    _DAT_00451278 = 0;
    DAT_00451258 = -1;
    DAT_0045129c = 0;
    _DAT_0045127c = 0;
    DAT_0045125c = -1;
    DAT_004512a0 = 0;
    _DAT_00451280 = 0;
    DAT_00451260 = -1;
    DAT_004512a4 = 0;
    _DAT_00451284 = 0;
    DAT_00451264 = -1;
    *(undefined4 *)(DAT_0044f8fc + 0xc) = 0x14;
    *(undefined4 *)(DAT_0044f8fc + 0x14) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x7e4) = 0;
    *(undefined4 *)(DAT_0044f8fc + 0xfb4) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x1784) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x3c) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x80c) = 0x80;
    *(undefined4 *)(DAT_0044f8fc + 0xfdc) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x17ac) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x18) = 0xcc;
    *(undefined4 *)(DAT_0044f8fc + 0x7e8) = 0;
    *(undefined4 *)(DAT_0044f8fc + 0xfb8) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x1788) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x40) = 0xcc;
    *(undefined4 *)(DAT_0044f8fc + 0x810) = 0x80;
    *(undefined4 *)(DAT_0044f8fc + 0xfe0) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x17b0) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x1c) = 0x132;
    *(undefined4 *)(DAT_0044f8fc + 0x7ec) = 0;
    *(undefined4 *)(DAT_0044f8fc + 0xfbc) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x178c) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x44) = 0x132;
    *(undefined4 *)(DAT_0044f8fc + 0x814) = 0x80;
    *(undefined4 *)(DAT_0044f8fc + 0xfe4) = 0x66;
    local_4 = 0xffffffff;
    DAT_0044d07c = 0;
    *(undefined4 *)(DAT_0044f8fc + 0x17b4) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x20) = 0x198;
    *(undefined4 *)(DAT_0044f8fc + 0x7f0) = 0;
    *(undefined4 *)(DAT_0044f8fc + 0xfc0) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x1790) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x48) = 0x198;
    *(undefined4 *)(DAT_0044f8fc + 0x818) = 0x80;
    *(undefined4 *)(DAT_0044f8fc + 0xfe8) = 0x66;
    *(undefined4 *)(DAT_0044f8fc + 0x17b8) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0x28) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x7f8) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0xfc8) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x1798) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x50) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x820) = 0xd0;
    *(undefined4 *)(DAT_0044f8fc + 0xff0) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17c0) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x2c) = 0x7a;
    *(undefined4 *)(DAT_0044f8fc + 0x7fc) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0xfcc) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x179c) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x54) = 0x7a;
    *(undefined4 *)(DAT_0044f8fc + 0x824) = 0xd0;
    *(undefined4 *)(DAT_0044f8fc + 0xff4) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17c4) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x30) = 0xb7;
    *(undefined4 *)(DAT_0044f8fc + 0x800) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0xfd0) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17a0) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x58) = 0xb7;
    *(undefined4 *)(DAT_0044f8fc + 0x828) = 0xd0;
    *(undefined4 *)(DAT_0044f8fc + 0xff8) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17c8) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x34) = 0xf4;
    *(undefined4 *)(DAT_0044f8fc + 0x804) = 0x50;
    *(undefined4 *)(DAT_0044f8fc + 0xfd4) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17a4) = 0x30;
    *(undefined4 *)(DAT_0044f8fc + 0x5c) = 0xf4;
    *(undefined4 *)(DAT_0044f8fc + 0x82c) = 0xd0;
    *(undefined4 *)(DAT_0044f8fc + 0xffc) = 0x3d;
    *(undefined4 *)(DAT_0044f8fc + 0x17cc) = 0x30;
    param_2 = local_a64;
    in_ECX = local_a90;
  }
  if ((*local_a88 == 5) && (DAT_00450c2c == 0)) {
    DAT_0044d02c = 1;
    *param_2 = 10;
LAB_00429ea0:
    FUN_00431d10(local_a80,param_2,local_a88,&DAT_004512c8);
    goto LAB_0042e0d2;
  }
  iVar5 = *param_2;
  if (iVar5 == 300) {
    FUN_00437220(local_a80,param_2,local_a88);
    goto LAB_0042e0d2;
  }
  if (iVar5 == 10) goto LAB_00429ea0;
  if ((0x13 < iVar5) && (iVar5 < 0x33)) {
    FUN_00432ab0(local_a80,param_2,local_a88);
    goto LAB_0042e0d2;
  }
  if ((0x77 < iVar5) && (iVar5 < 0x97)) {
    FUN_00434ab0(local_a80,param_2,local_a88);
    goto LAB_0042e0d2;
  }
  if (iVar5 == 3) {
    DAT_00451288 = 0;
    DAT_00451248 = -1;
    DAT_00451268 = 1;
    DAT_0045128c = 0;
    DAT_0045124c = -1;
    DAT_0045126c = 1;
    DAT_00451290 = 0;
    DAT_00451250 = -1;
    _DAT_00451270 = 1;
    DAT_00451294 = 0;
    DAT_00451254 = -1;
    _DAT_00451274 = 1;
    DAT_00451298 = 0;
    DAT_00451258 = -1;
    _DAT_00451278 = 1;
    DAT_0045129c = 0;
    DAT_0045125c = -1;
    _DAT_0045127c = 1;
    DAT_004512a0 = 0;
    DAT_00451260 = -1;
    _DAT_00451280 = 1;
    DAT_004512a4 = 0;
    DAT_00451264 = -1;
    _DAT_00451284 = 1;
    if (*local_a88 == 1) {
      piVar2 = (int *)(in_ECX + 0x194);
      iVar5 = 0x14;
      do {
        *(undefined4 *)(*piVar2 + 0x364) = 1;
        piVar2 = piVar2 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (*local_a88 == 4) {
      *(undefined4 *)(*(int *)(in_ECX + 0x1bc) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x194) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x1c0) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x198) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x1c4) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x19c) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x1c8) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x1a0) + 0x364) = 1;
      *(undefined4 *)(*(int *)(in_ECX + 0x1cc) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1a4) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1d0) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1a8) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1d4) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1ac) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1d8) + 0x364) = 2;
      *(undefined4 *)(*(int *)(in_ECX + 0x1b0) + 0x364) = 2;
    }
    DAT_004512c8 = 0;
LAB_0042a0ae:
    *param_2 = 1;
    local_a68 = 0;
  }
  else if (iVar5 == 2) {
    DAT_004512c8 = 3;
    goto LAB_0042a0ae;
  }
  if ((*local_a88 == 4) && (DAT_004512c8 == 3)) {
    iVar5 = *param_2;
    if (199 < iVar5) goto LAB_0042a0e4;
    *param_2 = 200;
LAB_0042a0eb:
    FUN_00438b40(local_a80,param_2,local_a88,&DAT_004512c8,&DAT_00451288,&DAT_00451248,&DAT_00451228
                );
    goto LAB_0042e0d2;
  }
  iVar5 = *param_2;
  if (199 < iVar5) {
LAB_0042a0e4:
    if (iVar5 < 300) goto LAB_0042a0eb;
  }
  DAT_00451224 = (DAT_00451224 + 1) % 0x1e;
  piVar2 = (int *)(in_ECX + 0x198);
  iVar5 = 0x50;
  do {
    iVar7 = *(int *)(piVar2[-1] + 0x364);
    if ((iVar7 < 0) || (4 < iVar7)) {
      *(undefined4 *)(piVar2[-1] + 0x364) = 0;
    }
    iVar7 = *(int *)(*piVar2 + 0x364);
    if ((iVar7 < 0) || (4 < iVar7)) {
      *(undefined4 *)(*piVar2 + 0x364) = 0;
    }
    iVar7 = *(int *)(piVar2[1] + 0x364);
    if ((iVar7 < 0) || (4 < iVar7)) {
      *(undefined4 *)(piVar2[1] + 0x364) = 0;
    }
    iVar7 = *(int *)(piVar2[2] + 0x364);
    if ((iVar7 < 0) || (4 < iVar7)) {
      *(undefined4 *)(piVar2[2] + 0x364) = 0;
    }
    iVar7 = *(int *)(piVar2[3] + 0x364);
    if ((iVar7 < 0) || (4 < iVar7)) {
      *(undefined4 *)(piVar2[3] + 0x364) = 0;
    }
    piVar2 = piVar2 + 5;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  FUN_00415160(0,0,0x31a,0x226,0);
  FUN_0043f010(0x28,0x21,0xffffffff,0,0,local_a80);
  if (DAT_004512c8 == 0) {
    if (DAT_00451288 == 0) {
      local_a7c = 1;
    }
    if (DAT_0045128c == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_00451290 == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_00451294 == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_00451298 == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_0045129c == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_004512a0 == 0) {
      local_a7c = local_a7c + 1;
    }
    if (DAT_004512a4 == 0) {
      local_a7c = local_a7c + 1;
    }
  }
  else {
    local_a7c = -1;
  }
  uVar8 = 0;
  do {
    uVar11 = (int)uVar8 >> 0x1f;
    if ((&DAT_00451288)[uVar8] < 1) {
      iVar5 = ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4;
      if (DAT_004512c8 != 0) {
        uVar11 = uVar8 & 0x80000003;
        if ((int)uVar11 < 0) {
          uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
        }
        uVar16 = 0xffffff;
        pcVar6 = "     ----";
        goto LAB_0042a3bb;
      }
      uVar11 = uVar8 & 0x80000003;
      if ((int)uVar11 < 0) {
        uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
      }
      iVar12 = uVar11 * 0x99;
      cVar4 = ((char)((ulonglong)((longlong)DAT_00451224 * 0x2aaaaaab) >> 0x20) -
              (char)((longlong)DAT_00451224 * 0x2aaaaaab >> 0x3f)) * 'L' +
              (char)DAT_00451224 * '\x1e';
      iVar7 = iVar5 + 0xdb;
      iVar1 = iVar12 + 0xb1;
      uVar16 = ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19);
      pcVar6 = "   Join?";
    }
    else if ((&DAT_00451288)[uVar8] < 0xb) {
      iVar5 = ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4;
      uVar11 = uVar8 & 0x80000003;
      if ((int)uVar11 < 0) {
        uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
      }
      iVar12 = uVar11 * 0x99;
      iVar7 = iVar5 + 0xdb;
      iVar1 = iVar12 + 0xb1;
      uVar16 = 0xffffff;
      pcVar6 = &DAT_0044fcc0 + uVar8 * 0xb;
    }
    else {
      iVar5 = ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4;
      uVar11 = uVar8 & 0x80000003;
      if ((int)uVar11 < 0) {
        uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
      }
      uVar16 = 0x9b9bff;
      pcVar6 = "Computer";
LAB_0042a3bb:
      iVar12 = uVar11 * 0x99;
      iVar1 = iVar12 + 0xb1;
      iVar7 = iVar5 + 0xdb;
    }
    FUN_00401290(DAT_00455608,pcVar6,0,uVar16,iVar1,iVar7);
    if (((&DAT_00451288)[uVar8] == 0) && (DAT_004512c8 == 0)) {
      if (DAT_0044d078 == 0x96) {
        iVar7 = iVar5 + 0x78;
        iVar14 = iVar12 + 0x93;
LAB_0042a46d:
        FUN_0043f010(iVar14,iVar7,0xffffffff,0,0,local_a80);
      }
      else if (-1 < DAT_0044d078) {
        iVar7 = iVar5 + 0x7d;
        iVar14 = iVar12 + 0xb5;
        goto LAB_0042a46d;
      }
      iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
      if (*(char *)(iVar7 + 0xd1) == '\0') {
        if ((*(char *)(iVar7 + 0xd2) == '\0') || (local_a7c != 8)) {
          (&DAT_00451268)[uVar8] = 0;
        }
        else {
          if ((&DAT_00451268)[uVar8] == 0) {
            FUN_00401a30(0);
            *local_a64 = 10;
            DAT_00457580 = 0;
            FUN_00431c70();
          }
          (&DAT_00451268)[uVar8] = 1;
        }
      }
      else {
        if (((&DAT_00451268)[uVar8] == 0) && (DAT_0044d074 == 0)) {
          (&DAT_00451288)[uVar8] = 1;
          FUN_00401a30(0);
        }
        (&DAT_00451268)[uVar8] = 1;
      }
    }
    if ((&DAT_00451288)[uVar8] == 1) {
      if ((&DAT_00451248)[uVar8] < 0) {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        cVar4 = ((char)((ulonglong)((longlong)DAT_00451224 * 0x2aaaaaab) >> 0x20) -
                (char)((longlong)DAT_00451224 * 0x2aaaaaab >> 0x3f)) * 'L' +
                (char)DAT_00451224 * '\x1e';
        uVar11 = ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19);
        pcVar6 = " Random";
      }
      else {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        iVar1 = iVar12 + 0xb1;
        uVar11 = ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19);
        pcVar6 = (char *)(*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) + 0x25324);
      }
      FUN_00401290(DAT_00455608,pcVar6,0,uVar11,iVar1,iVar5 + 0xf1);
      iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
      if (*(char *)(iVar7 + 0xd0) == '\0') {
        if (*(char *)(iVar7 + 0xcf) == '\0') {
          if (*(char *)(iVar7 + 0xcd) == '\0') {
            if (*(char *)(iVar7 + 0xd1) == '\0') {
              if (*(char *)(iVar7 + 0xd2) == '\0') {
                (&DAT_00451268)[uVar8] = 0;
              }
              else {
                if ((&DAT_00451268)[uVar8] == 0) {
                  FUN_00401a30(0);
                  (&DAT_00451288)[uVar8] = 0;
                }
                (&DAT_00451268)[uVar8] = 1;
              }
            }
            else {
              if ((&DAT_00451268)[uVar8] == 0) {
                FUN_00401a30(0);
                (&DAT_00451288)[uVar8] = 3 - (uint)(*local_a88 != 1);
              }
              (&DAT_00451268)[uVar8] = 1;
            }
          }
          else {
            if ((&DAT_00451268)[uVar8] == 0) {
              (&DAT_00451248)[uVar8] = -1;
            }
            (&DAT_00451268)[uVar8] = 1;
          }
        }
        else {
          if ((&DAT_00451268)[uVar8] == 0) {
            (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + -1;
            iVar7 = (&DAT_00451248)[uVar8];
            iVar1 = iVar7 + 1;
            if (iVar7 != -1) {
              do {
                if (SBORROW4(iVar7,-1) != iVar1 < 0) {
                  (&DAT_00451248)[uVar8] = *(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380) + -1;
                }
                iVar7 = *(int *)(*(int *)(local_a90 + 0x7d4) + (&DAT_00451248)[uVar8] * 4);
                if ((*(int *)(iVar7 + 0x6f8) == 0) &&
                   (((iVar7 = *(int *)(iVar7 + 0x6f4) / 10, iVar7 != 5 && (iVar7 != 3)) ||
                    (DAT_00458428 == 1)))) {
                  *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) =
                       *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + (&DAT_00451248)[uVar8] * 4);
                  goto LAB_0042a7d6;
                }
                (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + -1;
                iVar7 = (&DAT_00451248)[uVar8];
                iVar1 = iVar7 + 1;
              } while (iVar1 != 0);
              (&DAT_00451268)[uVar8] = 1;
              goto LAB_0042a899;
            }
          }
LAB_0042a7d6:
          (&DAT_00451268)[uVar8] = 1;
        }
      }
      else {
        if ((&DAT_00451268)[uVar8] == 0) {
          do {
            (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + 1;
            iVar7 = (&DAT_00451248)[uVar8];
            if (*(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380) <= iVar7) {
              (&DAT_00451248)[uVar8] = -1;
              (&DAT_00451268)[uVar8] = 1;
              goto LAB_0042a899;
            }
            if (iVar7 == -1) goto LAB_0042a6de;
            iVar1 = *(int *)(*(int *)(local_a90 + 0x7d4) + iVar7 * 4);
          } while ((*(int *)(iVar1 + 0x6f8) != 0) ||
                  (((iVar1 = *(int *)(iVar1 + 0x6f4) / 10, iVar1 == 5 || (iVar1 == 3)) &&
                   (DAT_00458428 != 1))));
          *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) =
               *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + iVar7 * 4);
        }
LAB_0042a6de:
        (&DAT_00451268)[uVar8] = 1;
      }
    }
LAB_0042a899:
    if ((&DAT_00451288)[uVar8] == 2) {
      cVar4 = DAT_00451288 == 3;
      if (DAT_0045128c == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_00451290 == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_00451294 == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_00451298 == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_0045129c == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_004512a0 == 3) {
        cVar4 = cVar4 + '\x01';
      }
      if (DAT_004512a4 == 3) {
        cVar4 = cVar4 + '\x01';
      }
      iVar7 = -1;
      local_a78 = -1;
      if ((cVar4 == '\a') && ((*local_a88 == 0 || (*local_a88 == 4)))) {
        local_a8c = (int *)(local_a90 + 0x198);
        local_a78 = 2;
        local_a74 = &DAT_0045128c;
        do {
          if ((local_a74[-1] % 10 == 3) && (local_a78 - 2 != uVar8)) {
            iVar1 = *(int *)(local_a8c[-1] + 0x364);
            if (iVar1 == 0) {
LAB_0042a993:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar1;
            }
            else if ((-1 < iVar7) && (iVar1 != iVar7)) goto LAB_0042a993;
          }
          if ((*local_a74 % 10 == 3) && (local_a78 - 1 != uVar8)) {
            iVar1 = *(int *)(*local_a8c + 0x364);
            if (iVar1 == 0) {
LAB_0042a9d7:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar1;
            }
            else if ((-1 < iVar7) && (iVar1 != iVar7)) goto LAB_0042a9d7;
          }
          if ((local_a74[1] % 10 == 3) && (local_a78 != uVar8)) {
            iVar1 = *(int *)(local_a8c[1] + 0x364);
            if (iVar1 == 0) {
LAB_0042aa18:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar1;
            }
            else if ((-1 < iVar7) && (iVar1 != iVar7)) goto LAB_0042aa18;
          }
          if ((local_a74[2] % 10 == 3) && (local_a78 + 1 != uVar8)) {
            iVar1 = *(int *)(local_a8c[2] + 0x364);
            if (iVar1 == 0) {
LAB_0042aa5e:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar1;
            }
            else if ((-1 < iVar7) && (iVar1 != iVar7)) goto LAB_0042aa5e;
          }
          local_a74 = local_a74 + 4;
          local_a8c = local_a8c + 4;
          iVar1 = local_a78 + 2;
          local_a78 = local_a78 + 4;
        } while (iVar1 < 8);
        local_a78 = iVar7;
      }
      uVar11 = local_a78;
      if ((&DAT_00451248)[uVar8] < 0) {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        pcVar6 = " Random";
      }
      else {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        pcVar6 = (char *)(*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) + 0x25324);
      }
      FUN_00401290(DAT_00455608,pcVar6,0,0xffffff,iVar12 + 0xb1,iVar5 + 0xf1);
      while( true ) {
        iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
        iVar1 = *(int *)(iVar7 + 0x364);
        if ((iVar1 != uVar11) && ((*local_a88 != 4 || ((iVar1 != 0 && (iVar1 < 3)))))) break;
        *(int *)(iVar7 + 0x364) = (iVar1 + 1) % 5;
        uVar11 = local_a78;
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 1) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        FUN_00401290(DAT_00455608,"Team 1",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),iVar12 + 0xbb
                     ,iVar5 + 0x107);
        uVar11 = local_a78;
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 2) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        FUN_00401290(DAT_00455608,"Team 2",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),iVar12 + 0xbb
                     ,iVar5 + 0x107);
        uVar11 = local_a78;
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 3) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        FUN_00401290(DAT_00455608,"Team 3",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),iVar12 + 0xbb
                     ,iVar5 + 0x107);
        uVar11 = local_a78;
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 4) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        FUN_00401290(DAT_00455608,"Team 4",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),iVar12 + 0xbb
                     ,iVar5 + 0x107);
        uVar11 = local_a78;
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 0) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        FUN_00401290(DAT_00455608,"Independent",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),iVar12 + 0xa7
                     ,iVar5 + 0x107);
        uVar11 = local_a78;
      }
      if (*local_a88 == 2) {
        *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) = 0;
        *(undefined1 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0xd1) = 1;
        (&DAT_00451268)[uVar8] = 0;
      }
      iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
      if (*(char *)(iVar7 + 0xd0) == '\0') {
        if (*(char *)(iVar7 + 0xcf) == '\0') {
          if (*(char *)(iVar7 + 0xd1) == '\0') {
            if (*(char *)(iVar7 + 0xd2) != '\0') {
              if ((&DAT_00451268)[uVar8] == 0) {
                (&DAT_00451288)[uVar8] = 1;
                FUN_00401a30(0);
              }
              goto LAB_0042af71;
            }
            (&DAT_00451268)[uVar8] = 0;
          }
          else {
            if ((&DAT_00451268)[uVar8] == 0) {
              FUN_00401a30(0);
              (&DAT_00451288)[uVar8] = 3;
            }
            (&DAT_00451268)[uVar8] = 1;
          }
        }
        else {
          if ((&DAT_00451268)[uVar8] == 0) {
            *(int *)(iVar7 + 0x364) = *(int *)(iVar7 + 0x364) + -1;
            iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
            if (*(int *)(iVar7 + 0x364) < 0) {
              *(undefined4 *)(iVar7 + 0x364) = 4;
            }
            while( true ) {
              iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
              iVar1 = *(int *)(iVar7 + 0x364);
              if ((iVar1 != uVar11) && ((*local_a88 != 4 || ((iVar1 != 0 && (iVar1 < 3)))))) break;
              piVar2 = (int *)(iVar7 + 0x364);
              *piVar2 = *piVar2 + -1;
              iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
              if (*(int *)(iVar7 + 0x364) < 0) {
                *(undefined4 *)(iVar7 + 0x364) = 4;
              }
            }
          }
LAB_0042af71:
          (&DAT_00451268)[uVar8] = 1;
        }
      }
      else {
        if ((&DAT_00451268)[uVar8] == 0) {
          iVar1 = *(int *)(iVar7 + 0x364);
          do {
            do {
              *(int *)(iVar7 + 0x364) = (iVar1 + 1) % 5;
              iVar7 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
              iVar1 = *(int *)(iVar7 + 0x364);
            } while (iVar1 == local_a78);
          } while ((*local_a88 == 4) && ((iVar1 == 0 || (2 < iVar1))));
        }
        (&DAT_00451268)[uVar8] = 1;
      }
    }
    iVar7 = local_a90;
    if ((&DAT_00451288)[uVar8] == 3) {
      if ((&DAT_00451248)[uVar8] < 0) {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        FUN_00401290(DAT_00455608," Random",0,0xffffff,iVar12 + 0xb1,iVar5 + 0xf1);
        iVar7 = local_a90;
      }
      else {
        FUN_0043f010(iVar12 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        FUN_00401290(DAT_00455608,*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x368) + 0x25324,0,
                     0xffffff,iVar12 + 0xb1,iVar5 + 0xf1);
      }
      if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 0) {
        FUN_00401290(DAT_00455608,"Independent",0,0xffffff,iVar12 + 0xa7,iVar5 + 0x107);
      }
      if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 1) {
        FUN_00401290(DAT_00455608,"Team 1",0,0xffffff,iVar12 + 0xbb,iVar5 + 0x107);
      }
      if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 2) {
        FUN_00401290(DAT_00455608,"Team 2",0,0xffffff,iVar12 + 0xbb,iVar5 + 0x107);
      }
      if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 3) {
        FUN_00401290(DAT_00455608,"Team 3",0,0xffffff,iVar12 + 0xbb,iVar5 + 0x107);
      }
      if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 4) {
        FUN_00401290(DAT_00455608,"Team 4",0,0xffffff,iVar12 + 0xbb,iVar5 + 0x107);
      }
      if (DAT_004512c8 == 0) {
        cVar4 = *(char *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0xd2);
        if (cVar4 == '\0') {
LAB_0042b1ec:
          (&DAT_00451268)[uVar8] = 0;
        }
        else if (DAT_0044d078 == 0x96) {
          if ((&DAT_00451268)[uVar8] == 0) {
            (&DAT_00451288)[uVar8] = (*local_a88 != 1) + 1;
            FUN_00401a30(0);
          }
          (&DAT_00451268)[uVar8] = 1;
        }
        else {
          if ((cVar4 == '\0') || (0x95 < DAT_0044d078)) goto LAB_0042b1ec;
          if ((&DAT_00451268)[uVar8] == 0) {
            local_a70 = (int *)0x1;
          }
          (&DAT_00451268)[uVar8] = 1;
        }
      }
      if ((&DAT_00451288)[uVar8] != 3) goto LAB_0042b217;
      local_a6c = (int *)((int)local_a6c + 1);
      *(undefined1 *)(local_a90 + 4 + uVar8) = 1;
    }
    else {
LAB_0042b217:
      *(undefined1 *)(local_a90 + 4 + uVar8) = 0;
    }
    iVar5 = DAT_0044d078;
    if (((&DAT_00451288)[uVar8] == 0) || ((&DAT_00451288)[uVar8] == 3)) {
      local_a84 = (int *)((int)local_a84 + 1);
    }
    uVar8 = uVar8 + 1;
  } while ((int)uVar8 < 8);
  if (((int)local_a6c < 1) || (local_a84 != (int *)0x8)) {
    DAT_0044d078 = 0x96;
  }
  else {
    DAT_0044d078 = DAT_0044d078 + -1;
    if (local_a70 != (int *)0x0) {
      DAT_0044d078 = iVar5 + -0x1f;
    }
    if (local_a6c == (int *)0x8) {
      DAT_0044d078 = 0;
    }
  }
  DAT_0044d074 = DAT_004512c8;
  if (DAT_004512c8 == 1) {
    DAT_00451220 = 0;
    FUN_0043f010(0xda,0xd7,0xffffffff,0,0,local_a80);
    local_a8c = (int *)0x0;
    pcVar6 = (char *)(local_a90 + 5);
    local_290.wYear = 0;
    local_290.wMonth = 0;
    local_290.wDayOfWeek = 0;
    local_290.wDay = 0;
    local_290.wHour = 0;
    local_290.wMinute = 0;
    local_290.wSecond = 0;
    local_290.wMilliseconds = 0;
    local_280 = 0;
    piVar2 = (int *)(local_a90 + 0x198);
    iVar5 = 2;
    do {
      if (pcVar6[-1] == '\0') {
        local_a8c = (int *)((int)local_a8c + 1);
      }
      else if ((*(int *)(piVar2[-1] + 0x364) == 0) ||
              (aiStack_a60[*(int *)(piVar2[-1] + 0x364) + 500] == 0)) {
        aiStack_a60[*(int *)(piVar2[-1] + 0x364) + 500] =
             aiStack_a60[*(int *)(piVar2[-1] + 0x364) + 500] + 1;
      }
      if (*pcVar6 == '\0') {
        local_a8c = (int *)((int)local_a8c + 1);
      }
      else if ((*(int *)(*piVar2 + 0x364) == 0) ||
              (aiStack_a60[*(int *)(*piVar2 + 0x364) + 500] == 0)) {
        aiStack_a60[*(int *)(*piVar2 + 0x364) + 500] =
             aiStack_a60[*(int *)(*piVar2 + 0x364) + 500] + 1;
      }
      if (pcVar6[1] == '\0') {
        local_a8c = (int *)((int)local_a8c + 1);
      }
      else if ((*(int *)(piVar2[1] + 0x364) == 0) ||
              (aiStack_a60[*(int *)(piVar2[1] + 0x364) + 500] == 0)) {
        aiStack_a60[*(int *)(piVar2[1] + 0x364) + 500] =
             aiStack_a60[*(int *)(piVar2[1] + 0x364) + 500] + 1;
      }
      if (pcVar6[2] == '\0') {
        local_a8c = (int *)((int)local_a8c + 1);
      }
      else if ((*(int *)(piVar2[2] + 0x364) == 0) ||
              (aiStack_a60[*(int *)(piVar2[2] + 0x364) + 500] == 0)) {
        aiStack_a60[*(int *)(piVar2[2] + 0x364) + 500] =
             aiStack_a60[*(int *)(piVar2[2] + 0x364) + 500] + 1;
      }
      piVar2 = piVar2 + 4;
      pcVar6 = pcVar6 + 4;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (local_a8c == (int *)0x0) {
      DAT_004512c8 = 3;
    }
    if ((local_280 + local_290._12_4_ + local_290._8_4_ + local_290._4_4_ + local_290._0_4_ < 2) &&
       (*local_a88 != 1)) {
      local_a74 = (int *)0x1;
    }
    else {
      local_a74 = (int *)0x0;
    }
    if (((DAT_0044d070 == (int *)0xffffff9c) || ((int)DAT_0044d070 < (int)local_a74)) ||
       ((int)local_a8c < (int)DAT_0044d070)) {
      DAT_0044d070 = local_a74;
    }
    iVar5 = 0;
    piVar9 = (int *)(local_a90 + 0x194);
    piVar2 = piVar9;
    do {
      if (*(char *)(local_a90 + 4 + iVar5) != '\0') {
        iVar7 = *piVar2;
        if (*(char *)(iVar7 + 0xd0) == '\0') {
          if (*(char *)(iVar7 + 0xcf) == '\0') {
            if (*(char *)(iVar7 + 0xd1) == '\0') {
              if (*local_a88 != 2) {
                if (*local_a88 != 3) {
                  (&DAT_00451268)[iVar5] = 0;
                  goto LAB_0042b539;
                }
                goto LAB_0042b507;
              }
LAB_0042b513:
              (&DAT_00451268)[iVar5] = 0;
              DAT_0044d070 = local_a8c;
            }
            else {
LAB_0042b507:
              if ((*local_a88 == 2) || (*local_a88 == 3)) goto LAB_0042b513;
            }
            if (((&DAT_00451268)[iVar5] == 0) && (local_a68 == 1)) {
              if ((*local_a88 != 2) && (*local_a88 != 3)) {
                FUN_00401a30(0);
              }
              piVar2 = DAT_0044d070;
              DAT_004512c8 = 2;
              if (DAT_0044d070 == (int *)0x0) {
                DAT_0044d06c = 2;
                DAT_00451228 = (uint)(DAT_00451248 < 0);
                DAT_0045122c = (uint)(DAT_0045124c < 0);
                DAT_00451230 = (uint)(DAT_00451250 < 0);
                DAT_00451234 = (uint)(DAT_00451254 < 0);
                DAT_00451238 = (uint)(DAT_00451258 < 0);
                DAT_0045123c = (uint)(DAT_0045125c < 0);
                DAT_00451240 = (uint)(DAT_00451260 < 0);
                DAT_004512c8 = 3;
                DAT_00451244 = (uint)(DAT_00451264 < 0);
                iVar5 = 0;
                do {
                  if (*(int *)((int)&DAT_00451228 + iVar5) != 0) {
                    piVar2 = *(int **)(local_a90 + 0x7d4);
                    iVar7 = 1;
                    iVar1 = 0;
                    if (1 < piVar2[0x13608e0]) {
                      local_a84 = (int *)piVar2[0x13608e0];
                      do {
                        piVar2 = piVar2 + 1;
                        if (((*(int *)(*piVar2 + 0x6f8) == 0) &&
                            (DAT_00451264 != iVar7 &&
                             (DAT_00451260 != iVar7 &&
                             (DAT_0045125c != iVar7 &&
                             (DAT_00451258 != iVar7 &&
                             (DAT_00451254 != iVar7 &&
                             (DAT_00451250 != iVar7 &&
                             (DAT_0045124c != iVar7 && DAT_00451248 != iVar7)))))))) &&
                           (*(int *)(*piVar2 + 0x6f4) < 0x1e)) {
                          aiStack_a60[iVar1] = iVar7;
                          iVar1 = iVar1 + 1;
                        }
                        iVar7 = iVar7 + 1;
                      } while (iVar7 < (int)local_a84);
                    }
                    iVar7 = FUN_00417170(0xd7,iVar1);
                    iVar7 = aiStack_a60[iVar7];
                    *(int *)((int)&DAT_00451248 + iVar5) = iVar7;
                    *(undefined4 *)(*piVar9 + 0x368) =
                         *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + iVar7 * 4);
                  }
                  iVar5 = iVar5 + 4;
                  piVar9 = piVar9 + 1;
                } while (iVar5 < 0x20);
              }
              else {
                piVar9 = DAT_0044d070;
                if ((*(char *)(local_a90 + 4) == '\0') && (0 < (int)DAT_0044d070)) {
                  piVar9 = (int *)((int)DAT_0044d070 + -1);
                  (&DAT_004511fc)[(int)DAT_0044d070 - (int)piVar9] = 0;
                  DAT_00451288 = 0xb;
                }
                if ((*(char *)(local_a90 + 5) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 1;
                  DAT_0045128c = 0xb;
                }
                if ((*(char *)(local_a90 + 6) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 2;
                  DAT_00451290 = 0xb;
                }
                if ((*(char *)(local_a90 + 7) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 3;
                  DAT_00451294 = 0xb;
                }
                if ((*(char *)(local_a90 + 8) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 4;
                  DAT_00451298 = 0xb;
                }
                if ((*(char *)(local_a90 + 9) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 5;
                  DAT_0045129c = 0xb;
                }
                if ((*(char *)(local_a90 + 10) == '\0') && (0 < (int)piVar9)) {
                  piVar9 = (int *)((int)piVar9 + -1);
                  (&DAT_004511fc)[(int)piVar2 - (int)piVar9] = 6;
                  DAT_004512a0 = 0xb;
                }
                if ((*(char *)(local_a90 + 0xb) == '\0') && (0 < (int)piVar9)) {
                  (&DAT_00451200)[(int)piVar2 - (int)piVar9] = 7;
                  DAT_004512a4 = 0xb;
                }
                DAT_004511fc = 0;
                (&DAT_00451268)[iVar5] = 1;
              }
              break;
            }
          }
          else if ((((&DAT_00451268)[iVar5] == 0) && (local_a68 == 1)) &&
                  (DAT_0044d070 = (int *)((int)DAT_0044d070 + -1),
                  (int)DAT_0044d070 < (int)local_a74)) {
            DAT_0044d070 = local_a8c;
          }
        }
        else if ((((&DAT_00451268)[iVar5] == 0) && (local_a68 == 1)) &&
                (DAT_0044d070 = (int *)((int)DAT_0044d070 + 1), (int)local_a8c < (int)DAT_0044d070))
        {
          DAT_0044d070 = local_a74;
        }
        (&DAT_00451268)[iVar5] = 1;
      }
LAB_0042b539:
      iVar5 = iVar5 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar5 < 8);
    piVar9 = local_a74;
    piVar2 = local_a8c;
    piVar13 = (int *)0x0;
    iVar5 = 0x118;
    do {
      sprintf((char *)&local_290,"%d",piVar13);
      if (((int)piVar13 < (int)piVar9) || ((int)piVar2 < (int)piVar13)) {
        uVar17 = 0xc06850;
      }
      else {
        uVar17 = 0xffffff;
      }
      FUN_00401290(DAT_00455608,&local_290,0x9f472f,uVar17,iVar5 + 6,0x11e);
      if (DAT_0044d070 == piVar13) {
        FUN_00415160(iVar5,0x11b,0x15,1,0xffffff);
        FUN_00415160(iVar5,0x11b,1,0x15,0xffffff);
        FUN_00415160(iVar5,0x12f,0x15,1,0xffffff);
        FUN_00415160(iVar5 + 0x14,0x11b,1,0x15,0xffffff);
      }
      iVar5 = iVar5 + 0x1e;
      piVar13 = (int *)((int)piVar13 + 1);
    } while (iVar5 < 0x1eb);
  }
  if ((DAT_004512c8 == 2) || (DAT_004512c8 == 3)) {
    local_a70 = (int *)0x0;
    local_a7c = 0;
    local_a6c = (int *)0x0;
    local_a78 = 0;
    local_a74 = (int *)0x0;
    if (DAT_004512c8 == 2) {
      pcVar6 = (char *)(local_a90 + 4);
      piVar9 = &DAT_00451268;
      piVar2 = (int *)(local_a90 + 0x194);
      do {
        if (*pcVar6 != '\0') {
          iVar5 = *piVar2;
          if (*(char *)(iVar5 + 0xcd) == '\0') {
            if (*(char *)(iVar5 + 0xce) == '\0') {
              if (*(char *)(iVar5 + 0xd0) == '\0') {
                if (*(char *)(iVar5 + 0xcf) == '\0') {
                  if (*(char *)(iVar5 + 0xd1) == '\0') {
                    if (*(char *)(iVar5 + 0xd2) == '\0') {
                      *piVar9 = 0;
                    }
                    else {
                      if ((*piVar9 == 0) && (local_a68 == 2)) {
                        local_a74 = (int *)0x1;
                      }
                      *piVar9 = 1;
                    }
                  }
                  else {
                    if ((*piVar9 == 0) && (local_a68 == 2)) {
                      local_a78 = 1;
                    }
                    *piVar9 = 1;
                  }
                }
                else {
                  if ((*piVar9 == 0) && (local_a68 == 2)) {
                    local_a7c = 1;
                  }
                  *piVar9 = 1;
                }
              }
              else {
                if ((*piVar9 == 0) && (local_a68 == 2)) {
                  local_a6c = (int *)0x1;
                }
                *piVar9 = 1;
              }
            }
            else {
              *piVar9 = 1;
            }
          }
          else {
            if ((*piVar9 == 0) && (local_a68 == 2)) {
              local_a70 = (int *)0x1;
            }
            *piVar9 = 1;
          }
        }
        piVar9 = piVar9 + 1;
        pcVar6 = pcVar6 + 1;
        piVar2 = piVar2 + 1;
      } while ((int)piVar9 < 0x451288);
    }
    iVar5 = 0;
    if (0 < (int)DAT_0044d070) {
      iVar7 = local_a90;
      do {
        uVar8 = (&DAT_00451200)[iVar5];
        uVar11 = (int)uVar8 >> 0x1f;
        if (0xb < (&DAT_00451288)[uVar8]) {
          iVar7 = ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4;
          if ((&DAT_00451248)[uVar8] < 0) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            iVar1 = uVar16 * 0x99;
            FUN_0043f010(iVar1 + 0x93,iVar7 + 0x5e,0xffffffff,0,0,local_a80);
            pcVar6 = " Random";
          }
          else {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            iVar1 = uVar16 * 0x99;
            FUN_0043f010(iVar1 + 0x93,iVar7 + 0x5e,0xffffffff,0,0,local_a80);
            pcVar6 = (char *)(*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) + 0x25324);
          }
          FUN_00401290(DAT_00455608,pcVar6,0,0x9b9bff,iVar1 + 0xb1,iVar7 + 0xf1);
          iVar7 = local_a90;
        }
        if (0xc < (&DAT_00451288)[uVar8]) {
          if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 0) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            FUN_00401290(DAT_00455608,"Independent",0,0x9b9bff,uVar16 * 0x99 + 0xa7,
                         ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
          }
          if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 1) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            FUN_00401290(DAT_00455608,"Team 1",0,0x9b9bff,uVar16 * 0x99 + 0xbb,
                         ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
          }
          if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 2) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            FUN_00401290(DAT_00455608,"Team 2",0,0x9b9bff,uVar16 * 0x99 + 0xbb,
                         ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
          }
          if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 3) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            FUN_00401290(DAT_00455608,"Team 3",0,0x9b9bff,uVar16 * 0x99 + 0xbb,
                         ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
          }
          if (*(int *)(*(int *)(iVar7 + 0x194 + uVar8 * 4) + 0x364) == 4) {
            uVar16 = uVar8 & 0x80000003;
            if ((int)uVar16 < 0) {
              uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
            }
            FUN_00401290(DAT_00455608,"Team 4",0,0x9b9bff,uVar16 * 0x99 + 0xbb,
                         ((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)DAT_0044d070);
    }
    uVar8 = (&DAT_00451200)[DAT_004511fc];
    iVar5 = DAT_004511fc;
    if ((&DAT_00451288)[uVar8] == 0xb) {
      iVar5 = ((int)(uVar8 + ((int)uVar8 >> 0x1f & 3U)) >> 2) * 0xd4;
      if ((&DAT_00451248)[uVar8] < 0) {
        uVar11 = uVar8 & 0x80000003;
        if ((int)uVar11 < 0) {
          uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
        }
        iVar7 = uVar11 * 0x99;
        FUN_0043f010(iVar7 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar11 = ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19);
        pcVar6 = " Random";
      }
      else {
        uVar11 = uVar8 & 0x80000003;
        if ((int)uVar11 < 0) {
          uVar11 = (uVar11 - 1 | 0xfffffffc) + 1;
        }
        iVar7 = uVar11 * 0x99;
        FUN_0043f010(iVar7 + 0x93,iVar5 + 0x5e,0xffffffff,0,0,local_a80);
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar11 = ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19);
        pcVar6 = (char *)(*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) + 0x25324);
      }
      FUN_00401290(DAT_00455608,pcVar6,0,uVar11,iVar7 + 0xb1,iVar5 + 0xf1);
      piVar2 = local_a88;
      iVar7 = local_a90;
      iVar5 = DAT_00458428;
      if (local_a6c != (int *)0x0) {
        do {
          (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + 1;
          iVar1 = (&DAT_00451248)[uVar8];
          if (*(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380) <= iVar1) {
            (&DAT_00451248)[uVar8] = -1;
            goto LAB_0042bf93;
          }
          if (iVar1 == -1) goto LAB_0042bf93;
          iVar12 = *(int *)(*(int *)(local_a90 + 0x7d4) + iVar1 * 4);
        } while ((*(int *)(iVar12 + 0x6f8) != 0) ||
                (((iVar12 = *(int *)(iVar12 + 0x6f4) / 10, iVar12 == 5 || (iVar12 == 3)) &&
                 (iVar5 != 1))));
        *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) =
             *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + iVar1 * 4);
        iVar5 = DAT_00458428;
      }
LAB_0042bf93:
      if (local_a7c != 0) {
        (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + -1;
        iVar1 = (&DAT_00451248)[uVar8];
        iVar12 = iVar1 + 1;
        if (iVar1 != -1) {
          do {
            if (SBORROW4(iVar1,-1) != iVar12 < 0) {
              (&DAT_00451248)[uVar8] = *(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380) + -1;
            }
            iVar1 = *(int *)(*(int *)(local_a90 + 0x7d4) + (&DAT_00451248)[uVar8] * 4);
            if ((*(int *)(iVar1 + 0x6f8) == 0) &&
               (((iVar1 = *(int *)(iVar1 + 0x6f4) / 10, iVar1 != 5 && (iVar1 != 3)) || (iVar5 == 1))
               )) {
              *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x368) =
                   *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + (&DAT_00451248)[uVar8] * 4);
              break;
            }
            (&DAT_00451248)[uVar8] = (&DAT_00451248)[uVar8] + -1;
            iVar1 = (&DAT_00451248)[uVar8];
            iVar12 = iVar1 + 1;
          } while (iVar12 != 0);
        }
      }
      if (local_a70 != (int *)0x0) {
        (&DAT_00451248)[uVar8] = -1;
      }
      if (DAT_00451220 == 1) {
        (&DAT_00451248)[uVar8] = -1;
        if (*local_a88 != 2) {
          (&DAT_00451288)[uVar8] = 0xb;
        }
        if (*local_a88 == 1) {
          (&DAT_00451288)[uVar8] = 0xb;
        }
        DAT_00451220 = 0;
      }
      if (local_a78 == 0) {
LAB_0042c2e7:
        iVar5 = DAT_004511fc;
      }
      else {
        FUN_00401a30(0);
        (&DAT_00451288)[uVar8] = 0xc;
        local_a78 = 0;
        if (*piVar2 != 1) goto LAB_0042c2e7;
        iVar5 = (&DAT_00451200)[DAT_004511fc];
        (&DAT_00451288)[uVar8] = 0xd;
        iVar1 = 0;
        DAT_00451220 = (uint)((&DAT_00451248)[iVar5] < 0);
        iVar5 = DAT_004511fc + 1;
        DAT_004511fc = iVar5;
        if ((int)DAT_0044d070 <= iVar5) {
          local_a74 = (int *)0x0;
          DAT_00451228 = (uint)(DAT_00451248 < 0);
          DAT_0045122c = (uint)(DAT_0045124c < 0);
          DAT_00451230 = (uint)(DAT_00451250 < 0);
          DAT_00451234 = (uint)(DAT_00451254 < 0);
          DAT_00451238 = (uint)(DAT_00451258 < 0);
          DAT_0045123c = (uint)(DAT_0045125c < 0);
          DAT_00451240 = (uint)(DAT_00451260 < 0);
          DAT_00451244 = (uint)(DAT_00451264 < 0);
          local_a84 = (int *)(iVar7 + 0x194);
          do {
            if (*(int *)((int)&DAT_00451228 + iVar1) != 0) {
              piVar2 = *(int **)(iVar7 + 0x7d4);
              iVar5 = 1;
              iVar12 = 0;
              if (1 < piVar2[0x13608e0]) {
                iVar7 = *(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380);
                do {
                  piVar2 = piVar2 + 1;
                  if (((*(int *)(*piVar2 + 0x6f8) == 0) &&
                      (DAT_00451264 != iVar5 &&
                       (DAT_00451260 != iVar5 &&
                       (DAT_0045125c != iVar5 &&
                       (DAT_00451258 != iVar5 &&
                       (DAT_00451254 != iVar5 &&
                       (DAT_00451250 != iVar5 && (DAT_0045124c != iVar5 && DAT_00451248 != iVar5))))
                       )))) && (*(int *)(*piVar2 + 0x6f4) < 0x1e)) {
                    aiStack_a60[iVar12] = iVar5;
                    iVar12 = iVar12 + 1;
                  }
                  iVar5 = iVar5 + 1;
                } while (iVar5 < iVar7);
                iVar7 = local_a90;
              }
              iVar5 = FUN_00417170(0xd8,iVar12);
              iVar5 = aiStack_a60[iVar5];
              *(int *)((int)&DAT_00451248 + iVar1) = iVar5;
              *(undefined4 *)(*local_a84 + 0x368) =
                   *(undefined4 *)(*(int *)(iVar7 + 0x7d4) + iVar5 * 4);
            }
            local_a84 = local_a84 + 1;
            iVar1 = iVar1 + 4;
          } while (iVar1 < 0x20);
          DAT_0044d06c = 2;
          DAT_004512c8 = 3;
          iVar5 = DAT_004511fc;
          goto LAB_0042c3bf;
        }
        (&DAT_00451288)[(&DAT_00451200)[iVar5]] = 0xb;
      }
      if (local_a74 != (int *)0x0) {
        FUN_00401a30(0);
        local_a74 = (int *)0x0;
        if (DAT_004511fc == 0) {
          DAT_004512c8 = 1;
          if (DAT_00451288 == 0xb) {
            DAT_00451288 = 0;
          }
          if (DAT_0045128c == 0xb) {
            DAT_0045128c = 0;
          }
          if (DAT_00451290 == 0xb) {
            DAT_00451290 = 0;
          }
          if (DAT_00451294 == 0xb) {
            DAT_00451294 = 0;
          }
          if (DAT_00451298 == 0xb) {
            DAT_00451298 = 0;
          }
          if (DAT_0045129c == 0xb) {
            DAT_0045129c = 0;
          }
          if (DAT_004512a0 == 0xb) {
            DAT_004512a0 = 0;
          }
          iVar5 = 0;
          if (DAT_004512a4 == 0xb) {
            DAT_004512a4 = 0;
          }
        }
        else {
          iVar7 = (&DAT_004511fc)[DAT_004511fc];
          iVar5 = DAT_004511fc + -1;
          (&DAT_00451288)[iVar7] = 0xc;
          DAT_004511fc = iVar5;
          if (*piVar2 == 1) {
            (&DAT_00451288)[iVar7] = 0xb;
          }
          if (*piVar2 == 2) {
            (&DAT_00451288)[iVar7] = 0xb;
          }
        }
      }
    }
LAB_0042c3bf:
    uVar8 = (&DAT_00451200)[iVar5];
    if ((&DAT_00451288)[uVar8] == 0xc) {
      iVar7 = -1;
      if ((iVar5 == (int)DAT_0044d070 + -1) && ((*local_a88 == 0 || (*local_a88 == 4)))) {
        local_a8c = (int *)(local_a90 + 0x198);
        piVar2 = &DAT_0045128c;
        uVar11 = 2;
        do {
          if ((piVar2[-1] % 10 == 3) && (uVar11 - 2 != uVar8)) {
            iVar5 = *(int *)(local_a8c[-1] + 0x364);
            if (iVar5 == 0) {
LAB_0042c44a:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar5;
            }
            else if ((-1 < iVar7) && (iVar5 != iVar7)) goto LAB_0042c44a;
          }
          if ((*piVar2 % 10 == 3) && (uVar11 - 1 != uVar8)) {
            iVar5 = *(int *)(*local_a8c + 0x364);
            if (iVar5 == 0) {
LAB_0042c482:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar5;
            }
            else if ((-1 < iVar7) && (iVar5 != iVar7)) goto LAB_0042c482;
          }
          if ((piVar2[1] % 10 == 3) && (uVar11 != uVar8)) {
            iVar5 = *(int *)(local_a8c[1] + 0x364);
            if (iVar5 == 0) {
LAB_0042c4b8:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar5;
            }
            else if ((-1 < iVar7) && (iVar5 != iVar7)) goto LAB_0042c4b8;
          }
          if ((piVar2[2] % 10 == 3) && (uVar11 + 1 != uVar8)) {
            iVar5 = *(int *)(local_a8c[2] + 0x364);
            if (iVar5 == 0) {
LAB_0042c4f1:
              iVar7 = -2;
            }
            else if (iVar7 == -1) {
              iVar7 = iVar5;
            }
            else if ((-1 < iVar7) && (iVar5 != iVar7)) goto LAB_0042c4f1;
          }
          local_a8c = local_a8c + 4;
          iVar5 = uVar11 + 2;
          piVar2 = piVar2 + 4;
          uVar11 = uVar11 + 4;
        } while (iVar5 < 8);
      }
      while( true ) {
        iVar5 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
        iVar1 = *(int *)(iVar5 + 0x364);
        if ((iVar1 != iVar7) && ((*local_a88 != 4 || ((iVar1 != 0 && (iVar1 < 3)))))) break;
        *(int *)(iVar5 + 0x364) = (*(int *)(iVar5 + 0x364) + 1) % 5;
      }
      uVar11 = (int)uVar8 >> 0x1f;
      if (*(int *)(iVar5 + 0x364) == 0) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar16 = uVar8 & 0x80000003;
        if ((int)uVar16 < 0) {
          uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
        }
        FUN_00401290(DAT_00455608,"Independent",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),
                     uVar16 * 0x99 + 0xa7,((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 1) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar16 = uVar8 & 0x80000003;
        if ((int)uVar16 < 0) {
          uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
        }
        FUN_00401290(DAT_00455608,"Team 1",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),
                     uVar16 * 0x99 + 0xbb,((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 2) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar16 = uVar8 & 0x80000003;
        if ((int)uVar16 < 0) {
          uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
        }
        FUN_00401290(DAT_00455608,"Team 2",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),
                     uVar16 * 0x99 + 0xbb,((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 3) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar16 = uVar8 & 0x80000003;
        if ((int)uVar16 < 0) {
          uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
        }
        FUN_00401290(DAT_00455608,"Team 3",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),
                     uVar16 * 0x99 + 0xbb,((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
      }
      if (*(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) == 4) {
        cVar4 = (char)(DAT_00451224 / 6) * 'L' + (char)DAT_00451224 * '\x1e';
        uVar16 = uVar8 & 0x80000003;
        if ((int)uVar16 < 0) {
          uVar16 = (uVar16 - 1 | 0xfffffffc) + 1;
        }
        FUN_00401290(DAT_00455608,"Team 4",0,
                     ((byte)(cVar4 + 0x46) | 0xff00) << 8 | (uint)(byte)(cVar4 + 0x19),
                     uVar16 * 0x99 + 0xbb,((int)(uVar8 + (uVar11 & 3)) >> 2) * 0xd4 + 0x107);
      }
      if (local_a6c != (int *)0x0) {
        iVar5 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
        *(int *)(iVar5 + 0x364) = (*(int *)(iVar5 + 0x364) + 1) % 5;
        iVar5 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
        if (*(int *)(iVar5 + 0x364) == iVar7) {
          *(int *)(iVar5 + 0x364) = (*(int *)(iVar5 + 0x364) + 1) % 5;
        }
      }
      if (local_a7c != 0) {
        piVar2 = (int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364);
        *piVar2 = *piVar2 + -1;
        iVar5 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
        if (*(int *)(iVar5 + 0x364) < 0) {
          *(undefined4 *)(iVar5 + 0x364) = 4;
        }
        while ((iVar5 = *(int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364), iVar5 == iVar7 ||
               ((*local_a88 == 4 && ((iVar5 == 0 || (2 < iVar5))))))) {
          piVar2 = (int *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364);
          *piVar2 = *piVar2 + -1;
          iVar5 = *(int *)(local_a90 + 0x194 + uVar8 * 4);
          if (*(int *)(iVar5 + 0x364) < 0) {
            *(undefined4 *)(iVar5 + 0x364) = 4;
          }
        }
      }
      if (*local_a88 != 2) {
        if (local_a78 != 0) goto LAB_0042c939;
LAB_0042cb53:
        if (local_a74 != (int *)0x0) {
          FUN_00401a30(0);
          (&DAT_00451288)[uVar8] = 0xb;
          DAT_00451220 = 0;
        }
        goto LAB_0042cb75;
      }
      *(undefined4 *)(*(int *)(local_a90 + 0x194 + uVar8 * 4) + 0x364) = 0;
LAB_0042c939:
      FUN_00401a30(0);
      iVar7 = local_a90;
      iVar5 = (&DAT_00451248)[(&DAT_00451200)[DAT_004511fc]];
      (&DAT_00451288)[uVar8] = 0xd;
      DAT_00451220 = (uint)(iVar5 < 0);
      DAT_004511fc = DAT_004511fc + 1;
      if (DAT_004511fc < (int)DAT_0044d070) {
        (&DAT_00451288)[(&DAT_00451200)[DAT_004511fc]] = 0xb;
        goto LAB_0042cb53;
      }
      DAT_00451228 = (uint)(DAT_00451248 < 0);
      DAT_0045122c = (uint)(DAT_0045124c < 0);
      DAT_00451230 = (uint)(DAT_00451250 < 0);
      DAT_00451234 = (uint)(DAT_00451254 < 0);
      DAT_00451238 = (uint)(DAT_00451258 < 0);
      DAT_0045123c = (uint)(DAT_0045125c < 0);
      DAT_00451240 = (uint)(DAT_00451260 < 0);
      DAT_00451244 = (uint)(DAT_00451264 < 0);
      local_a6c = (int *)(local_a90 + 0x194);
      iVar5 = 0;
      do {
        if (*(int *)((int)&DAT_00451228 + iVar5) != 0) {
          piVar2 = *(int **)(iVar7 + 0x7d4);
          iVar1 = 1;
          iVar12 = 0;
          if (1 < piVar2[0x13608e0]) {
            local_a84 = (int *)piVar2[0x13608e0];
            do {
              piVar2 = piVar2 + 1;
              if (((*(int *)(*piVar2 + 0x6f8) == 0) &&
                  (DAT_00451264 != iVar1 &&
                   (DAT_00451260 != iVar1 &&
                   (DAT_0045125c != iVar1 &&
                   (DAT_00451258 != iVar1 &&
                   (DAT_00451254 != iVar1 &&
                   (DAT_00451250 != iVar1 && (DAT_0045124c != iVar1 && DAT_00451248 != iVar1))))))))
                 && (*(int *)(*piVar2 + 0x6f4) < 0x1e)) {
                aiStack_a60[iVar12] = iVar1;
                iVar12 = iVar12 + 1;
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < (int)local_a84);
          }
          iVar1 = FUN_00417170(0xd9,iVar12);
          iVar1 = aiStack_a60[iVar1];
          *(int *)((int)&DAT_00451248 + iVar5) = iVar1;
          *(undefined4 *)(*local_a6c + 0x368) = *(undefined4 *)(*(int *)(iVar7 + 0x7d4) + iVar1 * 4)
          ;
        }
        local_a6c = local_a6c + 1;
        iVar5 = iVar5 + 4;
      } while (iVar5 < 0x20);
      DAT_0044d06c = 2;
      DAT_004512c8 = 3;
    }
    else {
LAB_0042cb75:
      if (DAT_004512c8 != 3) goto LAB_0042e0b6;
      iVar7 = local_a90;
    }
    uVar17 = local_a80;
    piVar2 = local_a88;
    if (*local_a88 != 4) {
      local_a70 = (int *)0x0;
      local_a84 = (int *)0x0;
      local_a74 = (int *)0x0;
      local_a6c = (int *)0x0;
      local_a8c = (int *)0x0;
      FUN_0043f010(3,3,8,0,0,local_a80);
      FUN_0043f010(3,0x9f,0xf,1,0,uVar17);
      if (DAT_0044d06c == 0) {
        FUN_0043f010(0x5c,0x10,9,0,0,uVar17);
      }
      if (DAT_0044d06c == 1) {
        FUN_0043f010(0x40,0x27,10,0,0,uVar17);
      }
      if (DAT_0044d06c == 2) {
        FUN_0043f010(0x28,0x40,0xb,0,0,uVar17);
      }
      if (DAT_0044d06c == 3) {
        FUN_0043f010(0xf,0x57,0xc,0,0,uVar17);
      }
      if (DAT_0044d06c == 4) {
        FUN_0043f010(0x25,0x6f,0xd,0,0,uVar17);
      }
      if (DAT_0044d06c == 5) {
        FUN_0043f010(0x65,0x89,0xe,0,0,uVar17);
      }
      if (DAT_0044d028 == 1) {
        DAT_0044d024 = 100;
      }
      if (*piVar2 == 1) {
        iVar5 = (DAT_00450b94 / 10) * 10;
        if (DAT_00450b94 != iVar5) {
          DAT_00450b94 = iVar5;
        }
        FUN_0043f010(0xf,0x57,0x17,0,0,uVar17);
        if (DAT_0044d06c == 3) {
          FUN_0043f010(0xf,0x57,0x16,0,0,uVar17);
        }
        if (DAT_00450b94 / 10 < 5) {
          uVar18 = 0xc2;
          puVar15 = local_268;
          local_268[0] = (ushort)(byte)((char)(DAT_00450b94 / 10) + 0x31);
        }
        else {
          uVar18 = 0xae;
          local_268 = (ushort  [2])0x76727553;
          puVar15 = local_268;
          builtin_strncpy(local_264,"ival",5);
        }
      }
      else {
        uVar18 = 0xae;
        puVar15 = (ushort *)(*(int *)(iVar7 + 0x7d4) + 0x4d4617c + DAT_0044d024 * 0x990);
      }
      FUN_00401290(DAT_00455608,puVar15,0,0xff9b9b,uVar18,0x5b);
      if (_DAT_00450c30 == 2) {
        pcVar6 = "Easy";
LAB_0042ce37:
        FUN_00401290(DAT_00455608,pcVar6,0,0xff9b9b,0xae,0x73);
      }
      else {
        if (_DAT_00450c30 == 1) {
          pcVar6 = "Normal";
          goto LAB_0042ce37;
        }
        if (_DAT_00450c30 == 0) {
          pcVar6 = "Difficult";
          goto LAB_0042ce37;
        }
        if (_DAT_00450c30 == -1) {
          pcVar6 = "CRAZY!";
          goto LAB_0042ce37;
        }
      }
      piVar9 = local_a88;
      pcVar6 = (char *)(iVar7 + 4);
      piVar2 = (int *)(iVar7 + 0x194);
      puVar3 = &DAT_00451268;
      do {
        if (*pcVar6 != '\0') {
          iVar5 = *piVar2;
          if (*(char *)(iVar5 + 0xcd) == '\0') {
            if (*(char *)(iVar5 + 0xce) == '\0') {
              if (*(char *)(iVar5 + 0xd0) == '\0') {
                if (*(char *)(iVar5 + 0xcf) == '\0') {
                  if (*(char *)(iVar5 + 0xd1) == '\0') {
                    *puVar3 = (uint)(*(char *)(iVar5 + 0xd2) != '\0');
                  }
                  else {
                    if ((*puVar3 == 0) && (local_a68 == 3)) {
                      local_a8c = (int *)0x1;
                    }
                    *puVar3 = 1;
                  }
                }
                else {
                  if ((*puVar3 == 0) && (local_a68 == 3)) {
                    local_a74 = (int *)0x1;
                  }
                  *puVar3 = 1;
                }
              }
              else {
                if ((*puVar3 == 0) && (local_a68 == 3)) {
                  local_a6c = (int *)0x1;
                }
                *puVar3 = 1;
              }
            }
            else {
              if ((*puVar3 == 0) && (local_a68 == 3)) {
                local_a84 = (int *)0x1;
              }
              *puVar3 = 1;
            }
          }
          else {
            if ((*puVar3 == 0) && (local_a68 == 3)) {
              local_a70 = (int *)0x1;
            }
            *puVar3 = 1;
          }
        }
        puVar3 = puVar3 + 1;
        pcVar6 = pcVar6 + 1;
        piVar2 = piVar2 + 1;
      } while ((int)puVar3 < 0x451288);
      if ((local_a70 != (int *)0x0) && (DAT_0044d06c = DAT_0044d06c + -1, DAT_0044d06c < 0)) {
        DAT_0044d06c = 5;
      }
      if (local_a84 != (int *)0x0) {
        DAT_0044d06c = (DAT_0044d06c + 1) % 6;
      }
      FUN_00402130(*local_a88,local_a74,local_a6c,uVar17);
      if (DAT_00450b98 == 0) {
        if (local_a8c != (int *)0x0) {
          if (DAT_0044d06c == 0) goto LAB_0042cf8a;
          goto LAB_0042d706;
        }
LAB_0042d791:
        iVar5 = local_a90;
      }
      else {
LAB_0042cf8a:
        DAT_00450bb0 = 0;
        DAT_00450bb4 = 0;
        if (*piVar9 == 1) {
          DAT_00450b9c = 0x46;
          DAT_00450ba8 = 0;
          DAT_00450bac = 0;
          DAT_00450ba4 = 0;
          DAT_0044d028 = 0;
          if (DAT_00450b94 == 0) {
            DAT_0044d024 = 1;
          }
          else if (DAT_00450b94 == 10) {
            DAT_0044d024 = 2;
          }
          else if (DAT_00450b94 == 0x14) {
            DAT_0044d024 = 3;
          }
          else if (DAT_00450b94 == 0x1e) {
            DAT_0044d024 = 4;
          }
          else if (DAT_00450b94 == 0x28) {
            DAT_0044d024 = 5;
          }
          else if (DAT_00450b94 == 0x32) {
            DAT_0044d024 = 6;
          }
          DAT_0044fb6c = 0xffffffff;
          DAT_00450ba0 = 0;
          DAT_0044f880 = 0xffffffff;
          DAT_00450bc8 = 0;
          DAT_00450bc4 = 0;
        }
        *local_a64 = 0;
        GetLocalTime(&local_290);
        sprintf(local_204,"%4d%02d%02d_%02d%02d%02d",(uint)local_290.wYear,
                (uint)local_290._0_4_ >> 0x10,(uint)local_290._4_4_ >> 0x10,(uint)local_290.wHour,
                (uint)local_290._8_4_ >> 0x10,(uint)local_290.wSecond);
        if (*piVar9 == 1) {
          if (DAT_00450b94 / 10 < 5) {
            sprintf(local_27c,"%d",DAT_00450b94 / 10 + 1);
            pcVar6 = &cStack_205;
            do {
              pcVar10 = pcVar6;
              pcVar6 = pcVar10 + 1;
            } while (pcVar10[1] != '\0');
            builtin_strncpy(pcVar10 + 1,"_Stage_",8);
            pcVar6 = local_27c;
            do {
              cVar4 = *pcVar6;
              pcVar6 = pcVar6 + 1;
            } while (cVar4 != '\0');
            uVar8 = (int)pcVar6 - (int)local_27c;
            pcVar6 = &cStack_205;
            do {
              pcVar10 = pcVar6 + 1;
              pcVar6 = pcVar6 + 1;
            } while (*pcVar10 != '\0');
            pcVar10 = local_27c;
            for (uVar11 = uVar8 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
              pcVar10 = pcVar10 + 4;
              pcVar6 = pcVar6 + 4;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *pcVar6 = *pcVar10;
              pcVar10 = pcVar10 + 1;
              pcVar6 = pcVar6 + 1;
            }
          }
          else {
            pcVar6 = &cStack_205;
            do {
              pcVar10 = pcVar6;
              pcVar6 = pcVar10 + 1;
            } while (pcVar10[1] != '\0');
            builtin_strncpy(pcVar10 + 1,"_Survival",10);
          }
        }
        if (*local_a88 == 0) {
          pcVar6 = &cStack_205;
          do {
            pcVar10 = pcVar6;
            pcVar6 = pcVar10 + 1;
          } while (pcVar10[1] != '\0');
          builtin_strncpy(pcVar10 + 1,"_VS",4);
        }
        sprintf(&DAT_0044fd98,"%s.lfr",local_204);
        DAT_00450b6c = 0;
        if (DAT_00450be4 != 0) {
          DAT_00450b70 = 1;
        }
        if (DAT_00450b98 == 0) {
          FUN_00401a30(0);
        }
        else {
          FUN_00415160(0,0,0x31a,0x226);
          DAT_00450b98 = 0;
        }
        iVar5 = local_a90;
        memset((void *)(local_a90 + 0xe),0,0x186);
        if ((DAT_0044d028 == 1) &&
           (DAT_0044d024 = FUN_00417170(0xda,*(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384) + -2),
           DAT_0044d024 == *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384) + -3)) {
          DAT_0044d024 = 99;
        }
        iVar7 = 0;
        piVar2 = (int *)(iVar5 + 0x194);
        local_a70 = (int *)DAT_0044d024;
        do {
          if ((&DAT_00451288)[iVar7] < 0xb) {
            if (0 < (&DAT_00451288)[iVar7]) {
              iVar1 = *piVar2;
              local_a84 = *(int **)(iVar1 + 0x364);
              iVar12 = *(int *)(iVar1 + 0x368);
              FUN_004061d0();
              iVar5 = local_a90;
              *(int *)(iVar1 + 0x368) = iVar12;
              uVar17 = *(undefined4 *)(iVar12 + 0x90);
              *(undefined8 *)(iVar1 + 0x58) = 0x4079000000000000;
              *(undefined8 *)(iVar1 + 0x60) = 0xc049000000000000;
              *(undefined4 *)(iVar1 + 0x31c) = uVar17;
              *(undefined8 *)(iVar1 + 0x68) = 0x4072c00000000000;
              *(int **)(*piVar2 + 0x364) = local_a84;
              iVar14 = (int)local_a70 * 0x990;
              *(undefined1 *)(local_a90 + 4 + iVar7) = 1;
              *(undefined4 *)(*piVar2 + 8) = 0x4b;
              iVar12 = FUN_00417170(0xdd,*(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d45db0 + iVar14)
                                         / 2);
              iVar1 = *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db0 + iVar14);
              *(int *)(*piVar2 + 0x10) = iVar12 + ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
              iVar1 = FUN_00417170(0xde,*(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db8 + iVar14) -
                                        *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db4 + iVar14));
              *(int *)(*piVar2 + 0x18) =
                   iVar1 + *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db4 + iVar14);
              *(undefined4 *)(*piVar2 + 0x14) = 0;
              *(double *)(*piVar2 + 0x58) = (double)*(int *)(*piVar2 + 0x10);
              *(double *)(*piVar2 + 0x68) = (double)*(int *)(*piVar2 + 0x18);
              *(undefined8 *)(*piVar2 + 0x60) = 0;
              *(undefined4 *)(*piVar2 + 0x308) = 200;
              if (*local_a88 == 1) {
                *(undefined4 *)(*piVar2 + 0x308) = 500;
              }
              *(int *)(*piVar2 + 0x354) = iVar7;
            }
          }
          else {
            local_a84 = *(int **)(*piVar2 + 0x364);
            iVar1 = piVar2[10];
            iVar12 = *(int *)(*piVar2 + 0x368);
            FUN_004061d0();
            iVar5 = local_a90;
            *(int *)(iVar1 + 0x368) = iVar12;
            uVar17 = *(undefined4 *)(iVar12 + 0x90);
            *(undefined8 *)(iVar1 + 0x58) = 0x4075e00000000000;
            *(undefined8 *)(iVar1 + 0x60) = 0;
            *(undefined4 *)(iVar1 + 0x31c) = uVar17;
            *(undefined8 *)(iVar1 + 0x68) = 0x4072c00000000000;
            *(int **)(piVar2[10] + 0x364) = local_a84;
            iVar14 = (int)local_a70 * 0x990;
            *(undefined1 *)(local_a90 + 0xe + iVar7) = 1;
            *(undefined4 *)(piVar2[10] + 8) = 0x4b;
            iVar12 = FUN_00417170(0xdb,*(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d45db0 + iVar14) /
                                       2);
            iVar1 = *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db0 + iVar14);
            *(int *)(piVar2[10] + 0x10) = iVar12 + ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
            iVar1 = FUN_00417170(0xdc,*(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db8 + iVar14) -
                                      *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db4 + iVar14));
            *(int *)(piVar2[10] + 0x18) =
                 iVar1 + *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d45db4 + iVar14);
            *(undefined4 *)(piVar2[10] + 0x14) = 0;
            *(double *)(piVar2[10] + 0x58) = (double)*(int *)(piVar2[10] + 0x10);
            *(double *)(piVar2[10] + 0x68) = (double)*(int *)(piVar2[10] + 0x18);
            *(undefined8 *)(piVar2[10] + 0x60) = 0;
            *(undefined4 *)(piVar2[10] + 0x308) = 200;
            if (*local_a88 == 1) {
              *(undefined4 *)(piVar2[10] + 0x308) = 500;
            }
            *(int *)(piVar2[10] + 0x354) = iVar7 + 10;
          }
          iVar7 = iVar7 + 1;
          piVar2 = piVar2 + 1;
        } while (iVar7 < 8);
        iVar7 = 10;
        piVar2 = (int *)(iVar5 + 0x198);
        iVar1 = 0x50;
        do {
          if ((*(char *)(iVar5 + -6 + iVar7) != '\0') && (*(int *)(piVar2[-1] + 0x364) == 0)) {
            *(int *)(piVar2[-1] + 0x364) = iVar7;
          }
          if ((*(char *)(iVar5 + -5 + iVar7) != '\0') && (*(int *)(*piVar2 + 0x364) == 0)) {
            *(int *)(*piVar2 + 0x364) = iVar7 + 1;
          }
          if ((*(char *)(iVar5 + -4 + iVar7) != '\0') && (*(int *)(piVar2[1] + 0x364) == 0)) {
            *(int *)(piVar2[1] + 0x364) = iVar7 + 2;
          }
          if ((*(char *)(iVar5 + -3 + iVar7) != '\0') && (*(int *)(piVar2[2] + 0x364) == 0)) {
            *(int *)(piVar2[2] + 0x364) = iVar7 + 3;
          }
          if ((*(char *)(iVar5 + -2 + iVar7) != '\0') && (*(int *)(piVar2[3] + 0x364) == 0)) {
            *(int *)(piVar2[3] + 0x364) = iVar7 + 4;
          }
          piVar2 = piVar2 + 5;
          iVar7 = iVar7 + 5;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
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
        if (0 < *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384)) {
          iVar7 = 0;
          do {
            FUN_0040c0e0(iVar7);
            iVar7 = iVar7 + 1;
          } while (iVar7 < *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384));
        }
        if (DAT_0044d024 != 99) {
          FUN_0040c030(DAT_0044d024);
        }
        piVar2 = local_a88;
        iVar7 = 0;
        DAT_0044d034 = 1;
        DAT_00450bbc = 0;
        DAT_00450bdc = 0;
        if (*local_a88 == 1) {
          piVar9 = (int *)(iVar5 + 0x194);
          do {
            if ((*(char *)(iVar5 + 4 + iVar7) != '\0') &&
               (*(int *)(*(int *)(*piVar9 + 0x368) + 0x6f8) == 0)) {
              iVar1 = FUN_00417170(0xdf,0x1e);
              *(int *)(*piVar9 + 0x10) = iVar1 + 0x32;
              *(double *)(*piVar9 + 0x58) = (double)*(int *)(*piVar9 + 0x10);
            }
            iVar7 = iVar7 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar7 < 400);
        }
        if (*piVar2 == 0) {
          FUN_004025b0();
        }
        iVar7 = 0x14;
        do {
          if (*(char *)(iVar5 + 4 + iVar7) == '\0') {
            FUN_004061d0();
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < 400);
        FUN_00431c70();
        FUN_0043d2c0(*local_a88,iVar5 + 4,iVar5 + 0x194);
LAB_0042d706:
        if (local_a8c == (int *)0x0) goto LAB_0042d791;
        if (DAT_0044d06c == 4) {
          _DAT_00450c30 = _DAT_00450c30 + -1;
          if (((_DAT_00450c30 < 0) && (DAT_00458428 == 0)) || (_DAT_00450c30 < -1)) {
            _DAT_00450c30 = 2;
          }
          FUN_00401a30(0);
        }
        if (DAT_0044d06c != 5) goto LAB_0042d791;
        FUN_00401a30(0);
        iVar5 = local_a90;
        *local_a64 = 10;
        DAT_00457580 = 0;
        FUN_00431c70();
      }
      if (DAT_00450c2c == 1) {
        FUN_004025d0();
        *local_a64 = 0;
        memset((void *)(iVar5 + 4),0,400);
        DAT_0044d028 = 1;
        DAT_0044d024 = FUN_00417170(0xe0,*(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384) + -2);
        if (DAT_0044d024 == *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384) + -3) {
          DAT_0044d024 = 99;
        }
        local_a70 = (int *)(iVar5 + 0x194);
        piVar2 = &DAT_00451248;
        do {
          iVar7 = 0;
          piVar9 = *(int **)(iVar5 + 0x7d4);
          iVar5 = 1;
          if (1 < piVar9[0x13608e0]) {
            iVar1 = *(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380);
            do {
              piVar9 = piVar9 + 1;
              if (((*(int *)(*piVar9 + 0x6f8) == 0) &&
                  (DAT_00451264 != iVar5 &&
                   (DAT_00451260 != iVar5 &&
                   (DAT_0045125c != iVar5 &&
                   (DAT_00451258 != iVar5 &&
                   (DAT_00451254 != iVar5 &&
                   (DAT_00451250 != iVar5 && (DAT_0045124c != iVar5 && DAT_00451248 != iVar5))))))))
                 && (*(int *)(*piVar9 + 0x6f4) < 0x1e)) {
                aiStack_a60[iVar7] = iVar5;
                iVar7 = iVar7 + 1;
              }
              iVar5 = iVar5 + 1;
            } while (iVar5 < iVar1);
          }
          iVar5 = FUN_00417170(0xe1,iVar7);
          iVar5 = aiStack_a60[iVar5];
          *piVar2 = iVar5;
          iVar7 = *local_a70;
          piVar2 = piVar2 + 1;
          local_a70 = local_a70 + 1;
          *(undefined4 *)(iVar7 + 0x368) = *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + iVar5 * 4);
          iVar5 = local_a90;
        } while ((int)piVar2 < 0x451268);
        iVar5 = 0;
        iVar7 = DAT_0044d024 * 0x990;
        DAT_00450c2c = 1;
        piVar2 = (int *)(local_a90 + 0x1bc);
        do {
          local_a70 = *(int **)(piVar2[-10] + 0x368);
          iVar1 = *piVar2;
          FUN_004061d0();
          iVar12 = local_a90;
          *(int **)(iVar1 + 0x368) = local_a70;
          uVar17 = *(undefined4 *)((int)local_a70 + 0x90);
          *(undefined8 *)(iVar1 + 0x58) = 0x4075e00000000000;
          *(undefined4 *)(iVar1 + 0x31c) = uVar17;
          *(undefined8 *)(iVar1 + 0x60) = 0;
          *(undefined8 *)(iVar1 + 0x68) = 0x4072c00000000000;
          *(undefined4 *)(*piVar2 + 8) = 0x4b;
          iVar14 = FUN_00417170(0xe2,*(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d45db0 + iVar7) / 2);
          iVar1 = *(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d45db0 + iVar7);
          *(int *)(*piVar2 + 0x10) = iVar14 + ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
          iVar1 = FUN_00417170(0xe3,*(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d45db8 + iVar7) -
                                    *(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d45db4 + iVar7));
          *(int *)(*piVar2 + 0x18) = iVar1 + *(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d45db4 + iVar7);
          iVar1 = iVar5 + 10;
          iVar5 = iVar5 + 1;
          *(double *)(*piVar2 + 0x58) = (double)*(int *)(*piVar2 + 0x10);
          *(double *)(*piVar2 + 0x68) = (double)*(int *)(*piVar2 + 0x18);
          *(undefined4 *)(*piVar2 + 0x308) = 200;
          *(int *)(*piVar2 + 0x354) = iVar1;
          piVar2 = piVar2 + 1;
        } while (iVar5 < 8);
        iVar5 = FUN_00417170(0xe4,0x1e);
        if (iVar5 < 7) {
          *(undefined1 *)(iVar12 + 0xe) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1bc) + 0x364) = 0;
          iVar5 = 1;
          piVar2 = (int *)(iVar12 + 0x1c0);
          do {
            uVar17 = FUN_00417170(0xe5,5);
            *(undefined4 *)(*piVar2 + 0x364) = uVar17;
            *(undefined1 *)(iVar12 + 0xe + iVar5) = 1;
            iVar5 = iVar5 + 1;
            piVar2 = piVar2 + 1;
          } while (iVar5 < 8);
        }
        else if (iVar5 < 0x12) {
          *(undefined4 *)(*(int *)(iVar12 + 0x1bc) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c0) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c4) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c8) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1cc) + 0x364) = 2;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d0) + 0x364) = 2;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d4) + 0x364) = 2;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d8) + 0x364) = 2;
          *(undefined4 *)(iVar12 + 0xe) = 0x1010101;
          *(undefined4 *)(iVar12 + 0x12) = 0x1010101;
          iVar5 = FUN_00417170(0xe6,3);
          if (iVar5 == 0) {
            *(undefined1 *)(iVar12 + 0x15) = 0;
            *(undefined1 *)(iVar12 + 0x11) = 0;
          }
          iVar5 = FUN_00417170(0xe7,6);
          if (iVar5 == 0) {
            *(undefined4 *)(*(int *)(iVar12 + 0x1d8) + 0x364) = 3;
            *(undefined4 *)(*(int *)(iVar12 + 0x1c8) + 0x364) = 3;
          }
        }
        else if (iVar5 < 0x19) {
          *(undefined4 *)(*(int *)(iVar12 + 0x1bc) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c0) + 0x364) = 1;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c4) + 0x364) = 2;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c8) + 0x364) = 2;
          *(undefined4 *)(*(int *)(iVar12 + 0x1cc) + 0x364) = 3;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d0) + 0x364) = 3;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d4) + 0x364) = 4;
          *(undefined4 *)(*(int *)(iVar12 + 0x1d8) + 0x364) = 4;
          iVar5 = FUN_00417170(0xe8,3);
          _Size = iVar5 * 2 + 4;
          if (0 < (int)_Size) goto LAB_0042dc51;
        }
        else {
          *(undefined4 *)(*(int *)(iVar12 + 0x1bc) + 0x364) = 0;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c0) + 0x364) = 0;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c4) + 0x364) = 0;
          *(undefined4 *)(*(int *)(iVar12 + 0x1c8) + 0x364) = 0;
          iVar5 = FUN_00417170(0xe9,3);
          _Size = iVar5 + 2;
          if (0 < (int)_Size) {
LAB_0042dc51:
            memset((void *)(iVar12 + 0xe),1,_Size);
          }
        }
        iVar5 = 10;
        piVar2 = (int *)(iVar12 + 0x198);
        iVar7 = 0x50;
        do {
          if ((*(char *)(iVar5 + -6 + iVar12) != '\0') && (*(int *)(piVar2[-1] + 0x364) == 0)) {
            *(int *)(piVar2[-1] + 0x364) = iVar5;
          }
          if ((*(char *)(iVar5 + -5 + iVar12) != '\0') && (*(int *)(*piVar2 + 0x364) == 0)) {
            *(int *)(*piVar2 + 0x364) = iVar5 + 1;
          }
          if ((*(char *)(iVar5 + -4 + iVar12) != '\0') && (*(int *)(piVar2[1] + 0x364) == 0)) {
            *(int *)(piVar2[1] + 0x364) = iVar5 + 2;
          }
          if ((*(char *)(iVar5 + -3 + iVar12) != '\0') && (*(int *)(piVar2[2] + 0x364) == 0)) {
            *(int *)(piVar2[2] + 0x364) = iVar5 + 3;
          }
          if ((*(char *)(iVar5 + -2 + iVar12) != '\0') && (*(int *)(piVar2[3] + 0x364) == 0)) {
            *(int *)(piVar2[3] + 0x364) = iVar5 + 4;
          }
          piVar2 = piVar2 + 5;
          iVar5 = iVar5 + 5;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
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
        if (0 < *(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d82384)) {
          iVar5 = 0;
          do {
            FUN_0040c0e0(iVar5);
            iVar5 = iVar5 + 1;
          } while (iVar5 < *(int *)(*(int *)(iVar12 + 0x7d4) + 0x4d82384));
        }
        if (DAT_0044d024 != 99) {
          FUN_0040c030(DAT_0044d024);
        }
        DAT_0044d034 = 1;
        DAT_00450bbc = 0;
        FUN_00415160(0,0,0x31a,0x226,0);
        DAT_00450bdc = 0;
        iVar5 = local_a90;
      }
      if (local_a8c != (int *)0x0) {
        if (DAT_0044d06c == 1) {
          FUN_00401a30(0);
          DAT_00451288 = 0;
          DAT_00451268 = 1;
          if (DAT_00451228 == 1) {
            DAT_00451248 = -1;
          }
          DAT_0045128c = 0;
          DAT_0045126c = 1;
          if (DAT_0045122c == 1) {
            DAT_0045124c = -1;
          }
          DAT_00451290 = 0;
          _DAT_00451270 = 1;
          if (DAT_00451230 == 1) {
            DAT_00451250 = -1;
          }
          DAT_00451294 = 0;
          _DAT_00451274 = 1;
          if (DAT_00451234 == 1) {
            DAT_00451254 = -1;
          }
          DAT_00451298 = 0;
          _DAT_00451278 = 1;
          if (DAT_00451238 == 1) {
            DAT_00451258 = -1;
          }
          DAT_0045129c = 0;
          _DAT_0045127c = 1;
          if (DAT_0045123c == 1) {
            DAT_0045125c = -1;
          }
          DAT_004512a0 = 0;
          _DAT_00451280 = 1;
          if (DAT_00451240 == 1) {
            DAT_00451260 = -1;
          }
          DAT_004512a4 = 0;
          _DAT_00451284 = 1;
          if (DAT_00451244 == 1) {
            DAT_00451264 = -1;
          }
          DAT_0044d078 = 0x96;
          DAT_004512c8 = 0;
        }
        if (DAT_0044d06c == 3) {
          if (*local_a88 == 1) {
            FUN_00401a30(0);
            DAT_00450b94 = DAT_00450b94 + 10;
            if (DAT_00450b94 == 0x3c) {
              DAT_00450b94 = 0;
            }
            if (DAT_0044d06c != 3) goto LAB_0042df64;
          }
          if (*local_a88 == 1) goto LAB_0042e0b6;
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
            if (DAT_0044d024 == *(int *)(*(int *)(iVar5 + 0x7d4) + 0x4d82384)) {
              DAT_0044d024 = 100;
              DAT_0044d028 = 1;
            }
          }
        }
LAB_0042df64:
        if (DAT_0044d06c == 2) {
          FUN_00401a30(0);
          local_a84 = (int *)(iVar5 + 0x194);
          local_a70 = (int *)0x0;
          do {
            piVar2 = local_a70;
            iVar1 = 0;
            iVar7 = 1;
            if (*(int *)((int)&DAT_00451228 + (int)local_a70) != 0) {
              piVar9 = *(int **)(iVar5 + 0x7d4);
              if (1 < piVar9[0x13608e0]) {
                iVar5 = *(int *)(*(int *)(local_a90 + 0x7d4) + 0x4d82380);
                do {
                  piVar9 = piVar9 + 1;
                  if (((*(int *)(*piVar9 + 0x6f8) == 0) &&
                      (DAT_00451264 != iVar7 &&
                       (DAT_00451260 != iVar7 &&
                       (DAT_0045125c != iVar7 &&
                       (DAT_00451258 != iVar7 &&
                       (DAT_00451254 != iVar7 &&
                       (DAT_00451250 != iVar7 && (DAT_0045124c != iVar7 && DAT_00451248 != iVar7))))
                       )))) && (*(int *)(*piVar9 + 0x6f4) < 0x1e)) {
                    aiStack_a60[iVar1] = iVar7;
                    iVar1 = iVar1 + 1;
                  }
                  iVar7 = iVar7 + 1;
                } while (iVar7 < iVar5);
              }
              iVar5 = FUN_00417170(0xea,iVar1);
              iVar5 = aiStack_a60[iVar5];
              *(int *)((int)&DAT_00451248 + (int)piVar2) = iVar5;
              *(undefined4 *)(*local_a84 + 0x368) =
                   *(undefined4 *)(*(int *)(local_a90 + 0x7d4) + iVar5 * 4);
              iVar5 = local_a90;
            }
            local_a84 = local_a84 + 1;
            local_a70 = (int *)((int)piVar2 + 4);
          } while ((int)local_a70 < 0x20);
        }
      }
    }
  }
LAB_0042e0b6:
  if ((DAT_0044d078 < 1) && (DAT_004512c8 == 0)) {
    DAT_004512c8 = 1;
  }
LAB_0042e0d2:
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_a90);
  return;
}

