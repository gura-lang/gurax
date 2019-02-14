//==============================================================================
// Value_Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Argument
//------------------------------------------------------------------------------
VType_Argument VTYPE_Argument("Argument");

void VType_Argument::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_Argument
//------------------------------------------------------------------------------

}
