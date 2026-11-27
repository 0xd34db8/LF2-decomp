#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>

/*
 * Virtual Address: 0x0040C910
 * Function: stage_dat_loader (FUN_0040c910)
 * Class / Subsystem: Data / Stage Wave & Spawn Loader
 *
 * Description:
 *   Decrypts data\stage.dat into data\temporary.txt and parses up to 60 <stage>
 *   entries, 100 <phase> wave definitions per stage, and 60 spawn slots per phase
 *   into the manager block at in_ECX, then scrubs data\temporary.txt.
 */

// FUNCTION: LF2 0x0040c910
void FUN_0040c910(void)
{
    uint8_t *ecx = (uint8_t *)in_ECX;
    if (!ecx) {
        return;
    }

    FUN_00414a30("data\\stage.dat", "data\\temporary.txt");
    FILE *fp = fopen("data\\temporary.txt", "r");
    if (!fp) {
        return;
    }

    for (int s = 0; s < 0x3c; ++s) {
        *(int32_t *)(ecx + (size_t)s * 0x149b08 + 0x7d0) = -1;
    }

    char tok[204];
    int stage_id = 0;
    while (!feof(fp)) {
        if (fscanf(fp, "%203s", tok) != 1) {
            break;
        }
        if (strcmp(tok, "<stage>") == 0) {
            int phase_idx = 0;
            while (fscanf(fp, "%203s", tok) == 1 && strcmp(tok, "<stage_end>") != 0) {
                if (strcmp(tok, "id:") == 0) {
                    if (fscanf(fp, "%d", &stage_id) == 1 && stage_id >= 0 && stage_id < 0x3c) {
                        size_t stage_off = (size_t)stage_id * 0x149b08;
                        for (size_t p_off = 0; p_off < 0x149b00; p_off += 0x34c0) {
                            uint8_t *phase_base = ecx + stage_off + p_off;
                            *(int32_t *)(phase_base + 0x7d8) = -1;
                            *(int32_t *)(phase_base + 0x3c90) = -1;
                            phase_base[0x7dc] = 0;
                            for (size_t s_off = 0; s_off < 0x3480; s_off += 0xe0) {
                                uint8_t *sp = phase_base + s_off;
                                *(int32_t *)(sp + 0x8bc) = -1;
                                *(int32_t *)(sp + 0x8c0) = 500;
                                *(int32_t *)(sp + 0x8c4) = 500;
                                *(int32_t *)(sp + 0x8c8) = 1;
                                *(int32_t *)(sp + 0x8cc) = 0;
                                *(int32_t *)(sp + 0x8e8) = 0;
                                *(int32_t *)(sp + 0x8d0) = 0;
                                *(int32_t *)(sp + 0x8d4) = 0;
                                *(double  *)(sp + 0x8e0) = 0.0;
                                *(int32_t *)(sp + 0x8dc) = 0;
                                *(int32_t *)(sp + 0x8d8) = 9;
                            }
                        }
                        *(int32_t *)(ecx + stage_off + 0x7d0) = -1;
                        phase_idx = 0;
                    }
                } else if (strcmp(tok, "<phase>") == 0) {
                    size_t stage_off = (size_t)stage_id * 0x149b08;
                    size_t phase_off = (size_t)phase_idx * 0x34c0;
                    int next_phase_idx = phase_idx + 1;
                    size_t x_cursor = phase_off + 0x7e0;
                    ptrdiff_t spawn_rel = -0xe0;

                    ecx[stage_off + phase_off + 0x7dc] = 0;
                    *(int32_t *)(ecx + stage_off + 0x7d0) = next_phase_idx;

                    while (fscanf(fp, "%203s", tok) == 1 && strcmp(tok, "<phase_end>") != 0) {
                        uint8_t *stage_ptr = ecx + stage_off;
                        uint8_t *phase_ptr = stage_ptr + phase_off;
                        if (strcmp(tok, "bound:") == 0) {
                            int32_t *bound_ptr = (int32_t *)(phase_ptr + 0x7d8);
                            if (fscanf(fp, "%d", bound_ptr) == 1) {
                                int32_t default_x = *bound_ptr + 0x50;
                                for (size_t s_idx = 0; s_idx < 0x3c; ++s_idx) {
                                    *(int32_t *)(phase_ptr + 0x8c0 + s_idx * 0xe0) = default_x;
                                }
                            }
                        } else if (strcmp(tok, "id:") == 0) {
                            x_cursor += 0xe0;
                            spawn_rel += 0xe0;
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8bc));
                        } else if (strcmp(tok, "music:") == 0) {
                            fscanf(fp, "%s", (char *)(phase_ptr + 0x7dc));
                        } else if (strcmp(tok, "x:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(stage_ptr + x_cursor));
                        } else if (strcmp(tok, "hp:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8c4));
                        } else if (strcmp(tok, "times:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8c8));
                        } else if (strcmp(tok, "reserve:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8cc));
                        } else if (strcmp(tok, "<boss>") == 0) {
                            *(int32_t *)(phase_ptr + spawn_rel + 0x8e8) = 2;
                        } else if (strcmp(tok, "join:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8d0));
                        } else if (strcmp(tok, "join_reserve:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8d4));
                        } else if (strcmp(tok, "<soldier>") == 0) {
                            *(int32_t *)(phase_ptr + spawn_rel + 0x8e8) = 1;
                            *(int32_t *)(phase_ptr + spawn_rel + 0x8c8) = 0x32;
                        } else if (strcmp(tok, "when_clear_goto_phase:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + 0x3c90));
                        } else if (strcmp(tok, "ratio:") == 0) {
                            fscanf(fp, "%lf", (double *)(phase_ptr + spawn_rel + 0x8e0));
                        } else if (strcmp(tok, "y:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8dc));
                        } else if (strcmp(tok, "act:") == 0) {
                            fscanf(fp, "%d", (int32_t *)(phase_ptr + spawn_rel + 0x8d8));
                        }
                    }
                    phase_idx = next_phase_idx;
                }
            }
        }
    }

    fclose(fp);
    FILE *tmp_fp = fopen("data\\temporary.txt", "w");
    if (tmp_fp) {
        fprintf(tmp_fp, "Do not erase this file.");
        fclose(tmp_fp);
    }
}
