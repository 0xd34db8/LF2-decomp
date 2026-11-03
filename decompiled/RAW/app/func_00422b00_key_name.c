/*
 * Function: Virtual Key Code to Friendly Display Name & Render Offset
 * Virtual Address: 0x00422B00
 * Calling Convention: __cdecl
 *
 * Parameters:
 *   param_1: Virtual key code (int)
 *   param_2: Output string buffer for key name (char*)
 *   param_3: Output horizontal rendering offset / width adjustment (int*)
 *
 * Description:
 *   Maps Win32 virtual key codes (e.g., VK_SPACE, VK_RETURN, A-Z, 0-9,
 *   Numpad 0-9, Arrow keys, modifiers) to human-readable strings and
 *   calculates character font offset width adjustments.
 */

#include <string.h>

void FUN_00422b00(int param_1, char *param_2, int *param_3)
{
  char cVar1;

  strncpy(param_2, "none", 5);
  *param_3 = 8;
  if (param_1 == 0x20) {
    strncpy(param_2, "Space", 6);
    *param_3 = 10;
    return;
  }
  if (param_1 == 0xd) {
    strncpy(param_2, "Enter", 6);
    *param_3 = 10;
    return;
  }
  cVar1 = (char)param_1;
  if ((param_1 < 0x41) || (0x5a < param_1)) {
    if ((param_1 < 0x60) || (0x69 < param_1)) {
      if (param_1 == 0x6b) {
        strncpy(param_2, "Keypad: +", 10);
        *param_3 = 0xf;
        return;
      }
      if (param_1 == 0x6d) {
        strncpy(param_2, "Keypad: -", 10);
        *param_3 = 0xf;
        return;
      }
      if (param_1 == 0x6a) {
        strncpy(param_2, "Keypad: *", 10);
        *param_3 = 0xf;
        return;
      }
      if (param_1 == 0x6f) {
        strncpy(param_2, "Keypad: /", 10);
        *param_3 = 0xf;
        return;
      }
      if (param_1 == 0x6e) {
        strncpy(param_2, "Keypad: .", 10);
        *param_3 = 0xf;
        return;
      }
    }
    else {
      param_2[0] = 'K';
      param_2[1] = 'e';
      param_2[2] = 'y';
      param_2[3] = 'p';
      param_2[4] = 'a';
      param_2[5] = 'd';
      param_2[6] = ':';
      param_2[7] = ' ';
      param_2[8] = cVar1 - 0x30;
      param_2[9] = '\0';
      *param_3 = 0xf;
      return;
    }
  }
  else {
    param_2[0] = cVar1;
    param_2[1] = '\0';
    *param_3 = 0;
    return;
  }
  if ((0x2f < param_1) && (param_1 < 0x3a)) {
    param_2[0] = cVar1;
    param_2[1] = '\0';
    *param_3 = 0;
    return;
  }
  if (param_1 == 0xbd) {
    *param_3 = 0;
    param_2[0] = '-';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xbb) {
    *param_3 = 0;
    param_2[0] = '=';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xdb) {
    *param_3 = 0;
    param_2[0] = '[';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xdd) {
    *param_3 = 0;
    param_2[0] = ']';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xba) {
    *param_3 = 0;
    param_2[0] = ';';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xde) {
    *param_3 = 0;
    param_2[0] = '\'';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xdc) {
    *param_3 = 0;
    param_2[0] = '\\';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xbc) {
    *param_3 = 0;
    param_2[0] = ',';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xbe) {
    *param_3 = 0;
    param_2[0] = '.';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xbf) {
    *param_3 = 0;
    param_2[0] = '/';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0xc0) {
    *param_3 = 0;
    param_2[0] = '`';
    param_2[1] = '\0';
    return;
  }
  if (param_1 == 0x11) {
    *param_3 = 7;
    strncpy(param_2, "Ctrl", 5);
    return;
  }
  if (param_1 == 0x10) {
    *param_3 = 7;
    strncpy(param_2, "Shift", 6);
    return;
  }
  if (param_1 == 9) {
    *param_3 = 5;
    strncpy(param_2, "Tab", 4);
    return;
  }
  if (param_1 == 8) {
    *param_3 = 0xd;
    strncpy(param_2, "Backspace", 10);
    return;
  }
  if (param_1 == 0x2d) {
    *param_3 = 8;
    strncpy(param_2, "Insert", 7);
    return;
  }
  if (param_1 == 0x2e) {
    *param_3 = 8;
    strncpy(param_2, "Delete", 7);
    return;
  }
  if (param_1 == 0x24) {
    *param_3 = 6;
    strncpy(param_2, "Home", 5);
    return;
  }
  if (param_1 == 0x23) {
    *param_3 = 5;
    strncpy(param_2, "End", 4);
    return;
  }
  if (param_1 == 0x21) {
    *param_3 = 10;
    strncpy(param_2, "PageUp", 7);
    return;
  }
  if (param_1 == 0x22) {
    *param_3 = 0xe;
    strncpy(param_2, "PageDown", 9);
    return;
  }
  if (param_1 == 0x26) {
    *param_3 = 2;
    param_2[0] = 'U';
    param_2[1] = 'p';
    param_2[2] = '\0';
    return;
  }
  if (param_1 == 0x25) {
    *param_3 = 4;
    strncpy(param_2, "Left", 5);
    return;
  }
  if (param_1 == 0x28) {
    *param_3 = 5;
    strncpy(param_2, "Down", 5);
    return;
  }
  if (param_1 == 0x27) {
    *param_3 = 6;
    strncpy(param_2, "Right", 6);
    return;
  }
  if (param_1 == 0x14) {
    *param_3 = 0x10;
    strncpy(param_2, "CapsLock", 9);
  }
  return;
}

