//==============================================================================
// Object_stringptr.cpp
// This object type is designed to be used with Formatter.
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_stringptr
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_stringptr
//------------------------------------------------------------------------------
KlassT_stringptr Klass_stringptr("stringptr");

void KlassT_stringptr::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

bool Object_stringptr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
