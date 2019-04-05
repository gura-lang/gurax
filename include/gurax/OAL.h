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
	static String ToNativeString(const char* str);
	static String FromNativeString(const char* str);
	static String GetCurDir();
};

}

#endif
