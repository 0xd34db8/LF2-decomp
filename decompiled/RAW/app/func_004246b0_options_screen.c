/* Function: FUN_004246b0 */
/* Address: 0x004246b0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004246b0(undefined4 param_1)

{
  char cVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  void *pvVar5;
  DWORD DVar6;
  int *in_ECX;
  int iVar7;
  uint uVar8;
  int iVar9;
  char *pcVar10;
  undefined4 *puVar11;
  char *pcVar12;
  int *piVar13;
  undefined2 *puVar14;
  bool bVar15;
  undefined1 auStackY_450040 [4520964];
  void *local_410;
  int *local_40c;
  undefined1 *local_408;
  undefined4 local_404;
  int *local_400;
  int local_3fc;
  int local_3f8;
  char *local_3f4;
  char local_3f0 [20];
  char local_3dc [15];
  char acStack_3cd [13];
  char local_3c0 [32];
  char local_3a0 [31];
  undefined1 auStack_381 [11];
  undefined1 local_376;
  undefined1 local_374;
  char local_360 [44];
  undefined1 local_334;
  char local_31c;
  char local_31b;
  char local_31a;
  char local_319;
  char local_318;
  char local_317;
  char local_316;
  char local_315;
  char acStack_2fc [48];
  char local_2cc [300];
  char local_1a0 [100];
  char local_13c [300];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00446080;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_410;
  ExceptionList = &local_c;
  local_404 = param_1;
  local_40c = in_ECX;
  if (*in_ECX == 1) {
    FUN_00423910();
    FUN_0043f010();
    *in_ECX = 2;
    FUN_004028a0();
    FUN_0043e940();
    goto LAB_004287de;
  }
  if (*in_ECX == 2) {
    FUN_0041bc90();
    DAT_00457580 = 0;
    goto LAB_004287de;
  }
  _DAT_004511f8 = 1 - _DAT_004511f8;
  if (DAT_0044d068 != 0) {
    local_410 = operator_new(0x1f50);
    local_4 = 0;
    if (local_410 == (void *)0x0) {
      DAT_00451170 = 0;
    }
    else {
      DAT_00451170 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    _DAT_0044fcc0 = 0x31;
    _DAT_0044fccb = 0x32;
    _DAT_0044fcd6 = 0x33;
    _DAT_0044fce1 = 0x34;
    _DAT_0044fcec = 0x35;
    _DAT_0044fcf7 = 0x36;
    _DAT_0044fd02 = 0x37;
    _DAT_0044fd0d = 0x38;
    local_410 = operator_new(0x1f50);
    local_4 = 1;
    if (local_410 == (void *)0x0) {
      DAT_004511a0 = 0;
    }
    else {
      DAT_004511a0 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 2;
    if (local_410 == (void *)0x0) {
      DAT_00451168 = 0;
    }
    else {
      DAT_00451168 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 3;
    if (local_410 == (void *)0x0) {
      DAT_00451178 = 0;
    }
    else {
      DAT_00451178 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 4;
    if (local_410 == (void *)0x0) {
      DAT_0045116c = 0;
    }
    else {
      DAT_0045116c = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 5;
    if (local_410 == (void *)0x0) {
      DAT_0045117c = 0;
    }
    else {
      DAT_0045117c = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 6;
    if (local_410 == (void *)0x0) {
      DAT_004511a4 = 0;
    }
    else {
      DAT_004511a4 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 7;
    if (local_410 == (void *)0x0) {
      DAT_00451188 = 0;
    }
    else {
      DAT_00451188 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 8;
    if (local_410 == (void *)0x0) {
      DAT_0045118c = 0;
    }
    else {
      DAT_0045118c = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 9;
    if (local_410 == (void *)0x0) {
      DAT_0045119c = 0;
    }
    else {
      DAT_0045119c = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 10;
    if (local_410 == (void *)0x0) {
      DAT_00451190 = 0;
    }
    else {
      DAT_00451190 = FUN_0043ee50();
    }
    *(undefined4 *)(DAT_0045119c + 0x10) = 0;
    *(undefined4 *)(DAT_0045119c + 0x7e0) = 0;
    *(undefined4 *)(DAT_0045119c + 0xfb0) = 0x12a;
    *(undefined4 *)(DAT_0045119c + 0x1780) = 0x84;
    *(undefined4 *)(DAT_0045119c + 0x14) = 299;
    *(undefined4 *)(DAT_0045119c + 0x7e4) = 0;
    *(undefined4 *)(DAT_0045119c + 0xfb4) = 0x12a;
    *(undefined4 *)(DAT_0045119c + 0x1784) = 0x84;
    *(undefined4 *)(DAT_0045119c + 0x18) = 0;
    *(undefined4 *)(DAT_0045119c + 0x7e8) = 0x85;
    *(undefined4 *)(DAT_0045119c + 0xfb8) = 0x12a;
    *(undefined4 *)(DAT_0045119c + 0x1788) = 0x84;
    *(undefined4 *)(DAT_0045119c + 0x1c) = 299;
    *(undefined4 *)(DAT_0045119c + 0x7ec) = 0x85;
    *(undefined4 *)(DAT_0045119c + 0xfbc) = 0x12a;
    *(undefined4 *)(DAT_0045119c + 0x178c) = 0x84;
    *(undefined4 *)(DAT_0045119c + 0xc) = 4;
    *(undefined4 *)(DAT_00451190 + 0x10) = 0;
    *(undefined4 *)(DAT_00451190 + 0x7e0) = 0;
    *(undefined4 *)(DAT_00451190 + 0xfb0) = 0x192;
    *(undefined4 *)(DAT_00451190 + 0x1780) = 0x42;
    *(undefined4 *)(DAT_00451190 + 0x14) = 0;
    *(undefined4 *)(DAT_00451190 + 0x7e4) = 0x43;
    *(undefined4 *)(DAT_00451190 + 0xfb4) = 0x192;
    *(undefined4 *)(DAT_00451190 + 0x1784) = 0x5b;
    *(undefined4 *)(DAT_00451190 + 0x18) = 0;
    *(undefined4 *)(DAT_00451190 + 0x7e8) = 0x9f;
    *(undefined4 *)(DAT_00451190 + 0xfb8) = 0x192;
    *(undefined4 *)(DAT_00451190 + 0x1788) = 0x9c;
    *(undefined4 *)(DAT_00451190 + 0x1c) = 0;
    *(undefined4 *)(DAT_00451190 + 0x7ec) = 0x13c;
    *(undefined4 *)(DAT_00451190 + 0xfbc) = 0x1a3;
    *(undefined4 *)(DAT_00451190 + 0x178c) = 0xa9;
    *(undefined4 *)(DAT_00451190 + 0x20) = 0;
    *(undefined4 *)(DAT_00451190 + 0x7f0) = 0x1e6;
    local_4 = 0xffffffff;
    *(undefined4 *)(DAT_00451190 + 0xfc0) = 0x1a3;
    *(undefined4 *)(DAT_00451190 + 0x1790) = 0x41;
    *(undefined4 *)(DAT_00451190 + 0x24) = 0x193;
    *(undefined4 *)(DAT_00451190 + 0x7f4) = 0x35;
    *(undefined4 *)(DAT_00451190 + 0xfc4) = 0xf;
    *(undefined4 *)(DAT_00451190 + 0x1794) = 0xd;
    *(undefined4 *)(DAT_00451190 + 0xc) = 6;
    *(undefined4 *)(DAT_004511a0 + 0x10) = 0;
    *(undefined4 *)(DAT_004511a0 + 0x7e0) = 0;
    *(undefined4 *)(DAT_004511a0 + 0xfb0) = 0x31a;
    *(undefined4 *)(DAT_004511a0 + 0x1780) = 0x25;
    *(undefined4 *)(DAT_004511a0 + 0x14) = 0;
    *(undefined4 *)(DAT_004511a0 + 0x7e4) = 0x29;
    *(undefined4 *)(DAT_004511a0 + 0xfb4) = 0x1f0;
    *(undefined4 *)(DAT_004511a0 + 0x1784) = 0x50;
    *(undefined4 *)(DAT_004511a0 + 0x18) = 0;
    *(undefined4 *)(DAT_004511a0 + 0x7e8) = 0x7d;
    *(undefined4 *)(DAT_004511a0 + 0xfb8) = 0x11a;
    *(undefined4 *)(DAT_004511a0 + 0x1788) = 0x77;
    *(undefined4 *)(DAT_004511a0 + 0x1c) = 0;
    *(undefined4 *)(DAT_004511a0 + 0x7ec) = 0xf7;
    *(undefined4 *)(DAT_004511a0 + 0xfbc) = 0x130;
    *(undefined4 *)(DAT_004511a0 + 0x178c) = 0x7e;
    *(undefined4 *)(DAT_004511a0 + 0x20) = 0;
    *(undefined4 *)(DAT_004511a0 + 0x7f0) = 0x178;
    *(undefined4 *)(DAT_004511a0 + 0xfc0) = 0x16b;
    *(undefined4 *)(DAT_004511a0 + 0x1790) = 0x7b;
    *(undefined4 *)(DAT_004511a0 + 0x24) = 500;
    *(undefined4 *)(DAT_004511a0 + 0x7f4) = 0x2a;
    *(undefined4 *)(DAT_004511a0 + 0xfc4) = 0x123;
    *(undefined4 *)(DAT_004511a0 + 0x1794) = 0x1b;
    *(undefined4 *)(DAT_004511a0 + 0x28) = 500;
    *(undefined4 *)(DAT_004511a0 + 0x7f8) = 0x48;
    *(undefined4 *)(DAT_004511a0 + 0xfc8) = 0x123;
    *(undefined4 *)(DAT_004511a0 + 0x1798) = 0x1b;
    *(undefined4 *)(DAT_004511a0 + 0x2c) = 0x217;
    *(undefined4 *)(DAT_004511a0 + 0x7fc) = 0x69;
    *(undefined4 *)(DAT_004511a0 + 0xfcc) = 0x100;
    *(undefined4 *)(DAT_004511a0 + 0x179c) = 0x1a;
    *(undefined4 *)(DAT_004511a0 + 0x30) = 0x217;
    *(undefined4 *)(DAT_004511a0 + 0x800) = 0x89;
    *(undefined4 *)(DAT_004511a0 + 0xfd0) = 0x100;
    *(undefined4 *)(DAT_004511a0 + 0x17a0) = 0x1a;
    *(undefined4 *)(DAT_004511a0 + 0x34) = 0x217;
    *(undefined4 *)(DAT_004511a0 + 0x804) = 0xa8;
    *(undefined4 *)(DAT_004511a0 + 0xfd4) = 0x100;
    *(undefined4 *)(DAT_004511a0 + 0x17a4) = 0x1d;
    *(undefined4 *)(DAT_004511a0 + 0x38) = 0x1cc;
    *(undefined4 *)(DAT_004511a0 + 0x808) = 0xcb;
    *(undefined4 *)(DAT_004511a0 + 0xfd8) = 0x14e;
    *(undefined4 *)(DAT_004511a0 + 0x17a8) = 0x6c;
    *(undefined4 *)(DAT_004511a0 + 0x3c) = 0x1cc;
    *(undefined4 *)(DAT_004511a0 + 0x80c) = 0x139;
    *(undefined4 *)(DAT_004511a0 + 0xfdc) = 0x14e;
    *(undefined4 *)(DAT_004511a0 + 0x17ac) = 0x6c;
    *(undefined4 *)(DAT_004511a0 + 0x40) = 0x283;
    *(undefined4 *)(DAT_004511a0 + 0x810) = 0x1aa;
    *(undefined4 *)(DAT_004511a0 + 0xfe0) = 0x97;
    *(undefined4 *)(DAT_004511a0 + 0x17b0) = 0x1a;
    *(undefined4 *)(DAT_004511a0 + 0x44) = 0x1e9;
    *(undefined4 *)(DAT_004511a0 + 0x814) = 0x1aa;
    *(undefined4 *)(DAT_004511a0 + 0xfe4) = 0x97;
    *(undefined4 *)(DAT_004511a0 + 0x17b4) = 0x1a;
    *(undefined4 *)(DAT_004511a0 + 0x48) = 0x1ea;
    *(undefined4 *)(DAT_004511a0 + 0x818) = 0x1ce;
    *(undefined4 *)(DAT_004511a0 + 0xfe8) = 0x130;
    *(undefined4 *)(DAT_004511a0 + 0x17b8) = 0x26;
    *(undefined4 *)(DAT_004511a0 + 0x4c) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x81c) = 0x7c;
    *(undefined4 *)(DAT_004511a0 + 0xfec) = 0x1d;
    *(undefined4 *)(DAT_004511a0 + 0x17bc) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x50) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x820) = 0x90;
    *(undefined4 *)(DAT_004511a0 + 0xff0) = 0x1d;
    *(undefined4 *)(DAT_004511a0 + 0x17c0) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x54) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x824) = 0xa4;
    *(undefined4 *)(DAT_004511a0 + 0xff4) = 0x1d;
    *(undefined4 *)(DAT_004511a0 + 0x17c4) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x58) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x828) = 0xb8;
    *(undefined4 *)(DAT_004511a0 + 0xff8) = 0x25;
    *(undefined4 *)(DAT_004511a0 + 0x17c8) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x5c) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x82c) = 0xcc;
    *(undefined4 *)(DAT_004511a0 + 0xffc) = 0x46;
    *(undefined4 *)(DAT_004511a0 + 0x17cc) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x60) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x830) = 0xe0;
    *(undefined4 *)(DAT_004511a0 + 0x1000) = 0x46;
    *(undefined4 *)(DAT_004511a0 + 0x17d0) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 100) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x834) = 0xf4;
    *(undefined4 *)(DAT_004511a0 + 0x1004) = 0x6e;
    *(undefined4 *)(DAT_004511a0 + 0x17d4) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x68) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x838) = 0x108;
    *(undefined4 *)(DAT_004511a0 + 0x1008) = 0x66;
    *(undefined4 *)(DAT_004511a0 + 0x17d8) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x6c) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x83c) = 0x11c;
    *(undefined4 *)(DAT_004511a0 + 0x100c) = 0x2d;
    *(undefined4 *)(DAT_004511a0 + 0x17dc) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0x70) = 0x13c;
    *(undefined4 *)(DAT_004511a0 + 0x840) = 0x130;
    *(undefined4 *)(DAT_004511a0 + 0x1010) = 0x25;
    *(undefined4 *)(DAT_004511a0 + 0x17e0) = 0x13;
    *(undefined4 *)(DAT_004511a0 + 0xc) = 0x19;
    *(undefined4 *)(DAT_00451168 + 0x10) = 0;
    *(undefined4 *)(DAT_00451168 + 0x7e0) = 0;
    *(undefined4 *)(DAT_00451168 + 0xfb0) = 0x2c0;
    *(undefined4 *)(DAT_00451168 + 0x1780) = 0x161;
    *(undefined4 *)(DAT_00451168 + 0x14) = 0;
    *(undefined4 *)(DAT_00451168 + 0x7e4) = 0x162;
    *(undefined4 *)(DAT_00451168 + 0xfb4) = 0x1ee;
    *(undefined4 *)(DAT_00451168 + 0x1784) = 0x17;
    *(undefined4 *)(DAT_00451168 + 0x18) = 0;
    *(undefined4 *)(DAT_00451168 + 0x7e8) = 0x17b;
    *(undefined4 *)(DAT_00451168 + 0xfb8) = 0x1ee;
    *(undefined4 *)(DAT_00451168 + 0x1788) = 0x17;
    *(undefined4 *)(DAT_00451168 + 0x1c) = 0;
    *(undefined4 *)(DAT_00451168 + 0x7ec) = 0x193;
    *(undefined4 *)(DAT_00451168 + 0xfbc) = 0x1d5;
    *(undefined4 *)(DAT_00451168 + 0x178c) = 0x29;
    *(undefined4 *)(DAT_00451168 + 0xc) = 4;
    *(undefined4 *)(DAT_00451178 + 0x10) = 0;
    *(undefined4 *)(DAT_00451178 + 0x7e0) = 0;
    *(undefined4 *)(DAT_00451178 + 0xfb0) = 0x14e;
    *(undefined4 *)(DAT_00451178 + 0x1780) = 0x6c;
    *(undefined4 *)(DAT_00451178 + 0x14) = 0;
    *(undefined4 *)(DAT_00451178 + 0x7e4) = 0x74;
    *(undefined4 *)(DAT_00451178 + 0xfb4) = 0x131;
    *(undefined4 *)(DAT_00451178 + 0x1784) = 0xd5;
    *(undefined4 *)(DAT_00451178 + 0x18) = 0x20;
    *(undefined4 *)(DAT_00451178 + 0x7e8) = 0x14b;
    *(undefined4 *)(DAT_00451178 + 0xfb8) = 0xd2;
    *(undefined4 *)(DAT_00451178 + 0x1788) = 0x16;
    *(undefined4 *)(DAT_00451178 + 0x1c) = 0x12;
    *(undefined4 *)(DAT_00451178 + 0x7ec) = 0x166;
    *(undefined4 *)(DAT_00451178 + 0xfbc) = 0xee;
    *(undefined4 *)(DAT_00451178 + 0x178c) = 0x18;
    *(undefined4 *)(DAT_00451178 + 0x20) = 0;
    *(undefined4 *)(DAT_00451178 + 0x7f0) = 0x181;
    *(undefined4 *)(DAT_00451178 + 0xfc0) = 0x113;
    *(undefined4 *)(DAT_00451178 + 0x1790) = 0x17;
    *(undefined4 *)(DAT_00451178 + 0x24) = 0;
    *(undefined4 *)(DAT_00451178 + 0x7f4) = 0x19c;
    *(undefined4 *)(DAT_00451178 + 0xfc4) = 0x113;
    *(undefined4 *)(DAT_00451178 + 0x1794) = 0x18;
    *(undefined4 *)(DAT_00451178 + 0x28) = 0x2a;
    *(undefined4 *)(DAT_00451178 + 0x7f8) = 0x1d2;
    *(undefined4 *)(DAT_00451178 + 0xfc8) = 0xbc;
    *(undefined4 *)(DAT_00451178 + 0x1798) = 0x17;
    *(undefined4 *)(DAT_00451178 + 0x2c) = 0x37;
    *(undefined4 *)(DAT_00451178 + 0x7fc) = 0x209;
    *(undefined4 *)(DAT_00451178 + 0xfcc) = 0xa5;
    *(undefined4 *)(DAT_00451178 + 0x179c) = 0x17;
    *(undefined4 *)(DAT_00451178 + 0x30) = 0x15c;
    *(undefined4 *)(DAT_00451178 + 0x800) = 0;
    *(undefined4 *)(DAT_00451178 + 0xfd0) = 0x130;
    *(undefined4 *)(DAT_00451178 + 0x17a0) = 0x9c;
    *(undefined4 *)(DAT_00451178 + 0x34) = 0x197;
    *(undefined4 *)(DAT_00451178 + 0x804) = 0xb7;
    *(undefined4 *)(DAT_00451178 + 0xfd4) = 0x7e;
    *(undefined4 *)(DAT_00451178 + 0x17a4) = 0x15;
    *(undefined4 *)(DAT_00451178 + 0x38) = 0x17b;
    *(undefined4 *)(DAT_00451178 + 0x808) = 0xce;
    *(undefined4 *)(DAT_00451178 + 0xfd8) = 0xba;
    *(undefined4 *)(DAT_00451178 + 0x17a8) = 0x15;
    *(undefined4 *)(DAT_00451178 + 0x3c) = 0x163;
    *(undefined4 *)(DAT_00451178 + 0x80c) = 0xe7;
    *(undefined4 *)(DAT_00451178 + 0xfdc) = 0xeb;
    *(undefined4 *)(DAT_00451178 + 0x17ac) = 0x15;
    *(undefined4 *)(DAT_00451178 + 0x40) = 0x14a;
    *(undefined4 *)(DAT_00451178 + 0x810) = 0xfe;
    *(undefined4 *)(DAT_00451178 + 0xfe0) = 0x117;
    *(undefined4 *)(DAT_00451178 + 0x17b0) = 0x16;
    *(undefined4 *)(DAT_00451178 + 0x44) = 0x160;
    *(undefined4 *)(DAT_00451178 + 0x814) = 0x116;
    *(undefined4 *)(DAT_00451178 + 0xfe4) = 0xe4;
    *(undefined4 *)(DAT_00451178 + 0x17b4) = 0x16;
    *(undefined4 *)(DAT_00451178 + 0x48) = 0x1a0;
    *(undefined4 *)(DAT_00451178 + 0x818) = 0x130;
    *(undefined4 *)(DAT_00451178 + 0xfe8) = 0x6f;
    *(undefined4 *)(DAT_00451178 + 0x17b8) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0x4c) = 0x15c;
    *(undefined4 *)(DAT_00451178 + 0x81c) = 0x9c;
    *(undefined4 *)(DAT_00451178 + 0xfec) = 0x130;
    *(undefined4 *)(DAT_00451178 + 0x17bc) = 10;
    *(undefined4 *)(DAT_00451178 + 0x50) = 0x16c;
    *(undefined4 *)(DAT_00451178 + 0x820) = 0x1c7;
    *(undefined4 *)(DAT_00451178 + 0xff0) = 0x1ad;
    *(undefined4 *)(DAT_00451178 + 0x17c0) = 6;
    *(undefined4 *)(DAT_00451178 + 0x54) = 0x16f;
    *(undefined4 *)(DAT_00451178 + 0x824) = 0x1d5;
    *(undefined4 *)(DAT_00451178 + 0xff4) = 0x3f;
    *(undefined4 *)(DAT_00451178 + 0x17c4) = 0x1a;
    *(undefined4 *)(DAT_00451178 + 0x58) = 0x1e7;
    *(undefined4 *)(DAT_00451178 + 0x828) = 0x1d5;
    *(undefined4 *)(DAT_00451178 + 0xff8) = 0x3f;
    *(undefined4 *)(DAT_00451178 + 0x17c8) = 0x1a;
    *(undefined4 *)(DAT_00451178 + 0x5c) = 0x25f;
    *(undefined4 *)(DAT_00451178 + 0x82c) = 0x1d5;
    *(undefined4 *)(DAT_00451178 + 0xffc) = 0x3f;
    *(undefined4 *)(DAT_00451178 + 0x17cc) = 0x1a;
    *(undefined4 *)(DAT_00451178 + 0x60) = 0x2d7;
    *(undefined4 *)(DAT_00451178 + 0x830) = 0x1d5;
    *(undefined4 *)(DAT_00451178 + 0x1000) = 0x3f;
    *(undefined4 *)(DAT_00451178 + 0x17d0) = 0x1a;
    *(undefined4 *)(DAT_00451178 + 100) = 0x11d;
    *(undefined4 *)(DAT_00451178 + 0x834) = 0x1ca;
    *(undefined4 *)(DAT_00451178 + 0x1004) = 0x3f;
    *(undefined4 *)(DAT_00451178 + 0x17d4) = 0x15;
    *(undefined4 *)(DAT_00451178 + 0x68) = 0x14a;
    *(undefined4 *)(DAT_00451178 + 0x838) = 0x14c;
    *(undefined4 *)(DAT_00451178 + 0x1008) = 0x117;
    *(undefined4 *)(DAT_00451178 + 0x17d8) = 0x16;
    *(undefined4 *)(DAT_00451178 + 0x6c) = 0x14a;
    *(undefined4 *)(DAT_00451178 + 0x83c) = 0x16b;
    *(undefined4 *)(DAT_00451178 + 0x100c) = 0x117;
    *(undefined4 *)(DAT_00451178 + 0x17dc) = 0x16;
    *(undefined4 *)(DAT_00451178 + 0x70) = 0x148;
    *(undefined4 *)(DAT_00451178 + 0x840) = 0x191;
    *(undefined4 *)(DAT_00451178 + 0x1010) = 0x84;
    *(undefined4 *)(DAT_00451178 + 0x17e0) = 0x29;
    *(undefined4 *)(DAT_00451178 + 0x74) = 0x1e8;
    *(undefined4 *)(DAT_00451178 + 0x844) = 400;
    *(undefined4 *)(DAT_00451178 + 0x1014) = 0xb0;
    *(undefined4 *)(DAT_00451178 + 0x17e4) = 0x29;
    *(undefined4 *)(DAT_00451178 + 0x78) = 0x2b4;
    *(undefined4 *)(DAT_00451178 + 0x848) = 0x7c;
    *(undefined4 *)(DAT_00451178 + 0x1018) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17e8) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x7c) = 0x296;
    *(undefined4 *)(DAT_00451178 + 0x84c) = 9;
    *(undefined4 *)(DAT_00451178 + 0x101c) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17ec) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x80) = 0x2b4;
    *(undefined4 *)(DAT_00451178 + 0x850) = 9;
    *(undefined4 *)(DAT_00451178 + 0x1020) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17f0) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x84) = 0x2d2;
    *(undefined4 *)(DAT_00451178 + 0x854) = 9;
    *(undefined4 *)(DAT_00451178 + 0x1024) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17f4) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x88) = 0x2f0;
    *(undefined4 *)(DAT_00451178 + 0x858) = 9;
    *(undefined4 *)(DAT_00451178 + 0x1028) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17f8) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x8c) = 0x296;
    *(undefined4 *)(DAT_00451178 + 0x85c) = 0x42;
    *(undefined4 *)(DAT_00451178 + 0x102c) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x17fc) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x90) = 0x2b4;
    *(undefined4 *)(DAT_00451178 + 0x860) = 0x42;
    *(undefined4 *)(DAT_00451178 + 0x1030) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1800) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x94) = 0x2d2;
    *(undefined4 *)(DAT_00451178 + 0x864) = 0x42;
    *(undefined4 *)(DAT_00451178 + 0x1034) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1804) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x98) = 0x2f0;
    *(undefined4 *)(DAT_00451178 + 0x868) = 0x42;
    *(undefined4 *)(DAT_00451178 + 0x1038) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1808) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0x9c) = 0x296;
    *(undefined4 *)(DAT_00451178 + 0x86c) = 0x7c;
    *(undefined4 *)(DAT_00451178 + 0x103c) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x180c) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0xa0) = 0x2d2;
    *(undefined4 *)(DAT_00451178 + 0x870) = 0x7c;
    *(undefined4 *)(DAT_00451178 + 0x1040) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1810) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0xa4) = 0xc;
    *(undefined4 *)(DAT_00451178 + 0x874) = 0x228;
    *(undefined4 *)(DAT_00451178 + 0x1044) = 0x182;
    *(undefined4 *)(DAT_00451178 + 0x1814) = 0x28;
    *(undefined4 *)(DAT_00451178 + 0xa8) = 0x21;
    *(undefined4 *)(DAT_00451178 + 0x878) = 0x1b6;
    *(undefined4 *)(DAT_00451178 + 0x1048) = 0xce;
    *(undefined4 *)(DAT_00451178 + 0x1818) = 0x18;
    *(undefined4 *)(DAT_00451178 + 0xac) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x87c) = 0xb4;
    *(undefined4 *)(DAT_00451178 + 0x104c) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x181c) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xb0) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x880) = 200;
    *(undefined4 *)(DAT_00451178 + 0x1050) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1820) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xb4) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x884) = 0xdc;
    *(undefined4 *)(DAT_00451178 + 0x1054) = 0x1d;
    *(undefined4 *)(DAT_00451178 + 0x1824) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xb8) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x888) = 0xf0;
    *(undefined4 *)(DAT_00451178 + 0x1058) = 0x25;
    *(undefined4 *)(DAT_00451178 + 0x1828) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xbc) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x88c) = 0x104;
    *(undefined4 *)(DAT_00451178 + 0x105c) = 0x46;
    *(undefined4 *)(DAT_00451178 + 0x182c) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xc0) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x890) = 0x118;
    *(undefined4 *)(DAT_00451178 + 0x1060) = 0x46;
    *(undefined4 *)(DAT_00451178 + 0x1830) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xc4) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x894) = 300;
    *(undefined4 *)(DAT_00451178 + 0x1064) = 0x6e;
    *(undefined4 *)(DAT_00451178 + 0x1834) = 0x13;
    *(undefined4 *)(DAT_00451178 + 200) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x898) = 0x140;
    *(undefined4 *)(DAT_00451178 + 0x1068) = 0x66;
    *(undefined4 *)(DAT_00451178 + 0x1838) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xcc) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x89c) = 0x154;
    *(undefined4 *)(DAT_00451178 + 0x106c) = 0x2d;
    *(undefined4 *)(DAT_00451178 + 0x183c) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xd0) = 0x276;
    *(undefined4 *)(DAT_00451178 + 0x8a0) = 0x168;
    *(undefined4 *)(DAT_00451178 + 0x1070) = 0x25;
    *(undefined4 *)(DAT_00451178 + 0x1840) = 0x13;
    *(undefined4 *)(DAT_00451178 + 0xd4) = 0;
    *(undefined4 *)(DAT_00451178 + 0x8a4) = 0x1ed;
    *(undefined4 *)(DAT_00451178 + 0x1074) = 0x115;
    *(undefined4 *)(DAT_00451178 + 0x1844) = 0x19;
    *(undefined4 *)(DAT_00451178 + 0xd8) = 0x125;
    *(undefined4 *)(DAT_00451178 + 0x8a8) = 0x1f8;
    *(undefined4 *)(DAT_00451178 + 0x1078) = 0x115;
    *(undefined4 *)(DAT_00451178 + 0x1848) = 0x19;
    *(undefined4 *)(DAT_00451178 + 0xdc) = 0x195;
    *(undefined4 *)(DAT_00451178 + 0x8ac) = 0x214;
    *(undefined4 *)(DAT_00451178 + 0x107c) = 0x115;
    *(undefined4 *)(DAT_00451178 + 0x184c) = 0x19;
    *(undefined4 *)(DAT_00451178 + 0xc) = 0x34;
    *(undefined4 *)(DAT_0045116c + 0x10) = 0;
    *(undefined4 *)(DAT_0045116c + 0x7e0) = 0;
    *(undefined4 *)(DAT_0045116c + 0xfb0) = 0x2c9;
    *(undefined4 *)(DAT_0045116c + 0x1780) = 0x14c;
    *(undefined4 *)(DAT_0045116c + 0x14) = 0;
    *(undefined4 *)(DAT_0045116c + 0x7e4) = 0x14f;
    *(undefined4 *)(DAT_0045116c + 0xfb4) = 0x28;
    *(undefined4 *)(DAT_0045116c + 0x1784) = 0x2d;
    *(undefined4 *)(DAT_0045116c + 0x18) = 0x2e;
    *(undefined4 *)(DAT_0045116c + 0x7e8) = 0x14f;
    *(undefined4 *)(DAT_0045116c + 0xfb8) = 0xeb;
    *(undefined4 *)(DAT_0045116c + 0x1788) = 0x6f;
    *(undefined4 *)(DAT_0045116c + 0x1c) = 0;
    *(undefined4 *)(DAT_0045116c + 0x7ec) = 0x1cd;
    *(undefined4 *)(DAT_0045116c + 0xfbc) = 0xab;
    *(undefined4 *)(DAT_0045116c + 0x178c) = 0x26;
    *(undefined4 *)(DAT_0045116c + 0x20) = 0xb7;
    *(undefined4 *)(DAT_0045116c + 0x7f0) = 0x1cd;
    *(undefined4 *)(DAT_0045116c + 0xfc0) = 0xad;
    *(undefined4 *)(DAT_0045116c + 0x1790) = 0x26;
    *(undefined4 *)(DAT_0045116c + 0x24) = 0x11c;
    *(undefined4 *)(DAT_0045116c + 0x7f4) = 0x14f;
    *(undefined4 *)(DAT_0045116c + 0xfc4) = 0x34;
    *(undefined4 *)(DAT_0045116c + 0x1794) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x28) = 0x156;
    *(undefined4 *)(DAT_0045116c + 0x7f8) = 0x14e;
    *(undefined4 *)(DAT_0045116c + 0xfc8) = 0x2f;
    *(undefined4 *)(DAT_0045116c + 0x1798) = 0x14;
    *(undefined4 *)(DAT_0045116c + 0x2c) = 0x11c;
    *(undefined4 *)(DAT_0045116c + 0x7fc) = 0x164;
    *(undefined4 *)(DAT_0045116c + 0xfcc) = 0x3b;
    *(undefined4 *)(DAT_0045116c + 0x179c) = 0x18;
    *(undefined4 *)(DAT_0045116c + 0x30) = 0x159;
    *(undefined4 *)(DAT_0045116c + 0x800) = 0x164;
    *(undefined4 *)(DAT_0045116c + 0xfd0) = 0x3b;
    *(undefined4 *)(DAT_0045116c + 0x17a0) = 0x18;
    *(undefined4 *)(DAT_0045116c + 0x34) = 0xaa;
    *(undefined4 *)(DAT_0045116c + 0x804) = 0;
    *(undefined4 *)(DAT_0045116c + 0xfd4) = 0x21f;
    *(undefined4 *)(DAT_0045116c + 0x17a4) = 0x14c;
    *(undefined4 *)(DAT_0045116c + 0x38) = 0x19e;
    *(undefined4 *)(DAT_0045116c + 0x808) = 0x154;
    *(undefined4 *)(DAT_0045116c + 0xfd8) = 0x11a;
    *(undefined4 *)(DAT_0045116c + 0x17a8) = 0xef;
    *(undefined4 *)(DAT_0045116c + 0x3c) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x80c) = 0;
    *(undefined4 *)(DAT_0045116c + 0xfdc) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17ac) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x40) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x810) = 0x15;
    *(undefined4 *)(DAT_0045116c + 0xfe0) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17b0) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x44) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x814) = 0x2a;
    *(undefined4 *)(DAT_0045116c + 0xfe4) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17b4) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x48) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x818) = 0x3f;
    *(undefined4 *)(DAT_0045116c + 0xfe8) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17b8) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x4c) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x81c) = 0x54;
    *(undefined4 *)(DAT_0045116c + 0xfec) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17bc) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x50) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x820) = 0x69;
    *(undefined4 *)(DAT_0045116c + 0xff0) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17c0) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x54) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x824) = 0x7e;
    *(undefined4 *)(DAT_0045116c + 0xff4) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17c4) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x58) = 0x2cd;
    *(undefined4 *)(DAT_0045116c + 0x828) = 0x93;
    *(undefined4 *)(DAT_0045116c + 0xff8) = 0xf;
    *(undefined4 *)(DAT_0045116c + 0x17c8) = 0x13;
    *(undefined4 *)(DAT_0045116c + 0x5c) = 0x8e;
    *(undefined4 *)(DAT_0045116c + 0x82c) = 0x1fc;
    *(undefined4 *)(DAT_0045116c + 0xffc) = 0x102;
    *(undefined4 *)(DAT_0045116c + 0x17cc) = 0x3a;
    *(undefined4 *)(DAT_0045116c + 0x60) = 0x120;
    *(undefined4 *)(DAT_0045116c + 0x830) = 0x182;
    *(undefined4 *)(DAT_0045116c + 0x1000) = 0x75;
    *(undefined4 *)(DAT_0045116c + 0x17d0) = 0x19;
    *(undefined4 *)(DAT_0045116c + 100) = 0x120;
    *(undefined4 *)(DAT_0045116c + 0x834) = 0x1a0;
    *(undefined4 *)(DAT_0045116c + 0x1004) = 0x3c;
    *(undefined4 *)(DAT_0045116c + 0x17d4) = 0x18;
    *(undefined4 *)(DAT_0045116c + 0x68) = 0;
    *(undefined4 *)(DAT_0045116c + 0x838) = 0x17f;
    *(undefined4 *)(DAT_0045116c + 0x1008) = 0x28;
    *(undefined4 *)(DAT_0045116c + 0x17d8) = 0x2d;
    *(undefined4 *)(DAT_0045116c + 0x6c) = 0;
    *(undefined4 *)(DAT_0045116c + 0x83c) = 0x1f9;
    *(undefined4 *)(DAT_0045116c + 0x100c) = 0x28;
    *(undefined4 *)(DAT_0045116c + 0x17dc) = 0x2d;
    *(undefined4 *)(DAT_0045116c + 0x70) = 2;
    *(undefined4 *)(DAT_0045116c + 0x840) = 0x24a;
    *(undefined4 *)(DAT_0045116c + 0x1010) = 0x2d5;
    *(undefined4 *)(DAT_0045116c + 0x17e0) = 0xc;
    *(undefined4 *)(DAT_0045116c + 0xc) = 0x19;
    *(undefined4 *)(DAT_0045117c + 0x10) = 0;
    *(undefined4 *)(DAT_0045117c + 0x7e0) = 0;
    *(undefined4 *)(DAT_0045117c + 0xfb0) = 0x11a;
    *(undefined4 *)(DAT_0045117c + 0x1780) = 0xb5;
    *(undefined4 *)(DAT_0045117c + 0x14) = 0x11d;
    *(undefined4 *)(DAT_0045117c + 0x7e4) = 0;
    *(undefined4 *)(DAT_0045117c + 0xfb4) = 0xf0;
    *(undefined4 *)(DAT_0045117c + 0x1784) = 0x1b;
    *(undefined4 *)(DAT_0045117c + 0x18) = 0x11d;
    *(undefined4 *)(DAT_0045117c + 0x7e8) = 0x20;
    *(undefined4 *)(DAT_0045117c + 0xfb8) = 0xf0;
    *(undefined4 *)(DAT_0045117c + 0x1788) = 0x1b;
    *(undefined4 *)(DAT_0045117c + 0x1c) = 0;
    *(undefined4 *)(DAT_0045117c + 0x7ec) = 0xcc;
    *(undefined4 *)(DAT_0045117c + 0xfbc) = 0x1a6;
    *(undefined4 *)(DAT_0045117c + 0x178c) = 0x58;
    *(undefined4 *)(DAT_0045117c + 0x20) = 0;
    *(undefined4 *)(DAT_0045117c + 0x7f0) = 0x129;
    *(undefined4 *)(DAT_0045117c + 0xfc0) = 0x1a6;
    *(undefined4 *)(DAT_0045117c + 0x1790) = 0x58;
    *(undefined4 *)(DAT_0045117c + 0x24) = 0x1d5;
    *(undefined4 *)(DAT_0045117c + 0x7f4) = 0x3e;
    *(undefined4 *)(DAT_0045117c + 0xfc4) = 0x144;
    *(undefined4 *)(DAT_0045117c + 0x1794) = 0x9b;
    *(undefined4 *)(DAT_0045117c + 0x28) = 0x1d5;
    *(undefined4 *)(DAT_0045117c + 0x7f8) = 0xdc;
    *(undefined4 *)(DAT_0045117c + 0xfc8) = 0x97;
    *(undefined4 *)(DAT_0045117c + 0x1798) = 0x1a;
    *(undefined4 *)(DAT_0045117c + 0x2c) = 0;
    *(undefined4 *)(DAT_0045117c + 0x7fc) = 0x185;
    *(undefined4 *)(DAT_0045117c + 0xfcc) = 0x212;
    *(undefined4 *)(DAT_0045117c + 0x179c) = 200;
    *(undefined4 *)(DAT_0045117c + 0x30) = 0x11c;
    *(undefined4 *)(DAT_0045117c + 0x800) = 0x3d;
    *(undefined4 *)(DAT_0045117c + 0xfd0) = 0x13;
    *(undefined4 *)(DAT_0045117c + 0x17a0) = 0xe;
    *(undefined4 *)(DAT_0045117c + 0x34) = 0x12f;
    *(undefined4 *)(DAT_0045117c + 0x804) = 0x3d;
    *(undefined4 *)(DAT_0045117c + 0xfd4) = 0x13;
    *(undefined4 *)(DAT_0045117c + 0x17a4) = 0xe;
    *(undefined4 *)(DAT_0045117c + 0x38) = 0x11c;
    *(undefined4 *)(DAT_0045117c + 0x808) = 0x4c;
    *(undefined4 *)(DAT_0045117c + 0xfd8) = 0x13;
    *(undefined4 *)(DAT_0045117c + 0x17a8) = 0xe;
    *(undefined4 *)(DAT_0045117c + 0x3c) = 0x12f;
    *(undefined4 *)(DAT_0045117c + 0x80c) = 0x4c;
    *(undefined4 *)(DAT_0045117c + 0xfdc) = 0x13;
    *(undefined4 *)(DAT_0045117c + 0x17ac) = 0xe;
    *(undefined4 *)(DAT_0045117c + 0xc) = 0xc;
    *(undefined4 *)(DAT_004511a4 + 0x10) = 0;
    *(undefined4 *)(DAT_004511a4 + 0x7e0) = 0;
    *(undefined4 *)(DAT_004511a4 + 0xfb0) = 0x2c0;
    *(undefined4 *)(DAT_004511a4 + 0x1780) = 0x138;
    *(undefined4 *)(DAT_004511a4 + 0x14) = 0;
    *(undefined4 *)(DAT_004511a4 + 0x7e4) = 0x168;
    *(undefined4 *)(DAT_004511a4 + 0xfb4) = 0x1b7;
    *(undefined4 *)(DAT_004511a4 + 0x1784) = 0x17;
    *(undefined4 *)(DAT_004511a4 + 0x18) = 0;
    *(undefined4 *)(DAT_004511a4 + 0x7e8) = 0x181;
    *(undefined4 *)(DAT_004511a4 + 0xfb8) = 0x1b7;
    *(undefined4 *)(DAT_004511a4 + 0x1788) = 0x17;
    *(undefined4 *)(DAT_004511a4 + 0x1c) = 0;
    *(undefined4 *)(DAT_004511a4 + 0x7ec) = 0x19b;
    *(undefined4 *)(DAT_004511a4 + 0xfbc) = 0x2c0;
    *(undefined4 *)(DAT_004511a4 + 0x178c) = 0x102;
    *(undefined4 *)(DAT_004511a4 + 0x20) = 0;
    *(undefined4 *)(DAT_004511a4 + 0x7f0) = 0x2a1;
    *(undefined4 *)(DAT_004511a4 + 0xfc0) = 0x21f;
    *(undefined4 *)(DAT_004511a4 + 0x1790) = 0x18;
    *(undefined4 *)(DAT_004511a4 + 0x24) = 0x224;
    *(undefined4 *)(DAT_004511a4 + 0x7f4) = 0x16b;
    *(undefined4 *)(DAT_004511a4 + 0xfc4) = 0x13;
    *(undefined4 *)(DAT_004511a4 + 0x1794) = 0x13;
    *(undefined4 *)(DAT_004511a4 + 0x28) = 0x23c;
    *(undefined4 *)(DAT_004511a4 + 0x7f8) = 0x16b;
    *(undefined4 *)(DAT_004511a4 + 0xfc8) = 0x13;
    *(undefined4 *)(DAT_004511a4 + 0x1798) = 0x13;
    *(undefined4 *)(DAT_004511a4 + 0x2c) = 0x1bb;
    *(undefined4 *)(DAT_004511a4 + 0x7fc) = 0x184;
    *(undefined4 *)(DAT_004511a4 + 0xfcc) = 0x157;
    *(undefined4 *)(DAT_004511a4 + 0x179c) = 0x16;
    *(undefined4 *)(DAT_004511a4 + 0xc) = 8;
    *(undefined4 *)(DAT_00451188 + 0x10) = 0;
    *(undefined4 *)(DAT_00451188 + 0x7e0) = 0;
    *(undefined4 *)(DAT_00451188 + 0xfb0) = 0x283;
    *(undefined4 *)(DAT_00451188 + 0x1780) = 0xa2;
    *(undefined4 *)(DAT_00451188 + 0x14) = 0;
    *(undefined4 *)(DAT_00451188 + 0x7e4) = 0xa3;
    *(undefined4 *)(DAT_00451188 + 0xfb4) = 0x283;
    *(undefined4 *)(DAT_00451188 + 0x1784) = 0x22;
    *(undefined4 *)(DAT_00451188 + 0x18) = 0;
    *(undefined4 *)(DAT_00451188 + 0x7e8) = 0xc6;
    *(undefined4 *)(DAT_00451188 + 0xfb8) = 0x283;
    *(undefined4 *)(DAT_00451188 + 0x1788) = 0x118;
    *(undefined4 *)(DAT_00451188 + 0x1c) = 0;
    *(undefined4 *)(DAT_00451188 + 0x7ec) = 0x1e2;
    *(undefined4 *)(DAT_00451188 + 0xfbc) = 0xea;
    *(undefined4 *)(DAT_00451188 + 0x178c) = 0x1d;
    *(undefined4 *)(DAT_00451188 + 0x20) = 0x100;
    *(undefined4 *)(DAT_00451188 + 0x7f0) = 0x1e2;
    *(undefined4 *)(DAT_00451188 + 0xfc0) = 0x58;
    *(undefined4 *)(DAT_00451188 + 0x1790) = 0x1d;
    *(undefined4 *)(DAT_00451188 + 0x24) = 0;
    *(undefined4 *)(DAT_00451188 + 0x7f4) = 0x204;
    *(undefined4 *)(DAT_00451188 + 0xfc4) = 0x168;
    *(undefined4 *)(DAT_00451188 + 0x1794) = 0x16;
    *(undefined4 *)(DAT_00451188 + 0x28) = 0x288;
    *(undefined4 *)(DAT_00451188 + 0x7f8) = 5;
    *(undefined4 *)(DAT_00451188 + 0xfc8) = 0x3e;
    *(undefined4 *)(DAT_00451188 + 0x1798) = 0xd;
    *(undefined4 *)(DAT_00451188 + 0x2c) = 0x288;
    *(undefined4 *)(DAT_00451188 + 0x7fc) = 0x1b;
    *(undefined4 *)(DAT_00451188 + 0xfcc) = 0x3e;
    *(undefined4 *)(DAT_00451188 + 0x179c) = 0xd;
    *(undefined4 *)(DAT_00451188 + 0x30) = 0x288;
    *(undefined4 *)(DAT_00451188 + 0x800) = 0x31;
    *(undefined4 *)(DAT_00451188 + 0xfd0) = 0x3e;
    *(undefined4 *)(DAT_00451188 + 0x17a0) = 0xd;
    *(undefined4 *)(DAT_00451188 + 0x34) = 0x288;
    *(undefined4 *)(DAT_00451188 + 0x804) = 0x47;
    *(undefined4 *)(DAT_00451188 + 0xfd4) = 0x3e;
    *(undefined4 *)(DAT_00451188 + 0x17a4) = 0xd;
    *(undefined4 *)(DAT_00451188 + 0x38) = 0x167;
    *(undefined4 *)(DAT_00451188 + 0x808) = 0x1e3;
    *(undefined4 *)(DAT_00451188 + 0xfd8) = 0x6c;
    *(undefined4 *)(DAT_00451188 + 0x17a8) = 0x12;
    *(undefined4 *)(DAT_00451188 + 0x3c) = 0x288;
    *(undefined4 *)(DAT_00451188 + 0x80c) = 0x5d;
    *(undefined4 *)(DAT_00451188 + 0xfdc) = 0x3e;
    *(undefined4 *)(DAT_00451188 + 0x17ac) = 0xd;
    *(undefined4 *)(DAT_00451188 + 0x40) = 0x174;
    *(undefined4 *)(DAT_00451188 + 0x810) = 0x1f7;
    *(undefined4 *)(DAT_00451188 + 0xfe0) = 0x47;
    *(undefined4 *)(DAT_00451188 + 0x17b0) = 9;
    *(undefined4 *)(DAT_00451188 + 0x44) = 0x173;
    *(undefined4 *)(DAT_00451188 + 0x814) = 0x202;
    *(undefined4 *)(DAT_00451188 + 0xfe4) = 0x93;
    *(undefined4 *)(DAT_00451188 + 0x17b4) = 10;
    *(undefined4 *)(DAT_00451188 + 0x48) = 0x173;
    *(undefined4 *)(DAT_00451188 + 0x818) = 0x20d;
    *(undefined4 *)(DAT_00451188 + 0xfe8) = 0x93;
    *(undefined4 *)(DAT_00451188 + 0x17b8) = 10;
    *(undefined4 *)(DAT_00451188 + 0xc) = 0xf;
    local_410 = operator_new(0x1f50);
    local_4 = 0xb;
    if (local_410 == (void *)0x0) {
      _DAT_00451198 = 0;
    }
    else {
      _DAT_00451198 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0xc;
    if (local_410 == (void *)0x0) {
      DAT_00451174 = 0;
    }
    else {
      DAT_00451174 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0xd;
    if (local_410 == (void *)0x0) {
      DAT_00451164 = 0;
    }
    else {
      DAT_00451164 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0xe;
    if (local_410 == (void *)0x0) {
      DAT_00451184 = 0;
    }
    else {
      DAT_00451184 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0xf;
    if (local_410 == (void *)0x0) {
      DAT_00451194 = 0;
    }
    else {
      DAT_00451194 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x10;
    if (local_410 == (void *)0x0) {
      DAT_00451180 = 0;
    }
    else {
      DAT_00451180 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x11;
    if (local_410 == (void *)0x0) {
      DAT_004511a8 = 0;
    }
    else {
      DAT_004511a8 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x12;
    if (local_410 == (void *)0x0) {
      DAT_0044faf4 = 0;
    }
    else {
      DAT_0044faf4 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x13;
    if (local_410 == (void *)0x0) {
      DAT_0044f888 = 0;
    }
    else {
      DAT_0044f888 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x14;
    if (local_410 == (void *)0x0) {
      DAT_0044fcbc = 0;
    }
    else {
      DAT_0044fcbc = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x15;
    if (local_410 == (void *)0x0) {
      DAT_0044fb68 = 0;
    }
    else {
      DAT_0044fb68 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x16;
    if (local_410 == (void *)0x0) {
      DAT_0044faf8 = 0;
    }
    else {
      DAT_0044faf8 = FUN_0043ee50();
    }
    local_4 = 0xffffffff;
    local_410 = operator_new(0x1f50);
    local_4 = 0x17;
    if (local_410 == (void *)0x0) {
      DAT_0044fd80 = 0;
    }
    else {
      DAT_0044fd80 = FUN_0043ee50();
    }
    *(undefined4 *)(DAT_0044faf4 + 0xc) = 0x100;
    *(undefined4 *)(DAT_0044f888 + 0xc) = 0x100;
    *(undefined4 *)(DAT_0044fcbc + 0xc) = 0x100;
    *(undefined4 *)(DAT_0044fb68 + 0xc) = 0x100;
    *(undefined4 *)(DAT_0044faf8 + 0xc) = 0x100;
    *(undefined4 *)(DAT_0044fd80 + 0xc) = 0x100;
    local_4 = 0xffffffff;
    local_408 = (undefined1 *)0x0;
    iVar4 = 0x7e0;
    do {
      iVar7 = ((uint)local_408 & 0xf) << 4;
      *(int *)(iVar4 + -2000 + DAT_0044faf4) = iVar7;
      iVar9 = ((uint)local_408 & 0xfffffff0) + 1;
      *(int *)(iVar4 + DAT_0044faf4) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044faf4) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044faf4) = 0x10;
      *(int *)(iVar4 + -2000 + DAT_0044f888) = iVar7;
      *(int *)(iVar4 + DAT_0044f888) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044f888) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044f888) = 0x10;
      *(int *)(iVar4 + -2000 + DAT_0044fcbc) = iVar7;
      *(int *)(iVar4 + DAT_0044fcbc) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044fcbc) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044fcbc) = 0x10;
      *(int *)(iVar4 + -2000 + DAT_0044fb68) = iVar7;
      *(int *)(iVar4 + DAT_0044fb68) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044fb68) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044fb68) = 0x10;
      *(int *)(iVar4 + -2000 + DAT_0044faf8) = iVar7;
      *(int *)(iVar4 + DAT_0044faf8) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044faf8) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044faf8) = 0x10;
      *(int *)(iVar4 + -2000 + DAT_0044fd80) = iVar7;
      *(int *)(iVar4 + DAT_0044fd80) = iVar9;
      *(undefined4 *)(iVar4 + 2000 + DAT_0044fd80) = 8;
      *(undefined4 *)(iVar4 + 4000 + DAT_0044fd80) = 0x10;
      local_408 = local_408 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar4 < 0xbe0);
    FUN_00423480();
    DAT_0044d068 = 0;
  }
  if (DAT_0044d064 == -2) {
    if (DAT_00450be8 == -1) {
      DAT_0044d064 = -3;
    }
    else {
      DAT_0044d064 = 0;
      if (DAT_00450be8 == 1) {
        FUN_004237e0();
      }
    }
  }
  FUN_00415160();
  if (DAT_004511ac == 0) {
    FUN_00423840();
  }
  FUN_0043f010();
  if (DAT_0044d064 == 0) {
    FUN_004236d0();
    iVar4 = DAT_0045757c;
    puVar11 = &DAT_004498d8;
    pcVar12 = local_3dc;
    for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined4 *)pcVar12 = *puVar11;
      puVar11 = puVar11 + 1;
      pcVar12 = pcVar12 + 4;
    }
    puVar11 = &DAT_004498b8;
    pcVar12 = local_3a0;
    for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined4 *)pcVar12 = *puVar11;
      puVar11 = puVar11 + 1;
      pcVar12 = pcVar12 + 4;
    }
    *(undefined2 *)pcVar12 = *(undefined2 *)puVar11;
    pcVar12[2] = *(char *)((int)puVar11 + 2);
    pcVar12 = "huvs:01zwx0OiuvoeGkjhugu.dqp";
    pcVar10 = local_3c0;
    for (iVar7 = 7; iVar7 != 0; iVar7 = iVar7 + -1) {
      *(undefined4 *)pcVar10 = *(undefined4 *)pcVar12;
      pcVar12 = pcVar12 + 4;
      pcVar10 = pcVar10 + 4;
    }
    pvVar5 = (void *)(DAT_0045757c + 0x1eb);
    *pcVar10 = *pcVar12;
    pcVar12 = local_3dc;
    do {
      cVar3 = *pcVar12;
      pcVar12 = pcVar12 + 1;
    } while (cVar3 != '\0');
    if (pcVar12 != local_3dc + 1) {
      uVar8 = 0;
      do {
        local_3dc[uVar8] = local_3dc[uVar8] - ((byte)uVar8 & 3);
        pcVar12 = local_3dc;
        uVar8 = uVar8 + 1;
        do {
          cVar3 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar3 != '\0');
      } while (uVar8 < (uint)((int)pcVar12 - (int)(local_3dc + 1)));
    }
    pcVar12 = local_3a0;
    do {
      cVar3 = *pcVar12;
      pcVar12 = pcVar12 + 1;
    } while (cVar3 != '\0');
    if (pcVar12 != local_3a0 + 1) {
      uVar8 = 0;
      do {
        local_3a0[uVar8] = local_3a0[uVar8] - ((byte)uVar8 & 3);
        pcVar12 = local_3a0;
        uVar8 = uVar8 + 1;
        do {
          cVar3 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar3 != '\0');
      } while (uVar8 < (uint)((int)pcVar12 - (int)(local_3a0 + 1)));
    }
    pcVar12 = local_3c0;
    do {
      cVar3 = *pcVar12;
      pcVar12 = pcVar12 + 1;
    } while (cVar3 != '\0');
    if (pcVar12 != local_3c0 + 1) {
      uVar8 = 0;
      do {
        local_3c0[uVar8] = local_3c0[uVar8] - ((byte)uVar8 & 3);
        pcVar12 = local_3c0;
        uVar8 = uVar8 + 1;
        do {
          cVar3 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar3 != '\0');
      } while (uVar8 < (uint)((int)pcVar12 - (int)(local_3c0 + 1)));
    }
    local_410 = pvVar5;
    FUN_00401290();
    FUN_00401290();
    FUN_00401290();
    if ((((0x24f < DAT_004546f0) && (iVar4 + 0x209 < DAT_00453cdc)) &&
        ((DAT_00453cdc < iVar4 + 0x227 || (DAT_0045757c == 0)))) &&
       ((FUN_00401290(), DAT_0044d060 == 0 && (DAT_00457580 == 1)))) {
      DAT_00457580 = 0;
      FUN_00401a30();
      Sleep(300);
      ShellExecuteA((HWND)0x0,"open","http://littlefighter.com",(LPCSTR)0x0,(LPCSTR)0x0,1);
    }
    if ((((0x263 < DAT_004546f0) && (DAT_004546f0 < 0x2ae)) && ((int)pvVar5 < DAT_00453cdc)) &&
       (DAT_00453cdc < iVar4 + 0x1ff)) {
      iVar7 = 0;
      do {
        cVar3 = local_3dc[iVar7 + 3];
        auStack_381[iVar7 + 1] = cVar3;
        iVar7 = iVar7 + 1;
      } while (cVar3 != '\0');
      local_376 = 0;
      FUN_00401290();
      if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
        DAT_00457580 = 0;
        FUN_00401a30();
        Sleep(300);
        ShellExecuteA((HWND)0x0,"open","http://martiwong.com",(LPCSTR)0x0,(LPCSTR)0x0,1);
      }
    }
    if (((0x2b4 < DAT_004546f0) && ((int)pvVar5 < DAT_00453cdc)) && (DAT_00453cdc < iVar4 + 0x1ff))
    {
      iVar4 = 0;
      do {
        cVar3 = acStack_3cd[iVar4];
        auStack_381[iVar4 + 1] = cVar3;
        iVar4 = iVar4 + 1;
      } while (cVar3 != '\0');
      local_374 = 0;
      FUN_00401290();
      if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
        DAT_00457580 = 0;
        FUN_00401a30();
        Sleep(300);
        ShellExecuteA((HWND)0x0,"open","http://lf2.net/starsky",(LPCSTR)0x0,(LPCSTR)0x0,1);
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    iVar4 = DAT_00458424;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    if ((iVar4 == 1) || (iVar4 == 2)) {
      FUN_0043f010();
    }
    else {
      if (DAT_00450be8 == 0) {
        FUN_0043f010();
      }
      else {
        FUN_0043f010();
      }
      if ((((0x2d4 < DAT_004546f0) && (DAT_00453cdc < 0x12)) && (FUN_0043f010(), DAT_0044d060 == 0))
         && (DAT_00457580 == 1)) {
        DAT_00457580 = 0;
        DAT_0044d064 = -3;
        FUN_00401a30();
      }
    }
    FUN_0043f010();
  }
  iVar4 = DAT_00453da4;
  if (DAT_0044d064 == -3) {
    if (DAT_004511f4 == 0) {
      iVar4 = 0x60;
    }
    else {
      iVar4 = (int)((ulonglong)((longlong)(DAT_004511f4 + 0x5a) * -0x2aaaaaab) >> 0x20);
      iVar4 = DAT_004511f4 + (iVar4 - (iVar4 >> 0x1f));
      DAT_004511f4 = iVar4;
    }
    FUN_0043f010();
    FUN_0043f010();
    if (((DAT_004546f0 - 0xd1U < 0xea) && (iVar4 + 0xae < DAT_00453cdc)) &&
       ((DAT_00453cdc < iVar4 + 0xcb && ((FUN_0043f010(), DAT_0044d060 == 0 && (DAT_00457580 == 1)))
        ))) {
      DAT_00457580 = 0;
      DAT_00450be8 = 1;
      FUN_00423230();
      DAT_0044d064 = 0;
      DAT_004511f4 = 0;
      FUN_00401a30();
      FUN_004237e0();
    }
    if ((((DAT_004546f0 - 0x1d1U < 0x58) && (iVar4 + 0xae < DAT_00453cdc)) &&
        (DAT_00453cdc < iVar4 + 0xcb)) &&
       ((FUN_0043f010(), DAT_0044d060 == 0 && (DAT_00457580 == 1)))) {
      DAT_00457580 = 0;
      DAT_00450be8 = 0;
      FUN_00423230();
      DAT_0044d064 = 0;
      DAT_004511f4 = 0;
      FUN_00401a30();
    }
    if (DAT_004511f4 == 0) {
      if (((DAT_004546f0 - 0xcbU < 0x167) && (iVar4 + 0xf0 < DAT_00453cdc)) &&
         (DAT_00453cdc < iVar4 + 0x106)) {
        FUN_0043f010();
        if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
          DAT_00457580 = 0;
          DAT_004511f4 = -0x11;
          FUN_00401a30();
        }
        if (DAT_004511f4 != 0) goto LAB_004277bd;
      }
      FUN_0043f010();
    }
    else {
LAB_004277bd:
      FUN_0043f010();
      FUN_0043f010();
    }
  }
  else if (DAT_0044d064 == -1) {
    FUN_0043f010();
    if ((_DAT_004511f0 & 1) == 0) {
      _DAT_004511f0 = _DAT_004511f0 | 1;
      _DAT_004511ec = timeGetTime();
    }
    DVar6 = timeGetTime();
    if (0x96 < DVar6 - _DAT_004511ec) {
      DAT_004511e8 = (DAT_004511e8 + 1) % 0xe;
      _DAT_004511ec = timeGetTime();
    }
    iVar4 = 0;
    if (0 < DAT_004511e8) {
      do {
        FUN_00415160();
        iVar4 = iVar4 + 1;
      } while (iVar4 < DAT_004511e8);
    }
    if (((((0x14a < DAT_004546f0) && (0x13f < DAT_00453cdc)) && (DAT_004546f0 < 0x1e2)) &&
        ((DAT_00453cdc < 0x15a && (FUN_0043f010(), DAT_0044d060 == 0)))) && (DAT_00457580 == 1)) {
      FUN_00401a30();
      DAT_00457580 = 0;
      DAT_0044d064 = 0;
    }
    _DAT_004511e4 = _DAT_004511e4 + 1;
  }
  else if (DAT_0044d064 == 0) {
    FUN_0043f010();
    iVar7 = 0;
    DAT_004511e0 = 0;
    if ((0x113 < DAT_004546f0) && (DAT_004546f0 < 0x209)) {
      if ((iVar4 + 0xd9 <= DAT_00453cdc) && (DAT_00453cdc <= iVar4 + 0xf1)) {
        iVar7 = 1;
      }
      local_410 = (void *)(iVar4 + 0xf7);
      if (((int)local_410 <= DAT_00453cdc) && (DAT_00453cdc <= iVar4 + 0x110)) {
        iVar7 = 2;
      }
      if ((iVar4 + 0x117 <= DAT_00453cdc) && (DAT_00453cdc <= iVar4 + 0x130)) {
        iVar7 = 3;
      }
      if ((iVar4 + 0x135 <= DAT_00453cdc) && (DAT_00453cdc <= iVar4 + 0x14e)) {
        iVar7 = 4;
      }
      if ((DAT_00453cdc < iVar4 + 0x153) || (iVar4 + 0x16c < DAT_00453cdc)) {
        if (iVar7 == 1) {
          FUN_0043f010();
          if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
            DAT_00457580 = 0;
            FUN_00401a30();
            DAT_004553bf = 0x75;
            DAT_0044d064 = 0;
            *local_40c = 1;
            FUN_00422ac0();
            DAT_00450b4c = 1;
            DAT_00450b50 = 2;
            DAT_00450b54 = 3;
            DAT_00450b58 = 4;
            FUN_00423b00();
            goto LAB_0042873e;
          }
        }
        else if (iVar7 == 2) {
          FUN_00422ac0();
          FUN_0043f010();
          if ((DAT_00457580 == 1) && (DAT_0044d060 == 0)) {
            DAT_00457580 = 0;
            FUN_00401a30();
            DAT_0044d064 = 1;
            iVar4 = FUN_00402b60();
            if (iVar4 == 0) {
              MessageBoxA((HWND)0x0,"InitWinSock()","Error",0);
              goto LAB_004287de;
            }
            memset(&DAT_0044f340,0,200);
            pcVar12 = inet_ntoa((in_addr)DAT_0044f264.S_un_b);
            pcVar10 = &DAT_0044f340;
            do {
              cVar3 = *pcVar12;
              *pcVar10 = cVar3;
              pcVar12 = pcVar12 + 1;
              pcVar10 = pcVar10 + 1;
            } while (cVar3 != '\0');
            iVar4 = bind(DAT_0044f1b4,(sockaddr *)&DAT_0044f58c,0x10);
            if (iVar4 == -1) {
              closesocket(DAT_0044f1b4);
              goto LAB_004287de;
            }
            iVar4 = listen(DAT_0044f1b4,5);
            if (iVar4 == -1) {
              MessageBoxA((HWND)0x0,"Listening() error","Error",0);
              closesocket(DAT_0044f1b4);
              goto LAB_004287de;
            }
          }
        }
        else if (iVar7 == 3) {
          FUN_0043f010();
          if ((DAT_00457580 == 1) && (DAT_0044d060 == 0)) {
            FUN_00401a30();
            DAT_0044d064 = 6;
            FUN_00423b00();
            goto LAB_0042873e;
          }
        }
        else if (iVar7 == 4) {
          FUN_0043f010();
          if ((DAT_00457580 == 1) && (DAT_0044d060 == 0)) {
            FUN_00401a30();
            DAT_0044d064 = 7;
            FUN_00423b00();
            goto LAB_0042873e;
          }
        }
        else if (iVar7 == 5) goto LAB_00427c3b;
      }
      else {
LAB_00427c3b:
        FUN_0043f010();
        if ((DAT_00457580 == 1) && (DAT_0044d060 == 0)) {
          FUN_00401a30();
          Sleep(300);
          ShellExecuteA((HWND)0x0,"open","http://littlefighter.com",(LPCSTR)0x0,(LPCSTR)0x0,1);
        }
      }
    }
    FUN_00423b00();
  }
  else if (DAT_0044d064 == 1) {
    if (DAT_004511ac == 0) {
      FUN_00423840();
    }
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    sprintf(local_2cc," Your IP Address: %s");
    FUN_00401290();
    if ((((DAT_004546f0 < 0x170) || (0x316 < DAT_004546f0)) || (DAT_00453cdc < 0x1c1)) ||
       (0x218 < DAT_00453cdc)) {
      FUN_0043f010();
    }
    else {
      FUN_0043f010();
      if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
        FUN_00401a30();
        Sleep(300);
        ShellExecuteA((HWND)0x0,"open","http://lf2.net/forum",(LPCSTR)0x0,(LPCSTR)0x0,1);
      }
    }
    iVar4 = 0;
    if ((0x103 < DAT_004546f0) && (DAT_004546f0 < 0x224)) {
      if ((0x111 < DAT_00453cdc) && (DAT_00453cdc < 0x12d)) {
        iVar4 = 1;
      }
      if ((0x130 < DAT_00453cdc) && (DAT_00453cdc < 0x14b)) {
        iVar4 = 2;
      }
      if ((DAT_00453cdc < 0x150) || (0x169 < DAT_00453cdc)) {
        if (iVar4 == 1) {
          FUN_0043f010();
          if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
            FUN_00401a30();
            DAT_0044d064 = 2;
          }
        }
        else if (iVar4 == 2) {
          FUN_0043f010();
          if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
            FUN_00401a30();
            DAT_0044d064 = 3;
            DAT_004511dc = 0;
            *(undefined1 *)(local_40c + 0x1f6) = 0;
          }
        }
        else if (iVar4 == 3) goto LAB_00427f17;
      }
      else {
LAB_00427f17:
        FUN_0043f010();
        if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
          FUN_00401a30();
          DAT_0044d064 = 0;
          DAT_0044d780 = 0xffffffff;
          FUN_00423910();
          FUN_00402d70();
        }
      }
    }
  }
  else if (DAT_0044d064 == 2) {
    if (DAT_004511ac == 0) {
      FUN_00423840();
    }
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    sprintf(local_2cc," Your IP Address: %s");
    FUN_00401290();
    FUN_0043f010();
    if ((_DAT_004511f0 & 2) == 0) {
      _DAT_004511f0 = _DAT_004511f0 | 2;
      _DAT_004511d8 = timeGetTime();
    }
    DVar6 = timeGetTime();
    if (0x96 < DVar6 - _DAT_004511d8) {
      DAT_004511d4 = (DAT_004511d4 + 1) % 0xe;
      _DAT_004511d8 = timeGetTime();
    }
    if (DAT_0044f1ae == '\x01') {
      *local_40c = 1;
    }
    if ((((0x141 < DAT_004546f0) && (DAT_004546f0 < 0x1d9)) && (0x168 < DAT_00453cdc)) &&
       (((DAT_00453cdc < 0x183 && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1)))) {
      FUN_00401a30();
      DAT_0044d064 = 1;
    }
    iVar4 = 0;
    if (0 < DAT_004511d4) {
      do {
        FUN_00415160();
        iVar4 = iVar4 + 1;
      } while (iVar4 < DAT_004511d4);
    }
  }
  else if (DAT_0044d064 == 3) {
    if (DAT_004511ac == 0) {
      FUN_00423840();
    }
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    sprintf(local_2cc," Your IP Address: %s");
    FUN_00401290();
    if (DAT_004511b0 == 0) {
      if (((DAT_004546f0 < 0xef) || (0x185 < DAT_004546f0)) ||
         ((DAT_00453cdc < 0x165 ||
          (((0x17e < DAT_00453cdc || (DAT_0044d060 != 0)) || (DAT_00457580 != 1)))))) {
        if (DAT_00455385 != 'd') {
          FUN_0043f010();
          if (((0x19a < DAT_004546f0) && (DAT_004546f0 < 0x232)) &&
             (((0x164 < DAT_00453cdc &&
               ((DAT_00453cdc < 0x17f && (FUN_0043f010(), DAT_0044d060 == 0)))) &&
              (DAT_00457580 == 1)))) {
            FUN_00401a30();
            DAT_0044d064 = 1;
          }
          if ((((0xee < DAT_004546f0) && (DAT_004546f0 < 0x186)) && (0x164 < DAT_00453cdc)) &&
             (DAT_00453cdc < 0x17f)) {
            FUN_0043f010();
          }
          sprintf(local_13c,"%s");
          FUN_00401290();
        }
      }
      else {
        DAT_00455385 = 'd';
      }
    }
    iVar4 = 0;
    do {
      if ((&DAT_00455378)[iVar4] == 'd') {
        cVar3 = FUN_00422f60();
        if (cVar3 == '\0') {
LAB_004283ad:
          if (iVar4 != 8) goto LAB_004283d0;
        }
        else if (iVar4 != 8) {
          if ((DAT_004511dc < 0x32) && (iVar4 != 0xd)) {
            *(char *)((int)local_40c + DAT_004511dc + 0x7d8) = cVar3;
            *(undefined1 *)((int)local_40c + DAT_004511dc + 0x7d9) = 0;
            DAT_004511dc = DAT_004511dc + 1;
            (&DAT_00455378)[iVar4] = 0x75;
            goto LAB_004283d0;
          }
          goto LAB_004283ad;
        }
        if (0 < DAT_004511dc) {
          (&DAT_00455378)[iVar4] = 0x75;
          *(undefined1 *)((int)local_40c + DAT_004511dc + 0x7d7) = 0;
          DAT_004511dc = DAT_004511dc + -1;
        }
      }
LAB_004283d0:
      iVar4 = iVar4 + 1;
    } while (iVar4 < 300);
    if (DAT_00455385 == 'd') {
      FUN_00401a30();
      DAT_00455385 = 'u';
      DAT_004511b0 = 1;
      FUN_0043f010();
    }
    else if (DAT_004511b0 == 1) {
      DAT_004511b0 = 0;
      closesocket(DAT_0044f46c);
      DAT_0044f46c = socket(2,1,6);
      if (DAT_0044f46c == 0xffffffff) {
        MessageBoxA((HWND)0x0,"socket()","Client Error",0);
        goto LAB_004287de;
      }
      piVar13 = local_40c + 0x1f6;
      DAT_0044f2d4 = gethostbyname((char *)piVar13);
      if (DAT_0044f2d4 == (hostent *)0x0) {
        local_410 = (void *)inet_addr((char *)piVar13);
        DAT_0044f2d4 = gethostbyaddr((char *)&local_410,4,2);
        if (DAT_0044f2d4 == (hostent *)0x0) {
          MessageBoxA((HWND)0x0,"Can\'t get the Server","Error",0);
          DAT_0044d064 = 1;
          goto LAB_0042873e;
        }
      }
      if (DAT_0044d064 != 1) {
        _DAT_0044f58c = 2;
        _DAT_0044f590 = *(undefined4 *)*DAT_0044f2d4->h_addr_list;
        _DAT_0044f58e = htons(0x3039);
        iVar4 = connect(DAT_0044f46c,(sockaddr *)&DAT_0044f58c,0x10);
        if (iVar4 == -1) {
          MessageBoxA((HWND)0x0,"Can\'t connect to server","Error",0);
          closesocket(DAT_0044f1b4);
          DAT_0044d064 = 1;
          goto LAB_004287de;
        }
        recv(DAT_0044f46c,local_1a0,100,0);
        iVar4 = 0xe;
        bVar15 = true;
        pcVar12 = local_1a0;
        pcVar10 = "u can connect";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar15 = *pcVar12 == *pcVar10;
          pcVar12 = pcVar12 + 1;
          pcVar10 = pcVar10 + 1;
        } while (bVar15);
        if (bVar15) {
          pcVar12 = "0000111100000000000000000000000000000000000000000000000000000000000000000000";
          pcVar10 = auStack_381 + 1;
          for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
            *(undefined4 *)pcVar10 = *(undefined4 *)pcVar12;
            pcVar12 = pcVar12 + 4;
            pcVar10 = pcVar10 + 4;
          }
          DAT_00450b5c = 1;
          DAT_00450b60 = 2;
          DAT_00450b64 = 3;
          DAT_00450b68 = 4;
          *pcVar10 = *pcVar12;
          memset(local_360,0x5f,0x2d);
          iVar4 = 0;
          do {
            pcVar12 = &DAT_0044fcc0 + iVar4;
            pcVar10 = pcVar12;
            do {
              cVar3 = *pcVar10;
              pcVar10[(int)(&DAT_0044fcec + (iVar4 - (int)pcVar12))] = cVar3;
              pcVar10 = pcVar10 + 1;
            } while (cVar3 != '\0');
            iVar7 = iVar4 - (int)pcVar12;
            do {
              cVar3 = *pcVar12;
              pcVar12[(int)(local_360 + iVar7)] = cVar3;
              pcVar12 = pcVar12 + 1;
            } while (cVar3 != '\0');
            iVar4 = iVar4 + 0xb;
          } while (iVar4 < 0x2c);
          iVar4 = 0;
          do {
            if (local_360[iVar4] == '\0') {
              local_360[iVar4] = '_';
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x2c);
          local_334 = 0;
          DAT_0044f1af = 1;
          send(DAT_0044f46c,auStack_381 + 1,0x4d,0);
          Sleep(500);
          recv(DAT_0044f46c,&local_31c,0x4d,0);
          Sleep(500);
          recv(DAT_0044f46c,&DAT_0044ff90,0xbb9,0);
          if (local_31c == '1') {
            DAT_00450b4c = 0xffffffff;
          }
          if (local_31b == '1') {
            DAT_00450b50 = 0xffffffff;
          }
          if (local_31a == '1') {
            DAT_00450b54 = 0xffffffff;
          }
          if (local_319 == '1') {
            DAT_00450b58 = 0xffffffff;
          }
          if (local_318 == '1') {
            DAT_00450b5c = 0xffffffff;
          }
          if (local_317 == '1') {
            DAT_00450b60 = 0xffffffff;
          }
          if (local_316 == '1') {
            DAT_00450b64 = 0xffffffff;
          }
          if (local_315 == '1') {
            DAT_00450b68 = 0xffffffff;
          }
          iVar4 = 0;
          do {
            cVar3 = acStack_2fc[iVar4];
            (&DAT_0044fcc0)[iVar4] = cVar3;
            if (cVar3 == '_') {
              (&DAT_0044fcc0)[iVar4] = 0;
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x2c);
          DAT_0044d064 = 4;
        }
      }
    }
  }
  else if (DAT_0044d064 == 4) {
    if ((_DAT_004511f0 & 4) == 0) {
      _DAT_004511f0 = _DAT_004511f0 | 4;
      _DAT_004511d0 = timeGetTime();
    }
    DVar6 = timeGetTime();
    if (0x96 < DVar6 - _DAT_004511d0) {
      DAT_004511cc = (DAT_004511cc + 1) % 0xe;
      _DAT_004511d0 = timeGetTime();
    }
    if (DAT_004511ac == 0) {
      FUN_00423840();
    }
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    FUN_0043f010();
    sprintf(local_13c," Your IP Address: %s");
    FUN_00401290();
    FUN_0043f010();
    if (((0x141 < DAT_004546f0) && (DAT_004546f0 < 0x1d9)) &&
       ((0x168 < DAT_00453cdc &&
        (((DAT_00453cdc < 0x183 && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1))))))
    {
      DAT_0044d064 = 1;
    }
    iVar4 = 0;
    if (0 < DAT_004511cc) {
      do {
        FUN_00415160();
        iVar4 = iVar4 + 1;
      } while (iVar4 < DAT_004511cc);
    }
    *local_40c = 1;
  }
  else if (DAT_0044d064 == 6) {
    FUN_0043f010();
    FUN_0043f010();
    if (((DAT_004546f0 < 0x2e) || (0x21c < DAT_004546f0)) ||
       ((DAT_00453cdc < 0x1db || (0x1f2 < DAT_00453cdc)))) {
      FUN_0043f010();
    }
    else {
      FUN_0043f010();
      if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
        FUN_00401a30();
        Sleep(300);
        ShellExecuteA((HWND)0x0,"open","http://www.littlefighter.com/control_index.html",(LPCSTR)0x0
                      ,(LPCSTR)0x0,1);
      }
    }
    if (0 < DAT_004511e0) {
      iVar4 = 0;
      if ((&DAT_0044fb70)[(DAT_004511e0 / 0x14) * 0x14] != 0) {
        pcVar12 = &DAT_00453fc4 + (&DAT_0044fb70)[(DAT_004511e0 / 0x14) * 0x14] * 0x30;
LAB_00428af0:
        if (*pcVar12 != '\x01') goto code_r0x00428af5;
        *(int *)(&DAT_0044fb7c + DAT_004511e0 * 4) = iVar4;
LAB_00428b09:
        DAT_004511e0 = 0;
        goto LAB_00428b0f;
      }
      do {
        if ((&DAT_00455378)[iVar4] == 'd') {
          (&DAT_0044fb70)[DAT_004511e0] = iVar4;
          goto LAB_00428b09;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0xfa);
    }
LAB_00428b0f:
    if (0 < DAT_004511c8) {
      iVar4 = 0;
      do {
        if ((&DAT_00455378)[iVar4] == 'd') {
          cVar3 = FUN_00422f60();
          iVar7 = DAT_004511c8 * 0xb;
          local_408 = (undefined1 *)(int)cVar3;
          pcVar12 = (char *)((int)&DAT_0044fcb4 + iVar7 + 1);
          pcVar10 = pcVar12;
          do {
            cVar1 = *pcVar10;
            pcVar10 = pcVar10 + 1;
          } while (cVar1 != '\0');
          iVar9 = (int)pcVar10 - (iVar7 + 0x44fcb6);
          if (local_408 == (undefined1 *)0x0) {
LAB_00428b99:
            if (iVar4 == 8) {
LAB_00428b9e:
              if (0 < iVar9) {
                *(undefined1 *)((int)&DAT_0044fcb4 + iVar7 + iVar9) = 0;
                goto LAB_00428ba9;
              }
            }
          }
          else {
            if (iVar4 == 8) goto LAB_00428b9e;
            do {
              cVar1 = *pcVar12;
              pcVar12 = pcVar12 + 1;
            } while (cVar1 != '\0');
            if ((9 < (uint)((int)pcVar12 - (iVar7 + 0x44fcb6))) || (iVar4 == 0xd))
            goto LAB_00428b99;
            *(char *)(iVar9 + 0x44fcb5 + iVar7) = cVar3;
            *(undefined1 *)(iVar9 + 0x44fcb6 + iVar7) = 0;
LAB_00428ba9:
            (&DAT_00455378)[iVar4] = 0x75;
          }
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 300);
    }
    local_408 = auStackY_450040;
    local_3f8 = 0;
    local_40c = (int *)0xc2;
    local_400 = &DAT_0044fb70;
    local_3fc = 1;
    local_3f4 = &DAT_0044fcc0;
    do {
      piVar13 = local_40c;
      if (((((int)local_40c <= DAT_004546f0) && (DAT_004546f0 <= (int)local_40c + 0x69)) &&
          (DAT_0044d060 == 0)) && ((DAT_00457580 == 1 && (DAT_00453cdc - 0xb6U < 0x5b)))) {
        DAT_004511e0 = 0;
        *local_400 = (*local_400 + 1) % 3;
      }
      if (DAT_004511c8 + -1 == local_3f8) {
        pcVar12 = local_3f4;
        do {
          cVar3 = *pcVar12;
          pcVar12 = pcVar12 + 1;
        } while (cVar3 != '\0');
        pcVar10 = local_3f4;
        if ((uint)((int)pcVar12 - (int)(local_3f4 + 1)) < 10) {
          do {
            cVar3 = *pcVar10;
            local_408[(int)pcVar10] = cVar3;
            pcVar10 = pcVar10 + 1;
          } while (cVar3 != '\0');
          puVar14 = (undefined2 *)auStack_381;
          do {
            pcVar12 = (char *)((int)puVar14 + 1);
            puVar14 = (undefined2 *)((int)puVar14 + 1);
          } while (*pcVar12 != '\0');
          *puVar14 = 0x5f;
        }
      }
      FUN_00401290();
      piVar2 = local_40c;
      if ((((int)piVar13 <= DAT_004546f0) && (DAT_004546f0 <= (int)piVar13 + 0x69)) &&
         ((DAT_00453cdc - 0x9cU < 0x12 && ((DAT_0044d060 == 0 && (DAT_00457580 == 1)))))) {
        DAT_004511c8 = local_3f8 + 1;
        DAT_004511e0 = 0;
      }
      iVar7 = 0;
      iVar4 = 0x11b;
      do {
        if ((((((int)local_40c <= DAT_004546f0) && (DAT_004546f0 <= (int)piVar2 + 0x69)) &&
             (DAT_0044d060 == 0)) && ((DAT_00457580 == 1 && (iVar4 + -3 <= DAT_00453cdc)))) &&
           (DAT_00453cdc <= iVar4 + 0xf)) {
          if ((*local_400 == 0) || (3 < iVar7)) {
            DAT_004511e0 = iVar7 + local_3fc;
          }
          DAT_004511c8 = 0;
        }
        if (*local_400 == 0) {
          FUN_00422b00();
          if (DAT_004511e0 == iVar7 + local_3fc) {
            FUN_00401290();
          }
          else {
            FUN_00401290();
          }
        }
        else if (iVar7 < 4) {
          FUN_00401290();
        }
        else {
          if (DAT_004511e0 == iVar7 + local_3fc) {
            sprintf(local_3f0,"Button: %d");
          }
          else {
            sprintf(local_3f0,"Button: %d");
          }
          FUN_00401290();
        }
        iVar4 = iVar4 + 0x16;
        iVar7 = iVar7 + 1;
      } while (iVar4 < 0x1b5);
      if (*local_400 == 0) {
        FUN_0043f010();
      }
      if (*local_400 == 1) {
        FUN_0043f010();
      }
      if (*local_400 == 2) {
        FUN_0043f010();
      }
      if (*local_400 == 3) {
        FUN_0043f010();
      }
      if (*local_400 == 4) {
        FUN_0043f010();
      }
      if (0x1b8 < DAT_00453cdc) {
        if ((((DAT_00453cdc < 0x1d2) && (DAT_004546f0 - 0x246U < 0x9c)) &&
            (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1)) {
          FUN_00401a30();
          FUN_00423480();
          DAT_0044d064 = 0;
          DAT_0044d780 = 0xffffffff;
          FUN_00423910();
        }
        if (((DAT_00453cdc - 0x1b9U < 0x19) && (DAT_004546f0 - 0x195U < 0x9c)) &&
           ((FUN_0043f010(), DAT_0044d060 == 0 && (DAT_00457580 == 1)))) {
          FUN_00401a30();
          FUN_00423230();
          DAT_0044d064 = 0;
          DAT_0044d780 = 0xffffffff;
          FUN_00423910();
        }
      }
      local_3f8 = local_3f8 + 1;
      local_408 = local_408 + -0xb;
      local_3fc = local_3fc + 0x14;
      local_400 = local_400 + 0x14;
      local_40c = (int *)((int)local_40c + 0x8b);
      local_3f4 = local_3f4 + 0xb;
    } while ((int)local_3f4 < 0x44fcec);
  }
  else if (DAT_0044d064 == 7) {
    FUN_0043f010();
    FUN_0043f010();
    if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
      if ((DAT_004546f0 < 0xd2) || (0x2da < DAT_004546f0)) {
LAB_004291ca:
        DAT_004511c4 = (char *)0x0;
      }
      else {
        if ((DAT_00453cdc < 0xcf) || (0xe1 < DAT_00453cdc)) {
          if (0x2da < DAT_004546f0) goto LAB_004291ca;
          if ((DAT_00453cdc < 0xe8) || (0x12e < DAT_00453cdc)) {
            if ((0x2da < DAT_004546f0) || ((DAT_00453cdc < 0x135 || (0x147 < DAT_00453cdc))))
            goto LAB_004291ca;
            DAT_004511c4 = &DAT_0044f890;
          }
          else {
            DAT_004511c4 = &DAT_0044f900;
          }
        }
        else {
          DAT_004511c4 = &DAT_0044fd18;
        }
LAB_004291e5:
        iVar4 = 0;
        do {
          if ((&DAT_00455378)[iVar4] == 'd') {
            cVar3 = FUN_00422f60();
            pcVar12 = DAT_004511c4;
            local_408 = (undefined1 *)(int)cVar3;
            if (iVar4 == 0xd) {
              local_408 = (undefined1 *)0xa;
LAB_00429225:
              pcVar10 = DAT_004511c4;
              do {
                cVar3 = *pcVar10;
                pcVar10 = pcVar10 + 1;
              } while (cVar3 != '\0');
              if ((pcVar10 != DAT_004511c4 + 1) || (local_408 != (undefined1 *)0xa)) {
                pcVar10 = DAT_004511c4;
                do {
                  cVar3 = *pcVar10;
                  pcVar10 = pcVar10 + 1;
                } while (cVar3 != '\0');
                *pcVar10 = '\0';
                do {
                  pcVar10 = pcVar12;
                  pcVar12 = pcVar10 + 1;
                } while (*pcVar10 != '\0');
                *pcVar10 = (char)local_408;
                (&DAT_00455378)[iVar4] = 0x75;
              }
            }
            else {
              if (local_408 == (undefined1 *)0x0) {
                if (iVar4 != 8) goto LAB_004292c0;
              }
              else if (iVar4 != 8) goto LAB_00429225;
              do {
                cVar3 = *pcVar12;
                pcVar12 = pcVar12 + 1;
              } while (cVar3 != '\0');
              if (pcVar12 != DAT_004511c4 + 1) {
                pcVar12 = DAT_004511c4;
                do {
                  pcVar10 = pcVar12;
                  pcVar12 = pcVar10 + 1;
                } while (*pcVar10 != '\0');
                pcVar10[-1] = '\0';
                (&DAT_00455378)[iVar4] = 0x75;
              }
            }
          }
LAB_004292c0:
          iVar4 = iVar4 + 1;
        } while (iVar4 < 0xfa);
      }
    }
    else if (DAT_004511c4 != (char *)0x0) goto LAB_004291e5;
    FUN_00423a70();
    FUN_00423a70();
    FUN_00423a70();
    if (DAT_00450be4 != 0) {
      FUN_0043f010();
    }
    if ((((0x11e < DAT_004546f0) && (0x185 < DAT_00453cdc)) && (DAT_004546f0 < 0x133)) &&
       (((DAT_00453cdc < 0x19a && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1)))) {
      DAT_00450be4 = 1 - DAT_00450be4;
    }
    if (((0x184 < DAT_004546f0) && (0x183 < DAT_00453cdc)) &&
       ((DAT_004546f0 < 0x2dd &&
        (((DAT_00453cdc < 0x19b && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1))))))
    {
      FUN_00401a30();
      Sleep(300);
      ShellExecuteA((HWND)0x0,"explore","recording",(LPCSTR)0x0,(LPCSTR)0x0,1);
    }
    if (((DAT_004546f0 < 0x2c) || (DAT_00453cdc < 0x1cd)) ||
       ((0x1e3 < DAT_004546f0 || (0x1e4 < DAT_00453cdc)))) {
      FUN_0043f010();
    }
    else {
      FUN_0043f010();
      if ((DAT_0044d060 == 0) && (DAT_00457580 == 1)) {
        FUN_00401a30();
        Sleep(300);
        ShellExecuteA((HWND)0x0,"open","http://www.littlefighter.com/record",(LPCSTR)0x0,(LPCSTR)0x0
                      ,1);
      }
    }
    if (0x19f < DAT_00453cdc) {
      if ((((DAT_00453cdc < 0x1b9) && (0x192 < DAT_004546f0)) && (DAT_004546f0 < 0x22f)) &&
         ((FUN_0043f010(), DAT_0044d060 == 0 && (DAT_00457580 == 1)))) {
        FUN_00423480();
        FUN_00401a30();
        DAT_0044d064 = 0;
        DAT_0044d780 = 0xffffffff;
        FUN_00423910();
      }
      if (((0x19f < DAT_00453cdc) && (DAT_00453cdc < 0x1b9)) &&
         ((0xe6 < DAT_004546f0 &&
          (((DAT_004546f0 < 0x183 && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1)))))
         ) {
        FUN_00423230();
        FUN_00401a30();
        DAT_0044d064 = 8;
      }
    }
  }
  else if (DAT_0044d064 == 8) {
    FUN_0043f010();
    FUN_0043f010();
    if (((0x5f < DAT_004546f0) && (0x15b < DAT_00453cdc)) &&
       (((DAT_004546f0 < 0x280 && ((DAT_00453cdc < 0x175 && (FUN_0043f010(), DAT_0044d060 == 0))))
        && (DAT_00457580 == 1)))) {
      FUN_00401a30();
      Sleep(300);
      ShellExecuteA((HWND)0x0,"open","http://www.littlefighter.com/challenge",(LPCSTR)0x0,
                    (LPCSTR)0x0,1);
    }
    if ((((0x17d < DAT_00453cdc) && (DAT_00453cdc < 0x197)) && (0x13d < DAT_004546f0)) &&
       (((DAT_004546f0 < 0x1d9 && (FUN_0043f010(), DAT_0044d060 == 0)) && (DAT_00457580 == 1)))) {
      FUN_00401a30();
      DAT_0044d064 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
  }
LAB_0042873e:
  FUN_0043f010();
  FUN_004028a0();
  FUN_0043e940();
  if (((DAT_004546f0 < 0x3f) && (0x201 < DAT_00453cdc)) &&
     ((DAT_0044d060 == 0 && (DAT_00457580 == 1)))) {
    FUN_004019b0();
    FUN_00401d30();
    FUN_0043d2a0();
    PostMessageA(DAT_004546f4,0x10,0,0);
  }
  DAT_0044d060 = DAT_00457580;
LAB_004287de:
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_410);
  return;
code_r0x00428af5:
  iVar4 = iVar4 + 1;
  pcVar12 = pcVar12 + 1;
  if (3 < iVar4) goto LAB_00428b0f;
  goto LAB_00428af0;
}
