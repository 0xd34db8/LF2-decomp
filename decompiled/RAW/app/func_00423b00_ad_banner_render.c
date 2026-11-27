/* Function: FUN_00423b00 */
/* Address: 0x00423b00 */

void FUN_00423b00(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  DWORD DVar3;
  char *pcVar4;
  int iVar5;
  LPCSTR lpFile;
  int iVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uVar9;
  int local_8;
  int local_4;
  
  iVar2 = DAT_00453da4;
  if (DAT_00458420 == (int *)0x0) {
    return;
  }
  if (*DAT_00458420 == 0) {
    return;
  }
  iVar5 = DAT_00453da4 + 199;
  uVar7 = 0;
  iVar6 = 0x24e;
  if (DAT_0044d780 == 0xffffffff) {
    if ((0 < (int)DAT_004546d0) && ((char)DAT_004546f8 != '?')) {
      uVar7 = DAT_004546d0;
    }
    if (((int)uVar7 < (int)DAT_004546d4) && (DAT_0045475c != '?')) {
      uVar7 = DAT_004546d4;
    }
    if (((int)uVar7 < (int)DAT_004546d8) && (DAT_004547c0 != '?')) {
      uVar7 = DAT_004546d8;
    }
    if (((int)uVar7 < (int)DAT_004546dc) && (DAT_00454824 != '?')) {
      uVar7 = DAT_004546dc;
    }
    if (((int)uVar7 < (int)DAT_004546e0) && (DAT_00454888 != '?')) {
      uVar7 = DAT_004546e0;
    }
    if (((int)uVar7 < (int)DAT_004546e4) && (DAT_004548ec != '?')) {
      uVar7 = DAT_004546e4;
    }
    if (((int)uVar7 < (int)DAT_004546e8) && (DAT_00454950 != '?')) {
      uVar7 = DAT_004546e8;
    }
    if (((int)uVar7 < (int)DAT_004546ec) && (DAT_004549b4 != '?')) {
      uVar7 = DAT_004546ec;
    }
    DVar3 = timeGetTime();
    DAT_0044d780 = DVar3 % uVar7;
    DAT_00458418 = 0;
    DAT_0045841c = 4;
  }
  else {
    pcVar4 = (char *)&DAT_004546f8;
    do {
      if ((((int)(&DAT_00452928)[uVar7] <= (int)DAT_0044d780) &&
          ((int)DAT_0044d780 < (int)(&DAT_004546d0)[uVar7])) && (*pcVar4 != '?')) {
        iVar1 = (&DAT_00453f50)[uVar7];
        if (DAT_0045841c < iVar1 + 10) {
          DAT_0045841c = DAT_0045841c + 1;
        }
        if (DAT_0045841c < 4) {
          iVar6 = DAT_0045841c * -0x3c + 0x314;
        }
        else if (iVar1 + -10 < DAT_0045841c) {
          if (iVar1 <= DAT_0045841c) goto LAB_00423c90;
          iVar6 = (DAT_0045841c - iVar1) * 0x14 + 0x314;
        }
        else if (iVar1 <= DAT_0045841c) {
LAB_00423c90:
          iVar6 = 0x348;
        }
        DAT_00458418 = uVar7;
        FUN_0043f010(iVar6,iVar5,uVar7 + 2,1,0,param_2);
        if (((0x24e < DAT_004546f0) && (iVar5 < DAT_00453cdc)) && (DAT_00453cdc < iVar2 + 0x189)) {
          if (iVar1 < DAT_0045841c) {
            DAT_0045841c = 0;
          }
          else if ((4 < DAT_0045841c) && (DAT_0045841c < iVar1 + -10)) {
            DAT_0045841c = 5;
          }
          if (iVar6 + 0xc2 < 0x31a) {
            FUN_00415160(iVar6,iVar5,0xc6,1,0xffffff);
            FUN_00415160(iVar6,iVar2 + 0x188,0xc6,1,0xffffff);
            FUN_00415160(iVar6,iVar5,1,0xc2,0xffffff);
            FUN_00415160(iVar6 + 0xc5,iVar5,1,0xc2,0xffffff);
          }
          if ((DAT_00457580 == 1) && (*param_1 == 0)) {
            DAT_00457580 = 0;
            FUN_00401a30(0);
            Sleep(300);
            ShellExecuteA((HWND)0x0,"open",(LPCSTR)(&DAT_004546f8 + uVar7 * 0x32),(LPCSTR)0x0,
                          (LPCSTR)0x0,1);
          }
        }
        break;
      }
      pcVar4 = pcVar4 + 100;
      uVar7 = uVar7 + 1;
    } while ((int)pcVar4 < 0x454a18);
  }
  bVar8 = (char)DAT_004546f8 != '?';
  if (DAT_0045475c != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_004547c0 != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_00454824 != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_00454888 != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_004548ec != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_00454950 != '?') {
    bVar8 = bVar8 + 1;
  }
  if (DAT_004549b4 != '?') {
    bVar8 = bVar8 + 1;
  }
  if (1 < bVar8) {
    iVar1 = iVar6 + 0xa0;
    if ((((iVar1 < DAT_004546f0) && (iVar2 + 0xb5 < DAT_00453cdc)) && (DAT_004546f0 < iVar6 + 0xb3))
       && (DAT_00453cdc <= iVar5)) {
      if (DAT_00453f70 < DAT_0045841c) {
        DAT_0045841c = 0;
      }
      else if ((4 < DAT_0045841c) && (DAT_0045841c < DAT_00453f70 + -10)) {
        DAT_0045841c = 5;
      }
      FUN_0043f010(iVar1,iVar2 + 0xb9,10,1,0,param_2);
      if ((DAT_00457580 == 1) && (*param_1 == 0)) {
        DAT_00457580 = 0;
        do {
          DAT_00458418 = DAT_00458418 - 1;
          if ((int)DAT_00458418 < 0) {
            DAT_00458418 = 7;
          }
          DAT_0044d780 = (&DAT_00452928)[DAT_00458418];
        } while (((int)DAT_0044d780 < 0) || (*(char *)(&DAT_004546f8 + DAT_00458418 * 0x32) == '?'))
        ;
      }
    }
    else {
      FUN_0043f010(iVar1,iVar2 + 0xb9,8,1,0,param_2);
    }
    iVar6 = iVar6 + 0xb3;
    if (((iVar6 < DAT_004546f0) && (iVar2 + 0xb5 < DAT_00453cdc)) && (DAT_00453cdc <= iVar5)) {
      if (DAT_00453f70 < DAT_0045841c) {
        DAT_0045841c = 0;
      }
      else if ((4 < DAT_0045841c) && (DAT_0045841c < DAT_00453f70 + -10)) {
        DAT_0045841c = 5;
      }
      FUN_0043f010(iVar6,iVar2 + 0xb9,0xb,1,0,param_2);
      if ((DAT_00457580 == 1) && (*param_1 == 0)) {
        DAT_00457580 = 0;
        do {
          DAT_00458418 = DAT_00458418 + 1;
          if (7 < (int)DAT_00458418) {
            DAT_00458418 = 0;
          }
          DAT_0044d780 = (&DAT_00452928)[DAT_00458418];
        } while (((int)DAT_0044d780 < 0) || (*(char *)(&DAT_004546f8 + DAT_00458418 * 0x32) == '?'))
        ;
      }
    }
    else {
      FUN_0043f010(iVar6,iVar2 + 0xb9,9,1,0,param_2);
    }
  }
  local_8 = 999;
  local_4 = 999;
  FUN_0043f010(0,0x1a6,10,1,0,param_2);
  uVar7 = 0;
  lpFile = (LPCSTR)&DAT_00454a18;
  do {
    iVar2 = (&DAT_004583b8)[uVar7];
    if ((iVar2 != -99) && (*lpFile != '?')) {
      if (iVar2 < local_8) {
        local_8 = iVar2;
      }
      iVar6 = (&DAT_00453c08)[uVar7];
      if (iVar6 < local_4) {
        local_4 = iVar6;
      }
      if ((((iVar2 < DAT_004546f0) && (DAT_004546f0 < (&DAT_00453f70)[uVar7] + iVar2)) &&
          (iVar6 < DAT_00453cdc)) &&
         ((DAT_00453cdc < (&DAT_00453ce0)[uVar7] + iVar6 || (uVar7 / 6 == 3)))) {
        FUN_00415160(iVar2,iVar6,(&DAT_00453f70)[uVar7],1,0xffffff);
        FUN_00415160((&DAT_004583b8)[uVar7],(&DAT_00453c08)[uVar7] + -1 + (&DAT_00453ce0)[uVar7],
                     (&DAT_00453f70)[uVar7],1,0xffffff);
        FUN_00415160((&DAT_004583b8)[uVar7],(&DAT_00453c08)[uVar7],1,(&DAT_00453ce0)[uVar7],0xffffff
                    );
        FUN_00415160((&DAT_00453f70)[uVar7] + -1 + (&DAT_004583b8)[uVar7],(&DAT_00453c08)[uVar7],1,
                     (&DAT_00453ce0)[uVar7],0xffffff);
        if ((DAT_00457580 == 1) && (*param_1 == 0)) {
          DAT_00457580 = 0;
          FUN_00401a30(0);
          Sleep(300);
          ShellExecuteA((HWND)0x0,"open",lpFile,(LPCSTR)0x0,(LPCSTR)0x0,1);
        }
      }
    }
    lpFile = lpFile + 100;
    uVar7 = uVar7 + 1;
  } while ((int)lpFile < 0x455378);
  if ((local_8 < 999) && (local_4 < 999)) {
    FUN_0043f010(local_8,local_4 + -10,0xc,1,0,param_2);
  }
  if (DAT_004554bc <= DAT_0044d03c) {
    return;
  }
  if (DAT_00453da8 == '?') {
    return;
  }
  DAT_004511b4 = DAT_004511b4 + 1;
  if (DAT_004511b4 < 0x3c) {
    if ((0x1d < DAT_004511b4) && ((0x18c < DAT_004546f0 || (0x21 < DAT_00453cdc)))) {
      uVar9 = 0;
      goto LAB_0042422b;
    }
  }
  else {
    DAT_004511b4 = 0;
  }
  uVar9 = 1;
LAB_0042422b:
  FUN_0043f010(0,0,uVar9,1,0,param_2);
  if ((((DAT_004546f0 < 0x18d) && (DAT_00453cdc < 0x22)) &&
      (FUN_0043f010(0,0,1,1,0,param_2), DAT_00457580 == 1)) && (*param_1 == 0)) {
    DAT_00457580 = 0;
    FUN_00401a30(0);
    Sleep(300);
    ShellExecuteA((HWND)0x0,"open",&DAT_00453da8,(LPCSTR)0x0,(LPCSTR)0x0,1);
  }
  return;
}

