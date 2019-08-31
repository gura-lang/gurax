//==============================================================================
// VType_StringPtr.cpp
// This object type is designed to be used with Formatter.
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_StringPtr
//------------------------------------------------------------------------------
VType_StringPtr VTYPE_StringPtr("StringPtr");

void VType_StringPtr::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_StringPtr
//------------------------------------------------------------------------------
VType& Value_StringPtr::vtype = VTYPE_StringPtr;

bool Value_StringPtr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
