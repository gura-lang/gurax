//==============================================================================
// Value_Symbol.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Symbol
//------------------------------------------------------------------------------
VType_Symbol VTYPE_Symbol("Symbol");

void VType_Symbol::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_Symbol
//------------------------------------------------------------------------------

}
