//==============================================================================
// VType_Any.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Any#ToString()
Gurax_DeclareMethod(Any, ToString)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementMethod(Any, ToString)
{
	// Function body
	return new Value_String("Any");
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// !Any
Gurax_ImplementOpUnary(Not, Any)
{
	return value.GetBool()? Value::false_() : Value::true_();
}

//------------------------------------------------------------------------------
// VType_Any
//------------------------------------------------------------------------------
VType_Any VTYPE_Any("Any");

void VType_Any::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Any, ToString));
	// Assignment of operator
	Gurax_AssignOpUnary(Not, Any);
}

Value* VType_Any::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// Value_Any
//------------------------------------------------------------------------------
VType& Value_Any::vtype = VTYPE_Any;

}
