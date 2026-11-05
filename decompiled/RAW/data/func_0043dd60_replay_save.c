/*

 * Procedure: FUN_0043dd60
 * Address: 0x0043dd60 - 0x0043def8 (Length: 405 bytes)
 * Purpose: Replay File Compressor and Obfuscation Cipher (Saves recording to recording\%s.lfr)

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FUN_0043dd60(void)
{
  char cVar1;
  void *pvVar2;
  char *pcVar3;
  char *_Memory;
  char *pcVar4;
  char *pcVar5;
  int unaff_EBX;
  char *pcVar6;
  undefined4 local_294;
  int local_290;
  basic_ofstream<char, std::char_traits<char> _> local_28c[136];
  char local_204[496];
  uint local_14;
  void *local_10;
  void *local_c;
  undefined1 *local_8;
  undefined4 uStack_4;

  uStack_4 = 0xffffffff;
  local_8 = &LAB_0044620c;
  local_c = ExceptionList;
  local_10 = (void *)(DAT_0044eea4 ^ (uint)&local_294);
  ExceptionList = &local_c;
  sprintf(local_204, "recording\\%s", &DAT_0044fd98, DAT_0044eea4 ^ (uint)(local_28c + -0x18));
  pvVar2 = DAT_004588a8;
  local_294 = &Rsrc_Bitmap_MENU_CLIP3_404.field_0xea40;
  _Memory = calloc(1, 0x631200);
  FUN_0043f4b0(_Memory, &local_294, pvVar2, 0x630e18);
  pcVar4 = &DAT_0044d7a0;
  pcVar6 = (char *)0x0;
  do
  {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (pcVar4 != &DAT_0044d7a1)
  {
    local_290 = (int)&DAT_0044d7a0 - (int)_Memory;
    pcVar4 = _Memory;
    do
    {
      if (local_294 <= pcVar6)
        break;
      *pcVar4 = pcVar4[local_290] + *pcVar4 + -0x30;
      pcVar6 = pcVar6 + 1;
      pcVar4 = pcVar4 + 1;
      pcVar3 = &DAT_0044d7a0;
      do
      {
        pcVar5 = pcVar3;
        pcVar3 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
    } while (pcVar6 < pcVar5 + -0x44d7a0);
  }
  std::basic_ofstream<char, std::char_traits<char> _>::basic_ofstream<char, std::char_traits<char> _>(local_28c, local_204, 0x20, 0x40);
  local_8 = (undefined1 *)0x0;
  std::basic_ostream<char, std::char_traits<char> _>::write((basic_ostream<char, std::char_traits<char> _> *)&local_290, (char *)(local_28c + -0xc), 4);
  std::basic_ostream<char, std::char_traits<char> _>::write((basic_ostream<char, std::char_traits<char> _> *)&local_290, _Memory, unaff_EBX);
  std::basic_ofstream<char, std::char_traits<char> _>::close((basic_ofstream<char, std::char_traits<char> _> *)&local_290);
  free(_Memory);
  free(DAT_004588a8);
  DAT_004588a8 = (void *)0x0;
  local_8 = (undefined1 *)0xffffffff;
  std::basic_ofstream<char, std::char_traits<char> _>::_vbase_destructor_((basic_ofstream<char, std::char_traits<char> _> *)&local_290);
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)(local_28c + -0xc));
  return;
}
