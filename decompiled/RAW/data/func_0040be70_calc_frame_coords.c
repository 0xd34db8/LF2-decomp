/* Function: FUN_0040be70 */
/* Address: 0x0040be70 */

void FUN_0040be70(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
                 int param_6,undefined4 param_7)

{
  int iVar1;
  int in_ECX;
  int *piVar2;
  
  iVar1 = param_3 * 0x178 + in_ECX;
  if (*(char *)(iVar1 + 0x7a4) != '\0') {
    param_6 = *(int *)(iVar1 + 0x7a8) + param_6;
    iVar1 = 0;
    if (0 < *(int *)(in_ECX + 0x498)) {
      piVar2 = (int *)(in_ECX + 0x62c);
      while ((param_6 < *piVar2 || (piVar2[0x28] * piVar2[0x1e] + *piVar2 <= param_6))) {
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
        if (*(int *)(in_ECX + 0x498) <= iVar1) {
          return;
        }
      }
      param_6 = param_6 - *(int *)(in_ECX + 0x62c + iVar1 * 4);
      if (param_5 != 0) {
        FUN_0043f010(param_1,param_2,param_6,param_4,0,param_7);
        return;
      }
      FUN_0043f010(param_1,param_2,param_6,param_4,0,param_7);
    }
  }
  return;
}
