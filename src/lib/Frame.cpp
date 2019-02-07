//==============================================================================
// Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Frame
//------------------------------------------------------------------------------
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

void Frame::AssignKlass(const Symbol* pSymbol, Klass& klass)
{
	AssignObject(pSymbol, new Object_klass(klass));
}

bool Frame::AssignKlass(const DottedSymbol& dottedSymbol, Klass& klass)
{
	return AssignObject(dottedSymbol, new Object_klass(klass));
}

void Frame::AssignFunction(const Symbol* pSymbol, Function* pFunction)
{
	pFunction->SetFrame(this);
	AssignObject(pSymbol, new Object_function(pFunction));
}

bool Frame::AssignFunction(const DottedSymbol& dottedSymbol, Function* pFunction)
{
	Frame* pFrame = SeekTarget(dottedSymbol);
	if (!pFrame) return false;
	pFrame->AssignFunction(dottedSymbol.GetSymbolLast(), pFunction);
	return true;
}

//------------------------------------------------------------------------------
// Frame_Node
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Frame_Branch
//------------------------------------------------------------------------------

}
