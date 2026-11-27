/* Function: FUN_0043ef50 */
/* Address: 0x0043ef50 */

void FUN_0043ef50(void)

{
  int *piVar1;
  int *in_ECX;
  
  piVar1 = (int *)*in_ECX;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *in_ECX = 0;
  }
  return;
}

