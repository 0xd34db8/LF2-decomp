#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Function: Player Control Configuration & Name Serializer (control.txt)
 * Original Virtual Address: 0x00423230 (Save) / 0x00423480 (Load)
 *
 * Description: Reads and writes player keyboard mappings (DAT_0044fb70, stride 20 ints per player),
 * player profile names (DAT_0044fcc0, stride 11 chars per player), demo/record flags
 * (DAT_00450be8, DAT_00450be4), and 3 profile strings (DAT_0044fd18, DAT_0044f890, DAT_0044f900)
 * from/to "data\\control.txt".
 */

#define MAX_CONTROL_PLAYERS 4
#define KEYS_PER_PLAYER 11
#define PLAYER_KEY_STRIDE 20
#define PLAYER_NAME_STRIDE 11

static void strip_trailing_spaces_and_newlines(char *str)
{
    size_t len = strlen(str);
    while (len > 0) {
        char c = str[len - 1];
        if (c == ' ' || c == '\r' || c == '\n') {
            str[len - 1] = '\0';
            --len;
        } else {
            break;
        }
    }
}

int FUN_00423480(void)
{
    FILE *fp = fopen("data\\control.txt", "r");
    if (!fp) return 0;

    /* 0x004234AB: Load 11 keys for each of 4 players into DAT_0044fb70 (stride 20 ints = 0x50 bytes) */
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (int k = 0; k < KEYS_PER_PLAYER; ++k) {
            fscanf(fp, "%d", &DAT_0044fb70[p * PLAYER_KEY_STRIDE + k]);
        }
    }

    /* 0x004234D6: Load 4 player names (stride 11 bytes = 0x0B in DAT_0044fcc0) */
    fscanf(fp, "%s %s %s %s\n",
           &DAT_0044fcc0[0 * PLAYER_NAME_STRIDE],
           &DAT_0044fcc0[1 * PLAYER_NAME_STRIDE],
           &DAT_0044fcc0[2 * PLAYER_NAME_STRIDE],
           &DAT_0044fcc0[3 * PLAYER_NAME_STRIDE]);

    /* Replace grave accent '`' with space ' ' */
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        char *name = &DAT_0044fcc0[p * PLAYER_NAME_STRIDE];
        size_t len = strlen(name);
        for (size_t i = 0; i < len; ++i) {
            if (name[i] == '`') {
                name[i] = ' ';
            }
        }
    }

    /* 0x0042352B: Load demo & replay/record mode flags */
    fscanf(fp, "%d\n", &DAT_00450be8);
    fscanf(fp, "%d\n", &DAT_00450be4);

    /* 0x0042354D: Read 3 profile strings (Name, Email, Info) */
    DAT_0044fd18[0] = '\0';
    DAT_0044f890[0] = '\0';
    DAT_0044f900[0] = '\0';

    if (fgets(DAT_0044fd18, 100, fp) != NULL) {
        strip_trailing_spaces_and_newlines(DAT_0044fd18);
    }
    if (fgets(DAT_0044f890, 100, fp) != NULL) {
        strip_trailing_spaces_and_newlines(DAT_0044f890);
    }

    if (!feof(fp)) {
        char line_buf[500];
        while (!feof(fp)) {
            line_buf[0] = '\0';
            if (fgets(line_buf, 100, fp) == NULL) {
                break;
            }
            size_t cur_len = strlen(DAT_0044f900);
            size_t add_len = strlen(line_buf);
            if (cur_len + add_len < sizeof(DAT_0044f900)) {
                memcpy(DAT_0044f900 + cur_len, line_buf, add_len + 1);
            }
        }
    }

    fclose(fp);
    return 1;
}

void FUN_00423230(void)
{
    FILE *fp = fopen("data\\control.txt", "w");
    if (!fp) return;

    /* 0x00423244: Save 11 keys per player on a space-separated line */
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (int k = 0; k < KEYS_PER_PLAYER; ++k) {
            fprintf(fp, "%d ", DAT_0044fb70[p * PLAYER_KEY_STRIDE + k]);
        }
        fprintf(fp, "\n");
    }

    /* 0x00423278: Encode player names ('`' -> '\'', ' ' -> '`') and ensure non-empty defaults "1".."4" */
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        char *name = &DAT_0044fcc0[p * PLAYER_NAME_STRIDE];
        size_t len = strlen(name);
        for (size_t i = 0; i < len; ++i) {
            if (name[i] == '`') {
                name[i] = '\'';
            } else if (name[i] == ' ') {
                name[i] = '`';
            }
        }
    }

    if (DAT_0044fcc0[0 * PLAYER_NAME_STRIDE] == '\0') {
        strcpy(&DAT_0044fcc0[0 * PLAYER_NAME_STRIDE], "1");
    }
    if (DAT_0044fcc0[1 * PLAYER_NAME_STRIDE] == '\0') {
        strcpy(&DAT_0044fcc0[1 * PLAYER_NAME_STRIDE], "2");
    }
    if (DAT_0044fcc0[2 * PLAYER_NAME_STRIDE] == '\0') {
        strcpy(&DAT_0044fcc0[2 * PLAYER_NAME_STRIDE], "3");
    }
    if (DAT_0044fcc0[3 * PLAYER_NAME_STRIDE] == '\0') {
        strcpy(&DAT_0044fcc0[3 * PLAYER_NAME_STRIDE], "4");
    }

    fprintf(fp, "%s %s %s %s\n",
            &DAT_0044fcc0[0 * PLAYER_NAME_STRIDE],
            &DAT_0044fcc0[1 * PLAYER_NAME_STRIDE],
            &DAT_0044fcc0[2 * PLAYER_NAME_STRIDE],
            &DAT_0044fcc0[3 * PLAYER_NAME_STRIDE]);

    if (DAT_0044fd18[0] == '\0') {
        strcpy(DAT_0044fd18, "<No name>");
    }
    if (DAT_0044f900[0] == '\0') {
        strcpy(DAT_0044f900, "<No info>");
    }
    if (DAT_0044f890[0] == '\0') {
        strcpy(DAT_0044f890, "<No email>");
    }

    fprintf(fp, "%d\n", DAT_00450be8);
    fprintf(fp, "%d\n", DAT_00450be4);
    fprintf(fp, "%s\n", DAT_0044fd18);
    fprintf(fp, "%s\n", DAT_0044f890);
    fprintf(fp, "%s", DAT_0044f900);
    fclose(fp);

    /* Restore spaces in player names in memory */
    for (int p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        char *name = &DAT_0044fcc0[p * PLAYER_NAME_STRIDE];
        size_t len = strlen(name);
        for (size_t i = 0; i < len; ++i) {
            if (name[i] == '`') {
                name[i] = ' ';
            }
        }
    }
}

int func_00423480_load_control_txt(void)
{
    return FUN_00423480();
}

int func_00423230_save_control_txt(void)
{
    FUN_00423230();
    return 1;
}

int func_004233e0_save_control_txt(void)
{
    FUN_00423230();
    return 1;
}


