/* Function: FUN_00401ae0 */
/* Address: 0x00401ae0 */

void FUN_00401ae0(void)

{
  FUN_00401a80();
  if (DAT_004546f4 != (HWND)0x0) {
    DestroyWindow(DAT_004546f4);
  }
  return;
}
