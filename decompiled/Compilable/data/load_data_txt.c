#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Virtual Address: 0x004122F0
 * Function: load_data_txt (FUN_004122f0)
 * Class / Subsystem: Data / Master Manifest Loader
 *
 * Description:
 *   Initializes built-in arena slot 99 ("Lee On Road", width 2400, z [350, 470],
 *   shadow1, back99_1..3, and "Random" label), parses <object> and <background>
 *   entries from data.txt (accumulating DAT_0044f620 checksums and instantiating
 *   each file_t / background via FUN_0040ef70 / FUN_0040c160), and finishes by
 *   invoking stage_dat_loader (FUN_0040c910).
 */

// FUNCTION: LF2 0x004122f0
void FUN_004122f0(const char *manifest_path, int progress_arg)
{
    uint8_t *ecx = (uint8_t *)in_ECX;
    if (!ecx || !manifest_path) {
        return;
    }

    /* Default arena slot 99 initialization */
    *(int32_t *)(ecx + 0x4d81060) = 0x960; /* 2400 */
    *(int32_t *)(ecx + 0x4d81064) = 0x15e; /* 350 */
    *(int32_t *)(ecx + 0x4d81068) = 0x1d6; /* 470 */
    *(int32_t *)(ecx + 0x4d81074) = 0x25;  /* 37 */
    *(int32_t *)(ecx + 0x4d81078) = 9;

    memcpy(ecx + 0x4d8142c, "Lee On Road", 12);
    memcpy(ecx + 0x4d81404, "shadow1", 8);

    void *shadow_mem = operator_new(0x1f50);
    uint32_t shadow_surf = 0;
    if (shadow_mem != NULL) {
        void *saved_ecx = in_ECX;
        in_ECX = shadow_mem;
        shadow_surf = (uint32_t)FUN_0043ee50(0x40, (char *)(ecx + 0x4d81404), 0);
        in_ECX = saved_ecx;
    }
    *(uint32_t *)(ecx + 0x4d819ec) = shadow_surf;

    const char *back_names[3] = { "back99_1", "back99_2", "back99_3" };
    const size_t back_name_offs[3] = { 0x4d81080, 0x4d8109e, 0x4d810bc };
    const size_t back_surf_offs[3] = { 0x4d81974, 0x4d81978, 0x4d8197c };
    for (int i = 0; i < 3; ++i) {
        strcpy((char *)(ecx + back_name_offs[i]), back_names[i]);
        void *mem = operator_new(0x1f50);
        uint32_t surf = 0;
        if (mem != NULL) {
            void *saved_ecx = in_ECX;
            in_ECX = mem;
            surf = (uint32_t)FUN_0043ee50(0x40, (char *)(ecx + back_name_offs[i]), 0);
            in_ECX = saved_ecx;
        }
        *(uint32_t *)(ecx + back_surf_offs[i]) = surf;
    }

    strcpy((char *)(ecx + 0x4d81dbc), "Random");
    strcpy((char *)(ecx + 0x4d82388), manifest_path);
    *(int32_t *)(ecx + 0x4d82384) = 0;
    *(int32_t *)(ecx + 0x4d82380) = 0;
#ifdef _WIN32
    (void)timeGetTime();
#endif

    FILE *fp = fopen(manifest_path, "r");
    if (!fp) {
        return;
    }

    char tok[200];
    char obj_path[200];
    char bg_path[200];
    int obj_id = 0;
    int obj_type = 0;
    int bg_id = 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%199s", tok) != 1) {
            break;
        }
        size_t tlen = strlen(tok);
        for (size_t u = 0; u < tlen; ++u) {
            DAT_0044f620 += (int)(int8_t)tok[u] * (int)u;
        }

        if (strcmp(tok, "<object>") == 0) {
            while (fscanf(fp, "%199s", tok) == 1 && strcmp(tok, "<object_end>") != 0) {
                if (strcmp(tok, "id:") == 0) {
                    if (fscanf(fp, "%d %199s %d %199s %199s",
                               &obj_id, tok, &obj_type, tok, obj_path) == 5) {
                        FUN_004242e0(obj_path, progress_arg);
                        file_t *file_slot = (file_t *)operator_new(sizeof(file_t));
                        if (file_slot != NULL) {
                            void *saved_ecx = in_ECX;
                            in_ECX = file_slot;
                            FUN_0040ef70(obj_id, obj_type, obj_path, progress_arg);
                            in_ECX = saved_ecx;
                        }
                        int32_t fcnt = *(int32_t *)(ecx + 0x4d82380);
                        ((file_t **)ecx)[fcnt] = file_slot;
                        *(int32_t *)(ecx + 0x4d82380) = fcnt + 1;
                    }
                }
            }
        } else if (strcmp(tok, "<background>") == 0) {
            while (fscanf(fp, "%199s", tok) == 1 && strcmp(tok, "<background_end>") != 0) {
                if (strcmp(tok, "id:") == 0) {
                    if (fscanf(fp, "%d %199s %199s", &bg_id, tok, bg_path) == 3) {
                        int32_t bg_idx = *(int32_t *)(ecx + 0x4d82384);
                        void *saved_ecx = in_ECX;
                        in_ECX = ecx;
                        FUN_0040c160(bg_idx, bg_id, bg_path);
                        in_ECX = saved_ecx;
                        *(int32_t *)(ecx + 0x4d82384) = bg_idx + 1;
                    }
                }
            }
        }
    }

    fclose(fp);
    void *saved_ecx = in_ECX;
    in_ECX = ecx;
    FUN_0040c910();
    in_ECX = saved_ecx;
}
