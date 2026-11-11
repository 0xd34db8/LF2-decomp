#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x004196F0: FUN_004196f0 (Velocity / impulse averaging pass across all 400 active objects)
 *   0x004197A0: FUN_004197a0 (Remote / network input bits unpacking & flag latching)
 *   0x004198F0: FUN_004198f0 (Local player input bits latching & replay recording)
 *   0x00419A60: FUN_00419a60 (Master per-slot controller / AI input dispatch & loop)
 */

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
                    param_1[param_3] = b;
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
                        int32_t key_offset = slot_type * 0x50 / sizeof(int);
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
                            }
                        }
                    }
                }
            }
            if (out_packed) out_packed++;
        }
    }

    // AI dispatch for world objects 10..399
    for (int32_t i = 10; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) continue;
        object_t *obj = global->objects[i];
        if (!obj || !obj->file) continue;

        if (obj->file->type == TYPE_CHARACTER) {
            FUN_004094b0(i, param_2);
        } else if (obj->file->frames[obj->frame_id1].state > 0) {
            FUN_00406ba0(i);
        }
    }
}

