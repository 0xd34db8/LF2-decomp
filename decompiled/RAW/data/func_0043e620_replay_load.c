/*

 * Procedure: FUN_0043e620
 * Address: 0x0043e620 - 0x0043e851 (Length: 558 bytes)
 * Purpose: Replay File Loader, De-obfuscation Cipher, and Zlib Decompressor

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

undefined4 FUN_0043e620(char *param_1)
{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  void *_Memory;
  undefined4 uVar5;
  int *piVar6;
  char *_Memory_00;
  char *pcVar7;
  char *pcVar8;
  char *unaff_EBP;
  char *pcVar9;
  char acStack_be[2];
  void *local_bc;
  basic_istream<char, std::char_traits<char> _> local_b8[4];
  void *local_b4;
  basic_ifstream<char, std::char_traits<char> _> local_b0[80];
  int local_60;
  void *pvStack_14;
  void *local_c;
  undefined1 *local_8;
  undefined4 uStack_4;

  uStack_4 = 0xffffffff;
  local_8 = &LAB_0044624c;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  DAT_0044d030 = 1;
  DAT_00450b74 = 0;
  _Memory = calloc(1, 0x630e18);
  local_b4 = _Memory;
  std::basic_ifstream<char, std::char_traits<char> _>::basic_ifstream<char, std::char_traits<char> _>(local_b0, param_1, 0x20, 0x40);
  local_8 = (undefined1 *)0x0;
  if (local_60 == 0)
  {
    std::basic_ifstream<char, std::char_traits<char> _>::close((basic_ifstream<char, std::char_traits<char> _> *)&local_b4);
    free(_Memory);
    local_8 = (undefined1 *)0xffffffff;
    std::basic_ifstream<char, std::char_traits<char> _>::_vbase_destructor_((basic_ifstream<char, std::char_traits<char> _> *)&local_b4);
    uVar5 = 0xffffffff;
  }
  else
  {
    std::basic_istream<char, std::char_traits<char> _>::seekg((basic_istream<char, std::char_traits<char> _> *)&local_b4, 0, 2);
    piVar6 = (int *)std::basic_istream<char, std::char_traits<char> _>::tellg((basic_istream<char, std::char_traits<char> _> *)&local_b4);
    iVar2 = piVar6[2];
    iVar3 = *piVar6;
    std::basic_istream<char, std::char_traits<char> _>::seekg(local_b8, 0, 0);
    if (iVar2 + iVar3 < 1000)
    {
      std::basic_ifstream<char, std::char_traits<char> _>::close((basic_ifstream<char, std::char_traits<char> _> *)local_b8);
      free(_Memory);
    }
    else
    {
      std::basic_istream<char, std::char_traits<char> _>::read(local_b8, acStack_be + -10, 4);
      _Memory_00 = calloc(1, (size_t)unaff_EBP);
      std::basic_istream<char, std::char_traits<char> _>::read(local_b8, _Memory_00, (int)unaff_EBP);
      std::basic_ifstream<char, std::char_traits<char> _>::close((basic_ifstream<char, std::char_traits<char> _> *)local_b8);
      pcVar7 = &DAT_0044d7a0;
      pcVar9 = (char *)0x0;
      do
      {
        cVar1 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      if (pcVar7 != &DAT_0044d7a1)
      {
        pcVar7 = _Memory_00;
        do
        {
          if (unaff_EBP <= pcVar9)
            break;
          *pcVar7 = (*pcVar7 - pcVar7[(int)&DAT_0044d7a0 - (int)_Memory_00]) + '0';
          pcVar9 = pcVar9 + 1;
          pcVar7 = pcVar7 + 1;
          pcVar4 = &DAT_0044d7a0;
          do
          {
            pcVar8 = pcVar4;
            pcVar4 = pcVar8 + 1;
          } while (*pcVar8 != '\0');
          _Memory = local_bc;
        } while (pcVar9 < pcVar8 + -0x44d7a0);
      }
      FUN_0043f4d0(_Memory, acStack_be + -6, _Memory_00, unaff_EBP);
      free(_Memory);
      free(_Memory_00);
    }
    local_c = (void *)0xffffffff;
    std::basic_ifstream<char, std::char_traits<char> _>::_vbase_destructor_((basic_ifstream<char, std::char_traits<char> _> *)local_b8);
    uVar5 = 0;
  }
  ExceptionList = pvStack_14;
  return uVar5;
}
