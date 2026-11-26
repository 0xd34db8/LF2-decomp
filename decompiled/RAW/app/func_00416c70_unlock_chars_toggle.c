/* Function: FUN_00416c70 */
/* Address: 0x00416c70 */

void FUN_00416c70(int param_1)

{
  *(byte *)(param_1 + 9) = *(byte *)(param_1 + 9) | 1;
  DAT_00458428 = 1 - DAT_00458428;
  FUN_00401a30(0);
  return;
}
