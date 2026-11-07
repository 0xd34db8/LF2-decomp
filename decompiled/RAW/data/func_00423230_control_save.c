/* Function: FUN_00423230 */
/* Address: 0x00423230 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00423230(void)

{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  char *pcVar6;
  int iVar7;
  
  _File = fopen("data\\control.txt","w");
  puVar4 = &DAT_0044fb70;
  do {
    iVar7 = 0xb;
    puVar5 = puVar4;
    do {
      fprintf(_File,"%d ",*puVar5);
      puVar5 = puVar5 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    fprintf(_File,"\n");
    puVar4 = puVar4 + 0x14;
  } while ((int)puVar4 < 0x44fcb0);
  pcVar6 = &DAT_0044fcc0;
  do {
    uVar3 = 0;
    pcVar2 = pcVar6;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (pcVar2 != pcVar6 + 1) {
      do {
        if (pcVar6[uVar3] == '`') {
          pcVar6[uVar3] = '\'';
        }
        else if (pcVar6[uVar3] == ' ') {
          pcVar6[uVar3] = '`';
        }
        uVar3 = uVar3 + 1;
        pcVar2 = pcVar6;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
      } while (uVar3 < (uint)((int)pcVar2 - (int)(pcVar6 + 1)));
    }
    pcVar6 = pcVar6 + 0xb;
  } while ((int)pcVar6 < 0x44fcec);
  if (DAT_0044fcc0 == '\0') {
    _DAT_0044fcc0 = 0x31;
  }
  if (DAT_0044fccb == '\0') {
    _DAT_0044fccb = 0x32;
  }
  if (DAT_0044fcd6 == '\0') {
    _DAT_0044fcd6 = 0x33;
  }
  if (DAT_0044fce1 == '\0') {
    _DAT_0044fce1 = 0x34;
  }
  fprintf(_File,"%s %s %s %s\n",&DAT_0044fcc0,&DAT_0044fccb,&DAT_0044fcd6,&DAT_0044fce1);
  if (DAT_0044fd18 == '\0') {
    DAT_0044fd18 = '<';
    DAT_0044fd19 = 'N';
    DAT_0044fd18_1._1_1_ = 'o';
    DAT_0044fd18_1._2_1_ = ' ';
    DAT_0044fd1c = 'n';
    DAT_0044fd1c_1._0_1_ = 'a';
    DAT_0044fd1c_1._1_1_ = 'm';
    DAT_0044fd1c_1._2_1_ = 'e';
    _DAT_0044fd20 = 0x3e;
  }
  if (DAT_0044f900 == '\0') {
    DAT_0044f900 = '<';
    DAT_0044f901 = 'N';
    DAT_0044f900_1._1_1_ = 'o';
    DAT_0044f900_1._2_1_ = ' ';
    DAT_0044f904 = 'i';
    DAT_0044f905 = 'n';
    DAT_0044f904_1._1_1_ = 'f';
    DAT_0044f904_1._2_1_ = 'o';
    _DAT_0044f908 = 0x3e;
  }
  if (DAT_0044f890 == '\0') {
    DAT_0044f890 = '<';
    DAT_0044f891 = 'N';
    DAT_0044f890_1._1_1_ = 'o';
    DAT_0044f890_1._2_1_ = ' ';
    DAT_0044f894 = 'e';
    DAT_0044f894_1._0_1_ = 'm';
    DAT_0044f894_1._1_1_ = 'a';
    DAT_0044f894_1._2_1_ = 'i';
    _DAT_0044f898 = 0x3e6c;
    DAT_0044f89a = 0;
  }
  fprintf(_File,"%d\n",DAT_00450be8);
  fprintf(_File,"%d\n",DAT_00450be4);
  fprintf(_File,"%s\n",&DAT_0044fd18);
  fprintf(_File,"%s\n",&DAT_0044f890);
  fprintf(_File,"%s",&DAT_0044f900);
  fclose(_File);
  pcVar6 = &DAT_0044fcc0;
  do {
    uVar3 = 0;
    pcVar2 = pcVar6;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    if (pcVar2 != pcVar6 + 1) {
      do {
        if (pcVar6[uVar3] == '`') {
          pcVar6[uVar3] = ' ';
        }
        uVar3 = uVar3 + 1;
        pcVar2 = pcVar6;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
      } while (uVar3 < (uint)((int)pcVar2 - (int)(pcVar6 + 1)));
    }
    pcVar6 = pcVar6 + 0xb;
  } while ((int)pcVar6 < 0x44fcec);
  return;
}
