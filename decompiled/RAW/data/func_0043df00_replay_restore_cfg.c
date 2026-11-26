/* Function: FUN_0043df00 */
/* Address: 0x0043df00 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043df00(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  _DAT_00450c30 = (int)DAT_0045877c;
  iVar4 = 0;
  do {
    pcVar2 = &DAT_00458850 + iVar4;
    iVar3 = iVar4 - (int)pcVar2;
    do {
      cVar1 = *pcVar2;
      pcVar2[(int)(&DAT_0044fcc0 + iVar3)] = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    iVar4 = iVar4 + 0xb;
  } while (iVar4 < 0x58);
  iVar4 = 0;
  do {
    pcVar2 = &DAT_004587e8 + iVar4;
    (&DAT_0044fd18)[iVar4] = *pcVar2;
    iVar4 = iVar4 + 1;
  } while (*pcVar2 != '\0');
  iVar4 = 0;
  do {
    pcVar2 = &DAT_00458588 + iVar4;
    (&DAT_0044f900)[iVar4] = *pcVar2;
    iVar4 = iVar4 + 1;
  } while (*pcVar2 != '\0');
  iVar4 = 0;
  do {
    pcVar2 = &DAT_00458780 + iVar4;
    (&DAT_0044f890)[iVar4] = *pcVar2;
    iVar4 = iVar4 + 1;
  } while (*pcVar2 != '\0');
  return;
}
