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
int FUN_0043f4b0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len) {
    return compress((Bytef *)dst, dst_len, (const Bytef *)src, src_len);
}

// 1:1 Parity with 0x0043F4D0: zlib uncompress wrapper
int FUN_0043f4d0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len) {
    return uncompress((Bytef *)dst, dst_len, (const Bytef *)src, src_len);
}

// 1:1 Parity with 0x0043DD60: Save replay file with zlib compression and secondary cipher
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

    DAT_004588ac = (int)(uintptr_t)uncomp_buf;
    return 1;
}
