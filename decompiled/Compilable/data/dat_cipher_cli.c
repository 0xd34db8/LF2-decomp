#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Virtual Addresses:
 *   - 0x00414450: cipher_cli_vk_to_char (FUN_00414450)
 *   - 0x00414B70: dat_cipher_cli (FUN_00414b70)
 * Class / Subsystem: Data / Developer Data Cipher CLI
 */

// FUNCTION: LF2 0x00414450
char FUN_00414450(uint32_t vk_code)
{
    char ch = (char)vk_code;
    if (vk_code == 0x20) {
        return ' ';
    }

#ifdef _WIN32
    SHORT caps = GetKeyState(VK_CAPITAL);
#else
    SHORT caps = 0;
#endif

    if (vk_code - 0x41 < 0x1a) {
        if ((DAT_00455388 == 'd' && caps == 0) ||
            (caps > 0 && DAT_00455388 != 'd')) {
            return ch;
        }
        return (char)(vk_code + 0x20);
    }

    if (vk_code - 0x60 < 10) {
        return (char)(ch - 0x30);
    }
    if (vk_code == 0x6b) return '+';
    if (vk_code == 0x6d) return '-';
    if (vk_code == 0x6a) return '*';
    if (vk_code == 0x6f) return '/';
    if (vk_code == 0x6e) return '.';

    if (DAT_00455388 == 'd') {
        if (vk_code == 0xbd) return '_';
        if (vk_code == 0xbb) return '+';
        if (vk_code == 0xdb) return '{';
        if (vk_code == 0xdd) return '}';
        if (vk_code == 0xba) return ':';
        if (vk_code == 0xde) return '\"';
        if (vk_code == 0xdc) return '|';
        if (vk_code == 0xbc) return '<';
        if (vk_code == 0xbe) return '>';
        if (vk_code == 0xbf) return '?';
        if (vk_code == 0xc0) return '~';
        if (vk_code == 0x31) return '!';
        if (vk_code == 0x32) return '@';
        if (vk_code == 0x33) return '#';
        if (vk_code == 0x34) return '$';
        if (vk_code == 0x35) return '%';
        if (vk_code == 0x36) return '^';
        if (vk_code == 0x37) return '&';
        if (vk_code == 0x38) return '*';
        if (vk_code == 0x39) return '(';
        if (vk_code == 0x30) return ')';
        return '\0';
    }

    if (vk_code - 0x30 < 10) {
        return ch;
    }
    if (vk_code == 0xbd) return '-';
    if (vk_code == 0xbb) return '=';
    if (vk_code == 0xdb) return '[';
    if (vk_code == 0xdd) return ']';
    if (vk_code == 0xba) return ';';
    if (vk_code == 0xde) return '\'';
    if (vk_code == 0xdc) return '\\';
    if (vk_code == 0xbc) return ',';
    if (vk_code == 0xbe) return '.';
    if (vk_code == 0xbf) return '/';
    if (vk_code == 0xc0) return '`';
    return '\0';
}

static const char *const k_helpme_batch_files[] = {
    "data\\template.txt",
    "data\\julian.txt",
    "data\\firzen.txt",
    "data\\louisEX.txt",
    "data\\bat.txt",
    "data\\justin.txt",
    "data\\knight.txt",
    "data\\jan.txt",
    "data\\monk.txt",
    "data\\sorcerer.txt",
    "data\\jack.txt",
    "data\\mark.txt",
    "data\\hunter.txt",
    "data\\bandit.txt",
    "data\\deep.txt",
    "data\\john.txt",
    "data\\henry.txt",
    "data\\rudolf.txt",
    "data\\louis.txt",
    "data\\firen.txt",
    "data\\freeze.txt",
    "data\\dennis.txt",
    "data\\woody.txt",
    "data\\davis.txt",
    "data\\weapon0.txt",
    "data\\weapon2.txt",
    "data\\weapon4.txt",
    "data\\weapon5.txt",
    "data\\weapon6.txt",
    "data\\weapon1.txt",
    "data\\weapon3.txt",
    "data\\weapon8.txt",
    "data\\weapon9.txt",
    "data\\weapon10.txt",
    "data\\weapon11.txt",
    "data\\criminal.txt",
    "data\\john_ball.txt",
    "data\\henry_arrow1.txt",
    "data\\rudolf_weapon.txt",
    "data\\deep_ball.txt",
    "data\\henry_wind.txt",
    "data\\dennis_ball.txt",
    "data\\woody_ball.txt",
    "data\\davis_ball.txt",
    "data\\henry_arrow2.txt",
    "data\\freeze_ball.txt",
    "data\\firen_ball.txt",
    "data\\firen_flame.txt",
    "data\\freeze_column.txt",
    "data\\weapon7.txt",
    "data\\john_biscuit.txt",
    "data\\dennis_chase.txt",
    "data\\jack_ball.txt",
    "data\\jan_chaseh.txt",
    "data\\jan_chase.txt",
    "data\\firzen_chasef.txt",
    "data\\firzen_chasei.txt",
    "data\\firzen_ball.txt",
    "data\\bat_ball.txt",
    "data\\bat_chase.txt",
    "data\\justin_ball.txt",
    "data\\julian_ball.txt",
    "data\\julian_ball2.txt",
    "data\\etc.txt",
    "data\\broken_weapon.txt",
    "bg\\sys\\hkc\\bg.txt",
    "bg\\sys\\sp\\bg.txt",
    "bg\\sys\\lf\\bg.txt",
    "bg\\sys\\gw\\bg.txt",
    "bg\\sys\\qi\\bg.txt",
    "bg\\sys\\ft\\bg.txt",
    "bg\\sys\\cuhk\\bg.txt",
    "bg\\sys\\thv\\bg.txt",
    "bg\\template\\1\\bg.txt",
    "bg\\template\\2\\bg.txt",
    "bg\\template\\3\\bg.txt",
    "data\\data.txt"
};

static int lf2_cli_poll_line(void)
{
    int len = DAT_0044f81c;
    for (int vk = 0; vk < 300; ++vk) {
        if (DAT_00455378[vk] == 'd') {
            char ch = FUN_00414450((uint32_t)vk);
            len = DAT_0044f81c;
            if (ch != '\0') {
                if (vk == 8) {
                    if (DAT_0044f81c > 0) {
                        DAT_0044f628[DAT_0044f81c - 1] = '\0';
                        len = DAT_0044f81c - 1;
                        DAT_0044f81c = len;
                        DAT_00455378[vk] = 'u';
                    }
                } else if (DAT_0044f81c <= 0x31 && vk != 0xd) {
                    DAT_0044f628[DAT_0044f81c] = ch;
                    DAT_0044f628[DAT_0044f81c + 1] = '\0';
                    len = DAT_0044f81c + 1;
                    DAT_0044f81c = len;
                    DAT_00455378[vk] = 'u';
                }
            } else if (vk == 8 && DAT_0044f81c > 0) {
                DAT_0044f628[DAT_0044f81c - 1] = '\0';
                len = DAT_0044f81c - 1;
                DAT_0044f81c = len;
                DAT_00455378[vk] = 'u';
            }
        }
    }
    return len;
}

// FUNCTION: LF2 0x00414b70
void FUN_00414b70(void)
{
    char msg[512];

    if (DAT_0044f820 == 0) {
        DAT_0044f81c = 0;
        DAT_0044f628[0] = '\0';
        sprintf(msg, "Doing what (\'E\'=encrp, \'D\'=decrp)? ");
        FUN_00401290(DAT_00455608, msg, 0, 0xffffff, 0x46, 0x46);
        if (DAT_004553bd == 'd') {
            DAT_004553bd = 'u';
            DAT_0044f820 = 1;
        } else if (DAT_004553bc == 'd') {
            DAT_004553bc = 'u';
            DAT_0044f820 = 2;
        }
        FUN_0043e940(DAT_00458348);
        return;
    }

    uint32_t prompt_color = 0;
    if (DAT_0044f820 == 1) {
        int len = lf2_cli_poll_line();
        if (DAT_00455385 == 'd') {
            if (len == 0) {
                DAT_00455385 = 'u';
                DAT_0044f820 = 0;
            } else if (len >= 1) {
                DAT_00455385 = 'u';
                if (strcmp(DAT_0044f628, "helpme") == 0) {
                    size_t n = sizeof(k_helpme_batch_files) / sizeof(k_helpme_batch_files[0]);
                    for (size_t i = 0; i < n; ++i) {
                        FUN_004146b0(k_helpme_batch_files[i]);
                    }
                } else {
                    FUN_004146b0(DAT_0044f628);
                }
                DAT_0044f820 = 0;
            }
        }
        sprintf(msg, "Encrp what file? ");
        prompt_color = 0x6464ff;
    } else if (DAT_0044f820 == 2) {
        int len = lf2_cli_poll_line();
        if (DAT_00455385 == 'd') {
            if (len == 0) {
                DAT_00455385 = 'u';
                DAT_0044f820 = 0;
            } else if (len >= 1) {
                DAT_00455385 = 'u';
                FUN_004148a0(DAT_0044f628);
                DAT_0044f820 = 0;
            }
        }
        sprintf(msg, "Decrp what file? ");
        prompt_color = 0xaaff00;
    } else {
        FUN_0043e940(DAT_00458348);
        return;
    }

    FUN_00401290(DAT_00455608, msg, 0, prompt_color, 0x46, 0x46);
    sprintf(msg, "%s_", DAT_0044f628);
    FUN_00401290(DAT_00455608, msg, 0, 0xffbe96, 0x50, 0x5a);
    FUN_0043e940(DAT_00458348);
}
