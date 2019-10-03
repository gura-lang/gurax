//==============================================================================
// Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Match
//------------------------------------------------------------------------------
Match::Match(OnigRegion* pRegion) : _pRegion(pRegion)
{
}

Match::~Match()
{
	::onig_region_free(_pRegion, 1);
}

String Match::ToString(const StringStyle& ss) const
{
	return "re.Match";
}

Gurax_EndModuleScope(re)
