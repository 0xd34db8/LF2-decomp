#ifndef LEGACY_GLOBALS_H
#define LEGACY_GLOBALS_H

#include "legacy_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ECX register context for member functions
extern void *in_ECX;

// Synthetic SEH scope handlers and labels
extern undefined1 LAB_004462a8;
extern undefined1 LAB_00445d30;
extern void *ExceptionList;
#define LAB_0043b3d0 FUN_0043b3d0

// Global constants and data buffers
extern const char *DAT_00447744;
extern int   DAT_0044d02c;
extern int   DAT_0044d788;
extern void *DAT_0044d78c;
extern void *DAT_0044d790;
extern int   DAT_0044dce4;
extern uint  DAT_0044eea4;
extern int   DAT_0044eecc;
extern int   DAT_0044f620;
extern unsigned char DAT_0044ff90[3000];
extern int   DAT_00450bcc;
extern int   DAT_00450bd0;
extern void *DAT_00450be0[100];
extern int   DAT_00450bec;
extern int   DAT_00450c34;
extern int   DAT_00451b60;
extern int   DAT_00451b68;
extern char  DAT_00451d48[64];
extern int   DAT_00451dac;
extern int   DAT_00452948;
extern int   DAT_00453e0c;
extern HWND  DAT_004546f4;
extern char  DAT_00455378[256];
extern char  DAT_004553e8;
extern char  DAT_004553e9;
extern char  DAT_004553ea;
extern int   DAT_004554a4;
extern int   DAT_004554c0;
extern int   DAT_00455608;
extern int   DAT_00455634;
extern int   DAT_00455638;
extern int   DAT_00457578;
extern int   DAT_00457584;
extern uintptr_t DAT_00458348;
extern char  DAT_00458350[64];
extern void *DAT_00458420;
extern void *DAT_00458430;
extern int   DAT_00458438;
extern int   DAT_00458440;
extern void *DAT_00458580;
extern int   DAT_004589b4;
extern int   DAT_004589b8;
extern int   DAT_004589bc;
extern int   DAT_004589c0;
extern int   DAT_004589c8;
extern int   DAT_004593a0;
extern int   DAT_004593a4;

#ifdef __cplusplus
}
#endif

#endif // LEGACY_GLOBALS_H
