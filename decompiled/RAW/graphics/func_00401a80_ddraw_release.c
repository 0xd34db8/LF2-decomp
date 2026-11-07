/* Function: FUN_00401a80 */
/* Address: 0x00401a80 */

void FUN_00401a80(void)

{
  if (DAT_00457578 != (int *)0x0) {
    if (DAT_00455608 != (int *)0x0) {
      (**(code **)(*DAT_00455608 + 8))(DAT_00455608);
      DAT_00455608 = (int *)0x0;
    }
    if (DAT_00455634 != (int *)0x0) {
      (**(code **)(*DAT_00455634 + 8))(DAT_00455634);
      DAT_00455634 = (int *)0x0;
    }
    (**(code **)(*DAT_00457578 + 8))(DAT_00457578);
    DAT_00457578 = (int *)0x0;
  }
  return;
}
