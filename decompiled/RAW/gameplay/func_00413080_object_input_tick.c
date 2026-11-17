/* Function: FUN_00413080 */
/* Address: 0x00413080 */

void FUN_00413080(undefined4 param_1,undefined4 param_2)

{
  double dVar1;
  char cVar2;
  char cVar3;
  int *piVar4;
  int *in_ECX;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if ('\0' < *(char *)((int)in_ECX + 0xc2)) {
    *(char *)((int)in_ECX + 0xc2) = *(char *)((int)in_ECX + 0xc2) + -1;
  }
  if ('\0' < *(char *)((int)in_ECX + 0xc3)) {
    *(char *)((int)in_ECX + 0xc3) = *(char *)((int)in_ECX + 0xc3) + -1;
  }
  if ('\0' < (char)in_ECX[0x31]) {
    *(char *)(in_ECX + 0x31) = (char)in_ECX[0x31] + -1;
  }
  if ('\0' < *(char *)((int)in_ECX + 0xc5)) {
    *(char *)((int)in_ECX + 0xc5) = *(char *)((int)in_ECX + 0xc5) + -1;
  }
  if ('\0' < *(char *)((int)in_ECX + 0xbf)) {
    *(char *)((int)in_ECX + 0xbf) = *(char *)((int)in_ECX + 0xbf) + -1;
  }
  if ('\0' < *(char *)((int)in_ECX + 0xbe)) {
    *(char *)((int)in_ECX + 0xbe) = *(char *)((int)in_ECX + 0xbe) + -1;
  }
  if ('\0' < (char)in_ECX[0x30]) {
    *(char *)(in_ECX + 0x30) = (char)in_ECX[0x30] + -1;
  }
  if ('\0' < *(char *)((int)in_ECX + 0xc1)) {
    *(char *)((int)in_ECX + 0xc1) = *(char *)((int)in_ECX + 0xc1) + -1;
  }
  if ((*(char *)((int)in_ECX + 0xc9) == '\0') && ((char)in_ECX[0x34] == '\x01')) {
    *(undefined1 *)((int)in_ECX + 0xc2) = 5;
    FUN_0040e450(6);
  }
  if (((char)in_ECX[0x32] == '\0') && (*(char *)((int)in_ECX + 0xcf) == '\x01')) {
    *(undefined1 *)((int)in_ECX + 0xc3) = 5;
    FUN_0040e450(4);
  }
  if ((*(char *)((int)in_ECX + 0xc6) == '\0') && (*(char *)((int)in_ECX + 0xcd) == '\x01')) {
    *(undefined1 *)(in_ECX + 0x31) = 5;
    FUN_0040e450(8);
  }
  if ((*(char *)((int)in_ECX + 199) == '\0') && (*(char *)((int)in_ECX + 0xce) == '\x01')) {
    *(undefined1 *)((int)in_ECX + 0xc5) = 5;
    FUN_0040e450(2);
  }
  if (((char)in_ECX[0x33] == '\0') && (*(char *)((int)in_ECX + 0xd3) == '\x01')) {
    *(undefined1 *)(in_ECX + 0x30) = 5;
    FUN_0040e450(9);
  }
  if ((*(char *)((int)in_ECX + 0xcb) == '\0') && (*(char *)((int)in_ECX + 0xd2) == '\x01')) {
    *(undefined1 *)((int)in_ECX + 0xbf) = 5;
    FUN_0040e450(0);
  }
  if ((*(char *)((int)in_ECX + 0xca) == '\0') && (*(char *)((int)in_ECX + 0xd1) == '\x01')) {
    *(undefined1 *)((int)in_ECX + 0xbe) = 5;
    FUN_0040e450(5);
  }
  FUN_00412800();
  FUN_004128f0();
  FUN_004129e0();
  FUN_00412ac0();
  FUN_00412ba0();
  FUN_00412c90();
  FUN_00412d80();
  FUN_00412e60();
  FUN_00412f40(param_2);
  iVar5 = in_ECX[0x1c] * 0x178 + in_ECX[0xda];
  if (((*(int *)(iVar5 + 0x7c8) == 0) || (*(char *)((int)in_ECX + 0xbe) <= (char)in_ECX[0x30])) ||
     (*(char *)((int)in_ECX + 0xbe) <= *(char *)((int)in_ECX + 0xbf))) {
    if (((*(int *)(iVar5 + 0x7cc) == 0) || ((char)in_ECX[0x30] <= *(char *)((int)in_ECX + 0xbe))) ||
       ((char)in_ECX[0x30] <= *(char *)((int)in_ECX + 0xbf))) {
      if (((*(int *)(iVar5 + 2000) != 0) &&
          (*(char *)((int)in_ECX + 0xbe) < *(char *)((int)in_ECX + 0xbf))) &&
         ((char)in_ECX[0x30] < *(char *)((int)in_ECX + 0xbf))) {
        FUN_0040e2d0(*(int *)(iVar5 + 2000));
        *(undefined1 *)((int)in_ECX + 0xbf) = 0;
      }
    }
    else {
      FUN_0040e2d0(*(int *)(iVar5 + 0x7cc));
      *(undefined1 *)(in_ECX + 0x30) = 0;
    }
  }
  else {
    FUN_0040e2d0(*(int *)(iVar5 + 0x7c8));
    *(undefined1 *)((int)in_ECX + 0xbe) = 0;
  }
  iVar5 = in_ECX[0x1c];
  if (iVar5 == 0x6e) {
    if ((char)in_ECX[0x34] == '\x01') {
      *(undefined1 *)(in_ECX + 0x20) = 0;
    }
    if (*(char *)((int)in_ECX + 0xcf) == '\x01') {
      *(undefined1 *)(in_ECX + 0x20) = 1;
    }
  }
  piVar4 = (int *)in_ECX[0xda];
  if (piVar4[iVar5 * 0x5e + 0x1eb] == 0x12d) {
    if (((*(char *)((int)in_ECX + 0xcd) == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) &&
       (in_ECX[5] == 0)) {
      *(double *)(in_ECX + 0x14) = -*(double *)(piVar4 + 10);
    }
    if (((*(char *)((int)in_ECX + 0xce) == '\x01') && (*(char *)((int)in_ECX + 0xcd) == '\0')) &&
       (in_ECX[5] == 0)) {
      *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 10);
    }
  }
  if (piVar4[iVar5 * 0x5e + 0x1eb] == 0x13) {
    if (((*(char *)((int)in_ECX + 0xcd) == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) &&
       (in_ECX[5] == 0)) {
      *(double *)(in_ECX + 0x14) = -*(double *)(piVar4 + 10);
    }
    if (((*(char *)((int)in_ECX + 0xce) == '\x01') && (*(char *)((int)in_ECX + 0xcd) == '\0')) &&
       (in_ECX[5] == 0)) {
      *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 10);
    }
  }
  iVar6 = in_ECX[0x26];
  if ((iVar6 != 2) && ((iVar5 = piVar4[iVar5 * 0x5e + 0x1eb], iVar5 == 0 || (iVar5 == 1)))) {
    if (0 < in_ECX[1]) {
      in_ECX[1] = in_ECX[1] + -1;
    }
    if (in_ECX[1] < 0) {
      in_ECX[1] = in_ECX[1] + 1;
    }
    if ((((char)in_ECX[0x34] == '\x01') && (*(char *)((int)in_ECX + 0xcf) == '\0')) &&
       (in_ECX[5] == 0)) {
      if ((char)in_ECX[0x20] == '\x01') {
        in_ECX[1] = 0;
      }
      *(undefined1 *)(in_ECX + 0x20) = 0;
      iVar5 = (*in_ECX + 1) % (*piVar4 * 6);
      *in_ECX = iVar5;
      if (iVar5 < *piVar4 * 4) {
        in_ECX[0x1c] = iVar5 / *piVar4 + 5;
      }
      else {
        in_ECX[0x1c] = 0xb - iVar5 / *piVar4;
      }
      *(undefined8 *)(in_ECX + 0x10) = *(undefined8 *)(piVar4 + 2);
      if (*(char *)((int)in_ECX + 0xc9) == '\0') {
        in_ECX[1] = in_ECX[1] + 10;
      }
      if (10 < in_ECX[1]) {
        in_ECX[0x1c] = 9;
        *in_ECX = 0;
        in_ECX[1] = 0;
      }
    }
    if ((((char)in_ECX[0x34] == '\0') && (*(char *)((int)in_ECX + 0xcf) == '\x01')) &&
       (in_ECX[5] == 0)) {
      if ((char)in_ECX[0x20] == '\0') {
        in_ECX[1] = 0;
      }
      *(undefined1 *)(in_ECX + 0x20) = 1;
      iVar5 = (*in_ECX + 1) % (*piVar4 * 6);
      *in_ECX = iVar5;
      if (iVar5 < *piVar4 * 4) {
        in_ECX[0x1c] = iVar5 / *piVar4 + 5;
      }
      else {
        in_ECX[0x1c] = 0xb - iVar5 / *piVar4;
      }
      *(double *)(in_ECX + 0x10) = -*(double *)(piVar4 + 2);
      if ((char)in_ECX[0x32] == '\0') {
        in_ECX[1] = in_ECX[1] + -10;
      }
      if (in_ECX[1] < -10) {
        in_ECX[0x1c] = 9;
        *in_ECX = 0;
        in_ECX[1] = 0;
      }
    }
    if (((*(char *)((int)in_ECX + 0xcd) == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) &&
       (in_ECX[5] == 0)) {
      if (*(char *)((int)in_ECX + 0xcf) == '\0') {
        if ((char)in_ECX[0x34] == '\0') {
LAB_00413529:
          iVar5 = (*in_ECX + 1) % (*piVar4 * 6);
          *in_ECX = iVar5;
          if (iVar5 < *piVar4 * 4) {
            in_ECX[0x1c] = iVar5 / *piVar4 + 5;
          }
          else {
            in_ECX[0x1c] = 0xb - iVar5 / *piVar4;
          }
        }
      }
      else if ((char)in_ECX[0x34] != '\0') goto LAB_00413529;
      *(double *)(in_ECX + 0x14) = -*(double *)(piVar4 + 4);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
    }
    if (((*(char *)((int)in_ECX + 0xce) == '\x01') && (*(char *)((int)in_ECX + 0xcd) == '\0')) &&
       (in_ECX[5] == 0)) {
      if (*(char *)((int)in_ECX + 0xcf) == '\0') {
        if ((char)in_ECX[0x34] == '\0') {
LAB_004135a5:
          iVar5 = (*in_ECX + 1) % (*piVar4 * 6);
          *in_ECX = iVar5;
          if (iVar5 < *piVar4 * 4) {
            in_ECX[0x1c] = iVar5 / *piVar4 + 5;
            *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 4);
            *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
            goto LAB_004135f9;
          }
          in_ECX[0x1c] = 0xb - iVar5 / *piVar4;
        }
      }
      else if ((char)in_ECX[0x34] != '\0') goto LAB_004135a5;
      *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 4);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
    }
LAB_004135f9:
    if ((*(char *)((int)in_ECX + 0xd1) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbe))) {
      in_ECX[1] = 0;
      in_ECX[0x22] = 0;
      if (iVar6 == 0) {
        if (*(char *)((int)in_ECX + 0xea) < '\x01') {
          iVar5 = FUN_00417170(0x82,2);
          in_ECX[0x1c] = (iVar5 + 0xc) * 5;
          if (DAT_0044d034 != 0) {
            iVar5 = (iVar5 + 0xc) * 0x758;
            piVar4 = in_ECX + 0xc2;
            *piVar4 = *piVar4 - *(int *)(iVar5 + 0x7f0 + in_ECX[0xda]);
            if (*piVar4 < 0) {
              in_ECX[0xc2] = 0;
            }
            else {
              in_ECX[0xd4] = in_ECX[0xd4] + *(int *)(iVar5 + 0x7f0 + in_ECX[0xda]);
            }
          }
        }
        else {
          in_ECX[0x1c] = 0x46;
        }
      }
      else if (iVar6 % 100 == 1) {
        if (iVar6 == 0x65) {
          if (((((char)in_ECX[0x34] != '\0') || (*(char *)((int)in_ECX + 0xcf) != '\0')) ||
              (*(char *)((int)in_ECX + 0xcd) != '\0')) || (*(char *)((int)in_ECX + 0xce) != '\0'))
          goto LAB_004136ff;
          iVar5 = FUN_00417170(0x83,2);
          in_ECX[0x1c] = (iVar5 + 4) * 5;
        }
        else {
          iVar5 = FUN_00417170(0x84,2);
          in_ECX[0x1c] = (iVar5 + 4) * 5;
        }
      }
      else if (iVar6 == 4) {
LAB_004136ff:
        in_ECX[0x1c] = 0x2d;
      }
      else if (iVar6 == 6) {
        in_ECX[0x1c] = 0x37;
      }
    }
    if ((*(char *)((int)in_ECX + 0xd2) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbf))) {
      in_ECX[0x22] = 0;
      in_ECX[1] = 0;
      in_ECX[0x1c] = 0xd2;
    }
    if (((*(char *)((int)in_ECX + 0xd3) == '\x01') && (*(char *)((int)in_ECX + 0xc1) == '\0')) &&
       ('\0' < (char)in_ECX[0x30])) {
      in_ECX[1] = 0;
      in_ECX[0x22] = 0;
      in_ECX[0x1c] = 0x6e;
    }
  }
  iVar5 = in_ECX[0x26];
  if (iVar5 == 2) {
    piVar4 = (int *)in_ECX[0xda];
    if ((piVar4[in_ECX[0x1c] * 0x5e + 0x1eb] == 0) || (piVar4[in_ECX[0x1c] * 0x5e + 0x1eb] == 1)) {
      if (0 < in_ECX[1]) {
        in_ECX[1] = in_ECX[1] + -1;
      }
      if (in_ECX[1] < 0) {
        in_ECX[1] = in_ECX[1] + 1;
      }
      if (in_ECX[0x1c] < 0xc) {
        in_ECX[0x1c] = 0xc;
      }
      cVar2 = (char)in_ECX[0x34];
      if (((cVar2 == '\x01') && (*(char *)((int)in_ECX + 0xcf) == '\0')) && (in_ECX[5] == 0)) {
        if ((char)in_ECX[0x20] == '\x01') {
          in_ECX[1] = 0;
        }
        *(undefined1 *)(in_ECX + 0x20) = 0;
        iVar6 = (*in_ECX + 1) % (*piVar4 * 6);
        *in_ECX = iVar6;
        if (iVar6 < *piVar4 * 4) {
          in_ECX[0x1c] = iVar6 / *piVar4 + 0xc;
        }
        else {
          in_ECX[0x1c] = 0x12 - iVar6 / *piVar4;
        }
        *(undefined8 *)(in_ECX + 0x10) = *(undefined8 *)(piVar4 + 0xc);
        if (*(char *)((int)in_ECX + 0xc9) == '\0') {
          in_ECX[1] = in_ECX[1] + 10;
        }
        if (10 < in_ECX[1]) {
          in_ECX[0x1c] = 0x10;
          *in_ECX = 0;
          in_ECX[1] = 0;
        }
      }
      if (((cVar2 == '\0') && (*(char *)((int)in_ECX + 0xcf) == '\x01')) && (in_ECX[5] == 0)) {
        if ((char)in_ECX[0x20] == '\0') {
          in_ECX[1] = 0;
        }
        *(undefined1 *)(in_ECX + 0x20) = 1;
        iVar6 = (*in_ECX + 1) % (*piVar4 * 6);
        *in_ECX = iVar6;
        if (iVar6 < *piVar4 * 4) {
          in_ECX[0x1c] = iVar6 / *piVar4 + 0xc;
        }
        else {
          in_ECX[0x1c] = 0x12 - iVar6 / *piVar4;
        }
        *(double *)(in_ECX + 0x10) = -*(double *)(piVar4 + 0xc);
        if ((char)in_ECX[0x32] == '\0') {
          in_ECX[1] = in_ECX[1] + -10;
        }
        if (in_ECX[1] < -10) {
          in_ECX[0x1c] = 0x10;
          *in_ECX = 0;
          in_ECX[1] = 0;
        }
      }
      if (((*(char *)((int)in_ECX + 0xcd) == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) &&
         (in_ECX[5] == 0)) {
        if (*(char *)((int)in_ECX + 0xcf) == '\0') {
          if (cVar2 == '\0') {
LAB_0041391f:
            iVar6 = (*in_ECX + 1) % (*piVar4 * 6);
            *in_ECX = iVar6;
            if (iVar6 < *piVar4 * 4) {
              in_ECX[0x1c] = iVar6 / *piVar4 + 0xc;
            }
            else {
              in_ECX[0x1c] = 0x12 - iVar6 / *piVar4;
            }
          }
        }
        else if (cVar2 != '\0') goto LAB_0041391f;
        *(double *)(in_ECX + 0x14) = -*(double *)(piVar4 + 0xe);
        *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
      }
      if (((*(char *)((int)in_ECX + 0xce) == '\x01') && (*(char *)((int)in_ECX + 0xcd) == '\0')) &&
         (in_ECX[5] == 0)) {
        if (*(char *)((int)in_ECX + 0xcf) == '\0') {
          if (cVar2 == '\0') {
LAB_00413991:
            iVar6 = (*in_ECX + 1) % (*piVar4 * 6);
            *in_ECX = iVar6;
            if (iVar6 < *piVar4 * 4) {
              in_ECX[0x1c] = iVar6 / *piVar4 + 0xc;
              *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 0xe);
              *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
              goto LAB_004139e1;
            }
            in_ECX[0x1c] = 0x12 - iVar6 / *piVar4;
          }
        }
        else if (cVar2 != '\0') goto LAB_00413991;
        *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(piVar4 + 0xe);
        *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.4;
      }
LAB_004139e1:
      if ((*(char *)((int)in_ECX + 0xd1) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbe))) {
        in_ECX[1] = 0;
        in_ECX[0x22] = 0;
        in_ECX[0x1c] = 0x32;
      }
    }
  }
  iVar6 = in_ECX[0xda];
  if ((*(int *)(in_ECX[0x1c] * 0x178 + 0x7ac + iVar6) == 4) && (in_ECX[5] < 0)) {
    cVar2 = (char)in_ECX[0x34];
    if ((cVar2 == '\x01') && (*(char *)((int)in_ECX + 0xcf) == '\0')) {
      *(undefined1 *)(in_ECX + 0x20) = 0;
    }
    if ((*(char *)((int)in_ECX + 0xcf) == '\x01') && (cVar2 == '\0')) {
      *(undefined1 *)(in_ECX + 0x20) = 1;
    }
    if (*(char *)((int)in_ECX + 0xd1) != '\0') {
      if (iVar5 == 0) {
        in_ECX[0x22] = 0;
        in_ECX[0x1c] = 0x50;
        if (DAT_0044d034 != 0) {
          piVar4 = in_ECX + 0xc2;
          *piVar4 = *piVar4 - *(int *)(iVar6 + 0x7d70);
          if (*piVar4 < 0) {
            in_ECX[0xc2] = 0;
          }
          else {
            in_ECX[0xd4] = in_ECX[0xd4] + *(int *)(iVar6 + 0x7d70);
          }
        }
      }
      else if (iVar5 % 100 == 1) {
        in_ECX[0x22] = 0;
        if ((*(char *)((int)in_ECX + 0xcf) == '\0') &&
           (((cVar2 == '\0' && (*(char *)((int)in_ECX + 0xcd) == '\0')) &&
            (*(char *)((int)in_ECX + 0xce) == '\0')))) {
          iVar5 = in_ECX[0x26];
          in_ECX[0x1c] = 0x1e;
        }
        else {
          iVar5 = in_ECX[0x26];
LAB_00413b10:
          in_ECX[0x1c] = 0x34;
        }
      }
      else {
        iVar5 = in_ECX[0x26];
        if ((iVar5 == 4) || (iVar5 == 6)) goto LAB_00413b10;
      }
    }
  }
  if ((*(int *)(in_ECX[0x1c] * 0x178 + 0x7ac + iVar6) == 2) && (iVar5 != 2)) {
    in_ECX[0x22] = 0;
    iVar7 = (*in_ECX + 1) % (*(int *)(iVar6 + 0x18) * 4);
    *in_ECX = iVar7;
    if (iVar7 < *(int *)(iVar6 + 0x18) * 3) {
      in_ECX[0x1c] = iVar7 / *(int *)(iVar6 + 0x18) + 9;
    }
    else {
      in_ECX[0x1c] = 10;
    }
    if (((char)in_ECX[0x20] == '\0') &&
       (*(undefined8 *)(in_ECX + 0x10) = *(undefined8 *)(iVar6 + 0x20),
       *(char *)((int)in_ECX + 0xcf) == '\x01')) {
      in_ECX[0x1c] = 0xda;
    }
    if (((char)in_ECX[0x20] == '\x01') &&
       (*(double *)(in_ECX + 0x10) = -*(double *)(iVar6 + 0x20), (char)in_ECX[0x34] == '\x01')) {
      in_ECX[0x1c] = 0xda;
    }
    cVar2 = *(char *)((int)in_ECX + 0xcd);
    if (((cVar2 == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) && (in_ECX[5] == 0)) {
      *(double *)(in_ECX + 0x14) = -*(double *)(iVar6 + 0x28);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.2;
    }
    if (((cVar2 == '\0') && (*(char *)((int)in_ECX + 0xce) == '\x01')) && (in_ECX[5] == 0)) {
      *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(iVar6 + 0x28);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.2;
    }
    if ((*(char *)((int)in_ECX + 0xd1) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbe))) {
      if (iVar5 == 0) {
        if (DAT_0044d034 == 0) {
          in_ECX[0x1c] = 0x55;
        }
        else if (*(int *)(iVar6 + 0x84c8) <= in_ECX[0xc2]) {
          in_ECX[0xc2] = in_ECX[0xc2] - *(int *)(iVar6 + 0x84c8);
          in_ECX[0xd4] = in_ECX[0xd4] + *(int *)(iVar6 + 0x84c8);
          in_ECX[0x1c] = 0x55;
        }
      }
      else if (iVar5 % 100 == 1) {
        if (((*(char *)((int)in_ECX + 0xcf) == '\0') && ((char)in_ECX[0x34] == '\0')) &&
           ((cVar2 == '\0' && (*(char *)((int)in_ECX + 0xce) == '\0')))) {
          in_ECX[0x1c] = 0x23;
        }
        else {
LAB_00413cc6:
          in_ECX[0x1c] = 0x2d;
        }
      }
      else {
        if (in_ECX[0x26] == 4) goto LAB_00413cc6;
        if (in_ECX[0x26] == 6) {
          if ((((*(char *)((int)in_ECX + 0xcf) != '\0') || ((char)in_ECX[0x34] != '\0')) ||
              (cVar2 != '\0')) || (*(char *)((int)in_ECX + 0xce) != '\0')) goto LAB_00413cc6;
          in_ECX[0x1c] = 0x37;
        }
      }
    }
    if ((*(char *)((int)in_ECX + 0xd3) == '\x01') && ('\0' < (char)in_ECX[0x30])) {
      in_ECX[0x1c] = 0x66;
    }
    if ((*(char *)((int)in_ECX + 0xd2) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbf))) {
      FUN_00417090(in_ECX[4],7);
      iVar6 = in_ECX[0xda];
      in_ECX[1] = 0;
      in_ECX[0x1c] = 0xd5;
      *(double *)(in_ECX + 0x10) = (double)((char)in_ECX[0x20] * -2 + 1) * *(double *)(iVar6 + 0x70)
      ;
      *(undefined8 *)(in_ECX + 0x12) = *(undefined8 *)(iVar6 + 0x68);
      if (*(char *)((int)in_ECX + 0xcd) == '\0') {
LAB_00413d5f:
        if (*(char *)((int)in_ECX + 0xce) != '\0') {
          *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(iVar6 + 0x78);
        }
      }
      else if (*(char *)((int)in_ECX + 0xce) == '\0') {
        *(double *)(in_ECX + 0x14) = -*(double *)(iVar6 + 0x78);
      }
      else if (*(char *)((int)in_ECX + 0xcd) == '\0') goto LAB_00413d5f;
    }
  }
  if ((*(int *)(in_ECX[0x1c] * 0x178 + 0x7ac + iVar6) == 2) && (in_ECX[0x26] == 2)) {
    in_ECX[0x22] = 0;
    iVar5 = (*in_ECX + 1) % (*(int *)(iVar6 + 0x18) * 4);
    *in_ECX = iVar5;
    if (iVar5 < *(int *)(iVar6 + 0x18) * 3) {
      in_ECX[0x1c] = iVar5 / *(int *)(iVar6 + 0x18) + 0x10;
    }
    else {
      in_ECX[0x1c] = 0x11;
    }
    if (((char)in_ECX[0x20] == '\0') &&
       (*(undefined8 *)(in_ECX + 0x10) = *(undefined8 *)(iVar6 + 0x40),
       *(char *)((int)in_ECX + 0xcf) == '\x01')) {
      in_ECX[0x1c] = 0x13;
    }
    if (((char)in_ECX[0x20] == '\x01') &&
       (*(double *)(in_ECX + 0x10) = -*(double *)(iVar6 + 0x40), (char)in_ECX[0x34] == '\x01')) {
      in_ECX[0x1c] = 0x13;
    }
    if (((*(char *)((int)in_ECX + 0xcd) == '\x01') && (*(char *)((int)in_ECX + 0xce) == '\0')) &&
       (in_ECX[5] == 0)) {
      *(double *)(in_ECX + 0x14) = -*(double *)(iVar6 + 0x48);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.2;
    }
    if (((*(char *)((int)in_ECX + 0xcd) == '\0') && (*(char *)((int)in_ECX + 0xce) == '\x01')) &&
       (in_ECX[5] == 0)) {
      *(undefined8 *)(in_ECX + 0x14) = *(undefined8 *)(iVar6 + 0x48);
      *(double *)(in_ECX + 0x10) = *(double *)(in_ECX + 0x10) / 1.2;
    }
    if ((*(char *)((int)in_ECX + 0xd1) == '\x01') && ('\0' < *(char *)((int)in_ECX + 0xbe))) {
      in_ECX[0x1c] = 0x32;
    }
  }
  if (in_ECX[0x1c] != 0xd7) goto LAB_00413f8d;
  if ((*(char *)((int)in_ECX + 0xd3) == '\x01') && ('\0' < (char)in_ECX[0x30])) {
    in_ECX[0x1c] = 0x66;
  }
  if (*(char *)((int)in_ECX + 0xd2) != '\0') {
    if ((((char)in_ECX[0x34] != '\0') || (0.001 < *(double *)(in_ECX + 0x10))) &&
       ('\0' < *(char *)((int)in_ECX + 0xbf))) {
      FUN_00417090(in_ECX[4],7);
      in_ECX[0x1c] = (char)in_ECX[0x20] + 0xd5;
      iVar6 = in_ECX[0xda];
      in_ECX[1] = 0;
      *(undefined8 *)(in_ECX + 0x10) = *(undefined8 *)(iVar6 + 0x70);
      *(undefined8 *)(in_ECX + 0x12) = *(undefined8 *)(iVar6 + 0x68);
    }
    if (((*(char *)((int)in_ECX + 0xd2) != '\0') &&
        ((*(char *)((int)in_ECX + 0xcf) != '\0' || (*(double *)(in_ECX + 0x10) < -0.001)))) &&
       ('\0' < *(char *)((int)in_ECX + 0xbf))) {
      FUN_00417090(in_ECX[4],7);
      in_ECX[0x1c] = 0xd6 - (char)in_ECX[0x20];
      iVar6 = in_ECX[0xda];
      in_ECX[1] = 0;
      *(double *)(in_ECX + 0x10) = -*(double *)(iVar6 + 0x70);
      *(undefined8 *)(in_ECX + 0x12) = *(undefined8 *)(iVar6 + 0x68);
    }
  }
  if (*(char *)((int)in_ECX + 0xcd) == '\0') {
LAB_00413f7e:
    if (*(char *)((int)in_ECX + 0xce) == '\0') goto LAB_00413f8d;
    dVar1 = *(double *)(iVar6 + 0x78);
  }
  else {
    if (*(char *)((int)in_ECX + 0xce) != '\0') {
      if (*(char *)((int)in_ECX + 0xcd) != '\0') goto LAB_00413f8d;
      goto LAB_00413f7e;
    }
    dVar1 = -*(double *)(iVar6 + 0x78);
  }
  *(double *)(in_ECX + 0x14) = dVar1;
LAB_00413f8d:
  if (((in_ECX[0x1c] == 0xb6) || (in_ECX[0x1c] == 0xbc)) &&
     ((-1 < in_ECX[200] &&
      (((*(char *)((int)in_ECX + 0xd2) == '\x01' && ('\0' < *(char *)((int)in_ECX + 0xbf))) &&
       (0 < in_ECX[0xbf])))))) {
    cVar2 = (char)in_ECX[0x20];
    if (((cVar2 == '\0') && (*(double *)(in_ECX + 0x10) <= 0.0)) ||
       ((cVar2 == '\x01' &&
        (dVar1 = *(double *)(in_ECX + 0x10), !NAN(dVar1) && 0.0 < dVar1 != (dVar1 == 0.0))))) {
      in_ECX[0x1c] = 100;
    }
    else {
      in_ECX[0x1c] = 0x6c;
    }
    in_ECX[0x22] = 0;
    if (*(double *)(iVar6 + 0x80) < *(double *)(in_ECX + 0x12)) {
      *(undefined8 *)(in_ECX + 0x12) = *(undefined8 *)(iVar6 + 0x80);
    }
    if ((1.0 <= *(double *)(in_ECX + 0x10)) || (*(double *)(in_ECX + 0x10) <= -1.0)) {
      dVar1 = *(double *)(iVar6 + 0x88);
      if (*(double *)(in_ECX + 0x10) <= 0.0) {
        dVar1 = -dVar1;
      }
      *(double *)(in_ECX + 0x10) = dVar1;
    }
    else if (cVar2 == '\x01') {
      *(double *)(in_ECX + 0x10) = *(double *)(iVar6 + 0x88);
    }
    else {
      *(double *)(in_ECX + 0x10) = -*(double *)(iVar6 + 0x88);
    }
  }
  if (*(int *)(in_ECX[0x1c] * 0x178 + 0x7ac + iVar6) == 5) {
    cVar2 = (char)in_ECX[0x34];
    if ((cVar2 == '\x01') && (*(char *)((int)in_ECX + 0xcf) == '\0')) {
      *(undefined1 *)(in_ECX + 0x20) = 0;
    }
    if ((((char)in_ECX[0x20] == '\0') && (in_ECX[0x1c] != 0xd9)) &&
       (*(double *)(in_ECX + 0x10) < 0.0)) {
      in_ECX[0x1c] = 0xd6;
    }
    if ((((char)in_ECX[0x20] == '\0') && (in_ECX[0x1c] != 0xd8)) &&
       (0.0 < *(double *)(in_ECX + 0x10))) {
      in_ECX[0x1c] = 0xd5;
    }
    if ((*(char *)((int)in_ECX + 0xcf) == '\x01') && (cVar2 == '\0')) {
      *(undefined1 *)(in_ECX + 0x20) = 1;
    }
    cVar3 = (char)in_ECX[0x20];
    if (cVar3 == '\x01') {
      if ((in_ECX[0x1c] != 0xd9) && (0.0 < *(double *)(in_ECX + 0x10))) {
        in_ECX[0x1c] = 0xd6;
      }
      if ((in_ECX[0x1c] != 0xd8) && (*(double *)(in_ECX + 0x10) < 0.0)) {
        in_ECX[0x1c] = 0xd5;
      }
    }
    if ((((0.0 < *(double *)(in_ECX + 0x10)) && (cVar3 == '\0')) ||
        ((*(double *)(in_ECX + 0x10) < 0.0 && (cVar3 == '\x01')))) &&
       (*(char *)((int)in_ECX + 0xd1) != '\0')) {
      iVar5 = in_ECX[0x26];
      if (iVar5 == 0) {
        if (DAT_0044d034 == 0) {
          in_ECX[0x1c] = 0x5a;
        }
        else if (*(int *)(iVar6 + 0x8c20) <= in_ECX[0xc2]) {
          in_ECX[0xc2] = in_ECX[0xc2] - *(int *)(iVar6 + 0x8c20);
          in_ECX[0xd4] = in_ECX[0xd4] + *(int *)(iVar6 + 0x8c20);
          in_ECX[0x1c] = 0x5a;
        }
      }
      else if ((iVar5 % 100 == 1) ||
              (((iVar5 == 4 || (iVar5 == 6)) &&
               ((*(char *)((int)in_ECX + 0xcf) != '\0' ||
                (((cVar2 != '\0' || (*(char *)((int)in_ECX + 0xcd) != '\0')) ||
                 (*(char *)((int)in_ECX + 0xce) != '\0')))))))) {
        if ((iVar5 == 4) || (iVar5 == 6)) {
          in_ECX[0x1c] = 0x34;
        }
        else {
          in_ECX[0x1c] = 0x28;
        }
        in_ECX[0x22] = 0;
        *(double *)(in_ECX + 0x12) = *(double *)(in_ECX + 0x12) - 1.0;
      }
    }
  }
  iVar5 = *(int *)(iVar6 + 0x7b8 + in_ECX[0x1c] * 0x178);
  iVar6 = iVar6 + in_ECX[0x1c] * 0x178;
  if (iVar5 < 0x1f5) {
    if (((0 < iVar5) && (*(double *)(in_ECX + 0x10) < (double)iVar5)) &&
       ((char)in_ECX[0x20] == '\0')) {
      *(double *)(in_ECX + 0x10) = (double)iVar5;
    }
    if (((0 < *(int *)(iVar6 + 0x7b8)) &&
        (dVar1 = (double)*(int *)(iVar6 + 0x7b8), -*(double *)(in_ECX + 0x10) < dVar1)) &&
       ((char)in_ECX[0x20] == '\x01')) {
      *(double *)(in_ECX + 0x10) = -dVar1;
    }
    if (((*(int *)(iVar6 + 0x7b8) < 0) &&
        (dVar1 = (double)*(int *)(iVar6 + 0x7b8), dVar1 < *(double *)(in_ECX + 0x10))) &&
       ((char)in_ECX[0x20] == '\0')) {
      *(double *)(in_ECX + 0x10) = dVar1;
    }
    if (((*(int *)(iVar6 + 0x7b8) < 0) &&
        (dVar1 = (double)*(int *)(iVar6 + 0x7b8), dVar1 < -*(double *)(in_ECX + 0x10))) &&
       ((char)in_ECX[0x20] == '\x01')) {
      *(double *)(in_ECX + 0x10) = -dVar1;
    }
  }
  else {
    *(double *)(in_ECX + 0x10) = (double)(iVar5 + -0x226);
  }
  iVar5 = *(int *)(iVar6 + 0x7bc);
  if (iVar5 != 0) {
    if (iVar5 < 0x1f5) {
      dVar1 = (double)iVar5 + *(double *)(in_ECX + 0x12);
    }
    else {
      dVar1 = (double)(iVar5 + -0x226);
    }
    *(double *)(in_ECX + 0x12) = dVar1;
  }
  iVar5 = *(int *)(iVar6 + 0x7c0);
  if (iVar5 != 0) {
    if (500 < iVar5) {
      *(double *)(in_ECX + 0x14) = (double)(iVar5 + -0x226);
      return;
    }
    if ((*(char *)((int)in_ECX + 0xcd) == '\x01') &&
       (*(char *)((int)in_ECX + 0xc5) <= (char)in_ECX[0x31])) {
      *(double *)(in_ECX + 0x14) = -(double)iVar5;
    }
    if ((*(char *)((int)in_ECX + 0xce) == '\x01') &&
       ((char)in_ECX[0x31] <= *(char *)((int)in_ECX + 0xc5))) {
      *(double *)(in_ECX + 0x14) = (double)*(int *)(iVar6 + 0x7c0);
    }
  }
  return;
}
