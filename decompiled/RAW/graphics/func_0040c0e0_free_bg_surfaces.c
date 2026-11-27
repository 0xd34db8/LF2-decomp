/* Function: FUN_0040c0e0 */
/* Address: 0x0040c0e0 */

void FUN_0040c0e0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int in_ECX;
  undefined4 *puVar3;
  int iVar4;
  
  iVar2 = param_1 * 0x990 + in_ECX;
  puVar1 = (undefined4 *)(iVar2 + 0x4d466c4);
  if (*(int *)(iVar2 + 0x4d466c4) == 0) {
    *puVar1 = 0;
    return;
  }
  iVar4 = 0;
  puVar3 = puVar1;
  if (*(int *)(iVar2 + 0x4d45dcc) < 1) {
    *puVar1 = 0;
    return;
  }
  do {
    (**(code **)(**(int **)*puVar3 + 8))(*(int **)*puVar3);
    free((void *)*puVar3);
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < *(int *)(iVar2 + 0x4d45dcc));
  *puVar1 = 0;
  return;
}

