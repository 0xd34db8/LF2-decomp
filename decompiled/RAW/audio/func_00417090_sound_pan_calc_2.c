/* Function: FUN_00417090 */
/* Address: 0x00417090 */

void FUN_00417090(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (param_1 - DAT_00450bc4) + -200;
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (iVar1 < 200) {
    iVar1 = 100;
  }
  else if (iVar1 < 400) {
    iVar1 = ((400 - iVar1) * 100) / 200;
  }
  else {
    iVar1 = 0;
  }
  iVar2 = (param_1 - DAT_00450bc4) + -600;
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar2 < 200) {
    iVar2 = 100;
  }
  else if (iVar2 < 400) {
    iVar2 = ((400 - iVar2) * 100) / 200;
  }
  else {
    iVar2 = 0;
  }
  if ((&DAT_00453e10)[param_2] == 0) {
    (&DAT_004527e8)[param_2] = 0;
    (&DAT_004554c8)[param_2] = 0;
  }
  (&DAT_004527e8)[param_2] = (&DAT_004527e8)[param_2] + iVar1;
  (&DAT_004554c8)[param_2] = (&DAT_004554c8)[param_2] + iVar2;
  (&DAT_00453e10)[param_2] = 1;
  return;
}
