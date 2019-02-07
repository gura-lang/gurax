//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame_Node
//------------------------------------------------------------------------------
class Frame_Node : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Node);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Node");
protected:
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Frame_Node() : Frame(Type::Node), _pObjectMap(new ObjectMap()) {}
public:
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pObjectMap->Assign(pSymbol, pObject);
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		return _pObjectMap->Lookup(pSymbol);
	}
};

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Frame* Frame::CreateNode()
{
	return new Frame_Node();
}

Frame* Frame::Expand() const
{
	return new Frame_Branch(Reference(), new Frame_Node());
}

Frame* Frame::Shrink(Frame* pFrame)
{
	if (!pFrame->IsBranch()) return pFrame;
	Frame* pFrameRtn = dynamic_cast<Frame_Branch*>(pFrame)->GetLeft()->Reference();
	Frame::Delete(pFrame);
	return pFrameRtn;
}

Frame* Frame::SeekTarget(const DottedSymbol& dottedSymbol)
{
	Frame* pFrame = this;
	const SymbolList& symbolList = dottedSymbol.GetSymbolList();
	if (symbolList.empty()) return nullptr;
	const Symbol* pSymbol = nullptr;
	for (auto ppSymbol = symbolList.begin(); ; ppSymbol++) {
		pSymbol = *ppSymbol;
		if (ppSymbol + 1 == symbolList.end()) break;
		Object* pObject = pFrame->LookupObject(pSymbol);
		if (!pObject) return nullptr;
		//pFrame = pObject->ProvideFrame();
		if (!pFrame) return nullptr;
	}
	return pFrame;
}

bool Frame::AssignObject(const DottedSymbol& dottedSymbol, Object* pObject)
{
	Frame* pFrame = SeekTarget(dottedSymbol);
	if (!pFrame) return false;
	pFrame->AssignObject(dottedSymbol.GetSymbolLast(), pObject);
	return true;
}

Object* Frame::LookupObject(const DottedSymbol& dottedSymbol) const
{
	const Frame* pFrame = const_cast<Frame*>(this)->SeekTarget(dottedSymbol);
	if (!pFrame) return nullptr;
	return pFrame->LookupObject(dottedSymbol.GetSymbolLast());
}

void Frame::AssignKlass(Klass& klass)
{
	klass.SetFrame(this);
	AssignObject(klass.GetSymbol(), new Object_Klass(klass));
}

void Frame::AssignFunction(Function* pFunction)
{
	pFunction->SetFrame(this);
	AssignObject(pFunction->GetSymbol(), new Object_Function(pFunction));
}

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------

}
