/* Function: FUN_00417200 */
/* Address: 0x00417200 */

undefined4 FUN_00417200(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int in_ECX;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  if ((((*(int *)(*(int *)(iVar6 + 0x70) * 0x178 + 0x8cc + *(int *)(iVar6 + 0x368)) == 0) ||
       (iVar6 = *(int *)(in_ECX + 0x194 + param_2 * 4),
       *(int *)((*(int *)(iVar6 + 0x70) + 6) * 0x178 + *(int *)(iVar6 + 0x368)) == 0)) ||
      (0 < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0xec))) ||
     ('\0' < *(char *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xf0 + param_1))) {
    return 0;
  }
  iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar7 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  iVar1 = *(int *)(iVar6 + 0x368) + *(int *)(iVar6 + 0x7c) * 0x178;
  iVar5 = *(int *)(iVar7 + 0x7c) * 0x178;
  iVar6 = *(int *)(iVar5 + 0x8ec + *(int *)(iVar7 + 0x368));
  iVar5 = iVar5 + *(int *)(iVar7 + 0x368);
  if (*(char *)(iVar7 + 0x80) == '\0') {
    iVar2 = *(int *)(iVar7 + 0x7c) * 0x178 + *(int *)(iVar7 + 0x368);
    iVar6 = iVar6 + (*(int *)(iVar7 + 0x10) - *(int *)(iVar2 + 0x7f4));
    iVar7 = *(int *)(iVar7 + 0x14) - *(int *)(iVar2 + 0x7f8);
  }
  else {
    iVar2 = *(int *)(iVar7 + 0x368) + *(int *)(iVar7 + 0x7c) * 0x178;
    iVar6 = ((*(int *)(iVar2 + 0x7f4) + *(int *)(iVar7 + 0x10)) - *(int *)(iVar5 + 0x8f4)) - iVar6;
    iVar7 = *(int *)(iVar7 + 0x14) - *(int *)(iVar2 + 0x7f8);
  }
  iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  if (*(char *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x80) == '\0') {
    iVar3 = *(int *)(iVar2 + 0x7c) * 0x178 + *(int *)(iVar2 + 0x368);
    iVar8 = *(int *)(iVar1 + 0x8dc) + (*(int *)(iVar2 + 0x10) - *(int *)(iVar3 + 0x7f4));
    iVar2 = *(int *)(iVar2 + 0x14) - *(int *)(iVar3 + 0x7f8);
  }
  else {
    iVar3 = *(int *)(iVar2 + 0x368) + *(int *)(iVar2 + 0x7c) * 0x178;
    iVar8 = ((*(int *)(iVar3 + 0x7f4) + *(int *)(iVar2 + 0x10)) - *(int *)(iVar1 + 0x8e4)) -
            *(int *)(iVar1 + 0x8dc);
    iVar2 = *(int *)(iVar2 + 0x14) - *(int *)(iVar3 + 0x7f8);
  }
  uVar4 = FUN_004171c0(iVar6,*(int *)(iVar5 + 0x8f0) + iVar7,*(int *)(iVar5 + 0x8f4),
                       *(undefined4 *)(iVar5 + 0x8f8),iVar8,*(int *)(iVar1 + 0x8e0) + iVar2,
                       *(int *)(iVar1 + 0x8e4),*(undefined4 *)(iVar1 + 0x8e8));
  return uVar4;
}
