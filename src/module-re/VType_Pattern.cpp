//==============================================================================
// VType_Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Pattern
//------------------------------------------------------------------------------
VType_Pattern VTYPE_Pattern("Pattern");

void VType_Pattern::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Pattern
//------------------------------------------------------------------------------
VType& Value_Pattern::vtype = VTYPE_Pattern;

Gurax_EndModuleScope(re)
