//==============================================================================
// CP950.h
//==============================================================================
#ifndef GURAX_MODULE_CODECS_JAPANESE_CP950_H
#define GURAX_MODULE_CODECS_JAPANESE_CP950_H
#include <gurax.h>

Gurax_BeginModuleScope(codecs_chinese)

UInt16 CP950ToUTF16(UInt16 codeCP950);
UInt16 UTF16ToCP950(UInt16 codeUTF16);

Gurax_EndModuleScope(codecs_chinese)

#endif
