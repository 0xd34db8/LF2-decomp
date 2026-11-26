/* Function: FUN_00416e10 */
/* Address: 0x00416e10 */

void FUN_00416e10(int param_1,int *param_2)

{
  if (*param_2 == 0) {
    *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) | 4;
    DAT_00450c28 = 2;
  }
  return;
}
