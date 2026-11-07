/* Function: FUN_00423910 */
/* Address: 0x00423910 */

void FUN_00423910(void)

{
  if (DAT_004511ac != 0) {
    FUN_0043ef50();
    free((void *)DAT_004511ac);
    DAT_004511ac = 0;
  }
  return;
}
