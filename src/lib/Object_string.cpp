//==============================================================================
// Object_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_String
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_String
//------------------------------------------------------------------------------
KlassT_String Klass_String("string");

void KlassT_String::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

bool Object_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
