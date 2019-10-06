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

int Match::LookupGroupNum(const char* name)
{
    return ::onig_name_to_backref_number(
		_pPattern->GetRegex(), reinterpret_cast<const OnigUChar*>(name),
		reinterpret_cast<const OnigUChar*>(name + ::strlen(name)), _region);
}

String Match::GetString() const
{
	return GetSourceStringSTL().substr(GetPosBegin(), GetPosEnd() - GetPosBegin());
}

String Match::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("re.Match:%d-%d", GetPosBegin(), GetPosEnd());
	return str;
}

Gurax_EndModuleScope(re)
