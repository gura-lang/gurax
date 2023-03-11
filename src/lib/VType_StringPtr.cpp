//==============================================================================
// VType_StringPtr.cpp
// This object type is designed to be used with Formatter.
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(StringPtr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(StringPtr, `en)}

${help.ComposeMethodHelp(StringPtr, `en)}
)""";

//------------------------------------------------------------------------------
// VType_StringPtr
//------------------------------------------------------------------------------
VType_StringPtr VTYPE_StringPtr("StringPtr");

void VType_StringPtr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_StringPtr
//------------------------------------------------------------------------------
VType& Value_StringPtr::vtype = VTYPE_StringPtr;

String Value_StringPtr::ToString(const StringStyle& ss) const
{
	if (ss.IsBracket()) return ToStringGeneric(ss, _str);
	return _str;
}

bool Value_StringPtr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
