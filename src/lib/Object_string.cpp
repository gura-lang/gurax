//==============================================================================
// Object_string.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_string
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_string
//------------------------------------------------------------------------------
KlassT_string Klass_string("string");

void KlassT_string::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

bool Object_string::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
