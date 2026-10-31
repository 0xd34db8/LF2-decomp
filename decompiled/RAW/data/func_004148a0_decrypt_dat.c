/* Decompiled from
 * - 0x004148a0: FUN_004148a0(param_1) - Decrypts param_1 into "data\\temporary.txt"
 * - 0x00414a30: FUN_00414a30(in_file, out_file) - Decrypts in_file into out_file
 * - 0x004146b0: FUN_004146b0(txt_file) - Encrypts txt_file into .dat file
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

static const char LF2_CIPHER_KEY[] = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
enum { LF2_KEY_LEN = 37, LF2_HEADER_LEN = 123 };

void lf2_decrypt_dat_to_temp(const char *dat_path)
{
    FILE *in = fopen(dat_path, "r");
    if (!in) return;
    FILE *out = fopen("data\\temporary.txt", "w");
    if (!out) {
        fclose(in);
        return;
    }

    int key_idx = 0;
    // Skip 123-byte header while stepping key index
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        int ch;
        if (fscanf(in, "%c", (char*)&ch) == EOF) break;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
    }

    // Decrypt payload
    int ch;
    while (fscanf(in, "%c", (char*)&ch) != EOF) {
        ch = ch - LF2_CIPHER_KEY[key_idx];
        if (ch < 0) ch += 256;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", ch);
    }

    fclose(in);
    fclose(out);
}

void lf2_decrypt_dat(const char *in_path, const char *out_path)
{
    FILE *in = fopen(in_path, "r");
    if (!in) return;
    FILE *out = fopen(out_path, "w");
    if (!out) {
        fclose(in);
        return;
    }

    int key_idx = 0;
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        int ch;
        if (fscanf(in, "%c", (char*)&ch) == EOF) break;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
    }

    int ch;
    while (fscanf(in, "%c", (char*)&ch) != EOF) {
        ch = ch - LF2_CIPHER_KEY[key_idx];
        if (ch < 0) ch += 256;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", ch);
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

    int key_idx = 0;
    // Write 123 dummy header bytes
    for (int i = 0; i < LF2_HEADER_LEN; ++i) {
        fprintf(out, "%c", ' ');
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
    }

    int ch;
    while (fscanf(in, "%c", (char*)&ch) != EOF) {
        int enc = (ch + LF2_CIPHER_KEY[key_idx]) % 256;
        key_idx = (key_idx + 1) % LF2_KEY_LEN;
        fprintf(out, "%c", enc);
    }

    fclose(in);
    fclose(out);
}

