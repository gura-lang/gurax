//==============================================================================
// OAL.h
//==============================================================================
#ifndef GURAX_OAL_H
#define GURAX_OAL_H
#include "Common.h"
#include "StringPicker.h"

#if defined(GURAX_ON_MSWIN)
#include <shlobj.h>
#if defined(_MSC_VER)
using mode_t = int;
#define S_IRUSR 0x0100
#define S_IWUSR 0x0080
#define S_IXUSR 0x0040
#else
#include <sys/stat.h>
#endif
#define S_IRGRP 0x0020
#define S_IWGRP 0x0010
#define S_IXGRP 0x0008
#define S_IROTH 0x0004
#define S_IWOTH 0x0002
#define S_IXOTH 0x0001
#else
#include <unistd.h>
#include <dlfcn.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#endif

#if defined(GURAX_ON_DARWIN)
#include <mach-o/dyld.h>
#endif

namespace Gurax {

//------------------------------------------------------------------------------
// OAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OAL {
public:
	class GURAX_DLLDECLARE FileStat : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(FileStat);
	public:
		using Attrs = UInt32;
		struct Attr {
			static const Attrs Dir	= (1 << 22);
			static const Attrs Chr	= (1 << 21);
			static const Attrs Blk	= (1 << 20);
			static const Attrs Reg	= (1 << 19);
			static const Attrs Fifo	= (1 << 18);
			static const Attrs Lnk	= (1 << 17);
			static const Attrs Sock	= (1 << 16);
		};
	private:
		String _pathName;
		UInt32 _attr;
		UInt32 _bytes;
		RefPtr<DateTime> _pDateTimeA;
		RefPtr<DateTime> _pDateTimeM;
		RefPtr<DateTime> _pDateTimeC;
		long _uid;
		long _gid;
	public:
		FileStat() : _attr(0), _bytes(0), _uid(0), _gid(0) {}
		FileStat(String pathName, UInt32 attr, UInt32 bytes,
				 DateTime* pDateTimeA, DateTime* pDateTimeM, DateTime* pDateTimeC,
				 long uid, long gid) :
			_pathName(pathName), _attr(attr), _bytes(bytes),
			_pDateTimeA(pDateTimeA), _pDateTimeM(pDateTimeM), _pDateTimeC(pDateTimeC),
			_uid(uid), _gid(gid) {}
		FileStat(const FileStat& fileStat) :
			_pathName(fileStat._pathName), _attr(fileStat._attr), _bytes(fileStat._bytes),
			_pDateTimeA(fileStat._pDateTimeA->Reference()), _pDateTimeM(fileStat._pDateTimeM->Reference()),
						_pDateTimeC(fileStat._pDateTimeC->Reference()),
			_uid(fileStat._uid), _gid(fileStat._gid) {}
#if defined(GURA_ON_MSWIN)
		FileStat(const char* pathName, const BY_HANDLE_FILE_INFORMATION& attrData);
		FileStat(const char* pathName, const WIN32_FILE_ATTRIBUTE_DATA& attrData);
		FileStat(const char* pathName, const WIN32_FIND_DATA& findData);
#else
		FileStat(const char* pathName, const struct stat& stat);
#endif
	protected:
		~FileStat() = default;
	public:
		static FileStat* Generate(const char* pathName);
		const char* GetPathName() const { return _pathName.c_str(); }
		ULong GetSize() const { return _bytes; }
		const DateTime& GetDateTimeA() const { return *_pDateTimeA; }
		const DateTime& GetDateTimeM() const { return *_pDateTimeM; }
		const DateTime& GetDateTimeC() const { return *_pDateTimeC; }
		long GetUid() const { return _uid; }
		long GetGid() const { return _gid; }
		long GetMode() const { return _attr & 0777; }
		bool IsDir() const { return (_attr & Attr::Dir) != 0; }
		bool IsChr() const { return (_attr & Attr::Chr) != 0; }
		bool IsBlk() const { return (_attr & Attr::Blk) != 0; }
		bool IsReg() const { return (_attr & Attr::Reg) != 0; }
		bool IsFifo() const { return (_attr & Attr::Fifo) != 0; }
		bool IsLnk() const { return (_attr & Attr::Lnk) != 0; }
		bool IsSock() const { return (_attr & Attr::Sock) != 0; }
	};
	class GURAX_DLLDECLARE DynamicLibrary {
	private:
#if defined(GURAX_ON_MSWIN)
		HMODULE _hLibrary;
#else
		void* _hLibrary;
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
	static void PutEnv(const char* name, const char* value);
	static String GetEnv(const char* name, bool* pFoundFlag = nullptr);
	static String ToNativeString(const char* str);
	static String FromNativeString(const char* str);
	static String GetCurDir();
	static bool DoesExistDir(const char* pathName);
	static bool DoesExistFile(const char* pathName);
	static int ExecProgram(
		const char* pathName, StringPicker&& args,
		Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag);
	static int ExecProgram(
		const char* pathName, const ValueList& args,
		Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag) {
		return ExecProgram(pathName, StringPicker_ValueList(args), pStreamCIn, pStreamCOut, pStreamCErr, forkFlag);
	}
	static int ExecProgram(
		const char* pathName, const StringList& args,
		Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag) {
		return ExecProgram(pathName, StringPicker_StringList(args), pStreamCIn, pStreamCOut, pStreamCErr, forkFlag);
	}
	static Double GetTickTime();
public:
	static DateTime* CreateDateTime(const struct tm& tm, int secsOffset);
	static DateTime* CreateDateTime(time_t t, bool utcFlag = false);
#if defined(GURAX_ON_MSWIN)
	static DateTime* CreateDateTime(const SYSTEMTIME& st, int secsOffset);
	static DateTime* CreateDateTime(const FILETIME& ft, bool utcFlag = false);
	static SYSTEMTIME DateTimeToSYSTEMTIME(const DateTime& dt);
	static FILETIME DateTimeToFILETIME(const DateTime& dt);
#endif
private:
	static void AppendCmdLine(String& cmdLine, const char* arg);
#if defined(GURAX_ON_MSWIN)
	static String ConvCodePage(const char* str, UINT codePageSrc, UINT codePageDst)
#endif
};

}

#endif
