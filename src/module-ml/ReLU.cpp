//==============================================================================
// ReLU.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// ReLU
//------------------------------------------------------------------------------
bool ReLU::EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	return false;
}

bool ReLU::EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array)
{
	return false;
}

String ReLU::ToString(const StringStyle& ss) const
{
	return String().Format("ml.ReLU");
}

//------------------------------------------------------------------------------
// ReLUList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ReLUOwner
//------------------------------------------------------------------------------
void ReLUOwner::Clear()
{
	for (ReLU* pReLU : *this) ReLU::Delete(pReLU);
	clear();
}

Gurax_EndModuleScope(ml)
