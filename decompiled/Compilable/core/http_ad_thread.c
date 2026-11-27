#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>

/*
 * Virtual Addresses:
 *   - 0x0043C0C0: http_download (FUN_0043c0c0)
 *   - 0x0043C240: ad_thread_proc (FUN_0043c240)
 *   - 0x0043C450: ad_thread_start (FUN_0043c450)
 * Class / Subsystem: Core / WinINet HTTP Client & Background Ad Loader
 */

// FUNCTION: LF2 0x0043c0c0
int FUN_0043c0c0(const char *primary_url, const char *fallback_url, const char *out_filepath)
{
#ifdef _WIN32
    HINTERNET hInternet = InternetOpenA("Sample", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hInternet == NULL || primary_url == NULL) {
        if (hInternet != NULL) {
            InternetCloseHandle(hInternet);
        }
        return 0;
    }

    HINTERNET hUrl = InternetOpenUrlA(hInternet, primary_url, NULL, 0, 0, 0);
    if (hUrl == NULL) {
        if (fallback_url == NULL) {
            InternetCloseHandle(hInternet);
            return 0;
        }
        (void)GetLastError();
        hUrl = InternetOpenUrlA(hInternet, fallback_url, NULL, 0, 0, 0);
        if (hUrl == NULL) {
            InternetCloseHandle(hInternet);
            return 0;
        }
    }

    int wrote_any = 0;
    HANDLE hFile = CreateFileA(out_filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) {
        uint8_t buf[1024];
        DWORD bytes_read = 0;
        BOOL read_ok = InternetReadFile(hUrl, buf, sizeof(buf), &bytes_read);
        while (read_ok == TRUE && bytes_read != 0) {
            DWORD bytes_written = 0;
            if (WriteFile(hFile, buf, bytes_read, &bytes_written, NULL) != 0) {
                wrote_any = 1;
            }
            read_ok = InternetReadFile(hUrl, buf, sizeof(buf), &bytes_read);
        }
        CloseHandle(hFile);
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return (wrote_any != 0) ? 1 : 0;
#else
    (void)primary_url;
    (void)fallback_url;
    (void)out_filepath;
    return 0;
#endif
}

// FUNCTION: LF2 0x0043c240
#ifdef _WIN32
DWORD WINAPI FUN_0043c240(LPVOID lpParameter)
#else
unsigned long FUN_0043c240(void *lpParameter)
#endif
{
    (void)lpParameter;
#ifdef _WIN32
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    DAT_00458424 = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);

    char txt_path[128];
    sprintf(txt_path, "data\\ad%d.txt", 1 - DAT_0044d784);
    int ok = FUN_0043c0c0(
        "http://www.littlefighter.com/_ad/ad.php",
        "http://www.lf2.net/_ad/ad.php",
        txt_path);
    if (ok == 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
        DAT_00458424 = 0;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
        return 0;
    }

    int parse_fail = 0;
    char line[500];
    line[0] = '\0';
    FILE *fp = fopen(txt_path, "r");
    if (fp == NULL) {
        parse_fail = 1;
    } else {
        if (fgets(line, sizeof(line), fp) == NULL) {
            line[0] = '\0';
        }
        fclose(fp);
    }

    if (line[0] != '\0') {
        int days = -99;
        char ad_tag[100];
        ad_tag[0] = '\0';
        sscanf(line, "%d %d %99s", &DAT_0044d77c, &days, ad_tag);
        if (days != -99 && ad_tag[0] != '\0' && DAT_0044d77c != -99) {
            DAT_0044d788 = days;
            if (DAT_0044d778 < DAT_0044d77c) {
                char url1[256];
                char url2[256];
                char bmp_path[128];
                sprintf(url1, "http://www.littlefighter.com/_ad/ad%s.bmp", ad_tag);
                sprintf(url2, "http://www.lf2.net/_ad/ad%s.bmp", ad_tag);
                sprintf(bmp_path, "sprite\\sys\\ad%d.bmp", 1 - DAT_0044d784);
                if (FUN_0043c0c0(url1, url2, bmp_path) == 0) {
                    return 0;
                }
            }
            if (parse_fail != 1) {
                EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
                DAT_00458424 = 2;
                LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
                return 0;
            }
        }
    }

    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    DAT_00458424 = 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    return 0;
#else
    return 0;
#endif
}

// FUNCTION: LF2 0x0043c450
void FUN_0043c450(void)
{
#ifdef _WIN32
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    int state = DAT_00458424;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);

    if (state == 0) {
        DWORD thread_id = 0;
        HANDLE hThread = CreateThread(NULL, 0, FUN_0043c240, NULL, 0, &thread_id);
        if (hThread == NULL) {
            (void)GetLastError();
        }
    }
#endif
}
