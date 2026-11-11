/* Function: FUN_004196f0 */
/* Address: 0x004196f0 */

void FUN_004196f0(void)

{
  int *piVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar1 = (int *)(in_ECX + 0x194);
  do {
    if ((*(char *)(in_ECX + 4 + iVar3) != '\0') && (iVar2 = *piVar1, *(int *)(iVar2 + 0xb4) == 0)) {
      if (*(int *)(iVar2 + 0x20) != 0) {
        *(double *)(iVar2 + 0x40) =
             (*(double *)(iVar2 + 0x28) * 2.0) / (double)(*(int *)(iVar2 + 0x20) + 1);
        iVar2 = *piVar1;
        *(double *)(iVar2 + 0x48) =
             (*(double *)(iVar2 + 0x30) * 2.0) / (double)(*(int *)(iVar2 + 0x20) + 1);
        iVar2 = *piVar1;
        *(double *)(iVar2 + 0x50) =
             (*(double *)(iVar2 + 0x38) * 2.0) / (double)(*(int *)(iVar2 + 0x20) + 1);
        *(undefined4 *)(*piVar1 + 0x20) = 0;
        iVar2 = *piVar1;
      }
      *(undefined8 *)(iVar2 + 0x28) = 0;
      *(undefined8 *)(*piVar1 + 0x30) = 0;
      *(undefined8 *)(*piVar1 + 0x38) = 0;
    }
    iVar3 = iVar3 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar3 < 400);
  return;
}

