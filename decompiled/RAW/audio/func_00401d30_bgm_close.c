/* Function: FUN_00401d30 */
/* Address: 0x00401d30 */

void FUN_00401d30(void)

{
  if (DAT_0044f04c != (int *)0x0) {
    (**(code **)(*DAT_0044f04c + 8))(DAT_0044f04c);
    DAT_0044f04c = (int *)0x0;
  }
  if (DAT_0044f048 != (int *)0x0) {
    (**(code **)(*DAT_0044f048 + 8))(DAT_0044f048);
    DAT_0044f048 = (int *)0x0;
  }
  if (DAT_0044f044 != (int *)0x0) {
    (**(code **)(*DAT_0044f044 + 8))(DAT_0044f044);
    DAT_0044f044 = (int *)0x0;
  }
  if (DAT_0044f040 != (int *)0x0) {
    (**(code **)(*DAT_0044f040 + 8))(DAT_0044f040);
    DAT_0044f040 = (int *)0x0;
  }
  return;
}
