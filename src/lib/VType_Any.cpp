//==============================================================================
// VType_Any.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Any#ToString()
Gurax_DeclareClassMethod(Any, ToString)
{
	Declare(VTYPE_String, Flag::None);
	StringStyle::DeclareAttrOpt(*this);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementClassMethod(Any, ToString)
{
	// Function body
	return new Value_String("<Any>");
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// !Any
Gurax_ImplementOpUnary(Not, Any)
{
	return value.GetBool()? Value::false_() : Value::true_();
}

// Any => Any
Gurax_ImplementBinary(Pair, Any, Any)
{
	return Value_List::Create(valueL.Reference(), valueR.Reference());
}

//------------------------------------------------------------------------------
// VType_Any
//------------------------------------------------------------------------------
VType_Any VTYPE_Any("Any");

void VType_Any::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Any, ToString));
	// Assignment of operator
	Gurax_AssignOpUnary(Not, Any);
	Gurax_AssignBinary(Pair, Any, Any);
}

Value* VType_Any::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.Reference();
}

//------------------------------------------------------------------------------
// Value_Any
//------------------------------------------------------------------------------
VType& Value_Any::vtype = VTYPE_Any;

String Value_Any::ToString(const StringStyle& ss) const
{
	return String().Format("<Any>");
}

}
