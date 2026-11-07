/* Function: FUN_0040de30 */
/* Address: 0x0040de30 */

void FUN_0040de30(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int local_4;
  
  local_4 = 0;
  if (*(int *)(in_ECX + 0xb4) < 0) {
    local_4 = param_3 * 6 + -3;
  }
  iVar2 = *(int *)(in_ECX + 0x368) + *(int *)(in_ECX + 0x70) * 0x178;
  if (*(int *)(iVar2 + 0x7ac) == 0x270d) {
    if (*(char *)(in_ECX + 0x80) == '\0') {
      iVar3 = *(int *)(in_ECX + 0x368);
      iVar2 = (((*(int *)(in_ECX + 0x1c) - *(int *)(iVar2 + 0x7f4)) + *(int *)(in_ECX + 0x10)) -
              param_1) + local_4;
      if (iVar2 < 0) {
        uVar7 = *(undefined4 *)(in_ECX + 0x318);
        iVar1 = *(int *)(in_ECX + 0x70);
        iVar3 = (*(int *)(in_ECX + 0x18) - *(int *)(iVar1 * 0x178 + 0x7f8 + iVar3)) +
                *(int *)(in_ECX + 0x14);
        iVar2 = 0;
      }
      else if (iVar2 < 0x2cb) {
        uVar7 = *(undefined4 *)(in_ECX + 0x318);
        iVar1 = *(int *)(in_ECX + 0x70);
        iVar3 = (*(int *)(in_ECX + 0x18) - *(int *)(iVar1 * 0x178 + 0x7f8 + iVar3)) +
                *(int *)(in_ECX + 0x14);
      }
      else {
        uVar7 = *(undefined4 *)(in_ECX + 0x318);
        iVar1 = *(int *)(in_ECX + 0x70);
        iVar3 = (*(int *)(in_ECX + 0x18) - *(int *)(iVar1 * 0x178 + 0x7f8 + iVar3)) +
                *(int *)(in_ECX + 0x14);
        iVar2 = 0x2ca;
      }
      FUN_0040be70(iVar2,iVar3,iVar1,1,0,uVar7,param_2);
    }
    if (*(char *)(in_ECX + 0x80) == '\x01') {
      iVar2 = *(int *)(in_ECX + 0x70);
      iVar1 = FUN_0040bf30(iVar2);
      iVar3 = *(int *)(in_ECX + 0x368);
      iVar1 = (((*(int *)(iVar2 * 0x178 + 0x7f4 + iVar3) + *(int *)(in_ECX + 0x1c) +
                *(int *)(in_ECX + 0x10)) - param_1) + local_4) - iVar1;
      iVar2 = *(int *)(in_ECX + 0x70);
      if (iVar1 < 0) {
        FUN_0040be70(0,(*(int *)(in_ECX + 0x18) - *(int *)(iVar2 * 0x178 + 0x7f8 + iVar3)) +
                       *(int *)(in_ECX + 0x14),iVar2,1,1,*(undefined4 *)(in_ECX + 0x318),param_2);
        return;
      }
      if (iVar1 < 0x2cb) {
        FUN_0040be70(iVar1,(*(int *)(in_ECX + 0x18) - *(int *)(iVar2 * 0x178 + 0x7f8 + iVar3)) +
                           *(int *)(in_ECX + 0x14),iVar2,1,1,*(undefined4 *)(in_ECX + 0x318),param_2
                    );
        return;
      }
      FUN_0040be70(0x2ca,(*(int *)(in_ECX + 0x18) - *(int *)(iVar2 * 0x178 + 0x7f8 + iVar3)) +
                         *(int *)(in_ECX + 0x14),iVar2,1,1,*(undefined4 *)(in_ECX + 0x318),param_2);
      return;
    }
  }
  else {
    if (*(char *)(in_ECX + 0x80) == '\0') {
      iVar2 = *(int *)(in_ECX + 0x70) * 0x178;
      FUN_0040be70((((*(int *)(in_ECX + 0x1c) - *(int *)(iVar2 + *(int *)(in_ECX + 0x368) + 0x7f4))
                    + *(int *)(in_ECX + 0x10)) - param_1) + local_4,
                   (*(int *)(in_ECX + 0x18) - *(int *)(iVar2 + 0x7f8 + *(int *)(in_ECX + 0x368))) +
                   *(int *)(in_ECX + 0x14),*(int *)(in_ECX + 0x70),1,0,
                   *(undefined4 *)(in_ECX + 0x318),param_2);
    }
    if (*(char *)(in_ECX + 0x80) == '\x01') {
      iVar2 = *(int *)(in_ECX + 0x70);
      iVar3 = *(int *)(in_ECX + 0x368);
      uVar7 = *(undefined4 *)(in_ECX + 0x318);
      uVar6 = 1;
      iVar4 = (*(int *)(in_ECX + 0x18) - *(int *)(iVar2 * 0x178 + 0x7f8 + iVar3)) +
              *(int *)(in_ECX + 0x14);
      uVar5 = 1;
      iVar1 = FUN_0040bf30(iVar2);
      FUN_0040be70((((*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7f4 + iVar3) +
                      *(int *)(in_ECX + 0x1c) + *(int *)(in_ECX + 0x10)) - param_1) + local_4) -
                   iVar1,iVar4,iVar2,uVar5,uVar6,uVar7,param_2);
    }
    if ((*(int *)(in_ECX + 0x2fc) < *(int *)(in_ECX + 0x304) / 3) &&
       (0 < *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x824 + *(int *)(in_ECX + 0x368)))) {
      iVar2 = *(int *)(in_ECX + 0x70) * 0x178 + *(int *)(in_ECX + 0x368);
      if (*(char *)(in_ECX + 0x80) == '\0') {
        iVar3 = *(int *)(iVar2 + 0x824) - *(int *)(iVar2 + 0x7f4);
      }
      else {
        iVar3 = *(int *)(iVar2 + 0x7f4) - *(int *)(iVar2 + 0x824);
      }
      FUN_0043f310(0,0x14,1,3,
                   ((iVar3 + *(int *)(in_ECX + 0x1c) + *(int *)(in_ECX + 0x10)) - param_1) + local_4
                   ,(*(int *)(iVar2 + 0x828) - *(int *)(iVar2 + 0x7f8)) + *(int *)(in_ECX + 0x18) +
                    *(int *)(in_ECX + 0x14),DAT_00455608);
    }
  }
  return;
}
