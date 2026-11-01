#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Function: Replay Filename Generator & Session Setup
 * Original Virtual Address: 0x0042D080
 *
 * Description: Generates timestamped replay filenames using current local time
 * ("%4d%02d%02d_%02d%02d%02d") appended with mode tags ("_Stage_%d", "_Survival",
 * or "_VS") and the authentic ".lfr" extension.
 */

#include <stdio.h>
#include <time.h>
#include <string.h>

extern char g_replay_filename[260]; // 0x0044FD98
extern int g_game_mode;             // 0x00450BE4
extern int g_stage_number;          // 0x00450B94
extern int g_recording_state;       // 0x00450B70

void func_0042d080_replay_filename(int mode, int stage) {
    time_t rawtime;
    struct tm* timeinfo;
    char timestamp[64];
    char mode_str[64];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // 0x0042D09F: Format timestamp "%4d%02d%02d_%02d%02d%02d"
    sprintf(timestamp, "%04d%02d%02d_%02d%02d%02d",
            timeinfo->tm_year + 1900,
            timeinfo->tm_mon + 1,
            timeinfo->tm_mday,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec);

    // 0x0042D0AA: Mode evaluation
    if (mode == 1) { // Stage / Survival
        if (stage >= 5) {
            sprintf(mode_str, "_Survival");
        } else {
            sprintf(mode_str, "_Stage_%d", stage + 1);
        }
    } else { // VS Mode
        sprintf(mode_str, "_VS");
    }

    // 0x0042D1A9: Assemble final filename "%s%s.lfr"
    sprintf(g_replay_filename, "recording\\%s%s.lfr", timestamp, mode_str);

    // 0x0042D1C6: Initialize recording state
    g_recording_state = 1; // "Start recording..."
}

