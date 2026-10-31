#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* 
 * Virtual Address: 0x0043e9a0
 * Description: Game mode initialization and resource loading.
 *              Detects "d" file extensions in "data\data.txt" to set game mode.
 *              Initializes character sprites, weapons, and AI.
 * Calling Convention: __cdecl (parameters on stack)
 */

int FUN_0043e9a0(void)

{
  FILE *_File;
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  undefined4 uVar5;
  void *local_140;
  char local_13c [300];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004462a8;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_140;
  ExceptionList = &local_c;
  iVar1 = 0;
  do {
    if ((&DAT_00455378)[iVar1] == 'd') {
      if (DAT_004593a4 == 0) {
        if (iVar1 == 0x41) {
          DAT_004593a4 = 1;
        }
        else {
LAB_0043ea3b:
          DAT_004593a4 = 0;
        }
      }
      else {
        if (DAT_004593a4 == 1) {
          if (iVar1 == 0x42) {
            DAT_004593a4 = 2;
            goto LAB_0043ea3d;
          }
          bVar4 = iVar1 == 0x41;
        }
        else if (DAT_004593a4 == 2) {
          if (iVar1 == 0x43) {
            DAT_004593a4 = 3;
            DAT_00450bec = 1;
            goto LAB_0043ea3d;
          }
          bVar4 = iVar1 == 0x42;
        }
        else {
          if (DAT_004593a4 != 3) goto LAB_0043ea3b;
          bVar4 = iVar1 == 0x43;
        }
        if (!bVar4) goto LAB_0043ea3b;
      }
    }
LAB_0043ea3d:
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xfa);
  if (DAT_00450bec != 0) {
    if (DAT_004553e8 == 'd') {
      DAT_004593a0 = 0;
    }
    if (DAT_004553e9 == 'd') {
      DAT_004593a0 = 1;
    }
    if (DAT_004553ea == 'd') {
      DAT_004593a0 = 2;
    }
  }
  if (DAT_0044dce4 == 1) {
    FUN_0043e8e0(0x40,0,DAT_0044eea4 ^ (uint)(local_13c + -0x14));
    DAT_00458440 = 1;
    DAT_0044dce4 = 2;
    DAT_004593a0 = 0;
  }
  else if (DAT_004593a0 == 1) {
    uVar5 = 0x2945;
    goto LAB_0043eac6;
  }
  uVar5 = 0;
LAB_0043eac6:
  FUN_00401250(DAT_00455608,uVar5);
  if (DAT_004593a0 == 1) {
    if (DAT_0044dce4 == 2) {
      DAT_0044dce4 = 3;
      _File = fopen("data\\data.txt","r");
      iVar1 = feof(_File);
      while (iVar1 == 0) {
        fscanf(_File,"%s",local_13c);
        iVar1 = 0xf;
        bVar4 = true;
        pcVar2 = local_13c;
        pcVar3 = "<file_editing>";
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar4 = *pcVar2 == *pcVar3;
          pcVar2 = pcVar2 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar4);
        if (bVar4) {
          fscanf(_File,"%s",&DAT_004589c8);
        }
        iVar1 = feof(_File);
      }
      local_140 = operator_new(0x25360);
      local_4 = 0;
      if (local_140 == (void *)0x0) {
        DAT_004589bc = 0;
      }
      else {
        DAT_004589bc = FUN_004143d0(0,0,&DAT_004589c8);
      }
      local_4 = 0xffffffff;
      local_140 = operator_new(0x25360);
      local_4 = 1;
      if (local_140 == (void *)0x0) {
        DAT_004589c0 = 0;
      }
      else {
        DAT_004589c0 = FUN_004143d0(0,1,"data\\weapon0.txt");
      }
      local_4 = 0xffffffff;
      local_140 = operator_new(0x25360);
      local_4 = 2;
      if (local_140 == (void *)0x0) {
        DAT_004589b8 = 0;
      }
      else {
        DAT_004589b8 = FUN_004143d0(0,2,"data\\weapon1.txt");
      }
      local_4 = 0xffffffff;
      local_140 = operator_new(0x25360);
      local_4 = 3;
      if (local_140 == (void *)0x0) {
        DAT_004589b4 = 0;
      }
      else {
        DAT_004589b4 = FUN_004143d0(0,6,"data\\weapon6.txt");
      }
      local_4 = 0xffffffff;
    }
    FUN_004151d0(DAT_004589bc,DAT_004589c0,DAT_004589b8,DAT_004589b4,DAT_00455608,&DAT_004589c8);
  }
  if (DAT_004593a0 == 0) {
    FUN_004246b0(DAT_00455608);
  }
  if (DAT_004593a0 == 2) {
    FUN_00414b70(DAT_00455608);
  }
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_140);
  return 0;
}


