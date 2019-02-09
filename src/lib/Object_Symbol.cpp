//==============================================================================
// Value_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Value_Symbol
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
VType_Symbol VTYPE_Symbol("Symbol");

void VType_Symbol::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
