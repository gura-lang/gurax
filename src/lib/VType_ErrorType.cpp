//==============================================================================
// VType_ErrorType.cpp
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
// Implementation of property
//------------------------------------------------------------------------------
// module.ErrorType#name
Gurax_DeclareProperty_R(ErrorType, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(ErrorType, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetErrorType().GetName());
}

//------------------------------------------------------------------------------
// VType_ErrorType
//------------------------------------------------------------------------------
VType_ErrorType VTYPE_ErrorType("ErrorType");

void VType_ErrorType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(ErrorType, name));
}

//------------------------------------------------------------------------------
// Value_ErrorType
//------------------------------------------------------------------------------
VType& Value_ErrorType::vtype = VTYPE_ErrorType;

String Value_ErrorType::ToStringFormatter(const StringStyle& ss) const
{
	String str;
	_ToStringFormatter(str, ss);
	str += ":";
	str += GetErrorType().GetName();
	str += ">";
	return str;
}

String Value_ErrorType::ToStringDetail(const StringStyle& ss) const
{
	return ToStringFormatter(ss);
}

}
