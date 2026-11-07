#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <windows.h>

/*
 * Function: Volume Adjustment & Replay Recording Screen Notifications
 * Original Virtual Address: 0x004028A0 (FUN_004028a0)
 *
 * Description: Polls F11 (DAT_004553f2) / F12 (DAT_004553f3) volume adjustment keys,
 * renders "Volume: %d" HUD overlay for 100 frames (DAT_0044f190), and renders
 * colored on-screen status text during battle recording (DAT_00450b70):
 *   - State 1 (Orange 0x00FF7800): "Start recording '%s'..."
 *   - State 2 (Green  0x0000FF00): "Recording file '%s' saved!"
 *   - State 3 (Red    0x000000FF): "Recording canceled!"
 */

void func_004028a0_recording_notify(void)
{
    char vol_buf[20];
    char msg_buf[500];

    int vol_delta = 0;
    if (DAT_004553f2 == 'd') {
        vol_delta = -1;
    }
    if (DAT_004553f3 == 'd') {
        vol_delta = 1;
    }

    if (vol_delta != 0) {
        FUN_00402810(vol_delta);
        DAT_0044f190 = 100;
    }

    if (vol_delta != 0 || DAT_0044f190 >= 1) {
        if (DAT_00450b70 == 0) {
            sprintf(vol_buf, "Volume: %d", DAT_0044d000);
            if (DAT_00455608 != 0) {
                FUN_00401290(DAT_00455608, vol_buf, 0, 0xff00, 3, 0x213);
            }
            DAT_0044f190 = DAT_0044f190 - 1;
        }
    }

    if (DAT_00450b70 > 0 && DAT_00450bfc == 0) {
        DAT_00450b6c = DAT_00450b6c + 1;
        if (DAT_00450b6c > 0xf0) {
            DAT_00450b6c = 0;
            DAT_00450b70 = 0;
            return;
        }
    }

    if (DAT_00450b70 == 1) {
        sprintf(msg_buf, "Start recording '%s'...", DAT_0044fd98);
        if (DAT_00455608 != 0) {
            FUN_00401290(DAT_00455608, msg_buf, 0, 0xff7800, 3, 0x213);
        }
    }
    if (DAT_00450b70 == 2) {
        sprintf(msg_buf, "Recording file '%s' saved!", DAT_0044fd98);
        if (DAT_00455608 != 0) {
            FUN_00401290(DAT_00455608, msg_buf, 0, 0xff00, 3, 0x213);
        }
    }
    if (DAT_00450b70 == 3) {
        sprintf(msg_buf, "Recording canceled!");
        DAT_00450b6c = DAT_00450b6c + 1;
        if (DAT_00455608 != 0) {
            FUN_00401290(DAT_00455608, msg_buf, 0, 0xff, 3, 0x213);
        }
    }
}

void func_00402980_replay_notify(void)
{
    func_004028a0_recording_notify();
}

void FUN_004028a0(void)
{
    func_004028a0_recording_notify();
}

int FUN_00402980(void)
{
    FUN_004028a0();
    return 0;
}


