//==============================================================================
// Value_DateTime.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DateTime
//------------------------------------------------------------------------------
VType_DateTime VTYPE_DateTime("Datetime");

void VType_DateTime::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_DateTime
//------------------------------------------------------------------------------

}
