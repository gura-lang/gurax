//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(Value* pValueCar, DeclCaller* pDeclCaller, Attribute* pAttr, Value* pValueThis) :
	_pValueCar(pValueCar), _pDeclCaller(pDeclCaller), _flags(0), _pAttr(pAttr),
	_pArgSlotToFeed(nullptr), _pValueThis(pValueThis)
{
	const DeclArgOwner &declArgOwner = _pDeclCaller->GetDeclArgOwner();
	DeclArgOwner::const_iterator ppDeclArg = declArgOwner.begin();
	if (ppDeclArg != declArgOwner.end()) {
		DeclArg* pDeclArg = *ppDeclArg++;
		_pArgSlotTop.reset(pDeclArg->GetArgSlotFactory().Create(pDeclArg->Reference()));
		ArgSlot* pArgSlotLast = _pArgSlotTop.get();
		while (ppDeclArg != declArgOwner.end()) {
			DeclArg* pDeclArg = *ppDeclArg++;
			ArgSlot* pArgSlot = pDeclArg->GetArgSlotFactory().Create(pDeclArg->Reference());
			pArgSlotLast->SetNext(pArgSlot);
			pArgSlotLast = pArgSlot;
		}			
	}
	_pArgSlotToFeed = _pArgSlotTop.get();
	_flags = GetDeclCaller().GetFlags() | DeclCaller::SymbolsToFlags(GetAttr().GetSymbols());
}

bool Argument::CheckValidity() const
{
	for (const ArgSlot* pArgSlot = GetArgSlotTop(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (!pArgSlot->IsValid()) {
			Error::Issue(ErrorType::ArgumentError, "not enough argument");
			return false;
		}
	}
	return true;
}

String Argument::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetValueCar().ToString(StringStyle(ss).Digest());
	rtn += '(';
	for (const ArgSlot* pArgSlot = GetArgSlotTop(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		if (pArgSlot != GetArgSlotTop()) rtn += ss.GetComma();
		rtn += pArgSlot->ToString(StringStyle(ss).Digest());
	}
	rtn += ')';
	rtn += GetAttr().ToString(ss);
	return rtn;
}

}
