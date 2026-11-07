/* Function: FUN_00402000 */
/* Address: 0x00402000 */

void FUN_00402000(void)

{
  if (DAT_0044f044 != (int *)0x0) {
    (**(code **)(*DAT_0044f044 + 0x1c))(DAT_0044f044);
  }
  return;
}
