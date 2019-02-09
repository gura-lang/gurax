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
VType_StringPtr VTYPE_StringPtr("StringPtr");

void VType_StringPtr::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

bool Object_StringPtr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
