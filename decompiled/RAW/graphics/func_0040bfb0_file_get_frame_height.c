/* Function: FUN_0040bfb0 */
/* Address: 0x0040bfb0 */

undefined4 FUN_0040bfb0(int param_1)

{
  int iVar1;
  int *piVar2;
  int in_ECX;
  int iVar3;
  
  iVar1 = param_1 * 0x178 + in_ECX;
  if (*(char *)(iVar1 + 0x7a4) == '\0') {
    return 0;
  }
  iVar1 = *(int *)(iVar1 + 0x7a8);
  iVar3 = 0;
  if (0 < *(int *)(in_ECX + 0x498)) {
    piVar2 = (int *)(in_ECX + 0x62c);
    do {
      if ((*piVar2 <= iVar1) && (iVar1 < piVar2[0x28] * piVar2[0x1e] + *piVar2)) {
        return *(undefined4 *)
                (*(int *)(in_ECX + 0x754 + iVar3 * 4) + 0x1780 +
                (iVar1 - *(int *)(in_ECX + 0x62c + iVar3 * 4)) * 4);
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *(int *)(in_ECX + 0x498));
  }
  return 0;
}

