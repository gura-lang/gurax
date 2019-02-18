//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame_ValueMap
//------------------------------------------------------------------------------
class Frame_ValueMap : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_ValueMap);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_ValueMap");
protected:
	RefPtr<ValueMap> _pValueMap;
public:
	// Constructor
	Frame_ValueMap() : Frame(Type::ValueMap), _pValueMap(new ValueMap()) {}
public:
	// Virtual functions of Frame
	virtual void AssignValue(const Symbol* pSymbol, Value* pValue) override {
		_pValueMap->Assign(pSymbol, pValue);
	}
	virtual Value* LookupValue(const Symbol* pSymbol) const override {
		return _pValueMap->Lookup(pSymbol);
	}
};

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Frame_Branch* Frame::CreateOfBranch(Frame* pFrameLeft, Frame* pFrameRight)
{
	return new Frame_Branch(pFrameLeft, pFrameRight);
}

Frame* Frame::CreateOfValueMap()
{
	return new Frame_ValueMap();
}

Frame* Frame::Expand() const
{
	return new Frame_Branch(Reference(), new Frame_ValueMap());
}

Frame* Frame::Shrink(Frame* pFrame)
{
	if (!pFrame->IsBranch()) return pFrame;
	Frame* pFrameRtn = dynamic_cast<Frame_Branch*>(pFrame)->GetLeft()->Reference();
	Frame::Delete(pFrame);
	return pFrameRtn;
}

Value* Frame::LookupValue(const DottedSymbol& dottedSymbol, size_t nTail) const
{
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.size() <= nTail) return nullptr;
	auto ppSymbol = symbolList.begin();
	const Symbol* pSymbol = *ppSymbol++;
	Value* pValue = LookupValue(pSymbol);
	while (pValue && ppSymbol + nTail != symbolList.end()) {
		const Symbol* pSymbol = *ppSymbol++;
		pValue = pValue->LookupPropValue(pSymbol, *Attribute::Empty);
	}
	return pValue;
}

bool Frame::AssignValue(const DottedSymbol& dottedSymbol, Value* pValue)
{
	if (dottedSymbol.IsEmpty()) return false;
	if (dottedSymbol.IsDotted()) {
		Value* pValueTarget = LookupValue(dottedSymbol, 1);
		if (!pValueTarget) return false;
		pValueTarget->AssignPropValue(dottedSymbol.GetSymbolLast(), pValue, *Attribute::Empty);
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
// Frame_Branch
//------------------------------------------------------------------------------
void Frame_Branch::AssignValue(const Symbol* pSymbol, Value* pValue)
{
	if (_pFrameRight) _pFrameRight->AssignValue(pSymbol, pValue);
}

Value* Frame_Branch::LookupValue(const Symbol* pSymbol) const
{
	Value* pValue = _pFrameRight? _pFrameRight->LookupValue(pSymbol) : nullptr;
	if (pValue) return pValue;
	pValue = _pFrameLeft? _pFrameLeft->LookupValue(pSymbol) : nullptr;
	return pValue;
}

}
