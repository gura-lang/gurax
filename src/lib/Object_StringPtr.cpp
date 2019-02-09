//==============================================================================
// Object_StringPtr.cpp
// This object type is designed to be used with Formatter.
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_StringPtr
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_StringPtr
//------------------------------------------------------------------------------
VTypeT_StringPtr VType_StringPtr("StringPtr");

void VTypeT_StringPtr::DoPrepare(Frame* pFrame)
{
	SetAttrs(VType_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

bool Object_StringPtr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
