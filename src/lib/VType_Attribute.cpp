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
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
VType& Value_Attribute::vtype = VTYPE_Attribute;

}
