#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses (Phases 21 & 22):
 *   0x0040D960: FUN_0040d960 (Per-object frame timer, sound trigger & frame.next advancement)
 *   0x0040E170: FUN_0040e170 (Combo timer == 5 interruption check helper)
 *   0x0040E2D0: FUN_0040e2d0 (Frame transition & HP/MP cost helper)
 *   0x0040E450: FUN_0040e450 (5-entry input history shift register)
 *   0x0040E490: FUN_0040e490 (Per-object physics, velocity integration, gravity & ground landing)
 *   0x00412800..0x00412F40: 9 special-move combo recognizers (D>A, D<A, D^A, DvA, D>J, D<J, D^J, DvJ, D>J>A)
 *   0x00413080: FUN_00413080 (Master per-object input/state tick & combo dispatcher)
 */

static int32_t resolve_frame_sound_id(const frame_t *frame)
{
    if (!frame) return -1;
    if (frame->sound != 0 && frame->sound_id >= 0) {
        return frame->sound_id;
    }
    if (frame->sound_id > 0) {
        return frame->sound_id;
    }
    if ((int32_t)frame->sound > 0) {
        return (int32_t)frame->sound;
    }
    return -1;
}

static void sync_wait_counter(object_t *obj, int32_t val)
{
    obj->wait_counter = val;
    obj->cpoint_hurt = val;
}

// 0x0040E450: 5-entry input history shift register
void lf2_input_history_push(object_t *obj, uint32_t key_code)
{
    if (!obj) return;
    obj->input_history[0] = obj->input_history[1];
    obj->input_history[1] = obj->input_history[2];
    obj->input_history[2] = obj->input_history[3];
    obj->input_history[3] = obj->input_history[4];
    obj->input_history[4] = (int32_t)key_code;
}

void FUN_0040e450(undefined4 param_1)
{
    lf2_input_history_push((object_t *)in_ECX, (uint32_t)param_1);
}

// 0x0040E170: Combo timer window (== 5) check helper
int lf2_combo_interrupted(const object_t *obj, char expected_key, int advanced)
{
    if (!obj) return 0;

    if (advanced == 0) {
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->left_press == 5 || obj->up_press == 5 || obj->down_press == 5 ||
            obj->right_press == 5) {
            return 1;
        }
        return 0;
    }

    if (advanced != 1) {
        return 0;
    }

    switch (expected_key) {
    case 'U':
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->left_press == 5 || obj->down_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    case 'D':
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->left_press == 5 || obj->up_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    case 'L':
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    case 'R':
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->left_press == 5 || obj->up_press == 5 || obj->down_press == 5) {
            return 1;
        }
        return 0;
    case 'd':
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->left_press == 5 ||
            obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    case 'j':
        if (obj->attack_press == 5 || obj->defend_press == 5 || obj->left_press == 5 ||
            obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    case 'a':
        if (obj->jump_press == 5 || obj->defend_press == 5 || obj->left_press == 5 ||
            obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) {
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

int FUN_0040e170(char param_1, int param_2)
{
    return lf2_combo_interrupted((const object_t *)in_ECX, param_1, param_2);
}

// 0x0040E2D0: Frame transition & MP/HP cost helper
int lf2_frame_transition(object_t *obj, int target_frame)
{
    if (!obj || !obj->file) return 0;

    bool flip_facing = (target_frame < 0);
    if (flip_facing) {
        target_frame = -target_frame;
    }
    if (target_frame == 999) {
        target_frame = 0;
    }
    if (target_frame < 0 || target_frame >= MAX_FRAMES) {
        return 0;
    }

    int frame_byte_off = target_frame * (int)sizeof(frame_t);
    const frame_t *target = &obj->file->frames[target_frame];
    if (target->present != 0) {
        if (DAT_0044d034 == 0) {
            obj->frame_id1 = (uint32_t)target_frame;
            obj->jump_press = 0;
            obj->attack_press = 0;
            obj->defend_press = 0;
            obj->down_press = 0;
            obj->up_press = 0;
            obj->left_press = 0;
            obj->right_press = 0;
            return frame_byte_off;
        }
        int32_t hp_div = target->mp / 1000;
        if (target->mp % 1000 <= obj->mp) {
            int32_t hp_cost = hp_div * 10;
            if (hp_cost < obj->hp) {
                obj->hp += hp_div * -10;
                obj->mp -= target->mp % 1000;
                obj->hp_lost += hp_div * 10;
                int32_t raw_mp = target->mp;
                frame_byte_off = raw_mp / 1000;
                obj->frame_id1 = (uint32_t)target_frame;
                obj->mp_used += raw_mp % 1000;
                if (flip_facing) {
                    obj->facing = (uint8_t)(1 - obj->facing);
                }
                obj->jump_press = 0;
                obj->attack_press = 0;
                obj->defend_press = 0;
                obj->down_press = 0;
                obj->up_press = 0;
                obj->left_press = 0;
                obj->right_press = 0;
            }
        }
        return frame_byte_off;
    }
    return frame_byte_off;
}

int FUN_0040e2d0(int param_1)
{
    return lf2_frame_transition((object_t *)in_ECX, param_1);
}

// 0x00412800: Combo D > R > A (hit_Fa, face right)
void FUN_00412800(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DRA == 0 && obj->defend_press == 5) {
        obj->click_DRA = 1;
        advanced = 1;
    }
    if (obj->click_DRA == 1) {
        if (obj->right_press == 5) {
            obj->click_DRA = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DRA = 0;
        }
    }
    if (obj->click_DRA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DRA = 3;
            advanced = 1;
        } else if (FUN_0040e170('R', advanced) != 0) {
            obj->click_DRA = 0;
        }
    }
    if (obj->click_DRA == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Fa;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->facing = FACING_RIGHT;
                obj->click_DRA = 0;
                return;
            }
        }
        if (FUN_0040e170('a', advanced) != 0) {
            obj->click_DRA = 0;
        }
    }
}

// 0x004128F0: Combo D > L > A (hit_Fa, face left)
void FUN_004128f0(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DLA == 0 && obj->defend_press == 5) {
        obj->click_DLA = 1;
        advanced = 1;
    }
    if (obj->click_DLA == 1) {
        if (obj->left_press == 5) {
            obj->click_DLA = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DLA = 0;
        }
    }
    if (obj->click_DLA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DLA = 3;
            advanced = 1;
        } else if (FUN_0040e170('L', advanced) != 0) {
            obj->click_DLA = 0;
        }
    }
    if (obj->click_DLA == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Fa;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->facing = FACING_LEFT;
                obj->click_DLA = 0;
                return;
            }
        }
        if (FUN_0040e170('a', advanced) != 0) {
            obj->click_DLA = 0;
        }
    }
}

// 0x004129E0: Combo D > U > A (hit_Ua)
void FUN_004129e0(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DUA == 0 && obj->defend_press == 5) {
        obj->click_DUA = 1;
        advanced = 1;
    }
    if (obj->click_DUA == 1) {
        if (obj->up_press == 5) {
            obj->click_DUA = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DUA = 0;
        }
    }
    if (obj->click_DUA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DUA = 3;
            advanced = 1;
        } else if (FUN_0040e170('U', advanced) != 0) {
            obj->click_DUA = 0;
        }
    }
    if (obj->click_DUA == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Ua;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->click_DUA = 0;
                return;
            }
        }
        if (FUN_0040e170('a', advanced) != 0) {
            obj->click_DUA = 0;
        }
    }
}

// 0x00412AC0: Combo D > D > A (hit_Da)
void FUN_00412ac0(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DDA == 0 && obj->defend_press == 5) {
        obj->click_DDA = 1;
        advanced = 1;
    }
    if (obj->click_DDA == 1) {
        if (obj->down_press == 5) {
            obj->click_DDA = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DDA = 0;
        }
    }
    if (obj->click_DDA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DDA = 3;
            advanced = 1;
        } else if (FUN_0040e170('D', advanced) != 0) {
            obj->click_DDA = 0;
        }
    }
    if (obj->click_DDA == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Da;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->click_DDA = 0;
                return;
            }
        }
        if (FUN_0040e170('a', advanced) != 0) {
            obj->click_DDA = 0;
        }
    }
}

// 0x00412BA0: Combo D > R > J (hit_Fj, face right)
void FUN_00412ba0(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DRJ == 0 && obj->defend_press == 5) {
        obj->click_DRJ = 1;
        advanced = 1;
    }
    if (obj->click_DRJ == 1) {
        if (obj->right_press == 5) {
            obj->click_DRJ = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DRJ = 0;
        }
    }
    if (obj->click_DRJ == 2) {
        if (obj->jump_press == 5) {
            obj->click_DRJ = 3;
            advanced = 1;
        } else if (FUN_0040e170('R', advanced) != 0) {
            obj->click_DRJ = 0;
        }
    }
    if (obj->click_DRJ == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Fj;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->facing = FACING_RIGHT;
                obj->click_DRJ = 0;
                return;
            }
        }
        if (FUN_0040e170('j', advanced) != 0) {
            obj->click_DRJ = 0;
        }
    }
}

// 0x00412C90: Combo D > L > J (hit_Fj, face left)
void FUN_00412c90(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DLJ == 0 && obj->defend_press == 5) {
        obj->click_DLJ = 1;
        advanced = 1;
    }
    if (obj->click_DLJ == 1) {
        if (obj->left_press == 5) {
            obj->click_DLJ = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DLJ = 0;
        }
    }
    if (obj->click_DLJ == 2) {
        if (obj->jump_press == 5) {
            obj->click_DLJ = 3;
            advanced = 1;
        } else if (FUN_0040e170('L', advanced) != 0) {
            obj->click_DLJ = 0;
        }
    }
    if (obj->click_DLJ == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Fj;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->facing = FACING_LEFT;
                obj->click_DLJ = 0;
                return;
            }
        }
        if (FUN_0040e170('j', advanced) != 0) {
            obj->click_DLJ = 0;
        }
    }
}

// 0x00412D80: Combo D > U > J (hit_Uj)
void FUN_00412d80(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DUJ == 0 && obj->defend_press == 5) {
        obj->click_DUJ = 1;
        advanced = 1;
    }
    if (obj->click_DUJ == 1) {
        if (obj->up_press == 5) {
            obj->click_DUJ = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DUJ = 0;
        }
    }
    if (obj->click_DUJ == 2) {
        if (obj->jump_press == 5) {
            obj->click_DUJ = 3;
            advanced = 1;
        } else if (FUN_0040e170('U', advanced) != 0) {
            obj->click_DUJ = 0;
        }
    }
    if (obj->click_DUJ == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Uj;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->click_DUJ = 0;
                return;
            }
        }
        if (FUN_0040e170('j', advanced) != 0) {
            obj->click_DUJ = 0;
        }
    }
}

// 0x00412E60: Combo D > D > J (hit_Dj)
void FUN_00412e60(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DDJ == 0 && obj->defend_press == 5) {
        obj->click_DDJ = 1;
        advanced = 1;
    }
    if (obj->click_DDJ == 1) {
        if (obj->down_press == 5) {
            obj->click_DDJ = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DDJ = 0;
        }
    }
    if (obj->click_DDJ == 2) {
        if (obj->jump_press == 5) {
            obj->click_DDJ = 3;
            advanced = 1;
        } else if (FUN_0040e170('D', advanced) != 0) {
            obj->click_DDJ = 0;
        }
    }
    if (obj->click_DDJ == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_Dj;
            if (target != 0 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->click_DDJ = 0;
                return;
            }
        }
        if (FUN_0040e170('j', advanced) != 0) {
            obj->click_DDJ = 0;
        }
    }
}

// 0x00412F40: Combo D > J > A (hit_ja, Louis EX transform / Firzen defusion)
void FUN_00412f40(void)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int advanced = 0;
    if (obj->click_DJA == 0 && obj->defend_press == 5) {
        obj->click_DJA = 1;
        advanced = 1;
    }
    if (obj->click_DJA == 1) {
        if (obj->jump_press == 5) {
            obj->click_DJA = 2;
            advanced = 1;
        } else if (FUN_0040e170('d', advanced) != 0) {
            obj->click_DJA = 0;
        }
    }
    if (obj->click_DJA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DJA = 3;
            advanced = 1;
        } else if (FUN_0040e170('j', advanced) != 0) {
            obj->click_DJA = 0;
        }
    }
    if (obj->click_DJA == 3 && obj->frame_id1 < MAX_FRAMES) {
        int32_t target = (int32_t)obj->file->frames[obj->frame_id1].hit_ja;
        if (obj->file->id != ID_LOUIS_DAT || target != 300 || obj->hp < 178 || DAT_00458428 != 0) {
            if (target != 0 && obj->uid == -1 && obj->weapon_type != TYPE_HEAVY_WEAPON) {
                FUN_0040e2d0(target);
                obj->click_DJA = 0;
                return;
            }
            if (obj->_unknown34_rest[0] == 1) {
                obj->firen_counter = 0;
                return;
            }
            if (FUN_0040e170('a', advanced) != 0) {
                obj->click_DJA = 0;
            }
        }
    }
}

// 0x0040D960: Per-object frame timer, sound trigger & frame.next advancement
void lf2_object_frame_advance(object_t *obj, int mode, int obj_idx)
{
    if (!obj || !obj->file) return;

    if (obj->shaking != 0 && obj->file->type != TYPE_ATTACK) {
        return;
    }
    if (obj->arest > 0) {
        obj->arest--;
    }
    if (obj->weapon_type < 0) {
        return;
    }
    if (obj->frame_id1 >= MAX_FRAMES) {
        return;
    }

    file_t *file = obj->file;
    const frame_t *cur = &file->frames[obj->frame_id1];
    if (cur->cpoint.kind == 2) {
        return;
    }

    if (file->type == TYPE_ATTACK && (int32_t)cur->hit_a > 0) {
        obj->hp -= (int32_t)cur->hit_a;
        if (obj->hp < 1) {
            obj->hp = 0;
            obj->frame_id1 = cur->hit_d;
        }
    }

    if (obj->blink_time > 0) {
        obj->blink_time--;
    }
    if (obj->blink_time < 0) {
        obj->blink_time++;
    }
    if (obj->fall > 0) {
        obj->fall--;
    }
    if (obj->bdefend > 0) {
        obj->bdefend--;
    }
    if ((int8_t)obj->can_hit > 0) {
        obj->can_hit--;
    }

    if (obj->frame_id1 != obj->frame_id2 && obj->frame_id1 < MAX_FRAMES) {
        int32_t snd = resolve_frame_sound_id(&file->frames[obj->frame_id1]);
        if (snd > -1) {
            FUN_00416fb0(obj->x, snd);
        }
        sync_wait_counter(obj, 0);
    }

    sync_wait_counter(obj, obj->wait_counter + 1);

    if ((int32_t)file->type >= 0 && obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_STANDING && obj->y < 0) {
        obj->frame_id1 = 212;
    }
    if (file->type == TYPE_HEAVY_WEAPON && obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == 2000 && obj->y == 0 &&
        obj->x_velocity < 0.1 && -0.1 < obj->x_velocity) {
        obj->frame_id1 = 20;
    }
    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_LYING && obj->hp < 1) {
        if ((obj->clone >= 0 || obj->team == 5 || obj_idx > 19) && obj->blink_time < 1) {
            obj->blink_time = 30;
        }
        sync_wait_counter(obj, 0);
    }
    if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == 2000) {
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        obj->wait_counter > (int32_t)file->frames[obj->frame_id1].wait) {
        sync_wait_counter(obj, 0);
        int32_t next_frame = file->frames[obj->frame_id1].next;
        if (next_frame != 0) {
            obj->frame_id1 = (uint32_t)next_frame;
            if ((int32_t)obj->frame_id1 < 0) {
                obj->facing = (uint8_t)(1 - obj->facing);
                obj->frame_id1 = (uint32_t)(-(int32_t)obj->frame_id1);
            }
            bool airborne_from_999 = false;
            if (obj->frame_id1 == 999) {
                if (obj->y == 0 || file->type != TYPE_CHARACTER) {
                    obj->frame_id1 = 0;
                } else {
                    airborne_from_999 = true;
                    obj->frame_id1 = 212;
                }
            }
            if ((int32_t)obj->frame_id1 < 0 || (int32_t)obj->frame_id1 > 399) {
                return;
            }

            if (obj->frame_id2 < MAX_FRAMES &&
                file->frames[obj->frame_id2].state == STATE_LYING &&
                file->frames[obj->frame_id1].state != STATE_ICE &&
                (((obj->team != 5 && obj->_unknown40 == 0) || DAT_00450c30 != 2) &&
                 (((mode != 1 && mode != 4) ||
                   (obj->team != 5 && obj->_unknown40 == 0)) ||
                  ((int32_t)file->id / 10 != 3 || file->id == ID_BAT_DAT)))) {
                obj->blink_time = 15;
            }

            if (obj->frame_id1 == 212 && !airborne_from_999) {
                obj->y_velocity = file->jump_height;
                if (obj->click_right == 1 && obj->click_left == 0) {
                    obj->x_velocity = file->jump_distance;
                } else if (obj->click_left == 1 && obj->click_right == 0) {
                    obj->x_velocity = -file->jump_distance;
                }
                if (obj->click_up == 0) {
                    if (obj->click_down != 0) {
                        obj->z_velocity = file->jump_distancez;
                    }
                } else if (obj->click_down == 0) {
                    obj->z_velocity = -file->jump_distancez;
                }
            }

            if (obj->frame_id1 < MAX_FRAMES) {
                int32_t snd = resolve_frame_sound_id(&file->frames[obj->frame_id1]);
                if (snd > -1) {
                    FUN_00416fb0(obj->x, snd);
                }
            }

            int32_t fmp = file->frames[obj->frame_id1].mp;
            if (fmp < 0 && DAT_0044d034 != 0) {
                if (obj->mp < fmp) {
                    obj->frame_id1 = file->frames[obj->frame_id1].hit_d;
                } else {
                    obj->mp += fmp;
                    obj->mp_used -= fmp;
                }
                if (obj->frame_id1 < MAX_FRAMES) {
                    int32_t hd = (int32_t)file->frames[obj->frame_id1].hit_d;
                    if (hd > 0) {
                        if (obj->click_left == 1 && obj->click_right == 0 &&
                            obj->y == 0 && obj->facing == FACING_RIGHT) {
                            obj->frame_id1 = (uint32_t)hd;
                        }
                        if (obj->click_left == 0 && obj->click_right == 1 &&
                            obj->y == 0 && obj->facing == FACING_LEFT) {
                            obj->frame_id1 = (uint32_t)hd;
                        }
                    }
                }
            }
        }
    }

    if (obj->frame_id1 == 110 || obj->frame_id1 == 114) {
        obj->defend_lock = 3;
    }
    if (obj->frame_id1 == 202) {
        obj->blink_time = 20;
    }
    obj->frame_id2 = obj->frame_id1;
}

void FUN_0040d960(int param_1, int param_2)
{
    lf2_object_frame_advance((object_t *)in_ECX, param_1, param_2);
}

// 0x0040E490: Per-object physics, velocity integration, gravity & ground landing
void lf2_object_physics_tick(object_t *obj)
{
    if (!obj) return;

    if (obj->shaking != 0) {
        if (obj->shaking > 0) {
            obj->shaking--;
        }
        if (obj->shaking < 0) {
            obj->shaking++;
            return;
        }
        return;
    }

    if (obj->weapon_type < 0) {
        return;
    }
    if (!obj->file || obj->frame_id1 >= MAX_FRAMES) {
        return;
    }

    file_t *file = obj->file;
    const frame_t *cur = &file->frames[obj->frame_id1];
    if (cur->cpoint.kind == 2) {
        return;
    }

    if ((obj->x_velocity <= 0.0 || obj->blocked_right != 1) &&
        (0.0 <= obj->x_velocity || obj->blocked_left != 1)) {
        obj->x_position += obj->x_velocity;
    }
    if (file->type == TYPE_THROW_WEAPON || file->id == ID_KNIFE_DAT) {
        obj->x_position += obj->x_velocity * 0.2;
    }
    if (file->id == ID_HOE_DAT) {
        obj->x_position -= obj->x_velocity * 0.2;
    }

    if ((obj->z_velocity <= 0.0 || obj->blocked_down != 1) &&
        (0.0 <= obj->z_velocity || obj->blocked_up != 1)) {
        obj->z_position += obj->z_velocity;
    }
    obj->blocked_down = 0;
    obj->blocked_up = 0;
    obj->blocked_left = 0;
    obj->blocked_right = 0;

    if (file->type == TYPE_ATTACK && (int32_t)cur->hit_j > 0) {
        obj->z_position += (double)((int32_t)cur->hit_j - 50);
    }

    if (obj->y >= 0) {
        if (0.0001 < obj->x_velocity) {
            double nv = obj->x_velocity - 1.0;
            obj->x_velocity = (nv < 0.0001) ? 0.0 : nv;
        }
        if (obj->x_velocity < -0.0001) {
            double nv = obj->x_velocity + 1.0;
            obj->x_velocity = (0.0001 < nv) ? 0.0 : nv;
        }
        if (0.0001 < obj->z_velocity) {
            double nv = obj->z_velocity - 1.0;
            obj->z_velocity = (nv < 0.0001) ? 0.0 : nv;
        }
        if (obj->z_velocity < -0.0001) {
            double nv = obj->z_velocity + 1.0;
            obj->z_velocity = (0.0001 < nv) ? 0.0 : nv;
        }
    }

    if ((file->type == TYPE_THROW_WEAPON || file->type == TYPE_DRINK) &&
        cur->state == 1000 &&
        (9.0 < obj->x_velocity || obj->x_velocity < -9.0)) {
        obj->frame_id1 = 40;
    }

    double new_y = obj->y_position + obj->y_velocity;
    obj->y_position = new_y;

    if (new_y < -0.0001) {
        uint32_t ftype = file->type;
        if (ftype != TYPE_ATTACK) {
            if (ftype == TYPE_DRINK) {
                obj->y_velocity += 1.1333333333333333;
            } else if (ftype == TYPE_THROW_WEAPON) {
                obj->y_velocity += 0.85;
            } else if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == 1002) {
                if (file->id == ID_BOOMERANG_DAT) {
                    obj->y_velocity += 0.16999999999999998;
                } else if (file->id == ID_KNIFE_DAT) {
                    obj->y_velocity += 0.425;
                } else if (file->id == ID_HOE_DAT) {
                    obj->y_velocity += 1.1333333333333333;
                } else {
                    obj->y_velocity += 0.5666666666666667;
                }
            } else {
                obj->y_velocity += 1.7;
            }
        }

        if (file->type == TYPE_CHARACTER && obj->frame_id1 < MAX_FRAMES) {
            int32_t fid = (int32_t)obj->frame_id1;
            if (file->frames[fid].state == STATE_FALLING) {
                if (fid < 185) {
                    if (obj->y_velocity >= -8.0) {
                        if (obj->y_velocity >= 1.0) {
                            obj->frame_id1 = (obj->y_velocity >= 8.0) ? 183 : 182;
                        } else {
                            obj->frame_id1 = 181;
                        }
                    } else {
                        obj->frame_id1 = 180;
                    }
                    if (obj->thrown_injury < 0) {
                        if (obj->y_velocity < 12.0 && DAT_00450bd0 > 5) {
                            obj->frame_id1 = 182;
                        } else {
                            obj->frame_id1 = 181;
                        }
                    }
                } else if (fid > 185 && fid < 191) {
                    if (obj->y_velocity >= -8.0) {
                        if (obj->y_velocity >= 1.0) {
                            obj->frame_id1 = (obj->y_velocity >= 8.0) ? 189 : 188;
                        } else {
                            obj->frame_id1 = 187;
                        }
                    } else {
                        obj->frame_id1 = 186;
                    }
                }
            }
            if (obj->frame_id1 < MAX_FRAMES &&
                file->frames[obj->frame_id1].state == STATE_BURNING &&
                obj->frame_id1 < 205 && obj->y_velocity > 1.0) {
                obj->frame_id1 = 205;
            }
        }
    } else if (obj->frame_id1 < MAX_FRAMES) {
        cur = &file->frames[obj->frame_id1];
        if (cur->cpoint.kind != 2) {
            uint32_t ftype = file->type;
            if (ftype == TYPE_CHARACTER) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity && cur->state == STATE_ICE) {
                    if (17.0 < obj->y_velocity || 9.0 < obj->x_velocity || obj->x_velocity < -9.0) {
                        if (obj->armor_multiplier == 0) {
                            obj->hp -= 10;
                        } else {
                            obj->hp += (int32_t)(-1000LL / (long long)obj->armor_multiplier);
                        }
                        obj->y_position = 0.0;
                        obj->y_velocity = -3.5;
                        if (7.0 < obj->x_velocity) obj->x_velocity = 7.0;
                        if (obj->x_velocity < -7.0) obj->x_velocity = -7.0;
                        obj->frame_id1 = 185;
                    } else {
                        obj->y_position = 0.0;
                        obj->y_velocity = 0.0;
                        obj->x_velocity /= 3.0;
                    }
                }

                bool crouch_land = false;
                uint32_t land_frame = obj->frame_id1;
                if (obj->y_position > 0.0 && obj->y_velocity == 0.0 && obj->frame_id1 == 212) {
                    land_frame = 212;
                    crouch_land = true;
                } else if (0.0001 < obj->y_position && 0.0001 < obj->y_velocity) {
                    uint32_t st = file->frames[obj->frame_id1].state;
                    if (st != STATE_FALLING && st != STATE_BURNING) {
                        land_frame = obj->frame_id1;
                        crouch_land = true;
                    }
                }

                if (crouch_land) {
                    obj->y_position = 0.0;
                    obj->y_velocity = 0.0;
                    obj->x_velocity /= 3.0;
                    uint32_t st = file->frames[land_frame].state;
                    if (st == 100) {
                        obj->frame_id1 = 94;
                    } else if (land_frame == 212 || st == STATE_ROWING) {
                        obj->frame_id1 = 215;
                    } else {
                        obj->frame_id1 = 219;
                    }
                    sync_wait_counter(obj, 0);
                } else if (0.0001 < obj->y_position && 0.0001 < obj->y_velocity &&
                           (file->frames[obj->frame_id1].state == STATE_FALLING ||
                            file->frames[obj->frame_id1].state == STATE_BURNING)) {
                    FUN_00417090(obj->x, 6);
                    int32_t dmg = obj->thrown_injury;
                    if (dmg != 0) {
                        if (dmg < 0) {
                            obj->thrown_injury = -dmg;
                            dmg = -dmg;
                        }
                        if (obj->armor_multiplier > 0) {
                            dmg = (dmg * 100) / obj->armor_multiplier;
                        }
                        obj->hp -= dmg;
                        obj->dark_hp -= dmg;
                        obj->thrown_injury = 0;
                    }
                    if (11.0 < obj->y_velocity || 9.0 < obj->x_velocity || obj->x_velocity < -9.0 ||
                        file->frames[obj->frame_id1].state == STATE_BURNING) {
                        obj->y_position = 0.0;
                        obj->y_velocity = -3.5;
                        if (7.0 < obj->x_velocity) obj->x_velocity = 7.0;
                        if (obj->x_velocity < -7.0) obj->x_velocity = -7.0;
                        if (obj->frame_id1 < 186 ||
                            file->frames[obj->frame_id1].state == STATE_BURNING) {
                            obj->frame_id1 = 185;
                        } else {
                            obj->frame_id1 = 191;
                        }
                    } else {
                        obj->y_position = 0.0;
                        obj->y_velocity = 0.0;
                        sync_wait_counter(obj, 0);
                        obj->frame_id1 = (obj->frame_id1 > 185) ? 231 : 230;
                        obj->x_velocity /= 3.0;
                    }
                }
            } else if (ftype == TYPE_LIGHT_WEAPON) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity) {
                    obj->y_position = 0.0;
                    obj->weapon_hp -= file->weapon_drop_hurt;
                    if (obj->y_velocity <= 9.9) {
                        obj->frame_id1 = (cur->state == 1002) ? 70 : 60;
                        obj->y_velocity = 0.0;
                        sync_wait_counter(obj, 0);
                        obj->x_velocity *= 0.5;
                    } else if (cur->state == 1002) {
                        obj->frame_id1 = 7;
                        obj->y_velocity = -8.0;
                        obj->facing = (uint8_t)(1 - obj->facing);
                        obj->x_velocity *= 0.5;
                        if (file->weapon_drop_sound_id > -1) {
                            FUN_00416fb0(obj->x, file->weapon_drop_sound_id);
                        }
                    } else {
                        obj->frame_id1 = 60;
                        obj->y_velocity = 0.0;
                        sync_wait_counter(obj, 0);
                        obj->x_velocity *= 0.5;
                    }
                }
            } else if (ftype == TYPE_THROW_WEAPON || ftype == TYPE_DRINK) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity) {
                    obj->weapon_hp -= file->weapon_drop_hurt;
                    if (file->type == TYPE_DRINK && obj->hp < 1) {
                        obj->weapon_hp = -1;
                    }
                    obj->y_position = 0.0;
                    if ((obj->y_velocity <= 8.5 && -10.0 <= obj->x_velocity && obj->x_velocity <= 10.0) ||
                        (cur->state != 1002 && cur->state != 1000)) {
                        obj->y_velocity = 0.0;
                        sync_wait_counter(obj, 0);
                        obj->x_velocity *= 0.7;
                        obj->frame_id1 = (cur->state == 1002) ? 70 : 60;
                    } else {
                        obj->frame_id1 = 0;
                        obj->y_velocity *= -0.7;
                        if (obj->y_velocity < -10.0) {
                            obj->y_velocity = -10.0;
                        }
                        obj->x_velocity *= 0.7;
                        if (file->weapon_drop_sound_id > -1) {
                            FUN_00416fb0(obj->x, file->weapon_drop_sound_id);
                        }
                    }
                }
            } else if (ftype == TYPE_HEAVY_WEAPON) {
                if (0.0001 < new_y) {
                    obj->weapon_hp -= 1;
                    obj->y_position = 0.0;
                    if (9.0 < obj->y_velocity) {
                        if (file->weapon_drop_sound_id > -1) {
                            FUN_00416fb0(obj->x, file->weapon_drop_sound_id);
                        }
                        obj->y_velocity = -5.0;
                        obj->facing = (uint8_t)(1 - obj->facing);
                        obj->x_velocity *= 0.5;
                    } else {
                        obj->weapon_hp -= file->weapon_drop_hurt;
                        if (obj->weapon_hp < 0) {
                            obj->weapon_hp = 0;
                        }
                        obj->frame_id1 = 20;
                        obj->y_velocity = 0.0;
                        sync_wait_counter(obj, 0);
                        obj->x_velocity *= 0.5;
                    }
                }
            } else if (file->id == ID_BROKEN_WEAPON_DAT && -0.0001 < new_y) {
                obj->y_position = 0.0;
                obj->frame_id1 = 101;
                obj->y_velocity = 0.0;
                sync_wait_counter(obj, 0);
                obj->x_velocity = 0.0;
            }
        }
    }

    obj->x = (int32_t)obj->x_position;
    obj->y = (int32_t)obj->y_position;
    obj->z = (int32_t)obj->z_position;
    if (obj->frame_id1 < MAX_FRAMES &&
        obj->file->frames[obj->frame_id1].state != STATE_FALLING) {
        obj->thrown_injury = 0;
    }
}

void FUN_0040e490(void)
{
    lf2_object_physics_tick((object_t *)in_ECX);
}

// 0x00413080: Master per-object input/state tick & combo dispatcher
void lf2_object_input_tick(object_t *obj)
{
    if (!obj || !obj->file || obj->frame_id1 >= MAX_FRAMES) return;

    if ((int8_t)obj->right_press > 0) obj->right_press--;
    if ((int8_t)obj->left_press > 0) obj->left_press--;
    if ((int8_t)obj->up_press > 0) obj->up_press--;
    if ((int8_t)obj->down_press > 0) obj->down_press--;
    if ((int8_t)obj->jump_press > 0) obj->jump_press--;
    if ((int8_t)obj->attack_press > 0) obj->attack_press--;
    if ((int8_t)obj->defend_press > 0) obj->defend_press--;
    if ((int8_t)obj->defend_lock > 0) obj->defend_lock--;

    if (obj->holding_right == 0 && obj->click_right == 1) {
        obj->right_press = 5;
        FUN_0040e450(6);
    }
    if (obj->holding_left == 0 && obj->click_left == 1) {
        obj->left_press = 5;
        FUN_0040e450(4);
    }
    if (obj->holding_up == 0 && obj->click_up == 1) {
        obj->up_press = 5;
        FUN_0040e450(8);
    }
    if (obj->holding_down == 0 && obj->click_down == 1) {
        obj->down_press = 5;
        FUN_0040e450(2);
    }
    if (obj->holding_defend == 0 && obj->click_defend == 1) {
        obj->defend_press = 5;
        FUN_0040e450(9);
    }
    if (obj->holding_jump == 0 && obj->click_jump == 1) {
        obj->jump_press = 5;
        FUN_0040e450(0);
    }
    if (obj->holding_attack == 0 && obj->click_attack == 1) {
        obj->attack_press = 5;
        FUN_0040e450(5);
    }

    void *prev_ecx = in_ECX;
    in_ECX = obj;

    FUN_00412800();
    FUN_004128f0();
    FUN_004129e0();
    FUN_00412ac0();
    FUN_00412ba0();
    FUN_00412c90();
    FUN_00412d80();
    FUN_00412e60();
    FUN_00412f40();

    file_t *file = obj->file;
    if (obj->frame_id1 < MAX_FRAMES) {
        const frame_t *cur = &file->frames[obj->frame_id1];
        if (cur->hit_a == 0 || (int8_t)obj->attack_press <= (int8_t)obj->defend_press ||
            (int8_t)obj->attack_press <= (int8_t)obj->jump_press) {
            if (cur->hit_d == 0 || (int8_t)obj->defend_press <= (int8_t)obj->attack_press ||
                (int8_t)obj->defend_press <= (int8_t)obj->jump_press) {
                if (cur->hit_j != 0 && (int8_t)obj->attack_press < (int8_t)obj->jump_press &&
                    (int8_t)obj->defend_press < (int8_t)obj->jump_press) {
                    FUN_0040e2d0((int32_t)cur->hit_j);
                    obj->jump_press = 0;
                }
            } else {
                FUN_0040e2d0((int32_t)cur->hit_d);
                obj->defend_press = 0;
            }
        } else {
            FUN_0040e2d0((int32_t)cur->hit_a);
            obj->attack_press = 0;
        }
    }

    if (obj->frame_id1 == 110) {
        if (obj->click_right == 1) obj->facing = FACING_RIGHT;
        if (obj->click_left == 1) obj->facing = FACING_LEFT;
    }

    if (obj->frame_id1 < MAX_FRAMES) {
        uint32_t st = file->frames[obj->frame_id1].state;
        if (st == 301 || st == STATE_FIRE) {
            if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
                obj->z_velocity = -file->running_speedz;
            }
            if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
                obj->z_velocity = file->running_speedz;
            }
        }
    }

    int32_t wtype = obj->weapon_type;
    if (wtype != TYPE_HEAVY_WEAPON && obj->frame_id1 < MAX_FRAMES &&
        (file->frames[obj->frame_id1].state == STATE_STANDING ||
         file->frames[obj->frame_id1].state == STATE_WALKING)) {
        if (obj->dash_counter > 0) obj->dash_counter--;
        if (obj->dash_counter < 0) obj->dash_counter++;

        int32_t wfr = (file->walking_frame_rate > 0) ? (int32_t)file->walking_frame_rate : 1;

        if (obj->click_right == 1 && obj->click_left == 0 && obj->y == 0) {
            if (obj->facing == FACING_LEFT) obj->dash_counter = 0;
            obj->facing = FACING_RIGHT;
            int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
            obj->move_counter = (uint32_t)mc;
            obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 5) : (11 - mc / wfr));
            obj->x_velocity = file->walking_speed;
            if (obj->holding_right == 0) obj->dash_counter += 10;
            if (obj->dash_counter > 10) {
                obj->frame_id1 = 9;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_right == 0 && obj->click_left == 1 && obj->y == 0) {
            if (obj->facing == FACING_RIGHT) obj->dash_counter = 0;
            obj->facing = FACING_LEFT;
            int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
            obj->move_counter = (uint32_t)mc;
            obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 5) : (11 - mc / wfr));
            obj->x_velocity = -file->walking_speed;
            if (obj->holding_left == 0) obj->dash_counter -= 10;
            if (obj->dash_counter < -10) {
                obj->frame_id1 = 9;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
                obj->move_counter = (uint32_t)mc;
                obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 5) : (11 - mc / wfr));
            }
            obj->z_velocity = -file->walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
                obj->move_counter = (uint32_t)mc;
                obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 5) : (11 - mc / wfr));
            }
            obj->z_velocity = file->walking_speedz;
            obj->x_velocity /= 1.4;
        }

        if (obj->click_attack == 1 && (int8_t)obj->attack_press > 0) {
            obj->dash_counter = 0;
            sync_wait_counter(obj, 0);
            if (wtype == 0) {
                if ((int8_t)obj->can_hit < 1) {
                    int32_t r = FUN_00417170(0x82, 2);
                    int32_t fid = (r + 12) * 5;
                    obj->frame_id1 = (uint32_t)fid;
                    if (DAT_0044d034 != 0) {
                        int32_t cost = file->frames[fid].mp;
                        obj->mp -= cost;
                        if (obj->mp < 0) {
                            obj->mp = 0;
                        } else {
                            obj->mp_used += cost;
                        }
                    }
                } else {
                    obj->frame_id1 = 70;
                }
            } else if (wtype % 100 == 1) {
                if (wtype == 101 &&
                    (obj->click_right != 0 || obj->click_left != 0 ||
                     obj->click_up != 0 || obj->click_down != 0)) {
                    obj->frame_id1 = 45;
                } else if (wtype == 101) {
                    obj->frame_id1 = (uint32_t)((FUN_00417170(0x83, 2) + 4) * 5);
                } else {
                    obj->frame_id1 = (uint32_t)((FUN_00417170(0x84, 2) + 4) * 5);
                }
            } else if (wtype == TYPE_THROW_WEAPON) {
                obj->frame_id1 = 45;
            } else if (wtype == TYPE_DRINK) {
                obj->frame_id1 = 55;
            }
        }
        if (obj->click_jump == 1 && (int8_t)obj->jump_press > 0) {
            sync_wait_counter(obj, 0);
            obj->dash_counter = 0;
            obj->frame_id1 = 210;
        }
        if (obj->click_defend == 1 && obj->defend_lock == 0 && (int8_t)obj->defend_press > 0) {
            obj->dash_counter = 0;
            sync_wait_counter(obj, 0);
            obj->frame_id1 = 110;
        }
    }

    wtype = obj->weapon_type;
    if (wtype == TYPE_HEAVY_WEAPON && obj->frame_id1 < MAX_FRAMES &&
        (file->frames[obj->frame_id1].state == STATE_STANDING ||
         file->frames[obj->frame_id1].state == STATE_WALKING)) {
        if (obj->dash_counter > 0) obj->dash_counter--;
        if (obj->dash_counter < 0) obj->dash_counter++;
        if (obj->frame_id1 < 12) obj->frame_id1 = 12;

        int32_t wfr = (file->walking_frame_rate > 0) ? (int32_t)file->walking_frame_rate : 1;

        if (obj->click_right == 1 && obj->click_left == 0 && obj->y == 0) {
            if (obj->facing == FACING_LEFT) obj->dash_counter = 0;
            obj->facing = FACING_RIGHT;
            int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
            obj->move_counter = (uint32_t)mc;
            obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 12) : (18 - mc / wfr));
            obj->x_velocity = file->heavy_walking_speed;
            if (obj->holding_right == 0) obj->dash_counter += 10;
            if (obj->dash_counter > 10) {
                obj->frame_id1 = 16;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_right == 0 && obj->click_left == 1 && obj->y == 0) {
            if (obj->facing == FACING_RIGHT) obj->dash_counter = 0;
            obj->facing = FACING_LEFT;
            int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
            obj->move_counter = (uint32_t)mc;
            obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 12) : (18 - mc / wfr));
            obj->x_velocity = -file->heavy_walking_speed;
            if (obj->holding_left == 0) obj->dash_counter -= 10;
            if (obj->dash_counter < -10) {
                obj->frame_id1 = 16;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
                obj->move_counter = (uint32_t)mc;
                obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 12) : (18 - mc / wfr));
            }
            obj->z_velocity = -file->heavy_walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                int32_t mc = ((int32_t)obj->move_counter + 1) % (wfr * 6);
                obj->move_counter = (uint32_t)mc;
                obj->frame_id1 = (uint32_t)((mc < wfr * 4) ? (mc / wfr + 12) : (18 - mc / wfr));
            }
            obj->z_velocity = file->heavy_walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_attack == 1 && (int8_t)obj->attack_press > 0) {
            obj->dash_counter = 0;
            sync_wait_counter(obj, 0);
            obj->frame_id1 = 50;
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_JUMPING && obj->y < 0) {
        if (obj->click_right == 1 && obj->click_left == 0) obj->facing = FACING_RIGHT;
        if (obj->click_left == 1 && obj->click_right == 0) obj->facing = FACING_LEFT;
        if (obj->click_attack != 0) {
            if (wtype == 0) {
                sync_wait_counter(obj, 0);
                obj->frame_id1 = 80;
                if (DAT_0044d034 != 0) {
                    int32_t cost = file->frames[80].mp;
                    obj->mp -= cost;
                    if (obj->mp < 0) {
                        obj->mp = 0;
                    } else {
                        obj->mp_used += cost;
                    }
                }
            } else if (wtype % 100 == 1) {
                sync_wait_counter(obj, 0);
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    wtype = obj->weapon_type;
                    obj->frame_id1 = 30;
                } else {
                    wtype = obj->weapon_type;
                    obj->frame_id1 = 52;
                }
            } else {
                wtype = obj->weapon_type;
                if (wtype == TYPE_THROW_WEAPON || wtype == TYPE_DRINK) {
                    obj->frame_id1 = 52;
                }
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_RUNNING && wtype != TYPE_HEAVY_WEAPON) {
        sync_wait_counter(obj, 0);
        int32_t rfr = (file->running_frame_rate > 0) ? (int32_t)file->running_frame_rate : 1;
        int32_t mc = ((int32_t)obj->move_counter + 1) % (rfr * 4);
        obj->move_counter = (uint32_t)mc;
        obj->frame_id1 = (uint32_t)((mc < rfr * 3) ? (mc / rfr + 9) : 10);

        if (obj->facing == FACING_RIGHT) {
            obj->x_velocity = file->running_speed;
            if (obj->click_left == 1) obj->frame_id1 = 218;
        }
        if (obj->facing == FACING_LEFT) {
            obj->x_velocity = -file->running_speed;
            if (obj->click_right == 1) obj->frame_id1 = 218;
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            obj->z_velocity = -file->running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_up == 0 && obj->click_down == 1 && obj->y == 0) {
            obj->z_velocity = file->running_speedz;
            obj->x_velocity /= 1.2;
        }

        if (obj->click_attack == 1 && (int8_t)obj->attack_press > 0) {
            if (wtype == 0) {
                if (DAT_0044d034 == 0) {
                    obj->frame_id1 = 85;
                } else if (file->frames[85].mp <= obj->mp) {
                    obj->mp -= file->frames[85].mp;
                    obj->mp_used += file->frames[85].mp;
                    obj->frame_id1 = 85;
                }
            } else if (wtype % 100 == 1) {
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    obj->frame_id1 = 35;
                } else {
                    obj->frame_id1 = 45;
                }
            } else if (obj->weapon_type == TYPE_THROW_WEAPON) {
                obj->frame_id1 = 45;
            } else if (obj->weapon_type == TYPE_DRINK) {
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    obj->frame_id1 = 55;
                } else {
                    obj->frame_id1 = 45;
                }
            }
        }
        if (obj->click_defend == 1 && (int8_t)obj->defend_press > 0) {
            obj->frame_id1 = 102;
        }
        if (obj->click_jump == 1 && (int8_t)obj->jump_press > 0) {
            FUN_00417090(obj->x, 7);
            obj->dash_counter = 0;
            obj->frame_id1 = 213;
            obj->x_velocity = (double)((int32_t)obj->facing * -2 + 1) * file->dash_distance;
            obj->y_velocity = file->dash_height;
            if (obj->click_up == 0) {
                if (obj->click_down != 0) {
                    obj->z_velocity = file->dash_distancez;
                }
            } else if (obj->click_down == 0) {
                obj->z_velocity = -file->dash_distancez;
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_RUNNING &&
        obj->weapon_type == TYPE_HEAVY_WEAPON) {
        sync_wait_counter(obj, 0);
        int32_t rfr = (file->running_frame_rate > 0) ? (int32_t)file->running_frame_rate : 1;
        int32_t mc = ((int32_t)obj->move_counter + 1) % (rfr * 4);
        obj->move_counter = (uint32_t)mc;
        obj->frame_id1 = (uint32_t)((mc < rfr * 3) ? (mc / rfr + 16) : 17);

        if (obj->facing == FACING_RIGHT) {
            obj->x_velocity = file->heavy_running_speed;
            if (obj->click_left == 1) obj->frame_id1 = 19;
        }
        if (obj->facing == FACING_LEFT) {
            obj->x_velocity = -file->heavy_running_speed;
            if (obj->click_right == 1) obj->frame_id1 = 19;
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            obj->z_velocity = -file->heavy_running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_up == 0 && obj->click_down == 1 && obj->y == 0) {
            obj->z_velocity = file->heavy_running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_attack == 1 && (int8_t)obj->attack_press > 0) {
            obj->frame_id1 = 50;
        }
    }

    if (obj->frame_id1 == 215) {
        if (obj->click_defend == 1 && (int8_t)obj->defend_press > 0) {
            obj->frame_id1 = 102;
        }
        if (obj->click_jump != 0) {
            if ((obj->click_right != 0 || 0.001 < obj->x_velocity) &&
                (int8_t)obj->jump_press > 0) {
                FUN_00417090(obj->x, 7);
                obj->frame_id1 = (uint32_t)obj->facing + 213;
                obj->dash_counter = 0;
                obj->x_velocity = file->dash_distance;
                obj->y_velocity = file->dash_height;
            }
            if (obj->click_jump != 0 &&
                (obj->click_left != 0 || obj->x_velocity < -0.001) &&
                (int8_t)obj->jump_press > 0) {
                FUN_00417090(obj->x, 7);
                obj->frame_id1 = 214U - (uint32_t)obj->facing;
                obj->dash_counter = 0;
                obj->x_velocity = -file->dash_distance;
                obj->y_velocity = file->dash_height;
            }
        }
        if (obj->click_up == 0) {
            if (obj->click_down != 0) {
                obj->z_velocity = file->dash_distancez;
            }
        } else if (obj->click_down == 0) {
            obj->z_velocity = -file->dash_distancez;
        }
    }

    if ((obj->frame_id1 == 182 || obj->frame_id1 == 188) &&
        obj->thrown_injury >= 0 && obj->click_jump == 1 &&
        (int8_t)obj->jump_press > 0 && obj->hp > 0) {
        if ((obj->facing == FACING_RIGHT && obj->x_velocity <= 0.0) ||
            (obj->facing == FACING_LEFT && obj->x_velocity >= 0.0)) {
            obj->frame_id1 = 100;
        } else {
            obj->frame_id1 = 108;
        }
        sync_wait_counter(obj, 0);
        if (file->rowing_height < obj->y_velocity) {
            obj->y_velocity = file->rowing_height;
        }
        if (1.0 <= obj->x_velocity || obj->x_velocity <= -1.0) {
            obj->x_velocity = (obj->x_velocity <= 0.0) ? -file->rowing_distance : file->rowing_distance;
        } else {
            obj->x_velocity = (obj->facing == FACING_LEFT) ? file->rowing_distance : -file->rowing_distance;
        }
    }

    if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == STATE_DASHING) {
        if (obj->click_right == 1 && obj->click_left == 0) {
            obj->facing = FACING_RIGHT;
        }
        if (obj->facing == FACING_RIGHT && obj->frame_id1 != 217 && obj->x_velocity < 0.0) {
            obj->frame_id1 = 214;
        }
        if (obj->facing == FACING_RIGHT && obj->frame_id1 != 216 && 0.0 < obj->x_velocity) {
            obj->frame_id1 = 213;
        }
        if (obj->click_left == 1 && obj->click_right == 0) {
            obj->facing = FACING_LEFT;
        }
        if (obj->facing == FACING_LEFT) {
            if (obj->frame_id1 != 217 && 0.0 < obj->x_velocity) {
                obj->frame_id1 = 214;
            }
            if (obj->frame_id1 != 216 && obj->x_velocity < 0.0) {
                obj->frame_id1 = 213;
            }
        }
        if (((0.0 < obj->x_velocity && obj->facing == FACING_RIGHT) ||
             (obj->x_velocity < 0.0 && obj->facing == FACING_LEFT)) &&
            obj->click_attack != 0) {
            int32_t wt = obj->weapon_type;
            if (wt == 0) {
                if (DAT_0044d034 == 0) {
                    obj->frame_id1 = 90;
                } else if (file->frames[90].mp <= obj->mp) {
                    obj->mp -= file->frames[90].mp;
                    obj->mp_used += file->frames[90].mp;
                    obj->frame_id1 = 90;
                }
            } else if ((wt % 100 == 1) ||
                       ((wt == TYPE_THROW_WEAPON || wt == TYPE_DRINK) &&
                        (obj->click_left != 0 || obj->click_right != 0 ||
                         obj->click_up != 0 || obj->click_down != 0))) {
                obj->frame_id1 = (wt == TYPE_THROW_WEAPON || wt == TYPE_DRINK) ? 52 : 40;
                sync_wait_counter(obj, 0);
                obj->y_velocity -= 1.0;
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES) {
        const frame_t *f = &file->frames[obj->frame_id1];
        if (f->dvx < 501) {
            if (f->dvx > 0 && obj->x_velocity < (double)f->dvx && obj->facing == FACING_RIGHT) {
                obj->x_velocity = (double)f->dvx;
            }
            if (f->dvx > 0 && -obj->x_velocity < (double)f->dvx && obj->facing == FACING_LEFT) {
                obj->x_velocity = -(double)f->dvx;
            }
            if (f->dvx < 0 && (double)f->dvx < obj->x_velocity && obj->facing == FACING_RIGHT) {
                obj->x_velocity = (double)f->dvx;
            }
            if (f->dvx < 0 && (double)f->dvx < -obj->x_velocity && obj->facing == FACING_LEFT) {
                obj->x_velocity = -(double)f->dvx;
            }
        } else {
            obj->x_velocity = (double)(f->dvx - 550);
        }

        if (f->dvy != 0) {
            obj->y_velocity = (f->dvy < 501) ? ((double)f->dvy + obj->y_velocity) : (double)(f->dvy - 550);
        }

        if (f->dvz != 0) {
            if (f->dvz > 500) {
                obj->z_velocity = (double)(f->dvz - 550);
                in_ECX = prev_ecx;
                return;
            }
            if (obj->click_up == 1 && (int8_t)obj->down_press <= (int8_t)obj->up_press) {
                obj->z_velocity = -(double)f->dvz;
            }
            if (obj->click_down == 1 && (int8_t)obj->up_press <= (int8_t)obj->down_press) {
                obj->z_velocity = (double)f->dvz;
            }
        }
    }

    in_ECX = prev_ecx;
}

void FUN_00413080(undefined4 param_1, undefined4 param_2)
{
    (void)param_1;
    (void)param_2;
    lf2_object_input_tick((object_t *)in_ECX);
}
