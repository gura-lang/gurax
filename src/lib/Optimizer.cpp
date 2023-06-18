//==============================================================================
// Optimizer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Optimizer
//------------------------------------------------------------------------------
String Optimizer::ToString(const StringStyle& ss) const
{
	return String().Format("Optimizer:%s", GetName());
}

//------------------------------------------------------------------------------
// OptimizerList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// OptimizerOwner
//------------------------------------------------------------------------------
void OptimizerOwner::Clear()
{
	for (Optimizer* pOptimizer : *this) Optimizer::Delete(pOptimizer);
	clear();
}

//------------------------------------------------------------------------------
// Optimizer_None
//-------------------------------------------------------------------------
void Optimizer_None::InstanceEx::Reset()
{
}

bool Optimizer_None::InstanceEx::Update(Processor& processor, RefPtr<Array>& pArray, const Array& arrayGrad)
{
	return true;
}

}
