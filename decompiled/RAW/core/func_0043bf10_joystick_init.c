/* Function: FUN_0043bf10 */
/* Address: 0x0043bf10 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043bf10(void)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  UINT UVar3;
  MMRESULT MVar4;
  joyinfoex_tag local_1cc;
  tagJOYCAPSA local_198;
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_1cc;
  puVar2 = &DAT_00453fec;
  do {
    uVar1 = *(undefined1 *)((int)puVar2 + 7);
    *(undefined1 *)((int)puVar2 + 6) = uVar1;
    *(undefined1 *)((int)puVar2 + 5) = uVar1;
    *(undefined1 *)(puVar2 + 1) = uVar1;
    puVar2[-7] = 0;
    *puVar2 = 0;
    puVar2[-1] = 0;
    puVar2[2] = 0;
    *(undefined2 *)(puVar2 + 3) = 0;
    puVar2 = puVar2 + 0xc;
  } while ((int)puVar2 < 0x4540ac);
  UVar3 = joyGetNumDevs();
  if (UVar3 != 0) {
    memset(&local_1cc,0,0x34);
    local_1cc.dwSize = 0x34;
    local_1cc.dwFlags = 0x83;
    MVar4 = joyGetPosEx(0,&local_1cc);
    if (MVar4 != 0xa7) {
      DAT_00453fd0 = 1;
      _DAT_00453fd4 = 0;
      joySetThreshold(0,100);
      joySetCapture(DAT_004546f4,0,0x19,1);
      joyGetDevCapsA(0,&local_198,0x194);
      DAT_00453fd8 = local_198.wXmin;
      DAT_00453fe8 = (int)(local_198.wXmin + local_198.wXmax) / 2;
      DAT_00453fec = (int)(local_198.wYmax + local_198.wYmin) / 2;
      DAT_00453fe0 = local_198.wXmax;
      DAT_00453fdc = local_198.wYmin;
      DAT_00453fe4 = local_198.wYmax;
    }
    MVar4 = joyGetPosEx(1,&local_1cc);
    if (MVar4 != 0xa7) {
      DAT_00454000 = 1;
      _DAT_00454004 = 1;
      joySetThreshold(1,100);
      joySetCapture(DAT_004546f4,1,0x19,1);
      joyGetDevCapsA(1,&local_198,0x194);
      DAT_00454008 = local_198.wXmin;
      DAT_00454018 = (int)(local_198.wXmin + local_198.wXmax) / 2;
      DAT_0045401c = (int)(local_198.wYmax + local_198.wYmin) / 2;
      DAT_00454010 = local_198.wXmax;
      DAT_0045400c = local_198.wYmin;
      DAT_00454014 = local_198.wYmax;
    }
  }
  __security_check_cookie(local_4 ^ (uint)&local_1cc);
  return;
}
