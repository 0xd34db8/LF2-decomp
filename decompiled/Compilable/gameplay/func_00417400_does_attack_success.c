#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"


void FUN_00417400(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  bool bVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int in_ECX = (int)(intptr_t)in_ECX;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int local_28;
  int local_20;
  
  iVar2 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar3 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  iVar2 = *(int *)(iVar2 + 0x7c) * 0x178 + 0x7a4 + *(int *)(iVar2 + 0x368);
  iVar3 = *(int *)(iVar3 + 0x7c) * 0x178 + 0x7a4 + *(int *)(iVar3 + 0x368);
  local_28 = 0;
  if (0 < *(int *)(iVar2 + 0x128)) {
    do {
      piVar8 = (int *)(local_28 * 0x50 + *(int *)(iVar2 + 0x130));
      local_20 = 0;
      if (0 < *(int *)(iVar3 + 300)) {
        while( true ) {
          iVar12 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x368);
          iVar17 = *(int *)(iVar12 + 0x6f4);
          if (((((((((iVar17 == 200) || (iVar17 == 0xcb)) || (iVar17 == 0xcd)) ||
                  ((iVar17 == 0xce || (iVar17 == 0xcf)))) || ((iVar17 == 0xd7 || (iVar17 == 0xd8))))
                && ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f4) ==
                     0xd1 && (*piVar8 != 9)))) ||
               ((iVar16 = *piVar8, iVar16 == 3 &&
                (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f8) != 0))))
              || ((iVar16 == 0 &&
                  ((((((iVar13 = piVar8[0xb], iVar13 == 4 &&
                       (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f8)
                        == 0)) ||
                      ((iVar13 == 0x14 &&
                       (((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f8)
                          != 0 || (iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                                  *(int *)(*(int *)(iVar9 + 0x78) * 0x178 + 0x7ac +
                                          *(int *)(iVar9 + 0x368)) == 0x12)) ||
                        (iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                        *(int *)(*(int *)(iVar9 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368))
                        == 0x13)))))) ||
                     ((iVar13 == 0x15 &&
                      ((iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                       *(int *)(*(int *)(iVar9 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) ==
                       0x12 || (iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                               *(int *)(*(int *)(iVar9 + 0x78) * 0x178 + 0x7ac +
                                       *(int *)(iVar9 + 0x368)) == 0x13)))))) ||
                    ((iVar13 == 0x1e &&
                     ((iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x70), 199 < iVar9
                      && (iVar9 < 0xcb)))))) ||
                   ((iVar13 == 2 &&
                    ((iVar13 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                     *(int *)(*(int *)(iVar13 + 0x78) * 0x178 + 0x7ac + *(int *)(iVar13 + 0x368)) ==
                     0x13 && (iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                             *(int *)(*(int *)(iVar13 + 0x78) * 0x178 + 0x7ac +
                                     *(int *)(iVar13 + 0x368)) == 0x12)))))))))) ||
             (((iVar16 == 8 &&
               (*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f8) != 0)) ||
              (((iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4), *(int *)(iVar13 + 8) != 0 &&
                (iVar16 != 8)) && (iVar16 != 0xe)))))) break;
          if ((((((iVar16 < 4) || (iVar16 == 6)) ||
                ((iVar16 == 9 && (*(int *)(*(int *)(iVar13 + 0x368) + 0x6f8) == 0)))) ||
               (((iVar16 == 10 || (iVar16 == 0xb)) || ((iVar16 == 0xf || (iVar16 == 0x10)))))) &&
              ((iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
               *(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) != 0xd &&
               (iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
               *(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) != 10))))
             && ((iVar9 = *(int *)(iVar13 + 0x368), *(int *)(iVar9 + 0x6f4) != 0xd4 ||
                 ((iVar17 == 0xd4 &&
                  ((*(int *)(iVar13 + 0x70) % 10 != 5 ||
                   (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x70) % 10 != 0)))))))) {
            iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            iVar10 = *(int *)(iVar4 + 0x364);
            if ((((iVar10 == *(int *)(iVar13 + 0x364)) &&
                 (((iVar10 != 0 && (iVar16 != 8)) &&
                  ((iVar10 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                   *(int *)(*(int *)(iVar10 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar10 + 0x368)) !=
                   0x12 || ((piVar8[0xb] == 0x15 || (piVar8[0xb] == 0x16)))))))) &&
                ((*(int *)(iVar12 + 0x6f8) != 0 ||
                 ((*(int *)(iVar9 + 0x6f8) != 3 ||
                  (*(char *)(iVar4 + 0x80) == *(char *)(iVar13 + 0x80))))))) &&
               ((iVar9 = *(int *)(iVar9 + 0x6f8), iVar9 != 1 &&
                (((iVar9 != 2 && (iVar9 != 4)) && (iVar9 != 6)))))) break;
          }
          if (iVar16 == 5) {
            iVar16 = *(int *)(in_ECX + 0x194 + param_1 * 4);
            iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar16 + 0xa0) * 4) + 0x364);
            if (((iVar9 == *(int *)(iVar13 + 0x364)) && (iVar9 != 0)) &&
               (iVar9 = *(int *)(in_ECX + 0x194 + param_2 * 4),
               *(int *)(*(int *)(iVar9 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar9 + 0x368)) != 0xd)) {
              iVar9 = *(int *)(*(int *)(iVar13 + 0x368) + 0x6f8);
              if ((((iVar9 != 1) && (iVar9 != 2)) && ((iVar9 != 4 && (iVar9 != 6)))) &&
                 ((*(int *)(*(int *)(iVar13 + 0x368) + 0x6f4) != 0xd4 ||
                  ((iVar17 == 0xd4 &&
                   ((*(int *)(iVar13 + 0x70) % 10 != 5 || (*(int *)(iVar16 + 0x70) % 10 != 0))))))))
              break;
            }
          }
          iVar17 = *(int *)(*(int *)(iVar3 + 0x134) + 4 + local_20 * 0x28);
          piVar1 = (int *)(*(int *)(iVar3 + 0x134) + local_20 * 0x28);
          iVar16 = *piVar1;
          if (*(char *)(iVar13 + 0x80) == '\0') {
            iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4);
            iVar9 = *(int *)(iVar13 + 0x7c) * 0x178 + *(int *)(iVar13 + 0x368);
            iVar17 = iVar17 + (*(int *)(iVar13 + 0x10) - *(int *)(iVar9 + 0x7f4));
          }
          else {
            iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4);
            iVar9 = *(int *)(iVar13 + 0x7c) * 0x178 + *(int *)(iVar13 + 0x368);
            iVar17 = ((*(int *)(iVar9 + 0x7f4) + *(int *)(iVar13 + 0x10)) - piVar1[3]) - iVar17;
          }
          iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
          iVar10 = *(int *)(iVar4 + 0x7c) * 0x178 + *(int *)(iVar4 + 0x368);
          if (*(char *)(iVar4 + 0x80) == '\0') {
            iVar15 = piVar8[1] + (*(int *)(iVar4 + 0x10) - *(int *)(iVar10 + 0x7f4));
          }
          else {
            iVar15 = ((*(int *)(iVar4 + 0x10) + *(int *)(iVar10 + 0x7f4)) - piVar8[3]) - piVar8[1];
          }
          iVar11 = piVar8[0x12];
          if (iVar11 == 0) {
            iVar11 = 0xf;
          }
          iVar5 = *(int *)(in_ECX + 0x194 + param_2 * 4);
          iVar14 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) - *(int *)(iVar5 + 0x18);
          if ((iVar11 <= iVar14) || (bVar6 = true, iVar14 <= -iVar11)) {
            bVar6 = false;
          }
          iVar17 = FUN_004171c0(iVar17,piVar1[2] +
                                       (*(int *)(iVar13 + 0x14) - *(int *)(iVar9 + 0x7f8)),piVar1[3]
                                ,piVar1[4],iVar15,
                                piVar8[2] + (*(int *)(iVar4 + 0x14) - *(int *)(iVar10 + 0x7f8)),
                                piVar8[3],piVar8[4]);
          if ((iVar17 != 0) && (bVar6)) {
            iVar17 = *(int *)(in_ECX + 0x194 + param_2 * 4);
            bVar6 = false;
            if ((*(int *)(*(int *)(iVar17 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar17 + 0x368)) == 0xc
                ) && (((piVar8[7] < 0x29 && (*piVar8 != 10)) && (*piVar8 != 0xb)))) {
              bVar6 = true;
            }
            if (param_3 == 1) {
              bVar7 = false;
              if ((((*(int *)(iVar12 + 0x6f8) == 0) || (*(int *)(iVar12 + 0x6f4) == 0xc9)) ||
                  (*(int *)(iVar12 + 0x6f4) == 0xca)) &&
                 (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x364) != 5)) {
                bVar7 = true;
              }
              iVar17 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if (((*(int *)(iVar17 + 0x98) < 0) &&
                  (iVar17 = *(int *)(iVar17 + 0xa0), *(char *)(iVar17 + 4 + in_ECX) == '\x01')) &&
                 ((iVar17 = *(int *)(in_ECX + 0x194 + iVar17 * 4),
                  *(int *)(*(int *)(iVar17 + 0x368) + 0x6f8) == 0 && (*(int *)(iVar17 + 0x364) != 5)
                  ))) {
                bVar7 = true;
              }
              if ((999 < iVar16) && (!bVar7)) {
                bVar6 = true;
              }
            }
            if (((((piVar8[9] != 0) || (iVar17 = *piVar8, iVar17 == 1)) || (iVar17 == 2)) ||
                (iVar17 == 7)) ||
               (((iVar17 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                 *(int *)(*(int *)(iVar17 + 0x7c) * 0x178 + 0x7ac + *(int *)(iVar17 + 0x368)) ==
                 0x3ec && ((*(int *)(iVar12 + 0x6f8) < 1 ||
                           (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x98) < 0)))) ||
                (bVar6)))) {
              iVar17 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              if ((0x13 < *(int *)(iVar17 + 0x2e4)) || (bVar6)) goto LAB_00417f3e;
              iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4);
              iVar16 = 0;
              if (((*(int *)(*(int *)(iVar13 + 0x7c) * 0x178 + 0x7ac + *(int *)(iVar13 + 0x368)) ==
                    0x3ec) &&
                  (((*(int *)(iVar12 + 0x6f8) < 1 || (*(int *)(iVar17 + 0x98) < 0)) &&
                   (iVar12 = *piVar8, iVar12 != 2)))) && ((iVar12 != 7 && (iVar12 != 10)))) {
                iVar16 = 2;
              }
              if (*piVar8 == 1) {
                iVar12 = *(int *)(iVar17 + 0x10) - *(int *)(iVar5 + 0x10);
                if (iVar12 < 0) {
                  iVar12 = -iVar12;
                }
                if ((iVar12 < *(int *)(iVar5 + 0x2ec)) ||
                   ((iVar12 == *(int *)(iVar5 + 0x2ec) &&
                    (iVar17 = FUN_00417170(0x86,2), iVar17 == 0)))) {
                  *(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x2ec) = iVar12;
                }
                else {
                  iVar16 = 2;
                }
              }
              iVar12 = *piVar8;
              if (((iVar12 == 4) && (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 800) != 0))
                 && (iVar16 != 2)) {
                iVar16 = 1;
              }
              if (iVar12 == 1) {
                iVar17 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if ((((*(char *)(iVar17 + 0xd0) != '\0') &&
                     (*(int *)(iVar17 + 0x10) <
                      *(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x10))) ||
                    ((*(char *)(iVar17 + 0xcf) != '\0' &&
                     (*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x10) <=
                      *(int *)(iVar17 + 0x10))))) &&
                   (iVar17 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                   *(int *)(*(int *)(iVar17 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar17 + 0x368)) ==
                   0x10)) {
LAB_00417e06:
                  if (iVar16 != 2) {
                    iVar16 = 1;
                  }
                }
LAB_00417e10:
                if (iVar12 == 2) goto LAB_00417e19;
              }
              else {
                if (iVar12 != 2) {
                  if (iVar12 != 7) goto LAB_00417e06;
                  goto LAB_00417e10;
                }
LAB_00417e19:
                iVar17 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                if (*(int *)(iVar17 + 0x98) == 0) {
                  if (*(char *)(iVar17 + 0xd1) == '\0') goto LAB_00417eb9;
                  if (((*(char *)(iVar17 + 0xca) == '\0') &&
                      (iVar13 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                      *(int *)(*(int *)(iVar13 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar13 + 0x368))
                      == 0x3ec)) && (iVar16 != 2)) {
                    iVar16 = 1;
                  }
                }
                if ((((*(char *)(iVar17 + 0xd1) != '\0') && (*(char *)(iVar17 + 0xca) == '\0')) &&
                    (iVar17 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                    *(int *)(*(int *)(iVar17 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar17 + 0x368)) ==
                    0x7d4)) && (iVar16 != 2)) {
                  iVar16 = 1;
                }
              }
LAB_00417eb9:
              if ((((iVar12 == 7) &&
                   (iVar12 = *(int *)(in_ECX + 0x194 + param_1 * 4),
                   *(char *)(iVar12 + 0xd1) != '\0')) &&
                  ((*(char *)(iVar12 + 0xca) == '\0' &&
                   ((iVar12 = *(int *)(in_ECX + 0x194 + param_2 * 4),
                    *(int *)(*(int *)(iVar12 + 0x70) * 0x178 + 0x7ac + *(int *)(iVar12 + 0x368)) ==
                    0x3ec && (iVar16 != 2)))))) || (iVar16 == 1)) {
                iVar12 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                *(int *)(iVar12 + 0x280 + *(int *)(iVar12 + 0x2e4) * 4) = param_2;
                iVar12 = *(int *)(in_ECX + 0x194 + param_1 * 4);
                *(undefined1 *)(*(int *)(iVar12 + 0x2e4) + 0x2d0 + iVar12) = (undefined1)local_28;
                piVar1 = (int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2e4);
                *piVar1 = *piVar1 + 1;
              }
            }
            else {
              iVar12 = *(int *)(in_ECX + 0x194 + param_1 * 4);
              iVar17 = *(int *)(iVar12 + 0x10) - *(int *)(iVar5 + 0x10);
              if (*(int *)(iVar12 + 0x98) < 0) {
                if (param_2 != *(int *)(iVar12 + 0xa0)) {
                  iVar17 = *(int *)(*(int *)(in_ECX + 0x194 + *(int *)(iVar12 + 0xa0) * 4) + 0x10) -
                           *(int *)(iVar5 + 0x10);
                  goto LAB_00417c3b;
                }
                iVar17 = 2000;
              }
              else {
LAB_00417c3b:
                if (iVar17 < 0) {
                  iVar17 = -iVar17;
                }
              }
              iVar12 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2e8);
              if ((iVar17 < iVar12) ||
                 ((iVar17 == iVar12 && (iVar12 = FUN_00417170(0x85,2), iVar12 == 0)))) {
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2e8) = iVar17;
                *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x280) = param_2;
                *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2d0) =
                     (undefined1)local_28;
                *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x2e4) = 1;
              }
            }
          }
LAB_00417f3e:
          local_20 = local_20 + 1;
          if (*(int *)(iVar3 + 300) <= local_20) break;
        }
      }
      local_28 = local_28 + 1;
    } while (local_28 < *(int *)(iVar2 + 0x128));
  }
  return;
}


