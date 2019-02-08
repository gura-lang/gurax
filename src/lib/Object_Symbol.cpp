//==============================================================================
// Object_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_Symbol
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Klass_Symbol
//------------------------------------------------------------------------------
KlassT_Symbol Klass_Symbol("Symbol");

void KlassT_Symbol::DoPrepare(Frame* pFrame)
{
	SetAttrs(Klass_Object, Flag::Immutable);
	pFrame->AssignKlass(*this);
}

}
