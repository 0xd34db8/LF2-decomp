#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

/*
 * Function: Interactive Options, Key Reconfiguration & Display Mode UI
 * Original Virtual Address: 0x004246B0
 * Calling Convention: __thiscall
 */

void lf2_options_screen(void *param_1)
{
    FUN_004246b0(param_1);
}

void FUN_004246b0(void *param_1)
{
    int iVar4;

    // Substate 6: Interactive Control Reconfiguration
    if (DAT_0044d064 == 6) {
        // If waiting for key press to rebind
        if (DAT_004511e0 > 0) {
            for (iVar4 = 0; iVar4 < 0xFA; ++iVar4) {
                if (DAT_00455378[iVar4] == 'd') {
                    DAT_0044fb70[DAT_004511e0] = iVar4;
                    DAT_004511e0 = 0;
                    break;
                }
            }
        }

        // If editing player name
        if (DAT_004511c8 > 0) {
            int p_idx = DAT_004511c8 - 1;
            char *p_name = &DAT_0044fcc0[p_idx * 11];
            for (iVar4 = 0; iVar4 < 300; ++iVar4) {
                if (DAT_00455378[iVar4] == 'd') {
                    char c = FUN_00422f60(iVar4);
                    int name_len = strlen(p_name);
                    if (iVar4 == 8) { // Backspace
                        if (name_len > 0) {
                            p_name[name_len - 1] = '\0';
                        }
                        DAT_00455378[iVar4] = 'u';
                    }
                    else if (c != '\0' && name_len < 10 && iVar4 != 0xD) {
                        p_name[name_len] = c;
                        p_name[name_len + 1] = '\0';
                        DAT_00455378[iVar4] = 'u';
                    }
                }
            }
        }

        // Process 4 player control slots
        for (int p = 0; p < 4; ++p) {
            int slot_x = 0xC2 + p * 0x8B;
            int *p_device = &DAT_0044fb70[p * 20];

            // Device toggle click (Keyboard vs Joystick 1..4)
            if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
                DAT_00457580 == 1 && DAT_0044d060 == 0 &&
                ((unsigned int)(DAT_00453cdc - 0xB6) < 0x5B)) {
                DAT_004511e0 = 0;
                *p_device = (*p_device + 1) % 3;
            }

            // Player name click
            if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
                ((unsigned int)(DAT_00453cdc - 0x9C) < 0x12) &&
                DAT_0044d060 == 0 && DAT_00457580 == 1) {
                DAT_004511c8 = p + 1;
                DAT_004511e0 = 0;
            }

            // Key row click (7 action keys: Up, Down, Left, Right, Attack, Jump, Defend)
            int key_y = 0x11B;
            for (int k = 0; k < 7; ++k) {
                if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
                    DAT_0044d060 == 0 && DAT_00457580 == 1 &&
                    DAT_00453cdc >= key_y - 3 && DAT_00453cdc <= key_y + 0xF) {
                    if (*p_device == 0 || k >= 4) {
                        DAT_004511e0 = p * 20 + (k + 1);
                    }
                    DAT_004511c8 = 0;
                }
                key_y += 0x16;
            }
        }

        // Save & Cancel buttons
        if (DAT_00453cdc > 0x1B8) {
            // Cancel / Reload
            if (DAT_00453cdc < 0x1D2 && ((unsigned int)(DAT_004546f0 - 0x246) < 0x9C) &&
                DAT_0044d060 == 0 && DAT_00457580 == 1) {
                FUN_00401a30(0);
                func_00423480_load_control_txt();
                DAT_0044d064 = 0;
                DAT_0044d780 = 0xFFFFFFFF;
            }
            // Save to control.txt
            if (((unsigned int)(DAT_00453cdc - 0x1B9) < 0x19) &&
                ((unsigned int)(DAT_004546f0 - 0x195) < 0x9C) &&
                DAT_0044d060 == 0 && DAT_00457580 == 1) {
                FUN_00401a30(0);
                func_004233e0_save_control_txt();
                DAT_0044d064 = 0;
                DAT_0044d780 = 0xFFFFFFFF;
            }
        }
    }

    // Substate 7: Profile and Recording Settings
    else if (DAT_0044d064 == 7) {
        // Toggle auto-record
        if (DAT_004546f0 > 0x11E && DAT_004546f0 < 0x133 &&
            DAT_00453cdc > 0x185 && DAT_00453cdc < 0x19A &&
            DAT_0044d060 == 0 && DAT_00457580 == 1) {
            DAT_00450be4 = 1 - DAT_00450be4;
        }

        // Save & Cancel
        if (DAT_00453cdc > 0x19F && DAT_00453cdc < 0x1B9) {
            if (DAT_004546f0 > 0x192 && DAT_004546f0 < 0x22F &&
                DAT_0044d060 == 0 && DAT_00457580 == 1) {
                func_00423480_load_control_txt();
                FUN_00401a30(0);
                DAT_0044d064 = 0;
            }
            if (DAT_004546f0 > 0xE6 && DAT_004546f0 < 0x183 &&
                DAT_0044d060 == 0 && DAT_00457580 == 1) {
                func_004233e0_save_control_txt();
                FUN_00401a30(0);
                DAT_0044d064 = 0;
            }
        }
    }

    DAT_0044d060 = DAT_00457580;
}

