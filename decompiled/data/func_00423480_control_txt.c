/*
 * Function: Player Control Configuration & Name Serializer (control.txt)
 * Original Virtual Address: 0x004233E0 (Save) / 0x00423480 (Load)
 *
 * Description: Reads and writes player keyboard mappings and player profile names
 * from "data/control.txt".
 */

#include <stdio.h>
#include <string.h>

#define MAX_CONTROL_PLAYERS 4
#define KEYS_PER_PLAYER 11

extern int g_player_keys[MAX_CONTROL_PLAYERS][KEYS_PER_PLAYER]; // 0x0044FB70
extern char g_player_names[MAX_CONTROL_PLAYERS][16];            // 0x0044FCC0
extern int g_replay_mode;                                       // 0x00450BE4
extern int g_demo_mode;                                         // 0x00450BE8

int func_00423480_load_control_txt(void) {
    FILE* fp = fopen("data\\control.txt", "r");
    if (!fp) return 0;

    // 0x004234D0: Load 11 keys for each of 4 players
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (int k = 0; k < KEYS_PER_PLAYER; ++k) {
            fscanf(fp, "%d", &g_player_keys[p][k]);
        }
    }

    // 0x00423510: Load 4 player names "%s %s %s %s"
    fscanf(fp, "%s %s %s %s",
           g_player_names[0], g_player_names[1],
           g_player_names[2], g_player_names[3]);

    // Replace grave accent '`' with space ' '
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (int i = 0; g_player_names[p][i]; ++i) {
            if (g_player_names[p][i] == '`') {
                g_player_names[p][i] = ' ';
            }
        }
    }

    // 0x0042356B: Load demo & replay mode flags
    fscanf(fp, "%d", &g_demo_mode);
    fscanf(fp, "%d", &g_replay_mode);

    fclose(fp);
    return 1;
}

int func_004233e0_save_control_txt(void) {
    FILE* fp = fopen("data\\control.txt", "w");
    if (!fp) return 0;

    // Save player keys
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (int k = 0; k < KEYS_PER_PLAYER; ++k) {
            fprintf(fp, "%d\n", g_player_keys[p][k]);
        }
    }

    // Save player names (spaces replaced with '`')
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        char name_buf[16];
        strncpy(name_buf, g_player_names[p], 15);
        name_buf[15] = '\0';
        for (int i = 0; name_buf[i]; ++i) {
            if (name_buf[i] == ' ') name_buf[i] = '`';
        }
        fprintf(fp, "%s%s", name_buf, (p == 3) ? "\n" : " ");
    }

    // Save demo & replay mode flags
    fprintf(fp, "%d\n", g_demo_mode);
    fprintf(fp, "%d\n", g_replay_mode);

    fclose(fp);
    return 1;
}

