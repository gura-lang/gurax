//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_SYMBOL_H
#define GURAX_MODULE_MTP_SYMBOL_H
#include <gurax.h>

Gurax_BeginModuleScope(mtp)

Gurax_DeclareSymbol(Undefined);
Gurax_DeclareSymbol(FixedROM);
Gurax_DeclareSymbol(RemovableROM);
Gurax_DeclareSymbol(FixedRAM);
Gurax_DeclareSymbol(RemovableRAM);
Gurax_DeclareSymbol(GenericFlat);
Gurax_DeclareSymbol(GenericHierarchical);
Gurax_DeclareSymbol(DCF);
Gurax_DeclareSymbol(ReadWrite);
Gurax_DeclareSymbol(ReadOnly);
Gurax_DeclareSymbol(ReadOnlyWithObjectDeletion);

Gurax_EndModuleScope(mtp)

#endif
