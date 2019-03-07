//==============================================================================
// Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
Argument::Argument(Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr, Value* pValueThis) :
	_pValueCar(pValueCar), _pDeclCallable(pDeclCallable), _pAttr(pAttr), _pValueThis(pValueThis),
	_flags(0), _pArgSlotToFeed(nullptr), _pPUnitNext(nullptr)
{
	const DeclArgOwner &declArgOwner = _pDeclCallable->GetDeclArgOwner();
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
	if (!_pDeclCallable->GetSymbolOfDict()->IsEmpty()) {
		_pValueOfDict.reset(new Value_Dict());
	}
	_flags = GetDeclCallable().GetFlags() | DeclCallable::SymbolsToFlags(GetAttr().GetSymbols());
	_pArgSlotToFeed = _pArgSlotTop.get();
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

void Argument::AssignToFrame(Frame& frame) const
{
	for (const ArgSlot* pArgSlot = GetArgSlotTop(); pArgSlot; pArgSlot = pArgSlot->GetNext()) {
		pArgSlot->AssignToFrame(frame);
	}
	do {
		// assign to symbol declared as dict%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfDict();
		if (!pSymbol->IsEmpty()) frame.AssignValue(pSymbol, _pValueOfDict->Reference());
	} while (0);
	do {
		// assign to symbol declared as arg%%
		const Symbol* pSymbol = GetDeclCallable().GetSymbolOfAccessor();
		if (!pSymbol->IsEmpty()) frame.AssignValue(pSymbol, new Value_Argument(Reference()));
	} while (0);
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
	if (GetValueOfDict()) {
		if (GetArgSlotTop()) rtn += ss.GetComma();
		rtn += "(";
		rtn += GetValueOfDict()->ToString(StringStyle(ss).Digest());
		rtn += ")%";
	}
	rtn += ')';
	rtn += GetAttr().ToString(ss);
	return rtn;
}

}
