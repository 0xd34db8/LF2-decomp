/* Function: FUN_0040c910 */
/* Address: 0x0040c910 */

void FUN_0040c910(void)

{
  FILE *pFVar1;
  undefined4 *puVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  bool bVar9;
  undefined1 auStack_f4 [4];
  int local_f0;
  FILE *local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  char local_d8 [204];
  uint local_c;
  
  local_c = DAT_0044eea4 ^ (uint)auStack_f4;
  FUN_00414a30("data\\stage.dat","data\\temporary.txt");
  pFVar1 = fopen("data\\temporary.txt","r");
  puVar2 = (undefined4 *)(in_ECX + 2000);
  iVar4 = 0x3c;
  do {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 0x526c2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  local_ec = pFVar1;
  iVar4 = feof(pFVar1);
  do {
    if (iVar4 != 0) {
      fclose(pFVar1);
      pFVar1 = fopen("data\\temporary.txt","w");
      fprintf(pFVar1,"Do not erase this file.");
      fclose(pFVar1);
      __security_check_cookie(local_c ^ (uint)auStack_f4);
      return;
    }
    fscanf(pFVar1,"%s",local_d8);
    iVar4 = 8;
    bVar9 = true;
    pcVar6 = local_d8;
    pcVar8 = "<stage>";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar9 = *pcVar6 == *pcVar8;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    } while (bVar9);
    if (bVar9) {
      do {
        fscanf(local_ec,"%s",local_d8);
        iVar4 = 4;
        bVar9 = true;
        pcVar6 = local_d8;
        pcVar8 = "id:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar9 = *pcVar6 == *pcVar8;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
        if (bVar9) {
          fscanf(local_ec,"%d",&local_f0);
          iVar4 = 0;
          do {
            *(undefined4 *)(local_f0 * 0x149b08 + iVar4 + 0x7d8 + in_ECX) = 0xffffffff;
            *(undefined4 *)(local_f0 * 0x149b08 + iVar4 + 0x3c90 + in_ECX) = 0xffffffff;
            *(undefined1 *)(local_f0 * 0x149b08 + iVar4 + 0x7dc + in_ECX) = 0;
            iVar3 = 0;
            iVar5 = iVar4 + 0x8c0;
            do {
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8bc + in_ECX) = 0xffffffff;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar5 + in_ECX) = 500;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8c4 + in_ECX) = 500;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8c8 + in_ECX) = 1;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8cc + in_ECX) = 0;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8e8 + in_ECX) = 0;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8d0 + in_ECX) = 0;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8d4 + in_ECX) = 0;
              iVar5 = iVar5 + 0xe0;
              *(undefined8 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8e0 + in_ECX) = 0;
              *(undefined4 *)(local_f0 * 0x149b08 + iVar3 + iVar4 + 0x8dc + in_ECX) = 0;
              iVar7 = local_f0 * 0x149b08 + iVar3;
              iVar3 = iVar3 + 0xe0;
              *(undefined4 *)(iVar7 + iVar4 + 0x8d8 + in_ECX) = 9;
            } while (iVar3 < 0x3480);
            iVar4 = iVar4 + 0x34c0;
          } while (iVar4 < 0x149b00);
          *(undefined4 *)(local_f0 * 0x149b08 + 2000 + in_ECX) = 0xffffffff;
          local_e0 = 0;
        }
        iVar4 = 8;
        bVar9 = true;
        pcVar6 = local_d8;
        pcVar8 = "<phase>";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar9 = *pcVar6 == *pcVar8;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
        if (bVar9) {
          local_e8 = local_e0 * 0x34c0;
          *(undefined1 *)(local_f0 * 0x149b08 + local_e8 + 0x7dc + in_ECX) = 0;
          local_dc = local_e0 + 1;
          local_e0 = local_e8 + 0x7e0;
          *(int *)(local_f0 * 0x149b08 + 2000 + in_ECX) = local_dc;
          local_e4 = -0xe0;
          do {
            fscanf(local_ec,"%s",local_d8);
            iVar4 = local_e8;
            iVar5 = 7;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "bound:";
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + 0x7d8 + in_ECX);
              iVar5 = iVar4 + 0x8c0;
              iVar3 = 0x3c;
              do {
                iVar7 = local_f0 * 0x149b08 + iVar5;
                iVar5 = iVar5 + 0xe0;
                iVar3 = iVar3 + -1;
                *(int *)(iVar7 + in_ECX) =
                     *(int *)(iVar4 + local_f0 * 0x149b08 + 0x7d8 + in_ECX) + 0x50;
              } while (iVar3 != 0);
            }
            iVar4 = 4;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "id:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              local_e0 = local_e0 + 0xe0;
              local_e4 = local_e4 + 0xe0;
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8bc + in_ECX);
            }
            iVar4 = 7;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "music:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%s",local_f0 * 0x149b08 + local_e8 + 0x7dc + in_ECX);
            }
            iVar4 = 3;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "x:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e0 + in_ECX);
            }
            iVar4 = 4;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "hp:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8c4 + in_ECX);
            }
            iVar4 = 7;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "times:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8c8 + in_ECX);
            }
            iVar4 = 9;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "reserve:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8cc + in_ECX);
            }
            iVar4 = 7;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "<boss>";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              *(undefined4 *)(local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8e8 + in_ECX) = 2;
            }
            iVar4 = 6;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "join:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8d0 + in_ECX);
            }
            iVar4 = 0xe;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "join_reserve:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8d4 + in_ECX);
            }
            iVar4 = 10;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "<soldier>";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              *(undefined4 *)(local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8e8 + in_ECX) = 1;
              *(undefined4 *)(local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8c8 + in_ECX) = 0x32;
            }
            iVar4 = 0x17;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "when_clear_goto_phase:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + 0x3c90 + in_ECX);
            }
            iVar4 = 7;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "ratio:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%lf",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8e0 + in_ECX);
            }
            iVar4 = 3;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "y:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8dc + in_ECX);
            }
            iVar4 = 5;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "act:";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              fscanf(local_ec,"%d",local_f0 * 0x149b08 + local_e8 + local_e4 + 0x8d8 + in_ECX);
            }
            iVar4 = 0xc;
            bVar9 = true;
            pcVar6 = local_d8;
            pcVar8 = "<phase_end>";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
          } while (!bVar9);
          local_e0 = local_dc;
        }
        iVar4 = 0xc;
        bVar9 = true;
        pcVar6 = local_d8;
        pcVar8 = "<stage_end>";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar9 = *pcVar6 == *pcVar8;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
      } while (!bVar9);
    }
    iVar4 = feof(local_ec);
    pFVar1 = local_ec;
  } while( true );
}

