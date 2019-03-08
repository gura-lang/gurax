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
// FrameList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FrameOwner
//------------------------------------------------------------------------------
void FrameOwner::Clear()
{
	for (Frame* pFrame : *this) Frame::Delete(pFrame);
	clear();
}

//------------------------------------------------------------------------------
// FrameStack
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
Frame_ValueMap::Frame_ValueMap() : Frame(nullptr), _pValueMap(new ValueMap())
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

//------------------------------------------------------------------------------
// Frame_Root
// _pFrameLocal is always nullptr.
//------------------------------------------------------------------------------
void Frame_Root::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	_pFrameOuter->AssignValue(pSymbol, pValue);
}

Value* Frame_Root::LookupValue(const Symbol* pSymbol) const
{
	return _pFrameOuter->LookupValue(pSymbol);
}

//------------------------------------------------------------------------------
// Frame_Environment
//------------------------------------------------------------------------------
void Frame_Environment::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	_pFrameLocal->AssignValue(pSymbol, pValue);
}

Value* Frame_Environment::LookupValue(const Symbol* pSymbol) const
{
	Value* pValue = _pFrameLocal->LookupValue(pSymbol);
	if (pValue) return pValue;
	return _pFrameOuter? _pFrameOuter->LookupValue(pSymbol) : nullptr;
}

//------------------------------------------------------------------------------
// Frame_Function
//------------------------------------------------------------------------------
void Frame_Function::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->AssignValue(pSymbol, pValue);
}

Value* Frame_Function::LookupValue(const Symbol* pSymbol) const
{
	if (_pFrameLocal) {
		Value* pValue = _pFrameLocal->LookupValue(pSymbol);
		if (pValue) return pValue;
	}
	return _pFrameOuter? _pFrameOuter->LookupValue(pSymbol) : nullptr;
}

}
