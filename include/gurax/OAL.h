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
	class GURAX_DLLDECLARE DynamicLibrary {
	private:
#if defined(GURAX_ON_MSWIN)
		HMODULE _hLibrary;
#else
		void *_hLibrary;
#endif
	public:
		// Constructor
		DynamicLibrary();
		// Copy constructor/operator
		DynamicLibrary(const DynamicLibrary& src) = delete;
		DynamicLibrary& operator=(const DynamicLibrary& src) = delete;
		// Move constructor/operator
		DynamicLibrary(DynamicLibrary&& src) = delete;
		DynamicLibrary& operator=(DynamicLibrary&& src) noexcept = delete;
		// Destructor
		~DynamicLibrary() = default;
	public:
		bool Open(const char* pathName);
		void* GetEntry(const char* funcName);
	};
public:
	static String ToNativeString(const char* str);
	static String FromNativeString(const char* str);
	static String GetCurDir();
	static bool DoesExistDir(const char* pathName);
	static bool DoesExistFile(const char* pathName);
};

}

#endif
