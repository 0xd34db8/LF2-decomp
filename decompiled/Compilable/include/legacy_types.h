#ifndef LEGACY_TYPES_H
#define LEGACY_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <winsock.h>
#include <commdlg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Win32 tagMSG compatibility
typedef MSG tagMSG;
typedef struct tagOFNA tagOFNA;
typedef SYSTEMTIME _SYSTEMTIME;

// Time structure compatibility
typedef struct tm tm;

// Ghidra decompiler synthetic primitive types
typedef uint8_t   undefined1;
typedef uint16_t  undefined2;
typedef uint32_t  undefined4;
typedef uint64_t  undefined8;
typedef uint8_t   byte;
typedef uint8_t   uchar;
typedef uint16_t  ushort;
typedef uint32_t  uint;
typedef uint32_t  ulong;
typedef int64_t   longlong;
typedef uint64_t  ulonglong;
typedef double    float10; // x87 80-bit float represented as 64-bit IEEE double

// Ghidra decompiler synthetic macros
#undef NAN
#define NAN(x) isnan(x)
#define SBORROW4(a, b) ((int32_t)(a) < (int32_t)(b))
#define CARRY4(a, b) ((uint32_t)(a) + (uint32_t)(b) < (uint32_t)(a))
#define operator_new(sz) malloc(sz)
#define __security_check_cookie(x) ((void)0)

// Ghidra generic function pointer type
typedef void (*code)();

// Builtin intrinsics
#define builtin_strncpy strncpy
#define builtin_memcpy memcpy

typedef union {
    char _0_1_;
    char str[4];
    int val;
} dat_0044d320_t;

// Calling convention bridge
#if defined(__GNUC__) && defined(__i386__)
#define THISCALL __attribute__((thiscall))
#elif defined(_MSC_VER)
#define THISCALL __thiscall
#else
#define THISCALL
#endif

#ifdef __cplusplus
}
#endif

#endif // LEGACY_TYPES_H
