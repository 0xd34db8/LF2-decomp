/* Function: FUN_00423480 */
/* Address: 0x00423480 */

void FUN_00423480(void)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  FILE *pFVar6;
  undefined4 *puVar7;
  char *pcVar8;
  code *pcVar9;
  int iVar10;
  FILE *local_200 [2];
  char local_1f8 [500];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)local_200;
  local_200[0] = fopen("data\\control.txt","r");
  puVar5 = &DAT_0044fb70;
  do {
    iVar10 = 0xb;
    puVar7 = puVar5;
    do {
      fscanf(local_200[0],"%d",puVar7);
      pFVar6 = local_200[0];
      puVar7 = puVar7 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    puVar5 = puVar5 + 0x14;
  } while ((int)puVar5 < 0x44fcb0);
  fscanf(local_200[0],"%s %s %s %s\n",&DAT_0044fcc0,&DAT_0044fccb,&DAT_0044fcd6,&DAT_0044fce1);
  pcVar8 = &DAT_0044fcc0;
  do {
    uVar3 = 0;
    pcVar2 = pcVar8;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (pcVar2 != pcVar8 + 1) {
      do {
        if (pcVar8[uVar3] == '`') {
          pcVar8[uVar3] = ' ';
        }
        uVar3 = uVar3 + 1;
        pcVar2 = pcVar8;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
      } while (uVar3 < (uint)((int)pcVar2 - (int)(pcVar8 + 1)));
    }
    pcVar8 = pcVar8 + 0xb;
  } while ((int)pcVar8 < 0x44fcec);
  fscanf(pFVar6,"%d\n",&DAT_00450be8);
  fscanf(pFVar6,"%d\n",&DAT_00450be4);
  pcVar9 = fgets_exref;
  fgets(&DAT_0044fd18,100,pFVar6);
  fgets(&DAT_0044f890,100,pFVar6);
  pcVar8 = &DAT_0044fd18;
  do {
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  if (pcVar8 != &DAT_0044fd19) {
    pcVar8 = &DAT_0044fd18;
    do {
      pcVar2 = pcVar8;
      pcVar8 = pcVar2 + 1;
    } while (*pcVar2 != '\0');
    for (pcVar2 = pcVar2 + -0x44fd19;
        (-1 < (int)pcVar2 &&
        (((cVar1 = pcVar2[0x44fd18], cVar1 == ' ' || (cVar1 == '\r')) || (cVar1 == '\n'))));
        pcVar2 = pcVar2 + -1) {
      pcVar2[0x44fd18] = '\0';
    }
  }
  pcVar8 = &DAT_0044f890;
  do {
    cVar1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar1 != '\0');
  if (pcVar8 != &DAT_0044f891) {
    pcVar8 = &DAT_0044f890;
    do {
      pcVar2 = pcVar8;
      pcVar8 = pcVar2 + 1;
    } while (*pcVar2 != '\0');
    for (pcVar2 = pcVar2 + -0x44f891;
        (-1 < (int)pcVar2 &&
        (((cVar1 = pcVar2[0x44f890], cVar1 == ' ' || (cVar1 == '\r')) || (cVar1 == '\n'))));
        pcVar2 = pcVar2 + -1) {
      pcVar2[0x44f890] = '\0';
    }
  }
  DAT_0044f900 = 0;
  iVar10 = feof(pFVar6);
  if (iVar10 == 0) {
    while( true ) {
      pFVar6 = local_200[0];
      (*pcVar9)(local_1f8,100,local_200[0]);
      pcVar8 = local_1f8;
      do {
        cVar1 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      uVar3 = (int)pcVar8 - (int)local_1f8;
      pcVar8 = (char *)((int)&DAT_0044f8fc + 3);
      do {
        pcVar2 = pcVar8 + 1;
        pcVar8 = pcVar8 + 1;
      } while (*pcVar2 != '\0');
      pcVar2 = local_1f8;
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar8 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar8 = pcVar8 + 1;
      }
      iVar10 = feof(pFVar6);
      if (iVar10 != 0) break;
      pcVar9 = fgets_exref;
    }
  }
  else {
    pFVar6 = local_200[0];
  }
  fclose(pFVar6);
  __security_check_cookie(local_4 ^ (uint)local_200);
  return;
}
