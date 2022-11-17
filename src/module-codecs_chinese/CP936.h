//==============================================================================
// CP936.h
//==============================================================================
#ifndef GURAX_MODULE_CODECS_JAPANESE_CP936_H
#define GURAX_MODULE_CODECS_JAPANESE_CP936_H
#include <gurax.h>

Gurax_BeginModuleScope(codecs_chinese)

UInt16 CP936ToUTF16(UInt16 codeCP936);
UInt16 UTF16ToCP936(UInt16 codeUTF16);

Gurax_EndModuleScope(codecs_chinese)

#endif
