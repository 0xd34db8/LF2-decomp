/* Function: FUN_00418c30 */
/* Address: 0x00418c30 */

void FUN_00418c30(void)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  int iVar4;
  char *in_ECX;
  int *piVar5;
  int iVar6;
  int iVar7;
  int local_8;
  int local_4;
  
  local_8 = 0;
  piVar5 = (int *)(in_ECX + 0x194);
  do {
    iVar6 = local_4;
    if (in_ECX[local_8 + 4] != '\0') {
      iVar4 = *(int *)(*piVar5 + 0x368);
      iVar7 = *(int *)(*piVar5 + 0x7c) * 0x178;
      iVar1 = iVar7 + 0x82c + iVar4;
      if ((*(int *)(iVar7 + 0x82c + iVar4) == 1) && (-1 < *(int *)(*piVar5 + 0xb4))) {
        iVar6 = *(int *)(*piVar5 + 0x8c);
        if ((*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x90) == local_8) &&
           (local_4 = iVar6,
           *(int *)(*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x7c) * 0x178 + 0x82c +
                   *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368)) == 2)) {
          if (0 < *(int *)(iVar1 + 0x30)) {
            *(int *)(*piVar5 + 0x94) = *(int *)(*piVar5 + 0x94) - *(int *)(iVar1 + 0x30);
          }
          if (*(int *)(iVar1 + 0x30) < 0) {
            *(int *)(*piVar5 + 0x94) = *(int *)(*piVar5 + 0x94) + *(int *)(iVar1 + 0x30);
            if (*(int *)(*piVar5 + 0x94) < 0) {
              *(undefined4 *)(*piVar5 + 0x70) = 0;
              *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) = 0;
              *(undefined4 *)(*piVar5 + 0x20) = 1;
              *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x20) = 1;
              iVar4 = *(int *)(in_ECX + iVar6 * 4 + 0x194);
              if (*(int *)(iVar4 + 0x10) < *(int *)(*piVar5 + 0x10)) {
                *(undefined8 *)(iVar4 + 0x28) = 0xc010000000000000;
                *(undefined8 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x30) = 0xc008000000000000;
                *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) = 0xb5;
              }
              else {
                *(undefined8 *)(iVar4 + 0x28) = 0x4010000000000000;
                *(undefined8 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x30) = 0xc008000000000000;
                *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) = 0xb5;
              }
              goto LAB_00418d91;
            }
          }
          iVar4 = *piVar5;
          if ((((*(char *)(iVar4 + 0xd1) != '\0') && ('\0' < *(char *)(iVar4 + 0xbe))) &&
              (*(int *)(iVar1 + 0x18) != 0)) &&
             (((*(char *)(iVar4 + 0xcf) == '\0' && (*(char *)(iVar4 + 0xd0) == '\0')) ||
              (*(int *)(iVar1 + 0x38) == 0)))) {
            *(int *)(iVar4 + 0x70) = *(int *)(iVar1 + 0x18);
            iVar4 = *piVar5;
            if (*(int *)(iVar4 + 0x70) < 0) {
              *(char *)(iVar4 + 0x80) = '\x01' - *(char *)(iVar4 + 0x80);
              *(int *)(*piVar5 + 0x70) = -*(int *)(*piVar5 + 0x70);
            }
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) =
                 *(undefined4 *)
                  (*(int *)(*piVar5 + 0x70) * 0x178 + 0x840 + *(int *)(*piVar5 + 0x368));
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x88) = 0;
            *(undefined4 *)(*piVar5 + 0x88) = 0;
          }
          iVar4 = *piVar5;
          if (((*(char *)(iVar4 + 0xd1) != '\0') && ('\0' < *(char *)(iVar4 + 0xbe))) &&
             (((*(char *)(iVar4 + 0xcf) != '\0' ||
               (((*(char *)(iVar4 + 0xd0) != '\0' || (*(char *)(iVar4 + 0xcd) != '\0')) ||
                (*(char *)(iVar4 + 0xce) != '\0')))) && (*(int *)(iVar1 + 0x38) != 0)))) {
            *(int *)(*piVar5 + 0x70) = *(int *)(iVar1 + 0x38);
            iVar4 = *piVar5;
            if (*(int *)(iVar4 + 0x70) < 0) {
              *(char *)(iVar4 + 0x80) = '\x01' - *(char *)(iVar4 + 0x80);
              *(int *)(*piVar5 + 0x70) = -*(int *)(*piVar5 + 0x70);
            }
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) =
                 *(undefined4 *)
                  (*(int *)(*piVar5 + 0x70) * 0x178 + 0x840 + *(int *)(*piVar5 + 0x368));
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x88) = 0;
            *(undefined4 *)(*piVar5 + 0x88) = 0;
          }
          if (((*(char *)(*piVar5 + 0xd2) != '\0') && ('\0' < *(char *)(*piVar5 + 0xbf))) &&
             (*(int *)(iVar1 + 0x1c) != 0)) {
            *(int *)(*piVar5 + 0x70) = *(int *)(iVar1 + 0x1c);
            iVar4 = *piVar5;
            if (*(int *)(iVar4 + 0x70) < 0) {
              *(char *)(iVar4 + 0x80) = '\x01' - *(char *)(iVar4 + 0x80);
              *(int *)(*piVar5 + 0x70) = -*(int *)(*piVar5 + 0x70);
            }
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) =
                 *(undefined4 *)
                  (*(int *)(*piVar5 + 0x70) * 0x178 + 0x840 + *(int *)(*piVar5 + 0x368));
            *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x88) = 0;
            *(undefined4 *)(*piVar5 + 0x88) = 0;
          }
        }
        else {
LAB_00418d91:
          *(undefined4 *)(*piVar5 + 0x70) = 0;
          iVar6 = local_4;
        }
        if (*(int *)(iVar1 + 0x24) != 0) {
          iVar4 = *(int *)(iVar1 + 0x3c);
          if (iVar4 < 1) {
            if (iVar4 == -1) {
              *(undefined4 *)(*piVar5 + 0x324) = *(undefined4 *)(*(int *)(*piVar5 + 0x368) + 0x6f4);
              *(undefined4 *)(*piVar5 + 0x33c) =
                   *(undefined4 *)(*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368) + 0x6f4);
              *(undefined4 *)(*piVar5 + 0x368) =
                   *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
              *(undefined4 *)(*piVar5 + 0x70) = 0;
              piVar3 = (int *)(in_ECX + 0x198);
              local_4 = 0x50;
              pcVar2 = in_ECX;
              do {
                if ((pcVar2[4] != '\0') && (*(int *)(piVar3[-1] + 0x2f4) == local_8)) {
                  *(undefined4 *)(piVar3[-1] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
                }
                if ((pcVar2[5] != '\0') && (*(int *)(*piVar3 + 0x2f4) == local_8)) {
                  *(undefined4 *)(*piVar3 + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
                }
                if ((pcVar2[6] != '\0') && (*(int *)(piVar3[1] + 0x2f4) == local_8)) {
                  *(undefined4 *)(piVar3[1] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
                }
                if ((pcVar2[7] != '\0') && (*(int *)(piVar3[2] + 0x2f4) == local_8)) {
                  *(undefined4 *)(piVar3[2] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
                }
                if ((pcVar2[8] != '\0') && (*(int *)(piVar3[3] + 0x2f4) == local_8)) {
                  *(undefined4 *)(piVar3[3] + 0x368) =
                       *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368);
                }
                piVar3 = piVar3 + 5;
                local_4 = local_4 + -1;
                pcVar2 = pcVar2 + 5;
              } while (local_4 != 0);
            }
          }
          else {
            *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 800) = iVar4;
          }
          iVar4 = *piVar5;
          *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x14) =
               (*(int *)(iVar4 + 0x14) -
               *(int *)(*(int *)(iVar4 + 0x70) * 0x178 + 0x7f8 + *(int *)(iVar4 + 0x368))) +
               *(int *)(iVar1 + 8);
          *(double *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x60) =
               (double)*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x14);
          iVar4 = *piVar5;
          iVar7 = *(int *)(iVar4 + 0x70) * 0x178;
          if (*(char *)(iVar4 + 0x80) == '\0') {
            *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x10) =
                 (*(int *)(iVar4 + 0x10) - *(int *)(iVar7 + 0x7f4 + *(int *)(iVar4 + 0x368))) +
                 *(int *)(iVar1 + 4);
          }
          else {
            *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x10) =
                 (*(int *)(iVar7 + 0x7f4 + *(int *)(iVar4 + 0x368)) - *(int *)(iVar1 + 4)) +
                 *(int *)(iVar4 + 0x10);
          }
          *(double *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x58) =
               (double)*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x10);
          iVar4 = *piVar5;
          *(undefined4 *)(iVar4 + 0x70) =
               *(undefined4 *)(*(int *)(iVar4 + 0x70) * 0x178 + 0x7b4 + *(int *)(iVar4 + 0x368));
          *(undefined4 *)(*piVar5 + 0x7c) = *(undefined4 *)(*piVar5 + 0x70);
          *(undefined4 *)(*piVar5 + 0x88) = 0;
          if (*(char *)(*piVar5 + 0x80) == '\0') {
            iVar4 = *(int *)(iVar1 + 0x24);
          }
          else {
            iVar4 = -*(int *)(iVar1 + 0x24);
          }
          *(double *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x40) = (double)iVar4;
          *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) =
               *(undefined4 *)(iVar1 + 0x14);
          *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x7c) =
               *(undefined4 *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70);
          *(double *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x48) = (double)*(int *)(iVar1 + 0x28);
          iVar4 = *piVar5;
          if (*(char *)(iVar4 + 0xcd) == '\0') {
LAB_00419221:
            if (*(char *)(iVar4 + 0xce) == '\0') goto LAB_00419237;
            iVar4 = *(int *)(iVar1 + 0x40);
          }
          else {
            if (*(char *)(iVar4 + 0xce) != '\0') {
              if (*(char *)(iVar4 + 0xcd) != '\0') goto LAB_00419237;
              goto LAB_00419221;
            }
            iVar4 = -*(int *)(iVar1 + 0x40);
          }
          *(double *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x50) = (double)iVar4;
        }
LAB_00419237:
        if ((*(int *)(iVar1 + 0x34) == 1) && (iVar4 = *piVar5, *(int *)(iVar4 + 0x88) == 2)) {
          if ((*(char *)(iVar4 + 0xd0) != '\0') && (*(char *)(iVar4 + 0xcf) == '\0')) {
            *(undefined1 *)(iVar4 + 0x80) = 0;
          }
          iVar4 = *piVar5;
          if ((*(char *)(iVar4 + 0xd0) == '\0') && (*(char *)(iVar4 + 0xcf) != '\0')) {
            *(undefined1 *)(iVar4 + 0x80) = 1;
          }
        }
        if ((*(int *)(iVar1 + 0x34) == -1) && (iVar1 = *piVar5, *(int *)(iVar1 + 0x88) == 2)) {
          if ((*(char *)(iVar1 + 0xd0) != '\0') && (*(char *)(iVar1 + 0xcf) == '\0')) {
            *(undefined1 *)(iVar1 + 0x80) = 1;
          }
          iVar1 = *piVar5;
          if ((*(char *)(iVar1 + 0xd0) == '\0') && (*(char *)(iVar1 + 0xcf) != '\0')) {
            *(undefined1 *)(iVar1 + 0x80) = 0;
          }
        }
      }
      else if ((*(int *)(*(int *)(*piVar5 + 0x70) * 0x178 + 0x82c + *(int *)(*piVar5 + 0x368)) == 2)
              && ((iVar6 = *(int *)(*piVar5 + 0x90),
                  *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x8c) != local_8 ||
                  (local_4 = iVar6,
                  *(int *)(*(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x70) * 0x178 + 0x82c +
                          *(int *)(*(int *)(in_ECX + iVar6 * 4 + 0x194) + 0x368)) != 1)))) {
        iVar6 = local_4;
        *(undefined4 *)(*piVar5 + 0x70) = 0xd4;
        *(undefined8 *)(*piVar5 + 0x48) = 0xc008000000000000;
        if (-2.0 < *(double *)(*piVar5 + 0x60)) {
          *(undefined8 *)(*piVar5 + 0x60) = 0xc000000000000000;
        }
      }
    }
    local_8 = local_8 + 1;
    piVar5 = piVar5 + 1;
    local_4 = iVar6;
    if (399 < local_8) {
      return;
    }
  } while( true );
}
