#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* Decompiled from:
 * - 0x004146b0: FUN_004146b0(txt_file) - Encrypts txt_file into .dat file with 123-byte obfuscated header
 * - 0x004148a0: FUN_004148a0(param_1) - Decrypts param_1 into "data\\temporary.txt"
 * - 0x00414a30: FUN_00414a30(in_file, out_file) - Decrypts in_file into out_file
 */

static const char LF2_CIPHER_KEY[] = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
enum { LF2_KEY_LEN = 37, LF2_HEADER_LEN = 123 };

void FUN_004148a0(const char *param_1)
{
    FILE *in = fopen(param_1, "r");
    if (!in) return;
    FILE *out = fopen("data\\temporary.txt", "w");
    if (!out) {
        fclose(in);
        return;
    }

    uint32_t key_idx = 0;
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        char dummy;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fscanf(in, "%c", &dummy);
    }

    int ch = 0;
    fscanf(in, "%c", (char *)&ch);
    while (!feof(in)) {
        ch = (ch & 0xFF) - (unsigned char)LF2_CIPHER_KEY[key_idx];
        if (ch < 0) {
            ch += 0x100;
        }
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", ch);
        ch = 0;
        fscanf(in, "%c", (char *)&ch);
    }

    fclose(in);
    fclose(out);
}

void FUN_00414a30(const char *in_path, const char *out_path)
{
    FILE *in = fopen(in_path, "r");
    if (!in) return;
    FILE *out = fopen(out_path, "w");
    if (!out) {
        fclose(in);
        return;
    }

    uint32_t key_idx = 0;
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        char dummy;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fscanf(in, "%c", &dummy);
    }

    int ch = 0;
    fscanf(in, "%c", (char *)&ch);
    while (!feof(in)) {
        ch = (ch & 0xFF) - (unsigned char)LF2_CIPHER_KEY[key_idx];
        if (ch < 0) {
            ch += 0x100;
        }
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", ch);
        ch = 0;
        fscanf(in, "%c", (char *)&ch);
    }

    fclose(in);
    fclose(out);
}

void lf2_encrypt_txt(const char *txt_path, const char *dat_path)
{
    FILE *in = fopen(txt_path, "r");
    if (!in) return;
    FILE *out = fopen(dat_path, "w");
    if (!out) {
        fclose(in);
        return;
    }

    uint32_t key_idx = 0;
    /* 0x004146b0: Write 123 obfuscated header bytes while stepping key_idx (123 % 37 == 12) */
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        char hdr_byte = (char)((rand() % 0x19) + 'A' + LF2_CIPHER_KEY[key_idx]);
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", hdr_byte);
    }

    int ch = 0;
    fscanf(in, "%c", (char *)&ch);
    while (!feof(in)) {
        char enc = (char)((ch & 0xFF) + (unsigned char)LF2_CIPHER_KEY[key_idx]);
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", enc);
        ch = 0;
        fscanf(in, "%c", (char *)&ch);
    }

    fclose(in);
    fclose(out);
}

void FUN_004146b0(const char *txt_path)
{
    char dat_path[260];
    strncpy(dat_path, txt_path, sizeof(dat_path) - 1);
    dat_path[sizeof(dat_path) - 1] = '\0';
    size_t len = strlen(dat_path);
    if (len >= 4) {
        strcpy(dat_path + len - 4, ".dat");
    }
    lf2_encrypt_txt(txt_path, dat_path);
}

void lf2_decrypt_dat_to_temp(const char *dat_path)
{
    FUN_004148a0(dat_path);
}

void lf2_decrypt_dat(const char *in_path, const char *out_path)
{
    FUN_00414a30(in_path, out_path);
}


