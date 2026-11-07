/* Function: FUN_0043e890 */
/* Address: 0x0043e890 */

void FUN_0043e890(void)

{
  int iVar1;
  
  iVar1 = FUN_0043e860();
  if (iVar1 < 0) {
    DAT_00458434 = 1;
    FUN_00401ae0();
    iVar1 = FUN_0043bdd0();
    if (iVar1 < 0) {
      OutputDebugStringA("Reinitialization failed.\n");
    }
    ShowWindow(DAT_004546f4,5);
    DAT_00458434 = 0;
  }
  return;
}
