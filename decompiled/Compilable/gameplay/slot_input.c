#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x00417200: FUN_00417200 (Broad-phase 2D bounding box overlap test)
 *   0x00419380: FUN_00419380 (Per-frame frame_id4/arest update & pairwise collision dispatch)
 *   0x004196F0: FUN_004196f0 (Velocity / impulse averaging pass across all 400 active objects)
 *   0x004197A0: FUN_004197a0 (Remote / network input bits unpacking & flag latching)
 *   0x004198F0: FUN_004198f0 (Local player input bits latching & replay recording)
 *   0x00419A60: FUN_00419a60 (Master per-slot controller / AI input dispatch & loop)
 */

// 0x00417200: Broad-phase 2D bounding box overlap test between attacker and injured
int FUN_00417200(int param_1, int param_2)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || param_1 < 0 || param_1 >= MAX_OBJECTS || param_2 < 0 || param_2 >= MAX_OBJECTS) {
        return 0;
    }
    if (!global->is_object_exists[param_1] || !global->is_object_exists[param_2]) {
        return 0;
    }
    object_t *attacker = global->objects[param_1];
    object_t *injured = global->objects[param_2];
    if (!attacker || !injured || !attacker->file || !injured->file) {
        return 0;
    }
    if (attacker->frame_id1 >= MAX_FRAMES || injured->frame_id1 >= MAX_FRAMES ||
        attacker->frame_id4 >= MAX_FRAMES || injured->frame_id4 >= MAX_FRAMES) {
        return 0;
    }

    frame_t *att_f1 = &attacker->file->frames[attacker->frame_id1];
    frame_t *inj_f1 = &injured->file->frames[injured->frame_id1];
    if (att_f1->itrs_size == 0 || inj_f1->bdys_size == 0 ||
        attacker->arest > 0 || injured->vrest_of_objects[param_1] > 0) {
        return 0;
    }

    frame_t *att_f4 = &attacker->file->frames[attacker->frame_id4];
    frame_t *inj_f4 = &injured->file->frames[injured->frame_id4];
    if (att_f4->itrs_size == 0 || !att_f4->itrs || inj_f4->bdys_size == 0 || !inj_f4->bdys) {
        return 0;
    }

    // Dynamic union AABB across injured bdys (0x8EC..0x8F8 in 0x0040ef70)
    int32_t bdy_min_x = inj_f4->bdys[0].x;
    int32_t bdy_min_y = inj_f4->bdys[0].y;
    int32_t bdy_max_x = inj_f4->bdys[0].x + inj_f4->bdys[0].w;
    int32_t bdy_max_y = inj_f4->bdys[0].y + inj_f4->bdys[0].h;
    for (uint32_t k = 1; k < inj_f4->bdys_size; ++k) {
        const bdy_t *b = &inj_f4->bdys[k];
        if (b->x < bdy_min_x) bdy_min_x = b->x;
        if (b->y < bdy_min_y) bdy_min_y = b->y;
        if (b->x + b->w > bdy_max_x) bdy_max_x = b->x + b->w;
        if (b->y + b->h > bdy_max_y) bdy_max_y = b->y + b->h;
    }
    int32_t bdy_bw = bdy_max_x - bdy_min_x;
    int32_t bdy_bh = bdy_max_y - bdy_min_y;

    // Dynamic union AABB across attacker itrs (0x8DC..0x8E8 in 0x0040ef70)
    int32_t itr_min_x = att_f4->itrs[0].x;
    int32_t itr_min_y = att_f4->itrs[0].y;
    int32_t itr_max_x = att_f4->itrs[0].x + att_f4->itrs[0].w;
    int32_t itr_max_y = att_f4->itrs[0].y + att_f4->itrs[0].h;
    for (uint32_t k = 1; k < att_f4->itrs_size; ++k) {
        const itr_t *it = &att_f4->itrs[k];
        if (it->x < itr_min_x) itr_min_x = it->x;
        if (it->y < itr_min_y) itr_min_y = it->y;
        if (it->x + it->w > itr_max_x) itr_max_x = it->x + it->w;
        if (it->y + it->h > itr_max_y) itr_max_y = it->y + it->h;
    }
    int32_t itr_bw = itr_max_x - itr_min_x;
    int32_t itr_bh = itr_max_y - itr_min_y;

    int32_t inj_left = (injured->facing == FACING_RIGHT)
        ? (bdy_min_x + (injured->x - inj_f4->centerx))
        : (((inj_f4->centerx + injured->x) - bdy_bw) - bdy_min_x);
    int32_t inj_top = bdy_min_y + (injured->y - inj_f4->centery);

    int32_t att_left = (attacker->facing == FACING_RIGHT)
        ? (itr_min_x + (attacker->x - att_f4->centerx))
        : (((att_f4->centerx + attacker->x) - itr_bw) - itr_min_x);
    int32_t att_top = itr_min_y + (attacker->y - att_f4->centery);

    return FUN_004171c0(inj_left, inj_top, bdy_bw, bdy_bh,
                        att_left, att_top, itr_bw, itr_bh);
}

// 0x00419380: Per-frame frame_id4/arest reset, pairwise vrest decrement & collision dispatch
void FUN_00419380(int param_1)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;

    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) continue;
        object_t *obj = global->objects[i];
        if (!obj || !obj->file) continue;

        obj->frame_id4 = obj->frame_id1;
        if (obj->frame_id1 < MAX_FRAMES) {
            frame_t *f1 = &obj->file->frames[obj->frame_id1];
            if (f1->itrs_size == 0) {
                obj->arest = 0;
            } else if (f1->state == 1001) {
                int32_t hid = obj->holder_id;
                if (hid >= 0 && hid < MAX_OBJECTS && global->objects[hid] && global->objects[hid]->file) {
                    object_t *holder = global->objects[hid];
                    if (holder->frame_id1 < MAX_FRAMES &&
                        holder->file->frames[holder->frame_id1].wpoint.attacking == 0) {
                        obj->arest = 0;
                    }
                }
            }
        }
    }

    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) continue;
        object_t *oi = global->objects[i];
        for (int32_t j = i + 1; j < MAX_OBJECTS; ++j) {
            if (global->is_object_exists[j] == 0) continue;
            object_t *oj = global->objects[j];

            if (oi && (int8_t)oi->vrest_of_objects[j] > 0) {
                oi->vrest_of_objects[j]--;
            }
            if (oj && (int8_t)oj->vrest_of_objects[i] > 0) {
                oj->vrest_of_objects[i]--;
            }
            if (FUN_00417200(i, j) != 0) {
                FUN_00417400(i, j, param_1);
            }
            if (FUN_00417200(j, i) != 0) {
                FUN_00417400(j, i, param_1);
            }
        }
    }

    FUN_004064d0();
}

// 0x004196F0: Physics velocity/impulse averaging pass across active objects
void FUN_004196f0(void)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;

    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) continue;
        object_t *obj = global->objects[i];
        if (!obj) continue;

        if (obj->shaking == 0) {
            if (obj->attacks != 0) {
                double factor = 2.0 / (double)(obj->attacks + 1);
                obj->x_velocity = obj->pic_x_gain * factor;
                obj->y_velocity = obj->y_accl * factor;
                obj->z_velocity = obj->z_accl * factor;
                obj->attacks = 0;
            }
            obj->pic_x_gain = 0.0;
            obj->y_accl = 0.0;
            obj->z_accl = 0.0;
        }
    }
}

// 0x004197A0: Remote / network input bits unpacking & flag latching
void FUN_004197a0(const uint8_t *param_1, int param_2)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;
    const uint8_t *packet_bytes = param_1;

    for (int32_t i = 0; i < 8; ++i) {
        object_t *obj = global->objects[i];
        if (!obj) continue;

        // Shift current input into previous input
        obj->holding_up     = obj->click_up;
        obj->holding_down   = obj->click_down;
        obj->holding_left   = obj->click_left;
        obj->holding_right  = obj->click_right;
        obj->holding_attack = obj->click_attack;
        obj->holding_jump   = obj->click_jump;
        obj->holding_defend = obj->click_defend;

        if (param_2 == 0 && packet_bytes) {
            obj->click_up     = 0;
            obj->click_down   = 0;
            obj->click_left   = 0;
            obj->click_right  = 0;
            obj->click_attack = 0;
            obj->click_jump   = 0;
            obj->click_defend = 0;

            uint8_t b = packet_bytes[i];
            if (b & 0x80) obj->click_up     = 1;
            if (b & 0x40) obj->click_down   = 1;
            if (b & 0x20) obj->click_left   = 1;
            if (b & 0x10) obj->click_right  = 1;
            if (b & 0x08) obj->click_attack = 1;
            if (b & 0x04) obj->click_jump   = 1;
            if (b & 0x02) obj->click_defend = 1;
        }
    }
}

// 0x004198F0: Local player input bits latching & replay recording
void FUN_004198f0(uint8_t *param_1, int param_2, int param_3)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || !param_1) return;

    for (int32_t i = 0; i < 8; ++i) {
        if (DAT_00450b4c[i] == -1) { // Local player slot
            object_t *obj = global->objects[i];
            if (!obj) continue;

            obj->holding_up     = obj->click_up;
            obj->holding_down   = obj->click_down;
            obj->holding_left   = obj->click_left;
            obj->holding_right  = obj->click_right;
            obj->holding_attack = obj->click_attack;
            obj->holding_jump   = obj->click_jump;
            obj->holding_defend = obj->click_defend;

            if (param_2 == 0) {
                obj->click_up     = 0;
                obj->click_down   = 0;
                obj->click_left   = 0;
                obj->click_right  = 0;
                obj->click_attack = 0;
                obj->click_jump   = 0;
                obj->click_defend = 0;

                uint8_t b = param_1[i];
                if (b & 0x80) obj->click_up     = 1;
                if (b & 0x40) obj->click_down   = 1;
                if (b & 0x20) obj->click_left   = 1;
                if (b & 0x10) obj->click_right  = 1;
                if (b & 0x08) obj->click_attack = 1;
                if (b & 0x04) obj->click_jump   = 1;
                if (b & 0x02) obj->click_defend = 1;

                if (DAT_00450b80 != 0) {
                    param_1[param_3 + i] = b;
                }
            }
        }
    }
}

// 0x00419A60: Master per-slot controller / AI input dispatch & loop
void FUN_00419a60(int param_1, int param_2, uint8_t *param_3)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;

    uint8_t *out_packed = param_3;

    if (DAT_00450b84 == 0) {
        for (int32_t i = 0; i < 8; ++i) {
            int32_t slot_type = DAT_00450b4c[i];
            if (slot_type > 0) {
                object_t *obj = global->objects[i];
                if (!obj) continue;

                obj->holding_up     = obj->click_up;
                obj->holding_down   = obj->click_down;
                obj->holding_left   = obj->click_left;
                obj->holding_right  = obj->click_right;
                obj->holding_attack = obj->click_attack;
                obj->holding_jump   = obj->click_jump;
                obj->holding_defend = obj->click_defend;

                if (param_1 == 0) {
                    obj->click_up     = 0;
                    obj->click_down   = 0;
                    obj->click_left   = 0;
                    obj->click_right  = 0;
                    obj->click_attack = 0;
                    obj->click_jump   = 0;
                    obj->click_defend = 0;

                    uint32_t slot_idx = (uint32_t)slot_type - 1;
                    if (slot_idx < 4) {
                        int32_t key_offset = slot_type * 0x50 / (int32_t)sizeof(int);
                        int32_t ctrl_type = DAT_0044fb20[key_offset];
                        if (ctrl_type == 0) {
                            // Keyboard controls
                            int up_key     = DAT_0044fb20[key_offset + 1];
                            int down_key   = DAT_0044fb20[key_offset + 2];
                            int left_key   = DAT_0044fb20[key_offset + 3];
                            int right_key  = DAT_0044fb20[key_offset + 4];
                            int attack_key = DAT_0044fb20[key_offset + 5];
                            int jump_key   = DAT_0044fb20[key_offset + 6];
                            int defend_key = DAT_0044fb20[key_offset + 7];

                            if (up_key >= 0 && up_key < 256 && DAT_00455378[up_key] == 'd') {
                                obj->click_up = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x80;
                            }
                            if (down_key >= 0 && down_key < 256 && DAT_00455378[down_key] == 'd') {
                                obj->click_down = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x40;
                            }
                            if (left_key >= 0 && left_key < 256 && DAT_00455378[left_key] == 'd') {
                                obj->click_left = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x20;
                            }
                            if (right_key >= 0 && right_key < 256 && DAT_00455378[right_key] == 'd') {
                                obj->click_right = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x10;
                            }
                            if (attack_key >= 0 && attack_key < 256 && DAT_00455378[attack_key] == 'd') {
                                obj->click_attack = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x08;
                            }
                            if (jump_key >= 0 && jump_key < 256 && DAT_00455378[jump_key] == 'd') {
                                obj->click_jump = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x04;
                            }
                            if (defend_key >= 0 && defend_key < 256 && DAT_00455378[defend_key] == 'd') {
                                obj->click_defend = 1;
                                if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x02;
                            }
                        } else if (ctrl_type > 0) {
                            // Joystick / gamepad
                            int joy_base = (ctrl_type * 3 - 3) * 0x10;
                            if (joy_base >= 0 && joy_base + 16 <= 128) {
                                int atk_btn = DAT_0044fb20[key_offset + 8];
                                int jmp_btn = DAT_0044fb20[key_offset + 9];
                                int def_btn = DAT_0044fb20[key_offset + 10];

                                if (DAT_00453ff0[joy_base] != '\0') {
                                    obj->click_up = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x80;
                                }
                                if (DAT_00453ff0[joy_base + 1] != '\0') {
                                    obj->click_down = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x40;
                                }
                                if (DAT_00453ff0[joy_base + 3] != '\0') {
                                    obj->click_left = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x20;
                                }
                                if (DAT_00453ff0[joy_base + 2] != '\0') {
                                    obj->click_right = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x10;
                                }
                                if (atk_btn >= 0 && joy_base + 4 + atk_btn < 128 &&
                                    DAT_00453ff0[joy_base + 4 + atk_btn] != '\0') {
                                    obj->click_attack = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x08;
                                }
                                if (jmp_btn >= 0 && joy_base + 4 + jmp_btn < 128 &&
                                    DAT_00453ff0[joy_base + 4 + jmp_btn] != '\0') {
                                    obj->click_jump = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x04;
                                }
                                if (def_btn >= 0 && joy_base + 4 + def_btn < 128 &&
                                    DAT_00453ff0[joy_base + 4 + def_btn] != '\0') {
                                    obj->click_defend = 1;
                                    if (out_packed && DAT_00450b80 != 0) *out_packed |= 0x02;
                                }
                            }
                        }
                    }

                    if (DAT_0044f1af > 0) {
                        if (obj->click_up != 0)     DAT_0044d040[i] |= 0x80;
                        if (obj->click_down != 0)   DAT_0044d040[i] |= 0x40;
                        if (obj->click_left != 0)   DAT_0044d040[i] |= 0x20;
                        if (obj->click_right != 0)  DAT_0044d040[i] |= 0x10;
                        if (obj->click_attack != 0) DAT_0044d040[i] |= 0x08;
                        if (obj->click_jump != 0)   DAT_0044d040[i] |= 0x04;
                        if (obj->click_defend != 0) DAT_0044d040[i] |= 0x02;
                    }
                }
            }
            if (out_packed) out_packed++;
        }
    }

    // AI / projectile steering dispatch for world objects 10..399
    for (int32_t i = 10; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) continue;
        object_t *obj = global->objects[i];
        if (!obj || !obj->file) continue;

        if (obj->file->type == TYPE_CHARACTER) {
            FUN_004094b0(i, param_2);
        } else if (obj->file->frames[obj->frame_id1].hit_Fa > 0) {
            FUN_00406ba0(i);
        }
    }
}

