#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>

/*
 * Function: Virtual Key Code to Friendly Display Name & Render Offset
 * Original Virtual Address: 0x00422B00
 * Calling Convention: __cdecl
 */

void lf2_get_key_name(int key_code, char *out_name, int *out_width_adj)
{
    FUN_00422b00(key_code, out_name, out_width_adj);
}

void FUN_00422b00(int param_1, char *param_2, int *param_3)
{
    char cVar1;

    strncpy(param_2, "none", 5);
    *param_3 = 8;

    if (param_1 == 0x20) { // VK_SPACE
        strncpy(param_2, "Space", 6);
        *param_3 = 10;
        return;
    }
    if (param_1 == 0x0D) { // VK_RETURN
        strncpy(param_2, "Enter", 6);
        *param_3 = 10;
        return;
    }

    cVar1 = (char)param_1;
    if ((param_1 < 0x41) || (0x5A < param_1)) { // Not 'A'..'Z'
        if ((param_1 < 0x60) || (0x69 < param_1)) { // Not Numpad 0..9
            if (param_1 == 0x6B) {
                strncpy(param_2, "Keypad: +", 10);
                *param_3 = 0xF;
                return;
            }
            if (param_1 == 0x6D) {
                strncpy(param_2, "Keypad: -", 10);
                *param_3 = 0xF;
                return;
            }
            if (param_1 == 0x6A) {
                strncpy(param_2, "Keypad: *", 10);
                *param_3 = 0xF;
                return;
            }
            if (param_1 == 0x6F) {
                strncpy(param_2, "Keypad: /", 10);
                *param_3 = 0xF;
                return;
            }
            if (param_1 == 0x6E) {
                strncpy(param_2, "Keypad: .", 10);
                *param_3 = 0xF;
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
            *param_3 = 0xF;
            return;
        }
    }
    else {
        param_2[0] = cVar1;
        param_2[1] = '\0';
        *param_3 = 0;
        return;
    }

    if ((0x2F < param_1) && (param_1 < 0x3A)) { // '0'..'9'
        param_2[0] = cVar1;
        param_2[1] = '\0';
        *param_3 = 0;
        return;
    }

    if (param_1 == 0xBD) { *param_3 = 0; param_2[0] = '-'; param_2[1] = '\0'; return; }
    if (param_1 == 0xBB) { *param_3 = 0; param_2[0] = '='; param_2[1] = '\0'; return; }
    if (param_1 == 0xDB) { *param_3 = 0; param_2[0] = '['; param_2[1] = '\0'; return; }
    if (param_1 == 0xDD) { *param_3 = 0; param_2[0] = ']'; param_2[1] = '\0'; return; }
    if (param_1 == 0xBA) { *param_3 = 0; param_2[0] = ';'; param_2[1] = '\0'; return; }
    if (param_1 == 0xDE) { *param_3 = 0; param_2[0] = '\''; param_2[1] = '\0'; return; }
    if (param_1 == 0xDC) { *param_3 = 0; param_2[0] = '\\'; param_2[1] = '\0'; return; }
    if (param_1 == 0xBC) { *param_3 = 0; param_2[0] = ','; param_2[1] = '\0'; return; }
    if (param_1 == 0xBE) { *param_3 = 0; param_2[0] = '.'; param_2[1] = '\0'; return; }
    if (param_1 == 0xBF) { *param_3 = 0; param_2[0] = '/'; param_2[1] = '\0'; return; }
    if (param_1 == 0xC0) { *param_3 = 0; param_2[0] = '`'; param_2[1] = '\0'; return; }
    if (param_1 == 0x11) { *param_3 = 7; strncpy(param_2, "Ctrl", 5); return; }
    if (param_1 == 0x10) { *param_3 = 7; strncpy(param_2, "Shift", 6); return; }
    if (param_1 == 0x09) { *param_3 = 5; strncpy(param_2, "Tab", 4); return; }
    if (param_1 == 0x08) { *param_3 = 0xD; strncpy(param_2, "Backspace", 10); return; }
    if (param_1 == 0x2D) { *param_3 = 8; strncpy(param_2, "Insert", 7); return; }
    if (param_1 == 0x2E) { *param_3 = 8; strncpy(param_2, "Delete", 7); return; }
    if (param_1 == 0x24) { *param_3 = 6; strncpy(param_2, "Home", 5); return; }
    if (param_1 == 0x23) { *param_3 = 5; strncpy(param_2, "End", 4); return; }
    if (param_1 == 0x21) { *param_3 = 10; strncpy(param_2, "PageUp", 7); return; }
    if (param_1 == 0x22) { *param_3 = 0xE; strncpy(param_2, "PageDown", 9); return; }
    if (param_1 == 0x26) { *param_3 = 2; param_2[0] = 'U'; param_2[1] = 'p'; param_2[2] = '\0'; return; }
    if (param_1 == 0x25) { *param_3 = 4; strncpy(param_2, "Left", 5); return; }
    if (param_1 == 0x28) { *param_3 = 5; strncpy(param_2, "Down", 5); return; }
    if (param_1 == 0x27) { *param_3 = 6; strncpy(param_2, "Right", 6); return; }
    if (param_1 == 0x14) { *param_3 = 0x10; strncpy(param_2, "CapsLock", 9); return; }
}

