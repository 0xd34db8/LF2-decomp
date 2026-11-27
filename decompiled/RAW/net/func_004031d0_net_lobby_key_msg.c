/* Function: FUN_004031d0 */
/* Address: 0x004031d0 */

void FUN_004031d0(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  
  if (param_1 == 0x20) {
    *(undefined1 *)(in_ECX[0x4c] + 4 + (int)in_ECX) = 0x20;
  }
  else if (param_1 == 0xbe) {
    *(undefined1 *)(in_ECX[0x4c] + 4 + (int)in_ECX) = 0x2e;
  }
  else {
    if ((0x17 < param_1 - 0x42U) && (9 < param_1 - 0x30U)) {
      if (param_1 == 8) {
        iVar1 = in_ECX[0x4c];
        if (0 < iVar1) {
          in_ECX[0x4c] = iVar1 + -1;
          *(undefined1 *)(iVar1 + 3 + (int)in_ECX) = 0;
          return;
        }
      }
      else if (param_1 == 0xd) {
        *in_ECX = 0;
      }
      return;
    }
    *(char *)(in_ECX[0x4c] + 4 + (int)in_ECX) = (char)param_1;
  }
  in_ECX[0x4d] = in_ECX[0x4d] + 1;
  in_ECX[0x4c] = in_ECX[0x4c] + 1;
  *(undefined1 *)(in_ECX[0x4c] + 4 + (int)in_ECX) = 0;
  return;
}

