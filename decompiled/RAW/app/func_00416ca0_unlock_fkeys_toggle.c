/* Function: FUN_00416ca0 */
/* Address: 0x00416ca0 */

void FUN_00416ca0(int param_1)

{
  *(byte *)(param_1 + 9) = *(byte *)(param_1 + 9) | 2;
  DAT_0045842c = 1 - DAT_0045842c;
  FUN_00401a30(0);
  return;
}
