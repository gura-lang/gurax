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
		if (IsSep(*p)) {
			prefix += GetSep();
			p++;
		}
		while (IsSep(*p)) p++;
	} else {
		while (IsSep(*p)) {
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
			if (IsSep(ch) || ch == '\0') {
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
			} else if (IsSep(ch)) {
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
	if (sepTailFlag && !pathName.empty() && !IsSep(pathName[pathName.size() - 1])) {
		pathName += GetSep();
	}
	return pathName;
}

}
