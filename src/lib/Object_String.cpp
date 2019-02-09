//==============================================================================
// Object_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_String
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
VTypeT_String VType_String("String");

void VTypeT_String::DoPrepare(Frame* pFrame)
{
	SetAttrs(VType_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

bool Object_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
