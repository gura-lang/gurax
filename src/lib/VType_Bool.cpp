//==============================================================================
// VType_Bool.cpp
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
// VType_Bool
//------------------------------------------------------------------------------
VType_Bool VTYPE_Bool("Bool");

void VType_Bool::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Bool
//------------------------------------------------------------------------------
VType& Value_Bool::vtype = VTYPE_Bool;

bool Value_Bool::Format_d(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	char buff[128];
	return formatter.PutAlignedString(
		formatterFlags, formatterFlags.FormatNumber_d(static_cast<Int>(GetBool()), buff, sizeof(buff)));
}

String Value_Bool::ToStringFormatter(const StringStyle& ss) const
{
	String str;
	_ToStringFormatter(str, ss);
	str.Format(":%s>", _flag? "true" : "false");
	return str;
}

String Value_Bool::ToStringDetail(const StringStyle& ss) const
{
	return _flag? "true" : "false";
}

}
