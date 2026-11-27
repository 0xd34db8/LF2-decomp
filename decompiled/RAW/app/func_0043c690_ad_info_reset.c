/* Function: FUN_0043c690 */
/* Address: 0x0043c690 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043c690(void)

{
  FILE *_File;
  
  _File = fopen("data\\adinfo.txt","w");
  if (_File != (FILE *)0x0) {
    fprintf(_File,"now 0 4 <end>\n");
    fclose(_File);
  }
  _DAT_004527b0 = 0x776f6e;
  DAT_0044d784 = 0;
  DAT_0044d788 = 4;
  sprintf(&DAT_00453c68,"data\\ad%d.txt",0);
  sprintf(&DAT_00453d40,"sprite\\sys\\ad%d.bmp",DAT_0044d784);
  return;
}

