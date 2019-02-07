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
// Object_stringptr::KlassEx
//------------------------------------------------------------------------------
Object_stringptr::KlassEx Object_stringptr::klass("stringptr");

void Object_stringptr::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

bool Object_stringptr::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
