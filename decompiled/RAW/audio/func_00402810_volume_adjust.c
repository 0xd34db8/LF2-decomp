/* Function: FUN_00402810 */
/* Address: 0x00402810 */

void FUN_00402810(int param_1)

{
  undefined4 *puVar1;
  
  DAT_0044d000 = DAT_0044d000 + param_1;
  if (DAT_0044d000 < 0x65) {
    if (DAT_0044d000 < 0) {
      DAT_0044d000 = 0;
    }
  }
  else {
    DAT_0044d000 = 100;
  }
  FUN_00401f30(DAT_0044d000);
  puVar1 = &DAT_0045560c;
  do {
    if (DAT_0044d000 < 1) {
      (**(code **)(*(int *)*puVar1 + 0x3c))((int *)*puVar1,0xffffd8f0);
    }
    else {
      (**(code **)(*(int *)*puVar1 + 0x3c))((int *)*puVar1,((DAT_0044d000 + -100) * 0xed8) / 100);
    }
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < 0x455620);
  return;
}
