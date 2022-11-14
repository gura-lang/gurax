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

${help.ComposePropertyHelp(Undefined, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Undefined, `en)}

${help.ComposeMethodHelp(Undefined, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Undefined#__str__()
Gurax_DeclareClassMethod(Undefined, __str__)
{
	Declare(VTYPE_String, Flag::None);
	StringStyle::DeclareAttrOpt(*this);
	AddHelp("en", u8R"**(
Converts the object to a string.
)**");
}

Gurax_ImplementClassMethod(Undefined, __str__)
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Invalid, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Undefined, __str__));
}

//------------------------------------------------------------------------------
// Value_Undefined
//------------------------------------------------------------------------------
VType& Value_Undefined::vtype = VTYPE_Undefined;

bool Value_Undefined::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeFunction() || function.IsTypeConstructor() || function.IsTypeStatement()) {
		return true;
	} else if (function.IsTypeMethod()) {
		if (function.IsSet(Function::Flag::OfClass)) return true;
	}
	Error::Issue(ErrorType::ValueError, "the function %s must be evaluated with an instance",
						function.MakeFullName().c_str());
	return false;
}

String Value_Undefined::ToString(const StringStyle& ss) const
{
	return (ss.IsBracket() || ss.IsUndefVisible())? "<Undefined>" : String::Empty;
}

}
