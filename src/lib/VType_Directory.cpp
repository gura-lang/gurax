//==============================================================================
// VType_Directory.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Directory
//------------------------------------------------------------------------------
VType_Directory VTYPE_Directory("Directory");

void VType_Directory::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Directory
//------------------------------------------------------------------------------
VType& Value_Directory::vtype = VTYPE_Directory;

}
