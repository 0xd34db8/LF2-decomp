#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Virtual Address: 0x0040C160
 * Function: load_bg_dat (FUN_0040c160)
 * Class / Subsystem: Data / Background Descriptor Loader
 *
 * Description:
 *   Decrypts (if suffix is .dat/.DAT) and parses a background configuration file
 *   into the background slot at in_ECX + bg_slot * 0x990, accumulating the data
 *   checksum into DAT_0044f620 and converting 16-bit RGB565 rect: colors to RGB888.
 */

// FUNCTION: LF2 0x0040c160
void FUN_0040c160(int bg_slot, int bg_id, const char *bg_path)
{
    (void)bg_id;
    uint8_t *ecx = (uint8_t *)in_ECX;
    if (!ecx || !bg_path) {
        return;
    }

    size_t plen = strlen(bg_path);
    int is_dat = 0;
    if (plen >= 3 &&
        (bg_path[plen - 3] == 'd' || bg_path[plen - 3] == 'D') &&
        (bg_path[plen - 2] == 'a' || bg_path[plen - 2] == 'A') &&
        (bg_path[plen - 1] == 't' || bg_path[plen - 1] == 'T')) {
        is_dat = 1;
    }

    FILE *fp = NULL;
    if (is_dat) {
        FUN_004148a0(bg_path);
        fp = fopen("data\\temporary.txt", "r");
    } else {
        fp = fopen(bg_path, "r");
    }
    if (!fp) {
        return;
    }

    size_t bg_off = (size_t)bg_slot * 0x990;
    uint8_t *bg_base = ecx + bg_off;
    *(int32_t *)(bg_base + 0x4d45dcc) = 0;
    *(int32_t *)(bg_base + 0x4d45dbc) = 0;
    *(int32_t *)(bg_base + 0x4d45dc0) = 0;

    char tok[100];
    while (!feof(fp)) {
        if (fscanf(fp, "%99s", tok) != 1) {
            break;
        }
        size_t tlen = strlen(tok);
        for (size_t u = 0; u < tlen; ++u) {
            DAT_0044f620 += (int)(int8_t)tok[u] * (int)u;
        }

        if (strcmp(tok, "name:") == 0) {
            char name_buf[30];
            if (fscanf(fp, "%29s", name_buf) == 1) {
                name_buf[29] = '\0';
                size_t nlen = strlen(name_buf);
                for (size_t i = 0; i < nlen; ++i) {
                    if (name_buf[i] == '_') {
                        name_buf[i] = ' ';
                    }
                }
                strcpy((char *)(bg_base + 0x4d4617c), name_buf);
            }
        } else if (strcmp(tok, "width:") == 0) {
            fscanf(fp, "%d", (int32_t *)(bg_base + 0x4d45db0));
        } else if (strcmp(tok, "zboundary:") == 0) {
            fscanf(fp, "%d %d",
                   (int32_t *)(bg_base + 0x4d45db4),
                   (int32_t *)(bg_base + 0x4d45db8));
        } else if (strcmp(tok, "perspective:") == 0) {
            fscanf(fp, "%d %d",
                   (int32_t *)(bg_base + 0x4d45dbc),
                   (int32_t *)(bg_base + 0x4d45dc0));
        } else if (strcmp(tok, "shadow:") == 0) {
            char unused_str[30];
            fscanf(fp, "%s %29s %d %d",
                   (char *)(bg_base + 0x4d46154),
                   unused_str,
                   (int32_t *)(bg_base + 0x4d45dc4),
                   (int32_t *)(bg_base + 0x4d45dc8));
            void *shadow_mem = operator_new(0x1f50);
            uint32_t shadow_surf = 0;
            if (shadow_mem != NULL) {
                void *saved_ecx = in_ECX;
                in_ECX = shadow_mem;
                shadow_surf = (uint32_t)FUN_0043ee50(0x40, (char *)(bg_base + 0x4d46154), 0);
                in_ECX = saved_ecx;
            }
            *(uint32_t *)(bg_base + 0x4d4673c) = shadow_surf;
        } else if (strcmp(tok, "layer:") == 0) {
            int32_t *layer_cnt_ptr = (int32_t *)(bg_base + 0x4d45dcc);
            int32_t layer_idx = *layer_cnt_ptr;
            fscanf(fp, "%s", (char *)(bg_base + (size_t)layer_idx * 0x1e + 0x4d45dd0));

            size_t slot_off = ((size_t)bg_slot * 0x264 + (size_t)layer_idx) * 4;
            *(uint32_t *)(ecx + 0x4d4664c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d4628c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d46304 + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d46214 + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d4637c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d463f4 + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d4619c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d4655c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d4646c + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d464e4 + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d465d4 + slot_off) = 0;
            *(int32_t *)(ecx + 0x4d466c4 + slot_off) = 0;

            while (fscanf(fp, "%99s", tok) == 1 && strcmp(tok, "layer_end") != 0) {
                if (strcmp(tok, "transparency:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d4619c + slot_off));
                } else if (strcmp(tok, "width:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d46214 + slot_off));
                } else if (strcmp(tok, "x:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d4628c + slot_off));
                } else if (strcmp(tok, "y:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d46304 + slot_off));
                } else if (strcmp(tok, "height:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d4637c + slot_off));
                } else if (strcmp(tok, "rect:") == 0) {
                    long rect_raw = 0;
                    fscanf(fp, "%ld", &rect_raw);
                    uint32_t u = (uint32_t)rect_raw;
                    *(uint32_t *)(ecx + 0x4d4664c + slot_off) =
                        ((((int32_t)u >> 11 & 0x1fU) * 0x200 + ((int32_t)u >> 5 & 0x3fU)) * 0x80 +
                         (u & 0x1fU)) * 8 + 0x70707U;
                } else if (strcmp(tok, "rect32:") == 0) {
                    long rect32_raw = 0;
                    fscanf(fp, "%ld", &rect32_raw);
                    *(uint32_t *)(ecx + 0x4d4664c + slot_off) = (uint32_t)rect32_raw;
                } else if (strcmp(tok, "loop:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d463f4 + slot_off));
                } else if (strcmp(tok, "cc:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d4655c + slot_off));
                } else if (strcmp(tok, "c1:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d4646c + slot_off));
                } else if (strcmp(tok, "c2:") == 0) {
                    fscanf(fp, "%d", (int32_t *)(ecx + 0x4d464e4 + slot_off));
                }
            }
            *layer_cnt_ptr = layer_idx + 1;
        }
    }

    fclose(fp);
    FILE *tmp_fp = fopen("data\\temporary.txt", "w");
    if (tmp_fp) {
        fprintf(tmp_fp, "Do not erase this file.");
        fclose(tmp_fp);
    }
}
