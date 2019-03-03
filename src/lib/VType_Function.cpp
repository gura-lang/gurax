//==============================================================================
// VType_Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
const DeclCaller* Value_Function::GetDeclCaller() const
{
	return &GetFunction().GetDeclCaller();
}

Value* Value_Function::DoCall(Processor& processor, Argument& argument)
{
	return GetFunction().Eval(processor, argument);
}

}
