//==============================================================================
// Object_stringptr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_stringptr
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_stringptr::KlassEx
//------------------------------------------------------------------------------
Object_stringptr::KlassEx Object_stringptr::klass("stringptr");

void Object_stringptr::KlassEx::DoPrepare()
{
	SetAttrs(Object::klass, Flag::Immutable);
}

bool Object_stringptr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
