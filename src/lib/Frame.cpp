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
	RefPtr<ObjectMap> _pObjectMap;
public:
	// Constructor
	Frame_Source() : Frame(Type::Source), _pObjectMap(new ObjectMap()) {}
public:
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pObjectMap->Assign(pSymbol, pObject);
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		return _pObjectMap->Lookup(pSymbol);
	}
};

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Frame_Branch : public Frame {
public:
	// Referable declaration
	Gurax_DeclareReferable(Frame_Branch);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Frame_Branch");
protected:
	RefPtr<Frame> _pFrameLeft;
	RefPtr<Frame> _pFrameRight;
public:
	// Constructor
	Frame_Branch(Frame* pFrameLeft, Frame* pFrameRight) : Frame(Type::Branch),
		_pFrameLeft(pFrameLeft), _pFrameRight(pFrameRight) {}
public:
	const Frame* GetLeft() const { return _pFrameLeft.get(); }
	const Frame* GetRight() const { return _pFrameRight.get(); }
public:
	virtual void AssignObject(const Symbol* pSymbol, Object* pObject) override {
		_pFrameRight->AssignObject(pSymbol, pObject);
	}
	virtual Object* LookupObject(const Symbol* pSymbol) const override {
		if (Object* pObject = _pFrameRight->LookupObject(pSymbol)) return pObject;
		return _pFrameLeft->LookupObject(pSymbol);
	}
};

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
Frame* Frame::CreateSource()
{
	return new Frame_Source();
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
		Object* pObject = pFrame->LookupObject(pSymbol);
		if (!pObject) return nullptr;
		pFrame = pObject->ProvideFrame();
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
	klass.SetFrameParent(this);
	AssignObject(klass.GetSymbol(), new Object_Klass(klass));
}

void Frame::AssignFunction(Function* pFunction)
{
	pFunction->SetFrameParent(this);
	AssignObject(pFunction->GetSymbol(), new Object_Function(pFunction));
}

bool Frame::AssignModule(Module* pModule)
{
	return false;
}

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------

}
