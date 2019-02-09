//==============================================================================
// Object_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_Symbol
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
VTypeT_Symbol VType_Symbol("Symbol");

void VTypeT_Symbol::DoPrepare(Frame* pFrame)
{
	SetAttrs(VType_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
