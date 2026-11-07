#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>

/*
 * Function: Formatted Text Box & Drop Shadow Renderer
 * Original Virtual Address: 0x00423940 & 0x00423A70
 * Calling Convention: __thiscall (in_ECX = font_mgr*)
 */

void FUN_00423940(char *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    char *pcVar2;
    int iVar3 = 0;
    int iVar4 = 0;
    int iVar5 = param_2;
    int iVar6 = param_3;
    int idx = 0;
    void **font_mgr = (void **)in_ECX;
    void *saved_ecx = in_ECX;

    pcVar2 = param_1;
    while (*pcVar2 != '\0') pcVar2++;

    if (pcVar2 > param_1) {
        while (idx < (int)(pcVar2 - param_1)) {
            if (param_5 <= iVar4) break;
            if (param_1[idx] == '\n') {
                if (param_5 - 1 <= iVar4) break;
                iVar6 += 0x10;
                iVar4 += 1;
                iVar3 = 0;
                iVar5 = param_2;
            }
            else {
                iVar3++;
                if (param_6 == 0 || param_6 == 1 || param_6 == 2) {
                    if (font_mgr != NULL) {
                        in_ECX = font_mgr[param_6 + 1]; /* +4 (0), +8 (1), +0xC (2) */
                    }
                    FUN_0043f010(iVar5, iVar6, (int)(unsigned char)param_1[idx], 1, 0, (void*)(uintptr_t)DAT_00455608);
                    in_ECX = saved_ecx;
                }
                iVar5 += 8;
                if (param_4 <= iVar3) {
                    if (iVar4 < param_5 - 1) {
                        iVar6 += 0x10;
                        iVar4 += 1;
                        iVar3 = 0;
                        iVar5 = param_2;
                    } else {
                        idx++;
                        break;
                    }
                }
            }
            idx++;
            pcVar2 = param_1;
            while (*pcVar2 != '\0') pcVar2++;
        }
    }
    param_1[idx] = '\0';
    if (param_7 != 0) {
        if (font_mgr != NULL && (param_6 == 0 || param_6 == 1 || param_6 == 2)) {
            in_ECX = font_mgr[param_6 + 1];
        }
        FUN_0043f010(iVar5, iVar6, 0x5F, 1, 0, (void*)(uintptr_t)DAT_00455608);
        in_ECX = saved_ecx;
    }
}

void FUN_00423a70(char *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    /* First 3 passes draw black shadow (font index 0) at (-1,+1), (-1,0), (0,+1); 4th pass draws foreground (param_6) */
    FUN_00423940(param_1, param_2 - 1, param_3 + 1, param_4, param_5, 0,       param_7);
    FUN_00423940(param_1, param_2 - 1, param_3,     param_4, param_5, 0,       param_7);
    FUN_00423940(param_1, param_2,     param_3 + 1, param_4, param_5, 0,       param_7);
    FUN_00423940(param_1, param_2,     param_3,     param_4, param_5, param_6, param_7);
}


