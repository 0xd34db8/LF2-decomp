#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

// Ghidra decompiler output for func_004034e0 (abs)
// Address: 0x004034e0

int FUN_004034e0(int param_1)

{
  if (param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}

