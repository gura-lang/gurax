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

String Pattern::SubstituteByString(const char* str, const char* replace, int cnt)
{
#if 0
	enum Stat { STAT_Start, STAT_Escape };
	size_t len = ::strlen(str);
	String result;
	OnigRegion *pRegion = ::onig_region_new();
	int idx = 0;
	for ( ; cnt != 0; cnt--) {
		int rtn = ::onig_search(pRegEx,
						reinterpret_cast<const OnigUChar *>(str),
						reinterpret_cast<const OnigUChar *>(str + len),
						reinterpret_cast<const OnigUChar *>(str + idx),
						reinterpret_cast<const OnigUChar *>(str + len),
						pRegion, ONIG_OPTION_NONE);
		if (rtn >= 0) {
			if (rtn < idx || pRegion->num_regs == 0 || pRegion->end[0] <= idx) {
				SetError_FailInOniguruma(sig);
				goto error_done;
			}
			result += String(str + idx, rtn - idx);
			Stat stat = STAT_Start;
			for (const char *p = replace; *p != '\0'; p++) {
				char ch = *p;
				if (stat == STAT_Start) {
					if (ch == '\\') {
						stat = STAT_Escape;
					} else {
						result.push_back(*p);
					}
				} else if (stat == STAT_Escape) {
					if (IsDigit(ch)) {
						int iGroup = ch - '0';
						if (iGroup < pRegion->num_regs) {
							int idxBegin = pRegion->beg[iGroup];
							int idxEnd = pRegion->end[iGroup];
							result += String(str + idxBegin, idxEnd - idxBegin);
						}
						stat = STAT_Start;
					} else {
						result.push_back(GetEscaped(ch));
						stat = STAT_Start;
					}
				}
			}
			idx = pRegion->end[0];
		} else if (rtn == ONIG_MISMATCH) {
			break;
		} else { // error
			SetError_OnigurumaError(sig, rtn);
			goto error_done;
		}
	}
	::onig_region_free(pRegion, 1); // 1:free self, 0:free contents only
	result += String(str + idx);
	return result;
error_done:
	::onig_region_free(pRegion, 1); // 1:free self, 0:free contents only
#endif
	return "";
}

String Pattern::SubstituteByFunction(const char* str, const Function& func, int cnt)
{
#if 0
	enum Stat { STAT_Start, STAT_Escape };
	size_t len = ::strlen(str);
	String result;
	OnigRegion *pRegion = ::onig_region_new();
	int idx = 0;
	for ( ; cnt != 0; cnt--) {
		int rtn = ::onig_search(pRegEx,
					reinterpret_cast<const OnigUChar *>(str),
					reinterpret_cast<const OnigUChar *>(str + len),
					reinterpret_cast<const OnigUChar *>(str + idx),
					reinterpret_cast<const OnigUChar *>(str + len),
					pRegion, ONIG_OPTION_NONE);
		if (rtn >= 0) {
			Object_match *pObj = new Object_match();
			if (!pObj->SetMatchInfo(str, pRegEx, pRegion, 0)) {
				SetError_FailInOniguruma(sig);
				delete pObj;
				goto error_done;
			}
			AutoPtr<Argument> pArg(new Argument(pFunc));
			if (!pArg->StoreValue(env, Value(pObj))) goto error_done;
			Value resultFunc = pFunc->Eval(env, *pArg);
			if (sig.IsSignalled()) goto error_done;
			result += String(str + idx, rtn - idx);
			result += resultFunc.ToString(false);
			if (sig.IsSignalled()) goto error_done;
			idx = pRegion->end[0];
		} else if (rtn == ONIG_MISMATCH) {
			break;
		} else { // error
			SetError_OnigurumaError(sig, rtn);
			goto error_done;
		}
	}
	::onig_region_free(pRegion, 1); // 1:free self, 0:free contents only
	result += String(str + idx);
	return result;
error_done:
	::onig_region_free(pRegion, 1); // 1:free self, 0:free contents only
#endif
	return "";
}

String Pattern::ToString(const StringStyle& ss) const
{
	return "re.Pattern";
}

Gurax_EndModuleScope(re)
