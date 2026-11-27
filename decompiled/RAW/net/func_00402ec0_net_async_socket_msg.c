/* Function: FUN_00402ec0 */
/* Address: 0x00402ec0 */

void FUN_00402ec0(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char local_a4;
  char local_a3;
  char local_a2;
  char local_a1;
  char local_a0;
  char local_9f;
  char local_9e;
  char local_9d;
  char acStack_84 [48];
  char local_54 [32];
  char local_34 [44];
  undefined1 local_8;
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_a4;
  switch(param_3) {
  case 1:
    pcVar5 = "FD_READ";
    break;
  default:
    goto switchD_00402eef_caseD_2;
  case 8:
    DAT_0044f1af = 2;
    DAT_0044f46c = accept(DAT_0044f1b4,(sockaddr *)0x0,(int *)0x0);
    if (DAT_0044f46c == 0xffffffff) {
      MessageBoxA((HWND)0x0,"Accpet() Error","Error",0);
      closesocket(DAT_0044f46c);
      closesocket(DAT_0044f1b4);
      __security_check_cookie(local_4 ^ (uint)&local_a4);
      return;
    }
    closesocket(DAT_0044f1b4);
    send(DAT_0044f46c,"u can connect",0xe,0);
    memset(&local_a4,0,0x4d);
    Sleep(3000);
    recv(DAT_0044f46c,&local_a4,0x4d,0);
    Sleep(500);
    pcVar5 = "1111000000000000000000000000000000000000000000000000000000000000000000000000";
    pcVar4 = local_54;
    for (iVar2 = 0x13; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pcVar4 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar4 = pcVar4 + 4;
    }
    *pcVar4 = *pcVar5;
    memset(local_34,0x5f,0x2d);
    iVar2 = 0;
    do {
      pcVar5 = &DAT_0044fcc0 + iVar2;
      iVar3 = iVar2 - (int)pcVar5;
      do {
        cVar1 = *pcVar5;
        (local_34 + iVar3)[(int)pcVar5] = cVar1;
        pcVar5 = pcVar5 + 1;
      } while (cVar1 != '\0');
      iVar2 = iVar2 + 0xb;
    } while (iVar2 < 0x2c);
    iVar2 = 0;
    do {
      if (local_34[iVar2] == '\0') {
        local_34[iVar2] = '_';
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x2c);
    local_8 = 0;
    send(DAT_0044f46c,local_54,0x4d,0);
    Sleep(500);
    send(DAT_0044f46c,&DAT_0044ff90,0xbb9,0);
    DAT_00450b4c = 1;
    DAT_00450b50 = 2;
    DAT_00450b54 = 3;
    DAT_00450b58 = 4;
    if (local_a4 == '1') {
      DAT_00450b4c = 0xffffffff;
    }
    if (local_a3 == '1') {
      DAT_00450b50 = 0xffffffff;
    }
    if (local_a2 == '1') {
      DAT_00450b54 = 0xffffffff;
    }
    if (local_a1 == '1') {
      DAT_00450b58 = 0xffffffff;
    }
    if (local_a0 == '1') {
      DAT_00450b5c = 0xffffffff;
    }
    if (local_9f == '1') {
      DAT_00450b60 = 0xffffffff;
    }
    if (local_9e == '1') {
      DAT_00450b64 = 0xffffffff;
    }
    if (local_9d == '1') {
      DAT_00450b68 = 0xffffffff;
    }
    iVar2 = 0;
    do {
      cVar1 = acStack_84[iVar2];
      (&DAT_0044fcec)[iVar2] = cVar1;
      if (cVar1 == '_') {
        (&DAT_0044fcec)[iVar2] = 0;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x2c);
    DAT_0044f1ae = 1;
    __security_check_cookie(local_4 ^ (uint)&local_a4);
    return;
  case 0x10:
    pcVar5 = "FD_CONNECT";
    break;
  case 0x20:
    pcVar5 = "FD_CLOSE";
  }
  MessageBoxA((HWND)0x0,pcVar5,"Handle Message",0);
switchD_00402eef_caseD_2:
  __security_check_cookie(local_4 ^ (uint)&local_a4);
  return;
}

