//==============================================================================
// VType_PUnit.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PUnit
//------------------------------------------------------------------------------
VType_PUnit VTYPE_PUnit("PUnit");

void VType_PUnit::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_PUnit
//------------------------------------------------------------------------------

}
