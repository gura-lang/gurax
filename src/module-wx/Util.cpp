//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// EntityCore
//------------------------------------------------------------------------------
bool EntityCore::PrepareMethod(const Symbol* pSymbolFunc, Function** ppFunc, RefPtr<Argument>& pArgument) const
{
	RefPtr<Value> pValueThis(LockValue());
	if (!pValueThis) return false;
	*ppFunc = &pValueThis->LookupMethod(pSymbolFunc);
	if ((*ppFunc)->IsEmpty()) return false;
	pArgument.reset(new Argument(**ppFunc));
	pArgument->SetValueThis(pValueThis.release());
	return true;
}

Gurax_EndModuleScope(wx)
