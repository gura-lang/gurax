//==============================================================================
// VType_Group.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Group
//------------------------------------------------------------------------------
VType_Group VTYPE_Group("Group");

void VType_Group::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Group
//------------------------------------------------------------------------------
VType& Value_Group::vtype = VTYPE_Group;

Gurax_EndModuleScope(re)
