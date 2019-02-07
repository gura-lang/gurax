//==============================================================================
// Object_Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_Binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_Binary
//------------------------------------------------------------------------------
KlassT_Binary Klass_Binary("binary");

void KlassT_Binary::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
