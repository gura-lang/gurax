//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Value* Frame::LookupValue(const DottedSymbol& dottedSymbol, size_t nTail) const
{
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.size() <= nTail) return nullptr;
	auto ppSymbol = symbolList.begin();
	const Symbol* pSymbol = *ppSymbol++;
	Value* pValue = LookupValue(pSymbol);
	while (pValue && ppSymbol + nTail != symbolList.end()) {
		const Symbol* pSymbol = *ppSymbol++;
		pValue = pValue->DoPropGet(pSymbol, *Attribute::Empty);
	}
	return pValue;
}

bool Frame::AssignValue(const DottedSymbol& dottedSymbol, Value* pValue)
{
	if (dottedSymbol.IsEmpty()) return false;
	if (dottedSymbol.IsDotted()) {
		Value* pValueTarget = LookupValue(dottedSymbol, 1);
		if (!pValueTarget) return false;
		pValueTarget->DoPropSet(dottedSymbol.GetSymbolLast(), pValue, *Attribute::Empty);
	} else {
		AssignValue(dottedSymbol.GetSymbolLast(), pValue);
	}
	return true;
}

bool Frame::AssignModule(Module* pModule)
{
	return AssignValue(pModule->GetDottedSymbol(), new Value_Module(pModule));
}

void Frame::AssignVType(VType& vtype)
{
	vtype.SetFrameParent(this);
	AssignValue(vtype.GetSymbol(), new Value_VType(vtype));
}

void Frame::AssignFunction(Function* pFunction)
{
	pFunction->SetFrameParent(this);
	AssignValue(pFunction->GetSymbol(), new Value_Function(pFunction));
}

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
Frame_ValueMap::Frame_ValueMap() : _pValueMap(new ValueMap())
{
}

Frame_ValueMap::~Frame_ValueMap()
{
	ValueMap::Delete(_pValueMap);
}

void Frame_ValueMap::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

Value* Frame_ValueMap::LookupValue(const Symbol* pSymbol) const
{
	return _pValueMap->Lookup(pSymbol);
}

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
void Frame_Branch::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	if (_pFrameLocal) _pFrameLocal->AssignValue(pSymbol, pValue);
}

Value* Frame_Branch::LookupValue(const Symbol* pSymbol) const
{
	Value* pValue = _pFrameLocal? _pFrameLocal->LookupValue(pSymbol) : nullptr;
	if (pValue) return pValue;
	pValue = _pFrameOuter? _pFrameOuter->LookupValue(pSymbol) : nullptr;
	return pValue;
}

}
