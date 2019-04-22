//==============================================================================
// VType_Attribute.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
VType_Attribute VTYPE_Attribute("Attribute");

void VType_Attribute::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------

}
