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

${help.ComposePropertyHelp(Bool, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Bool, `en)}

${help.ComposeMethodHelp(Bool, `en)}
)**";

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
VType_Bool VTYPE_Bool("Bool");

void VType_Bool::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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

String Value_Bool::ToString(const StringStyle& ss) const
{
	const char* strEntity = _flag? "true" : "false";
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity);
	return strEntity;
}

}
