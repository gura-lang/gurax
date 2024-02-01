//==============================================================================
// Referencer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Referencer
//------------------------------------------------------------------------------
void Referencer::Bootup()
{
}


//------------------------------------------------------------------------------
// Referencer_Lookup
//------------------------------------------------------------------------------
Referencer_Lookup::Referencer_Lookup(Frame* pFrame, const Symbol* pSymbol, Value* pValue) :
							_pFrame(pFrame), _pSymbol(pSymbol), _pValue(pValue)
{
}

void Referencer_Lookup::SetValue(Processor& processor, Value* pValue)
{
	_pValue.reset(pValue->Reference());
	GetFrame().Assign(GetSymbol(), pValue);
}

String Referencer_Lookup::ToString(const StringStyle& ss) const
{
	return String().Format("Referencer_Lookup:%s", GetSymbol()->GetName());
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
