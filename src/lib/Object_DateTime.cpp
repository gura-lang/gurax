//==============================================================================
// Object_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_DateTime
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_DateTime
//------------------------------------------------------------------------------
KlassT_DateTime Klass_DateTime("Datetime");

void KlassT_DateTime::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_Object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
