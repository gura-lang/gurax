//==============================================================================
// PathName.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PathName
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)
const char PathName::SepDefault			= SepMSWIN;
const bool PathName::CaseFlagDefault	= false;
#elif defined(GURAX_ON_LINUX)
const char PathName::SepDefault			= SepUNIX;
const bool PathName::CaseFlagDefault	= true;
#elis defined(GURAX_ON_DARWIN)
const char PathName::SepDefault			= SepUNIX;
const bool PathName::CaseFlagDefault	= false;
#else
const char PathName::SepDefault			= SepUNIX;
const bool PathName::CaseFlagDefault	= false;
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

#if 0
bool PathName::DoesMatchName(const char *pattern)
{
	if (*pattern == '!') {
		return !DoesMatchNameSub(pattern + 1, fileName, ignoreCaseFlag);
	}
	return DoesMatchNameSub(pattern, fileName, ignoreCaseFlag);
}
	
bool PathName::DoesMatchNameSub(const char *pattern, const char *fileName, bool ignoreCaseFlag)
{
	if (*pattern == '\0') {
		return *fileName == '\0';
	} else if (*pattern == '*') {
		return DoesMatchNameSub(pattern + 1, fileName, ignoreCaseFlag) ||
			(*fileName != '\0' && DoesMatchNameSub(pattern, fileName + 1, ignoreCaseFlag));
	} else if (*pattern == '?') {
		return *fileName != '\0' && DoesMatchNameSub(pattern + 1, fileName + 1, ignoreCaseFlag);
	} else if (*pattern == '[') {
		pattern++;
		if (*pattern == '!') {
			pattern++;
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (CompareChar(*fileName, *pattern, ignoreCaseFlag) == 0) return false;
			}
		} else {
			for ( ; *pattern != ']' && *pattern != '\0'; pattern++) {
				if (CompareChar(*fileName, *pattern, ignoreCaseFlag) != 0) return false;
			}
		}
		if (*pattern == ']') pattern++;
		return DoesMatchNameSub(pattern, fileName + 1, ignoreCaseFlag);
	} else {
		return CompareChar(*pattern, *fileName, ignoreCaseFlag) == 0 &&
						DoesMatchNameSub(pattern + 1, fileName + 1, ignoreCaseFlag);
	}
}
#endif

}
