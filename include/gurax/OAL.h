//==============================================================================
// OAL.h
//==============================================================================
#ifndef GURAX_OAL_H
#define GURAX_OAL_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// OAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OAL {
public:
	static const char FileSeparatorMSWIN		= '\\';
	static const char FileSeparatorUNIX			= '/';
	static const char FileSeparator;
	static const bool IgnoreCaseInPathNameFlag;
public:
	static bool IsFileSeparator(char ch) { return ch == FileSeparatorMSWIN || ch == FileSeparatorUNIX; }
	static String RegulatePathName(const char* pathName, char chSeparator = FileSeparator);
};

}

#endif
