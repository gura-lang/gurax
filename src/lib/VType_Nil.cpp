//==============================================================================
// VType_Nil.cpp
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
// Implementation of operator
//------------------------------------------------------------------------------
// Nil == Nil
Gurax_ImplementBinary(Eq, Nil, Nil)
{
	return new Value_Bool(true);
}

// Any == Nil
Gurax_ImplementBinary(Eq, Any, Nil)
{
	return new Value_Bool(false);
}

// Nil == Any
Gurax_ImplementBinary(Eq, Nil, Any)
{
	return new Value_Bool(false);
}

// Nil != Nil
Gurax_ImplementBinary(Ne, Nil, Nil)
{
	return new Value_Bool(false);
}

// Any != Nil
Gurax_ImplementBinary(Ne, Any, Nil)
{
	return new Value_Bool(true);
}

// Nil != Any
Gurax_ImplementBinary(Ne, Nil, Any)
{
	return new Value_Bool(true);
}

//------------------------------------------------------------------------------
// VType_Nil
//------------------------------------------------------------------------------
VType_Nil VTYPE_Nil("Nil");

void VType_Nil::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Implementation of operator
	Gurax_AssignBinary(Eq, Nil, Nil);
	Gurax_AssignBinary(Eq, Any, Nil);
	Gurax_AssignBinary(Eq, Nil, Any);
	Gurax_AssignBinary(Ne, Nil, Nil);
	Gurax_AssignBinary(Ne, Any, Nil);
	Gurax_AssignBinary(Ne, Nil, Any);
}

//------------------------------------------------------------------------------
// Value_Nil
//------------------------------------------------------------------------------
VType& Value_Nil::vtype = VTYPE_Nil;

String Value_Nil::ToString(const StringStyle& ss) const
{
	return (ss.IsBracket() || ss.IsNilVisible())? "<Nil>" : String::Empty;
}

}
