//==============================================================================
// Version.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Version
//------------------------------------------------------------------------------
const char* Version::GetBanner(bool timeStampFlag)
{
	static char buff[256];
#if defined(_DEBUG)
	const char* debugIndicator = " *Debug*";
#else
	const char* debugIndicator = "";
#endif
#if defined(_MSC_VER)
	::sprintf(buff, "Gurax %s [MSC v.%d, %s%s%s] %s",
			GURAX_VERSION, _MSC_VER, __DATE__,
			timeStampFlag? " " __TIME__ : "", debugIndicator, GURAX_COPYRIGHT);
#elif defined(__clang_major__) && defined(__clang_minor__)
	::sprintf(buff, "Gurax %s [clang v.%d.%d, %s%s%s] %s",
			GURAX_VERSION, __clang_major__, __clang_minor__, __DATE__,
			timeStampFlag? " " __TIME__ : "", debugIndicator, GURAX_COPYRIGHT);
#elif defined(__GNUC__) && defined(__GNUC_MINOR__)
	::sprintf(buff, "Gurax %s [GNUC v.%d.%d, %s%s%s] %s",
			GURAX_VERSION, __GNUC__, __GNUC_MINOR__, __DATE__,
			timeStampFlag? " " __TIME__ : "", debugIndicator, GURAX_COPYRIGHT);
#else
	::sprintf(buff, "Gurax %s [%s%s] %s",
			GURAX_VERSION, __DATE__, timeStampFlag? " " __TIME__ : "", GURAX_COPYRIGHT);
#endif
	return buff;
}

const char *Version::GetTimeStamp()
{
	return __DATE__ " " __TIME__;
}

bool Version::CheckCoreVersion(const char* strVer, ...)
{
	const char* strCoreVer = GetVersion();
	if (::strcmp(strCoreVer, strVer) == 0) return true;
	va_list vargs;
	va_start(vargs, strVer);
	while (const char* strVerOther = va_arg(vargs, const char*)) {
		if (::strcmp(strCoreVer, strVerOther) == 0) return true;
	}
	va_end(vargs);
	return false;
}

}
