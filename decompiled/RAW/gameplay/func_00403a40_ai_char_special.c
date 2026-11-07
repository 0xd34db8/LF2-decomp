/* Function: FUN_00403a40 */
/* Address: 0x00403a40 */

undefined4
FUN_00403a40(int param_1,int *param_2,undefined4 param_3,int param_4,int *param_5,int param_6,
            int *param_7)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int in_ECX;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  int extraout_ECX_08;
  int extraout_ECX_09;
  int extraout_ECX_10;
  int extraout_ECX_11;
  int extraout_ECX_12;
  int extraout_ECX_13;
  int extraout_ECX_14;
  int extraout_ECX_15;
  int extraout_ECX_16;
  int extraout_ECX_17;
  int extraout_ECX_18;
  int extraout_ECX_19;
  int extraout_ECX_20;
  int extraout_ECX_21;
  int extraout_ECX_22;
  int extraout_ECX_23;
  int extraout_ECX_24;
  int extraout_ECX_25;
  int extraout_ECX_26;
  int extraout_ECX_27;
  int extraout_ECX_28;
  int extraout_ECX_29;
  int extraout_ECX_30;
  int extraout_ECX_31;
  int extraout_ECX_32;
  int extraout_ECX_33;
  int extraout_ECX_34;
  int extraout_ECX_35;
  int extraout_ECX_36;
  int extraout_ECX_37;
  int extraout_ECX_38;
  int extraout_ECX_39;
  int extraout_ECX_40;
  int extraout_ECX_41;
  int extraout_ECX_42;
  int extraout_ECX_43;
  int extraout_ECX_44;
  int extraout_ECX_45;
  int extraout_ECX_46;
  int extraout_ECX_47;
  int extraout_ECX_48;
  int extraout_ECX_49;
  int extraout_ECX_50;
  int extraout_ECX_51;
  int extraout_ECX_52;
  int extraout_ECX_53;
  int extraout_ECX_54;
  int extraout_ECX_55;
  int extraout_ECX_56;
  int extraout_ECX_57;
  int extraout_ECX_58;
  int extraout_ECX_59;
  int extraout_ECX_60;
  int extraout_ECX_61;
  int extraout_ECX_62;
  int extraout_ECX_63;
  int extraout_ECX_64;
  int extraout_ECX_65;
  int extraout_ECX_66;
  int extraout_ECX_67;
  int extraout_ECX_68;
  int extraout_ECX_69;
  int extraout_ECX_70;
  int extraout_ECX_71;
  int extraout_ECX_72;
  int extraout_ECX_73;
  int extraout_ECX_74;
  int extraout_ECX_75;
  int extraout_ECX_76;
  int extraout_ECX_77;
  int extraout_EDX;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int local_4;
  
  iVar7 = (int)param_2;
  iVar2 = FUN_00417170(0x3c,DAT_0044f618 + 1);
  if (0 < iVar2) {
    return 0;
  }
  iVar2 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 2) {
    iVar2 = FUN_00417170(0x3d,10);
    if (((iVar2 == 0) &&
        (iVar2 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4), 0x15e < *(int *)(iVar2 + 0x308))) &&
       (((*(int *)(iVar2 + 0x2fc) < *(int *)(iVar2 + 0x300) + -0x46 &&
         (*(int *)(iVar2 + 0x2fc) < 0x8c)) ||
        ((iVar4 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4),
         *(int *)(iVar4 + 0x2fc) < (*(int *)(iVar4 + 0x300) * 3) / 5 &&
         (0x8b < *(int *)(iVar2 + 0x2fc))))))) goto LAB_004055e4;
    if ((param_6 < 10000) &&
       ((iVar2 = FUN_00417170(0x3e,0x1e), iVar2 == 0 &&
        (iVar2 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4), 0xfa < *(int *)(iVar2 + 0x308)))))
    goto LAB_004052f7;
    iVar2 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368) + 0x6f4);
    if ((iVar2 == 2) ||
       ((((iVar2 == 9 || (iVar2 == 10)) || (iVar2 == 0xb)) || ((iVar2 == 0x21 || (iVar2 == 0x22)))))
       ) {
      iVar2 = FUN_00417170(0x3f,0xf);
      if (iVar2 == 0) {
        iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
        iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + (int)param_2 * 4) + 0x10);
        uVar8 = FUN_004034e0(iVar4 - iVar2);
        if ((100 < (int)uVar8) && ((int)uVar8 < 500)) {
          uVar8 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_01 + 0x18));
          if (((int)uVar8 < 0x1e) &&
             ((100 < *(int *)(extraout_ECX_02 + 0x308) &&
              (0xdc < *(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x308))))) {
            iVar3 = extraout_ECX_02;
            if (param_5 == (int *)0x0) goto LAB_00403c0e;
          }
        }
      }
LAB_00403ca1:
      iVar2 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4);
      if ((((*(int *)(iVar2 + 0x98) == 0) || (*(int *)(iVar2 + 0x70) < 9)) &&
          ((iVar4 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4),
           *(int *)(iVar4 + 0x300) + -0x46 <= *(int *)(iVar4 + 0x2fc) ||
           (0x8b < *(int *)(iVar2 + 0x2fc))))) &&
         (((iVar4 = *(int *)(in_ECX + 0x194 + (int)param_2 * 4),
           (*(int *)(iVar4 + 0x300) * 3) / 5 <= *(int *)(iVar4 + 0x2fc) ||
           (*(int *)(iVar2 + 0x2fc) < 0x8c)) && (param_7 == (int *)0x0)))) {
        param_2 = (int *)(in_ECX + 0x194);
        param_5 = (int *)0x0;
        do {
          if ((param_5 != (int *)iVar7) && (*(char *)(in_ECX + 4 + (int)param_5) != '\0')) {
            iVar4 = *param_2;
            if ((*(int *)(iVar4 + 0x364) != 0) &&
               (*(int *)(iVar4 + 0x364) == *(int *)(iVar2 + 0x364))) {
              local_4 = FUN_004034e0(*(int *)(iVar4 + 0x10) - *(int *)(iVar2 + 0x10));
              iVar2 = extraout_ECX_03;
              if (local_4 < 0xfa) {
                iVar3 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(extraout_ECX_03 + 0x18));
                iVar2 = extraout_ECX_04;
                if (((iVar3 < 0x3c) && (0x15e < *(int *)(extraout_ECX_04 + 0x308))) &&
                   (((((*(int *)(iVar4 + 0x2fc) < *(int *)(iVar4 + 0x300) + -0x5a &&
                       (iVar5 = *(int *)(iVar4 + 0x2fc), iVar5 < 0x8c)) ||
                      ((*(int *)(*param_2 + 0x2fc) < (*(int *)(*param_2 + 0x300) * 3) / 5 &&
                       (iVar5 = *(int *)(iVar4 + 0x2fc), 0x8b < iVar5)))) && (0 < iVar5)) &&
                    (iVar3 + local_4 < param_6 / 3)))) {
                  if (*(int *)(extraout_ECX_04 + 0x10) <
                      *(int *)(*(int *)(in_ECX + 0x194 + (int)param_5 * 4) + 0x10)) {
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd0) = 1;
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcf) = 0;
                  }
                  else {
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd0) = 0;
                    *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcf) = 1;
                  }
                  iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
                  iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + (int)param_5 * 4) + 0x10);
                  iVar4 = *(int *)(iVar7 + 0x10);
                  if ((((iVar4 < iVar2) && (*(char *)(iVar7 + 0x80) == '\0')) ||
                      ((iVar2 < iVar4 && (*(char *)(iVar7 + 0x80) == '\x01')))) ||
                     (iVar2 = FUN_004034e0(iVar2 - iVar4), iVar2 < 5)) {
                    *(undefined1 *)(iVar7 + 0xda) = 3;
                  }
                  return 1;
                }
              }
            }
          }
          param_5 = (int *)((int)param_5 + 1);
          param_2 = param_2 + 1;
        } while ((int)param_5 < 0x14);
      }
      goto LAB_00403e83;
    }
    iVar2 = FUN_00417170(0x40,0xf);
    if (iVar2 != 0) goto LAB_00403ca1;
    iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
    iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + (int)param_2 * 4) + 0x10);
    uVar8 = FUN_004034e0(iVar4 - iVar2);
    if (((int)uVar8 < 0x65) || (0xf9 < (int)uVar8)) goto LAB_00403ca1;
    uVar8 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                         *(int *)(extraout_ECX + 0x18));
    if ((0x1d < (int)uVar8) ||
       ((*(int *)(extraout_ECX_00 + 0x308) < 0x65 ||
        (*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x308) < 0xab)))) goto LAB_00403ca1;
    iVar3 = extraout_ECX_00;
    if (param_5 != (int *)0x0) goto LAB_00403ca1;
LAB_00403c0e:
    param_2 = (int *)iVar4;
    if (iVar2 < (int)param_2) {
      *(undefined1 *)(iVar3 + 0xd8) = 3;
      return 1;
    }
    goto LAB_00405f01;
  }
LAB_00403e83:
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 1) {
    if ((0x103 < *(int *)(iVar2 + 0x70)) && (*(int *)(iVar2 + 0x70) < 0x122)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((int)uVar8 < 100) {
        uVar8 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_05 + 0x18));
        if ((int)uVar8 < 7) {
          if ((((*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x14) == 0) &&
               (*(int *)(extraout_ECX_06 + 0x14) == 0)) &&
              (iVar2 = FUN_00417170(0x41,3), iVar2 == 0)) ||
             (((*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) < 0 &&
               (*(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x14) < 0)) &&
              (iVar2 = FUN_00417170(0x42,7), iVar2 == 0)))) {
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd1) = 1;
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xca) = 0;
            return 1;
          }
          if (((*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) < 0) &&
              (iVar2 = FUN_00417170(0x43,5), iVar2 == 0)) ||
             (iVar2 = FUN_00417170(0x44,0x1e), iVar2 == 0)) {
            iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
            iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
            if (((*(int *)(iVar2 + 0x10) < iVar4) && (*(char *)(iVar2 + 0x80) == '\0')) ||
               ((iVar4 < *(int *)(iVar2 + 0x10) && (*(char *)(iVar2 + 0x80) == '\x01')))) {
              *(undefined1 *)(iVar2 + 0xd2) = 1;
            }
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcb) = 0;
          }
          return 1;
        }
      }
    }
    iVar2 = FUN_00417170(0x45,7);
    if (iVar2 != 0) {
LAB_004040f2:
      iVar2 = FUN_00417170(0x48,7);
      if (iVar2 == 0) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
        if ((((int)uVar8 < 100) &&
            (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                  *(int *)(extraout_ECX_09 + 0x18)), iVar2 < 7)) &&
           (0x4b < *(int *)(extraout_ECX_10 + 0x308))) {
          if ((*(int *)(extraout_ECX_10 + 0x308) < 0x97) ||
             (((iVar2 = FUN_00417170(0x49,10), iVar2 != 0 || (param_4 == 3)) &&
              ((iVar2 = FUN_00417170(0x4a,3), iVar2 < 1 || (param_4 != 0x10)))))) {
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd7) = 3;
            return 1;
          }
          iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
          if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
            *(undefined1 *)(iVar7 + 0xd8) = 3;
            return 1;
          }
          *(undefined1 *)(iVar7 + 0xd9) = 3;
          return 1;
        }
      }
      goto LAB_004041e4;
    }
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
    if ((((0x95 < (int)uVar8) ||
         (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_07 + 0x18)), 7 < iVar2)) ||
        (*(int *)(extraout_ECX_08 + 0x308) < 0x97)) ||
       (((iVar2 = FUN_00417170(0x46,10), iVar2 != 0 || (param_4 == 3)) &&
        ((iVar2 = FUN_00417170(0x47,3), iVar2 < 1 ||
         (((param_4 != 0x10 && (param_4 != 8)) && (param_4 != 0xb)))))))) goto LAB_004040f2;
LAB_00404a75:
    iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
      *(undefined1 *)(iVar7 + 0xd8) = 3;
      return 1;
    }
    goto LAB_00406175;
  }
LAB_004041e4:
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 4) {
    if (0x168 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((int)uVar8 < 100) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_11 + 0x18)), iVar2 < 0x46)) &&
         (iVar2 = FUN_00417170(0x4b,*(int *)(extraout_ECX_12 + 0x2fc) / 5 + 10), iVar2 == 0)) {
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xda) = 3;
        return 1;
      }
    }
    iVar2 = FUN_00417170(0x4c,0x2d);
    if (iVar2 == 0) {
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
      uVar8 = FUN_004034e0(iVar4 - iVar2);
      if (((100 < (int)uVar8) && ((int)uVar8 < 0x226)) &&
         (iVar3 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_13 + 0x18)), iVar3 < 0x14)) {
        iVar3 = extraout_ECX_14;
        if (0xaa < *(int *)(extraout_ECX_14 + 0x308)) goto LAB_00403c0e;
      }
    }
    iVar2 = FUN_00417170(0x4d,0x1e);
    if ((iVar2 == 0) &&
       (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 200 < *(int *)(iVar2 + 0x308))) {
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = FUN_004034e0(iVar4 - iVar2);
      if ((100 < (int)uVar8) &&
         (((int)uVar8 < 0xa0 &&
          (iVar3 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_15 + 0x18)), iVar3 < 0x37)))) {
        iVar3 = extraout_ECX_16;
        if (((*(char *)(extraout_ECX_16 + 0x80) == '\0') && (iVar2 < iVar4)) ||
           ((*(char *)(extraout_ECX_16 + 0x80) == '\x01' && (iVar4 < iVar2)))) goto LAB_00405d7d;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 5) {
    if (0x1c2 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if (((100 < (int)uVar8) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_17 + 0x18)), 0x32 < iVar2)) &&
         (iVar2 = FUN_00417170(0x4e,3), iVar2 == 0)) {
        iVar2 = FUN_00417170(0x4f,2);
        if (iVar2 == 0) {
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xda) = 3;
          return 1;
        }
        iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        goto LAB_004043fe;
      }
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (0x46 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if (((100 < (int)uVar8) && ((int)uVar8 < 0xa0)) &&
         ((iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_18 + 0x18)), iVar2 < 8 &&
          (iVar2 = FUN_00417170(0x50,10), iVar2 == 0)))) goto LAB_00404a75;
    }
    iVar2 = FUN_00417170(0x51,0x1e);
    if ((iVar2 == 0) &&
       (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 200 < *(int *)(iVar2 + 0x308))) {
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar8 = FUN_004034e0(iVar4 - iVar2);
      if ((100 < (int)uVar8) &&
         (((int)uVar8 < 0xa0 &&
          (iVar3 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_19 + 0x18)), iVar3 < 0x37)))) {
        iVar3 = extraout_ECX_20;
        if ((*(char *)(extraout_ECX_20 + 0x80) == '\0') && (iVar2 < iVar4)) goto LAB_00405e75;
        if ((*(char *)(extraout_ECX_20 + 0x80) == '\x01') && (iVar4 < iVar2)) goto LAB_00405e8b;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 6) {
    if (100 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((0x50 < (int)uVar8) && ((int)uVar8 < 0x82)) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_21 + 0x18)), iVar2 < 0x1e)) &&
         (iVar2 = FUN_00417170(0x52,10), iVar2 == 0)) goto LAB_00404a75;
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (*(int *)(iVar2 + 0x308) < 0x65) {
LAB_004045b0:
      iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      if ((*(int *)(*(int *)(iVar2 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar2 + 0x368)) == 9) &&
         (iVar2 = FUN_00417170(0x54,8), iVar2 == 0)) {
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd2) = 1;
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcb) = 0;
      }
      goto LAB_004045fc;
    }
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(iVar2 + 0x10));
    if (((0x2c < (int)uVar8) ||
        (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                              *(int *)(extraout_ECX_22 + 0x18)), 4 < iVar2)) ||
       (iVar2 = FUN_00417170(0x53,3), iVar2 != 0)) goto LAB_004045b0;
LAB_00405a3e:
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    goto LAB_00405a45;
  }
LAB_004045fc:
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 7) {
    if ((0x10b < *(int *)(iVar2 + 0x70)) && (*(int *)(iVar2 + 0x70) < 0x11b)) {
      if ((param_4 == 0xc) || (param_4 == 0xb)) goto LAB_00404abb;
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar3 = *(int *)(iVar2 + 0x10);
      uVar8 = FUN_004034e0(iVar4 - iVar3);
      if ((((0x96 < (int)uVar8) ||
           (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                 *(int *)(extraout_ECX_23 + 0x18)), 0x19 < iVar2)) ||
          ((*(char *)(extraout_ECX_24 + 0x80) == '\0' && (iVar3 < iVar4)))) ||
         ((iVar2 = extraout_ECX_24, *(char *)(extraout_ECX_24 + 0x80) == '\x01' && (iVar4 < iVar3)))
         ) goto LAB_00404abb;
    }
    if ((param_4 != 0x12) && (param_4 != 0xe)) {
      if (((param_4 != 0xc) && (0x46 < *(int *)(iVar2 + 0x2fc))) &&
         (0x140 < *(int *)(iVar2 + 0x308))) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(iVar2 + 0x10));
        iVar4 = (int)((ulonglong)uVar8 >> 0x20);
        iVar2 = extraout_ECX_25;
        if ((int)uVar8 < 0x33) {
          uVar9 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(extraout_ECX_25 + 0x18));
          iVar4 = (int)((ulonglong)uVar9 >> 0x20);
          iVar2 = extraout_ECX_26;
          if ((int)uVar9 < 0xb) goto LAB_0040473e;
        }
        if ((((int)uVar8 < 0x55) && (*(int *)(iVar4 + 0x2fc) < *(int *)(iVar2 + 0x2fc))) &&
           ((iVar2 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar2 + 0x18)), iVar2 < 0x23 &&
            (iVar2 = FUN_00417170(0x55,5), iVar2 == 0)))) goto LAB_00405a3e;
      }
LAB_0040473e:
      if ((param_4 != 0xc) &&
         (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 200 < *(int *)(iVar2 + 0x308))) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(iVar2 + 0x10));
        if ((100 < (int)uVar8) &&
           ((((int)uVar8 < 0x172 &&
             (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                   *(int *)(extraout_ECX_27 + 0x18)), iVar2 < 0x3c)) &&
            (iVar2 = FUN_00417170(0x56,0x14), iVar2 == 0)))) goto LAB_00404a75;
      }
    }
    iVar2 = FUN_00417170(0x57,100);
    if (((iVar2 == 0) &&
        (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                              *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10)), 0xf0 < iVar2))
       && (iVar2 < 400)) goto LAB_00404a75;
    if (((param_4 != 0x12) && (param_4 != 0xe)) &&
       ((param_4 != 0xc &&
        (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 200 < *(int *)(iVar2 + 0x308))))) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((0x3c < (int)uVar8) && ((int)uVar8 < 0x118)) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_28 + 0x18)), iVar2 < 0x3c)) &&
         (iVar2 = FUN_00417170(0x58,0xf), iVar2 == 0)) {
        iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        if (((*(char *)(iVar2 + 0x80) == '\0') &&
            (*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10))) ||
           ((*(char *)(iVar2 + 0x80) == '\x01' &&
            (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) < *(int *)(iVar2 + 0x10))))) {
          *(undefined1 *)(iVar2 + 0xdb) = 3;
          return 1;
        }
      }
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if ((*(int *)(iVar2 + 0x70) < 0xff) || (0x105 < *(int *)(iVar2 + 0x70))) goto LAB_0040498d;
    if (((*(char *)(iVar2 + 0x80) == '\0') &&
        ((*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) + 0x78 < *(int *)(iVar2 + 0x10) ||
         (DAT_0044f604 + -0x1e < *(int *)(iVar2 + 0x10))))) ||
       ((*(char *)(iVar2 + 0x80) == '\x01' &&
        ((*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) + -0x78
         || (*(int *)(iVar2 + 0x10) < 0x1e)))))) {
LAB_00404abb:
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd3) = 1;
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcc) = 0;
      return 1;
    }
    iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
    iVar2 = *(int *)(iVar2 + 0x18);
    uVar8 = FUN_004034e0(iVar4 - iVar2);
    iVar3 = (int)((ulonglong)uVar8 >> 0x20);
    if ((0x46 < (int)uVar8) || (DAT_0044f608 == 1)) goto LAB_00404abb;
    cVar1 = *(char *)(extraout_ECX_29 + 0x80);
    if (cVar1 == '\0') {
      if (*(int *)(iVar3 + 0x10) <= *(int *)(extraout_ECX_29 + 0x10)) {
        cVar1 = *(char *)(extraout_ECX_29 + 0x80);
        goto LAB_00404968;
      }
LAB_0040497c:
      if (iVar4 <= iVar2) {
LAB_00404aaf:
        *(undefined1 *)(extraout_ECX_29 + 0xcd) = 1;
        goto LAB_0040498d;
      }
    }
    else {
LAB_00404968:
      if ((cVar1 == '\x01') && (*(int *)(iVar3 + 0x10) < *(int *)(extraout_ECX_29 + 0x10)))
      goto LAB_0040497c;
      if (iVar2 <= iVar4) goto LAB_00404aaf;
    }
    *(undefined1 *)(extraout_ECX_29 + 0xce) = 1;
  }
LAB_0040498d:
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 8) {
    if (param_4 == 0xd) {
LAB_00404ae6:
      if ((param_4 != 0xe) &&
         (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 0x140 < *(int *)(iVar2 + 0x308))) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(iVar2 + 0x10));
        iVar4 = (int)((ulonglong)uVar8 >> 0x20);
        iVar2 = extraout_ECX_32;
        if ((int)uVar8 < 0x33) {
          uVar9 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(extraout_ECX_32 + 0x18));
          iVar4 = (int)((ulonglong)uVar9 >> 0x20);
          iVar2 = extraout_ECX_33;
          if (((int)uVar9 < 8) && (param_4 != 0xd)) goto LAB_00404ba5;
        }
        if (((int)uVar8 < 0x7d) &&
           ((iVar2 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar2 + 0x18)), iVar2 < 0x19 &&
            (iVar2 = FUN_00417170(0x5b,3), iVar2 == 0)))) {
          iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
          if (((*(char *)(iVar2 + 0x80) == '\0') &&
              (*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10))) ||
             ((*(char *)(iVar2 + 0x80) == '\x01' &&
              (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) < *(int *)(iVar2 + 0x10)))))
          {
LAB_00405a45:
            *(undefined1 *)(iVar2 + 0xda) = 3;
            return 1;
          }
        }
      }
    }
    else {
      if (200 < *(int *)(iVar2 + 0x308)) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(iVar2 + 0x10));
        if ((((int)uVar8 < 400) &&
            (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                  *(int *)(extraout_ECX_30 + 0x18)), iVar2 < 0xaa)) &&
           (iVar2 = FUN_00417170(0x59,0xfa), iVar2 == 0)) goto LAB_00404a75;
      }
      if (param_4 != 0xe) {
        iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        if (200 < *(int *)(iVar2 + 0x308)) {
          uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                               *(int *)(iVar2 + 0x10));
          if (((0x3c < (int)uVar8) && ((int)uVar8 < 0x118)) &&
             ((iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                    *(int *)(extraout_ECX_31 + 0x18)), iVar2 < 0x41 &&
              (iVar2 = FUN_00417170(0x5a,0xf), iVar2 == 0)))) goto LAB_00404a75;
        }
        goto LAB_00404ae6;
      }
    }
LAB_00404ba5:
    iVar2 = FUN_00417170(0x5c,0x32);
    if ((iVar2 == 0) &&
       ((iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), *(int *)(iVar2 + 0x98) == 0 &&
        (200 < *(int *)(iVar2 + 0x308))))) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if (200 < (int)uVar8) {
        iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_34 + 0x18));
        iVar2 = extraout_ECX_35;
        if (0x32 < iVar4) {
LAB_004043fe:
          *(undefined1 *)(iVar2 + 0xdb) = 3;
          return 1;
        }
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0xb) {
    if (0x96 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((int)uVar8 < 0x118) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_36 + 0x18)), iVar2 < 0x1e)) &&
         (iVar2 = FUN_00417170(0x5d,10), iVar2 == 0)) {
        iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        if ((*(char *)(iVar2 + 0x80) == '\0') &&
           (*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10))) {
LAB_00404caa:
          *(undefined1 *)(iVar2 + 0xd7) = 3;
          return 1;
        }
        if (*(char *)(iVar2 + 0x80) == '\x01') {
          iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
          if (iVar4 < *(int *)(iVar2 + 0x10)) {
            if (iVar4 <= *(int *)(iVar2 + 0x10)) {
              return 1;
            }
            goto LAB_00404caa;
          }
        }
      }
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if ((*(int *)(*(int *)(iVar2 + 0x70) * 0x178 + 2000 + *(int *)(iVar2 + 0x368)) == 0x122) &&
       (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) < 0)) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcb) = 0;
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd2) = 1;
    }
    iVar2 = FUN_00417170(0x5e,5);
    if (((iVar2 == 0) || (param_4 == 0x10)) || (param_4 == 8)) {
      iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar4 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      iVar3 = *(int *)(iVar2 + 0x10);
      iVar5 = FUN_004450d0();
      iVar5 = FUN_004034e0((iVar5 - *(int *)(iVar4 + 0x10)) + iVar3);
      if (((iVar5 < 100) &&
          (iVar2 = FUN_004034e0(*(int *)(iVar2 + 0x18) - *(int *)(iVar4 + 0x18)), iVar2 < 7)) &&
         (200 < *(int *)(extraout_ECX_37 + 0x308))) {
        iVar2 = extraout_ECX_37;
        if (((*(char *)(extraout_ECX_37 + 0x80) == '\0') &&
            (*(int *)(extraout_ECX_37 + 0x10) < iVar3)) ||
           ((*(char *)(extraout_ECX_37 + 0x80) == '\x01' &&
            (iVar3 < *(int *)(extraout_ECX_37 + 0x10))))) goto LAB_004060e1;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 10) {
    if (100 < *(int *)(iVar2 + 0x308)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((int)uVar8 < 0x118) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_38 + 0x18)), iVar2 < 0x19)) &&
         (iVar2 = FUN_00417170(0x5f,10), iVar2 == 0)) {
        iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
        if ((*(char *)(iVar2 + 0x80) == '\0') &&
           (*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10))) {
LAB_00404e54:
          *(undefined1 *)(iVar2 + 0xd7) = 3;
          return 1;
        }
        if (*(char *)(iVar2 + 0x80) == '\x01') {
          iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
          if (iVar4 < *(int *)(iVar2 + 0x10)) {
            if (iVar4 <= *(int *)(iVar2 + 0x10)) {
              return 1;
            }
            goto LAB_00404e54;
          }
        }
      }
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (((*(int *)(iVar2 + 0x70) == 0x10f) &&
        (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) < 0)) && (param_4 == 0xc)) {
      *(undefined1 *)(iVar2 + 0xd6) = 3;
      return 1;
    }
    iVar2 = FUN_00417170(0x60,10);
    if (((iVar2 == 0) || (param_4 == 0x10)) || (param_4 == 8)) {
      iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar4 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      iVar3 = *(int *)(iVar2 + 0x10);
      iVar5 = FUN_004450d0();
      iVar5 = FUN_004034e0((iVar5 - *(int *)(iVar4 + 0x10)) + iVar3);
      if ((iVar5 < 0x50) &&
         (iVar2 = FUN_004034e0(*(int *)(iVar2 + 0x18) - *(int *)(iVar4 + 0x18)), iVar2 < 7)) {
        iVar2 = extraout_ECX_39;
        if (((*(char *)(extraout_ECX_39 + 0x80) == '\0') &&
            (*(int *)(extraout_ECX_39 + 0x10) < iVar3)) ||
           ((*(char *)(extraout_ECX_39 + 0x80) == '\x01' &&
            (iVar3 < *(int *)(extraout_ECX_39 + 0x10))))) goto LAB_004060e1;
      }
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (*(int *)(iVar2 + 0x308) < 0xc9) {
LAB_00404fd7:
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x2fc);
      if ((((iVar2 < 0xfa) &&
           (iVar2 < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc) + 0x32)) &&
          (iVar2 = FUN_00417170(99,0x14), iVar2 == 0)) &&
         (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 0x4b < *(int *)(iVar2 + 0x308))) {
        param_5 = (int *)(in_ECX + 0x194);
        param_2 = (int *)0xffffffff;
        iVar4 = 0;
        do {
          if (iVar4 != iVar7) {
            if (*(char *)(in_ECX + 4 + iVar4) != '\0') {
              iVar3 = *param_5;
              if (*(int *)(*(int *)(iVar3 + 0x368) + 0x6f8) == 0) {
                if (*(int *)(iVar3 + 0x364) == *(int *)(iVar2 + 0x364)) {
                  if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc) <
                      *(int *)(iVar3 + 0x2fc)) {
                    FUN_004034e0(*(int *)(iVar3 + 0x18) - *(int *)(iVar2 + 0x18));
                    iVar3 = FUN_004034e0(*(int *)(extraout_EDX + 0x10) - *(int *)(iVar2 + 0x10));
                    if ((int)param_2 < extraout_ECX_41 + iVar3) {
                      param_2 = (int *)(extraout_ECX_41 + iVar3);
                      local_4 = iVar4;
                    }
                  }
                }
              }
            }
          }
          param_5 = param_5 + 1;
          iVar4 = iVar4 + 1;
        } while (iVar4 < 400);
        if (((local_4 != -1) && (300 < (int)param_2)) && (*(int *)(iVar2 + 0x98) == 0)) {
          *(undefined1 *)(iVar2 + 0xdb) = 3;
        }
      }
      if (((*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc) <
            *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x2fc)) &&
          (iVar2 = FUN_00417170(100,0x46), iVar2 == 0)) &&
         (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 500 < *(int *)(iVar2 + 0x308))) {
        *(undefined1 *)(iVar2 + 0xda) = 3;
      }
      goto LAB_0040513a;
    }
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(iVar2 + 0x10));
    if (((((int)uVar8 < 0x3d) || (0x117 < (int)uVar8)) ||
        (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                              *(int *)(extraout_ECX_40 + 0x18)), 0x40 < iVar2)) ||
       ((iVar2 = FUN_00417170(0x61,0xf), iVar2 != 0 &&
        ((iVar2 = FUN_00417170(0x62,4), iVar2 != 0 ||
         (((param_4 != 0x10 && (param_4 != 8)) &&
          ((param_4 != 0xc || (-0x29 < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14)))))))
        )))) goto LAB_00404fd7;
LAB_004053de:
    iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
      *(undefined1 *)(iVar7 + 0xd8) = 3;
      return 1;
    }
    goto LAB_00406175;
  }
LAB_0040513a:
  if (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x368) + 0x6f4) == 9) {
    iVar2 = FUN_00417170(0x65,10);
    if (((iVar2 == 0) || (param_4 == 0x10)) || (param_4 == 8)) {
      iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar3 = FUN_004450d0();
      iVar3 = FUN_004034e0((iVar3 - *(int *)(iVar2 + 0x10)) + iVar4);
      if (((iVar3 < 0x78) &&
          (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                                *(int *)(iVar2 + 0x18)), iVar2 < 7)) &&
         (((*(char *)(extraout_ECX_42 + 0x80) == '\0' && (*(int *)(extraout_ECX_42 + 0x10) < iVar4))
          || ((*(char *)(extraout_ECX_42 + 0x80) == '\x01' &&
              (iVar4 < *(int *)(extraout_ECX_42 + 0x10))))))) {
        *(undefined1 *)(extraout_ECX_42 + 0xd7) = 3;
        return 1;
      }
    }
    if ((((param_4 != 0x12) && (param_4 != 0xe)) && (param_4 != 0xc)) &&
       (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 200 < *(int *)(iVar2 + 0x308))) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if (((0x4b < (int)uVar8) && ((int)uVar8 < 0x172)) &&
         ((iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_43 + 0x18)), iVar2 < 0x3c &&
          (iVar2 = FUN_00417170(0x66,0xd), iVar2 == 0)))) goto LAB_004053de;
    }
    iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc);
    iVar2 = FUN_00417170(0x67,((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) + 0x28);
    if (((iVar2 == 0) &&
        (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                              *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10)), 0x96 < iVar2))
       && (iVar2 < 400)) goto LAB_004053de;
    if (((param_6 < 10000) && (iVar2 = FUN_00417170(0x68,0x1e), iVar2 == 0)) &&
       (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 0x96 < *(int *)(iVar2 + 0x308))) {
LAB_004052f7:
      *(undefined1 *)(iVar2 + 0xd6) = 3;
      return 1;
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x20) {
    if (((param_4 != 0x12) && (param_4 != 0xe)) &&
       ((param_4 != 0xc && (200 < *(int *)(iVar2 + 0x308))))) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(iVar2 + 0x10));
      if ((((int)uVar8 < 0x10e) &&
          (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_44 + 0x18)), iVar2 < 0x3c)) &&
         (iVar2 = FUN_00417170(0x69,0x3c), iVar2 == 0)) goto LAB_004053de;
    }
    iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2fc);
    iVar2 = FUN_00417170(0x6a,((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) + 0x28);
    if (((iVar2 == 0) &&
        (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                              *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10)), 0x96 < iVar2))
       && (iVar2 < 400)) goto LAB_004053de;
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
    if ((((int)uVar8 < 0x96) &&
        (iVar2 = FUN_004034e0(*(int *)(extraout_ECX_45 + 0x18) -
                              *(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18)), iVar2 < 0x28)) &&
       (iVar2 = FUN_00417170(0x6b,0xf), iVar2 == 0)) {
      iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
        *(undefined1 *)(iVar7 + 0xd4) = 3;
        return 1;
      }
      *(undefined1 *)(iVar7 + 0xd5) = 3;
      return 1;
    }
  }
  if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x368) + 0x6f4) == 0x21) &&
     (((iVar2 = FUN_00417170(0x6c,5), iVar2 == 0 || (param_4 == 0x10)) || (param_4 == 8)))) {
    iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar4 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    iVar3 = *(int *)(iVar2 + 0x10);
    iVar5 = FUN_004450d0();
    iVar5 = FUN_004034e0((iVar5 - *(int *)(iVar4 + 0x10)) + iVar3);
    if (((iVar5 < 0x3c) &&
        (iVar2 = FUN_004034e0(*(int *)(iVar2 + 0x18) - *(int *)(iVar4 + 0x18)), iVar2 < 7)) &&
       (0x96 < *(int *)(extraout_ECX_46 + 0x308))) {
      iVar2 = extraout_ECX_46;
      if (((*(char *)(extraout_ECX_46 + 0x80) == '\0') && (*(int *)(extraout_ECX_46 + 0x10) < iVar3)
          ) || ((*(char *)(extraout_ECX_46 + 0x80) == '\x01' &&
                (iVar3 < *(int *)(extraout_ECX_46 + 0x10))))) goto LAB_004060e1;
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x22) {
    iVar2 = FUN_00417170(0x6d,10);
    if (((iVar2 == 0) &&
        (iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 0x15e < *(int *)(iVar2 + 0x308))) &&
       (((*(int *)(iVar2 + 0x2fc) < *(int *)(iVar2 + 0x300) + -0x46 &&
         (*(int *)(iVar2 + 0x2fc) < 0x8c)) ||
        ((iVar4 = *(int *)(in_ECX + 0x194 + iVar7 * 4),
         *(int *)(iVar4 + 0x2fc) < (*(int *)(iVar4 + 0x300) * 3) / 5 &&
         (0x8b < *(int *)(iVar2 + 0x2fc))))))) {
LAB_004055e4:
      *(undefined1 *)(iVar2 + 0xdb) = 3;
      return 1;
    }
    iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
    if ((*(int *)(iVar2 + 0x98) == 0) || (*(int *)(iVar2 + 0x70) < 9)) {
      iVar4 = *(int *)(iVar2 + 0x2fc);
      if (((*(int *)(iVar2 + 0x300) + -0x46 <= iVar4) || (0x8b < iVar4)) &&
         ((((*(int *)(iVar2 + 0x300) * 3) / 5 <= iVar4 || (iVar4 < 0x8c)) && (param_7 == (int *)0x0)
          ))) {
        param_7 = (int *)(in_ECX + 0x194);
        param_5 = (int *)0x0;
        do {
          if ((param_5 != (int *)iVar7) && (*(char *)((int)param_5 + 4 + in_ECX) != '\0')) {
            iVar4 = *(int *)(*param_7 + 0x364);
            if (((iVar4 != 0) &&
                ((iVar4 == *(int *)(iVar2 + 0x364) &&
                 (iVar4 = FUN_004034e0(*(int *)(*param_7 + 0x10) - *(int *)(iVar2 + 0x10)),
                 iVar4 < 0xfa)))) &&
               ((iVar3 = FUN_004034e0(*(int *)(extraout_ECX_47 + 0x18) - *(int *)(iVar2 + 0x18)),
                iVar3 < 0x3c && (0x15e < *(int *)(iVar2 + 0x308))))) {
              iVar5 = *(int *)(extraout_ECX_48 + 0x2fc);
              if ((((iVar5 < *(int *)(extraout_ECX_48 + 0x300) + -0x5a) && (iVar5 < 0x8c)) ||
                  ((iVar5 < (*(int *)(extraout_ECX_48 + 0x300) * 3) / 5 && (0x8b < iVar5)))) &&
                 ((0 < iVar5 && (iVar3 + iVar4 < param_6 / 3)))) {
                if (*(int *)(iVar2 + 0x10) <
                    *(int *)(*(int *)(in_ECX + 0x194 + (int)param_5 * 4) + 0x10)) {
                  *(undefined1 *)(iVar2 + 0xd0) = 1;
                  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcf) = 0;
                }
                else {
                  *(undefined1 *)(iVar2 + 0xd0) = 0;
                  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xcf) = 1;
                }
                iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
                iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + (int)param_5 * 4) + 0x10);
                iVar4 = *(int *)(iVar7 + 0x10);
                if ((((iVar4 < iVar2) && (*(char *)(iVar7 + 0x80) == '\0')) ||
                    ((iVar2 < iVar4 && (*(char *)(iVar7 + 0x80) == '\x01')))) ||
                   (iVar2 = FUN_004034e0(iVar2 - iVar4), iVar2 < 5)) {
                  *(undefined1 *)(iVar7 + 0xda) = 3;
                }
                return 1;
              }
            }
          }
          param_7 = param_7 + 1;
          param_5 = (int *)((int)param_5 + 1);
        } while ((int)param_5 < 0x14);
      }
    }
  }
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x32) {
    iVar2 = FUN_00417170(0x6e,7);
    if (iVar2 != 0) {
LAB_00405807:
      iVar2 = FUN_00417170(0x6f,7);
      if (iVar2 == 0) {
        uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                             *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
        if ((((int)uVar8 < 100) &&
            (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                  *(int *)(extraout_ECX_51 + 0x18)), iVar2 < 7)) &&
           (iVar2 = extraout_ECX_52, 0x4b < *(int *)(extraout_ECX_52 + 0x308))) goto LAB_00405866;
      }
      goto LAB_00405917;
    }
    param_2 = *(int **)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
    iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
    uVar8 = FUN_004034e0((int)param_2 - iVar2);
    if ((499 < (int)uVar8) || ((int)uVar8 < 0x5b)) goto LAB_00405807;
    uVar8 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                         *(int *)(extraout_ECX_49 + 0x18));
    if ((3 < (int)uVar8) || (*(int *)(extraout_ECX_50 + 0x308) < 0x97)) goto LAB_00405807;
    iVar4 = *(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x70);
    if ((iVar4 == 0x107) || (iVar3 = extraout_ECX_50, iVar4 == 0x108)) {
      *(undefined1 *)(extraout_ECX_50 + 0xca) = 0;
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd1) = 1;
      goto LAB_00405807;
    }
LAB_00405e6f:
    if (iVar2 < (int)param_2) {
LAB_00405e75:
      *(undefined1 *)(iVar3 + 0xd4) = 3;
      return 1;
    }
LAB_00405e8b:
    *(undefined1 *)(iVar3 + 0xd5) = 3;
    return 1;
  }
LAB_00405917:
  if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x368) + 0x6f4) == 0x23) &&
     (iVar2 = FUN_00417170(0x70,7), iVar2 == 0)) {
    param_2 = *(int **)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
    iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
    uVar8 = FUN_004034e0((int)param_2 - iVar2);
    if ((((int)uVar8 < 0x28a) &&
        ((0x28 < (int)uVar8 &&
         (iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_53 + 0x18)), iVar4 < 4)))) &&
       (iVar3 = extraout_ECX_54, 0x78 < *(int *)(extraout_ECX_54 + 0x308))) goto LAB_00405e6f;
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x24) {
    if ((200 < *(int *)(iVar2 + 0x308)) && (iVar2 = FUN_00417170(0x71,5), iVar2 == 0)) {
      iVar2 = 0;
      piVar6 = (int *)(in_ECX + 0x194);
      do {
        if (((*(char *)(in_ECX + 4 + iVar2) == '\x01') &&
            (iVar4 = *piVar6, *(int *)(*(int *)(iVar4 + 0x368) + 0x6f8) == 0)) &&
           (*(int *)(iVar4 + 0x364) == *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x364))) {
          iVar3 = *(int *)(iVar4 + 0x2fc);
          if ((iVar3 < *(int *)(iVar4 + 0x300) + -200) ||
             ((iVar3 < 200 && (iVar3 < *(int *)(iVar4 + 0x300) + -100)))) goto LAB_00405a3e;
        }
        iVar2 = iVar2 + 1;
        piVar6 = piVar6 + 1;
        if (99 < iVar2) {
          return 1;
        }
      } while( true );
    }
    if ((0x104 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x72,10), iVar2 == 0)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
      if ((int)uVar8 < 0x28a) {
        iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_55 + 0x18));
        iVar2 = extraout_ECX_56;
        if (iVar4 < 0xf0) goto LAB_004060e1;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x26) {
    if ((0x96 < *(int *)(iVar2 + 0x308)) && (iVar2 = FUN_00417170(0x73,5), iVar2 == 0)) {
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
      uVar8 = FUN_004034e0(iVar2 - iVar4);
      if (((int)uVar8 < 0xfa) &&
         ((0x82 < (int)uVar8 &&
          (iVar3 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                                *(int *)(extraout_ECX_57 + 0x18)), iVar3 < 10)))) {
        iVar3 = extraout_ECX_58;
        if (iVar4 < iVar2) {
          *(undefined1 *)(extraout_ECX_58 + 0xd8) = 3;
          return 1;
        }
        goto LAB_00405f01;
      }
    }
    if ((200 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x74,10), iVar2 == 0)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                           *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x18));
      if ((int)uVar8 < 10) {
        iVar3 = extraout_ECX_59;
        if (*(int *)(extraout_ECX_59 + 0x10) < *(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x10)) {
          *(undefined1 *)(extraout_ECX_59 + 0xd4) = 3;
          return 1;
        }
        goto LAB_00405e8b;
      }
    }
    if ((200 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x75,10), iVar2 == 0)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
      iVar2 = extraout_ECX_60;
      if (200 < (int)uVar8) goto LAB_00405df5;
      iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                           *(int *)(extraout_ECX_60 + 0x18));
      iVar2 = extraout_ECX_61;
      if (iVar4 < 0xfa) goto LAB_00405df5;
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x27) {
    if ((100 < *(int *)(iVar2 + 0x308)) && (iVar2 = FUN_00417170(0x76,3), iVar2 == 0)) {
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      uVar8 = FUN_004034e0(iVar2 - *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
      iVar4 = (int)((ulonglong)uVar8 >> 0x20);
      if (((int)uVar8 < 0x78) &&
         (((*(char *)(extraout_ECX_62 + 0x80) == '\0' && (iVar4 < iVar2)) ||
          ((*(char *)(extraout_ECX_62 + 0x80) == '\x01' && (iVar2 < iVar4)))))) {
        iVar4 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                             *(int *)(extraout_ECX_62 + 0x18));
        iVar2 = extraout_ECX_63;
        if (iVar4 < 10) {
LAB_00405866:
          *(undefined1 *)(iVar2 + 0xd7) = 3;
          return 1;
        }
      }
    }
    if ((100 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x77,7), iVar2 == 0)) {
      param_2 = *(int **)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
      uVar8 = FUN_004034e0((int)param_2 - iVar2);
      if ((int)uVar8 < 0xfa) {
        iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_64 + 0x18));
        iVar3 = extraout_ECX_65;
        if (iVar4 < 10) goto LAB_00405e6f;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 0x34) {
    if (((param_4 == 3) && (0x7d < *(int *)(iVar2 + 0x308))) &&
       (iVar2 = FUN_00417170(0x78,10), iVar2 == 0)) {
      uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                           *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
      if ((int)uVar8 < 0x78) {
        iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_66 + 0x18));
        iVar3 = extraout_ECX_67;
        if (iVar2 < 10) {
LAB_00405d7d:
          *(undefined1 *)(iVar3 + 0xdc) = 3;
          return 1;
        }
      }
    }
    if ((0x7d < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x7b,5), iVar2 == 0)) {
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar3 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
      uVar8 = FUN_004034e0(iVar4 - iVar3);
      if (((int)uVar8 < 100) &&
         (iVar2 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_68 + 0x18)), iVar2 < 0x1e)) {
        iVar2 = extraout_ECX_69;
        if (iVar4 <= iVar3) {
          return 1;
        }
        goto LAB_00405df5;
      }
    }
    if ((0x7d < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x7c,0xe), iVar2 == 0)) {
      param_2 = *(int **)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar2 = *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10);
      uVar8 = FUN_004034e0((int)param_2 - iVar2);
      if ((int)uVar8 < 700) {
        iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                             *(int *)(extraout_ECX_70 + 0x18));
        iVar3 = extraout_ECX_71;
        if (iVar4 < 0x96) goto LAB_00405e6f;
      }
    }
    if ((0x7d < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
       (iVar2 = FUN_00417170(0x7d,5), iVar2 == 0)) {
      iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar4 = FUN_004034e0(*(int *)(iVar2 + 0x18) -
                           *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x18));
      if (iVar4 < 0x14) {
        iVar3 = extraout_ECX_72;
        if (*(int *)(extraout_ECX_72 + 0x10) < *(int *)(iVar2 + 0x10)) {
          *(undefined1 *)(extraout_ECX_72 + 0xd8) = 3;
          return 1;
        }
LAB_00405f01:
        *(undefined1 *)(iVar3 + 0xd9) = 3;
        return 1;
      }
    }
    iVar2 = FUN_00417170(0x7e,5);
    if (((iVar2 == 0) || (param_4 == 0x10)) || (param_4 == 8)) {
      iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar4 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
      iVar3 = *(int *)(iVar2 + 0x10);
      iVar5 = FUN_004450d0();
      iVar5 = FUN_004034e0((iVar5 - *(int *)(iVar4 + 0x10)) + iVar3);
      if ((((iVar5 < 100) &&
           (iVar2 = FUN_004034e0(*(int *)(iVar2 + 0x18) - *(int *)(iVar4 + 0x18)), iVar2 < 7)) &&
          (*(int *)(iVar4 + 0x308) < 100)) &&
         (((*(char *)(iVar4 + 0x80) == '\0' && (*(int *)(iVar4 + 0x10) < iVar3)) ||
          ((*(char *)(iVar4 + 0x80) == '\x01' && (iVar3 < *(int *)(iVar4 + 0x10))))))) {
        *(undefined1 *)(iVar4 + 0xd6) = 3;
        return 1;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + iVar7 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) != 0x33) {
    return 0;
  }
  if ((0x109 < *(int *)(iVar2 + 0x70)) && (*(int *)(iVar2 + 0x70) < 0x118)) {
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                         *(int *)(iVar2 + 0x18));
    if ((0xd < (int)uVar8) ||
       (iVar2 = extraout_ECX_73,
       *(int *)(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x368) + 0x6f8) != 0)) {
      *(undefined1 *)(extraout_ECX_73 + 0xcc) = 0;
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0xd3) = 1;
      return 1;
    }
  }
  if ((300 < *(int *)(iVar2 + 0x308)) && (iVar2 = FUN_00417170(0x7f,10), iVar2 == 0)) {
    uVar8 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
    if ((int)uVar8 < 300) {
      iVar4 = FUN_004034e0(*(int *)((int)((ulonglong)uVar8 >> 0x20) + 0x18) -
                           *(int *)(extraout_ECX_74 + 0x18));
      iVar2 = extraout_ECX_75;
      if (iVar4 < 200) {
LAB_00405df5:
        *(undefined1 *)(iVar2 + 0xda) = 3;
        return 1;
      }
    }
  }
  if ((300 < *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x308)) &&
     (iVar2 = FUN_00417170(0x80,10), iVar2 == 0)) {
    iVar4 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) -
                         *(int *)(*(int *)(in_ECX + 0x194 + iVar7 * 4) + 0x10));
    iVar2 = extraout_ECX_76;
    if (iVar4 < 0x3b6) {
LAB_004060e1:
      *(undefined1 *)(iVar2 + 0xd6) = 3;
      return 1;
    }
  }
  iVar2 = FUN_00417170(0x81,5);
  if ((iVar2 == 0) && (iVar7 = *(int *)(in_ECX + 0x194 + iVar7 * 4), 0xfa < *(int *)(iVar7 + 0x308))
     ) {
    iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar4 = FUN_004034e0(*(int *)(iVar2 + 0x10) - *(int *)(iVar7 + 0x10));
    if ((iVar4 < 0x4b0) && (0x28 < iVar4)) {
      uVar8 = FUN_004034e0(*(int *)(iVar2 + 0x18) - *(int *)(iVar7 + 0x18));
      if ((int)uVar8 < 0xd) {
        if ((int)((ulonglong)uVar8 >> 0x20) < extraout_ECX_77) {
          *(undefined1 *)(iVar7 + 0xd8) = 3;
          return 1;
        }
LAB_00406175:
        *(undefined1 *)(iVar7 + 0xd9) = 3;
        return 1;
      }
    }
  }
  return 0;
}
