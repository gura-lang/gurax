//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(DeclCaller* pDeclCaller, Attribute* pAttr) :
	_pDeclCaller(pDeclCaller), _flags(0), _pAttr(pAttr)
{
	ArgSlot* pArgSlotLast = nullptr;
	const DeclArgOwner &declArgOwner = _pDeclCaller->GetDeclArgOwner();
	for (const DeclArg* pDeclArg : declArgOwner) {
		ArgSlot* pArgSlot = nullptr;
		if (pDeclArg->IsOccurZeroOrMore() || pDeclArg->IsOccurOnceOrMore()) {
			pArgSlot = new ArgSlot_List(pDeclArg->Reference());
		} else {
			pArgSlot = new ArgSlot_Value(pDeclArg->Reference());
		}
		if (pArgSlotLast) {
			pArgSlotLast->SetNext(pArgSlot);
		} else {
			_pArgSlotTop.reset(pArgSlot);
		}
		pArgSlotLast = pArgSlot;
	}
	_flags = GetDeclCaller().GetFlags() | DeclCaller::SymbolsToFlags(GetAttr().GetSymbols());
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	//const ArgSlot* pArgSlot = GetArgSlotTop();
	return rtn;
}

}
