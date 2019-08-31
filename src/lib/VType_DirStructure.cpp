//==============================================================================
// VType_DirStructure.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DirStructure
//------------------------------------------------------------------------------
VType_DirStructure VTYPE_DirStructure("DirStructure");

void VType_DirStructure::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_DirStructure
//------------------------------------------------------------------------------
VType& Value_DirStructure::vtype = VTYPE_DirStructure;

}
