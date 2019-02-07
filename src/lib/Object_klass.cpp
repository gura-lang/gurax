//==============================================================================
// Object_klass.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_klass
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_klass::KlassEx
//------------------------------------------------------------------------------
Object_klass::KlassEx Object_klass::klass("klass");

void Object_klass::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
