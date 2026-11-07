/* Function: FUN_00401a30 */
/* Address: 0x00401a30 */

void FUN_00401a30(void)

{
  int *in_ECX;
  int *piVar1;
  
  if ((DAT_0044eecc != 0) && (piVar1 = (int *)*in_ECX, piVar1 != (int *)0x0)) {
    (**(code **)(*piVar1 + 0x48))(piVar1);
    (**(code **)(*(int *)*in_ECX + 0x34))((int *)*in_ECX,0);
    (**(code **)(*(int *)*in_ECX + 0x30))((int *)*in_ECX,0,0,piVar1 != (int *)0x0);
  }
  return;
}
