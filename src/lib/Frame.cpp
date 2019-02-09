//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame_Source
//------------------------------------------------------------------------------
class Frame_Source : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Source);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Source");
protected:
	RefPtr<ValueMap> _pValueMap;
public:
	// Constructor
	Frame_Source() : Frame(Type::Source), _pValueMap(new ValueMap()) {}
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
Frame* Frame::CreateSource()
{
	return new Frame_Source();
}

Frame_Branch* Frame::CreateBranch(Frame* pFrameLeft, Frame* pFrameRight)
{
	return new Frame_Branch(pFrameLeft, pFrameRight);
}

Frame* Frame::Expand() const
{
	return new Frame_Branch(Reference(), new Frame_Source());
}

Frame* Frame::Shrink(Frame* pFrame)
{
	if (!pFrame->IsBranch()) return pFrame;
	Frame* pFrameRtn = dynamic_cast<Frame_Branch*>(pFrame)->GetLeft()->Reference();
	Frame::Delete(pFrame);
	return pFrameRtn;
}

Frame* Frame::SeekTarget(const DottedSymbol& dottedSymbol, size_t nTail)
{
	Frame* pFrame = this;
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.size() <= nTail) return pFrame;
	for (auto ppSymbol = symbolList.begin(); ; ) {
		const Symbol* pSymbol = *ppSymbol++;
		if (ppSymbol + nTail == symbolList.end()) break;
		Value* pValue = pFrame->LookupValue(pSymbol);
		if (!pValue) return nullptr;
		pFrame = pValue->ProvideFrame();
		if (!pFrame) return nullptr;
	}
	return pFrame;
}

bool Frame::AssignValue(const DottedSymbol& dottedSymbol, Value* pValue)
{
	Frame* pFrame = SeekTarget(dottedSymbol);
	if (!pFrame) return false;
	pFrame->AssignValue(dottedSymbol.GetSymbolLast(), pValue);
	return true;
}

Value* Frame::LookupValue(const DottedSymbol& dottedSymbol) const
{
	const Frame* pFrame = const_cast<Frame*>(this)->SeekTarget(dottedSymbol);
	if (!pFrame) return nullptr;
	return pFrame->LookupValue(dottedSymbol.GetSymbolLast());
}

bool Frame::AssignModule(Module* pModule)
{
	const DottedSymbol& dottedSymbol = pModule->GetDottedSymbol();
	Frame* pFrame = SeekTarget(dottedSymbol, 1);
	if (pFrame == nullptr) return false;
	pFrame->AssignValue(dottedSymbol.GetSymbolLast(), new Value_Module(pModule));
	return true;
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
