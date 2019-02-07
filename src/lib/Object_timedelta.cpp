//==============================================================================
// Object_TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_TimeDelta
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_TimeDelta
//------------------------------------------------------------------------------
KlassT_TimeDelta Klass_TimeDelta("timedelta");

void KlassT_TimeDelta::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
