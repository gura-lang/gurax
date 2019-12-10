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
// Implementation of method
//------------------------------------------------------------------------------

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
}

//------------------------------------------------------------------------------
// Value_ErrorType
//------------------------------------------------------------------------------
VType& Value_ErrorType::vtype = VTYPE_ErrorType;

String Value_ErrorType::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetErrorType().GetName();
	str += ">";
	return str;
}

String Value_ErrorType::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
