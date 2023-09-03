//==============================================================================
// Referencer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Referencer
//------------------------------------------------------------------------------
Referencer::Referencer(Frame* pFrame, const Symbol* pSymbol, Value* pValue) : _pFrame(pFrame), _pSymbol(pSymbol), _pValue(pValue)
{
}

String Referencer::ToString(const StringStyle& ss) const
{
	return String().Format("Referencer");
}

//------------------------------------------------------------------------------
// ReferencerList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ReferencerOwner
//------------------------------------------------------------------------------
void ReferencerOwner::Clear()
{
	for (Referencer* pReferencer : *this) Referencer::Delete(pReferencer);
	clear();
}

}
