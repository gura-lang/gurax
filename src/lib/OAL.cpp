//==============================================================================
// OAL.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// OAL (common)
//------------------------------------------------------------------------------
bool OAL::ParseStatMode(const char* mode, mode_t& st_mode)
{
	mode_t st_mode_r = 0, st_mode_w = 0, st_mode_x = 0;
	mode_t st_mode_mask = 0;
	enum {
		STAT_Target, STAT_ModeOp, STAT_Mode_Plus, STAT_Mode_Minus,
	} stat = STAT_Target;
	// state machine to parse regular expression: [ugoa]*([-+=]([rwxXst]*|[ugo]))+
	char ch = '\0';
	bool eatNextChar = true;
	for (const char* p = mode; *p != '\0'; ) {
		if (eatNextChar) ch = *p++;
		eatNextChar = true;
		if (stat == STAT_Target) {
			if (ch == 'u') {
				st_mode_r |= S_IRUSR;
				st_mode_w |= S_IWUSR;
				st_mode_x |= S_IXUSR;
				st_mode_mask |= S_IRUSR | S_IWUSR | S_IXUSR;
			} else if (ch == 'g') {
				st_mode_r |= S_IRGRP;
				st_mode_w |= S_IWGRP;
				st_mode_x |= S_IXGRP;
				st_mode_mask |= S_IRGRP | S_IWGRP | S_IXGRP;
			} else if (ch == 'o') {
				st_mode_r |= S_IROTH;
				st_mode_w |= S_IWOTH;
				st_mode_x |= S_IXOTH;
				st_mode_mask |= S_IROTH | S_IWOTH | S_IXOTH;
			} else if (ch == 'a') {
				st_mode_r |= S_IRUSR | S_IRGRP | S_IROTH;
				st_mode_w |= S_IWUSR | S_IWGRP | S_IWOTH;
				st_mode_x |= S_IXUSR | S_IXGRP | S_IXOTH;
				st_mode_mask |=
					S_IRUSR | S_IWUSR | S_IXUSR |
					S_IRGRP | S_IWGRP | S_IXGRP |
					S_IROTH | S_IWOTH | S_IXOTH;
			} else {
				if (st_mode_mask == 0) {
					st_mode_r |= S_IRUSR | S_IRGRP | S_IROTH;
					st_mode_w |= S_IWUSR | S_IWGRP | S_IWOTH;
					st_mode_x |= S_IXUSR | S_IXGRP | S_IXOTH;
					st_mode_mask |=
						S_IRUSR | S_IWUSR | S_IXUSR |
						S_IRGRP | S_IWGRP | S_IXGRP |
						S_IROTH | S_IWOTH | S_IXOTH;
				}
				eatNextChar = false;
				stat = STAT_ModeOp;
			}
		} else if (stat == STAT_ModeOp) {
			if (ch == '+') {
				stat = STAT_Mode_Plus;
			} else if (ch == '-') {
				stat = STAT_Mode_Minus;
			} else if (ch == '=') {
				st_mode &= ~st_mode_mask;
				stat = STAT_Mode_Plus;
			} else {
				return false;
			}
		} else if (stat == STAT_Mode_Plus) {
			if (ch == 'r') {
				st_mode |= st_mode_r;
			} else if (ch == 'w') {
				st_mode |= st_mode_w;
			} else if (ch == 'x') {
				st_mode |= st_mode_x;
			} else {
				eatNextChar = false;
				stat = STAT_ModeOp;
			}
		} else if (stat == STAT_Mode_Minus) {
			if (ch == 'r') {
				st_mode &= ~st_mode_r;
			} else if (ch == 'w') {
				st_mode &= ~st_mode_w;
			} else if (ch == 'x') {
				st_mode &= ~st_mode_x;
			} else {
				eatNextChar = false;
				stat = STAT_ModeOp;
			}
		}
	}
	return true;
}

void OAL::AppendCmdLine(String& cmdLine, const char* arg)
{
	if (::strchr(arg, ' ')) {
		cmdLine += '"';
		cmdLine += arg;
		cmdLine += '"';
	} else {
		cmdLine += arg;
	}
}

DateTime* OAL::CreateDateTime(const struct tm& tm, int secsOffset)
{
	return new DateTime(
		static_cast<Int16>(tm.tm_year) + 1900,
		static_cast<Int8>(tm.tm_mon) + 1,
		static_cast<Int8>(tm.tm_mday),
		DateTime::CalcSecPacked(static_cast<Int8>(tm.tm_hour),
								static_cast<Int8>(tm.tm_min),
								static_cast<Int8>(tm.tm_sec)),
		0, secsOffset);
}

bool OAL::CopyDir(const char* dirNameSrc, const char* dirNameDst)
{
	if (!CreateDirTree(dirNameDst)) return false;
	DirLister dirLister(dirNameSrc, false);
	bool dirFlag = false;
	String fileName;
	while (dirLister.Next(nullptr, fileName, &dirFlag)) {
		if (dirFlag) continue;
		String pathNameSrc = PathName(dirNameSrc).JoinAfter(fileName.c_str());
		String pathNameDst = PathName(dirNameDst).JoinAfter(fileName.c_str());
		if (!Copy(pathNameSrc.c_str(), pathNameDst.c_str(), false, false)) return false;
	}
	return true;
}

bool OAL::CopyDirTree(const char* dirNameSrc, const char* dirNameDst)
{
	std::list<String> relNames;
	relNames.push_back("");
	for (const String& relNameIter : relNames) {
		String dirNameIterSrc = PathName(dirNameSrc).JoinAfter(relNameIter.c_str());
		String dirNameIterDst = PathName(dirNameDst).JoinAfter(relNameIter.c_str());
		if (!CreateDirTree(dirNameIterDst.c_str())) return false;
		DirLister dirLister(dirNameIterSrc.c_str(), false);
		bool dirFlag = false;
		String fileName;
		while (dirLister.Next(nullptr, fileName, &dirFlag)) {
			if (dirFlag) {
				String relName = PathName(relNameIter).JoinAfter(fileName.c_str());
				relNames.push_back(relName);
				continue;
			}
			String pathNameSrc = PathName(dirNameIterSrc).JoinAfter(fileName.c_str());
			String pathNameDst = PathName(dirNameIterDst).JoinAfter(fileName.c_str());
			if (!Copy(pathNameSrc.c_str(), pathNameDst.c_str(), false, false)) return false;
		}
	}
	return true;
}

bool OAL::CreateDirTree(const char* dirName)
{
	bool existFlag = false;
	if (IsDir(dirName, &existFlag)) return true;
	if (existFlag) return false;
	StringList dirNames;
	dirNames.push_back(dirName);
	String dirNameParent = PathName(dirName).ExtractHeadName();
	while (!dirNameParent.empty()) {
		if (IsDir(dirNameParent.c_str(), &existFlag)) break;
		if (existFlag) return false;
		dirNames.push_back(dirNameParent);
		dirNameParent = PathName(dirNameParent).ExtractHeadName();
	}
	for (auto pDirName = dirNames.rbegin(); pDirName != dirNames.rend(); pDirName++) {
		const String &dirName = *pDirName;
		if (!CreateDir(dirName.c_str())) return false;
	}
	return true;
}

bool OAL::RemoveDirTree(const char* dirName)
{
	bool rtn = true;
	std::list<String> dirNames;
	dirNames.push_back(dirName);
	for (const String& dirNameIter : dirNames) {
		DirLister dirLister(dirNameIter.c_str());
		bool dirFlag = false;
		String pathName;
		while (dirLister.Next(nullptr, pathName, &dirFlag)) {
			if (dirFlag) dirNames.push_back(pathName);
		}
	}
	for (auto pDirNameIter = dirNames.rbegin(); pDirNameIter != dirNames.rend(); pDirNameIter++) {
		const char *dirNameIter = pDirNameIter->c_str();
		DirLister dirLister(dirNameIter);
		bool dirFlag = false;
		String pathName;
		while (dirLister.Next(nullptr, pathName, &dirFlag)) {
			if (dirFlag) {
				// nothing to do
			} else if (!Remove(pathName.c_str())) {
				ChangeMode("u+w", pathName.c_str(), false);
				if (!Remove(pathName.c_str())) rtn = false;
			}
		}
		if (!RemoveDir(dirNameIter)) {
			ChangeMode("u+w", dirNameIter, false);
			if (!RemoveDir(dirNameIter)) rtn = false;
		}
	}
	return rtn;
}

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// OAL (MSWIN)
//------------------------------------------------------------------------------
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

bool OAL::ChangeDir(const char* pathName)
{
	return false;
}

bool OAL::ChangeMode(const char* pathName, mode_t mode, bool followLinkFlag)
{
	return false;
}

bool OAL::ChangeMode(const char* pathName, const char* mode, bool followLinkFlag)
{
	return false;
}

bool OAL::Copy(const char* pathNameSrc, const char* pathNameDst, bool failIfExistFlag, bool followLinkFlag)
{
	return false;
}

bool OAL::CreateDir(const char* dirName)
{
	return ::CreateDirectory(ToNativeString(dirName).c_str(), nullptr)? true : false;
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

bool OAL::IsDir(const char* pathName, bool* pExistFlag)
{
	WIN32_FILE_ATTRIBUTE_DATA attrData;
	bool existFlag = (::GetFileAttributesEx(ToNativeString(pathName).c_str(),
											GetFileExInfoStandard, &attrData) != 0);
	if (pExistFlag != nullptr) *pExistFlag = existFlag;
	if (!existFlag) return false;
	return (attrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

bool OAL::Remove(const char* pathName)
{
	return false;
}

bool OAL::RemoveDir(const char* dirName)
{
	return false;
}

bool OAL::Rename(const char* pathNameOld, const char* pathNameNew)
{
	return false;
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

DateTime* OAL::CreateDateTime(time_t t, bool utcFlag)
{
	struct tm tm;
	int secsOffset = 0;
	if (utcFlag) {
		gmtime_s(&tm, &t);
	} else {
		localtime_s(&tm, &t);
		secsOffset = GetSecsOffsetTZ();
	}
	return CreateDateTime(tm, secsOffset);
}

DateTime* OAL::CreateDateTime(const SYSTEMTIME& st, int secsOffset)
{
	return nullptr;
}

DateTime* OAL::CreateDateTime(const FILETIME& ft, bool utcFlag)
{
	return nullptr;
}

SYSTEMTIME OAL::DateTimeToSYSTEMTIME(const DateTime& dt)
{
	SYSTEMTIME st;
	st.wYear			= dt.GetYear();
	st.wMonth			= dt.GetMonth();
	st.wDayOfWeek		= dt.GetDayOfWeek();
	st.wDay				= dt.GetDay();
	st.wHour			= dt.GetHour();
	st.wMinute			= dt.GetMin();
	st.wSecond			= dt.GetSec();
	st.wMilliseconds	= static_cast<WORD>(dt.GetUSec() / 1000);
	return st;
}

FILETIME OAL::DateTimeToFILETIME(const DateTime& dt)
{
	SYSTEMTIME st = ToSYSTEMTIME(dt);
	FILETIME ftLocal, ft;
	::SystemTimeToFileTime(&st, &ftLocal);
	::LocalFileTimeToFileTime(&ftLocal, &ft);
	return ft;
}

String OAL::ConvCodePage(const char* str, UINT codePageSrc, UINT codePageDst)
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

//-----------------------------------------------------------------------------
// OAL::DirLister (MSWIN)
//-----------------------------------------------------------------------------
OAL::DirLister::DirLister(const char* dirName, bool joinPathNameFlag) :
	_dirName(dirName), _joinPathNameFlag(joinPathNameFlag), _hFind(INVALID_HANDLE_VALUE)
{
}

OAL::DirLister::~DirLister()
{
	::FindClose(_hFind);
}

bool OAL::DirLister::Next(const char* pattern, String& pathName, bool* pDirFlag)
{
	WIN32_FIND_DATA findData;
	pathName.clear();
	String fileName;
	for (;;) {
		if (_hFind == INVALID_HANDLE_VALUE) {
			String pattern = JoinPathName(_dirName.c_str(), "*.*");
			_hFind = ::FindFirstFile(ToNativeString(pattern.c_str()).c_str(), &findData);
			if (_hFind == INVALID_HANDLE_VALUE) return false;
		} else {
			if (!::FindNextFile(_hFind, &findData)) return false;
		}
		fileName = FromNativeString(findData.cFileName);
		if (fileName != "." && fileName != ".." &&
			(!pattern || PathName(fileName).DoesMatch(pattern))) break;
	}
	if (_joinPathNameFlag) {
		pathName = JoinPathName(_dirName.c_str(), fileName.c_str());
	} else {
		pathName = fileName;
	}
	*pDirFlag = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? true : false;
	return true;
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
	if (!str) {
		if (pFoundFlag) *pFoundFlag = false;
		return String("");
	}
	if (pFoundFlag) *pFoundFlag = true;
	return FromNativeString(str);
}

void OAL::PutEnv(const char* name, const char* value)
{
	int overwrite = 1;
	::setenv(ToNativeString(name).c_str(), ToNativeString(value).c_str(), overwrite);
}

String OAL::ToNativeString(const char* str)
{
	return str;
}

String OAL::FromNativeString(const char* str)
{
	return str;
}

bool OAL::ChangeDir(const char* pathName)
{
	return ::chdir(ToNativeString(pathName).c_str()) == 0;
}

bool OAL::ChangeMode(const char* pathName, mode_t mode, bool followLinkFlag)
{
	return followLinkFlag?
		::chmod(ToNativeString(pathName).c_str(), mode) == 0 :
		lchmod(ToNativeString(pathName).c_str(), mode) == 0;
}

bool OAL::ChangeMode(const char* pathName, const char* mode, bool followLinkFlag)
{
	String pathNameEnc = ToNativeString(pathName);
	mode_t st_mode = 0;
	do {
		struct stat statFs;
		if (followLinkFlag) {
			if (::stat(pathNameEnc.c_str(), &statFs) < 0) return false;
		} else {
			if (::lstat(pathNameEnc.c_str(), &statFs) < 0) return false;
		}
		st_mode = statFs.st_mode;
	} while (0);
	if (!ParseStatMode(mode, st_mode)) return false;
	return followLinkFlag?
		::chmod(pathNameEnc.c_str(), st_mode) == 0 :
		lchmod(pathNameEnc.c_str(), st_mode) == 0;
}

bool OAL::Copy(const char* pathNameSrc, const char* pathNameDst, bool failIfExistFlag, bool followLinkFlag)
{
	struct stat statSrc, statDst;
	String pathNameSrcN = ToNativeString(pathNameSrc);
	String pathNameTmp = IsDir(pathNameDst)?
		PathName(pathNameDst).JoinAfter(PathName(pathNameSrc).ExtractFileName().c_str()) : pathNameDst;
	String pathNameDstN = ToNativeString(pathNameTmp.c_str());
	if (followLinkFlag) {
		if (::stat(pathNameSrcN.c_str(), &statSrc) < 0) return false;
	} else {
		if (::lstat(pathNameSrcN.c_str(), &statSrc) < 0) return false;
	}
	if (S_ISREG(statSrc.st_mode)) {
		if (::stat(pathNameDstN.c_str(), &statDst) < 0) {
			// nothing to do
		} else if (failIfExistFlag) {
			return false;
		} else if (!Remove(pathNameTmp.c_str())) {
			//ChangeMode("u+w", pathNameTmp.c_str());
			//if (!Remove(pathNameTmp.c_str())) return false;
			return false;
		}
		FDCloser fdSrc(::open(pathNameSrcN.c_str(), O_RDONLY));
		if (fdSrc.get() < 0) return false;
		FDCloser fdDst(::open(pathNameDstN.c_str(), O_WRONLY | O_CREAT | O_TRUNC, statSrc.st_mode));
		if (fdDst.get() < 0) return false;
		size_t bytesSrc = statSrc.st_size;
		MemoryUnmapper memSrc(::mmap(nullptr, bytesSrc, PROT_READ, MAP_PRIVATE, fdSrc.get(), 0), bytesSrc);
		if (memSrc.get() == MAP_FAILED) {
			RefPtr<Memory> pMemory(new MemoryHeap(65536));
			for (;;) {
				int bytesRead = ::read(fdSrc.get(), pMemory->GetPointer(), pMemory->GetSize());
				if (bytesRead == 0) break;
				if (::write(fdDst.get(), pMemory->GetPointer(), bytesRead) < bytesRead) return false;
			}
		} else {
			if (::write(fdDst.get(), memSrc.get(), bytesSrc) < static_cast<int>(bytesSrc)) {
				return false;
			}
		}
		return true;
	} else if (S_ISDIR(statSrc.st_mode)) {
		// nothing to do
	} else if (S_ISCHR(statSrc.st_mode)) {
		// nothing to do
	} else if (S_ISBLK(statSrc.st_mode)) {
		// nothing to do
	} else if (S_ISFIFO(statSrc.st_mode)) {
		// nothing to do
	} else if (S_ISLNK(statSrc.st_mode)) {
		// still buggy
		if (::stat(pathNameDstN.c_str(), &statDst) < 0) {
			// nothing to do
		} else if (failIfExistFlag) {
			return false;
		} else if (!Remove(pathNameTmp.c_str())) {
			//ChangeMode("u+w", pathNameTmp.c_str());
			//if (!Remove(pathNameTmp.c_str())) return false;
			return false;
		}
		char *tgt = new char [statSrc.st_size];
		if (::readlink(pathNameSrcN.c_str(), tgt, statSrc.st_size) < 0) return false;
		if (::symlink(tgt, pathNameDstN.c_str()) < 0) return false;
		delete[] tgt;
		return true;
	} else if (S_ISSOCK(statSrc.st_mode)) {
		// nothing to do
	}
	return false;
}

bool OAL::CreateDir(const char* dirName)
{
	return ::mkdir(ToNativeString(dirName).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

bool OAL::IsDir(const char* pathName, bool* pExistFlag)
{
	struct stat stat;
	bool existFlag = (::stat(ToNativeString(pathName).c_str(), &stat) == 0);
	if (pExistFlag != nullptr) *pExistFlag = existFlag;
	if (!existFlag) return false;
	return S_ISDIR(stat.st_mode);
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

bool OAL::Remove(const char* pathName)
{
	return ::unlink(ToNativeString(pathName).c_str()) == 0;
}

bool OAL::RemoveDir(const char* dirName)
{
	return ::rmdir(ToNativeString(dirName).c_str()) == 0;
}

bool OAL::Rename(const char* pathNameOld, const char* pathNameNew)
{
	return ::rename(ToNativeString(pathNameOld).c_str(), ToNativeString(pathNameNew).c_str()) == 0;
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

DateTime* OAL::CreateDateTime(time_t t, bool utcFlag)
{
	struct tm tm;
	int secsOffset = 0;
	if (utcFlag) {
		gmtime_r(&t, &tm);
	} else {
		localtime_r(&t, &tm);
		//secsOffset = GetSecsOffsetTZ();
		secsOffset = 0;
	}
	return CreateDateTime(tm, secsOffset);
}

//-----------------------------------------------------------------------------
// OAL::DirLister (POSIX)
//-----------------------------------------------------------------------------
OAL::DirLister::DirLister(const char* dirName, bool joinPathNameFlag) :
	_dirName(dirName), _dirp(nullptr), _joinPathNameFlag(joinPathNameFlag)
{
}

OAL::DirLister::~DirLister()
{
	if (_dirp) ::closedir(_dirp);
}

bool OAL::DirLister::Next(const char* pattern, String& pathName, bool* pDirFlag)
{
	struct dirent* direntp = nullptr;
	pathName.clear();
	String fileName;
	for (;;) {
		if (!_dirp) {
			_dirp = ::opendir(_dirName.empty()? "." : _dirName.c_str());
			if (!_dirp) return false;
		}
		direntp = ::readdir(_dirp);
		if (!direntp) return false;
		fileName = FromNativeString(direntp->d_name);
		if (fileName != "." && fileName != ".." &&
			(!pattern || PathName(fileName).DoesMatch(pattern))) break;
	}
	if (_joinPathNameFlag) {
		pathName = PathName(_dirName).JoinAfter(fileName.c_str());
	} else {
		pathName = fileName;
	}
	*pDirFlag = (direntp->d_type == DT_DIR);
	return true;
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
	if (!_hLibrary) {
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
