//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Value* Frame::Lookup(const DottedSymbol& dottedSymbol, size_t nTail) const
{
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.size() <= nTail) return nullptr;
	auto ppSymbol = symbolList.begin();
	const Symbol* pSymbol = *ppSymbol++;
	Value* pValue = Lookup(pSymbol);
	while (pValue && ppSymbol + nTail != symbolList.end()) {
		const Symbol* pSymbol = *ppSymbol++;
		pValue = pValue->DoPropGet(pSymbol, *Attribute::Empty);
	}
	return pValue;
}

bool Frame::Assign(const DottedSymbol& dottedSymbol, Value* pValue)
{
	if (dottedSymbol.IsEmpty()) return false;
	if (dottedSymbol.IsDotted()) {
		Value* pValueTarget = Lookup(dottedSymbol, 1);
		if (!pValueTarget) return false;
		pValueTarget->DoPropSet(dottedSymbol.GetSymbolLast(), pValue, *Attribute::Empty);
	} else {
		Assign(dottedSymbol.GetSymbolLast(), pValue);
	}
	return true;
}

bool Frame::Assign(Module* pModule)
{
	return Assign(pModule->GetDottedSymbol(), new Value_Module(pModule));
}

void Frame::Assign(VType& vtype)
{
	vtype.SetFrameParent(*this);
	Assign(vtype.GetSymbol(), new Value_VType(vtype));
}

void Frame::Assign(Function* pFunction)
{
	pFunction->SetFrameParent(*this);
	Assign(pFunction->GetSymbol(), new Value_Function(pFunction));
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

void Frame_ValueMap::Assign(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

void Frame_ValueMap::AssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	_pValueMap->Assign(pSymbol, pValue);
}

Value* Frame_ValueMap::Lookup(const Symbol* pSymbol) const
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
Frame_Root::Frame_Root() : Frame_Branch(new Frame_ValueMap(), nullptr)
{
}

void Frame_Root::Assign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameOuter->Assign(pSymbol, pValue);
}

void Frame_Root::AssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	// nothing to do
}

Value* Frame_Root::Lookup(const Symbol* pSymbol) const
{
	return _pFrameOuter->Lookup(pSymbol);
}

//------------------------------------------------------------------------------
// Frame_VType
//------------------------------------------------------------------------------
Frame_VType::Frame_VType(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, new Frame_ValueMap())
{
}

void Frame_VType::Assign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameLocal->Assign(pSymbol, pValue);
}

void Frame_VType::AssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	// nothing to do
}

Value* Frame_VType::Lookup(const Symbol* pSymbol) const
{
	Value* pValue = _pFrameLocal->Lookup(pSymbol);
	if (pValue) return pValue;
	return _pFrameOuter? _pFrameOuter->Lookup(pSymbol) : nullptr;
}

//------------------------------------------------------------------------------
// Frame_Function
//------------------------------------------------------------------------------
Frame_Function::Frame_Function(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, nullptr)
{
}

void Frame_Function::Assign(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->Assign(pSymbol, pValue);
}

void Frame_Function::AssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	if (!_pFrameLocal) _pFrameLocal.reset(new Frame_ValueMap());
	_pFrameLocal->Assign(pSymbol, pValue);
}

Value* Frame_Function::Lookup(const Symbol* pSymbol) const
{
	if (_pFrameLocal) {
		Value* pValue = _pFrameLocal->Lookup(pSymbol);
		if (pValue) return pValue;
	}
	return _pFrameOuter? _pFrameOuter->Lookup(pSymbol) : nullptr;
}

//------------------------------------------------------------------------------
// Frame_Block
//------------------------------------------------------------------------------
Frame_Block::Frame_Block(Frame* pFrameOuter) : Frame_Branch(pFrameOuter, new Frame_ValueMap())
{
}

void Frame_Block::Assign(const Symbol* pSymbol, Value* pValue)
{
	_pFrameOuter->Assign(pSymbol, pValue);
}

void Frame_Block::AssignFromArgument(const Symbol* pSymbol, Value* pValue)
{
	_pFrameLocal->Assign(pSymbol, pValue);
}

Value* Frame_Block::Lookup(const Symbol* pSymbol) const
{
	Value* pValue = _pFrameLocal->Lookup(pSymbol);
	if (pValue) return pValue;
	return _pFrameOuter? _pFrameOuter->Lookup(pSymbol) : nullptr;
}

}
