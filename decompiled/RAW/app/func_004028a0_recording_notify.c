/*
 * Procedure: FUN_004028a0
 * Address: 0x004028a0 - 0x00402a5f (Length: 448 bytes)
 * Purpose: Volume adjustment HUD and recording notify messages ("Start recording...", "Recording file saved!", "Recording canceled!")
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



void FUN_004028a0(void)

{
  int iVar1;
  char local_20c [20];
  char local_1f8 [500];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)local_20c;
  iVar1 = 0;
  if (DAT_004553f2 == 'd') {
    iVar1 = -1;
  }
  if (DAT_004553f3 == 'd') {
    iVar1 = 1;
LAB_004028dd:
    FUN_00402810(iVar1,DAT_00455608);
    DAT_0044f190 = 100;
  }
  else {
    if (iVar1 != 0) goto LAB_004028dd;
    if (DAT_0044f190 < 1) goto LAB_00402947;
  }
  if (DAT_00450b70 == 0) {
    sprintf(local_20c,"Volume: %d",DAT_0044d000);
    FUN_00401290(DAT_00455608,local_20c,0,0xff00,3,0x213);
    DAT_0044f190 = DAT_0044f190 + -1;
  }
LAB_00402947:
  if (((0 < DAT_00450b70) && (DAT_00450bfc == 0)) &&
     (DAT_00450b6c = DAT_00450b6c + 1, 0xf0 < DAT_00450b6c)) {
    DAT_00450b6c = 0;
    DAT_00450b70 = 0;
    __security_check_cookie(local_4 ^ (uint)local_20c);
    return;
  }
  if (DAT_00450b70 == 1) {
    sprintf(local_1f8,"Start recording \'%s\'...",&DAT_0044fd98);
    FUN_00401290(DAT_00455608,local_1f8,0,0xff7800,3,0x213);
  }
  if (DAT_00450b70 == 2) {
    sprintf(local_1f8,"Recording file \'%s\' saved!",&DAT_0044fd98);
    FUN_00401290(DAT_00455608,local_1f8,0,0xff00,3,0x213);
  }
  if (DAT_00450b70 == 3) {
    sprintf(local_1f8,"Recording canceled!");
    DAT_00450b6c = DAT_00450b6c + 1;
    FUN_00401290(DAT_00455608,local_1f8,0,0xff,3,0x213);
  }
  __security_check_cookie(local_4 ^ (uint)local_20c);
  return;
}

