/*
 * Procedure: FUN_00402b60
 * Address: 0x00402b60 - 0x00402d63 (Length: 516 bytes)
 * Purpose: Network winsock initialization, gethostname, gethostbyname, socket creation, WSAAsyncSelect
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402b60(HWND param_1)

{
  int iVar1;
  int iVar2;
  WSADATA local_294;
  char local_104 [256];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_294;
  WSAStartup(0x101,&local_294);
  if (local_294.wVersion != 0x101) {
    MessageBoxA((HWND)0x0,"WSAStartup()","Error",0);
    __security_check_cookie(local_4 ^ (uint)&local_294);
    return;
  }
  iVar1 = gethostname(local_104,0x100);
  if (iVar1 == -1) {
    MessageBoxA((HWND)0x0,"gethostname()","Error",0);
    __security_check_cookie(local_4 ^ (uint)&local_294);
    return;
  }
  DAT_0044f2d4 = gethostbyname(local_104);
  if (DAT_0044f2d4 == (hostent *)0x0) {
    MessageBoxA((HWND)0x0,"gethostbyname()","Error",0);
    __security_check_cookie(local_4 ^ (uint)&local_294);
    return;
  }
  iVar1 = FUN_00402ad0(DAT_0044f2d4->h_addr_list);
  _DAT_0044f260 = 2;
  DAT_0044f264 = *(undefined4 *)DAT_0044f2d4->h_addr_list[iVar1];
  _DAT_0044f262 = htons(5000);
  DAT_0044f1b4 = 0;
  DAT_0044f1b0 = 0;
  DAT_0044f1b4 = socket(2,1,6);
  if (DAT_0044f1b4 == 0xffffffff) {
    MessageBoxA((HWND)0x0,"socket()","Error",0);
    __security_check_cookie(local_4 ^ (uint)&local_294);
    return;
  }
  iVar2 = WSAAsyncSelect(DAT_0044f1b4,param_1,0x401,0x38);
  if (iVar2 == 0) {
    _DAT_0044f58c = 2;
    _DAT_0044f590 = *(undefined4 *)DAT_0044f2d4->h_addr_list[iVar1];
    _DAT_0044f58e = htons(0x3039);
    DAT_0044f1ae = 0;
    __security_check_cookie(local_4 ^ (uint)&local_294);
    return;
  }
  MessageBoxA((HWND)0x0,"WSAAsyncSelect()","Error",0);
  __security_check_cookie(local_4 ^ (uint)&local_294);
  return;
}

