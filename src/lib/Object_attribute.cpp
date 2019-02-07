//==============================================================================
// Object_attribute.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_attribute
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_attribute::KlassEx
//------------------------------------------------------------------------------
Object_attribute::KlassEx Object_attribute::klass("attribute");

void Object_attribute::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
