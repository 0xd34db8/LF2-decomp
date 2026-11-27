/* Function: FUN_00401250 */
/* Address: 0x00401250 */

void FUN_00401250(int *param_1,undefined4 param_2)

{
  undefined4 local_64 [20];
  undefined4 local_14;
  
  local_14 = param_2;
  local_64[0] = 100;
  (**(code **)(*param_1 + 0x14))(param_1,0,0,0,0x1000400,local_64);
  return;
}

