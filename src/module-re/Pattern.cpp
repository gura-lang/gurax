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
		IssueError_Onigmo(rtn, einfo);
		return false;
	}
	return true;
}

Match* Pattern::CreateMatch(const char* str, int pos, int posEnd)
{
	OnigRegion_Ptr region(::onig_region_new());
	const char* strEnd = (posEnd < 0)? str + ::strlen(str) : String::Forward(str, posEnd);
	const char* strStart = String::Forward(str, pos);
	const char* strRange = strEnd;
	int rtn = ::onig_search(_regex, reinterpret_cast<const OnigUChar*>(str),
							reinterpret_cast<const OnigUChar*>(strEnd),
							reinterpret_cast<const OnigUChar*>(strStart),
							reinterpret_cast<const OnigUChar*>(strRange),
							region.get(), ONIG_OPTION_NONE);
	if (rtn < 0) return nullptr;
	return new Match(Reference(), region.release(), str);
}

String Pattern::SubstituteByString(const char* str, const char* replace, int cnt)
{
	enum class Stat { Start, Escape };
	size_t len = ::strlen(str);
	String strRtn;
	OnigRegion_Ptr region(::onig_region_new());
	int idx = 0;
	for ( ; cnt != 0; cnt--) {
		int rtn = ::onig_search(_regex, reinterpret_cast<const OnigUChar *>(str),
								reinterpret_cast<const OnigUChar *>(str + len),
								reinterpret_cast<const OnigUChar *>(str + idx),
								reinterpret_cast<const OnigUChar *>(str + len),
								region.get(), ONIG_OPTION_NONE);
		if (rtn == ONIG_MISMATCH) {
			break;
		} else if (rtn < 0) { // error
			IssueError_Onigmo(rtn);
			return String::Empty;
		} else if (rtn < idx || region->num_regs == 0 || region->end[0] <= idx) {
			IssueError_Onigmo();
			return String::Empty;
		}
		strRtn += String(str + idx, rtn - idx);
		Stat stat = Stat::Start;
		for (const char *p = replace; *p != '\0'; p++) {
			char ch = *p;
			if (stat == Stat::Start) {
				if (ch == '\\') {
					stat = Stat::Escape;
				} else {
					strRtn += *p;
				}
			} else if (stat == Stat::Escape) {
				if (String::IsDigit(ch)) {
					int iGroup = ch - '0';
					if (iGroup < region->num_regs) {
						int idxBegin = region->beg[iGroup];
						int idxEnd = region->end[iGroup];
						strRtn += String(str + idxBegin, idxEnd - idxBegin);
					}
					stat = Stat::Start;
				} else {
					strRtn += String::ToEscaped(ch);
					stat = Stat::Start;
				}
			}
		}
		idx = region->end[0];
	}
	strRtn += String(str + idx);
	return strRtn;
}

String Pattern::SubstituteByFunction(const char* str, Processor& processor, const Function& func, int cnt)
{
	enum class Stat { Start, Escape };
	size_t len = ::strlen(str);
	String strRtn;
	OnigRegion_Ptr region(::onig_region_new());
	int idx = 0;
	RefPtr<Frame> pFrame(func.LockFrameOuter());
	for ( ; cnt != 0; cnt--) {
		int rtn = ::onig_search(_regex, reinterpret_cast<const OnigUChar *>(str),
								reinterpret_cast<const OnigUChar *>(str + len),
								reinterpret_cast<const OnigUChar *>(str + idx),
								reinterpret_cast<const OnigUChar *>(str + len),
								region.get(), ONIG_OPTION_NONE);
		if (rtn == ONIG_MISMATCH) {
			break;
		} else if (rtn < 0) { // error
			IssueError_Onigmo(rtn);
			return String::Empty;
		} else if (rtn < idx || region->num_regs == 0 || region->end[0] <= idx) {
			IssueError_Onigmo();
			return String::Empty;
		}
		RefPtr<Match> pMatch(new Match(Reference(), region.release(), str));
		RefPtr<Argument> pArgument(new Argument(func));
		ArgFeeder args(*pArgument);
		if (!args.FeedValue(*pFrame, new Value_Match(pMatch.release()))) return String::Empty;
		RefPtr<Value> pValueRtn(func.DoEval(processor, *pArgument));
		if (Error::IsIssued()) return String::Empty;
		strRtn += String(str + idx, rtn - idx);
		strRtn += pValueRtn->ToString();
		idx = region->end[0];
	}
	strRtn += String(str + idx);
	return strRtn;
}

String Pattern::ToString(const StringStyle& ss) const
{
	return "re.Pattern";
}

Gurax_EndModuleScope(re)
