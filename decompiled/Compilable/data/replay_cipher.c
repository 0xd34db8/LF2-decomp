#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <zlib.h>
#include "legacy_globals.h"
#include "legacy_signatures.h"

// Authentic LF2 v2.0 Secondary Obfuscation Cipher Key (0x0044D7A0)
// Exactly 1,345 characters in the .data section of lf2.exe (SHA256: a1e3e58e52cb7091bff6e1ea7ed8e14274b882f51134af69ca4ce0a72cc8613b)
const char DAT_0044d7a0[1346] =
    "1545661123545613454563115345689405689745604785048986746544565456136456245431"
    "2533445678979896784059687456091782394756456465544556446655457455664756448745"
    "2745645562344562436545143854546475674965478568456745653456544839758943486789"
    "4576845120873105456014566402435664056405766456778981904859018359719402875091"
    "2712309585959025903485028490134472190217021375815872018620461270456072816578"
    "6150742721078651876510768150401865107486150745189750163541864518675018675018"
    "6745018674745604785048986746544565456136456245431253344567897989678405968745"
    "6091782393095859590259034850284901344721902170213758158720186204612704560728"
    "1657861507427210786518762436545143854546475674965478568456745653456544839758"
    "9434867894576846134545631153456894056897456047850489867465445654561364562454"
    "3125334456789798967840596874560917823947564564655445564466554574556647564487"
    "4527456455623445624365451438545464756749654785684567456534565448397589434867"
    "8945768451208731054560145664024356640564057664567789819048590183597194028750"
    "9127123095859590259034850284901344721902170213758158720186204612704560728165"
    "7861507427210786518765107681504018651074861507451897501635418645186750186750"
    "1867450186747456047850489867465445654561364562454312533445678979896784059687"
    "4560917823930958595902590348502849013447219021702137581587201862046127045607"
    "28165786150742721078651876243654514385454647567496547";

// Global recording and playback buffers
void *DAT_004588a8 = NULL;

// 1:1 Parity with 0x0043DD60 secondary obfuscation cipher encryption
void lf2_replay_cipher_encrypt(uint8_t *buffer, size_t size) {
    if (!buffer || size == 0) return;
    size_t key_len = sizeof(DAT_0044d7a0) - 1; // 1345 bytes
    size_t n = (size < key_len) ? size : key_len;
    for (size_t i = 0; i < n; ++i) {
        buffer[i] = (uint8_t)(buffer[i] + (uint8_t)DAT_0044d7a0[i] - 0x30);
    }
}

// 1:1 Parity with 0x0043E620 secondary obfuscation cipher decryption
void lf2_replay_cipher_decrypt(uint8_t *buffer, size_t size) {
    if (!buffer || size == 0) return;
    size_t key_len = sizeof(DAT_0044d7a0) - 1; // 1345 bytes
    size_t n = (size < key_len) ? size : key_len;
    for (size_t i = 0; i < n; ++i) {
        buffer[i] = (uint8_t)(buffer[i] - (uint8_t)DAT_0044d7a0[i] + 0x30);
    }
}

// 1:1 Parity with 0x0043F4B0: zlib compress wrapper
// LIBRARY: LF2 0x0043f4b0
int FUN_0043f4b0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len) {
    return compress((Bytef *)dst, dst_len, (const Bytef *)src, src_len);
}

// 1:1 Parity with 0x0043F4D0: zlib uncompress wrapper
// LIBRARY: LF2 0x0043f4d0
int FUN_0043f4d0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len) {
    return uncompress((Bytef *)dst, dst_len, (const Bytef *)src, src_len);
}

// 1:1 Parity with 0x0043DD60: Save replay file with zlib compression and secondary cipher
// FUNCTION: LF2 0x0043dd60
void FUN_0043dd60(void) {
    if (!DAT_004588a8) return;

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "recording\\%s", DAT_0044fd98);

    unsigned long max_comp_len = 0x631200; // 6,492,672 bytes
    uint8_t *comp_buf = (uint8_t *)calloc(1, max_comp_len);
    if (!comp_buf) return;

    unsigned long comp_len = max_comp_len;
    // Uncompressed recording buffer size is 0x630E18 (6,491,672 bytes)
    int ret = FUN_0043f4b0(comp_buf, &comp_len, DAT_004588a8, 0x630e18);
    if (ret != Z_OK) {
        free(comp_buf);
        return;
    }

    // Apply secondary obfuscation cipher
    lf2_replay_cipher_encrypt(comp_buf, comp_len);

    // Write to file: 4-byte compressed size followed by encrypted stream
    FILE *fp = fopen(filepath, "wb");
    if (fp) {
        uint32_t sz = (uint32_t)comp_len;
        fwrite(&sz, 1, 4, fp);
        fwrite(comp_buf, 1, comp_len, fp);
        fclose(fp);
    }

    free(comp_buf);
    free(DAT_004588a8);
    DAT_004588a8 = NULL;
}

// 1:1 Parity with 0x0043E620: Load replay file with secondary decipher and zlib decompression
// FUNCTION: LF2 0x0043e620
int FUN_0043e620(char *param_1) {
    DAT_0044d030 = 1;
    DAT_00450b74 = 0;

    FILE *fp = fopen(param_1, "rb");
    if (!fp) {
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (file_size < 1000) {
        fclose(fp);
        return 0;
    }

    uint32_t comp_size = 0;
    if (fread(&comp_size, 1, 4, fp) != 4) {
        fclose(fp);
        return 0;
    }

    uint8_t *comp_buf = (uint8_t *)calloc(1, comp_size);
    if (!comp_buf) {
        fclose(fp);
        return 0;
    }

    if (fread(comp_buf, 1, comp_size, fp) != comp_size) {
        free(comp_buf);
        fclose(fp);
        return 0;
    }
    fclose(fp);

    // Apply secondary de-obfuscation cipher
    lf2_replay_cipher_decrypt(comp_buf, comp_size);

    // Allocate uncompressed playback buffer (0x630E18)
    uint8_t *uncomp_buf = (uint8_t *)calloc(1, 0x630e18);
    if (!uncomp_buf) {
        free(comp_buf);
        return 0;
    }

    unsigned long uncomp_len = 0x631200;
    int ret = FUN_0043f4d0(uncomp_buf, &uncomp_len, comp_buf, comp_size);
    free(comp_buf);

    if (ret != Z_OK || uncomp_len != 0x630e18) {
        free(uncomp_buf);
        return 0;
    }

    DAT_004588ac = (intptr_t)(uintptr_t)uncomp_buf;
    return 1;
}

// 1:1 Parity with 0x0043D280: Free single heap buffer pointer slot
// FUNCTION: LF2 0x0043d280
void FUN_0043d280(void *ptr_slot) {
    if (!ptr_slot) return;
    void **slot = (void **)ptr_slot;
    if (*slot != NULL) {
        free(*slot);
        *slot = NULL;
    }
}

// 1:1 Parity with 0x0043D2A0: Free recording (DAT_004588a8) and playback (DAT_004588ac) buffers
// FUNCTION: LF2 0x0043d2a0
void FUN_0043d2a0(void) {
    FUN_0043d280(&DAT_004588a8);
    FUN_0043d280(&DAT_004588ac);
}

// 1:1 Parity with 0x0043DB40: Write 10-byte per-frame input record into recording buffer
// FUNCTION: LF2 0x0043db40
void FUN_0043db40(const uint8_t *param_1) {
    if (!DAT_004588a8 || !param_1) return;
    uint8_t *dst = (uint8_t *)DAT_004588a8 + 0x2b38 + (size_t)DAT_00450b8c * 10;
    for (int i = 0; i < 10; ++i) {
        dst[i] = param_1[i];
    }
}

// 1:1 Parity with 0x0043DC50: Read 10-byte per-frame input record from playback buffer
// FUNCTION: LF2 0x0043dc50
void FUN_0043dc50(uint8_t *param_1) {
    if (!DAT_004588ac || !param_1) return;
    const uint8_t *src = (const uint8_t *)(uintptr_t)DAT_004588ac + 0x2b38 + (size_t)DAT_00450b8c * 10;
    for (int i = 0; i < 10; ++i) {
        param_1[i] = src[i];
    }
}

// 1:1 Parity with 0x0043DF00: Restore difficulty, 8 player names, and 3 profile strings after replay
// FUNCTION: LF2 0x0043df00
void FUN_0043df00(void) {
    DAT_00450c30 = DAT_0045877c;
    for (int offset = 0; offset < 0x58; offset += 0x0b) {
        const char *src = DAT_00458850 + offset;
        char *dst = DAT_0044fcc0 + offset;
        int k = 0;
        do {
            dst[k] = src[k];
        } while (src[k++] != '\0' && (offset + k) < 0x58);
    }
    for (int i = 0; i < 100; ++i) {
        DAT_0044fd18[i] = DAT_004587e8[i];
        if (DAT_004587e8[i] == '\0') break;
    }
    for (int i = 0; i < 400; ++i) {
        DAT_0044f900[i] = DAT_00458588[i];
        if (DAT_00458588[i] == '\0') break;
    }
    for (int i = 0; i < 100; ++i) {
        DAT_0044f890[i] = DAT_00458780[i];
        if (DAT_00458780[i] == '\0') break;
    }
}

// 1:1 Parity with 0x0043DFA0: Unpack replay header, config backups, 18 slots, PRNG table & random fighters
// FUNCTION: LF2 0x0043dfa0
void FUN_0043dfa0(int *param_1, char *param_2, void *param_3, void *param_4) {
    if (!DAT_004588ac || !param_1 || !param_2 || !param_3) return;

    uint8_t *buf = (uint8_t *)(uintptr_t)DAT_004588ac;
    int32_t *u32 = (int32_t *)buf;
    object_t **objects = (object_t **)param_3;
    file_t **files = (file_t **)param_4;

    DAT_0045877c = DAT_00450c30;
    DAT_00450b8c = 0;
    DAT_00450b84 = 1;
    DAT_00450b88 = 1;
    DAT_00450c30 = u32[0];
    *(int32_t *)(buf + 0x630bb8) = DAT_00458428;
    *(int32_t *)(buf + 0x630bbc) = DAT_0045842c;
    DAT_00458428 = u32[2];
    DAT_0045842c = u32[3];
    DAT_00450b94 = u32[1];
    *param_1 = u32[0x52];

    // Backup & apply 8 player names (+0x14C = 0x53*4)
    for (int offset = 0; offset < 0x58; offset += 0x0b) {
        const char *cur = DAT_0044fcc0 + offset;
        char *bak = DAT_00458850 + offset;
        int k = 0;
        do {
            bak[k] = cur[k];
        } while (cur[k++] != '\0' && (offset + k) < 0x58);

        const char *rep_name = (const char *)(buf + 0x14c + offset);
        char *dst_name = DAT_0044fcc0 + offset;
        k = 0;
        do {
            dst_name[k] = rep_name[k];
        } while (rep_name[k++] != '\0' && (offset + k) < 0x58);
    }

    // Backup & apply 3 profile strings (+0x630BC0, +0x630C24, +0x630DB4)
    for (int i = 0; i < 100; ++i) {
        DAT_004587e8[i] = DAT_0044fd18[i];
        if (DAT_0044fd18[i] == '\0') break;
    }
    for (int i = 0; i < 100; ++i) {
        DAT_0044fd18[i] = (char)buf[0x630bc0 + i];
        if (buf[0x630bc0 + i] == '\0') break;
    }
    for (int i = 0; i < 400; ++i) {
        DAT_00458588[i] = DAT_0044f900[i];
        if (DAT_0044f900[i] == '\0') break;
    }
    for (int i = 0; i < 400; ++i) {
        DAT_0044f900[i] = (char)buf[0x630c24 + i];
        if (buf[0x630c24 + i] == '\0') break;
    }
    buf[0x630e17] = '\0';
    for (int i = 0; i < 100; ++i) {
        DAT_00458780[i] = DAT_0044f890[i];
        if (DAT_0044f890[i] == '\0') break;
    }
    for (int i = 0; i < 100; ++i) {
        DAT_0044f890[i] = (char)buf[0x630db4 + i];
        if (buf[0x630db4 + i] == '\0') break;
    }

    DAT_0044d024 = u32[0x69];
    memset(param_2, 0, MAX_OBJECTS);

    // Restore initial 18 object slots (+0x1A8..+0x54F)
    for (int slot = 0; slot < 18; ++slot) {
        size_t base_off = 0x238 + (size_t)slot * 4;
        int exists = *(int32_t *)(buf + base_off);
        if (exists != 0 && objects[slot] != NULL) {
            int32_t target_id = *(int32_t *)(buf + base_off - 0x48);
            file_t *matched = NULL;
            if (files != NULL) {
                for (int f = 0; f < MAX_FILES; ++f) {
                    if (files[f] != NULL && (int32_t)files[f]->id == target_id) {
                        matched = files[f];
                        break;
                    }
                }
            }
            if (matched != NULL) {
                object_t *obj = objects[slot];
                lf2_object_init(obj);
                obj->file = matched;
                obj->x_position = 350.0;
                obj->weapon_hp = matched->weapon_hp;
                obj->y_position = 0.0;
                obj->z_position = 300.0;
            }
            object_t *obj = objects[slot];
            obj->team = *(int32_t *)(buf + base_off - 0x90);
            param_2[slot] = (char)exists;
            obj->blink_time = *(int32_t *)(buf + base_off + 0x48);
            obj->x = *(int32_t *)(buf + base_off + 0x90);
            obj->y = *(int32_t *)(buf + base_off + 0xd8);
            obj->z = *(int32_t *)(buf + base_off + 0x120);
            obj->x_position = (double)obj->x;
            obj->z_position = (double)obj->z;
            obj->mp = *(int32_t *)(buf + base_off + 0x168);
            obj->owner = *(int32_t *)(buf + base_off + 0x1b0);
            obj->max_hp = *(int32_t *)(buf + base_off + 0x1f8);
            obj->dark_hp = obj->max_hp;
            obj->hp = obj->dark_hp;
            obj->transformed_to_id = *(int32_t *)(buf + base_off + 0x240);
            obj->player_index = *(int32_t *)(buf + base_off + 0x288);
            obj->armor_multiplier = *(int32_t *)(buf + base_off + 0x2d0);
        }
    }

    DAT_00450c24 = 0;
    DAT_00450c20 = 0;
    DAT_00450c1c = 0;
    DAT_00450c18 = 0;
    DAT_00450c14 = 0;
    DAT_00450c10 = 0;
    DAT_00450c0c = 0;
    DAT_00450c08 = 0;
    DAT_00450c04 = 0;
    DAT_00450c28 = 0;

    // BGM string at +0x550 (0x154 * 4)
    for (int i = 0; i < 260; ++i) {
        DAT_0044eed0[i] = (char)buf[0x550 + i];
        if (buf[0x550 + i] == '\0') break;
    }

    // Battle troop tables
    int *d5f8 = &DAT_0044d5f8;
    int *d650 = &DAT_0044d650;
    int *d6a8 = &DAT_0044d6a8;
    int *d700 = &DAT_0044d700;
    for (int k = 0; k < 20; ++k) {
        d5f8[k] = u32[0x1d3 + k];
        d650[k] = u32[0x1e9 + k];
        d6a8[k] = u32[0x1ff + k];
        d700[k] = u32[0x215 + k];
    }

    // PRNG index (+0x8C4 = 0x231*4) & 3000-byte table (+0x8C8)
    DAT_00450bcc = u32[0x231];
    memcpy(DAT_0044ff90, buf + 0x8c8, 3000);

    // Stage random fighters (+0x1488..+0x14B4)
    int *d324 = &DAT_0044d324;
    for (int k = 0; k < 10; ++k) {
        d324[k] = u32[0x522 + k];
    }
    DAT_0044d34c = u32[0x52c];
    DAT_00450b90 = u32[0x52d];

    DAT_0044d034 = 1;
    DAT_00450bbc = 0;
    DAT_00450bb0 = 0;
    DAT_00450bb4 = 0;
    if (*param_1 == 1) {
        DAT_00450b9c = 0x46;
        DAT_00450ba8 = 0;
        DAT_00450bac = 0;
        DAT_00450ba4 = 0;
        DAT_0044fb6c = 0xffffffff;
        DAT_0044f880 = 0xffffffff;
        DAT_00450bc8 = 0;
        DAT_00450bc4 = 0;
    }
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (param_2[i] == '\0' && objects[i] != NULL) {
            lf2_object_init(objects[i]);
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (param_2[i + 10] == '\0' && param_2[i] == '\0' && objects[i] && objects[i + 10]) {
            objects[i]->team = objects[i + 10]->team;
        }
    }
    DAT_00450c34 = 0;
    DAT_00450bd0 = 0;
    DAT_00450bd4 = 0;
    DAT_00450bd8 = 0;
}
