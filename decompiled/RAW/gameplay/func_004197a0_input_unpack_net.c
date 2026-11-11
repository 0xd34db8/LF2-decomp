/* Function: FUN_004197a0 */
/* Address: 0x004197a0 */

void FUN_004197a0(int param_1,int param_2)

{
  int *piVar1;
  int in_ECX;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(in_ECX + 0x194);
  do {
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
      if ((*(byte *)(iVar2 + param_1) & 0x80) != 0) {
        *(undefined1 *)(*piVar1 + 0xcd) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 0x40) != 0) {
        *(undefined1 *)(*piVar1 + 0xce) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 0x20) != 0) {
        *(undefined1 *)(*piVar1 + 0xcf) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 0x10) != 0) {
        *(undefined1 *)(*piVar1 + 0xd0) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 8) != 0) {
        *(undefined1 *)(*piVar1 + 0xd1) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 4) != 0) {
        *(undefined1 *)(*piVar1 + 0xd2) = 1;
      }
      if ((*(byte *)(iVar2 + param_1) & 2) != 0) {
        *(undefined1 *)(*piVar1 + 0xd3) = 1;
      }
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar2 < 8);
  return;
}

