#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <windows.h>
#include <stdbool.h>

/*
 * Function: Virtual Key Code to ASCII Character
 * Original Virtual Address: 0x00422F60
 * Calling Convention: __cdecl
 */

char lf2_vk_to_ascii(int key_code)
{
    return FUN_00422f60(key_code);
}

char FUN_00422f60(int param_1)
{
    char cVar1 = '\0';
    char cVar4 = (char)param_1;

    if (param_1 == 0x20) {
        return ' ';
    }

    if (param_1 - 0x41U < 0x1a) { // 'A'..'Z'
        SHORT caps = GetKeyState(0x14); // VK_CAPITAL
        bool shift_down = (DAT_00455388 == 'd');
        bool caps_on = (caps & 1) != 0;
        bool upper = (shift_down ^ caps_on);
        return upper ? cVar4 : (cVar4 + 0x20); // 0x20 offset = lowercase
    }

    // Keypad numbers 0..9 (0x60..0x69)
    if (param_1 - 0x60U < 10) {
        return cVar4 - 0x30;
    }
    if (param_1 == 0x6B) return '+';
    if (param_1 == 0x6D) return '-';
    if (param_1 == 0x6A) return '*';
    if (param_1 == 0x6F) return '/';
    if (param_1 == 0x6E) return '.';

    // Shifted symbols when shift is pressed
    if (DAT_00455388 == 'd') {
        if (param_1 == 0xBD) return '_';
        if (param_1 == 0xBB) return '+';
        if (param_1 == 0xDB) return '{';
        if (param_1 == 0xDD) return '}';
        if (param_1 == 0xBA) return ':';
        if (param_1 == 0xDE) return '\"';
        if (param_1 == 0xDC) return '|';
        if (param_1 == 0xBC) return '<';
        if (param_1 == 0xBE) return '>';
        if (param_1 == 0xBF) return '?';
        if (param_1 == 0xC0) return '~';
        if (param_1 == 0x31) return '!';
        if (param_1 == 0x32) return '@';
        if (param_1 == 0x33) return '#';
        if (param_1 == 0x34) return '$';
        if (param_1 == 0x35) return '%';
        if (param_1 == 0x36) return '^';
        if (param_1 == 0x37) return '&';
        if (param_1 == 0x38) return '*';
        if (param_1 == 0x39) return '(';
        if (param_1 == 0x30) return ')';
    }
    else {
        if (param_1 == 0xBD) return '-';
        if (param_1 == 0xBB) return '=';
        if (param_1 == 0xDB) return '[';
        if (param_1 == 0xDD) return ']';
        if (param_1 == 0xBA) return ';';
        if (param_1 == 0xDE) return '\'';
        if (param_1 == 0xDC) return '\\';
        if (param_1 == 0xBC) return ',';
        if (param_1 == 0xBE) return '.';
        if (param_1 == 0xBF) return '/';
        if (param_1 == 0xC0) return '`';
    }

    // Number keys '0'..'9' (0x30..0x39) when not shifted
    if (param_1 >= 0x30 && param_1 <= 0x39) {
        return cVar4;
    }

    // Navigation and keypad controls
    if (param_1 == 0x21) return '9'; // PageUp
    if (param_1 == 0x22) return '3'; // PageDown
    if (param_1 == 0x23) return '1'; // End
    if (param_1 == 0x24) return '7'; // Home
    if (param_1 == 0x25) return '4'; // Left
    if (param_1 == 0x26) return '8'; // Up
    if (param_1 == 0x27) return '6'; // Right
    if (param_1 == 0x28) return '2'; // Down
    if (param_1 == 0x0C) return '5'; // Clear
    if (param_1 == 0x2D) return '0'; // Insert

    return cVar1;
}

