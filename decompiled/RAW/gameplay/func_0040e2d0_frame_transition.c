/* Function: FUN_0040e2d0 */
/* Address: 0x0040e2d0 */

int FUN_0040e2d0(int param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  bool bVar3;
  
  bVar3 = param_1 < 0;
  if (bVar3) {
    param_1 = -param_1;
  }
  if (param_1 == 999) {
    param_1 = 0;
  }
  iVar2 = param_1 * 0x178;
  iVar1 = *(int *)(in_ECX + 0x368) + iVar2;
  if (*(char *)(*(int *)(in_ECX + 0x368) + 0x7a4 + iVar2) != '\0') {
    if (DAT_0044d034 == 0) {
      *(int *)(in_ECX + 0x70) = param_1;
      *(undefined1 *)(in_ECX + 0xbf) = 0;
      *(undefined1 *)(in_ECX + 0xbe) = 0;
      *(undefined1 *)(in_ECX + 0xc0) = 0;
      *(undefined1 *)(in_ECX + 0xc5) = 0;
      *(undefined1 *)(in_ECX + 0xc4) = 0;
      *(undefined1 *)(in_ECX + 0xc3) = 0;
      *(undefined1 *)(in_ECX + 0xc2) = 0;
      return iVar2;
    }
    iVar2 = *(int *)(iVar1 + 0x7f0) / 1000;
    if (*(int *)(iVar1 + 0x7f0) % 1000 <= *(int *)(in_ECX + 0x308)) {
      iVar2 = iVar2 * 10;
      if (iVar2 < *(int *)(in_ECX + 0x2fc)) {
        *(int *)(in_ECX + 0x2fc) = *(int *)(in_ECX + 0x2fc) + (*(int *)(iVar1 + 0x7f0) / 1000) * -10
        ;
        *(int *)(in_ECX + 0x308) = *(int *)(in_ECX + 0x308) - *(int *)(iVar1 + 0x7f0) % 1000;
        *(int *)(in_ECX + 0x34c) = *(int *)(in_ECX + 0x34c) + (*(int *)(iVar1 + 0x7f0) / 1000) * 10;
        iVar1 = *(int *)(iVar1 + 0x7f0);
        iVar2 = iVar1 / 1000;
        *(int *)(in_ECX + 0x70) = param_1;
        *(int *)(in_ECX + 0x350) = *(int *)(in_ECX + 0x350) + iVar1 % 1000;
        if (bVar3) {
          *(char *)(in_ECX + 0x80) = '\x01' - *(char *)(in_ECX + 0x80);
        }
        *(undefined1 *)(in_ECX + 0xbf) = 0;
        *(undefined1 *)(in_ECX + 0xbe) = 0;
        *(undefined1 *)(in_ECX + 0xc0) = 0;
        *(undefined1 *)(in_ECX + 0xc5) = 0;
        *(undefined1 *)(in_ECX + 0xc4) = 0;
        *(undefined1 *)(in_ECX + 0xc3) = 0;
        *(undefined1 *)(in_ECX + 0xc2) = 0;
      }
    }
  }
  return iVar2;
}
