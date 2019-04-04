//==============================================================================
// OAL.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

#if defined(GURAX_ON_MSWIN)
const char OAL::FileSeparator				= FileSeparatorMSWIN;
const bool OAL::IgnoreCaseInPathNameFlag	= false;
#elif defined(GURAX_ON_LINUX)
const char OAL::FileSeparator				= FileSeparatorUNIX;
const bool OAL::IgnoreCaseInPathNameFlag	= true;
#elis defined(GURAX_ON_DARWIN)
const char OAL::FileSeparator				= FileSeparatorUNIX;
const bool OAL::IgnoreCaseInPathNameFlag	= false;
#else
const char OAL::FileSeparator				= FileSeparatorUNIX;
const bool OAL::IgnoreCaseInPathNameFlag	= false;
#endif

//------------------------------------------------------------------------------
// OAL
//------------------------------------------------------------------------------
String OAL::RegulatePathName(const char* pathName, char chSeparator)
{
	enum class Stat { Field, FileSeparator } stat = Stat::Field;
	String prefix;
	char driveLetter = '\0';
	const char* p = pathName;
	if (String::IsAlpha(*p) && *(p + 1) == ':') {
		driveLetter = *p;
		p += 2;
		if (IsFileSeparator(*p)) {
			prefix += chSeparator;
			p++;
		}
		while (IsFileSeparator(*p)) p++;
	} else {
		while (IsFileSeparator(*p)) {
			prefix += chSeparator;
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
			if (IsFileSeparator(ch) || ch == '\0') {
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
				stat = Stat::FileSeparator;
			} else {
				field += ch;
			}
			break;
		}
		case Stat::FileSeparator: {
			if (ch == '\0') {
				sepTailFlag = true;
			} else if (IsFileSeparator(ch)) {
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
	String rtn;
	if (driveLetter != '\0') {
		rtn += driveLetter;
		rtn += ':';
	}
	rtn += prefix;
	for (auto pField = fields.begin(); pField != fields.end(); pField++) {
		if (pField != fields.begin()) rtn += chSeparator;
		rtn += *pField;
	}
	if (sepTailFlag && !rtn.empty() && !IsFileSeparator(rtn[rtn.size() - 1])) {
		rtn += chSeparator;
	}
	return rtn;
}

}
