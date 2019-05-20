//==============================================================================
// OAL.cpp
//==============================================================================
#include "stdafx.h"
#if defined(GURAX_ON_MSWIN)
#include <shlobj.h>
#if defined(_MSC_VER)
typedef int mode_t;
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

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// OAL (MSWIN)
//------------------------------------------------------------------------------
String ConvCodePage(const char* str, UINT codePageSrc, UINT codePageDst)
{
	int cchWideChar = ::MultiByteToWideChar(codePageSrc, 0, str, -1, nullptr, 0);
	WCHAR* wcharBuff = new WCHAR [cchWideChar + 1];
	::MultiByteToWideChar(codePageSrc, 0, str, -1, wcharBuff, cchWideChar);
	int cchMultiByte = ::WideCharToMultiByte(codePageDst, 0,
				wcharBuff, cchWideChar, nullptr, 0, nullptr, nullptr);
	char* charBuff = new char [cchMultiByte + 1];
	::WideCharToMultiByte(codePageDst, 0,
				wcharBuff, cchWideChar, charBuff, cchMultiByte, nullptr, nullptr);
	charBuff[cchMultiByte] = '\0';
	String rtn(charBuff); // don't use String(charBuff, cchMultiByte) here!
	delete[] wcharBuff;
	delete[] charBuff;
	return rtn;
}

String OAL::ToNativeString(const char* str)
{
	return ConvCodePage(str, CP_UTF8, CP_THREAD_ACP);
}

String OAL::FromNativeString(const char* str)
{
	return ConvCodePage(str, CP_THREAD_ACP, CP_UTF8);
}

String OAL::GetCurDir()
{
	char rtn[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, rtn);
	String dirName = FromNativeString(rtn);
	if (dirName.empty() || !PathName::IsSep(dirName.back())) {
		dirName += PathName::SepPlatform;
	}
	return dirName;
}

bool OAL::DoesExistDir(const char* pathName)
{
	WIN32_FILE_ATTRIBUTE_DATA attrData;
	if (::GetFileAttributesEx(ToNativeString(pathName).c_str(),
							  GetFileExInfoStandard, &attrData) == 0) return false;
	return (attrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

bool OAL::DoesExistFile(const char* pathName)
{
	WIN32_FILE_ATTRIBUTE_DATA attrData;
	if (::GetFileAttributesEx(ToNativeString(pathName).c_str(),
							  GetFileExInfoStandard, &attrData) == 0) return false;
	return (attrData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) == 0;
}

//-----------------------------------------------------------------------------
// OAL::DynamicLibrary (MSWIN)
//-----------------------------------------------------------------------------
OAL::DynamicLibrary::DynamicLibrary() : _hModule(nullptr)
{
}

bool OAL::DynamicLibrary::Open(const char* pathName)
{
	_hModule = ::LoadLibrary(ToNativeString(pathName).c_str());
	if (!_hModule) {
		Error::Issue(ErrorType::ImportError, "can't open module file '%s'", pathName);
		return false;
	}
	return true;
}

void* OAL::DynamicLibrary::GetEntry(const char* funcName)
{
	if (!_hModule) {
		Error::Issue(ErrorType::ImportError, "library has not been opened");
		return nullptr;
	}
	FARPROC pFunc = ::GetProcAddress(_hModule, funcName);
	if (!pFunc) {
		String funcNameEx = "_";
		funcNameEx += funcName;
		pFunc = ::GetProcAddress(_hModule, funcNameEx.c_str());
	}
	if (!pFunc) {
		sig.SetError(ErrorType::ImportError, "can't find entry function '%s'", funcName);
		return nullptr;
	}
	return pFunc;
}

#else

//------------------------------------------------------------------------------
// OAL (POSIX)
//------------------------------------------------------------------------------
String OAL::ToNativeString(const char* str)
{
	return String(str);
}

String OAL::FromNativeString(const char* str)
{
	return String(str);
}

String OAL::GetCurDir()
{
	char* rtn = ::getcwd(nullptr, 0);
	String dirName = FromNativeString(rtn);
	::free(rtn);
	if (dirName.empty() || !PathName::IsSep(dirName.back())) {
		dirName += PathName::SepPlatform;
	}
	return dirName;
}

bool OAL::DoesExistDir(const char* pathName)
{
	struct stat stat;
	if (::stat(ToNativeString(pathName).c_str(), &stat) != 0) return false;
	return S_ISDIR(stat.st_mode);
}

bool OAL::DoesExistFile(const char* pathName)
{
	struct stat stat;
	if (::stat(ToNativeString(pathName).c_str(), &stat) != 0) return false;
	return S_ISREG(stat.st_mode);
}

int OAL::ExecProgram(
	const char* pathName, StringPicker&& args,
	Stream& streamCIn, Stream& streamCOut, Stream& streamCErr, bool forkFlag)
{
	int exitCode = 0;
#if 0
	pid_t pid = 0;
	RefPtr<Memory> pMemory(new MemoryHeap(32768));
	char *argv[4];
	argv[0] = ::strdup("/bin/sh");
	argv[1] = ::strdup("-c");
	String cmdLine;
	cmdLine = ToNativeString(pathName);
	foreach_const (ValueList, pValue, valList) {
		cmdLine += " ";
		AppendCmdLine(cmdLine, ToNativeString(pValue->GetString()).c_str());
	}
	argv[2] = ::strdup(cmdLine.c_str());
	argv[3] = nullptr;
	if (forkFlag) {
		pid_t pid = ::fork();
		if (pid == 0) {
			::execv("/bin/sh", argv);
			::exit(1);
		}
		goto done;
	}
	int fdsStdin[2];
	int fdsStdout[2];
	int fdsStderr[2];
	if (::pipe(fdsStdin) < 0 || ::pipe(fdsStdout) < 0 || ::pipe(fdsStderr) < 0) {
		Error::Issue(ERR_IOError, "failed to create pipes");
		goto done;
	}
	pid = ::fork();
	if (pid == 0) {
		::dup2(fdsStdin[0], 0);
		::dup2(fdsStdout[1], 1);
		::dup2(fdsStderr[1], 2);
		for (int i = 0; i < 2; i++) {
			::close(fdsStdin[i]);
			::close(fdsStdout[i]);
			::close(fdsStderr[i]);
		}
		::execv("/bin/sh", argv);
		::exit(1);
	}
	fd_set fdsRead;
	for (;;) {
		if (pStreamStdin != nullptr && !pStreamStdin->GetBlocking()) {
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = pStreamStdin->Read(sig, buff, pMemory->GetSize());
			if (sig.IsSignalled()) goto done;
			if (bytesRead == 0) {
				::close(fdsStdin[1]);
			} else {
				::write(fdsStdin[1], buff, bytesRead);
			}
		}
		timeval tv;
		::memset(&tv, 0x00, sizeof(tv));
		tv.tv_sec = 0;
		tv.tv_usec = 100 * 1000;
		FD_ZERO(&fdsRead);
		if (pStreamStdout != nullptr) FD_SET(fdsStdout[0], &fdsRead);
		if (pStreamStderr != nullptr) FD_SET(fdsStderr[0], &fdsRead);
		::select(ChooseMax(fdsStdout[0], fdsStderr[0]) + 1, &fdsRead, nullptr, nullptr, &tv);
		bool idleFlag = true;
		if (FD_ISSET(fdsStdout[0], &fdsRead)) {
			idleFlag = false;
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = ::read(fdsStdout[0], buff, pMemory->GetSize());
			pStreamStdout->Write(buff, bytesRead);
			if (Error::IsIssued()) goto done;
		}
		if (FD_ISSET(fdsStderr[0], &fdsRead)) {
			idleFlag = false;
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = ::read(fdsStderr[0], buff, pMemory->GetSize());
			pStreamStderr->Write(buff, bytesRead);
			if (Error::IsIssued()) goto done;
		}
		if (idleFlag) {
			int status;
			int rtn = waitpid(pid, &status, WNOHANG);
			if (rtn > 0 && WIFEXITED(status)) {
				exitCode = WEXITSTATUS(status);
				break;
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		::close(fdsStdin[i]);	// fdsStdin[1] may already have been closed.
		::close(fdsStdout[i]);
		::close(fdsStderr[i]);
	}
done:
	for (size_t i = 0; i < ArraySizeOf(argv); i++) ::free(argv[i]);
#endif
	return exitCode;
}

//-----------------------------------------------------------------------------
// OAL::DynamicLibrary (POSIX)
//-----------------------------------------------------------------------------
OAL::DynamicLibrary::DynamicLibrary() : _hLibrary(nullptr)
{
}

bool OAL::DynamicLibrary::Open(const char* pathName)
{
	_hLibrary = dlopen(ToNativeString(pathName).c_str(), RTLD_LAZY);
	if (_hLibrary == nullptr) {
		Error::Issue(ErrorType::ImportError, "%s", dlerror());
		return false;
	}
	dlerror(); // clear any existing error
	return true;
}

void* OAL::DynamicLibrary::GetEntry(const char* funcName)
{
	void* pFunc = dlsym(_hLibrary, funcName);
	if (!pFunc) {
		Error::Issue(ErrorType::ImportError, "can't find entry function '%s'", funcName);
		return nullptr;
	}
	return pFunc;
}

#endif

}
