//==============================================================================
// Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Match
//------------------------------------------------------------------------------
Match::Match(Pattern* pPattern, OnigRegion* region, StringReferable* pStr) :
	_pPattern(pPattern), _region(region), _pStr(pStr)
{
}

Match::Match(Pattern* pPattern, OnigRegion* region, String str) :
	Match(pPattern, region, new StringReferable(std::move(str)))
{
}

Match::~Match()
{
	::onig_region_free(_region, 1);
}

Group* Match::CreateGroup(int iGroup) const
{
	return new Group(Reference(), _region->beg[iGroup], _region->end[iGroup]);
}

#if 0
int Match::LookupGroupNum(const char* name)
{
	if (!_pNameMap) {
		_pNameMap.reset(new NameMap());
		//::onig_name_to_group_numbers(
	}
}
#endif

String Match::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("re.Match:%dregions", _region->num_regs);
	return str;
}

Gurax_EndModuleScope(re)
