//==============================================================================
// VType_Undefined.cpp
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
// Undefined#__ToString__()
Gurax_DeclareClassMethod(Undefined, __ToString__)
{
	Declare(VTYPE_String, Flag::None);
	StringStyle::DeclareAttrOpt(*this);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts the object to a string.\n");
}

Gurax_ImplementClassMethod(Undefined, __ToString__)
{
	// Function body
	return new Value_String("<Undefined>");
}

//------------------------------------------------------------------------------
// VType_Undefined
//------------------------------------------------------------------------------
VType_Undefined VTYPE_Undefined("Undefined");

void VType_Undefined::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Empty, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Undefined, __ToString__));
}

//------------------------------------------------------------------------------
// Value_Undefined
//------------------------------------------------------------------------------
VType& Value_Undefined::vtype = VTYPE_Undefined;

String Value_Undefined::ToString(const StringStyle& ss) const
{
	return (ss.IsBracket() || ss.IsUndefVisible())? "<Undefined>" : String::Empty;
}

}
