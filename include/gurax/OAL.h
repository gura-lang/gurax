//==============================================================================
// OAL.h
//==============================================================================
#ifndef GURAX_OAL_H
#define GURAX_OAL_H
#include "Common.h"
#include "StringPicker.h"

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
	static int ExecProgram(
		const char* pathName, StringPicker&& args,
		Stream& streamCIn, Stream& streamCOut, Stream& streamCErr, bool forkFlag);
	static int ExecProgram(
		const char* pathName, const ValueList& args,
		Stream& streamCIn, Stream& streamCOut, Stream& streamCErr, bool forkFlag) {
		return ExecProgram(pathName, StringPicker_ValueList(args), streamCIn, streamCOut, streamCErr, forkFlag);
	}
	static int ExecProgram(
		const char* pathName, const StringList& args,
		Stream& streamCIn, Stream& streamCOut, Stream& streamCErr, bool forkFlag) {
		return ExecProgram(pathName, StringPicker_StringList(args), streamCIn, streamCOut, streamCErr, forkFlag);
	}
};

}

#endif
