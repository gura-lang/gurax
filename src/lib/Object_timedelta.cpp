//==============================================================================
// Object_timedelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_timedelta
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Object_timedelta::KlassEx
//------------------------------------------------------------------------------
Object_timedelta::KlassEx Object_timedelta::klass("timedelta");

void Object_timedelta::KlassEx::DoPrepare(Frame* pFrame)
{
	SetAttrs(Object::klass, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
