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

${help.ComposePropertyHelp(Nil, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Nil, `en)}

${help.ComposeMethodHelp(Nil, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Nil == Nil
Gurax_ImplementOpBinary(Eq, Nil, Nil)
{
	return new Value_Bool(true);
}

// Any == Nil
Gurax_ImplementOpBinary(Eq, Any, Nil)
{
	return new Value_Bool(false);
}

// Nil == Any
Gurax_ImplementOpBinary(Eq, Nil, Any)
{
	return new Value_Bool(false);
}

// Nil != Nil
Gurax_ImplementOpBinary(Ne, Nil, Nil)
{
	return new Value_Bool(false);
}

// Any != Nil
Gurax_ImplementOpBinary(Ne, Any, Nil)
{
	return new Value_Bool(true);
}

// Nil != Any
Gurax_ImplementOpBinary(Ne, Nil, Any)
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Implementation of operator
	Gurax_AssignOpBinary(Eq, Nil, Nil);
	Gurax_AssignOpBinary(Eq, Any, Nil);
	Gurax_AssignOpBinary(Eq, Nil, Any);
	Gurax_AssignOpBinary(Ne, Nil, Nil);
	Gurax_AssignOpBinary(Ne, Any, Nil);
	Gurax_AssignOpBinary(Ne, Nil, Any);
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
