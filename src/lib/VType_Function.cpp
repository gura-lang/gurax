//==============================================================================
// VType_Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Function#name
Gurax_DeclareProperty_R(Function, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The name of the function.");
}

Gurax_ImplementPropertyGetter(Function, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetFunction().GetName());
}

// Function#type
Gurax_DeclareProperty_R(Function, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The type of the function. One of `` `statement``, `` `function``, `` `method`` and `` `classMethod``.");
}

Gurax_ImplementPropertyGetter(Function, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Function& func = valueThis.GetFunction();
	return new Value_Symbol(
		func.IsTypeStatement()? Gurax_Symbol(statement) :
		func.IsTypeFunction()? Gurax_Symbol(function) :
		func.IsTypeMethod()? Gurax_Symbol(method) :
		func.IsTypeClassMethod()? Gurax_Symbol(classMethod) : Symbol::Empty);
}

//------------------------------------------------------------------------------
// VType_Function
//------------------------------------------------------------------------------
VType_Function VTYPE_Function("Function");

void VType_Function::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(Function, name));
	Assign(Gurax_CreateProperty(Function, type));
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
