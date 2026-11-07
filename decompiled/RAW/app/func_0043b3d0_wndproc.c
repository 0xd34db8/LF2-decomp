/*
 * Procedure: FUN_0043b3d0 (LF2_WindowProc)
 * Address: 0x0043b3d0 - 0x0043bdcf (Length: 2560 bytes)
 * Purpose: LF2 Main Window Procedure (WndProc) - handles window messages, palette, joysticks, keyboard, mouse, and cheats
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


LRESULT LF2_WindowProc(HWND param_1,uint param_2,HWND param_3,uint param_4)

{
  int iVar1;
  int xRight;
  LRESULT LVar2;
  bool bVar3;
  
  if (0x200 < param_2) {
    if (param_2 < 0x310) {
      if (param_2 == 0x30f) {
        if ((DAT_00455634 == (int *)0x0) || (DAT_004554c4 == 0)) {
          OutputDebugStringA("Ignoring palette message.\n");
          return 1;
        }
        OutputDebugStringA("We have the palette.\n");
        (**(code **)(*DAT_00455634 + 0x7c))(DAT_00455634,DAT_004554c4);
      }
      else {
        switch(param_2) {
        case 0x201:
          DAT_00457580 = 1;
          break;
        case 0x202:
          DAT_00457580 = 0;
          break;
        case 0x204:
          DAT_004527e4 = 1;
          break;
        case 0x205:
          DAT_004527e4 = 0;
        }
      }
    }
    else {
      switch(param_2) {
      case 0x311:
        if (param_3 != param_1) {
          OutputDebugStringA("Palette lost.\n");
          (**(code **)(*DAT_00455634 + 0x7c))(DAT_00455634,DAT_004554c4);
        }
        break;
      case 0x3a0:
        iVar1 = DAT_00453fe0 + DAT_00453fd8 * 3;
        DAT_00453fe8 = param_4 & 0xffff;
        DAT_00453fec = param_4 >> 0x10;
        DAT_00453ff2 = 0;
        DAT_00453ff3 = 0;
        DAT_00453ff1 = 0;
        DAT_00453ff0 = 0;
        if ((int)DAT_00453fe8 < (int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) {
          DAT_00453ff3 = 1;
        }
        else {
          iVar1 = DAT_00453fd8 + DAT_00453fe0 * 3;
          if ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2 < (int)DAT_00453fe8) {
            DAT_00453ff2 = 1;
          }
        }
        iVar1 = DAT_00453fe4 + DAT_00453fdc * 3;
        if ((int)DAT_00453fec < (int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) {
          DAT_00453ff0 = 1;
        }
        else {
          iVar1 = DAT_00453fdc + DAT_00453fe4 * 3;
          if ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2 < (int)DAT_00453fec) {
            DAT_00453ff1 = 1;
          }
        }
        break;
      case 0x3a1:
        iVar1 = DAT_00454010 + DAT_00454008 * 3;
        DAT_00454018 = param_4 & 0xffff;
        DAT_0045401c = param_4 >> 0x10;
        DAT_00454022 = 0;
        DAT_00454023 = 0;
        DAT_00454021 = 0;
        DAT_00454020 = 0;
        if ((int)DAT_00454018 < (int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) {
          DAT_00454023 = 1;
        }
        else {
          iVar1 = DAT_00454008 + DAT_00454010 * 3;
          if ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2 < (int)DAT_00454018) {
            DAT_00454022 = 1;
          }
        }
        iVar1 = DAT_00454014 + DAT_0045400c * 3;
        if ((int)DAT_0045401c < (int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2) {
          DAT_00454020 = 1;
        }
        else {
          iVar1 = DAT_0045400c + DAT_00454014 * 3;
          if ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2 < (int)DAT_0045401c) {
            DAT_00454021 = 1;
          }
        }
        break;
      case 0x3b5:
        if (((uint)param_3 & 1) != 0) {
          DAT_00453ff4._0_1_ = 1;
        }
        if (((uint)param_3 & 2) != 0) {
          DAT_00453ff4._1_1_ = 1;
        }
        if (((uint)param_3 & 4) != 0) {
          DAT_00453ff4._2_1_ = 1;
        }
        if (((uint)param_3 & 8) != 0) {
          DAT_00453ff4._3_1_ = 1;
        }
        break;
      case 0x3b6:
        if (((uint)param_3 & 1) != 0) {
          DAT_00454024._0_1_ = 1;
        }
        if (((uint)param_3 & 2) != 0) {
          DAT_00454024._1_1_ = 1;
        }
        if (((uint)param_3 & 4) != 0) {
          DAT_00454024._2_1_ = 1;
        }
        if (((uint)param_3 & 8) != 0) {
          DAT_00454024._3_1_ = 1;
        }
        break;
      case 0x3b7:
        if (((uint)param_3 & 1) == 0) {
          DAT_00453ff4._0_1_ = 0;
        }
        if (((uint)param_3 & 2) == 0) {
          DAT_00453ff4._1_1_ = 0;
        }
        if (((uint)param_3 & 4) == 0) {
          DAT_00453ff4._2_1_ = 0;
        }
        if (((uint)param_3 & 8) == 0) {
          DAT_00453ff4._3_1_ = 0;
        }
        break;
      case 0x3b8:
        if (((uint)param_3 & 1) == 0) {
          DAT_00454024._0_1_ = 0;
        }
        if (((uint)param_3 & 2) == 0) {
          DAT_00454024._1_1_ = 0;
        }
        if (((uint)param_3 & 4) == 0) {
          DAT_00454024._2_1_ = 0;
        }
        if (((uint)param_3 & 8) == 0) {
          DAT_00454024._3_1_ = 0;
        }
        break;
      case 0x400:
        FUN_00401e90();
        break;
      case 0x401:
        FUN_00402ec0(param_1,param_3,param_4);
      }
    }
    goto switchD_0043b417_caseD_4;
  }
  if (param_2 == 0x200) {
    DAT_004546f0 = param_4 & 0xffff;
    DAT_00453cdc = param_4 >> 0x10;
    goto switchD_0043b417_caseD_4;
  }
  if (param_2 < 0x21) {
    if (param_2 == 0x20) {
      if (DAT_00458430 != 0) {
        SetCursor((HCURSOR)0x0);
      }
      return 0;
    }
    switch(param_2) {
    case 2:
      FUN_004019b0();
      FUN_00401d30();
      FUN_0043d2a0();
      if (DAT_00458434 == 0) {
        PostQuitMessage(0);
      }
      return 0;
    case 3:
      if (DAT_00458430 == 0) {
        GetClientRect(param_1,(LPRECT)&DAT_00453ccc);
        ClientToScreen(param_1,(LPPOINT)&DAT_00453ccc);
        ClientToScreen(param_1,(LPPOINT)&DAT_00453cd4);
      }
      else {
        iVar1 = GetSystemMetrics(1);
        xRight = GetSystemMetrics(0);
        SetRect((LPRECT)&DAT_00453ccc,0,0,xRight,iVar1);
      }
      break;
    case 5:
      if (param_3 == (HWND)0x1) {
        InvalidateRect(param_1,(RECT *)0x0,1);
        DAT_00451dac = 0;
        return 0;
      }
      DAT_00451dac = 1;
      return 0;
    case 0x1c:
      OutputDebugStringA("Active App!\n ");
    }
    goto switchD_0043b417_caseD_4;
  }
  switch(param_2) {
  case 0x100:
    if (DAT_00458440 == 1) {
      FUN_004031d0(param_3);
    }
    iVar1 = DAT_0045857c;
    bVar3 = DAT_0045857c == 0;
    *(undefined1 *)&param_3[0x1154de].unused = 100;
    if (bVar3) {
      if (param_3 == (HWND)0x4c) {
        DAT_0045857c = 1;
      }
      else {
LAB_0043b610:
        DAT_0045857c = 0;
      }
    }
    else if (iVar1 == 1) {
      if (param_3 == (HWND)0x46) {
        DAT_0045857c = 2;
      }
      else {
        bVar3 = param_3 == (HWND)0x4c;
LAB_0043b60e:
        if (!bVar3) goto LAB_0043b610;
      }
    }
    else if (iVar1 == 2) {
      if (param_3 != (HWND)0x32) {
        bVar3 = param_3 == (HWND)0x46;
        goto LAB_0043b60e;
      }
      DAT_0045857c = 3;
    }
    else if (iVar1 == 3) {
      if (param_3 != (HWND)0xbe) {
        bVar3 = param_3 == (HWND)0x32;
        goto LAB_0043b60e;
      }
      DAT_0045857c = 4;
    }
    else if (iVar1 == 4) {
      if (param_3 != (HWND)0x4e) {
        bVar3 = param_3 == (HWND)0xbe;
        goto LAB_0043b60e;
      }
      DAT_0045857c = 5;
    }
    else if (iVar1 == 5) {
      if (param_3 != (HWND)0x45) {
        bVar3 = param_3 == (HWND)0x4e;
        goto LAB_0043b60e;
      }
      DAT_0045857c = 6;
    }
    else {
      if (iVar1 != 6) goto LAB_0043b610;
      if (param_3 != (HWND)0x54) {
        bVar3 = param_3 == (HWND)0x45;
        goto LAB_0043b60e;
      }
      DAT_00455471 = 100;
    }
    if (DAT_00458578 == 0) {
      if (param_3 == (HWND)0x48) {
        DAT_00458578 = 1;
      }
      else {
LAB_0043b7d1:
        DAT_00458578 = 0;
      }
    }
    else if (DAT_00458578 == 1) {
      if (param_3 == (HWND)0x45) {
        DAT_00458578 = 2;
      }
      else {
LAB_0043b79c:
        bVar3 = param_3 == (HWND)0x48;
LAB_0043b7cf:
        if (!bVar3) goto LAB_0043b7d1;
      }
    }
    else if (DAT_00458578 == 2) {
      if (param_3 != (HWND)0x52) {
LAB_0043b7a1:
        bVar3 = param_3 == (HWND)0x45;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 3;
    }
    else if (DAT_00458578 == 3) {
      if (param_3 != (HWND)0x4f) {
LAB_0043b7a6:
        bVar3 = param_3 == (HWND)0x52;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 4;
    }
    else if (DAT_00458578 == 4) {
      if (param_3 != (HWND)0x46) {
LAB_0043b7cc:
        bVar3 = param_3 == (HWND)0x4f;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 5;
    }
    else if (DAT_00458578 == 5) {
      if (param_3 != (HWND)0x49) {
        bVar3 = param_3 == (HWND)0x46;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 6;
    }
    else if (DAT_00458578 == 6) {
      if (param_3 != (HWND)0x47) {
        bVar3 = param_3 == (HWND)0x49;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 7;
    }
    else if (DAT_00458578 == 7) {
      if (param_3 != (HWND)0x48) {
        bVar3 = param_3 == (HWND)0x47;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 8;
    }
    else if (DAT_00458578 == 8) {
      if (param_3 != (HWND)0x54) goto LAB_0043b79c;
      DAT_00458578 = 9;
    }
    else if (DAT_00458578 == 9) {
      if (param_3 != (HWND)0x45) {
        bVar3 = param_3 == (HWND)0x54;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 10;
    }
    else if (DAT_00458578 == 10) {
      if (param_3 != (HWND)0x52) goto LAB_0043b7a1;
      DAT_00458578 = 0xb;
    }
    else if (DAT_00458578 == 0xb) {
      if (param_3 != (HWND)0xbe) goto LAB_0043b7a6;
      DAT_00458578 = 0xc;
    }
    else if (DAT_00458578 == 0xc) {
      if (param_3 != (HWND)0x43) {
        bVar3 = param_3 == (HWND)0xbe;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 0xd;
    }
    else if (DAT_00458578 == 0xd) {
      if (param_3 != (HWND)0x4f) {
        bVar3 = param_3 == (HWND)0x43;
        goto LAB_0043b7cf;
      }
      DAT_00458578 = 0xe;
    }
    else {
      if (DAT_00458578 != 0xe) goto LAB_0043b7d1;
      if (param_3 != (HWND)0x4d) goto LAB_0043b7cc;
      DAT_00455470 = 100;
    }
    if (param_3 == (HWND)0x1b) {
      iVar1 = MessageBoxA(param_1,"Are you sure to quit?","LF2",4);
      if (iVar1 == 6) {
        FUN_004019b0();
        FUN_00401d30();
        FUN_0043d2a0();
        PostMessageA(param_1,0x10,0,0);
      }
      return 0;
    }
    if (param_3 == (HWND)0x90) {
      return 0;
    }
    break;
  case 0x101:
    *(undefined1 *)&param_3[0x1154de].unused = 0x75;
    break;
  case 0x105:
    if ((param_3 == (HWND)0xd) && (OutputDebugStringA("Alt enter...\n"), DAT_0044d794 != 0)) {
      DAT_00458434 = 1;
      DAT_00458430 = (uint)(DAT_00458430 == 0);
      FUN_00401ae0();
      iVar1 = FUN_0043bdd0();
      if (iVar1 < 0) {
        OutputDebugStringA("Reinitialization failed.\n");
      }
      ShowWindow(DAT_004546f4,5);
      DAT_00458434 = 0;
    }
    break;
  case 0x112:
    if (param_3 == (HWND)0xf100) {
      return 1;
    }
  }
switchD_0043b417_caseD_4:
  LVar2 = DefWindowProcA(param_1,param_2,(WPARAM)param_3,param_4);
  return LVar2;
}

