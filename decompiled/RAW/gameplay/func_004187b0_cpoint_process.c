/* Function: FUN_004187b0 */
/* Address: 0x004187b0 */

void FUN_004187b0(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int in_ECX;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_c;
  int *local_4;
  
  local_4 = (int *)(in_ECX + 0x194);
  local_c = 0;
  do {
    if (((*(char *)(in_ECX + 4 + local_c) != '\0') &&
        (iVar3 = *(int *)(*local_4 + 0x368), iVar5 = *(int *)(*local_4 + 0x70) * 0x178,
        iVar2 = iVar5 + 0x82c + iVar3, *(int *)(iVar5 + 0x82c + iVar3) == 1)) &&
       (*(int *)(*(int *)(*local_4 + 0x70) * 0x178 + 0x7ac + *(int *)(*local_4 + 0x368)) == 9)) {
      iVar3 = *(int *)(*local_4 + 0x8c);
      iVar5 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
      if ((*(int *)(iVar5 + 0x90) == local_c) &&
         (*(int *)(*(int *)(iVar5 + 0x70) * 0x178 + 0x82c + *(int *)(iVar5 + 0x368)) == 2)) {
        iVar5 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        if (((*(int *)(iVar5 + 0xb4) == 0) && (*(int *)(iVar2 + 0x2c) == 1)) ||
           (*(int *)(iVar2 + 0x2c) == 0)) {
          *(undefined4 *)(iVar5 + 0x70) = *(undefined4 *)(iVar2 + 0x14);
        }
        iVar5 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        if (*(int *)(iVar5 + 0x70) < 0) {
          *(char *)(iVar5 + 0x80) = '\x01' - *(char *)(iVar5 + 0x80);
          iVar5 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
          *(int *)(iVar5 + 0x70) = -*(int *)(iVar5 + 0x70);
        }
        iVar5 = *(int *)(iVar2 + 0xc);
        if ((iVar5 != 0) && (*(int *)(*local_4 + 0x88) == 0)) {
          if (iVar5 < 1) {
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x2fc);
            *piVar1 = *piVar1 + *(int *)(iVar2 + 0xc);
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x300);
            *piVar1 = *piVar1 + *(int *)(iVar2 + 0xc) / 3;
            *(undefined4 *)(*local_4 + 0x88) = 1;
          }
          else {
            iVar6 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
            if (0 < *(int *)(iVar6 + 0x340)) {
              iVar5 = (iVar5 * 100) / *(int *)(iVar6 + 0x340);
            }
            if (((0 < *(int *)(iVar6 + 0x2fc)) && (*(int *)(iVar6 + 0x2fc) <= iVar5)) &&
               (*(int *)(iVar6 + 0x2f4) == -1)) {
              piVar1 = (int *)(*(int *)(in_ECX + 0x194 + *(int *)(*local_4 + 0x354) * 4) + 0x358);
              *piVar1 = *piVar1 + 1;
              iVar6 = *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x344);
              if ((0 < iVar6) && (iVar6 < 3)) {
                *(int *)(&DAT_00451b60 + *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x344) * 4)
                     = *(int *)(&DAT_00451b60 +
                               *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x344) * 4) + 1;
              }
            }
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x2fc);
            *piVar1 = *piVar1 - iVar5;
            iVar6 = (int)((ulonglong)((longlong)iVar5 * 0x55555555) >> 0x20) - iVar5;
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x300);
            *piVar1 = *piVar1 + ((iVar6 >> 1) - (iVar6 >> 0x1f));
            *(undefined4 *)(*local_4 + 0x88) = 1;
            *(undefined4 *)(*local_4 + 0xb4) = 2;
            *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0xb4) = 0xfffffffd;
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x34c);
            *piVar1 = *piVar1 + iVar5;
            piVar1 = (int *)(*(int *)(in_ECX + 0x194 + *(int *)(*local_4 + 0x354) * 4) + 0x348);
            *piVar1 = *piVar1 + iVar5;
            iVar6 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
            if ((0 < *(int *)(iVar6 + 0x344)) && (*(int *)(iVar6 + 0x344) < 3)) {
              (&DAT_00451b68)[*(int *)(iVar6 + 0x344)] =
                   (&DAT_00451b68)[*(int *)(iVar6 + 0x344)] + iVar5;
            }
          }
        }
        iVar5 = *local_4;
        if (*(char *)(iVar5 + 0x80) == '\0') {
          iVar8 = *(int *)(iVar5 + 0x368) + *(int *)(iVar5 + 0x70) * 0x178;
          iVar6 = (*(int *)(iVar5 + 0x10) - *(int *)(iVar8 + 0x7f4)) + *(int *)(iVar2 + 4);
        }
        else {
          iVar8 = *(int *)(iVar5 + 0x368) + *(int *)(iVar5 + 0x70) * 0x178;
          iVar6 = (*(int *)(iVar8 + 0x7f4) - *(int *)(iVar2 + 4)) + *(int *)(iVar5 + 0x10);
        }
        iVar7 = (*(int *)(iVar5 + 0x14) - *(int *)(iVar8 + 0x7f8)) + *(int *)(iVar2 + 8);
        iVar5 = *(int *)(iVar2 + 0x14) * 0x178 + 0x82c +
                *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x368);
        iVar8 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        if (*(char *)(iVar8 + 0x80) == '\0') {
          *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x10) =
               (*(int *)(*(int *)(iVar8 + 0x70) * 0x178 + 0x7f4 + *(int *)(iVar8 + 0x368)) -
               *(int *)(iVar5 + 4)) + iVar6;
          iVar6 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
          *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x14) =
               (*(int *)(*(int *)(iVar6 + 0x70) * 0x178 + 0x7f8 + *(int *)(iVar6 + 0x368)) -
               *(int *)(iVar5 + 8)) + iVar7;
        }
        else {
          *(int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x10) =
               (*(int *)(iVar5 + 4) -
               *(int *)(*(int *)(iVar8 + 0x368) + 0x7f4 + *(int *)(iVar8 + 0x70) * 0x178)) + iVar6;
          iVar6 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
          *(int *)(iVar6 + 0x14) =
               (*(int *)(*(int *)(iVar6 + 0x70) * 0x178 + 0x7f8 + *(int *)(iVar6 + 0x368)) -
               *(int *)(iVar5 + 8)) + iVar7;
        }
        *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x18) =
             *(undefined4 *)(*local_4 + 0x18);
        iVar5 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        if (*(int *)(iVar2 + 0x10) % 10 == 0) {
          piVar1 = (int *)(iVar5 + 0x18);
          *piVar1 = *piVar1 + -1;
          piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x14);
          *piVar1 = *piVar1 + 1;
        }
        else {
          piVar1 = (int *)(iVar5 + 0x18);
          *piVar1 = *piVar1 + 1;
          piVar1 = (int *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x14);
          *piVar1 = *piVar1 + -1;
        }
        iVar2 = *(int *)(iVar2 + 0x10) / 10;
        if (iVar2 == 1) {
          cVar4 = *(char *)(*local_4 + 0x80);
LAB_00418bda:
          *(char *)(*(int *)(in_ECX + 0x194 + iVar3 * 4) + 0x80) = cVar4;
        }
        else if (iVar2 == 2) {
          cVar4 = '\x01' - *(char *)(*local_4 + 0x80);
          goto LAB_00418bda;
        }
        iVar2 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        *(double *)(iVar2 + 0x68) = (double)*(int *)(iVar2 + 0x18);
        iVar2 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        *(double *)(iVar2 + 0x58) = (double)*(int *)(iVar2 + 0x10);
        iVar2 = *(int *)(in_ECX + 0x194 + iVar3 * 4);
        *(double *)(iVar2 + 0x60) = (double)*(int *)(iVar2 + 0x14);
      }
    }
    local_c = local_c + 1;
    local_4 = local_4 + 1;
    if (399 < local_c) {
      return;
    }
  } while( true );
}
