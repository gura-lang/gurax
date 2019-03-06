//==============================================================================
// FunctionCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
Value* FunctionCustom::DoCall(Processor& processor, Argument& argument) const
{
	argument.SetPUnitNext(GetPUnitBody());
	return Value::nil();
}

}
