/*
 * Function: Save Player Controls & Settings (data\control.txt)
 * Virtual Address: 0x00423230
 * Calling Convention: __cdecl
 *
 * Description:
 *   Serializes player key configurations (4 players x 11 keys),
 *   player profile names (substituting spaces with grave accents '`'),
 *   system profile strings (<No name>, <No info>, <No email>),
 *   and demo/replay flags to "data\control.txt".
 */

#include <stdio.h>
#include <string.h>

extern int DAT_0044fb70[80];       // 4 players x 20 ints (11 keys used)
extern char DAT_0044fcc0[44];      // 4 players x 11 chars
extern char DAT_0044fd18[100];     // Profile name
extern char DAT_0044f890[100];     // Profile email
extern char DAT_0044f900[100];     // Profile info
extern int DAT_00450be8;          // Demo mode flag
extern int DAT_00450be4;          // Replay mode flag

void FUN_00423230(void)
{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  unsigned int uVar3;
  int *puVar4;
  int *puVar5;
  char *pcVar6;
  int iVar7;

  _File = fopen("data\\control.txt", "w");
  if (!_File) return;

  puVar4 = DAT_0044fb70;
  do {
    iVar7 = 11;
    puVar5 = puVar4;
    do {
      fprintf(_File, "%d ", *puVar5);
      puVar5 = puVar5 + 1;
      iVar7 = iVar7 - 1;
    } while (iVar7 != 0);
    fprintf(_File, "\n");
    puVar4 = puVar4 + 20; // 0x14 dwords = 80 bytes stride
  } while ((char*)puVar4 < (char*)DAT_0044fb70 + 320);

  pcVar6 = DAT_0044fcc0;
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
      } while (uVar3 < (unsigned int)((int)pcVar2 - (int)(pcVar6 + 1)));
    }
    pcVar6 = pcVar6 + 11;
  } while (pcVar6 < DAT_0044fcc0 + 44);

  if (DAT_0044fcc0[0] == '\0') strcpy(DAT_0044fcc0, "1");
  if (DAT_0044fcc0[11] == '\0') strcpy(DAT_0044fcc0 + 11, "2");
  if (DAT_0044fcc0[22] == '\0') strcpy(DAT_0044fcc0 + 22, "3");
  if (DAT_0044fcc0[33] == '\0') strcpy(DAT_0044fcc0 + 33, "4");

  fprintf(_File, "%s %s %s %s\n",
          &DAT_0044fcc0[0], &DAT_0044fcc0[11],
          &DAT_0044fcc0[22], &DAT_0044fcc0[33]);

  if (DAT_0044fd18[0] == '\0') strcpy(DAT_0044fd18, "<No name>");
  if (DAT_0044f900[0] == '\0') strcpy(DAT_0044f900, "<No info>");
  if (DAT_0044f890[0] == '\0') strcpy(DAT_0044f890, "<No email>");

  fprintf(_File, "%d\n", DAT_00450be8);
  fprintf(_File, "%d\n", DAT_00450be4);
  fprintf(_File, "%s\n", DAT_0044fd18);
  fprintf(_File, "%s\n", DAT_0044f890);
  fprintf(_File, "%s", DAT_0044f900);
  fclose(_File);

  // Restore spaces in player names in memory
  pcVar6 = DAT_0044fcc0;
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
      } while (uVar3 < (unsigned int)((int)pcVar2 - (int)(pcVar6 + 1)));
    }
    pcVar6 = pcVar6 + 11;
  } while (pcVar6 < DAT_0044fcc0 + 44);
}

