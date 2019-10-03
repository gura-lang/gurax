//==============================================================================
// Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Pattern
//------------------------------------------------------------------------------
Pattern::Pattern() : _regex(nullptr)
{
}

Pattern::~Pattern()
{
	::onig_free(_regex);
}

bool Pattern::Prepare(const char* pattern)
{
	OnigErrorInfo einfo;
	int rtn = ::onig_new(&_regex, reinterpret_cast<const OnigUChar*>(pattern),
						 reinterpret_cast<const OnigUChar*>(pattern) + ::strlen(pattern),
						 ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
	if (rtn != ONIG_NORMAL) {
		IssueGuestError(rtn, einfo);
		return false;
	}
	return true;
}

Match* Pattern::CreateMatch(const char* str)
{
	OnigRegion* region = ::onig_region_new();
	const char* strEnd = str + ::strlen(str);
	const char* strStart = str;
	const char* strRange = strEnd;
	int rtn = ::onig_search(_regex, reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(strEnd),
							reinterpret_cast<const OnigUChar*>(strStart),
							reinterpret_cast<const OnigUChar*>(strRange),
							region, ONIG_OPTION_NONE);
	if (rtn < 0) {
		::onig_region_free(region, 1);
		return nullptr;
	}
	return new Match(Reference(), region, str);
}

String Pattern::ToString(const StringStyle& ss) const
{
	return "re.Pattern";
}

Gurax_EndModuleScope(re)
