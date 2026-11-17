/* Function: FUN_0040d960 */
/* Address: 0x0040d960 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040d960(int param_1,int param_2)

{
  double dVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  
  if ((*(int *)(in_ECX + 0xb4) != 0) && (*(int *)(*(int *)(in_ECX + 0x368) + 0x6f8) != 3)) {
    return;
  }
  if (0 < *(int *)(in_ECX + 0xec)) {
    *(int *)(in_ECX + 0xec) = *(int *)(in_ECX + 0xec) + -1;
  }
  if (*(int *)(in_ECX + 0x98) < 0) {
    return;
  }
  iVar2 = *(int *)(in_ECX + 0x368);
  iVar4 = *(int *)(in_ECX + 0x70) * 0x178 + iVar2;
  if (*(int *)(iVar4 + 0x82c) == 2) {
    return;
  }
  if (((*(int *)(iVar2 + 0x6f8) == 3) && (iVar4 = *(int *)(iVar4 + 0x7c8), 0 < iVar4)) &&
     (*(int *)(in_ECX + 0x2fc) = *(int *)(in_ECX + 0x2fc) - iVar4, *(int *)(in_ECX + 0x2fc) < 1)) {
    *(undefined4 *)(in_ECX + 0x2fc) = 0;
    *(undefined4 *)(in_ECX + 0x70) =
         *(undefined4 *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7cc + iVar2);
  }
  if (0 < *(int *)(in_ECX + 8)) {
    *(int *)(in_ECX + 8) = *(int *)(in_ECX + 8) + -1;
  }
  if (*(int *)(in_ECX + 8) < 0) {
    *(int *)(in_ECX + 8) = *(int *)(in_ECX + 8) + 1;
  }
  if (0 < *(int *)(in_ECX + 0xb0)) {
    *(int *)(in_ECX + 0xb0) = *(int *)(in_ECX + 0xb0) + -1;
  }
  if (0 < *(int *)(in_ECX + 0xb8)) {
    *(int *)(in_ECX + 0xb8) = *(int *)(in_ECX + 0xb8) + -1;
  }
  if ('\0' < *(char *)(in_ECX + 0xea)) {
    *(char *)(in_ECX + 0xea) = *(char *)(in_ECX + 0xea) + -1;
  }
  if (*(int *)(in_ECX + 0x70) != *(int *)(in_ECX + 0x74)) {
    iVar2 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x918 + iVar2);
    if (-1 < iVar2) {
      FUN_00416fb0(*(undefined4 *)(in_ECX + 0x10),iVar2);
    }
    *(undefined4 *)(in_ECX + 0x88) = 0;
  }
  iVar2 = *(int *)(in_ECX + 0x368);
  *(int *)(in_ECX + 0x88) = *(int *)(in_ECX + 0x88) + 1;
  if (((-1 < *(int *)(iVar2 + 0x6f8)) &&
      (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 0)) &&
     (*(int *)(in_ECX + 0x14) < 0)) {
    *(undefined4 *)(in_ECX + 0x70) = 0xd4;
  }
  if (((*(int *)(iVar2 + 0x6f8) == 2) &&
      (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 2000)) &&
     ((*(int *)(in_ECX + 0x14) == 0 &&
      ((*(double *)(in_ECX + 0x40) < 0.1 && (-0.1 < *(double *)(in_ECX + 0x40))))))) {
    *(undefined4 *)(in_ECX + 0x70) = 0x14;
  }
  if ((*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 0xe) &&
     (*(int *)(in_ECX + 0x2fc) < 1)) {
    if (((-1 < *(int *)(in_ECX + 0x2f4)) || ((*(int *)(in_ECX + 0x364) == 5 || (0x13 < param_2))))
       && (*(int *)(in_ECX + 8) < 1)) {
      *(undefined4 *)(in_ECX + 8) = 0x1e;
    }
    *(undefined4 *)(in_ECX + 0x88) = 0;
  }
  if (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 2000) {
    if (*(double *)(in_ECX + 0x40) <= 0.0) {
      *(undefined1 *)(in_ECX + 0x80) = 1;
    }
    else {
      *(undefined1 *)(in_ECX + 0x80) = 0;
    }
  }
  if (*(int *)(in_ECX + 0x88) <= *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7b0 + iVar2))
  goto LAB_0040ddf3;
  *(undefined4 *)(in_ECX + 0x88) = 0;
  iVar4 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7b4 + iVar2);
  if (iVar4 == 0) goto LAB_0040ddf3;
  *(int *)(in_ECX + 0x70) = iVar4;
  if (iVar4 < 0) {
    *(char *)(in_ECX + 0x80) = '\x01' - *(char *)(in_ECX + 0x80);
    *(int *)(in_ECX + 0x70) = -*(int *)(in_ECX + 0x70);
  }
  bVar3 = false;
  if (*(int *)(in_ECX + 0x70) == 999) {
    if ((*(int *)(in_ECX + 0x14) == 0) || (*(int *)(iVar2 + 0x6f8) != 0)) {
      *(undefined4 *)(in_ECX + 0x70) = 0;
    }
    else {
      bVar3 = true;
      *(undefined4 *)(in_ECX + 0x70) = 0xd4;
    }
  }
  iVar4 = *(int *)(in_ECX + 0x70);
  if (iVar4 < 0) {
    return;
  }
  if (399 < iVar4) {
    return;
  }
  if (((*(int *)(*(int *)(in_ECX + 0x74) * 0x178 + 0x7ac + iVar2) == 0xe) &&
      (*(int *)(iVar4 * 0x178 + 0x7ac + iVar2) != 0xd)) &&
     ((((*(int *)(in_ECX + 0x364) != 5 && (*(int *)(in_ECX + 0x344) == 0)) || (_DAT_00450c30 != 2))
      && ((((param_1 != 1 && (param_1 != 4)) ||
           ((*(int *)(in_ECX + 0x364) != 5 && (*(int *)(in_ECX + 0x344) == 0)))) ||
          ((*(int *)(iVar2 + 0x6f4) / 10 != 3 || (*(int *)(iVar2 + 0x6f4) == 0x26)))))))) {
    *(undefined4 *)(in_ECX + 8) = 0xf;
  }
  if ((*(int *)(in_ECX + 0x70) == 0xd4) && (!bVar3)) {
    *(undefined8 *)(in_ECX + 0x48) = *(undefined8 *)(iVar2 + 0x50);
    if ((*(char *)(in_ECX + 0xd0) == '\x01') && (*(char *)(in_ECX + 0xcf) == '\0')) {
      dVar1 = *(double *)(iVar2 + 0x58);
LAB_0040dccf:
      *(double *)(in_ECX + 0x40) = dVar1;
    }
    else if ((*(char *)(in_ECX + 0xcf) == '\x01') && (*(char *)(in_ECX + 0xd0) == '\0')) {
      dVar1 = -*(double *)(iVar2 + 0x58);
      goto LAB_0040dccf;
    }
    if (*(char *)(in_ECX + 0xcd) == '\0') {
LAB_0040dcf0:
      if (*(char *)(in_ECX + 0xce) == '\0') goto LAB_0040dcff;
      dVar1 = *(double *)(iVar2 + 0x60);
    }
    else {
      if (*(char *)(in_ECX + 0xce) != '\0') {
        if (*(char *)(in_ECX + 0xcd) != '\0') goto LAB_0040dcff;
        goto LAB_0040dcf0;
      }
      dVar1 = -*(double *)(iVar2 + 0x60);
    }
    *(double *)(in_ECX + 0x50) = dVar1;
  }
LAB_0040dcff:
  if ((*(int *)(in_ECX + 0x70) < 400) &&
     (iVar2 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x918 + iVar2), -1 < iVar2)) {
    FUN_00416fb0(*(undefined4 *)(in_ECX + 0x10),iVar2);
  }
  iVar2 = *(int *)(in_ECX + 0x368);
  iVar5 = *(int *)(in_ECX + 0x70) * 0x178;
  iVar4 = *(int *)(iVar5 + 0x7f0 + iVar2);
  if ((iVar4 < 0) && (DAT_0044d034 != 0)) {
    if (*(int *)(in_ECX + 0x308) < iVar4) {
      *(undefined4 *)(in_ECX + 0x70) = *(undefined4 *)(iVar5 + iVar2 + 0x7cc);
    }
    else {
      *(int *)(in_ECX + 0x308) = iVar4 + *(int *)(in_ECX + 0x308);
      *(int *)(in_ECX + 0x350) =
           *(int *)(in_ECX + 0x350) - *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7f0 + iVar2);
    }
    iVar4 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7cc + iVar2);
    if (0 < iVar4) {
      if ((((*(char *)(in_ECX + 0xcf) == '\x01') && (*(char *)(in_ECX + 0xd0) == '\0')) &&
          (*(int *)(in_ECX + 0x14) == 0)) && (*(char *)(in_ECX + 0x80) == '\0')) {
        *(int *)(in_ECX + 0x70) = iVar4;
      }
      if (((*(char *)(in_ECX + 0xcf) == '\0') && (*(char *)(in_ECX + 0xd0) == '\x01')) &&
         ((*(int *)(in_ECX + 0x14) == 0 && (*(char *)(in_ECX + 0x80) == '\x01')))) {
        *(undefined4 *)(in_ECX + 0x70) =
             *(undefined4 *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7cc + iVar2);
      }
    }
  }
LAB_0040ddf3:
  if ((*(int *)(in_ECX + 0x70) == 0x6e) || (*(int *)(in_ECX + 0x70) == 0x72)) {
    *(undefined1 *)(in_ECX + 0xc1) = 3;
  }
  if (*(int *)(in_ECX + 0x70) == 0xca) {
    *(undefined4 *)(in_ECX + 8) = 0x14;
  }
  *(undefined4 *)(in_ECX + 0x74) = *(undefined4 *)(in_ECX + 0x70);
  return;
}
