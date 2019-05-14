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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Function
//------------------------------------------------------------------------------
String Value_Function::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s>", GetFunction().MakeFullName().c_str());
	return str;
}

String Value_Function::ToStringDetail(const StringStyle& ss) const
{
	return GetFunction().ToString(ss);
}

const DeclCallable* Value_Function::GetDeclCallable() const
{
	return &GetFunction().GetDeclCallable();
}

void Value_Function::DoCall(Processor& processor, Argument& argument)
{
	GetFunction().DoCall(processor, argument);
}

}
