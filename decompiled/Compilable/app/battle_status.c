#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdio.h>
#include <string.h>



/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */



void FUN_00437860(int param_1,int *param_2)



{

  int iVar1;

  char *pcVar2;

  int *piVar3;

  undefined4 uVar4;

  int iVar5;

  char *in_ecx = (char *)in_ecx;

  int iVar6;

  int iVar7;

  uint uVar8;

  int *piVar9;

  bool bVar10;

  int iVar11;

  undefined4 *puVar12;

  int iVar13;

  int local_4;

  

  puVar12 = &DAT_004514e0;

  for (iVar6 = 400; uVar8 = DAT_0044fb6c, iVar6 != 0; iVar6 = iVar6 + -1) {

    *puVar12 = 0;

    puVar12 = puVar12 + 1;

  }

  if (2 < DAT_00450ba8) {

    if ((DAT_00450ba8 == 3) && (DAT_00450bdc = 0, DAT_00450ba4 < 0x15)) {

      if ((int)DAT_00450ba4 < 10) {

        iVar6 = DAT_00450ba4 * 0x2b;

        iVar5 = 0x87;

        do {

          FUN_00415160(0,iVar5,0x31a,iVar6 / 10,0);

          iVar5 = iVar5 + 0x2b;

        } while (iVar5 < 0x235);

      }

      else {

        FUN_00415160(0,0x6d,0x31a,0x1b8,0);

      }

      DAT_00450ba4 = DAT_00450ba4 + 1;

      if (DAT_00450ba4 == 0x15) {

        if (DAT_00450b94 / 10 == 4) {

          if ((DAT_00450b88 == 0) || (*param_2 == 10)) {

            *param_2 = 300;

            return;

          }

        }

        else {

          DAT_00450b94 = ((DAT_00450b94 / 10) * 5 + 5) * 2;

          DAT_00450b98 = 1;

        }

        DAT_00450bdc = 0x15e;

        return;

      }

    }

    return;

  }

  if ((DAT_0044fb6c == 0xffffffff) && (DAT_00450b94 == (DAT_00450b94 / 10) * 10)) {

    DAT_0044d34c = 0xffffffff;

  }

  iVar6 = DAT_00450b94 * 0x149b08;

  if ((((int)DAT_0044fb6c < *(int *)(iVar6 + 2000 + *(int *)(in_ecx + 0x7d4)) + -1) ||

      ((-1 < (int)DAT_0044fb6c &&

       (*(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x3c90 + *(int *)(in_ecx + 0x7d4)) != -1)))) &&

     ((DAT_0044fb6c == 0xffffffff || (DAT_00451b34 == 1)))) {

    piVar3 = (int *)(in_ecx + 0x198);

    DAT_00451b34 = 0;

    DAT_00451b30 = 0;

    DAT_00450bac = 0;

    param_2 = (int *)0x4;

    do {

      param_2 = (int *)((int)param_2 + -1);

    } while (param_2 != (int *)0x0);

    if (_DAT_00450c30 == -1) {

      FUN_004450d0();

    }

    DAT_0044f880 = DAT_0044f880 + 1;

    if (DAT_00450b94 / 10 == 5) {

      DAT_00450ba0 = 1;

    }

    if (((int)uVar8 < 0) ||

       (DAT_0044fb6c = *(uint *)(uVar8 * 0x34c0 + iVar6 + 0x3c90 + *(int *)(in_ecx + 0x7d4)),

       DAT_0044fb6c == 0xffffffff)) {

      DAT_0044fb6c = uVar8 + 1;

    }

    iVar6 = DAT_0044fb6c * 0x34c0 + iVar6;

    if (*(char *)(iVar6 + 0x7dc + *(int *)(in_ecx + 0x7d4)) != '\0') {

      FUN_00402020(iVar6 + 0x7dc + *(int *)(in_ecx + 0x7d4));

    }

    DAT_00450bb0 = *(int *)(DAT_0044fb6c * 0x34c0 + DAT_00450b94 * 0x149b08 + 0x7d8 +

                           *(int *)(in_ecx + 0x7d4)) + -0x31a;

    DAT_00450bb4 = *(undefined4 *)

                    (DAT_0044fb6c * 0x34c0 + DAT_00450b94 * 0x149b08 + 0x7d8 +

                    *(int *)(in_ecx + 0x7d4));

    if (DAT_00450b94 / 10 == 5) {

      iVar6 = 2;

      do {

        iVar5 = piVar3[-1];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[-1] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[-1] + 0x308) = 500;

          *(undefined4 *)(piVar3[-1] + 0x10) = 100;

          *(undefined8 *)(piVar3[-1] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = *piVar3;

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(*piVar3 + 0x2fc) = 5;

          *(undefined4 *)(*piVar3 + 0x308) = 500;

          *(undefined4 *)(*piVar3 + 0x10) = 100;

          *(undefined8 *)(*piVar3 + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[1];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[1] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[1] + 0x308) = 500;

          *(undefined4 *)(piVar3[1] + 0x10) = 100;

          *(undefined8 *)(piVar3[1] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[2];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[2] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[2] + 0x308) = 500;

          *(undefined4 *)(piVar3[2] + 0x10) = 100;

          *(undefined8 *)(piVar3[2] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[3];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[3] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[3] + 0x308) = 500;

          *(undefined4 *)(piVar3[3] + 0x10) = 100;

          *(undefined8 *)(piVar3[3] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[4];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[4] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[4] + 0x308) = 500;

          *(undefined4 *)(piVar3[4] + 0x10) = 100;

          *(undefined8 *)(piVar3[4] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[5];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[5] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[5] + 0x308) = 500;

          *(undefined4 *)(piVar3[5] + 0x10) = 100;

          *(undefined8 *)(piVar3[5] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[6];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[6] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[6] + 0x308) = 500;

          *(undefined4 *)(piVar3[6] + 0x10) = 100;

          *(undefined8 *)(piVar3[6] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[7];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[7] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[7] + 0x308) = 500;

          *(undefined4 *)(piVar3[7] + 0x10) = 100;

          *(undefined8 *)(piVar3[7] + 0x58) = 0x4059000000000000ULL;

        }

        iVar5 = piVar3[8];

        if (*(int *)(iVar5 + 0x2fc) < 1) {

          if (*(int *)(iVar5 + 0x300) < 5) {

            *(undefined4 *)(iVar5 + 0x300) = 5;

          }

          *(undefined4 *)(piVar3[8] + 0x2fc) = 5;

          *(undefined4 *)(piVar3[8] + 0x308) = 500;

          *(undefined4 *)(piVar3[8] + 0x10) = 100;

          *(undefined8 *)(piVar3[8] + 0x58) = 0x4059000000000000ULL;

        }

        piVar3 = piVar3 + 10;

        iVar6 = iVar6 + -1;

      } while (iVar6 != 0);

    }

    iVar6 = 0;

    do {

      iVar5 = *(int *)(in_ecx + 0x7d4);

      iVar11 = DAT_00450b94 * 0x149b08 + DAT_0044fb6c * 0x34c0 + iVar6;

      puVar12 = (undefined4 *)(iVar11 + 0x810 + iVar5);

      *puVar12 = 0;

      if (-1 < *(int *)(iVar11 + 0x8bc + iVar5)) {

        if (*(double *)(puVar12 + 0x34) <= 0.0) {

          puVar12[1] = puVar12[0x2e];

          puVar12[2] = 1;

        }

        else {

          uVar4 = FUN_004450d0();

          puVar12[1] = uVar4;

          iVar5 = FUN_004450d0();

          puVar12[2] = iVar5;

          if (0x28 < iVar5) {

            puVar12[2] = 0x28;

          }

        }

        if (0 < (int)puVar12[2]) {

          iVar5 = 0;

          do {

            FUN_00437400(puVar12,iVar5);

            iVar5 = iVar5 + 1;

          } while (iVar5 < (int)puVar12[2]);

        }

      }

      iVar6 = iVar6 + 0xe0;

    } while (iVar6 < 0x3480);

  }

  iVar6 = 0;

  DAT_00451b34 = 1;

  DAT_00451b30 = 0;

  if ((int)DAT_0044fb6c < 0) {

    iVar6 = DAT_00450b94;

  }

  else {

    iVar11 = DAT_0044fb6c * 0x34c0;

    iVar5 = DAT_00450b94 * 0x149b08;

    do {

      iVar7 = iVar6 + iVar11 + iVar5;

      iVar13 = iVar7 + 0x810 + *(int *)(in_ecx + 0x7d4);

      if (((-1 < *(int *)(iVar7 + 0x8bc + *(int *)(in_ecx + 0x7d4))) &&

          (1 < *(int *)(iVar13 + 0xd8))) && (iVar7 = 0, 0 < *(int *)(iVar13 + 8))) {

        piVar3 = (int *)(iVar13 + 0xc);

        do {

          iVar1 = *piVar3;

          if (((-1 < iVar1) && ((&DAT_004514e0)[iVar1] = 1, in_ecx[iVar1 + 4] == '\x01')) &&

             ((*(int *)(*(int *)(in_ecx + iVar1 * 4 + 0x194) + 0x364) == 5 &&

              (*(int *)(*(int *)(*(int *)(in_ecx + iVar1 * 4 + 0x194) + 0x368) + 0x6f8) == 0)))) {

            DAT_00451b30 = 1;

          }

          iVar7 = iVar7 + 1;

          piVar3 = piVar3 + 1;

        } while (iVar7 < *(int *)(iVar13 + 8));

      }

      iVar6 = iVar6 + 0xe0;

    } while (iVar6 < 0x3480);

    param_2 = (int *)0x0;

    iVar6 = DAT_00450b94;

    do {

      local_4 = 0;

      do {

        iVar5 = iVar6 * 0x149b08 + DAT_0044fb6c * 0x34c0 + local_4;

        piVar3 = (int *)(iVar5 + 0x810 + *(int *)(in_ecx + 0x7d4));

        if (-1 < *(int *)(iVar5 + 0x8bc + *(int *)(in_ecx + 0x7d4))) {

          iVar5 = 0;

          if (0 < piVar3[2]) {

            piVar9 = piVar3 + 3;

            do {

              if ((-1 < *piVar9) && (in_ecx[*piVar9 + 4] == '\0')) {

                if (param_2 == (int *)0x0) {

                  if (piVar3[0x36] == 1) {

                    if ((DAT_00451b30 == 0) || (piVar3[1] <= *piVar3)) {

                      *piVar9 = -1;

                      *piVar3 = piVar3[1];

                    }

                    if (piVar3[0x36] == 1) goto LAB_0043801a;

                  }

                  if (piVar3[1] <= *piVar3) {

                    *piVar9 = -1;

                    *piVar3 = piVar3[1];

                  }

                }

                else if ((param_2 == (int *)0x1) && (*piVar3 < piVar3[1])) {

                  FUN_00437400(piVar3,iVar5);

                  DAT_00451b34 = 0;

                }

              }

LAB_0043801a:

              iVar5 = iVar5 + 1;

              piVar9 = piVar9 + 1;

            } while (iVar5 < piVar3[2]);

            iVar6 = DAT_00450b94;

          }

        }

        local_4 = local_4 + 0xe0;

      } while (local_4 < 0x3480);

      param_2 = (int *)((int)param_2 + 1);

    } while ((int)param_2 < 2);

  }

  iVar5 = 0x14;

  piVar3 = (int *)(in_ecx + 0x1e4);

  do {

    if (((in_ecx[iVar5 + 4] != '\0') && (*(int *)(*(int *)(*piVar3 + 0x368) + 0x6f8) == 0)) &&

       (*(int *)(*piVar3 + 0x364) == 5)) {

      DAT_00451b34 = 0;

      goto LAB_0043811d;

    }

    iVar5 = iVar5 + 1;

    piVar3 = piVar3 + 1;

  } while (iVar5 < 400);

  if ((DAT_00451b34 == 1) && (DAT_00450b9c == 0)) {

    if (DAT_00450bac == 0) {

      DAT_00450b9c = 0xa9;

      if (DAT_0044fb6c == *(int *)(iVar6 * 0x149b08 + 2000 + *(int *)(in_ecx + 0x7d4)) - 1U) {

        DAT_00450bac = 1;

        DAT_00450bb4 = 0;

      }

      goto LAB_00438236;

    }

LAB_00438311:

    if (DAT_00450bac == 1) goto LAB_0043831e;

LAB_0043854d:

    if (DAT_00450ba4 - 0xb < 10) {

      iVar6 = 0x87;

      do {

        FUN_00415160(0,iVar6,0x31a,(int)((0x15 - DAT_00450ba4) * 0x2b) / 10,0);

        iVar6 = iVar6 + 0x2b;

      } while (iVar6 < 0x235);

      DAT_00450ba4 = DAT_00450ba4 + 1;

      if (DAT_00450ba4 != 0x15) goto LAB_004385b7;

      DAT_00450ba4 = 0;

    }

    else {

LAB_004385b7:

      if ((0 < (int)DAT_00450ba4) && ((int)DAT_00450ba4 < 0xb)) goto LAB_004385c0;

    }

  }

  else {

LAB_0043811d:

    if ((0 < DAT_00450b9c) && (DAT_00450b9c < 100)) {

      if (iVar6 / 10 < 5) {

        FUN_0043f010(0x109,299,0x19,1,0,param_1);

        FUN_0043f010(0x1ea,299,0x24,1,0,param_1);

        FUN_0043f010(0x1cc,299,DAT_00450b94 / 10 + 0x1b,1,0,param_1);

        iVar6 = DAT_00450b94 % 10 + 0x1b;

        uVar4 = 0x208;

      }

      else {

        iVar6 = 3;

        uVar4 = 0xa5;

      }

      FUN_0043f010(uVar4,299,iVar6,1,0,param_1);

      DAT_00450b9c = DAT_00450b9c + -1;

      iVar6 = DAT_00450b94;

    }

    if ((DAT_00450b9c < 0x65) || (299 < DAT_00450b9c)) goto LAB_00438311;

LAB_00438236:

    if ((DAT_0044fb6c < 99) &&

       ((iVar5 = DAT_0044fb6c * 0x34c0 + iVar6 * 0x149b08 + *(int *)(in_ecx + 0x7d4),

        *(int *)(iVar5 + 0x7d8) == *(int *)(iVar5 + 0x3c98) && (DAT_00450bac != 1)))) {

      DAT_00450b9c = 0;

    }

    uVar8 = DAT_00450b9c / 10 & 0x80000001;

    if ((int)uVar8 < 0) {

      uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;

    }

    if (uVar8 == 1) {

      if ((DAT_00450b9c % 10 == 0) && (DAT_00450b9c < 200)) {

        FUN_00401a30(0);

      }

      FUN_0043f010(0x294,299,0x18,1,0,param_1);

      iVar6 = DAT_00450b94;

    }

    DAT_00450b9c = DAT_00450b9c + -1;

    if ((DAT_00450b9c != 0x65) && (DAT_00450b9c != 0xc9)) goto LAB_00438311;

    if (DAT_00450bac != 1) {

      DAT_00450b9c = 0;

      goto LAB_00438311;

    }

    DAT_00450b9c = 0x118;

LAB_0043831e:

    if (DAT_00450ba4 != 0) goto LAB_0043854d;

    if (iVar6 % 10 == 9) {

LAB_004384d7:

      if (DAT_00450bdc == 1) {

        DAT_0044d02c = 1;

        FUN_00402100();

        FUN_00401a30(0);

      }

      if (DAT_00450bdc < 0x5a) {

        FUN_0043f010(0xd7,0x12a,0x25,1,0,param_1);

      }

      if (DAT_00450ba8 == 0) {

        DAT_00450ba8 = 1;

      }

      DAT_00450bac = 0;

      DAT_00450b9c = 0;

      DAT_00450ba4 = 0;

      goto LAB_00438614;

    }

    iVar5 = *(int *)(in_ecx + 0x7d4);

    iVar6 = iVar6 * 0x149b08;

    if (*(int *)(iVar6 + 0x14a2d8 + iVar5) == -1) goto LAB_004384d7;

    bVar10 = true;

    piVar3 = (int *)(in_ecx + 0x198);

    param_1 = 4;

    pcVar2 = in_ecx;

    do {

      if ((((pcVar2[4] != '\0') &&

           (iVar11 = piVar3[-1], *(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0)) &&

          (0 < *(int *)(iVar11 + 0x2fc))) &&

         (*(int *)(iVar11 + 0x10) < *(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x7d8 + iVar5))) {

        bVar10 = false;

      }

      if (((pcVar2[5] != '\0') &&

          (iVar11 = *piVar3, *(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0)) &&

         ((0 < *(int *)(iVar11 + 0x2fc) &&

          (*(int *)(iVar11 + 0x10) < *(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x7d8 + iVar5))))) {

        bVar10 = false;

      }

      if (((pcVar2[6] != '\0') &&

          (iVar11 = piVar3[1], *(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0)) &&

         ((0 < *(int *)(iVar11 + 0x2fc) &&

          (*(int *)(iVar11 + 0x10) < *(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x7d8 + iVar5))))) {

        bVar10 = false;

      }

      if ((((pcVar2[7] != '\0') &&

           (iVar11 = piVar3[2], *(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0)) &&

          (0 < *(int *)(iVar11 + 0x2fc))) &&

         (*(int *)(iVar11 + 0x10) < *(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x7d8 + iVar5))) {

        bVar10 = false;

      }

      if (((pcVar2[8] != '\0') &&

          (iVar11 = piVar3[3], *(int *)(*(int *)(iVar11 + 0x368) + 0x6f8) == 0)) &&

         ((0 < *(int *)(iVar11 + 0x2fc) &&

          (*(int *)(iVar11 + 0x10) < *(int *)(DAT_0044fb6c * 0x34c0 + iVar6 + 0x7d8 + iVar5))))) {

        bVar10 = false;

      }

      piVar3 = piVar3 + 5;

      param_1 = param_1 + -1;

      pcVar2 = pcVar2 + 5;

    } while (param_1 != 0);

    if (!bVar10) goto LAB_00438614;

    DAT_00450ba4 = 1;

LAB_004385c0:

    iVar6 = 0x87;

    do {

      FUN_00415160(0,iVar6,0x31a,(int)(DAT_00450ba4 * 0x2b) / 10,0);

      iVar6 = iVar6 + 0x2b;

    } while (iVar6 < 0x235);

    DAT_00450ba4 = DAT_00450ba4 + 1;

    if (DAT_00450ba4 == 0xb) {

      FUN_00436fc0();

    }

  }

LAB_00438614:

  iVar6 = 0;

  piVar3 = (int *)(in_ecx + 0x194);

  bVar10 = false;

  piVar9 = piVar3;

  do {

    if ((((in_ecx[iVar6 + 4] != '\0') &&

         (iVar5 = *piVar9, *(int *)(*(int *)(iVar5 + 0x368) + 0x6f8) == 0)) &&

        (0 < *(int *)(iVar5 + 0x2fc))) && (*(int *)(iVar5 + 0x364) != 5)) {

      bVar10 = true;

      break;

    }

    iVar6 = iVar6 + 1;

    piVar9 = piVar9 + 1;

  } while (iVar6 < 0x14);

  iVar5 = 0;

  iVar11 = 0;

  param_2 = (int *)0x0;

  local_4 = 0;

  iVar6 = 0;

  iVar13 = 0;

  do {

    if ((in_ecx[iVar5 + 4] != '\0') &&

       (iVar7 = *piVar3, *(int *)(*(int *)(iVar7 + 0x368) + 0x6f8) == 0)) {

      if (*(int *)(iVar7 + 0x364) == 5) {

        if (0 < *(int *)(iVar7 + 0x2fc)) {

          param_2 = (int *)((int)param_2 + *(int *)(iVar7 + 0x2fc));

          local_4 = local_4 + 1;

        }

      }

      else {

        if (0 < *(int *)(iVar7 + 0x2fc)) {

          iVar13 = iVar13 + *(int *)(iVar7 + 0x2fc);

          iVar11 = iVar11 + 1;

        }

        iVar7 = *(int *)(iVar7 + 0x30c);

        if (iVar7 < 2) {

          if (bVar10) goto LAB_004386e1;

        }

        else {

          if (bVar10) {

            iVar6 = iVar6 + -1 + iVar7;

LAB_004386e1:

            if (-1 < iVar7) goto LAB_0043870a;

          }

          else if (iVar7 < 1) goto LAB_0043870a;

          *(int *)(*piVar3 + 0x30c) = -*(int *)(*piVar3 + 0x30c);

        }

      }

    }

LAB_0043870a:

    iVar5 = iVar5 + 1;

    piVar3 = piVar3 + 1;

  } while (iVar5 < 400);

  if (DAT_00450b94 < 0x32) {

    sprintf(&DAT_00451418,"STAGE %d-%d",DAT_00450b94 / 10 + 1,DAT_00450b94 % 10 + 1);

    FUN_00401290(DAT_00455608,&DAT_00451418,0,0xc8c8c8,0x168,0x6e);

    goto LAB_00438828;

  }

  if (DAT_0044f880 < 0) goto LAB_00438828;

  if (0 < DAT_00450ba0) {

    DAT_00450ba0 = DAT_00450ba0 + 1;

  }

  if (0x45 < DAT_00450ba0) {

    DAT_00450ba0 = 0;

  }

  sprintf(&DAT_00451418,"Survival Stage: %d",DAT_0044f880);

  if (DAT_00450ba0 == 0) {

LAB_00438807:

    uVar4 = 0xc8c8c8;

  }

  else {

    uVar8 = DAT_00450ba0 / 10 & 0x80000001;

    if ((int)uVar8 < 0) {

      uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;

    }

    if (uVar8 == 1) goto LAB_00438807;

    uVar4 = 0xc85a5a;

  }

  FUN_00401290(DAT_00455608,&DAT_00451418,0,uVar4,0x154,0x6e);

LAB_00438828:

  if (iVar6 == 0) {

    sprintf(&DAT_00451418,"Man: %3d      HP: %4d",iVar11,iVar13);

  }

  else {

    sprintf(&DAT_00451418,"Man: %3d      HP: %4d     Reserve: %3d",iVar11,iVar13,iVar6);

  }

  FUN_00401290(DAT_00455608,&DAT_00451418,0,0xff7878,10,0x6e);

  sprintf(&DAT_00451418,"Man: %3d      HP: %4d",local_4,param_2);

  FUN_00401290(DAT_00455608,&DAT_00451418,0,0xff00ff,0x285,0x6e);

  return;

}



