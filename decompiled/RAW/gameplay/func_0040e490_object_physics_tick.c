/* Function: FUN_0040e490 */
/* Address: 0x0040e490 */

void FUN_0040e490(void)

{
  double dVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int in_ECX;
  
  iVar4 = *(int *)(in_ECX + 0xb4);
  if (iVar4 != 0) {
    if (0 < iVar4) {
      *(int *)(in_ECX + 0xb4) = iVar4 + -1;
    }
    if (*(int *)(in_ECX + 0xb4) < 0) {
      *(int *)(in_ECX + 0xb4) = *(int *)(in_ECX + 0xb4) + 1;
      return;
    }
    return;
  }
  if (*(int *)(in_ECX + 0x98) < 0) {
    return;
  }
  iVar2 = *(int *)(in_ECX + 0x368);
  iVar3 = *(int *)(in_ECX + 0x70) * 0x178;
  iVar4 = iVar3 + iVar2;
  if (*(int *)(iVar3 + 0x82c + iVar2) == 2) {
    return;
  }
  if (((*(double *)(in_ECX + 0x40) <= 0.0) || (*(int *)(in_ECX + 0x3f4) != 1)) &&
     ((0.0 <= *(double *)(in_ECX + 0x40) || (*(int *)(in_ECX + 0x3f0) != 1)))) {
    *(double *)(in_ECX + 0x58) = *(double *)(in_ECX + 0x58) + *(double *)(in_ECX + 0x40);
  }
  if ((*(int *)(iVar2 + 0x6f8) == 4) || (*(int *)(iVar2 + 0x6f4) == 0x78)) {
    *(double *)(in_ECX + 0x58) = *(double *)(in_ECX + 0x40) * 0.2 + *(double *)(in_ECX + 0x58);
  }
  if (*(int *)(iVar2 + 0x6f4) == 0x65) {
    *(double *)(in_ECX + 0x58) = *(double *)(in_ECX + 0x58) - *(double *)(in_ECX + 0x40) * 0.2;
  }
  if (((*(double *)(in_ECX + 0x50) <= 0.0) || (*(int *)(in_ECX + 0x3ec) != 1)) &&
     ((0.0 <= *(double *)(in_ECX + 0x50) || (*(int *)(in_ECX + 1000) != 1)))) {
    *(double *)(in_ECX + 0x68) = *(double *)(in_ECX + 0x68) + *(double *)(in_ECX + 0x50);
  }
  *(undefined4 *)(in_ECX + 0x3ec) = 0;
  *(undefined4 *)(in_ECX + 1000) = 0;
  *(undefined4 *)(in_ECX + 0x3f0) = 0;
  *(undefined4 *)(in_ECX + 0x3f4) = 0;
  if ((*(int *)(iVar2 + 0x6f8) == 3) && (iVar3 = *(int *)(iVar4 + 2000), 0 < iVar3)) {
    *(double *)(in_ECX + 0x68) = (double)(iVar3 + -0x32) + *(double *)(in_ECX + 0x68);
  }
  if (-1 < *(int *)(in_ECX + 0x14)) {
    if ((0.0001 < *(double *)(in_ECX + 0x40)) &&
       (dVar1 = *(double *)(in_ECX + 0x40) - 1.0, *(double *)(in_ECX + 0x40) = dVar1, dVar1 < 0.0001
       )) {
      *(undefined8 *)(in_ECX + 0x40) = 0;
    }
    if ((*(double *)(in_ECX + 0x40) < -0.0001) &&
       (dVar1 = *(double *)(in_ECX + 0x40) + 1.0, *(double *)(in_ECX + 0x40) = dVar1, 0.0001 < dVar1
       )) {
      *(undefined8 *)(in_ECX + 0x40) = 0;
    }
    if ((0.0001 < *(double *)(in_ECX + 0x50)) &&
       (dVar1 = *(double *)(in_ECX + 0x50) - 1.0, *(double *)(in_ECX + 0x50) = dVar1, dVar1 < 0.0001
       )) {
      *(undefined8 *)(in_ECX + 0x50) = 0;
    }
    if ((*(double *)(in_ECX + 0x50) < -0.0001) &&
       (dVar1 = *(double *)(in_ECX + 0x50) + 1.0, *(double *)(in_ECX + 0x50) = dVar1, 0.0001 < dVar1
       )) {
      *(undefined8 *)(in_ECX + 0x50) = 0;
    }
  }
  if ((((*(int *)(iVar2 + 0x6f8) == 4) || (*(int *)(iVar2 + 0x6f8) == 6)) &&
      (*(int *)(iVar4 + 0x7ac) == 1000)) &&
     ((9.0 < *(double *)(in_ECX + 0x40) || (*(double *)(in_ECX + 0x40) < -9.0)))) {
    *(undefined4 *)(in_ECX + 0x70) = 0x28;
  }
  dVar1 = *(double *)(in_ECX + 0x60) + *(double *)(in_ECX + 0x48);
  *(double *)(in_ECX + 0x60) = dVar1;
  if (dVar1 < -0.0001) {
    iVar4 = *(int *)(iVar2 + 0x6f8);
    if (iVar4 != 3) {
      if (iVar4 == 6) {
        dVar1 = *(double *)(in_ECX + 0x48) + 1.1333333333333333;
      }
      else if (iVar4 == 4) {
        dVar1 = *(double *)(in_ECX + 0x48) + 0.85;
      }
      else if (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 0x3ea) {
        if (*(int *)(iVar2 + 0x6f4) == 0x7c) {
          dVar1 = *(double *)(in_ECX + 0x48) + 0.16999999999999998;
        }
        else if (*(int *)(iVar2 + 0x6f4) == 0x78) {
          dVar1 = *(double *)(in_ECX + 0x48) + 0.425;
        }
        else if (*(int *)(iVar2 + 0x6f4) == 0x65) {
          dVar1 = *(double *)(in_ECX + 0x48) + 1.1333333333333333;
        }
        else {
          dVar1 = *(double *)(in_ECX + 0x48) + 0.5666666666666667;
        }
      }
      else {
        dVar1 = *(double *)(in_ECX + 0x48) + 1.7;
      }
      *(double *)(in_ECX + 0x48) = dVar1;
    }
    if (*(int *)(iVar2 + 0x6f8) == 0) {
      iVar4 = *(int *)(in_ECX + 0x70);
      if (*(int *)(iVar4 * 0x178 + 0x7ac + iVar2) == 0xc) {
        if (iVar4 < 0xb9) {
          if (-8.0 <= *(double *)(in_ECX + 0x48)) {
            if (1.0 <= *(double *)(in_ECX + 0x48)) {
              if (8.0 <= *(double *)(in_ECX + 0x48)) {
                *(undefined4 *)(in_ECX + 0x70) = 0xb7;
              }
              else {
                *(undefined4 *)(in_ECX + 0x70) = 0xb6;
              }
            }
            else {
              *(undefined4 *)(in_ECX + 0x70) = 0xb5;
            }
          }
          else {
            *(undefined4 *)(in_ECX + 0x70) = 0xb4;
          }
          if (*(int *)(in_ECX + 800) < 0) {
            dVar1 = *(double *)(in_ECX + 0x48);
            if ((NAN(dVar1) || 12.0 < dVar1 == (dVar1 == 12.0)) && (5 < DAT_00450bd0)) {
              *(undefined4 *)(in_ECX + 0x70) = 0xb6;
            }
            else {
              *(undefined4 *)(in_ECX + 0x70) = 0xb5;
            }
          }
        }
        else if ((iVar4 < 0xbf) && (0xb9 < iVar4)) {
          if (-8.0 <= *(double *)(in_ECX + 0x48)) {
            if (1.0 <= *(double *)(in_ECX + 0x48)) {
              if (8.0 <= *(double *)(in_ECX + 0x48)) {
                *(undefined4 *)(in_ECX + 0x70) = 0xbd;
              }
              else {
                *(undefined4 *)(in_ECX + 0x70) = 0xbc;
              }
            }
            else {
              *(undefined4 *)(in_ECX + 0x70) = 0xbb;
            }
          }
          else {
            *(undefined4 *)(in_ECX + 0x70) = 0xba;
          }
        }
      }
      if (((*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2) == 0x12) &&
          (*(int *)(in_ECX + 0x70) < 0xcd)) && (1.0 < *(double *)(in_ECX + 0x48))) {
        *(undefined4 *)(in_ECX + 0x70) = 0xcd;
      }
    }
    goto LAB_0040ef22;
  }
  iVar3 = *(int *)(in_ECX + 0x70) * 0x178;
  iVar4 = iVar3 + iVar2;
  if (*(int *)(iVar3 + 0x82c + iVar2) == 2) goto LAB_0040ef22;
  iVar3 = *(int *)(iVar2 + 0x6f8);
  if (iVar3 != 0) {
    if (iVar3 == 1) {
      if ((dVar1 <= 0.0001) || (*(double *)(in_ECX + 0x48) <= 0.0001)) goto LAB_0040ef22;
      iVar3 = *(int *)(iVar2 + 0x94);
      *(undefined8 *)(in_ECX + 0x60) = 0;
      *(int *)(in_ECX + 0x31c) = *(int *)(in_ECX + 0x31c) - iVar3;
      if (*(double *)(in_ECX + 0x48) <= 9.9) {
        if (*(int *)(iVar4 + 0x7ac) == 0x3ea) {
          *(undefined4 *)(in_ECX + 0x70) = 0x46;
          goto LAB_0040edbf;
        }
      }
      else if (*(int *)(iVar4 + 0x7ac) == 0x3ea) {
        *(undefined4 *)(in_ECX + 0x70) = 7;
        *(undefined8 *)(in_ECX + 0x48) = 0xc020000000000000;
        *(char *)(in_ECX + 0x80) = '\x01' - *(char *)(in_ECX + 0x80);
        dVar1 = *(double *)(in_ECX + 0x40) * 0.5;
        goto LAB_0040ecce;
      }
      *(undefined4 *)(in_ECX + 0x70) = 0x3c;
    }
    else {
      if ((iVar3 == 4) || (iVar3 == 6)) {
        if ((dVar1 <= 0.0001) || (*(double *)(in_ECX + 0x48) <= 0.0001)) goto LAB_0040ef22;
        *(int *)(in_ECX + 0x31c) = *(int *)(in_ECX + 0x31c) - *(int *)(iVar2 + 0x94);
        if ((*(int *)(iVar2 + 0x6f8) == 6) && (*(int *)(in_ECX + 0x2fc) < 1)) {
          *(undefined4 *)(in_ECX + 0x31c) = 0xffffffff;
        }
        *(undefined8 *)(in_ECX + 0x60) = 0;
        if ((((*(double *)(in_ECX + 0x48) <= 8.5) && (-10.0 <= *(double *)(in_ECX + 0x40))) &&
            (*(double *)(in_ECX + 0x40) <= 10.0)) ||
           ((*(int *)(iVar4 + 0x7ac) != 0x3ea && (*(int *)(iVar4 + 0x7ac) != 1000)))) {
          iVar4 = *(int *)(iVar4 + 0x7ac);
          *(undefined8 *)(in_ECX + 0x48) = 0;
          *(undefined4 *)(in_ECX + 0x88) = 0;
          *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) * 0.7;
          if (iVar4 == 0x3ea) {
            *(undefined4 *)(in_ECX + 0x70) = 0x46;
          }
          else {
            *(undefined4 *)(in_ECX + 0x70) = 0x3c;
          }
          goto LAB_0040ef22;
        }
        *(undefined4 *)(in_ECX + 0x70) = 0;
        dVar1 = *(double *)(in_ECX + 0x48) * -0.7;
        *(double *)(in_ECX + 0x48) = dVar1;
        if (-10.0 <= dVar1) {
          dVar1 = *(double *)(in_ECX + 0x40) * 0.7;
        }
        else {
          *(undefined8 *)(in_ECX + 0x48) = 0xc024000000000000;
          dVar1 = *(double *)(in_ECX + 0x40) * 0.7;
        }
LAB_0040ecce:
        *(double *)(in_ECX + 0x40) = dVar1;
        if (-1 < *(int *)(iVar2 + 0xa8)) {
          FUN_00416fb0(*(undefined4 *)(in_ECX + 0x10),*(int *)(iVar2 + 0xa8));
        }
        goto LAB_0040ef22;
      }
      if (iVar3 != 2) {
        if ((*(int *)(iVar2 + 0x6f4) == 999) && (-0.0001 < dVar1)) {
          *(undefined8 *)(in_ECX + 0x60) = 0;
          *(undefined4 *)(in_ECX + 0x70) = 0x65;
          *(undefined8 *)(in_ECX + 0x48) = 0;
          *(undefined4 *)(in_ECX + 0x88) = 0;
          *(undefined8 *)(in_ECX + 0x40) = 0;
        }
        goto LAB_0040ef22;
      }
      if (dVar1 <= 0.0001) goto LAB_0040ef22;
      *(int *)(in_ECX + 0x31c) = *(int *)(in_ECX + 0x31c) + -1;
      *(undefined8 *)(in_ECX + 0x60) = 0;
      if (9.0 < *(double *)(in_ECX + 0x48)) {
        if (-1 < *(int *)(iVar2 + 0xa8)) {
          FUN_00416fb0(*(undefined4 *)(in_ECX + 0x10),*(int *)(iVar2 + 0xa8));
        }
        *(undefined8 *)(in_ECX + 0x48) = 0xc014000000000000;
        *(char *)(in_ECX + 0x80) = '\x01' - *(char *)(in_ECX + 0x80);
        *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) * 0.5;
        goto LAB_0040ef22;
      }
      iVar4 = *(int *)(in_ECX + 0x31c) - *(int *)(iVar2 + 0x94);
      *(int *)(in_ECX + 0x31c) = iVar4;
      if (iVar4 < 0) {
        *(undefined4 *)(in_ECX + 0x31c) = 0;
      }
      *(undefined4 *)(in_ECX + 0x70) = 0x14;
    }
LAB_0040edbf:
    *(undefined8 *)(in_ECX + 0x48) = 0;
    *(undefined4 *)(in_ECX + 0x88) = 0;
    *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) * 0.5;
    goto LAB_0040ef22;
  }
  if (((0.0001 < dVar1) && (0.0001 < *(double *)(in_ECX + 0x48))) &&
     (*(int *)(iVar4 + 0x7ac) == 0xd)) {
    if (((17.0 < *(double *)(in_ECX + 0x48)) || (9.0 < *(double *)(in_ECX + 0x40))) ||
       (*(double *)(in_ECX + 0x40) < -9.0)) {
      if (*(int *)(in_ECX + 0x340) == 0) {
        *(int *)(in_ECX + 0x2fc) = *(int *)(in_ECX + 0x2fc) + -10;
      }
      else {
        *(int *)(in_ECX + 0x2fc) =
             *(int *)(in_ECX + 0x2fc) + (int)(-1000 / (longlong)*(int *)(in_ECX + 0x340));
      }
      *(undefined8 *)(in_ECX + 0x60) = 0;
      *(undefined8 *)(in_ECX + 0x48) = 0xc00c000000000000;
      if (7.0 < *(double *)(in_ECX + 0x40)) {
        *(undefined8 *)(in_ECX + 0x40) = 0x401c000000000000;
      }
      if (*(double *)(in_ECX + 0x40) < -7.0) {
        *(undefined8 *)(in_ECX + 0x40) = 0xc01c000000000000;
      }
      *(undefined4 *)(in_ECX + 0x70) = 0xb9;
    }
    else {
      *(undefined8 *)(in_ECX + 0x60) = 0;
      *(undefined8 *)(in_ECX + 0x48) = 0;
      *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) / 3.0;
    }
  }
  if (((*(double *)(in_ECX + 0x60) <= 0.0) || (*(double *)(in_ECX + 0x48) != 0.0)) ||
     (*(int *)(in_ECX + 0x70) != 0xd4)) {
    if ((0.0001 < *(double *)(in_ECX + 0x60)) && (0.0001 < *(double *)(in_ECX + 0x48))) {
      iVar4 = *(int *)(in_ECX + 0x70);
      iVar3 = *(int *)(iVar4 * 0x178 + 0x7ac + iVar2);
      if ((iVar3 != 0xc) && (iVar3 != 0x12)) goto LAB_0040ea4f;
    }
    if (((0.0001 < *(double *)(in_ECX + 0x60)) && (0.0001 < *(double *)(in_ECX + 0x48))) &&
       ((iVar4 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + iVar2), iVar4 == 0xc ||
        (iVar4 == 0x12)))) {
      FUN_00417090(*(undefined4 *)(in_ECX + 0x10),6);
      iVar4 = *(int *)(in_ECX + 800);
      if (iVar4 != 0) {
        if (iVar4 < 0) {
          *(int *)(in_ECX + 800) = -iVar4;
        }
        iVar4 = *(int *)(in_ECX + 800);
        if (0 < *(int *)(in_ECX + 0x340)) {
          iVar4 = (iVar4 * 100) / *(int *)(in_ECX + 0x340);
        }
        *(int *)(in_ECX + 0x2fc) = *(int *)(in_ECX + 0x2fc) - iVar4;
        *(int *)(in_ECX + 0x300) = *(int *)(in_ECX + 0x300) - iVar4;
        *(undefined4 *)(in_ECX + 800) = 0;
      }
      if ((((11.0 < *(double *)(in_ECX + 0x48)) || (9.0 < *(double *)(in_ECX + 0x40))) ||
          (*(double *)(in_ECX + 0x40) < -9.0)) ||
         (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + *(int *)(in_ECX + 0x368)) == 0x12)) {
        *(undefined8 *)(in_ECX + 0x60) = 0;
        *(undefined8 *)(in_ECX + 0x48) = 0xc00c000000000000;
        if (7.0 < *(double *)(in_ECX + 0x40)) {
          *(undefined8 *)(in_ECX + 0x40) = 0x401c000000000000;
        }
        if (*(double *)(in_ECX + 0x40) < -7.0) {
          *(undefined8 *)(in_ECX + 0x40) = 0xc01c000000000000;
        }
        if ((*(int *)(in_ECX + 0x70) < 0xba) ||
           (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + *(int *)(in_ECX + 0x368)) == 0x12)) {
          *(undefined4 *)(in_ECX + 0x70) = 0xb9;
        }
        else {
          *(undefined4 *)(in_ECX + 0x70) = 0xbf;
        }
      }
      else {
        *(undefined8 *)(in_ECX + 0x60) = 0;
        *(undefined8 *)(in_ECX + 0x48) = 0;
        *(undefined4 *)(in_ECX + 0x88) = 0;
        *(uint *)(in_ECX + 0x70) = (0xb9 < *(int *)(in_ECX + 0x70)) + 0xe6;
        *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) / 3.0;
      }
    }
  }
  else {
    iVar4 = 0xd4;
LAB_0040ea4f:
    *(undefined8 *)(in_ECX + 0x60) = 0;
    *(undefined8 *)(in_ECX + 0x48) = 0;
    *(double *)(in_ECX + 0x40) = *(double *)(in_ECX + 0x40) / 3.0;
    iVar2 = *(int *)(iVar4 * 0x178 + 0x7ac + iVar2);
    if (iVar2 == 100) {
      *(undefined4 *)(in_ECX + 0x70) = 0x5e;
      *(undefined4 *)(in_ECX + 0x88) = 0;
    }
    else if ((iVar4 == 0xd4) || (iVar2 == 6)) {
      *(undefined4 *)(in_ECX + 0x70) = 0xd7;
      *(undefined4 *)(in_ECX + 0x88) = 0;
    }
    else {
      *(undefined4 *)(in_ECX + 0x70) = 0xdb;
      *(undefined4 *)(in_ECX + 0x88) = 0;
    }
  }
LAB_0040ef22:
  uVar5 = FUN_004450d0();
  *(undefined4 *)(in_ECX + 0x10) = uVar5;
  uVar5 = FUN_004450d0();
  *(undefined4 *)(in_ECX + 0x14) = uVar5;
  uVar5 = FUN_004450d0();
  *(undefined4 *)(in_ECX + 0x18) = uVar5;
  if (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ac + *(int *)(in_ECX + 0x368)) != 0xc) {
    *(undefined4 *)(in_ECX + 800) = 0;
  }
  return;
}
