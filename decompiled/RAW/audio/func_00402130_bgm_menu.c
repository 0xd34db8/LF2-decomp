/*
 * Procedure: FUN_00402130
 * Address: 0x00402130 - 0x004025a5 (Length: 1142 bytes)
 * Purpose: In-Game & Menu BGM Selector, HUD String Renderer & Track Cycler (Music: %s)
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00402130(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 == 1) {
    if ((param_2 == 0) && (param_3 == 0)) {
      if (DAT_0044f18c != -1) goto LAB_004021c2;
    }
    else {
      if (DAT_0044f18c == -1) {
        DAT_0044f18c = 0;
LAB_004021c2:
        DAT_0044f128 = 'O';
        DAT_0044f128_1._0_1_ = 'N';
        DAT_0044f12a = '\0';
        goto LAB_00402530;
      }
      DAT_0044f18c = -1;
    }
  }
  else {
    if (param_3 != 0) {
      DAT_0044f18c = DAT_0044f18c + 1;
    }
    if (8 < DAT_0044f18c) {
      DAT_0044f18c = -1;
    }
    if (param_2 != 0) {
      DAT_0044f18c = DAT_0044f18c + -1;
    }
    if (DAT_0044f18c < -1) {
      DAT_0044f18c = 8;
LAB_004022f1:
      DAT_0044f128 = 'F';
      DAT_0044f128_1._0_1_ = 'i';
      DAT_0044f12a = 'n';
      DAT_0044f128_1._2_1_ = 'a';
      _DAT_0044f130 = 0x7373;
      DAT_0044f12c = 'l';
      DAT_0044f12c_1._0_1_ = ' ';
      DAT_0044f12e = 'B';
      DAT_0044f12c_1._2_1_ = 'o';
LAB_00402313:
      DAT_0044f132 = 0;
    }
    else if (DAT_0044f18c == 0) {
      DAT_0044f128 = 'R';
      DAT_0044f128_1._0_1_ = 'a';
      DAT_0044f12a = 'n';
      DAT_0044f128_1._2_1_ = 'd';
      _DAT_0044f12c = CONCAT13(DAT_0044f12c_1._2_1_,0x6d6f);
    }
    else {
      if (DAT_0044f18c == 1) {
        DAT_0044f128 = 'M';
        DAT_0044f128_1._0_1_ = 'a';
        DAT_0044f12a = 'i';
        DAT_0044f128_1._2_1_ = 'n';
        _DAT_0044f130 = 0x656d;
        DAT_0044f12c = ' ';
        DAT_0044f12c_1._0_1_ = 'T';
        DAT_0044f12e = 'h';
        DAT_0044f12c_1._2_1_ = 'e';
        goto LAB_00402313;
      }
      if (DAT_0044f18c == 2) {
        DAT_0044f128 = 'S';
        DAT_0044f128_1._0_1_ = 't';
        DAT_0044f12a = 'a';
        DAT_0044f128_1._2_1_ = 'g';
        DAT_0044f12c = 'e';
        DAT_0044f12c_1._0_1_ = ' ';
        DAT_0044f12e = '1';
        DAT_0044f12c_1._2_1_ = '\0';
      }
      else if (DAT_0044f18c == 3) {
        DAT_0044f128 = 'S';
        DAT_0044f128_1._0_1_ = 't';
        DAT_0044f12a = 'a';
        DAT_0044f128_1._2_1_ = 'g';
        DAT_0044f12c = 'e';
        DAT_0044f12c_1._0_1_ = ' ';
        DAT_0044f12e = '2';
        DAT_0044f12c_1._2_1_ = '\0';
      }
      else if (DAT_0044f18c == 4) {
        DAT_0044f128 = 'S';
        DAT_0044f128_1._0_1_ = 't';
        DAT_0044f12a = 'a';
        DAT_0044f128_1._2_1_ = 'g';
        DAT_0044f12c = 'e';
        DAT_0044f12c_1._0_1_ = ' ';
        DAT_0044f12e = '3';
        DAT_0044f12c_1._2_1_ = '\0';
      }
      else if (DAT_0044f18c == 5) {
        DAT_0044f128 = 'S';
        DAT_0044f128_1._0_1_ = 't';
        DAT_0044f12a = 'a';
        DAT_0044f128_1._2_1_ = 'g';
        DAT_0044f12c = 'e';
        DAT_0044f12c_1._0_1_ = ' ';
        DAT_0044f12e = '4';
        DAT_0044f12c_1._2_1_ = '\0';
      }
      else if (DAT_0044f18c == 6) {
        DAT_0044f128 = 'S';
        DAT_0044f128_1._0_1_ = 't';
        DAT_0044f12a = 'a';
        DAT_0044f128_1._2_1_ = 'g';
        DAT_0044f12c = 'e';
        DAT_0044f12c_1._0_1_ = ' ';
        DAT_0044f12e = '5';
        DAT_0044f12c_1._2_1_ = '\0';
      }
      else if (DAT_0044f18c == 7) {
        DAT_0044f128 = 'B';
        DAT_0044f128_1._0_1_ = 'o';
        DAT_0044f12a = 's';
        DAT_0044f128_1._2_1_ = 's';
        _DAT_0044f12c = _DAT_0044f12c & 0xffffff00;
      }
      else if (DAT_0044f18c == 8) goto LAB_004022f1;
    }
    iVar1 = DAT_0044f18c;
    if (DAT_0044f18c == 0) {
      iVar1 = FUN_00417170(1,8);
      iVar1 = iVar1 + 1;
    }
    if (iVar1 == 1) {
      _DAT_0044eed0 = 0x5c6d6762;
      DAT_0044eed4 = 'm';
      DAT_0044eed4_1._0_1_ = 'a';
      DAT_0044eed4_1._1_1_ = 'i';
      DAT_0044eed4_1._2_1_ = 'n';
      DAT_0044eed8 = '.';
      DAT_0044eed8_1._0_1_ = 'w';
      DAT_0044eed8_1._1_1_ = 'm';
      DAT_0044eed8_1._2_1_ = 'a';
      _DAT_0044eedc = _DAT_0044eedc & 0xff00;
    }
    else if (iVar1 == 2) {
      DAT_0044eed0 = 'b';
      DAT_0044eed1 = 'g';
      DAT_0044eed0_1._1_1_ = 'm';
      DAT_0044eed0_1._2_1_ = '\\';
      DAT_0044eed4 = 's';
      DAT_0044eed4_1._0_1_ = 't';
      DAT_0044eed4_1._1_1_ = 'a';
      DAT_0044eed4_1._2_1_ = 'g';
      DAT_0044eed8 = 'e';
      DAT_0044eed8_1._0_1_ = '1';
      DAT_0044eed8_1._1_1_ = '.';
      DAT_0044eed8_1._2_1_ = 'w';
      _DAT_0044eedc = 0x616d;
      DAT_0044eede = 0;
    }
    else if (iVar1 == 3) {
      DAT_0044eed0 = 'b';
      DAT_0044eed1 = 'g';
      DAT_0044eed0_1._1_1_ = 'm';
      DAT_0044eed0_1._2_1_ = '\\';
      DAT_0044eed4 = 's';
      DAT_0044eed4_1._0_1_ = 't';
      DAT_0044eed4_1._1_1_ = 'a';
      DAT_0044eed4_1._2_1_ = 'g';
      DAT_0044eed8 = 'e';
      DAT_0044eed8_1._0_1_ = '2';
      DAT_0044eed8_1._1_1_ = '.';
      DAT_0044eed8_1._2_1_ = 'w';
      _DAT_0044eedc = 0x616d;
      DAT_0044eede = 0;
    }
    else if (iVar1 == 4) {
      _DAT_0044eed0 = 0x5c6d6762;
      DAT_0044eed4 = 's';
      DAT_0044eed4_1._0_1_ = 't';
      DAT_0044eed4_1._1_1_ = 'a';
      DAT_0044eed4_1._2_1_ = 'g';
      DAT_0044eed8 = 'e';
      DAT_0044eed8_1._0_1_ = '3';
      DAT_0044eed8_1._1_1_ = '.';
      DAT_0044eed8_1._2_1_ = 'w';
      _DAT_0044eedc = 0x616d;
      DAT_0044eede = 0;
    }
    else if (iVar1 == 5) {
      _DAT_0044eed0 = 0x5c6d6762;
      DAT_0044eed4 = 's';
      DAT_0044eed4_1._0_1_ = 't';
      DAT_0044eed4_1._1_1_ = 'a';
      DAT_0044eed4_1._2_1_ = 'g';
      DAT_0044eed8 = 'e';
      DAT_0044eed8_1._0_1_ = '4';
      DAT_0044eed8_1._1_1_ = '.';
      DAT_0044eed8_1._2_1_ = 'w';
      _DAT_0044eedc = 0x616d;
      DAT_0044eede = 0;
    }
    else if (iVar1 == 6) {
      _DAT_0044eed0 = 0x5c6d6762;
      DAT_0044eed4 = 's';
      DAT_0044eed4_1._0_1_ = 't';
      DAT_0044eed4_1._1_1_ = 'a';
      DAT_0044eed4_1._2_1_ = 'g';
      DAT_0044eed8 = 'e';
      DAT_0044eed8_1._0_1_ = '5';
      DAT_0044eed8_1._1_1_ = '.';
      DAT_0044eed8_1._2_1_ = 'w';
      _DAT_0044eedc = 0x616d;
      DAT_0044eede = 0;
    }
    else if (iVar1 == 7) {
      _DAT_0044eed0 = 0x5c6d6762;
      DAT_0044eed4 = 'b';
      DAT_0044eed4_1._0_1_ = 'o';
      DAT_0044eed4_1._1_1_ = 's';
      DAT_0044eed4_1._2_1_ = 's';
      DAT_0044eed8 = '1';
      DAT_0044eed8_1._0_1_ = '.';
      DAT_0044eed8_1._1_1_ = 'w';
      DAT_0044eed8_1._2_1_ = 'm';
      _DAT_0044eedc = 0x61;
    }
    else if (iVar1 == 8) {
      DAT_0044eed0 = 'b';
      DAT_0044eed1 = 'g';
      DAT_0044eed0_1._1_1_ = 'm';
      DAT_0044eed0_1._2_1_ = '\\';
      DAT_0044eed4 = 'b';
      DAT_0044eed4_1._0_1_ = 'o';
      DAT_0044eed4_1._1_1_ = 's';
      DAT_0044eed4_1._2_1_ = 's';
      DAT_0044eed8 = '2';
      DAT_0044eed8_1._0_1_ = '.';
      DAT_0044eed8_1._1_1_ = 'w';
      DAT_0044eed8_1._2_1_ = 'm';
      _DAT_0044eedc = 0x61;
    }
    else if (iVar1 == -1) {
      _DAT_0044eed0 = _DAT_0044eed0 & 0xffffff00;
    }
LAB_00402530:
    if (DAT_0044f18c != -1) {
      DAT_0044d010 = 1;
      goto LAB_00402556;
    }
  }
  DAT_0044f128 = 'O';
  DAT_0044f128_1._0_1_ = 'F';
  DAT_0044f12a = 'F';
  DAT_0044f128_1._2_1_ = '\0';
  DAT_0044d010 = 0;
  FUN_00402100();
LAB_00402556:
  sprintf(&DAT_0044f060,"Music: %s",&DAT_0044f128);
  FUN_00401290(param_4,&DAT_0044f060,0,0xd8775a,0x25b,3);
  FUN_00401290(param_4,"(Press Left/Right to change)",0,0xa03f22,0x25b,0x14);
  return;
}
