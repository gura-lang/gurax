//==============================================================================
// Value_Undefined.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Undefined
//------------------------------------------------------------------------------
VType_Undefined VTYPE_Undefined("Undefined");

void VType_Undefined::DoPrepare(Frame& frame)
{
	SetAttrs(VType::Empty, Flag::Immutable);
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_Undefined
//------------------------------------------------------------------------------

}
