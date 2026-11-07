#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#ifdef _WIN32
#include <direct.h>
#endif

/*
 * Virtual Address: 0x00431D10
 * Function: main_menu_dispatch
 * Class / Subsystem: Application / Main Menu Navigation
 *
 * Description:
 *   Handles rendering and user input for the primary game menu:
 *   - Option 0: VS Mode (transitions to state 3)
 *   - Option 1: Stage Mode (transitions to state 3)
 *   - Option 2: Championship (transitions to state 0x14 / 20)
 *   - Option 3: Battle Mode (transitions to state 0x78 / 120)
 *   - Option 4: Demo (transitions to state 3)
 *   - Option 5: Options (transitions to state 2)
 *   - Option 6: Replay (opens file dialog for .lfr, checks version & data hash, initiates playback)
 *   - Option 7: Quit (calls PostQuitMessage(0))
 *   Also handles clickable website hyperlinks to martiwong.com, littlefighter.com, and lf2.net.
 */

void FUN_00431d10(undefined4 param_1,undefined4 *param_2,uint *param_3,undefined4 *param_4)
{
  int iVar1;
  char cVar2;
  uint *puVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  BOOL BVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  uint *local_708;
  undefined4 *local_704;
  undefined4 local_700;
  int local_6fc;
  undefined4 *local_6f8;
  char local_6f0 [15];
  char acStack_6e1 [13];
  undefined4 local_6d4;
  uint local_6d0;
  char local_6cc [44];
  undefined4 local_6a0;
  undefined1 local_69c;
  tagOFNA local_66c;
  char local_60b [3];
  CHAR local_608 [260];
  char cStack_505;
  CHAR local_504 [10];
  char acStack_4fa [250];
  char local_400 [260];
  char local_2fc [500];
  CHAR local_108 [260];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)(uintptr_t)&local_708;
  local_700 = param_1;
  local_704 = param_2;
  local_708 = param_3;
  local_6f8 = param_4;
  local_6fc = (int)(uintptr_t)in_ECX;
  DAT_00451b7c = 0;
  FUN_00415160(0,0,0x31a,0x226,0x122565);
  if (DAT_004511ac == 0) {
    FUN_00423840();
  }
  FUN_004236d0();
  FUN_0043f010(0,DAT_00453da4,0xffffffff,1,0,param_1);
  FUN_0043f010(0x99,DAT_00453da4 + 0x60,1,1,0,param_1);
  iVar6 = DAT_0045757c;
  puVar11 = (undefined4 *)&DAT_004498d8;
  pcVar5 = local_6f0;
  for (iVar8 = 7; iVar8 != 0; iVar8 = iVar8 + -1) {
    *(undefined4 *)pcVar5 = *puVar11;
    puVar11 = puVar11 + 1;
    pcVar5 = pcVar5 + 4;
  }
  puVar11 = (undefined4 *)&DAT_004498b8;
  puVar12 = &local_6d4;
  for (iVar8 = 7; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  *(undefined2 *)puVar12 = *(undefined2 *)puVar11;
  *(undefined1 *)((char *)puVar12 + 2) = *(undefined1 *)((char *)puVar11 + 2);
  puVar11 = (undefined4 *)&DAT_00449204;
  puVar12 = &local_6a0;
  for (iVar8 = 7; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar12 = *puVar11;
    puVar11 = puVar11 + 1;
    puVar12 = puVar12 + 1;
  }
  pcVar5 = local_6f0;
  iVar8 = DAT_0045757c + 0x1eb;
  *(undefined1 *)puVar12 = *(undefined1 *)puVar11;
  uVar9 = 0;
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  if (pcVar5 != local_6f0 + 1) {
    do {
      local_6f0[uVar9] = local_6f0[uVar9] - ((byte)uVar9 & 3);
      pcVar5 = local_6f0;
      uVar9 = uVar9 + 1;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
    } while (uVar9 < (uint)((intptr_t)pcVar5 - (intptr_t)(local_6f0 + 1)));
  }
  pcVar5 = (char *)&local_6d4;
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  if (pcVar5 != (char *)((intptr_t)&local_6d4 + 1)) {
    uVar9 = 0;
    do {
      acStack_6e1[uVar9 + 0xd] = acStack_6e1[uVar9 + 0xd] - ((byte)uVar9 & 3);
      pcVar5 = (char *)&local_6d4;
      uVar9 = uVar9 + 1;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
    } while (uVar9 < (uint)((intptr_t)pcVar5 - ((intptr_t)&local_6d4 + 1)));
  }
  pcVar5 = (char *)&local_6a0;
  do {
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  if (pcVar5 != (char *)((intptr_t)&local_6a0 + 1)) {
    uVar9 = 0;
    do {
      local_6cc[uVar9 + 0x2c] = local_6cc[uVar9 + 0x2c] - ((byte)uVar9 & 3);
      pcVar5 = (char *)&local_6a0;
      uVar9 = uVar9 + 1;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
    } while (uVar9 < (uint)((intptr_t)pcVar5 - ((intptr_t)&local_6a0 + 1)));
  }
  FUN_00401290(DAT_00455608,local_6f0,0x602010,0xd07750,0x24f,iVar8);
  iVar1 = iVar6 + 0x1ff;
  FUN_00401290(DAT_00455608,&local_6d4,0x602010,0xd07750,0x24f,iVar1);
  FUN_00401290(DAT_00455608,&local_6a0,0x602010,0xd07750,0x24f,iVar6 + 0x213);
  if ((((0x24f < DAT_004546f0) && (iVar6 + 0x209 < DAT_00453cdc)) &&
      ((DAT_00453cdc < iVar6 + 0x227 || (DAT_0045757c == 0)))) &&
     ((FUN_00401290(DAT_00455608,&local_6a0,0x602010,0xffffff,0x24f,iVar6 + 0x213),
      DAT_004513c4 == 0 && (DAT_00457580 == 1)))) {
    DAT_00457580 = 0;
    FUN_00401a30(0);
    Sleep(300);
    ShellExecuteA((HWND)0x0,"open","http://littlefighter.com",(LPCSTR)0x0,(LPCSTR)0x0,1);
  }
  if ((((0x263 < DAT_004546f0) && (DAT_004546f0 < 0x2ae)) && (iVar8 < DAT_00453cdc)) &&
     (DAT_00453cdc < iVar1)) {
    iVar6 = 0;
    do {
      cVar2 = local_6f0[iVar6 + 3];
      local_60b[iVar6 + -0x61] = cVar2;
      iVar6 = iVar6 + 1;
    } while (cVar2 != '\0');
    ((char *)&local_66c.hInstance)[2] = cVar2;
    FUN_00401290(DAT_00455608,&local_66c,0x602010,0xffffff,0x263,iVar8);
    if ((DAT_004513c4 == 0) && (DAT_00457580 == 1)) {
      DAT_00457580 = 0;
      FUN_00401a30(0);
      Sleep(300);
      ShellExecuteA((HWND)0x0,"open","http://martiwong.com",(LPCSTR)0x0,(LPCSTR)0x0,1);
    }
  }
  if (((0x2b4 < DAT_004546f0) && (iVar8 < DAT_00453cdc)) && (DAT_00453cdc < iVar1)) {
    iVar6 = 0;
    do {
      cVar2 = acStack_6e1[iVar6];
      local_60b[iVar6 + -0x61] = cVar2;
      iVar6 = iVar6 + 1;
    } while (cVar2 != '\0');
    local_66c.lpstrFilter = (LPCSTR)((uintptr_t)local_66c.lpstrFilter & 0xffffff00);
    FUN_00401290(DAT_00455608,&local_66c,0x602010,0xffffff,0x2b6,iVar8);
    if ((DAT_004513c4 == 0) && (DAT_00457580 == 1)) {
      DAT_00457580 = 0;
      FUN_00401a30(0);
      Sleep(300);
      ShellExecuteA((HWND)0x0,"open","http://lf2.net/starsky",(LPCSTR)0x0,(LPCSTR)0x0,1);
    }
  }
  uVar4 = local_700;
  iVar6 = DAT_00453da4;
  FUN_0043f010(0xf4,DAT_00453da4 + 0xce,1,1,0,local_700);
  if (DAT_0044f1af < '\x01') {
    uVar13 = 0x33;
  }
  else {
    uVar13 = 0x32;
  }
  FUN_0043f010(0x101,iVar6 + 0x16e,uVar13,1,0,uVar4);
  if (*local_708 == 0) {
    FUN_0043f010(0x121,iVar6 + 0xcc,2,0,0,uVar4);
  }
  if (*local_708 == 1) {
    FUN_0043f010(0x113,iVar6 + 0xe7,3,0,0,uVar4);
  }
  if (*local_708 == 2) {
    FUN_0043f010(0x101,iVar6 + 0x102,4,0,0,uVar4);
  }
  if (*local_708 == 3) {
    FUN_0043f010(0x101,iVar6 + 0x11d,5,0,0,uVar4);
  }
  if (*local_708 == 4) {
    FUN_0043f010(0x122,iVar6 + 0x137,0x26,0,0,uVar4);
  }
  if (*local_708 == 5) {
    FUN_0043f010(299,iVar6 + 0x153,6,0,0,uVar4);
  }
  if (*local_708 == 6) {
    FUN_0043f010(0x101,iVar6 + 0x16e,0x31,0,0,uVar4);
  }
  if (*local_708 == 7) {
    FUN_0043f010(0x138,iVar6 + 0x18a,7,0,0,uVar4);
  }
  FUN_00431b70();
  if (DAT_004513a4 != 0) {
    *local_708 = *local_708 - 1;
    DAT_004513c0 = 0;
    if ((int)*local_708 < 0) {
      *local_708 = 7;
    }
    if (('\0' < DAT_0044f1af) && (*local_708 == 6)) {
      *local_708 = 5;
    }
  }
  if (DAT_004513a8 != 0) {
    uVar9 = *local_708 + 1 & 0x80000007;
    DAT_004513c0 = 0;
    if ((int)uVar9 < 0) {
      uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
    }
    *local_708 = uVar9;
    if (('\0' < DAT_0044f1af) && (uVar9 == 6)) {
      *local_708 = 7;
    }
  }
  if (DAT_004513b4 != 0) {
    DAT_004513c0 = 0;
    if ((int)*local_708 < 7) {
      FUN_00401a30(0);
    }
    puVar11 = local_704;
    if (*local_708 == 0) {
      *local_6f8 = 0;
      *local_704 = 3;
      DAT_0044d024 = 100;
      DAT_0044d028 = 1;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 1) {
      *local_6f8 = 0;
      *puVar11 = 3;
      DAT_0044d024 = 100;
      DAT_0044d028 = 1;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 2) {
      *puVar11 = 0x14;
      DAT_0044d024 = 0;
      DAT_0044d028 = 0;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 3) {
      *puVar11 = 0x78;
      DAT_0044d024 = 0;
      DAT_0044d028 = 0;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 4) {
      *local_6f8 = 0;
      *puVar11 = 3;
      DAT_0044d024 = 100;
      DAT_0044d028 = 1;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 5) {
      *puVar11 = 2;
      DAT_00450c2c = 1;
      DAT_004513c0 = 0;
      DAT_0044d780 = 0xffffffff;
      FUN_00423910();
    }
    if (*local_708 == 6) {
      FUN_00431c70();
      Sleep(300);
      memset(local_608,0,0x104);
      memset(&local_66c,0,0x58);
      local_66c.lpstrFile = local_608;
      local_66c.lStructSize = 0x58;
      local_66c.hwndOwner = (HWND)0x0;
      builtin_memcpy(local_504,"c:\\",4);
      local_66c.lpstrFilter = "LF2 recording files (*.lfr)";
      pcVar5 = _getcwd((char *)0x0,0);
      if (pcVar5 != (char *)0x0) {
        pcVar10 = pcVar5;
        do {
          cVar2 = *pcVar10;
          pcVar10[(intptr_t)(local_504 + -(intptr_t)pcVar5)] = cVar2;
          pcVar10 = pcVar10 + 1;
        } while (cVar2 != '\0');
        pcVar10 = pcVar5;
        do {
          cVar2 = *pcVar10;
          pcVar10[(intptr_t)(local_400 + -(intptr_t)pcVar5)] = cVar2;
          pcVar10 = pcVar10 + 1;
        } while (cVar2 != '\0');
        free(pcVar5);
        pcVar5 = &cStack_505;
        do {
          pcVar10 = pcVar5;
          pcVar5 = pcVar10 + 1;
        } while (pcVar10[1] != '\0');
        builtin_strncpy(pcVar10 + 1,"\\recording",0xb);
      }
      local_66c.lpstrInitialDir = local_504;
      local_66c.lpstrFileTitle = local_108;
      local_66c.nMaxFile = 0x103;
      local_66c.nMaxFileTitle = 0x103;
      local_66c.Flags = 0x1804;
      BVar7 = GetOpenFileNameA(&local_66c);
      if (BVar7 != 0) {
        _chdir(local_400);
        FUN_0043d280((undefined4 *)(uintptr_t)&DAT_004588ac);
        pcVar5 = local_608;
        do {
          cVar2 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
        iVar6 = (int)((intptr_t)pcVar5 - (intptr_t)(local_608 + 1));
        if ((((iVar6 < 5) || (local_60b[iVar6 + -1] != '.')) ||
            ((local_60b[iVar6] != 't' && (local_60b[iVar6] != 'T')))) ||
           (((local_60b[iVar6 + 1] != 'x' && (local_60b[iVar6 + 1] != 'X')) ||
            ((local_60b[iVar6 + 2] != 't' && (local_60b[iVar6 + 2] != 'T')))))) {
          iVar6 = FUN_0043e620(local_608);
          puVar3 = local_708;
          if (iVar6 == 0) {
            MessageBoxA((HWND)0x0,"Loading error!  Recording file may be corrupted!!",(LPCSTR)0x0,0)
            ;
          }
          else if (iVar6 == -1) {
            MessageBoxA((HWND)0x0,
                        "File path error!  File path should not contain chinese or unicode character!"
                        ,(LPCSTR)0x0,0);
          }
          else {
            FUN_0043dfa0(local_708,local_6fc + 4,local_6fc + 0x194,
                         *(undefined4 *)(uintptr_t)(local_6fc + 0x7d4));
            if (*(int *)(uintptr_t)(DAT_004588ac + 0x744) == DAT_0044f620) {
              if (*(int *)(uintptr_t)(DAT_004588ac + 0x748) == DAT_0044d03c) {
                DAT_0044d380 = *(int *)(uintptr_t)(DAT_004588ac + 0x8c0) / 10000000 + -1;
                DAT_00451b74 = (*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 10000000) / 1000000 + -1;
                DAT_0044d758 = ((*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 100000) / 10000 +
                               ((*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 1000000) / 100000) * 10) * 10;
                DAT_0044d384 = (*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 10000) / 1000 + -1;
                DAT_00451b78 = (*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 1000) / 100 + -1;
                DAT_0044d75c = (*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 10 +
                               ((*(int *)(uintptr_t)(DAT_004588ac + 0x8c0) % 100) / 10) * 10) * 10;
                *local_704 = 0;
                goto LAB_004328cc;
              }
              local_6d4 = local_6d4 & 0xffffff00;
              local_6a0 = local_6a0 & 0xffffff00;
              if (*(int *)(uintptr_t)(DAT_004588ac + 0x748) == 0x1e) {
                local_6d4 = 0x302e3276;
                local_6d0 = local_6d0 & 0xffffff00;
              }
              if (DAT_0044d03c < *(int *)(uintptr_t)(DAT_004588ac + 0x748)) {
                ((char *)&local_6d4)[0] = 'a';
                ((char *)&local_6d4)[1] = ' ';
                ((char *)&local_6d4)[2] = 'n';
                ((char *)&local_6d4)[3] = 'e';
                ((char *)&local_6d0)[0] = 'w';
                ((char *)&local_6d0)[1] = 'e';
                ((char *)&local_6d0)[2] = 'r';
                ((char *)&local_6d0)[3] = ' ';
                builtin_strncpy(local_6cc,"version",8);
              }
              if (DAT_0044d03c == 0x1e) {
                local_6a0 = 0x302e3276;
                local_69c = 0;
              }
              sprintf(local_2fc,
                      "Version error.  Recording file are recorded in %s. (your LF2 is %s)!",
                      (char *)&local_6d4,(char *)&local_6a0);
              pcVar5 = local_2fc;
            }
            else {
              pcVar5 = 
              "Error!  Recording file are recorded in a LF2 with some data files (character or stage files) different from yours.  Your LF2 has to use the same set of data files in order in replay this recording file!"
              ;
            }
            MessageBoxA((HWND)0x0,pcVar5,(LPCSTR)0x0,0);
            DAT_00450b88 = 0;
            DAT_00450b84 = 0;
            *puVar3 = 6;
          }
        }
        else {
          ShellExecuteA((HWND)0x0,"open",local_608,(LPCSTR)0x0,(LPCSTR)0x0,1);
        }
      }
LAB_004328cc:
      _chdir(local_400);
    }
    if ((*local_708 == 7) && (FUN_004019b0(), DAT_00458434 == 0)) {
      PostQuitMessage(0);
    }
  }
  FUN_00423b00(&DAT_004513c4,local_700);
  if (0 < DAT_004513c0) {
    FUN_0043f010(5,0x27,7,1,0,local_700);
    iVar6 = 0;
    puVar11 = (undefined4 *)&DAT_0044fb74;
    do {
      iVar8 = 0x5d;
      puVar12 = puVar11;
      do {
        FUN_00422b00(*puVar12,local_6f0,&local_704);
        FUN_00401290(DAT_00455608,local_6f0,0x652512,0xffffff,(iVar6 - (int)(intptr_t)local_704) + 0x82,iVar8)
        ;
        iVar8 = iVar8 + 0x14;
        puVar12 = puVar12 + 1;
      } while (iVar8 < 0xe9);
      puVar11 = puVar11 + 0x14;
      iVar6 = iVar6 + 0x6c;
    } while ((uintptr_t)puVar11 < (uintptr_t)0x44fcb4);
    DAT_004513c0 = DAT_004513c0 + -1;
  }
  iVar8 = DAT_00453cdc + 2;
  iVar6 = DAT_004546f0;
  if (0x307 < DAT_004546f0) {
    iVar6 = 0x307;
  }
  if (0x217 < iVar8) {
    iVar8 = 0x217;
  }
  FUN_0043f010(iVar6,iVar8,0xffffffff,1,0,local_700);
  if (0xde < DAT_004546f0) {
    if (DAT_00453cdc <= DAT_00453da4 + 0xc2) {
LAB_00432a49:
      DAT_004513c4 = DAT_00457580;
      __security_check_cookie(local_4 ^ (uint)(uintptr_t)&local_708);
      return;
    }
    if (0x23d < DAT_004546f0) {
      DAT_004513c4 = DAT_00457580;
      __security_check_cookie(local_4 ^ (uint)(uintptr_t)&local_708);
      return;
    }
    if (DAT_00453cdc < DAT_00453da4 + 0x1b0) {
      if ((DAT_00457580 != 1) || (DAT_004546f0 == 0)) goto LAB_00432a49;
      DAT_00457580 = 0;
      DAT_004513c0 = 0x1c2;
    }
  }
  DAT_004513c4 = DAT_00457580;
  __security_check_cookie(local_4 ^ (uint)(uintptr_t)&local_708);
  return;
}
