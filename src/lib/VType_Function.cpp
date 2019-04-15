//==============================================================================
// VType_Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frameOuter)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
const DeclCallable* Value_Function::GetDeclCallable() const
{
	return &GetFunction().GetDeclCallable();
}

void Value_Function::DoCall(Processor& processor, Argument& argument)
{
	GetFunction().DoCall(processor, argument);
}

}
