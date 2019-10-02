//==============================================================================
// VType_Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// VType_Match
//------------------------------------------------------------------------------
VType_Match VTYPE_Match("Match");

void VType_Match::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Match
//------------------------------------------------------------------------------
VType& Value_Match::vtype = VTYPE_Match;

Gurax_EndModuleScope(re)
