/* Function: FUN_00416e60 */
/* Address: 0x00416e60 */

void FUN_00416e60(int param_1,int *param_2,int *param_3)

{
  if ((DAT_00450c28 < 2) && (((*param_3 == 0 || (DAT_0045842c == 1)) && (*param_2 == 0)))) {
    *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) | 0x10;
    DAT_0044d034 = 1 - DAT_0044d034;
    DAT_00450c18 = DAT_00450c18 + 1;
    DAT_00450c28 = 1;
  }
  return;
}
