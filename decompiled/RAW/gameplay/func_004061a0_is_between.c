/* Function: FUN_004061a0 */
/* Address: 0x004061a0 */

undefined4 FUN_004061a0(int param_1,int param_2,int param_3)

{
  if (((param_1 < param_2) && (param_2 < param_3)) || ((param_3 < param_2 && (param_2 < param_1))))
  {
    return 1;
  }
  return 0;
}

