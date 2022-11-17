//==============================================================================
// CP932.h
//==============================================================================
#ifndef GURAX_MODULE_XML_CP932_H
#define GURAX_MODULE_XML_CP932_H
#include <gurax.h>

Gurax_BeginModuleScope(xml)

UInt16 CP932ToUTF16(UInt16 codeCP932);
UInt16 UTF16ToCP932(UInt16 codeUTF16);
UInt16 CP932ToJIS(UInt16 codeCP932);
UInt16 JISToCP932(UInt16 codeJIS);
UInt16 CP932ToEUCJP(UInt16 codeCP932);
UInt16 EUCJPToCP932(UInt16 codeEUCJP);

Gurax_EndModuleScope(xml)

#endif
