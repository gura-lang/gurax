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

void AppendCmdLine(String& cmdLine, const char* arg)
{
	if (::strchr(arg, ' ')) {
		cmdLine += '"';
		cmdLine += arg;
		cmdLine += '"';
	} else {
		cmdLine += arg;
	}
}

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

void OAL::PutEnv(const char* name, const char* value)
{
	::SetEnvironmentVariable(ToNativeString(name).c_str(), ToNativeString(value).c_str());
}

String OAL::GetEnv(const char* name, bool* pFoundFlag)
{
	String nameEnc = ToNativeString(name);
	DWORD len = ::GetEnvironmentVariable(nameEnc.c_str(), nullptr, 0);
	if (len == 0) {
		if (pFoundFlag != nullptr) *pFoundFlag = false;
		return String("");
	}
	char* buff = new char [len];
	::GetEnvironmentVariable(nameEnc.c_str(), buff, len);
	String rtn(FromNativeString(buff));
	delete[] buff;
	if (pFoundFlag != nullptr) *pFoundFlag = true;
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

Double OAL::GetTickTime()
{
	LARGE_INTEGER freq, counter;
	if (::QueryPerformanceFrequency(&freq) && ::QueryPerformanceCounter(&counter)) {
		return static_cast<Double>(counter.QuadPart) / freq.QuadPart;
	} else {
		return static_cast<Double>(::GetTickCount()) / 1000;
	}
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
String OAL::GetEnv(const char* name, bool* pFoundFlag)
{
	const char* str = ::getenv(ToNativeString(name).c_str());
	if (str == nullptr) {
		if (pFoundFlag != nullptr) *pFoundFlag = false;
		return String("");
	}
	if (pFoundFlag != nullptr) *pFoundFlag = true;
	return FromNativeString(str);
}

void OAL::PutEnv(const char* name, const char* value)
{
	int overwrite = 1;
	::setenv(ToNativeString(name).c_str(), ToNativeString(value).c_str(), overwrite);
}

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
	//struct stat stat;
	//if (::stat(ToNativeString(pathName).c_str(), &stat) != 0) return false;
	//return S_ISDIR(stat.st_mode);
	return false;
}

bool OAL::DoesExistFile(const char* pathName)
{
	//struct stat stat;
	//if (::stat(ToNativeString(pathName).c_str(), &stat) != 0) return false;
	//return S_ISREG(stat.st_mode);
	return false;
}

int OAL::ExecProgram(
	const char* pathName, StringPicker&& args,
	Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag)
{
	int exitCode = 0;
	pid_t pid = 0;
	RefPtr<Memory> pMemory(new MemoryHeap(32768));
	std::array<char*, 4> argv;
	argv[0] = ::strdup("/bin/sh");
	argv[1] = ::strdup("-c");
	String cmdLine;
	cmdLine = ToNativeString(pathName);
	while (const char* arg = args.Pick()) {
		cmdLine += " ";
		AppendCmdLine(cmdLine, ToNativeString(arg).c_str());
	}
	argv[2] = ::strdup(cmdLine.c_str());
	argv[3] = nullptr;
	if (forkFlag) {
		pid_t pid = ::fork();
		if (pid == 0) {
			::execv("/bin/sh", argv.data());
			::exit(1);
		}
		goto done;
	}
	int fdsCIn[2];
	int fdsCOut[2];
	int fdsCErr[2];
	if (::pipe(fdsCIn) < 0 || ::pipe(fdsCOut) < 0 || ::pipe(fdsCErr) < 0) {
		Error::Issue(ErrorType::IOError, "failed to create pipes");
		goto done;
	}
	pid = ::fork();
	if (pid == 0) {
		::dup2(fdsCIn[0], 0);
		::dup2(fdsCOut[1], 1);
		::dup2(fdsCErr[1], 2);
		for (int i = 0; i < 2; i++) {
			::close(fdsCIn[i]);
			::close(fdsCOut[i]);
			::close(fdsCErr[i]);
		}
		::execv("/bin/sh", argv.data());
		::exit(1);
	}
	fd_set fdsRead;
	for (;;) {
#if 0
		if (pStreamCIn && !pStreamCIn->GetBlocking()) {
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = pStreamCIn->Read(sig, buff, pMemory->GetSize());
			if (sig.IsSignalled()) goto done;
			if (bytesRead == 0) {
				::close(fdsCIn[1]);
			} else {
				::write(fdsCIn[1], buff, bytesRead);
			}
		}
#endif
		timeval tv;
		::memset(&tv, 0x00, sizeof(tv));
		tv.tv_sec = 0;
		tv.tv_usec = 100 * 1000;
		FD_ZERO(&fdsRead);
		if (pStreamCOut) FD_SET(fdsCOut[0], &fdsRead);
		if (pStreamCErr) FD_SET(fdsCErr[0], &fdsRead);
		::select(std::max(fdsCOut[0], fdsCErr[0]) + 1, &fdsRead, nullptr, nullptr, &tv);
		bool idleFlag = true;
		if (FD_ISSET(fdsCOut[0], &fdsRead)) {
			idleFlag = false;
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = ::read(fdsCOut[0], buff, pMemory->GetSize());
			pStreamCOut->Write(buff, bytesRead);
			if (Error::IsIssued()) goto done;
		}
		if (FD_ISSET(fdsCErr[0], &fdsRead)) {
			idleFlag = false;
			char* buff = reinterpret_cast<char*>(pMemory->GetPointer());
			size_t bytesRead = ::read(fdsCErr[0], buff, pMemory->GetSize());
			pStreamCErr->Write(buff, bytesRead);
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
		::close(fdsCIn[i]);	// fdsCIn[1] may already have been closed.
		::close(fdsCOut[i]);
		::close(fdsCErr[i]);
	}
done:
	for (char* arg : argv) ::free(arg);
	return exitCode;
}

Double OAL::GetTickTime()
{
	timeval tv;
	struct timezone tz;
	::gettimeofday(&tv, &tz);
	Double num = tv.tv_sec;
	num += static_cast<Double>(tv.tv_usec) / 1000000;
	return num;
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
