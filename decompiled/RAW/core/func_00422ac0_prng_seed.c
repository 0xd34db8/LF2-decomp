/* Function: FUN_00422ac0 */
/* Address: 0x00422ac0 */

int FUN_00422ac0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  do {
    iVar1 = rand();
    iVar3 = iVar2 + 1;
    (&DAT_0044ff90)[iVar2] = (char)(iVar1 % 0xff) + '\x01';
    iVar2 = iVar3;
  } while (iVar3 < 3000);
  DAT_00450b48 = 0;
  return iVar1 / 0xff;
}
