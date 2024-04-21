//==============================================================================
// OAL.h
//==============================================================================
#ifndef GURAX_OAL_H
#define GURAX_OAL_H
#include "Common.h"
#include "Referable.h"
#include "StringPicker.h"

#if defined(GURAX_ON_MSWIN)
#include <windows.h>
#include <stdarg.h>
#include <io.h>
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
#include <stdarg.h>
#include <dirent.h>
#include <unistd.h>
#include <dlfcn.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
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
	static const char SepPathList;
public:
	enum class FileType { None, Unknown, Normal, Directory, Device, FIFO, Link, Socket };
	class GURAX_DLLDECLARE SymbolAssoc_FileType : public SymbolAssoc<FileType, FileType::None> {
	public:
		SymbolAssoc_FileType() {
			Assoc(Gurax_Symbol(unknown),	FileType::Unknown);
			Assoc(Gurax_Symbol(normal),		FileType::Normal);
			Assoc(Gurax_Symbol(directory),	FileType::Directory);
			Assoc(Gurax_Symbol(device),		FileType::Device);
			Assoc(Gurax_Symbol(fifo),		FileType::FIFO);
			Assoc(Gurax_Symbol(link),		FileType::Link);
			Assoc(Gurax_Symbol(socket),		FileType::Socket);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_FileType());
		}
	};
	static FileType SymbolToFileType(const Symbol* pSymbol) {
		return SymbolAssoc_FileType::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* FileTypeToSymbol(FileType fileType) {
		return SymbolAssoc_FileType::GetInstance().ToSymbol(fileType);
	}
public:
	class GURAX_DLLDECLARE DirLister {
		String _dirName;
#if defined(GURAX_ON_MSWIN)
		HANDLE _hFind;
#else
		DIR* _dirp;
#endif
		bool _joinPathNameFlag;
	public:
		DirLister(const char* dirName, bool joinPathNameFlag = true);
		~DirLister();
		bool Next(const char* pattern, String& pathName, bool* pDirFlag);
	};
public:
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
	class GURAX_DLLDECLARE Thread : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Thread);
	private:
#if defined(GURAX_ON_MSWIN)
		HANDLE _hThread;
		DWORD _threadId;
#else
		pthread_t _pt;
#endif
	public:
		// Constructor
		Thread();
		// Copy constructor/operator
		Thread(const Thread& src) = delete;
		Thread& operator=(const Thread& src) = delete;
		// Move constructor/operator
		Thread(Thread&& src) = delete;
		Thread& operator=(Thread&& src) noexcept = delete;
	protected:
		// Destructor
		virtual ~Thread();
	public:
		void Start();
		void Wait();
		virtual void Run() = 0;
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const Thread& thread) const { return this == &thread; }
		bool IsEqualTo(const Thread& thread) const { return IsIdentical(thread); }
		bool IsLessThan(const Thread& thread) const { return this < &thread; }
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
public:
	class GURAX_DLLDECLARE Semaphore : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Semaphore);
	private:
#if defined(GURAX_ON_MSWIN)
		HANDLE _hMutex;
#else
		sem_t _sem;
#endif
	public:
		Semaphore();
		~Semaphore();
		void Wait();
		void Release();
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const Semaphore& semaphore) const { return this == &semaphore; }
		bool IsEqualTo(const Semaphore& semaphore) const { return IsIdentical(semaphore); }
		bool IsLessThan(const Semaphore& semaphore) const { return this < &semaphore; }
		String ToString(const StringStyle& ss = StringStyle::Empty) const;
	};
public:
	class GURAX_DLLDECLARE FILECloser {
	private:
		FILE* _fp;
	public:
		FILECloser(FILE* fp) : _fp(fp) {}
		~FILECloser() { ::fclose(_fp); }
		FILE* get() { return _fp; }
	};
public:
	class GURAX_DLLDECLARE FDCloser {
	private:
		int _fd;
	public:
		FDCloser(int fd) : _fd(fd) {}
		~FDCloser() { ::close(_fd); _fd = -1;}
		int get() { return _fd; }
	};
#if defined(GURAX_ON_MSWIN)
	class GURAX_DLLDECLARE HANDLECloser {
	private:
		HANDLE _handle;
	public:
		HANDLECloser(HANDLE handle) : _handle(handle) {}
		~HANDLECloser() { ::CloseHandle(_handle); }
		HANDLE get() { return _handle; }
	};
#else
	class GURAX_DLLDECLARE MemoryUnmapper {
	private:
		void* _p;
		size_t _bytes;
	public:
		MemoryUnmapper(void* p, size_t bytes) : _p(p), _bytes(bytes) {}
		~MemoryUnmapper() { ::munmap(_p, _bytes); }
		void* get() { return _p; }
	};
#endif
public:
	static String GetPathName_Executable();
	static String GetDirName_Base();
	static String GetDirName_Executable();
	static String GetDirName_Data();
	static String GetDirName_Module();
	static String GetDirName_Include();
	static String GetDirName_Library();
	static String GetDirName_Font();
	static String GetDirName_Script();
	static String GetDirName_Local();
public:
	static void PutEnv(const char* name, const char* value);
	static String GetEnv(const char* name, bool* pFoundFlag = nullptr);
	static const char* GetEncodingForConsole();
	static const Symbol* GetLangCode();
	static String ToNativeString(const char* str);
	static String FromNativeString(const char* str);
	static bool DoesExist(const char* pathName) {
		return GetFileType(pathName) != FileType::None;
	}
	static bool IsFileType(const char* pathName, FileType fileType) {
		return GetFileType(pathName) == fileType;
	}
	static FileType GetFileType(const char* pathName);
	static int ExecProgram(
		const char* pathName, StringPicker&& args,
		Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag);
	//static int ExecProgram(
	//	const char* pathName, const ValueList& args,
	//	Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag) {
	//	return ExecProgram(pathName, StringPicker_ValueList(args, StringStyle::Quote_NilVisible),
	//					pStreamCIn, pStreamCOut, pStreamCErr, forkFlag);
	//}
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
	static DateTime* CreateDateTimeCur(bool utcFlag);
	static int GetSecsOffsetTZ();
	static bool FollowLink(String& pathName);
public:
	static bool CopyDir(const char* dirNameSrc, const char* dirNameDst);
	static bool CopyDirTree(const char* dirNameSrc, const char* dirNameDst);
	static bool CreateDirTree(const char* dirName);
	static bool RemoveDirTree(const char* dirName);
	static bool PrepareLocalDir();
public:
	static bool ChangeDir(const char* dirName);
	static bool ChangeMode(const char* pathName, mode_t mode, bool followLinkFlag);
	static bool ChangeMode(const char* pathName, const char* mode, bool followLinkFlag);
	static bool Copy(const char* pathNameSrc, const char* pathNameDst, bool failIfExistFlag, bool followLinkFlag);
	static bool CreateLink(const char* pathNameSrc, const char* pathNameDst);
	static bool CreateDir(const char* dirName);
	static bool IsDir(const char* pathName, bool* pExistFlag = nullptr);
	static String GetCurDir();
	static bool Remove(const char* pathName);
	static bool RemoveDir(const char* dirName);
	static bool Rename(const char* pathNameOld, const char* pathNameNew);
	static void Sleep(Double secs);
public:
	static bool ParseStatMode(const char* mode, mode_t& st_mode);
	static void AppendCmdLine(String& cmdLine, const char* arg);
#if defined(GURAX_ON_MSWIN)
	static String ConvCodePage(const char* str, UINT codePageSrc, UINT codePageDst);
#else
	static String ReadLink(const char* pathName);
#endif
};

}

#endif
