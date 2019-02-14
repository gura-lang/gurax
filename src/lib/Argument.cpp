//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(DeclCaller* pDeclCaller, Attribute* pAttr) :
	_pDeclCaller(pDeclCaller), _flags(0), _pAttr(pAttr), _pArgSlotToFeed(nullptr)
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
	_pArgSlotToFeed = _pArgSlotTop.get();
	_flags = GetDeclCaller().GetFlags() | DeclCaller::SymbolsToFlags(GetAttr().GetSymbols());
}

bool Argument::CheckValidity() const
{
	return true;
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += '(';
	for (const ArgSlot* pArgSlot = GetArgSlotTop(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot != GetArgSlotTop()) rtn += ss.GetComma();
		rtn += pArgSlot->ToString(StringStyle().Digest());
	}
	rtn += ')';
	rtn += GetAttr().ToString(ss);
	return rtn;
}

}
