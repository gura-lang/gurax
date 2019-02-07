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
// Klass_StringPtr
//------------------------------------------------------------------------------
KlassT_StringPtr Klass_StringPtr("stringptr");

void KlassT_StringPtr::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

bool Object_StringPtr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
