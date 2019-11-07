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
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Nil
//------------------------------------------------------------------------------
VType& Value_Nil::vtype = VTYPE_Nil;

}
