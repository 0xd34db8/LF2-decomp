/*
 * Function: Replay Recording Screen Notifications
 * Original Virtual Address: 0x00402980
 *
 * Description: Renders colored on-screen status text during battle recording:
 * State 1 (Orange): "Start recording '%s'..." (0x004477D8)
 * State 2 (Green):  "Recording file '%s' saved!" (0x004477BC)
 * State 3 (Red):    "Recording canceled!" (0x004477A8)
 */

#include <stdio.h>
#include <windows.h>

extern char g_replay_filename[260]; // 0x0044FD98
extern int g_recording_state;       // 0x00450B70
extern void* g_back_surface;        // 0x00455608

void func_00402980_replay_notify(void) {
    char msg[512];

    if (g_recording_state == 1) {
        // 0x004029A6: Orange text notification (0x00FF7800)
        sprintf(msg, "Start recording '%s'...", g_replay_filename);
        // DrawText(g_back_surface, msg, x=0, y=0x213, color=0x00FF7800)
    } else if (g_recording_state == 2) {
        // 0x004029E2: Green text notification (0x0000FF00)
        sprintf(msg, "Recording file '%s' saved!", g_replay_filename);
        // DrawText(g_back_surface, msg, x=0, y=0x213, color=0x0000FF00)
    } else if (g_recording_state == 3) {
        // 0x00402A19: Red text notification (0x000000FF)
        sprintf(msg, "Recording canceled!");
        // DrawText(g_back_surface, msg, x=0, y=0x213, color=0x000000FF)
    }
}

