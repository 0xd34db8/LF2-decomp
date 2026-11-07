/*
 * Procedure: FUN_004014e0
 * Address: 0x004014e0 - 0x00401968 (Length: 1161 bytes)
 * Purpose: DirectSound WAV loader, RIFF header parser, secondary buffer creation
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



void FUN_004014e0(LPSTR param_1)

{
  char cVar1;
  HMMIO hmmio;
  LPSTR pCVar2;
  MMRESULT MVar3;
  LONG LVar4;
  HPSTR pch;
  undefined4 *in_ECX;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  LPSTR pCVar8;
  CHAR *pCVar9;
  undefined2 *puVar10;
  undefined4 uStack_1e8;
  size_t _Size;
  undefined4 *_Size_00;
  void *_Dst;
  void *_Dst_00;
  int *piVar11;
  int *piVar12;
  undefined4 local_1b8;
  int iStack_1b4;
  int *piStack_1b0;
  _MMCKINFO local_1a4;
  undefined2 local_190;
  undefined2 uStack_18e;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 *local_180;
  _MMCKINFO local_17c;
  short local_168;
  undefined2 local_166;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_154;
  undefined4 local_150;
  uint local_14c;
  undefined4 local_148;
  undefined2 *local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined1 local_134 [4];
  CHAR local_130 [300];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_1b8;
  if (DAT_0044eecc == (int *)0x0) {
    __security_check_cookie(local_4 ^ (uint)&local_1b8);
    return;
  }
  *in_ECX = 0;
  if (DAT_0044eecc == (int *)0x0) {
    __security_check_cookie(local_4 ^ (uint)&local_1b8);
    return;
  }
  local_180 = in_ECX;
  hmmio = mmioOpenA(param_1,(LPMMIOINFO)0x0,0x10000);
  if (hmmio == (HMMIO)0x0) {
    pcVar7 = "Could not Open Wave File <";
    pCVar9 = local_130;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)pCVar9 = *(undefined4 *)pcVar7;
      pcVar7 = pcVar7 + 4;
      pCVar9 = pCVar9 + 4;
    }
    *(undefined2 *)pCVar9 = *(undefined2 *)pcVar7;
    pCVar9[2] = pcVar7[2];
    pCVar2 = param_1;
    do {
      cVar1 = *pCVar2;
      pCVar2 = pCVar2 + 1;
    } while (cVar1 != '\0');
    pCVar9 = local_134 + 3;
    do {
      pcVar7 = pCVar9 + 1;
      pCVar9 = pCVar9 + 1;
    } while (*pcVar7 != '\0');
    pCVar8 = param_1;
    for (uVar6 = (uint)((int)pCVar2 - (int)param_1) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *(undefined4 *)pCVar9 = *(undefined4 *)pCVar8;
      pCVar8 = pCVar8 + 4;
      pCVar9 = pCVar9 + 4;
    }
    for (uVar6 = (int)pCVar2 - (int)param_1 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
      *pCVar9 = *pCVar8;
      pCVar8 = pCVar8 + 1;
      pCVar9 = pCVar9 + 1;
    }
    puVar10 = (undefined2 *)(local_134 + 3);
    do {
      pcVar7 = (char *)((int)puVar10 + 1);
      puVar10 = (undefined2 *)((int)puVar10 + 1);
    } while (*pcVar7 != '\0');
    *puVar10 = 0x3e;
    MessageBoxA((HWND)0x0,local_130,param_1,0);
  }
  else {
    local_1a4.fccType = 0;
    local_17c.dwDataOffset = 0;
    local_1a4.dwDataOffset = 0;
    local_17c.ckid = 0;
    local_17c.cksize = 0;
    local_17c.dwFlags = 0;
    local_1a4.ckid = 0;
    local_1a4.cksize = 0;
    local_1a4.dwFlags = 0;
    local_17c.fccType = 0x45564157;
    MVar3 = mmioDescend(hmmio,&local_17c,(MMCKINFO *)0x0,0x20);
    if (MVar3 == 0) {
      local_1a4.ckid = 0x20746d66;
      MVar3 = mmioDescend(hmmio,&local_1a4,&local_17c,0);
      if (MVar3 == 0) {
        LVar4 = mmioRead(hmmio,(HPSTR)&local_168,0x12);
        if (LVar4 == 0x12) {
          if (local_168 == 1) {
            MVar3 = mmioAscend(hmmio,&local_1a4,0);
            if (MVar3 == 0) {
              local_1a4.ckid = 0x61746164;
              MVar3 = mmioDescend(hmmio,&local_1a4,&local_17c,0x10);
              if (MVar3 == 0) {
                pch = operator_new(local_1a4.cksize);
                uVar6 = mmioRead(hmmio,pch,local_1a4.cksize);
                if (uVar6 == local_1a4.cksize) {
                  mmioClose(hmmio,0);
                  local_18c = local_164;
                  local_188 = local_160;
                  local_144 = &local_190;
                  piVar12 = (int *)0x0;
                  local_148 = 0;
                  local_140 = 0;
                  local_13c = 0;
                  local_138 = 0;
                  local_134 = (undefined1  [4])0x0;
                  _local_190 = CONCAT22(local_166,1);
                  local_154 = 0x24;
                  local_150 = 0xe0;
                  local_14c = local_1a4.cksize;
                  piVar11 = DAT_0044eecc;
                  iVar5 = (**(code **)(*DAT_0044eecc + 0xc))();
                  if (iVar5 != 0) {
                    uStack_1e8 = (int *)0x401871;
                    MessageBoxA((HWND)0x0,"Could not Create Sound Buffer.",(LPCSTR)0x0,0);
                    operator_delete(pch);
                  }
                  _Dst_00 = (void *)0x0;
                  _Dst = (void *)((int)register0x00000010 + -0x1c0);
                  _Size_00 = &local_1b8;
                  _Size = (int)register0x00000010 - 0x1c4;
                  uStack_1e8 = (int *)((int)register0x00000010 + -0x1bc);
                  iVar5 = (**(code **)(*piVar12 + 0x2c))(piVar12,0);
                  if (iVar5 == -0x7787ff6a) {
                    (**(code **)(*uStack_1e8 + 0x50))(uStack_1e8);
                    (**(code **)(*piStack_1b0 + 0x2c))
                              (piStack_1b0,0,piVar11,(int)register0x00000010 + -0x1e0,&uStack_1e8,
                               (int)register0x00000010 + -0x1dc,(int)register0x00000010 + -0x1e4,0);
                  }
                  memcpy(_Dst,pch,_Size);
                  if (_Dst_00 != (void *)0x0) {
                    memcpy(_Dst_00,pch + _Size,(size_t)_Size_00);
                  }
                  (**(code **)(*uStack_1e8 + 0x4c))(uStack_1e8,_Dst,_Size,_Dst_00,_Size_00);
                  operator_delete(pch);
                  *local_180 = local_1b8;
                }
                else {
                  mmioClose(hmmio,0);
                  MessageBoxA((HWND)0x0,"Could not read Wave Data",(LPCSTR)0x0,0);
                }
              }
              else {
                mmioClose(hmmio,0);
                MessageBoxA((HWND)0x0,"Wave file has no data",(LPCSTR)0x0,0);
              }
            }
            else {
              mmioClose(hmmio,0);
              MessageBoxA((HWND)0x0,"Unable to Ascend",(LPCSTR)0x0,0);
            }
          }
          else {
            mmioClose(hmmio,0);
            MessageBoxA((HWND)0x0,"Not a valid Wave Format",(LPCSTR)0x0,0);
          }
        }
        else {
          mmioClose(hmmio,0);
          MessageBoxA((HWND)0x0,"Error reading Wave Format",(LPCSTR)0x0,0);
        }
      }
      else {
        mmioClose(hmmio,0);
        MessageBoxA((HWND)0x0,"Could not Descend into format of Wave File",(LPCSTR)0x0,0);
      }
    }
    else {
      mmioClose(hmmio,0);
      MessageBoxA((HWND)0x0,"Could not Descend into Wave File",(LPCSTR)0x0,0);
    }
  }
  __security_check_cookie(local_4 ^ (uint)&local_1b8);
  return;
}

