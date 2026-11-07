#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* 
 * Function: FUN_0040ef70
 * Loads and decrypts stage data from DAT file.
 * Virtual Address: 0x0040ef70
 * Calling Convention: __stdcall (parameters on stack)
 */


void FUN_0040ef70(undefined4 param_1,undefined4 param_2,char *param_3,int param_4)



{

  int *piVar1;

  char cVar2;

  byte bVar3;

  uint uVar4;

  char *pcVar5;

  char *pcVar6;

  int *piVar7;

  undefined4 uVar8;

  int iVar9;

  void *pvVar10;

  byte *pbVar11;

  int iVar12;

  FILE *pFVar13;

  int in_ecx_val = (int)(intptr_t)in_ECX;
#define in_ECX in_ecx_val

  byte *pbVar14;

  int iVar15;

  int iVar16;

  byte *pbVar17;

  undefined4 *puVar18;

  bool bVar19;

  FILE *local_4e8;

  int iStack_4e4;

  byte *local_4e0;

  void *local_4dc;

  char *local_4d8;

  int local_4d4;

  int local_4d0;

  undefined4 local_4cc;

  undefined4 local_4c8;

  undefined4 local_4c4;

  undefined4 local_4c0;

  undefined4 local_4bc;

  undefined4 local_4b8;

  undefined4 local_4b4;

  undefined4 local_4b0;

  undefined4 local_4ac;

  undefined4 local_4a8;

  undefined4 local_4a4;

  undefined4 local_4a0;

  undefined4 local_49c;

  undefined4 local_498;

  undefined4 local_494;

  undefined4 local_490;

  char local_48c [200];

  char local_3c4 [48];

  undefined4 local_394;

  uint local_390;

  char acStack_268 [300];

  char acStack_13c [300];

  uint local_10;

  void *local_c;

  undefined1 *puStack_8;

  undefined4 local_4;

  

  local_4 = 0xffffffff;

  puStack_8 = &LAB_00445d30;

  local_c = ExceptionList;

  local_10 = DAT_0044eea4 ^ (uint)&local_4e8;

  uVar4 = DAT_0044eea4 ^ (uint)(local_48c + -0x6c);

  ExceptionList = &local_c;

  local_4d8 = param_3;

  local_4d4 = param_4;

  iVar15 = 399;

  do {

    FUN_0040bbf0(uVar4);

    iVar15 = iVar15 + -1;

  } while (-1 < iVar15);

  *(undefined4 *)(in_ECX + 0xac) = 0xffffffff;

  *(undefined4 *)(in_ECX + 0xa8) = 0xffffffff;

  *(undefined4 *)(in_ECX + 0xa4) = 0xffffffff;

  *(undefined4 *)(in_ECX + 0xa0) = 0;

  *(undefined4 *)(in_ECX + 0x9c) = 0;

  *(undefined4 *)(in_ECX + 0x98) = 0;

  *(undefined4 *)(in_ECX + 0x90) = 0;

  *(undefined4 *)(in_ECX + 0x94) = 0;

  *(undefined4 *)(in_ECX + 0x700) = 0x656e6f6e;

  *(undefined1 *)(in_ECX + 0x704) = 0;

  *(undefined4 *)(in_ECX + 0x25324) = 0x656e6f6e;

  *(undefined4 *)(in_ECX + 0x498) = 0;

  *(undefined1 *)(in_ECX + 0x25328) = 0;

  *(undefined4 *)(in_ECX + 0x6f4) = param_1;

  *(undefined4 *)(in_ECX + 0x6f8) = param_2;

  *(undefined4 *)(in_ECX + 0x62c) = 3000;

  *(undefined4 *)(in_ECX + 0x630) = 3000;

  *(undefined4 *)(in_ECX + 0x634) = 3000;

  *(undefined4 *)(in_ECX + 0x638) = 3000;

  *(undefined4 *)(in_ECX + 0x63c) = 3000;

  *(undefined4 *)(in_ECX + 0x640) = 3000;

  *(undefined4 *)(in_ECX + 0x644) = 3000;

  *(undefined4 *)(in_ECX + 0x648) = 3000;

  *(undefined4 *)(in_ECX + 0x64c) = 3000;

  *(undefined4 *)(in_ECX + 0x650) = 3000;

  puVar18 = (undefined4 *)(in_ECX + 0xb0);

  for (iVar15 = 200; iVar15 != 0; iVar15 = iVar15 + -1) {

    *puVar18 = 0;

    puVar18 = puVar18 + 1;

  }

  pcVar6 = param_3 + 1;

  pcVar5 = param_3;

  do {

    cVar2 = *pcVar5;

    pcVar5 = pcVar5 + 1;

  } while (cVar2 != '\0');

  if ((((param_3[(int)(pcVar5 + (-3 - (int)pcVar6))] == 'd') ||

       (param_3[(int)(pcVar5 + (-3 - (int)pcVar6))] == 'D')) &&

      ((param_3[(int)(pcVar5 + (-2 - (int)pcVar6))] == 'a' ||

       (param_3[(int)(pcVar5 + (-2 - (int)pcVar6))] == 'A')))) &&

     ((param_3[(int)(pcVar5 + (-1 - (int)pcVar6))] == 't' ||

      (param_3[(int)(pcVar5 + (-1 - (int)pcVar6))] == 'T')))) {

    FUN_004148a0(param_3);

    local_4e8 = fopen("data\\temporary.txt","r");

  }

  else {

    local_4e8 = fopen(param_3,"r");

  }

  local_4d0 = 10;

  iVar15 = feof(local_4e8);

  do {

    if (iVar15 != 0) {

      fclose(local_4e8);

      pFVar13 = fopen("data\\temporary.txt","w");

      fprintf(pFVar13,"Do not erase this file.");

      fclose(pFVar13);

      ExceptionList = local_c;

      __security_check_cookie(local_10 ^ (uint)&local_4e8);

      return;

    }

    fscanf(local_4e8,"%s",local_48c);

    pcVar6 = local_48c;

    uVar4 = 0;

    do {

      cVar2 = *pcVar6;

      pcVar6 = pcVar6 + 1;

    } while (cVar2 != '\0');

    if (pcVar6 != local_48c + 1) {

      do {

        DAT_0044f620 = DAT_0044f620 + (int)local_48c[uVar4] * uVar4;

        pcVar6 = local_48c;

        uVar4 = uVar4 + 1;

        do {

          cVar2 = *pcVar6;

          pcVar6 = pcVar6 + 1;

        } while (cVar2 != '\0');

      } while (uVar4 < (uint)((int)pcVar6 - (int)(local_48c + 1)));

    }

    local_4d0 = local_4d0 + -1;

    if (local_4d0 == 0) {

      local_4d0 = 10;

      FUN_0043d230();

    }

    iVar15 = 0xc;

    bVar19 = true;

    pcVar6 = local_48c;

    pcVar5 = "<bmp_begin>";

    do {

      if (iVar15 == 0) break;

      iVar15 = iVar15 + -1;

      bVar19 = *pcVar6 == *pcVar5;

      pcVar6 = pcVar6 + 1;

      pcVar5 = pcVar5 + 1;

    } while (bVar19);

    if (bVar19) {

LAB_0040f1d8:

      if (local_4d4 != 0) {

        FUN_004242e0(local_4d8,local_4d4);

      }

      fscanf(local_4e8,"%s",local_48c);

      iVar15 = 10;

      bVar19 = true;

      pcVar6 = local_48c;

      pcVar5 = "<bmp_end>";

      do {

        if (iVar15 == 0) break;

        iVar15 = iVar15 + -1;

        bVar19 = *pcVar6 == *pcVar5;

        pcVar6 = pcVar6 + 1;

        pcVar5 = pcVar5 + 1;

      } while (bVar19);

      if (!bVar19) {

        iVar15 = 0;

        do {

          cVar2 = local_48c[iVar15];

          local_3c4[iVar15 + 0x30] = cVar2;

          iVar15 = iVar15 + 1;

        } while (cVar2 != '\0');

        local_390 = local_390 & 0xffffff00;

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = (char *)&local_394;

        pcVar5 = "file";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          if (0 < *(int *)(in_ECX + 0x498)) {

            iVar15 = 0;

            *(undefined4 *)(in_ECX + 0x628 + *(int *)(in_ECX + 0x498) * 4) = 0;

            if (0 < *(int *)(in_ECX + 0x498) + -1) {

              piVar7 = (int *)(in_ECX + 0x6a4);

              do {

                piVar1 = (int *)(in_ECX + 0x628 + *(int *)(in_ECX + 0x498) * 4);

                *piVar1 = *piVar1 + piVar7[10] * *piVar7;

                iVar15 = iVar15 + 1;

                piVar7 = piVar7 + 1;

              } while (iVar15 < *(int *)(in_ECX + 0x498) + -1);

            }

            local_4dc = operator_new(0x1f50);

            iVar15 = 0;

            local_4 = 3;

            if (local_4dc == (void *)0x0) {

              uVar8 = 0;

            }

            else {

              uVar8 = FUN_0043ee50(0x40,in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28,0);

            }

            iVar16 = local_4d4;

            local_4 = 0xffffffff;

            *(undefined4 *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

            if (local_4d4 != 0) {

              FUN_004242e0(local_4d8,local_4d4);

            }

            pcVar6 = (char *)(in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28);

            iVar12 = -(int)pcVar6;

            do {

              cVar2 = *pcVar6;

              pcVar6[(int)(local_3c4 + iVar12)] = cVar2;

              pcVar6 = pcVar6 + 1;

            } while (cVar2 != '\0');

            pcVar6 = local_3c4;

            do {

              pcVar5 = pcVar6;

              pcVar6 = pcVar5 + 1;

            } while (*pcVar5 != '\0');

            builtin_strncpy(pcVar5 + -0xffffffff00000004,"_mirror.bmp",0xc);

            local_4dc = operator_new(0x1f50);

            local_4 = 4;

            if (local_4dc == (void *)0x0) {

              uVar8 = 0;

            }

            else {

              uVar8 = FUN_0043ee50(0x40,local_3c4,1);

            }

            local_4 = 0xffffffff;

            *(undefined4 *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

            if (iVar16 != 0) {

              FUN_004242e0(local_4d8,iVar16);

            }

            if (**(int **)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) == 0) {

              local_4dc = operator_new(0x1f50);

              local_4 = 5;

              if (local_4dc == (void *)0x0) {

                uVar8 = 0;

              }

              else {

                uVar8 = FUN_0043ee50(0x40,in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28,0);

              }

              local_4 = 0xffffffff;

              *(undefined4 *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

              memset(&local_394,0,100);

              iVar16 = *(int *)(in_ECX + 0x498);

              local_394 = 100;

              local_390 = 2;

              local_49c = 0;

              local_498 = 0;

              local_494 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar16 * 4) + 4);

              local_490 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar16 * 4) + 8);

              local_4cc = 0;

              local_4c8 = 0;

              local_4c4 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar16 * 4) + 4);

              local_4c0 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar16 * 4) + 8);

              piVar7 = (int *)**(undefined4 **)(in_ECX + 0x778 + iVar16 * 4);

              (**(code **)(*piVar7 + 0x14))

                        (piVar7,&local_49c,**(undefined4 **)(in_ECX + 0x750 + iVar16 * 4),&local_4cc

                         ,0x1000800,&local_394);

              iVar16 = local_4d4;

            }

            if (iVar16 != 0) {

              FUN_004242e0(local_4d8,iVar16);

            }

            iVar16 = *(int *)(in_ECX + 0x498);

            *(int *)(*(int *)(in_ECX + 0x750 + iVar16 * 4) + 0xc) =

                 *(int *)(in_ECX + 0x6c8 + iVar16 * 4) * *(int *)(in_ECX + 0x6a0 + iVar16 * 4);

            iVar16 = *(int *)(in_ECX + 0x498);

            *(int *)(*(int *)(in_ECX + 0x778 + iVar16 * 4) + 0xc) =

                 *(int *)(in_ECX + 0x6c8 + iVar16 * 4) * *(int *)(in_ECX + 0x6a0 + iVar16 * 4);

            if (0 < *(int *)(*(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) + 0xc)) {

              iVar16 = 0x7e0;

              do {

                iVar12 = *(int *)(in_ECX + 0x498);

                *(int *)(iVar16 + -2000 + *(int *)(in_ECX + 0x750 + iVar12 * 4)) =

                     (iVar15 % *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

                     (*(int *)(in_ECX + 0x650 + iVar12 * 4) + 1);

                iVar12 = *(int *)(in_ECX + 0x498);

                *(int *)(iVar16 + *(int *)(in_ECX + 0x750 + iVar12 * 4)) =

                     (iVar15 / *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

                     (*(int *)(in_ECX + 0x678 + iVar12 * 4) + 1);

                *(undefined4 *)

                 (iVar16 + 2000 + *(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4)) =

                     *(undefined4 *)(in_ECX + 0x650 + *(int *)(in_ECX + 0x498) * 4);

                *(undefined4 *)

                 (iVar16 + 4000 + *(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4)) =

                     *(undefined4 *)(in_ECX + 0x678 + *(int *)(in_ECX + 0x498) * 4);

                iVar12 = *(int *)(in_ECX + 0x498);

                *(int *)(iVar16 + -2000 + *(int *)(in_ECX + 0x778 + iVar12 * 4)) =

                     (*(int *)(*(int *)(in_ECX + 0x750 + iVar12 * 4) + 4) -

                     (iVar15 % *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

                     (*(int *)(in_ECX + 0x650 + iVar12 * 4) + 1)) -

                     *(int *)(in_ECX + 0x650 + iVar12 * 4);

                iVar12 = *(int *)(in_ECX + 0x498);

                iVar9 = iVar15 / *(int *)(in_ECX + 0x6a0 + iVar12 * 4);

                iVar15 = iVar15 + 1;

                *(int *)(iVar16 + *(int *)(in_ECX + 0x778 + iVar12 * 4)) =

                     iVar9 * (*(int *)(in_ECX + 0x678 + iVar12 * 4) + 1);

                *(undefined4 *)

                 (iVar16 + 2000 + *(int *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4)) =

                     *(undefined4 *)(in_ECX + 0x650 + *(int *)(in_ECX + 0x498) * 4);

                *(undefined4 *)

                 (iVar16 + 4000 + *(int *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4)) =

                     *(undefined4 *)(in_ECX + 0x678 + *(int *)(in_ECX + 0x498) * 4);

                iVar16 = iVar16 + 4;

              } while (iVar15 < *(int *)(*(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) +

                                        0xc));

            }

          }

          *(int *)(in_ECX + 0x498) = *(int *)(in_ECX + 0x498) + 1;

          fscanf(local_4e8,"%s",in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28);

        }

        iVar15 = 6;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "head:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",in_ECX + 0x700);

          local_4dc = operator_new(0x1f50);

          local_4 = 6;

          if (local_4dc == (void *)0x0) {

            uVar8 = 0;

          }

          else {

            uVar8 = FUN_0043ee50(0x40,in_ECX + 0x700,0);

          }

          local_4 = 0xffffffff;

          *(undefined4 *)(in_ECX + 0x6fc) = uVar8;

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "small:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",in_ECX + 0x72c);

          local_4dc = operator_new(0x1f50);

          local_4 = 7;

          if (local_4dc == (void *)0x0) {

            uVar8 = 0;

          }

          else {

            uVar8 = FUN_0043ee50(0x40,in_ECX + 0x72c,0);

          }

          local_4 = 0xffffffff;

          *(undefined4 *)(in_ECX + 0x728) = uVar8;

        }

        iVar15 = 0x13;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "walking_frame_rate";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d");

        }

        iVar15 = 0xe;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "walking_speed";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 8);

        }

        iVar15 = 0xf;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "walking_speedz";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x10);

        }

        iVar15 = 0x13;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "running_frame_rate";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x18);

        }

        iVar15 = 0xe;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "running_speed";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x20);

        }

        iVar15 = 0xf;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "running_speedz";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x28);

        }

        iVar15 = 0x14;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "heavy_walking_speed";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x30);

        }

        iVar15 = 0x15;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "heavy_walking_speedz";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x38);

        }

        iVar15 = 0x14;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "heavy_running_speed";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x40);

        }

        iVar15 = 0x15;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "heavy_running_speedz";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x48);

        }

        iVar15 = 0xc;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "jump_height";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x50);

        }

        iVar15 = 0xe;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "jump_distance";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x58);

        }

        iVar15 = 0xf;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "jump_distancez";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x60);

        }

        iVar15 = 0xc;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dash_height";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x68);

        }

        iVar15 = 0xe;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dash_distance";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x70);

        }

        iVar15 = 0xf;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dash_distancez";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x78);

        }

        iVar15 = 0xe;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "rowing_height";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x80);

        }

        iVar15 = 0x10;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "rowing_distance";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%lf",in_ECX + 0x88);

        }

        iVar15 = 6;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "name:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",in_ECX + 0x25324);

        }

        iVar15 = 3;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "w:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x650 + *(int *)(in_ECX + 0x498) * 4);

        }

        iVar15 = 3;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "h:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x678 + *(int *)(in_ECX + 0x498) * 4);

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "row:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x6a0 + *(int *)(in_ECX + 0x498) * 4);

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "col:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x6c8 + *(int *)(in_ECX + 0x498) * 4);

        }

        iVar15 = 0xb;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "weapon_hp:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x90);

        }

        iVar15 = 0x12;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "weapon_drop_hurt:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",in_ECX + 0x94);

        }

        iVar15 = 0x12;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "weapon_hit_sound:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",&local_394);

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            pcVar6 = pcVar6 + 1;

          } while (cVar2 != '\0');

          pcVar5 = malloc((size_t)(pcVar6 + (1 - ((int)&local_394 + 1))));

          *(char **)(in_ECX + 0x98) = pcVar5;

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            *pcVar5 = cVar2;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (cVar2 != '\0');

          FUN_0040bd90(*(undefined4 *)(in_ECX + 0x98),in_ECX + 0xa4);

        }

        iVar15 = 0x13;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "weapon_drop_sound:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",&local_394);

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            pcVar6 = pcVar6 + 1;

          } while (cVar2 != '\0');

          pcVar5 = malloc((size_t)(pcVar6 + (1 - ((int)&local_394 + 1))));

          *(char **)(in_ECX + 0x9c) = pcVar5;

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            *pcVar5 = cVar2;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (cVar2 != '\0');

          FUN_0040bd90(*(undefined4 *)(in_ECX + 0x9c),in_ECX + 0xa8);

        }

        iVar15 = 0x15;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "weapon_broken_sound:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",&local_394);

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            pcVar6 = pcVar6 + 1;

          } while (cVar2 != '\0');

          pcVar5 = malloc((size_t)(pcVar6 + (1 - ((int)&local_394 + 1))));

          *(char **)(in_ECX + 0xa0) = pcVar5;

          pcVar6 = (char *)&local_394;

          do {

            cVar2 = *pcVar6;

            *pcVar5 = cVar2;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (cVar2 != '\0');

          FUN_0040bd90(*(undefined4 *)(in_ECX + 0xa0),in_ECX + 0xac);

        }

        goto LAB_0040f1d8;

      }

      iVar16 = 0;

      *(undefined4 *)(in_ECX + 0x628 + *(int *)(in_ECX + 0x498) * 4) = 0;

      iVar15 = 0;

      if (0 < *(int *)(in_ECX + 0x498) + -1) {

        piVar7 = (int *)(in_ECX + 0x6a4);

        do {

          piVar1 = (int *)(in_ECX + 0x628 + *(int *)(in_ECX + 0x498) * 4);

          *piVar1 = *piVar1 + piVar7[10] * *piVar7;

          iVar15 = iVar15 + 1;

          piVar7 = piVar7 + 1;

        } while (iVar15 < *(int *)(in_ECX + 0x498) + -1);

      }

      local_4dc = operator_new(0x1f50);

      local_4 = 0;

      if (local_4dc == (void *)0x0) {

        uVar8 = 0;

      }

      else {

        uVar8 = FUN_0043ee50(0x40,in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28,0);

      }

      iVar15 = local_4d4;

      local_4 = 0xffffffff;

      *(undefined4 *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

      if (local_4d4 != 0) {

        FUN_004242e0(local_4d8,local_4d4);

      }

      pcVar6 = (char *)(in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28);

      iVar12 = -(int)pcVar6;

      do {

        cVar2 = *pcVar6;

        pcVar6[(int)(local_3c4 + iVar12)] = cVar2;

        pcVar6 = pcVar6 + 1;

      } while (cVar2 != '\0');

      pcVar6 = local_3c4;

      do {

        pcVar5 = pcVar6;

        pcVar6 = pcVar5 + 1;

      } while (*pcVar5 != '\0');

      builtin_strncpy(pcVar5 + -0xffffffff00000004,"_mirror.bmp",0xc);

      local_4dc = operator_new(0x1f50);

      local_4 = 1;

      if (local_4dc == (void *)0x0) {

        uVar8 = 0;

      }

      else {

        uVar8 = FUN_0043ee50(0x40,local_3c4,1);

      }

      local_4 = 0xffffffff;

      *(undefined4 *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

      if (iVar15 != 0) {

        FUN_004242e0(local_4d8,iVar15);

      }

      if (**(int **)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) == 0) {

        local_4dc = operator_new(0x1f50);

        local_4 = 2;

        if (local_4dc == (void *)0x0) {

          uVar8 = 0;

        }

        else {

          uVar8 = FUN_0043ee50(0x40,in_ECX + 0x474 + *(int *)(in_ECX + 0x498) * 0x28,0);

        }

        local_4 = 0xffffffff;

        *(undefined4 *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4) = uVar8;

        memset(&local_394,0,100);

        iVar15 = *(int *)(in_ECX + 0x498);

        local_390 = 2;

        local_394 = 100;

        local_4ac = 0;

        local_4a8 = 0;

        local_4a4 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar15 * 4) + 4);

        local_4a0 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar15 * 4) + 8);

        local_4bc = 0;

        local_4b8 = 0;

        local_4b4 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar15 * 4) + 4);

        local_4b0 = *(undefined4 *)(*(int *)(in_ECX + 0x750 + iVar15 * 4) + 8);

        piVar7 = (int *)**(undefined4 **)(in_ECX + 0x778 + iVar15 * 4);

        (**(code **)(*piVar7 + 0x14))

                  (piVar7,&local_4ac,**(undefined4 **)(in_ECX + 0x750 + iVar15 * 4),&local_4bc,

                   0x1000800,&local_394);

        iVar15 = local_4d4;

      }

      if (iVar15 != 0) {

        FUN_004242e0(local_4d8,iVar15);

      }

      iVar15 = *(int *)(in_ECX + 0x498);

      *(int *)(*(int *)(in_ECX + 0x750 + iVar15 * 4) + 0xc) =

           *(int *)(in_ECX + 0x6c8 + iVar15 * 4) * *(int *)(in_ECX + 0x6a0 + iVar15 * 4);

      iVar15 = *(int *)(in_ECX + 0x498);

      *(int *)(*(int *)(in_ECX + 0x778 + iVar15 * 4) + 0xc) =

           *(int *)(in_ECX + 0x6c8 + iVar15 * 4) * *(int *)(in_ECX + 0x6a0 + iVar15 * 4);

      if (0 < *(int *)(*(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) + 0xc)) {

        iVar15 = 0x7e0;

        do {

          iVar12 = *(int *)(in_ECX + 0x498);

          *(int *)(iVar15 + -2000 + *(int *)(in_ECX + 0x750 + iVar12 * 4)) =

               (iVar16 % *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

               (*(int *)(in_ECX + 0x650 + iVar12 * 4) + 1);

          iVar12 = *(int *)(in_ECX + 0x498);

          *(int *)(iVar15 + *(int *)(in_ECX + 0x750 + iVar12 * 4)) =

               (iVar16 / *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

               (*(int *)(in_ECX + 0x678 + iVar12 * 4) + 1);

          *(undefined4 *)(iVar15 + 2000 + *(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4)) =

               *(undefined4 *)(in_ECX + 0x650 + *(int *)(in_ECX + 0x498) * 4);

          *(undefined4 *)(iVar15 + 4000 + *(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4)) =

               *(undefined4 *)(in_ECX + 0x678 + *(int *)(in_ECX + 0x498) * 4);

          iVar12 = *(int *)(in_ECX + 0x498);

          *(int *)(iVar15 + -2000 + *(int *)(in_ECX + 0x778 + iVar12 * 4)) =

               (*(int *)(*(int *)(in_ECX + 0x750 + iVar12 * 4) + 4) -

               (iVar16 % *(int *)(in_ECX + 0x6a0 + iVar12 * 4)) *

               (*(int *)(in_ECX + 0x650 + iVar12 * 4) + 1)) - *(int *)(in_ECX + 0x650 + iVar12 * 4);

          iVar12 = *(int *)(in_ECX + 0x498);

          iVar9 = iVar16 / *(int *)(in_ECX + 0x6a0 + iVar12 * 4);

          iVar16 = iVar16 + 1;

          *(int *)(iVar15 + *(int *)(in_ECX + 0x778 + iVar12 * 4)) =

               iVar9 * (*(int *)(in_ECX + 0x678 + iVar12 * 4) + 1);

          *(undefined4 *)(iVar15 + 2000 + *(int *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4)) =

               *(undefined4 *)(in_ECX + 0x650 + *(int *)(in_ECX + 0x498) * 4);

          *(undefined4 *)(iVar15 + 4000 + *(int *)(in_ECX + 0x778 + *(int *)(in_ECX + 0x498) * 4)) =

               *(undefined4 *)(in_ECX + 0x678 + *(int *)(in_ECX + 0x498) * 4);

          iVar15 = iVar15 + 4;

        } while (iVar16 < *(int *)(*(int *)(in_ECX + 0x750 + *(int *)(in_ECX + 0x498) * 4) + 0xc));

      }

    }

    iVar15 = 0x17;

    bVar19 = true;

    pcVar6 = local_48c;

    pcVar5 = "<weapon_strength_list>";

    do {

      if (iVar15 == 0) break;

      iVar15 = iVar15 + -1;

      bVar19 = *pcVar6 == *pcVar5;

      pcVar6 = pcVar6 + 1;

      pcVar5 = pcVar5 + 1;

    } while (bVar19);

    if (bVar19) {

      local_4e0 = (byte *)0x0;

      fscanf(local_4e8,"%s",local_48c);

      iVar15 = 0x1b;

      bVar19 = true;

      pcVar6 = local_48c;

      pcVar5 = "<weapon_strength_list_end>";

      do {

        if (iVar15 == 0) break;

        iVar15 = iVar15 + -1;

        bVar19 = *pcVar6 == *pcVar5;

        pcVar6 = pcVar6 + 1;

        pcVar5 = pcVar5 + 1;

      } while (bVar19);

joined_r0x004101a7:

      if (!bVar19) {

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "entry:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d %s",&local_4e0,in_ECX + 0x3d0 + (int)local_4e0 * 0x1e);

        }

        else {

          iVar15 = 5;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "dvx:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

          if (bVar19) {

            iVar15 = (int)local_4e0 * 0x50 + 0xc4 + in_ECX;

          }

          else {

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvy:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = (int)local_4e0 * 0x50 + 200 + in_ECX;

            }

            else {

              iVar15 = 6;

              bVar19 = true;

              pcVar6 = local_48c;

              pcVar5 = "fall:";

              do {

                if (iVar15 == 0) break;

                iVar15 = iVar15 + -1;

                bVar19 = *pcVar6 == *pcVar5;

                pcVar6 = pcVar6 + 1;

                pcVar5 = pcVar5 + 1;

              } while (bVar19);

              if (bVar19) {

                iVar15 = (int)local_4e0 * 0x50 + 0xcc + in_ECX;

              }

              else {

                iVar15 = 7;

                bVar19 = true;

                pcVar6 = local_48c;

                pcVar5 = "arest:";

                do {

                  if (iVar15 == 0) break;

                  iVar15 = iVar15 + -1;

                  bVar19 = *pcVar6 == *pcVar5;

                  pcVar6 = pcVar6 + 1;

                  pcVar5 = pcVar5 + 1;

                } while (bVar19);

                if (bVar19) {

                  iVar15 = (int)local_4e0 * 0x50 + 0xd0 + in_ECX;

                }

                else {

                  iVar15 = 7;

                  bVar19 = true;

                  pcVar6 = local_48c;

                  pcVar5 = "vrest:";

                  do {

                    if (iVar15 == 0) break;

                    iVar15 = iVar15 + -1;

                    bVar19 = *pcVar6 == *pcVar5;

                    pcVar6 = pcVar6 + 1;

                    pcVar5 = pcVar5 + 1;

                  } while (bVar19);

                  if (bVar19) {

                    iVar15 = (int)local_4e0 * 0x50 + 0xd4 + in_ECX;

                  }

                  else {

                    iVar15 = 9;

                    bVar19 = true;

                    pcVar6 = local_48c;

                    pcVar5 = "respond:";

                    do {

                      if (iVar15 == 0) break;

                      iVar15 = iVar15 + -1;

                      bVar19 = *pcVar6 == *pcVar5;

                      pcVar6 = pcVar6 + 1;

                      pcVar5 = pcVar5 + 1;

                    } while (bVar19);

                    if (bVar19) {

                      iVar15 = (int)local_4e0 * 0x50 + 0xd8 + in_ECX;

                    }

                    else {

                      iVar15 = 9;

                      bVar19 = true;

                      pcVar6 = local_48c;

                      pcVar5 = "bdefend:";

                      do {

                        if (iVar15 == 0) break;

                        iVar15 = iVar15 + -1;

                        bVar19 = *pcVar6 == *pcVar5;

                        pcVar6 = pcVar6 + 1;

                        pcVar5 = pcVar5 + 1;

                      } while (bVar19);

                      if (!bVar19) {

                        iVar15 = 8;

                        bVar19 = true;

                        pcVar6 = local_48c;

                        pcVar5 = "injury:";

                        do {

                          if (iVar15 == 0) break;

                          iVar15 = iVar15 + -1;

                          bVar19 = *pcVar6 == *pcVar5;

                          pcVar6 = pcVar6 + 1;

                          pcVar5 = pcVar5 + 1;

                        } while (bVar19);

                        if (bVar19) {

                          iVar15 = (int)local_4e0 * 0x50 + 0xf4 + in_ECX;

                        }

                        else {

                          iVar15 = 8;

                          bVar19 = true;

                          pcVar6 = local_48c;

                          pcVar5 = "zwidth:";

                          do {

                            if (iVar15 == 0) break;

                            iVar15 = iVar15 + -1;

                            bVar19 = *pcVar6 == *pcVar5;

                            pcVar6 = pcVar6 + 1;

                            pcVar5 = pcVar5 + 1;

                          } while (bVar19);

                          if (bVar19) {

                            iVar15 = (int)local_4e0 * 0x50 + 0xf8 + in_ECX;

                          }

                          else {

                            iVar15 = 8;

                            bVar19 = true;

                            pcVar6 = local_48c;

                            pcVar5 = "effect:";

                            do {

                              if (iVar15 == 0) break;

                              iVar15 = iVar15 + -1;

                              bVar19 = *pcVar6 == *pcVar5;

                              pcVar6 = pcVar6 + 1;

                              pcVar5 = pcVar5 + 1;

                            } while (bVar19);

                            if (!bVar19) goto LAB_004103cc;

                            iVar15 = (int)local_4e0 * 0x50 + 0xdc + in_ECX;

                          }

                        }

                      }

                      else {

                        iVar15 = ((int)local_4e0 * 5 + 0xf) * 0x10 + in_ECX;

                      }

                    }

                  }

                }

              }

            }

          }

          fscanf(local_4e8,"%d",iVar15);

        }

LAB_004103cc:

        fscanf(local_4e8,"%s",local_48c);

        iVar15 = 0x1b;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "<weapon_strength_list_end>";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        goto joined_r0x004101a7;

      }

    }

    pFVar13 = local_4e8;

    iVar15 = 8;

    bVar19 = true;

    pcVar6 = local_48c;

    pcVar5 = "<frame>";

    do {

      if (iVar15 == 0) break;

      iVar15 = iVar15 + -1;

      bVar19 = *pcVar6 == *pcVar5;

      pcVar6 = pcVar6 + 1;

      pcVar5 = pcVar5 + 1;

    } while (bVar19);

    if (bVar19) {

      fscanf(local_4e8,"%d",&iStack_4e4);

      fscanf(pFVar13,"%s",iStack_4e4 * 0x178 + 0x900 + in_ECX);

      *(undefined4 *)((iStack_4e4 + 6) * 0x178 + in_ECX) = 0;

      *(undefined4 *)(iStack_4e4 * 0x178 + 0x8cc + in_ECX) = 0;

      *(undefined1 *)(iStack_4e4 * 0x178 + 0x7a4 + in_ECX) = 1;

      sprintf(acStack_13c,"%d",iStack_4e4);

      fscanf(pFVar13,"%s",local_48c);

      iVar15 = 0xc;

      bVar19 = true;

      pcVar6 = local_48c;

      pcVar5 = "<frame_end>";

      do {

        if (iVar15 == 0) break;

        iVar15 = iVar15 + -1;

        bVar19 = *pcVar6 == *pcVar5;

        pcVar6 = pcVar6 + 1;

        pcVar5 = pcVar5 + 1;

      } while (bVar19);

joined_r0x004104b3:

      if (!bVar19) {

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "pic:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7a8 + in_ECX);

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "state:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7ac + in_ECX);

        }

        iVar15 = 6;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "wait:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7b0 + in_ECX);

        }

        iVar15 = 6;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "next:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7b4 + in_ECX);

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dvx:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7b8 + in_ECX);

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dvy:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7bc + in_ECX);

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "dvz:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7c0 + in_ECX);

        }

        iVar15 = 9;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "centerx:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7f4 + in_ECX);

        }

        iVar15 = 9;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "centery:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7f8 + in_ECX);

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_a:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7c8 + in_ECX);

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_d:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7cc + in_ECX);

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_j:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 2000 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Fa:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7d4 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Ua:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7d8 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Da:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7dc + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Fj:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7e0 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Uj:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7e4 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_Dj:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7e8 + in_ECX);

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "hit_ja:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7ec + in_ECX);

        }

        iVar15 = 4;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "mp:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7f0 + in_ECX);

        }

        iVar15 = 7;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "sound:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",acStack_268);

          pcVar6 = acStack_268;

          do {

            cVar2 = *pcVar6;

            pcVar6 = pcVar6 + 1;

          } while (cVar2 != '\0');

          pvVar10 = malloc((size_t)(pcVar6 + (1 - (int)(acStack_268 + 1))));

          *(void **)(iStack_4e4 * 0x178 + 0x914 + in_ECX) = pvVar10;

          pcVar5 = *(char **)(iStack_4e4 * 0x178 + 0x914 + in_ECX);

          pcVar6 = acStack_268;

          do {

            cVar2 = *pcVar6;

            *pcVar5 = cVar2;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (cVar2 != '\0');

          iVar15 = 0;

          *(undefined4 *)(iStack_4e4 * 0x178 + 0x918 + in_ECX) = 0xffffffff;

          if (0 < DAT_00458438) {

            local_4e0 = *(byte **)(iStack_4e4 * 0x178 + 0x914 + in_ECX);

            local_4dc = (void *)(iStack_4e4 * 0x178 + in_ECX);

            pbVar14 = (byte*)&DAT_00455638;

            do {

              pbVar11 = local_4e0;

              pbVar17 = pbVar14;

              do {

                bVar3 = *pbVar11;

                bVar19 = bVar3 < *pbVar17;

                if (bVar3 != *pbVar17) {

LAB_004109d6:

                  iVar16 = (1 - (uint)bVar19) - (uint)(bVar19 != 0);

                  goto LAB_004109db;

                }

                if (bVar3 == 0) break;

                bVar3 = pbVar11[1];

                bVar19 = bVar3 < pbVar17[1];

                if (bVar3 != pbVar17[1]) goto LAB_004109d6;

                pbVar11 = pbVar11 + 2;

                pbVar17 = pbVar17 + 2;

              } while (bVar3 != 0);

              iVar16 = 0;

LAB_004109db:

              if (iVar16 == 0) {

                *(int *)((int)local_4dc + 0x918) = iVar15;

                break;

              }

              iVar15 = iVar15 + 1;

              pbVar14 = pbVar14 + 0x14;

            } while (iVar15 < DAT_00458438);

          }

          if (*(int *)(iStack_4e4 * 0x178 + 0x918 + in_ECX) == -1) {

            *(int *)(iStack_4e4 * 0x178 + 0x918 + in_ECX) = DAT_00458438;

            if (DAT_0044eecc != 0) {

              FUN_004014e0(*(undefined4 *)(iStack_4e4 * 0x178 + 0x914 + in_ECX));

              (**(code **)(*(int *)(&DAT_00452948)[DAT_00458438] + 0x3c))

                        ((int *)(&DAT_00452948)[DAT_00458438],0xffffd8f0);

            }

            pcVar5 = *(char **)(iStack_4e4 * 0x178 + 0x914 + in_ECX);

            pcVar6 = (char*)&DAT_00455638 + DAT_00458438 * 0x14;

            do {

              cVar2 = *pcVar5;

              *pcVar6 = cVar2;

              pcVar5 = pcVar5 + 1;

              pcVar6 = pcVar6 + 1;

            } while (cVar2 != '\0');

            DAT_00458438 = DAT_00458438 + 1;

          }

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "opoint:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 0xc;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "opoint_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x00410add:

          if (!bVar19) {

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "kind:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x7fc + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x800 + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x804 + in_ECX);

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "action:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x808 + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvx:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x80c + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvy:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x810 + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "oid:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x814 + in_ECX);

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "facing:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x818 + in_ECX);

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "opoint_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x00410add;

          }

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "bpoint:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 0xc;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "bpoint_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x00410d02:

          if (!bVar19) {

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x824 + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x828 + in_ECX);

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "bpoint_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x00410d02;

          }

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "cpoint:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 0xc;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "cpoint_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x00410de4:

          if (!bVar19) {

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "kind:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x82c + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x830 + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x834 + in_ECX);

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "injury:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x838 + in_ECX);

            }

            iVar15 = 7;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "cover:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x83c + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "vaction:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x840 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "aaction:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x844 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "jaction:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x848 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "taction:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x864 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "daction:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x84c + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "throwvx:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x850 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "throwvy:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x854 + in_ECX);

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "throwvz:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x86c + in_ECX);

            }

            iVar15 = 10;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "hurtable:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x858 + in_ECX);

            }

            iVar15 = 0xd;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "throwinjury:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x868 + in_ECX);

            }

            iVar15 = 0xe;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "fronthurtact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x838 + in_ECX);

            }

            iVar15 = 0xd;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "backhurtact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x83c + in_ECX);

            }

            iVar15 = 10;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "decrease:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x85c + in_ECX);

            }

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dircontrol:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x860 + in_ECX);

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "cpoint_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x00410de4;

          }

        }

        iVar15 = 8;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "wpoint:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 0xc;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "wpoint_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x00411249:

          if (!bVar19) {

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "kind:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x87c + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x880 + in_ECX);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x884 + in_ECX);

            }

            iVar15 = 0xb;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "weaponact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x888 + in_ECX);

            }

            iVar15 = 0xb;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "attacking:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x88c + in_ECX);

            }

            iVar15 = 7;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "cover:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x890 + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvx:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x894 + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvy:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x898 + in_ECX);

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvz:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",iStack_4e4 * 0x178 + 0x89c + in_ECX);

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "wpoint_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x00411249;

          }

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "itr:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          piVar7 = (int *)(iStack_4e4 * 0x178 + 0x8cc + in_ECX);

          *piVar7 = *piVar7 + 1;

          if (*(int *)(iStack_4e4 * 0x178 + 0x8cc + in_ECX) == 1) {

            pvVar10 = malloc(400);

            *(void **)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX) = pvVar10;

          }

          iVar15 = 0;

          do {

            *(undefined4 *)

             (*(int *)(iStack_4e4 * 0x178 + in_ECX + 0x8d4) + -0x50 +

             (iVar15 + *(int *)(iStack_4e4 * 0x178 + 0x8cc + in_ECX) * 0x14) * 4) = 0;

            iVar16 = iStack_4e4 * 0x178 + in_ECX;

            *(undefined4 *)

             (*(int *)(iVar16 + 0x8d4) + -0x4c + (iVar15 + *(int *)(iVar16 + 0x8cc) * 0x14) * 4) = 0

            ;

            iVar16 = iStack_4e4 * 0x178 + in_ECX;

            *(undefined4 *)

             (*(int *)(iVar16 + 0x8d4) + -0x48 + (iVar15 + *(int *)(iVar16 + 0x8cc) * 0x14) * 4) = 0

            ;

            iVar16 = iStack_4e4 * 0x178 + in_ECX;

            *(undefined4 *)

             (*(int *)(iVar16 + 0x8d4) + -0x44 + (iVar15 + *(int *)(iVar16 + 0x8cc) * 0x14) * 4) = 0

            ;

            iVar16 = iStack_4e4 * 0x178 + in_ECX;

            iVar12 = iVar15 + *(int *)(iVar16 + 0x8cc) * 0x14;

            iVar15 = iVar15 + 5;

            *(undefined4 *)(*(int *)(iVar16 + 0x8d4) + -0x40 + iVar12 * 4) = 0;

          } while (iVar15 < 0x14);

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 9;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "itr_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x004115b1:

          if (!bVar19) {

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "kind:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x50 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x4c + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x48 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "w:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x44 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "h:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x40 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvx:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x3c + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 5;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "dvy:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x38 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "fall:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x34 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 7;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "arest:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x30 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 7;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "vrest:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x2c + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "respond:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x28 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "bdefend:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x10 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "injury:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0xc + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "zwidth:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",*(int *)(iVar15 + 0x8cc) * 0x50 + -8 + *(int *)(iVar15 + 0x8d4))

              ;

            }

            iVar15 = 8;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "effect:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x24 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 0xd;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "catchingact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              iVar15 = *(int *)(iVar15 + 0x8d4) + *(int *)(iVar15 + 0x8cc) * 0x50;

              fscanf(local_4e8,"%d %d",iVar15 + -0x20,iVar15 + -0x1c);

            }

            iVar15 = 0xb;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "caughtact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              iVar15 = *(int *)(iVar15 + 0x8d4) + *(int *)(iVar15 + 0x8cc) * 0x50;

              fscanf(local_4e8,"%d %d",iVar15 + -0x18,iVar15 + -0x14);

            }

            iVar15 = 0xc;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "pickingact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x20 + *(int *)(iVar15 + 0x8d4));

            }

            iVar15 = 0xb;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "pickedact:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              iVar15 = iStack_4e4 * 0x178 + in_ECX;

              fscanf(local_4e8,"%d",

                     *(int *)(iVar15 + 0x8cc) * 0x50 + -0x1c + *(int *)(iVar15 + 0x8d4));

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "itr_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x004115b1;

          }

        }

        iVar15 = 5;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "bdy:";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        if (bVar19) {

          piVar7 = (int *)((iStack_4e4 + 6) * 0x178 + in_ECX);

          *piVar7 = *piVar7 + 1;

          if (*(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) == 1) {

            pvVar10 = malloc(200);

            *(void **)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) = pvVar10;

          }

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x28 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x24 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x20 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x1c +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x18 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x14 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x10 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0xc +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -8 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          *(undefined4 *)

           (*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -4 +

           *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28) = 0;

          fscanf(local_4e8,"%s",local_48c);

          iVar15 = 9;

          bVar19 = true;

          pcVar6 = local_48c;

          pcVar5 = "bdy_end:";

          do {

            if (iVar15 == 0) break;

            iVar15 = iVar15 + -1;

            bVar19 = *pcVar6 == *pcVar5;

            pcVar6 = pcVar6 + 1;

            pcVar5 = pcVar5 + 1;

          } while (bVar19);

joined_r0x00411d29:

          if (!bVar19) {

            iVar15 = 6;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "kind:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",

                     *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x28 +

                     *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "x:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",

                     *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x24 +

                     *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "y:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",

                     *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x20 +

                     *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "w:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",

                     *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x1c +

                     *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28);

            }

            iVar15 = 3;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "h:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            if (bVar19) {

              fscanf(local_4e8,"%d",

                     *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + -0x18 +

                     *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX) * 0x28);

            }

            fscanf(local_4e8,"%s",local_48c);

            iVar15 = 9;

            bVar19 = true;

            pcVar6 = local_48c;

            pcVar5 = "bdy_end:";

            do {

              if (iVar15 == 0) break;

              iVar15 = iVar15 + -1;

              bVar19 = *pcVar6 == *pcVar5;

              pcVar6 = pcVar6 + 1;

              pcVar5 = pcVar5 + 1;

            } while (bVar19);

            goto joined_r0x00411d29;

          }

        }

        fscanf(local_4e8,"%s",local_48c);

        iVar15 = 0xc;

        bVar19 = true;

        pcVar6 = local_48c;

        pcVar5 = "<frame_end>";

        do {

          if (iVar15 == 0) break;

          iVar15 = iVar15 + -1;

          bVar19 = *pcVar6 == *pcVar5;

          pcVar6 = pcVar6 + 1;

          pcVar5 = pcVar5 + 1;

        } while (bVar19);

        goto joined_r0x004104b3;

      }

      iVar15 = iStack_4e4 * 0x178 + in_ECX;

      if (0 < *(int *)(iVar15 + 0x8cc)) {

        *(undefined4 *)(iVar15 + 0x8dc) = *(undefined4 *)(*(int *)(iVar15 + 0x8d4) + 4);

        *(undefined4 *)(iStack_4e4 * 0x178 + in_ECX + 0x8e0) =

             *(undefined4 *)(*(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX) + 8);

        iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX);

        *(int *)(iStack_4e4 * 0x178 + in_ECX + 0x8e4) =

             *(int *)(iVar15 + 0xc) + *(int *)(iVar15 + 4);

        iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX);

        *(int *)(iStack_4e4 * 0x178 + in_ECX + 0x8e8) =

             *(int *)(iVar15 + 0x10) + *(int *)(iVar15 + 8);

        iVar15 = iStack_4e4 * 0x178 + in_ECX;

        local_4e0 = (byte *)0x1;

        if (1 < *(int *)(iVar15 + 0x8cc)) {

          iVar16 = 0x50;

          do {

            iVar12 = *(int *)(*(int *)(iVar15 + 0x8d4) + 4 + iVar16);

            if (iVar12 < *(int *)(iVar15 + 0x8dc)) {

              *(int *)(iVar15 + 0x8dc) = iVar12;

            }

            iVar15 = *(int *)(*(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX) + 8 + iVar16);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (iVar15 < *(int *)(iVar12 + 0x8e0)) {

              *(int *)(iVar12 + 0x8e0) = iVar15;

            }

            iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (*(int *)(iVar12 + 0x8e4) <

                *(int *)(iVar15 + 0xc + iVar16) + *(int *)(iVar15 + 4 + iVar16)) {

              *(int *)(iVar12 + 0x8e4) =

                   *(int *)(*(int *)(iVar12 + 0x8d4) + 0xc + iVar16) +

                   *(int *)(*(int *)(iVar12 + 0x8d4) + iVar16 + 4);

            }

            iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d4 + in_ECX);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (*(int *)(iVar12 + 0x8e8) <

                *(int *)(iVar15 + 0x10 + iVar16) + *(int *)(iVar15 + 8 + iVar16)) {

              *(int *)(iVar12 + 0x8e8) =

                   *(int *)(*(int *)(iVar12 + 0x8d4) + 0x10 + iVar16) +

                   *(int *)(*(int *)(iVar12 + 0x8d4) + iVar16 + 8);

            }

            local_4e0 = local_4e0 + 1;

            iVar15 = iStack_4e4 * 0x178 + in_ECX;

            iVar16 = iVar16 + 0x50;

          } while ((int)local_4e0 < *(int *)(iVar15 + 0x8cc));

        }

        piVar7 = (int *)(iStack_4e4 * 0x178 + 0x8e4 + in_ECX);

        *piVar7 = *piVar7 - *(int *)(iStack_4e4 * 0x178 + 0x8dc + in_ECX);

        piVar7 = (int *)(iStack_4e4 * 0x178 + in_ECX + 0x8e8);

        *piVar7 = *piVar7 - *(int *)(iStack_4e4 * 0x178 + 0x8e0 + in_ECX);

      }

      if (0 < *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX)) {

        *(undefined4 *)(iStack_4e4 * 0x178 + 0x8ec + in_ECX) =

             *(undefined4 *)(*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + 4);

        *(undefined4 *)(iStack_4e4 * 0x178 + in_ECX + 0x8f0) =

             *(undefined4 *)(*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + 8);

        iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX);

        *(int *)(iStack_4e4 * 0x178 + in_ECX + 0x8f4) =

             *(int *)(iVar15 + 0xc) + *(int *)(iVar15 + 4);

        iVar15 = *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX);

        *(int *)(iStack_4e4 * 0x178 + in_ECX + 0x8f8) =

             *(int *)(iVar15 + 0x10) + *(int *)(iVar15 + 8);

        local_4e0 = (byte *)0x1;

        if (1 < *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX)) {

          iVar15 = 0x28;

          do {

            iVar16 = *(int *)(*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + 4 + iVar15);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (iVar16 < *(int *)(iVar12 + 0x8ec)) {

              *(int *)(iVar12 + 0x8ec) = iVar16;

            }

            iVar16 = *(int *)(*(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX) + 8 + iVar15);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (iVar16 < *(int *)(iVar12 + 0x8f0)) {

              *(int *)(iVar12 + 0x8f0) = iVar16;

            }

            iVar16 = *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (*(int *)(iVar12 + 0x8f4) <

                *(int *)(iVar16 + 0xc + iVar15) + *(int *)(iVar16 + 4 + iVar15)) {

              *(int *)(iVar12 + 0x8f4) =

                   *(int *)(*(int *)(iVar12 + 0x8d8) + 0xc + iVar15) +

                   *(int *)(*(int *)(iVar12 + 0x8d8) + iVar15 + 4);

            }

            iVar16 = *(int *)(iStack_4e4 * 0x178 + 0x8d8 + in_ECX);

            iVar12 = iStack_4e4 * 0x178 + in_ECX;

            if (*(int *)(iVar12 + 0x8f8) <

                *(int *)(iVar16 + 0x10 + iVar15) + *(int *)(iVar16 + 8 + iVar15)) {

              *(int *)(iVar12 + 0x8f8) =

                   *(int *)(*(int *)(iVar12 + 0x8d8) + 0x10 + iVar15) +

                   *(int *)(*(int *)(iVar12 + 0x8d8) + iVar15 + 8);

            }

            local_4e0 = local_4e0 + 1;

            iVar15 = iVar15 + 0x28;

          } while ((int)local_4e0 < *(int *)((iStack_4e4 + 6) * 0x178 + in_ECX));

        }

        piVar7 = (int *)(iStack_4e4 * 0x178 + 0x8f4 + in_ECX);

        *piVar7 = *piVar7 - *(int *)(iStack_4e4 * 0x178 + 0x8ec + in_ECX);

        piVar7 = (int *)(iStack_4e4 * 0x178 + 0x8f8 + in_ECX);

        *piVar7 = *piVar7 - *(int *)(iStack_4e4 * 0x178 + 0x8f0 + in_ECX);

      }

    }

    iVar15 = feof(local_4e8);

  } while( true );

}



