//==============================================================================
// VType_Nil.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Nil
//------------------------------------------------------------------------------
VType_Nil VTYPE_Nil("Nil");

void VType_Nil::DoPrepare(Frame& frameOuter)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Nil
//------------------------------------------------------------------------------

}
