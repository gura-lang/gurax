//==============================================================================
// Version.h
//==============================================================================
#ifndef GURAX_VERSION_H
#define GURAX_VERSION_H

#include "Common.h"

#define GURAX_VERSION_MAJOR	0
#define GURAX_VERSION_MINOR	0
#define GURAX_VERSION_PATCH	1

#define GURAX_VERSION	"0.0.1"

#define GURAX_COPYRIGHT	"Copyright (C) 2011-2020 ypsitau"

namespace Gurax {

//------------------------------------------------------------------------------
// Version
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Version {
public:
	static const char* GetVersion() { return GURAX_VERSION; }
	static const char* GetBanner(bool timeStampFlag);
	static const char* GetTimeStamp();
	static bool CheckCoreVersion(const char* strVer, ...);
};

}

#endif
