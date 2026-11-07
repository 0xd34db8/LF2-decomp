#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Phase 19: Background Music (BGM) Streaming & State Machine (0x00401C90 - 0x004025D0)
 * 
 * Functions:
 *   - FUN_00401c90: COM Filter Graph & Interface Init (IGraphBuilder, IMediaControl, IMediaSeeking)
 *   - FUN_00401d30: DirectShow COM Release & Graph Teardown
 *   - FUN_00401da0: BGM Load / Render File
 *   - FUN_00401e90: Media Event Loop & Track Rewind (Looping)
 *   - FUN_00401f30: Basic Audio Volume Level Configurator
 *   - FUN_00402000: BGM Stream Playback Stop
 *   - FUN_00402020: Master BGM Playback Dispatcher with Cache Check
 *   - FUN_00402100: BGM Playback Pause & Rewind to Origin
 *   - FUN_00402130: Menu / In-Game BGM Selector & HUD Text Cycler
 *   - FUN_004025b0: Play Staged Current Track
 *   - FUN_004025d0: Master Track Selector & Stage Randomizer
 */

static const char* const BGM_TRACK_PATHS[] = {
    "",                 // 0: unused/random placeholder
    "bgm\\main.wma",    // 1: Main Theme
    "bgm\\stage1.wma",  // 2: Stage 1
    "bgm\\stage2.wma",  // 3: Stage 2
    "bgm\\stage3.wma",  // 4: Stage 3
    "bgm\\stage4.wma",  // 5: Stage 4
    "bgm\\stage5.wma",  // 6: Stage 5
    "bgm\\boss1.wma",   // 7: Boss 1
    "bgm\\boss2.wma"    // 8: Boss 2 (Final Boss)
};

static const char* const BGM_TRACK_NAMES[] = {
    "Random",
    "Main Theme",
    "Stage 1",
    "Stage 2",
    "Stage 3",
    "Stage 4",
    "Stage 5",
    "Boss",
    "Final Boss"
};

int FUN_00401c90(void)
{
    // Emulated DirectShow Graph initialization
    DAT_0044ef04[0] = '\0';
    DAT_0044f040 = (void*)0x1000;
    DAT_0044f044 = (void*)0x1000;
    DAT_0044f048 = (void*)0x1000;
    DAT_0044f04c = (void*)0x1000;
    return 0;
}

void FUN_00401d30(void)
{
    // DirectShow Interface Release & Graph Teardown
    DAT_0044f04c = NULL;
    DAT_0044f048 = NULL;
    DAT_0044f044 = NULL;
    DAT_0044f040 = NULL;
}

void FUN_00401da0(const char *param_1)
{
    if (!param_1) return;
    strncpy(DAT_0044ef04, param_1, sizeof(DAT_0044ef04) - 1);
    DAT_0044ef04[sizeof(DAT_0044ef04) - 1] = '\0';
}

void FUN_00401e90(void)
{
    // BGM track loop event pump
    // In authentic binary: checks EC_COMPLETE event, rewinds position to 0
}

int FUN_00401f30(int vol)
{
    DAT_0044d000 = vol;
    return 0;
}

void FUN_00402000(void)
{
    // BGM Playback Stop
}

void FUN_00402020(const char *param_1)
{
    if (DAT_0044d010 == 0 || !param_1 || param_1[0] == '\0') {
        return;
    }

    // Cache check: If track is already playing, do not restart
    if (strcmp(DAT_0044ef04, param_1) == 0) {
        return;
    }

    FUN_00401d30();
    if (FUN_00401c90() == 0) {
        FUN_00401da0(param_1);
        FUN_00401f30(DAT_0044d000);
        strncpy(DAT_0044ef04, param_1, sizeof(DAT_0044ef04) - 1);
        DAT_0044ef04[sizeof(DAT_0044ef04) - 1] = '\0';
    }
}

void func_00402020_bgm_play(const char *filepath)
{
    FUN_00402020(filepath);
}

void FUN_00402100(void)
{
    // BGM Pause & Rewind to Origin
    DAT_0044ef04[0] = '\0';
}

void FUN_00402130(int param_1, int param_2, int param_3, void *param_4)
{
    (void)param_4;

    if (param_1 == 1) {
        // Toggle mode: toggle between ON (0) and OFF (-1)
        if (param_2 == 0 && param_3 == 0) {
            if (DAT_0044f18c != -1) {
                strcpy(DAT_0044f128, "ON");
                goto update_status;
            }
        } else {
            if (DAT_0044f18c == -1) {
                DAT_0044f18c = 0;
                strcpy(DAT_0044f128, "ON");
                goto update_status;
            }
            DAT_0044f18c = -1;
        }
    } else {
        // Cycle mode: cycle between track indices -1..8
        if (param_3 != 0) {
            DAT_0044f18c++;
        }
        if (DAT_0044f18c > 8) {
            DAT_0044f18c = -1;
        }
        if (param_2 != 0) {
            DAT_0044f18c--;
        }
        if (DAT_0044f18c < -1) {
            DAT_0044f18c = 8;
        }

        if (DAT_0044f18c == -1) {
            strcpy(DAT_0044f128, "OFF");
            DAT_0044eed0[0] = '\0';
        } else if (DAT_0044f18c >= 0 && DAT_0044f18c <= 8) {
            strcpy(DAT_0044f128, BGM_TRACK_NAMES[DAT_0044f18c]);
            int track_idx = DAT_0044f18c;
            if (track_idx == 0) {
                track_idx = FUN_00417170(1, 8) + 1;
            }
            if (track_idx >= 1 && track_idx <= 8) {
                strncpy(DAT_0044eed0, BGM_TRACK_PATHS[track_idx], sizeof(DAT_0044eed0) - 1);
                DAT_0044eed0[sizeof(DAT_0044eed0) - 1] = '\0';
            }
        }
    }

update_status:
    if (DAT_0044f18c != -1) {
        DAT_0044d010 = 1;
    } else {
        strcpy(DAT_0044f128, "OFF");
        DAT_0044d010 = 0;
        FUN_00402100();
    }

    snprintf(DAT_0044f060, sizeof(DAT_0044f060), "Music: %s", DAT_0044f128);
}

void FUN_004025b0(void)
{
    if (DAT_0044eed0[0] != '\0') {
        FUN_00402020(DAT_0044eed0);
    }
}

void FUN_004025d0(int track_id)
{
    if (DAT_0044d010 == 0) {
        return;
    }

    int chosen = track_id;
    if (chosen == 0) {
        chosen = FUN_00417170(2, 8) + 1;
    }

    if (chosen >= 1 && chosen <= 8) {
        strncpy(DAT_0044eed0, BGM_TRACK_PATHS[chosen], sizeof(DAT_0044eed0) - 1);
        DAT_0044eed0[sizeof(DAT_0044eed0) - 1] = '\0';
        FUN_004025b0();
    }
}

void func_004025d0_bgm_select(int track_id)
{
    FUN_004025d0(track_id);
}
