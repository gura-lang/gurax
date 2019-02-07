//==============================================================================
// Object_undefined.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_undefined
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_undefined::KlassEx
//------------------------------------------------------------------------------
Object_undefined::KlassEx Object_undefined::klass("undefined");

void Object_undefined::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
