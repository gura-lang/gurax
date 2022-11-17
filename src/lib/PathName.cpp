//==============================================================================
// PathName.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathName
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)
const char PathName::SepPlatform		= SepMSWIN;
const bool PathName::CaseFlagPlatform	= false;
#elif defined(GURAX_ON_LINUX)
const char PathName::SepPlatform		= SepUNIX;
const bool PathName::CaseFlagPlatform	= true;
#elif defined(GURAX_ON_DARWIN)
const char PathName::SepPlatform		= SepUNIX;
const bool PathName::CaseFlagPlatform	= false;
#else
const char PathName::SepPlatform		= SepUNIX;
const bool PathName::CaseFlagPlatform	= false;
#endif

char PathName::FindSep(char sepDefault) const
{
	const char* p = _pathName;
	for ( ; *p; p++) if (IsSep(*p)) return *p;
	return sepDefault;
}

String PathName::ReplaceSep(const char* sep) const
{
	String pathNameRtn;
	const char* p = _pathName;
	for ( ; *p; p++) {
		if (IsSep(*p)) {
			pathNameRtn += sep;
		} else {
			pathNameRtn += *p;
		}
	}
	return pathNameRtn;
}

void PathName::SplitIntoFields(String* pDriveLetter, String* pPrefix, StringList& fields) const
{
	enum class Stat { Field, Sep } stat = Stat::Field;
	const char* p = _pathName;
	if (String::IsAlpha(*p) && *(p + 1) == ':') {
		*pDriveLetter += *p;
		*pDriveLetter += ':';
		p += 2;
		if (IsSepEx(*p)) {
			*pPrefix += GetSep();
			p++;
		}
		while (IsSepEx(*p)) p++;
	} else {
		while (IsSepEx(*p)) {
			*pPrefix += GetSep();
			p++;
		}
	}
	String field;
	for ( ; ; p++) {
		char ch = *p;
		Gurax_BeginPushbackRegion();
		switch (stat) {
		case Stat::Field: {
			if (IsSepEx(ch) || ch == '\0') {
				if (field == ".") {
					// nothing to do
				} else if (field == "..") {
					if (fields.empty()) {
						if (pPrefix->empty()) {
							fields.push_back(field);
						}
					} else if (fields.back() == "..") {
						fields.push_back(field);
					} else {
						fields.pop_back();
					}
				} else if (!field.empty()) {
					fields.push_back(field);
				}
				field.clear();
				stat = Stat::Sep;
			} else {
				field += ch;
			}
			break;
		}
		case Stat::Sep: {
			if (ch == '\0') {
				fields.push_back("");
			} else if (IsSepEx(ch)) {
				// nothing to do
			} else {
				Gurax_Pushback();
				stat = Stat::Field;
			}
			break;
		}
		}
		Gurax_EndPushbackRegion();
		if (ch == '\0') break;
	}
}

String PathName::Regulate() const
{
	String driveLetter;
	String prefix;
	StringList fields;
	SplitIntoFields(&driveLetter, &prefix, fields);
	String pathName;
	pathName += driveLetter;
	pathName += prefix;
	auto pField = fields.begin();
	if (pField != fields.end()) {
		pathName += *pField++;
		for ( ; pField != fields.end(); pField++) {
			pathName += GetSep();
			pathName += *pField;
		}
	}
	return pathName;
}

String PathName::JoinBefore(const char* pathName) const
{
	String pathNameRtn;
	if (*pathName) {
		pathNameRtn += pathName;
		if (!*_pathName) {
			// nothing to do
		} else if (IsSep(pathNameRtn.back())) {
			pathNameRtn += IsSep(*_pathName)? _pathName + 1 : _pathName;
		} else {
			if (!IsSep(*_pathName)) pathNameRtn += GetSep();
			pathNameRtn += _pathName;
		}
	} else {
		pathNameRtn += _pathName;
	}
	return pathNameRtn;
}

String PathName::JoinAfter(const char* pathName) const
{
	String pathNameRtn;
	if (*_pathName) {
		pathNameRtn += _pathName;
		if (!*pathName) {
			// nothing to do
		} else if (IsSep(pathNameRtn.back())) {
			pathNameRtn += IsSep(*pathName)? pathName + 1 : pathName;
		} else {
			if (!IsSep(*pathName)) pathNameRtn += GetSep();
			pathNameRtn += pathName;
		}
	} else {
		pathNameRtn += pathName;
	}
	return pathNameRtn;
}

void PathName::SplitFileName(String* pDirName, String* pFileName) const
{
	const char* p = SeekFileName();
	if (pDirName) *pDirName = String(_pathName, p);
	if (pFileName) *pFileName = String(p);
}

void PathName::SplitBottomName(String* pHeadName, String* pBottomName) const
{
	const char* p = SeekTerminator();
	if (p != _pathName && IsSep(*(p - 1))) p--;
	const char* pEnd = p;
	for ( ; p != _pathName && !IsSepEx(*(p - 1)); p--) ;
	if (pHeadName) *pHeadName = (p == pEnd)? String(_pathName) : String(_pathName, p);
	if (pBottomName) *pBottomName = String(p, pEnd);
}

void PathName::SplitExtName(String* pBaseName, String* pExtName) const
{
	const char* p = SeekExtName();
	if (pBaseName) *pBaseName = String(_pathName, p);
	if (pExtName) *pExtName = String(p);
}

const char* PathName::SeekFileName() const
{
	const char* p = SeekTerminator();
	for ( ; p != _pathName && !IsSepEx(*(p - 1)); p--) ;
	return p;
}

const char* PathName::SeekExtName() const
{
	const char* pTerminator = SeekTerminator();
	const char* p = pTerminator;
	if (p == _pathName) return pTerminator;
	p--;
	for ( ; ; p--) {
		if (*p == '.') {
			return (p == _pathName || IsSepEx(*(p - 1)) || *(p - 1) == '.')?
				pTerminator : p;
		}
		if (p == _pathName || IsSepEx(*p)) break;
	}
	return pTerminator;
}

bool PathName::HasWildCard() const
{
	for (const char* p = _pathName; *p; p++) if (IsWildCardChar(*p)) return true;
	return false;
}

bool PathName::HasSeparator() const
{
	for (const char* p = _pathName; *p; p++) if (IsSepEx(*p)) return true;
	return false;
}

template<typename T_CharCmp>
bool PathName::DoesMatchSub(const char* pathName1, const char* pathName2)
{
	T_CharCmp charCmp;
	const char* p1 = pathName1;
	const char* p2 = pathName2;
	for ( ; ; p1++, p2++) {
		char ch1 = *p1, ch2 = *p2;
		if (IsSep(ch1) && IsSep(ch2)) {
			// nothing to do
		} else if (charCmp(ch1, ch2) != 0) {
			return false;
		} else if (!ch1) {
			break;
		}
	}
	return true;
}

bool PathName::DoesMatch(const char* pathName) const
{
	return GetCaseFlag()?
		DoesMatchSub<CharCase>(pathName, _pathName) :
		DoesMatchSub<CharICase>(pathName, _pathName);
}

template<typename T_CharCmp>
bool PathName::DoesMatchPatternSub(const char* pattern, const char* pathName)
{
	T_CharCmp charCmp;
	if (*pattern == '\0') {
		return *pathName == '\0';
	} else if (*pattern == '*') {
		return DoesMatchPatternSub<T_CharCmp>(pattern + 1, pathName) ||
			(*pathName != '\0' && DoesMatchPatternSub<T_CharCmp>(pattern, pathName + 1));
	} else if (*pattern == '?') {
		return *pathName != '\0' && DoesMatchPatternSub<T_CharCmp>(pattern + 1, pathName + 1);
	} else if (*pattern == '[') {
		pattern++;
		if (*pattern == '!') {
			pattern++;
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (charCmp(*pathName, *pattern) == 0 || (IsSep(*pathName) && IsSep(*pattern))) return false;
			}
		} else {
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (!(charCmp(*pathName, *pattern) == 0 || (IsSep(*pathName) && IsSep(*pattern)))) return false;
			}
		}
		if (*pattern == ']') pattern++;
		return DoesMatchPatternSub<T_CharCmp>(pattern, pathName + 1);
	} else {
		return (charCmp(*pathName, *pattern) == 0 || (IsSep(*pathName) && IsSep(*pattern))) &&
			DoesMatchPatternSub<T_CharCmp>(pattern + 1, pathName + 1);
	}
}

bool PathName::DoesMatchPattern(const char* pattern) const
{
	if (*pattern == '!') {
		pattern++;
		return GetCaseFlag()?
			!DoesMatchPatternSub<CharCase>(pattern, _pathName) :
			!DoesMatchPatternSub<CharICase>(pattern, _pathName);
	}
	return GetCaseFlag()?
		DoesMatchPatternSub<CharCase>(pattern, _pathName) :
		DoesMatchPatternSub<CharICase>(pattern, _pathName);
}

String PathName::MakeAbsName() const
{
	if (IsAbsName()) return PathName(*this, _pathName).Regulate();
	String pathName = JoinBefore(OAL::GetCurDir().c_str());
	return PathName(*this, pathName).Regulate();
}

bool PathName::IsAbsName() const
{
	return IsSep(*_pathName) ||
		(String::IsAlpha(*_pathName) && *(_pathName + 1) == ':' && IsSep(*(_pathName + 2)));
}

}
