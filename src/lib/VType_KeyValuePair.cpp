//==============================================================================
// VType_KeyValuePair.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_KeyValuePair
//------------------------------------------------------------------------------
VType_KeyValuePair VTYPE_KeyValuePair("KeyValuePair");

void VType_KeyValuePair::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_KeyValuePair
//------------------------------------------------------------------------------
VType& Value_KeyValuePair::vtype = VTYPE_KeyValuePair;

}
