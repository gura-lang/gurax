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
#elis defined(GURAX_ON_DARWIN)
const char PathName::SepPlatform		= SepUNIX;
const bool PathName::CaseFlagPlatform	= false;
#else
const char PathName::SepPlatform		= SepUNIX;
const bool PathName::CaseFlagPlatform	= false;
#endif

String PathName::Regulate() const
{
	enum class Stat { Field, Sep } stat = Stat::Field;
	String prefix;
	char driveLetter = '\0';
	const char* p = _pathName;
	if (String::IsAlpha(*p) && *(p + 1) == ':') {
		driveLetter = *p;
		p += 2;
		if (IsSepEx(*p)) {
			prefix += GetSep();
			p++;
		}
		while (IsSepEx(*p)) p++;
	} else {
		while (IsSepEx(*p)) {
			prefix += GetSep();
			p++;
		}
	}
	StringList fields;
	String field;
	bool sepTailFlag = false;
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
						if (prefix.empty()) {
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
				sepTailFlag = true;
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
	String pathName;
	if (driveLetter != '\0') {
		pathName += driveLetter;
		pathName += ':';
	}
	pathName += prefix;
	for (auto pField = fields.begin(); pField != fields.end(); pField++) {
		if (pField != fields.begin()) pathName += GetSep();
		pathName += *pField;
	}
	if (sepTailFlag && !pathName.empty() && !IsSepEx(pathName[pathName.size() - 1])) {
		pathName += GetSep();
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
	if (pHeadName) *pHeadName = String(_pathName, p);
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
	for ( ; p - 1 != _pathName && !IsSepEx(*(p - 1)); p--) {
		if (*p == '.') return (*(p - 1) == '.')? pTerminator : p;
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
bool PathName::DoesMatchSub(const char* pattern, const char* pathName)
{
	T_CharCmp charCmp;
	if (*pattern == '\0') {
		return *pathName == '\0';
	} else if (*pattern == '*') {
		return DoesMatchSub<T_CharCmp>(pattern + 1, pathName) ||
			(*pathName != '\0' && DoesMatchSub<T_CharCmp>(pattern, pathName + 1));
	} else if (*pattern == '?') {
		return *pathName != '\0' && DoesMatchSub<T_CharCmp>(pattern + 1, pathName + 1);
	} else if (*pattern == '[') {
		pattern++;
		if (*pattern == '!') {
			pattern++;
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (charCmp(*pathName, *pattern) == 0) return false;
			}
		} else {
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (charCmp(*pathName, *pattern) != 0) return false;
			}
		}
		if (*pattern == ']') pattern++;
		return DoesMatchSub<T_CharCmp>(pattern, pathName + 1);
	} else {
		return charCmp(*pattern, *pathName) == 0 && DoesMatchSub<T_CharCmp>(pattern + 1, pathName + 1);
	}
}

bool PathName::DoesMatch(const char* pattern) const
{
	if (*pattern == '!') {
		pattern++;
		return GetCaseFlag()?
			!DoesMatchSub<CharCase>(pattern, _pathName) :
			!DoesMatchSub<CharICase>(pattern, _pathName);
	}
	return GetCaseFlag()?
		DoesMatchSub<CharCase>(pattern, _pathName) :
		DoesMatchSub<CharICase>(pattern, _pathName);
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
