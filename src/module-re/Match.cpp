//==============================================================================
// Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Match
//------------------------------------------------------------------------------
Match::Match(Pattern* pPattern, OnigRegion* pRegion) : _pPattern(pPattern), _pRegion(pRegion)
{
}

Match::~Match()
{
	::onig_region_free(_pRegion, 1);
}

Group* Match::CreateGroup(int iGroup) const
{
	return new Group(Reference(), _pRegion->beg[iGroup], _pRegion->end[iGroup]);
}

String Match::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("re.Match:%dregions", _pRegion->num_regs);
	return str;
}

Gurax_EndModuleScope(re)
