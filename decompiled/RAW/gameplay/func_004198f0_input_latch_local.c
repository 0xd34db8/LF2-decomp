/* Function: FUN_004198f0 */
/* Address: 0x004198f0 */

void FUN_004198f0(byte *param_1,int param_2,int param_3)

{
  int *piVar1;
  int in_ECX;
  int *piVar2;
  
  param_3 = param_3 - (int)param_1;
  piVar1 = (int *)(in_ECX + 0x194);
  piVar2 = &DAT_00450b4c;
  do {
    if (*piVar2 == -1) {
      *(undefined1 *)(*piVar1 + 0xc6) = *(undefined1 *)(*piVar1 + 0xcd);
      *(undefined1 *)(*piVar1 + 199) = *(undefined1 *)(*piVar1 + 0xce);
      *(undefined1 *)(*piVar1 + 200) = *(undefined1 *)(*piVar1 + 0xcf);
      *(undefined1 *)(*piVar1 + 0xc9) = *(undefined1 *)(*piVar1 + 0xd0);
      *(undefined1 *)(*piVar1 + 0xca) = *(undefined1 *)(*piVar1 + 0xd1);
      *(undefined1 *)(*piVar1 + 0xcb) = *(undefined1 *)(*piVar1 + 0xd2);
      *(undefined1 *)(*piVar1 + 0xcc) = *(undefined1 *)(*piVar1 + 0xd3);
      if (param_2 == 0) {
        *(undefined1 *)(*piVar1 + 0xd3) = 0;
        *(undefined1 *)(*piVar1 + 0xd2) = 0;
        *(undefined1 *)(*piVar1 + 0xd1) = 0;
        *(undefined1 *)(*piVar1 + 0xd0) = 0;
        *(undefined1 *)(*piVar1 + 0xcf) = 0;
        *(undefined1 *)(*piVar1 + 0xce) = 0;
        *(undefined1 *)(*piVar1 + 0xcd) = 0;
        if ((*param_1 & 0x80) != 0) {
          *(undefined1 *)(*piVar1 + 0xcd) = 1;
        }
        if ((*param_1 & 0x40) != 0) {
          *(undefined1 *)(*piVar1 + 0xce) = 1;
        }
        if ((*param_1 & 0x20) != 0) {
          *(undefined1 *)(*piVar1 + 0xcf) = 1;
        }
        if ((*param_1 & 0x10) != 0) {
          *(undefined1 *)(*piVar1 + 0xd0) = 1;
        }
        if ((*param_1 & 8) != 0) {
          *(undefined1 *)(*piVar1 + 0xd1) = 1;
        }
        if ((*param_1 & 4) != 0) {
          *(undefined1 *)(*piVar1 + 0xd2) = 1;
        }
        if ((*param_1 & 2) != 0) {
          *(undefined1 *)(*piVar1 + 0xd3) = 1;
        }
        if (DAT_00450b80 != 0) {
          param_1[param_3] = *param_1;
        }
      }
    }
    piVar2 = piVar2 + 1;
    piVar1 = piVar1 + 1;
    param_1 = param_1 + 1;
  } while ((int)piVar2 < 0x450b6c);
  return;
}

