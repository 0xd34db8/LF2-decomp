/* Function: FUN_0043c710 */
/* Address: 0x0043c710 */

void FUN_0043c710(void)

{
  FILE *_File;
  
  sprintf(&DAT_00453c68,"data\\ad%d.txt",DAT_0044d784);
  sprintf(&DAT_00453d40,"sprite\\sys\\ad%d.bmp",DAT_0044d784);
  _File = fopen("data\\adinfo.txt","w");
  if (_File != (FILE *)0x0) {
    fprintf(_File,"%s %d %d <end>\n",&DAT_004527b0,DAT_0044d784,DAT_0044d788);
    fclose(_File);
  }
  return;
}

