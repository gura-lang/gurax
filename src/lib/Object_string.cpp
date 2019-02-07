//==============================================================================
// Object_string.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_string
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_string::KlassEx
//------------------------------------------------------------------------------
Object_string::KlassEx Object_string::klass("string");

void Object_string::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
}

bool Object_string::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
