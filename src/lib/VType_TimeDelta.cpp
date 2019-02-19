//==============================================================================
// VType_TimeDelta.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_TimeDelta
//------------------------------------------------------------------------------
VType_TimeDelta VTYPE_TimeDelta("Timedelta");

void VType_TimeDelta::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_TimeDelta
//------------------------------------------------------------------------------

}
