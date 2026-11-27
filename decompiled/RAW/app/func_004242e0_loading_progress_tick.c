/* Function: FUN_004242e0 */
/* Address: 0x004242e0 */

void FUN_004242e0(undefined4 param_1,undefined4 param_2)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  LPCSTR local_c;
  uint local_8;
  int local_4;
  
  if (DAT_004511c0 == 0) {
    DAT_004511c0 = timeGetTime();
  }
  DVar1 = timeGetTime();
  if (DVar1 - DAT_004511c0 < 0x22) {
    DVar1 = timeGetTime();
    DVar1 = (DAT_004511c0 - DVar1) + 0x21;
    if (0 < (int)DVar1) {
      if (5 < (int)DVar1) {
        Sleep(5);
        return;
      }
      Sleep(DVar1);
    }
    return;
  }
  DVar1 = timeGetTime();
  if (100 < DVar1 - DAT_004511c0) {
    DVar1 = timeGetTime();
    DAT_004511c0 = DVar1 - 100;
  }
  DAT_004511c0 = DAT_004511c0 + 0x21;
  FUN_0043f010(0,0,0xffffffff,0,0,param_2);
  DAT_004511bc = (DAT_004511bc + 1) % 10;
  if (DAT_004511bc < 2) {
    uVar7 = 0xff6464;
  }
  else if (DAT_004511bc - 5U < 3) {
    uVar7 = 0xffffff;
  }
  else {
    uVar7 = 0xffb4b4;
  }
  FUN_00401290(DAT_00455608,param_1,0x601b0d,uVar7,0x260,0x3c);
  local_8 = 999;
  local_4 = 999;
  if ((DAT_00458420 != (int *)0x0) && (*DAT_00458420 != 0)) {
    uVar4 = 0;
    local_c = (LPCSTR)&DAT_004546f8;
    do {
      if (*local_c != '?') {
        iVar2 = (uVar4 / 4) * 0xc2;
        iVar5 = (uVar4 % 4) * 0xc6;
        iVar3 = iVar2 + 0x8e;
        uVar6 = iVar5 + 1;
        DAT_00458418 = uVar4;
        FUN_0043f010(uVar6,iVar3,uVar4 + 2,1,0,param_2);
        if (iVar3 < local_4) {
          local_4 = iVar3;
        }
        if (uVar6 < local_8) {
          local_8 = uVar6;
        }
        if ((((int)uVar6 < DAT_004546f0) &&
            (((DAT_004546f0 < iVar5 + 199 || (uVar4 % 4 == 3)) && (iVar3 < DAT_00453cdc)))) &&
           (DAT_00453cdc < iVar2 + 0x150)) {
          FUN_00415160(uVar6,iVar3,0xc6,1,0xffffff);
          FUN_00415160(uVar6,iVar2 + 0x14f,0xc6,1,0xffffff);
          FUN_00415160(uVar6,iVar3,1,0xc2,0xffffff);
          FUN_00415160(iVar5 + 0xc6,iVar3,1,0xc2,0xffffff);
          if ((DAT_00457580 == 1) && (DAT_004511b8 == 0)) {
            DAT_00457580 = 0;
            FUN_00401a30(0);
            Sleep(300);
            ShellExecuteA((HWND)0x0,"open",local_c,(LPCSTR)0x0,(LPCSTR)0x0,1);
          }
        }
      }
      local_c = local_c + 100;
      uVar4 = uVar4 + 1;
    } while ((int)local_c < 0x454a18);
    if ((local_8 < 999) && (local_4 < 999)) {
      FUN_0043f010(local_8,local_4 + -10,0xc,1,0,param_2);
    }
  }
  FUN_0043f010(0,0x217,0xe,1,0,param_2);
  if ((((DAT_004546f0 - 1U < 0x92) && (0x216 < DAT_00453cdc)) &&
      (FUN_0043f010(0,0x217,0xd,1,0,param_2), DAT_00457580 == 1)) && (DAT_004511b8 == 0)) {
    DAT_00457580 = 0;
    FUN_00401a30(0);
    Sleep(300);
    ShellExecuteA((HWND)0x0,"open","http://www.littlefighter.com/advertise",(LPCSTR)0x0,(LPCSTR)0x0,
                  1);
  }
  DAT_004511b8 = DAT_00457580;
  iVar3 = DAT_00453cdc + 2;
  iVar2 = DAT_004546f0;
  if (0x307 < DAT_004546f0) {
    iVar2 = 0x307;
  }
  if (0x217 < iVar3) {
    iVar3 = 0x217;
  }
  FUN_0043f010(iVar2,iVar3,0xffffffff,1,0,param_2);
  FUN_004028a0(param_2);
  FUN_0043e940(DAT_00458348);
  FUN_0043d230();
  return;
}

