/* Function: FUN_004019b0 */
/* Address: 0x004019b0 */

void FUN_004019b0(void)

{
  int iVar1;
  
  if (DAT_0044eecc != (int *)0x0) {
    iVar1 = 0;
    if (0 < DAT_00458438) {
      do {
        (**(code **)(*(int *)(&DAT_00452948)[iVar1] + 8))((int *)(&DAT_00452948)[iVar1]);
        iVar1 = iVar1 + 1;
      } while (iVar1 < DAT_00458438);
    }
    iVar1 = 0;
    if (0 < DAT_0045843c) {
      do {
        (**(code **)(*(int *)(&DAT_00451db0)[iVar1] + 8))((int *)(&DAT_00451db0)[iVar1]);
        iVar1 = iVar1 + 1;
      } while (iVar1 < DAT_0045843c);
    }
    if (DAT_0044eecc != (int *)0x0) {
      (**(code **)(*DAT_0044eecc + 8))(DAT_0044eecc);
      DAT_0044eecc = (int *)0x0;
    }
  }
  return;
}
