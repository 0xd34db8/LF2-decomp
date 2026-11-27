/* Function: FUN_00402d70 */
/* Address: 0x00402d70 */

void FUN_00402d70(void)

{
  char cVar1;
  SOCKET s;
  char *pcVar2;
  int iVar3;
  char local_104 [21];
  undefined1 local_ef;
  undefined1 local_ee;
  undefined1 local_ed;
  uint local_4;
  
  s = DAT_0044f1b4;
  local_4 = DAT_0044eea4 ^ (uint)local_104;
  if ((DAT_0044f1b4 != 0) && (DAT_0044f1b0 != 0)) {
    memset(local_104,0,0x100);
    builtin_strncpy(local_104,"Client want to EXIT.",0x14);
    local_104[0x14] = DAT_0044f208;
    local_ee = DAT_0044f20a;
    pcVar2 = local_104;
    local_ef = DAT_0044f209;
    local_ed = DAT_0044f20b;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    iVar3 = sendto(s,local_104,(int)pcVar2 - (int)(local_104 + 1),0,(sockaddr *)&DAT_0044f58c,0x10);
    if (iVar3 == -1) {
      MessageBoxA((HWND)0x0,"sendto()","Error",0);
      closesocket(DAT_0044f1b4);
      __security_check_cookie(local_4 ^ (uint)local_104);
      return;
    }
  }
  closesocket(DAT_0044f1b4);
  DAT_0044f1b4 = 0;
  DAT_0044f1b0 = 0;
  WSACleanup();
  __security_check_cookie(local_4 ^ (uint)local_104);
  return;
}

