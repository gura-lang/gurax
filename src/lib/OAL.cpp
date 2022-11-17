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
	enum class Stat { Target, ModeOp, Mode_Plus, Mode_Minus } stat = Stat::Target;
	// state machine to parse regular expression: [ugoa]*([-+=]([rwxXst]*|[ugo]))+
	char ch = '\0';
	bool eatNextChar = true;
	for (const char* p = mode; *p != '\0'; ) {
		if (eatNextChar) ch = *p++;
		eatNextChar = true;
		if (stat == Stat::Target) {
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
				stat = Stat::ModeOp;
			}
		} else if (stat == Stat::ModeOp) {
			if (ch == '+') {
				stat = Stat::Mode_Plus;
			} else if (ch == '-') {
				stat = Stat::Mode_Minus;
			} else if (ch == '=') {
				st_mode &= ~st_mode_mask;
				stat = Stat::Mode_Plus;
			} else {
				return false;
			}
		} else if (stat == Stat::Mode_Plus) {
			if (ch == 'r') {
				st_mode |= st_mode_r;
			} else if (ch == 'w') {
				st_mode |= st_mode_w;
			} else if (ch == 'x') {
				st_mode |= st_mode_x;
			} else {
				eatNextChar = false;
				stat = Stat::ModeOp;
			}
		} else if (stat == Stat::Mode_Minus) {
			if (ch == 'r') {
				st_mode &= ~st_mode_r;
			} else if (ch == 'w') {
				st_mode &= ~st_mode_w;
			} else if (ch == 'x') {
				st_mode &= ~st_mode_x;
			} else {
				eatNextChar = false;
				stat = Stat::ModeOp;
			}
		}
	}
	return true;
}

void OAL::AppendCmdLine(String& cmdLine, const char* arg)
{
	if (::strchr(arg, ' ') && !::strchr(arg, '"')) {
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

bool OAL::PrepareLocalDir()
{
	String dirName = GetDirName_Local();
	if (CreateDirTree(dirName.c_str()) &&
		CreateDir(PathName(dirName).JoinAfter("module").c_str()) &&
		CreateDir(PathName(dirName).JoinAfter("application").c_str()) &&
		CreateDir(PathName(dirName).JoinAfter("config").c_str()) &&
		CreateDir(PathName(dirName).JoinAfter("work").c_str())) return true;
	Error::Issue(ErrorType::IOError, "failed to create local directory");
	return false;
}

//-----------------------------------------------------------------------------
// Path Information (MSWIN/DARWIN/LINUX/Others)
//-----------------------------------------------------------------------------
String OAL::GetDirName_Base()
{
	bool foundFlag;
	String dirNameBase = GetEnv("GURAX_DIRBASE", &foundFlag);
	if (!foundFlag) {
		String pathName = GetPathName_Executable();
		FollowLink(pathName);
		pathName = PathName(pathName).ExtractDirName();
		dirNameBase = PathName(pathName).ExtractHeadName();
	}
	return dirNameBase;
}

String OAL::GetDirName_Executable()
{
	return PathName(GetPathName_Executable()).ExtractDirName();
}

String OAL::GetDirName_Data()
{
#if defined(GURAX_ON_MSWIN)
	return GetDirName_Base();
#else
	return PathName(GetDirName_Base()).JoinAfter("share/gurax/" GURAX_VERSION);
#endif
}

String OAL::GetDirName_Module()
{
#if defined(GURAX_ON_MSWIN)
	return PathName(GetDirName_Base()).JoinAfter("module");
#else
	return PathName(GetDirName_Base()).JoinAfter("lib/gurax/" GURAX_VERSION "/module");
#endif
}

String OAL::GetDirName_Include()
{
#if defined(GURAX_ON_MSWIN)
	return PathName(GetDirName_Base()).JoinAfter("include");
#else
	return PathName(GetDirName_Base()).JoinAfter("include/gurax/" GURAX_VERSION);
#endif
}

String OAL::GetDirName_Library()
{
	return PathName(GetDirName_Base()).JoinAfter("lib");
}

String OAL::GetDirName_Font()
{
	return PathName(GetDirName_Data()).JoinAfter("font");
}

String OAL::GetDirName_Script()
{
	return PathName(GetDirName_Data()).JoinAfter("script");
}
	
String OAL::GetDirName_Local()
{
#if defined(GURAX_ON_MSWIN)
	char dirNameN[MAX_PATH];
	::SHGetSpecialFolderPath(nullptr, dirNameN, CSIDL_LOCAL_APPDATA, FALSE);
	String dirName = FromNativeString(dirNameN);
	dirName += "\\Gura\\";
	dirName += Version::GetVersion();
	return dirName;
#else
	String dirName = FromNativeString(GetEnv("HOME").c_str());
	dirName += "/.gurax/";
	dirName += Version::GetVersion();
	return dirName;
#endif
}

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// OAL (MSWIN)
//------------------------------------------------------------------------------
const char OAL::SepPathList = ';';

String OAL::GetPathName_Executable()
{
	char pathName[MAX_PATH];
	::GetModuleFileName(nullptr, pathName, MAX_PATH); // Win32 API
	return FromNativeString(pathName);
}

String OAL::GetEnv(const char* name, bool* pFoundFlag)
{
	String nameEnc = ToNativeString(name);
	DWORD len = ::GetEnvironmentVariable(nameEnc.c_str(), nullptr, 0);
	if (len == 0) {
		if (pFoundFlag != nullptr) *pFoundFlag = false;
		return String("");
	}
	char* buff = new char[len];
	::GetEnvironmentVariable(nameEnc.c_str(), buff, len);
	String rtn(FromNativeString(buff));
	delete[] buff;
	if (pFoundFlag != nullptr) *pFoundFlag = true;
	return rtn;
}

void OAL::PutEnv(const char* name, const char* value)
{
	::SetEnvironmentVariable(ToNativeString(name).c_str(), ToNativeString(value).c_str());
}

const char* OAL::GetEncodingForConsole()
{
	UINT codePage = ::GetConsoleOutputCP();
	if (codePage == 0) codePage = ::GetACP();
	return
		(codePage == 1252)?		"iso-8859-1" :
		(codePage == 28592)?	"iso-8859-2" :
		(codePage == 1255)?		"iso-8859-8" :
		(codePage == 932)?		"shift_jis" :
		(codePage == 936)?		"gbk" :
		(codePage == 949)?		"euc-kr" :
		(codePage == 950)?		"big5" :
		(codePage == 65001)?	"utf-8" :
		"iso-8859-1";
}

const Symbol *GetLangCode()
{
	// http://www.loc.gov/standards/iso639-2/php/code_list.php
	UINT codePage = ::GetConsoleOutputCP();
	if (codePage == 0) codePage = ::GetACP();
	return
		(codePage == 1252)?		Gurax_Symbol(en) :
		(codePage == 28592)?	Gurax_Symbol(en) :
		(codePage == 1255)?		Gurax_Symbol(en) :
		(codePage == 932)?		Gurax_Symbol(ja) :
		(codePage == 936)?		Gurax_Symbol(zh) :
		(codePage == 949)?		Gurax_Symbol(ko) :
		(codePage == 950)?		Gurax_Symbol(zh) :
		Gurax_Symbol(en);
}

String OAL::ToNativeString(const char* str)
{
	return ConvCodePage(str, CP_UTF8, CP_THREAD_ACP);
}

String OAL::FromNativeString(const char* str)
{
	return ConvCodePage(str, CP_THREAD_ACP, CP_UTF8);
}

bool OAL::ChangeDir(const char* dirName)
{
	return ::SetCurrentDirectory(ToNativeString(dirName).c_str())? true : false;
}

bool OAL::ChangeMode(const char* pathName, mode_t mode, bool followLinkFlag)
{
	// nothing to do
	return true;
}

bool OAL::ChangeMode(const char* pathName, const char* mode, bool followLinkFlag)
{
	// nothing to do
	return true;
}

bool OAL::Copy(const char* pathNameSrc, const char* pathNameDst, bool failIfExistFlag, bool followLinkFlag)
{
	String pathNameSrcN = ToNativeString(pathNameSrc);
	String pathNameDstN;
	if (IsDir(pathNameDst, nullptr)) {
		String fileName = PathName(pathNameSrc).ExtractFileName();
		pathNameDstN = ToNativeString(PathName(pathNameDst).JoinAfter(fileName.c_str()).c_str());
	}
	else {
		pathNameDstN = ToNativeString(pathNameDst);
	}
	return ::CopyFile(pathNameSrcN.c_str(), pathNameDstN.c_str(), failIfExistFlag) ? true : false;
}

bool OAL::CreateLink(const char* pathNameSrc, const char* pathNameDst)
{
	// nothing to do
	return true;
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
	return ::DeleteFile(ToNativeString(pathName).c_str())? true : false;
}

bool OAL::RemoveDir(const char* dirName)
{
	return ::RemoveDirectory(ToNativeString(dirName).c_str())? true : false;
}

bool OAL::Rename(const char* pathNameOld, const char* pathNameNew)
{
	return ::MoveFileEx(ToNativeString(pathNameOld).c_str(), ToNativeString(pathNameNew).c_str(),
		MOVEFILE_REPLACE_EXISTING)? true : false;
}

void OAL::Sleep(Double secs)
{
	::Sleep(static_cast<long>(secs * 1000));	// unit: msec
}

OAL::FileType OAL::GetFileType(const char* pathName)
{
	WIN32_FILE_ATTRIBUTE_DATA attrData;
	if (::GetFileAttributesEx(ToNativeString(pathName).c_str(),
							  GetFileExInfoStandard, &attrData) == 0) return FileType::None;
	return ((attrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)?
		FileType::Directory : FileType::Normal;
}

int OAL::ExecProgram(
	const char* pathName, StringPicker&& args,
	Stream* pStreamCIn, Stream* pStreamCOut, Stream* pStreamCErr, bool forkFlag)
{
	String cmdLine;
	AppendCmdLine(cmdLine, ToNativeString(pathName).c_str());
	while (const char* arg = args.Pick()) {
		cmdLine += " ";
		AppendCmdLine(cmdLine, ToNativeString(arg).c_str());
	}
	if (forkFlag) {
		STARTUPINFO si;
		PROCESS_INFORMATION ps;
		::memset(&si, 0x00, sizeof(si));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags = STARTF_USESTDHANDLES;
		si.hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
		si.hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
		si.hStdError = ::GetStdHandle(STD_ERROR_HANDLE);
		BOOL rtn = ::CreateProcess(nullptr, const_cast<char*>(cmdLine.c_str()),
			nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &ps);
		if (!rtn) {
			Error::Issue(ErrorType::IOError, "failed to execute %s", pathName);
			return -1;
		}
		return 0;
	}
	HANDLE hStdout = INVALID_HANDLE_VALUE;
	HANDLE hStderr = INVALID_HANDLE_VALUE;
	HANDLE hStdoutWatch = INVALID_HANDLE_VALUE;
	HANDLE hStderrWatch = INVALID_HANDLE_VALUE;
	do {
		SECURITY_ATTRIBUTES sa;
		::memset(&sa, 0x00, sizeof(sa));
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = nullptr;
		sa.bInheritHandle = TRUE;
		if (pStreamCOut && !::CreatePipe(&hStdoutWatch, &hStdout, &sa, 0)) {
			Error::Issue(ErrorType::IOError, "failed to create a pipe");
			return -1;
		}
		if (pStreamCErr && !::CreatePipe(&hStderrWatch, &hStderr, &sa, 0)) {
			Error::Issue(ErrorType::IOError, "failed to create a pipe");
			return -1;
		}
	} while (0);
	STARTUPINFO si;
	PROCESS_INFORMATION ps;
	::memset(&si, 0x00, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput = hStdout;
	si.hStdError = hStderr;
	BOOL rtn = ::CreateProcess(nullptr, const_cast<char*>(cmdLine.c_str()),
		nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &ps);
	if (!rtn) {
		Error::Issue(ErrorType::IOError, "failed to execute %s", pathName);
		return -1;
	}
	::WaitForInputIdle(ps.hProcess, INFINITE);
	RefPtr<Memory> pMemory(new MemoryHeap(32768));
	DWORD exitCode = 0;
	for (;;) {
		bool dataAvailFlag = false;
		if (pStreamCOut) {
			DWORD bytesAvail;
			::PeekNamedPipe(hStdoutWatch, nullptr, 0, nullptr, &bytesAvail, nullptr);
			if (bytesAvail > 0) {
				dataAvailFlag = true;
				char* buff = pMemory->GetPointerC<char>();
				DWORD bytesRead;
				::ReadFile(hStdoutWatch, buff,
					static_cast<DWORD>(pMemory->GetBytes()), &bytesRead, nullptr);
				pStreamCOut->Write(buff, bytesRead);
			}
		}
		if (pStreamCErr) {
			DWORD bytesAvail;
			::PeekNamedPipe(hStderrWatch, nullptr, 0, nullptr, &bytesAvail, nullptr);
			if (bytesAvail > 0) {
				dataAvailFlag = true;
				char* buff = pMemory->GetPointerC<char>();
				DWORD bytesRead;
				::ReadFile(hStderrWatch, buff,
					static_cast<DWORD>(pMemory->GetBytes()), &bytesRead, nullptr);
				pStreamCErr->Write(buff, bytesRead);
			}
		}
		if (!dataAvailFlag) {
			::GetExitCodeProcess(ps.hProcess, &exitCode);
			if (exitCode != STILL_ACTIVE) break;
			::Sleep(100);
		}
	}
	::CloseHandle(ps.hProcess);
	::CloseHandle(ps.hThread);
	::CloseHandle(hStdout);
	::CloseHandle(hStderr);
	::CloseHandle(hStdoutWatch);
	::CloseHandle(hStderrWatch);
	return static_cast<int>(exitCode);

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
	return new DateTime(
		static_cast<short>(st.wYear),
		static_cast<char>(st.wMonth),
		static_cast<char>(st.wDay),
		static_cast<long>(st.wHour) * 3600 +
		static_cast<long>(st.wMinute) * 60 + st.wSecond,
		static_cast<long>(st.wMilliseconds) * 1000, secsOffset);
}

DateTime* OAL::CreateDateTime(const FILETIME& ft, bool utcFlag)
{
	SYSTEMTIME stUTC;
	::FileTimeToSystemTime(&ft, &stUTC);
	if (!utcFlag) {
		SYSTEMTIME stLocal;
		::SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);
		return CreateDateTime(stLocal, GetSecsOffsetTZ());
	}
	return CreateDateTime(stUTC, 0);
}

DateTime* OAL::CreateDateTimeCur(bool utcFlag)
{
	SYSTEMTIME st;
	if (utcFlag) {
		::GetSystemTime(&st);
		return CreateDateTime(st, 0);
	} else {
		::GetLocalTime(&st);
		return CreateDateTime(st, GetSecsOffsetTZ());
	}
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
	SYSTEMTIME st = DateTimeToSYSTEMTIME(dt);
	FILETIME ftLocal, ft;
	::SystemTimeToFileTime(&st, &ftLocal);
	::LocalFileTimeToFileTime(&ftLocal, &ft);
	return ft;
}

int OAL::GetSecsOffsetTZ()
{
	TIME_ZONE_INFORMATION tzInfo;
	if (::GetTimeZoneInformation(&tzInfo) == TIME_ZONE_ID_INVALID) return 0;
	return -tzInfo.Bias * 60;
}

bool OAL::FollowLink(String& pathName)
{
	// nothing to do
	return true;
}

String OAL::ConvCodePage(const char* str, UINT codePageSrc, UINT codePageDst)
{
	int cchWideChar = ::MultiByteToWideChar(codePageSrc, 0, str, -1, nullptr, 0);
	std::unique_ptr<WCHAR []> wcharBuff(new WCHAR [static_cast<size_t>(cchWideChar) + 1]);
	::MultiByteToWideChar(codePageSrc, 0, str, -1, wcharBuff.get(), cchWideChar);
	int cchMultiByte = ::WideCharToMultiByte(codePageDst, 0,
				wcharBuff.get(), cchWideChar, nullptr, 0, nullptr, nullptr);
	std::unique_ptr<char []> charBuff(new char [static_cast<size_t>(cchMultiByte) + 1]);
	::WideCharToMultiByte(codePageDst, 0,
				wcharBuff.get(), cchWideChar, charBuff.get(), cchMultiByte, nullptr, nullptr);
	charBuff[cchMultiByte] = '\0';
	return String(charBuff.get()); // don't use String(charBuff, cchMultiByte) here!
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
			String pattern; // = JoinPathName(_dirName.c_str(), "*.*");
			_hFind = ::FindFirstFile(ToNativeString(pattern.c_str()).c_str(), &findData);
			if (_hFind == INVALID_HANDLE_VALUE) return false;
		} else {
			if (!::FindNextFile(_hFind, &findData)) return false;
		}
		fileName = FromNativeString(findData.cFileName);
		if (fileName != "." && fileName != ".." &&
			(!pattern || PathName(fileName).DoesMatchPattern(pattern))) break;
	}
	if (_joinPathNameFlag) {
		//pathName = JoinPathName(_dirName.c_str(), fileName.c_str());
	} else {
		pathName = fileName;
	}
	*pDirFlag = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? true : false;
	return true;
}

//-----------------------------------------------------------------------------
// OAL::DynamicLibrary (MSWIN)
//-----------------------------------------------------------------------------
OAL::DynamicLibrary::DynamicLibrary() : _hLibrary(nullptr)
{
}

bool OAL::DynamicLibrary::Open(const char* pathName)
{
	_hLibrary = ::LoadLibrary(ToNativeString(pathName).c_str());
	if (!_hLibrary) {
		Error::Issue(ErrorType::ImportError, "can't open module file '%s'", pathName);
		return false;
	}
	return true;
}

void* OAL::DynamicLibrary::GetEntry(const char* funcName)
{
	if (!_hLibrary) {
		Error::Issue(ErrorType::ImportError, "library has not been opened");
		return nullptr;
	}
	FARPROC pFunc = ::GetProcAddress(_hLibrary, funcName);
	if (!pFunc) {
		String funcNameEx = "_";
		funcNameEx += funcName;
		pFunc = ::GetProcAddress(_hLibrary, funcNameEx.c_str());
	}
	if (!pFunc) {
		//sig.SetError(ErrorType::ImportError, "can't find entry function '%s'", funcName);
		return nullptr;
	}
	return pFunc;
}

//-----------------------------------------------------------------------------
// Thread (MSWIN)
//-----------------------------------------------------------------------------
static DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	RefPtr<OAL::Thread> pThread(reinterpret_cast<OAL::Thread*>(lpParameter));
	pThread->Run();
	return 0;
}

OAL::Thread::Thread() : _hThread(nullptr), _threadId(0)
{
}

OAL::Thread::~Thread()
{
}

void OAL::Thread::Start()
{
	_hThread = ::CreateThread(nullptr, 0, ThreadProc, Reference(), 0, &_threadId);
}

void OAL::Thread::Wait()
{
	::WaitForSingleObject(_hThread, INFINITE);
}

String OAL::Thread::ToString(const StringStyle& ss) const
{
	return "Thread";
}

//-----------------------------------------------------------------------------
// Semaphore (MSWIN)
//-----------------------------------------------------------------------------
OAL::Semaphore::Semaphore()
{
	_hMutex = ::CreateMutex(nullptr, FALSE, nullptr);
}

OAL::Semaphore::~Semaphore()
{
	::CloseHandle(_hMutex);
}

void OAL::Semaphore::Wait()
{
	::WaitForSingleObject(_hMutex, INFINITE);
}

void OAL::Semaphore::Release()
{
	::ReleaseMutex(_hMutex);
}

String OAL::Semaphore::ToString(const StringStyle& ss) const
{
	return "Semaphore";
}

#else

//------------------------------------------------------------------------------
// OAL (POSIX)
//------------------------------------------------------------------------------
const char OAL::SepPathList = ':';

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

const char* OAL::GetEncodingForConsole()
{
	const char* encodingDefault = "utf-8";
	struct AssocInfo {
		const char* key;
		const char* value;
	};
	String str = GetEnv("LANG");
	if (str.empty()) return encodingDefault;
	const char* strp = str.c_str();
	const char* p = ::strchr(strp, '.');
	String langLeft, langRight;
	if (p == nullptr) {
		langLeft = strp;
	} else {
		langLeft = String(strp, p - strp);
		langRight = p + 1;
	}
	if (langRight.empty()) {
		static const AssocInfo assocInfoTbl[] = {
			{ "C",		"us-ascii"	},
			{ "en_US",	"us-ascii"	},
			{ "ja",	 	"euc-jp"	},
			{ "ja_JP",	"euc-jp"	},
			{ "zh_CN",	"gbk"		},	// CP936
			{ "ko_KR",	"euc-kr"	},	// CP949
			{ "zh_TW",	"big5"		},	// CP950
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(assocInfoTbl); i++) {
			if (::strcasecmp(langLeft.c_str(), assocInfoTbl[i].key) == 0) {
				return assocInfoTbl[i].value;
			}
		}
	} else {
		static const AssocInfo assocInfoTbl[] = {
			{ "eucJP",	"euc-jp"	},
			{ "ujis",	"euc-jp"	},
			{ "utf-8",	"utf-8"		},
			{ "utf8",	"utf-8"		},
			{ "utf-16",	"utf-16"	},
			{ "utf16",	"utf-16"	},
			{ "SJIS",	"shift_jis"	},	// CP932
			{ "gbk",	"gbk"		},	// CP936
			{ "eucKR",	"euc-kr"	},	// CP949
			{ "big5",	"big5"		},	// CP950
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(assocInfoTbl); i++) {
			if (::strcasecmp(langRight.c_str(), assocInfoTbl[i].key) == 0) {
				return assocInfoTbl[i].value;
			}
		}
	}
	return encodingDefault;
}

#if 0
const Symbol* OAL::GetLangCodeFromCFUserTextEncoding()
{
	struct AssocInfo {
		ULong key;
		const char* value;
	};
	static const AssocInfo assocInfoTbl[] = {
		{ 0,		"en"	},	// English
		{ 1,		"fr"	},	// French (not confirmed)
		{ 2,		"ru"	},	// Russian (not confirmed)
		{ 3,		"de"	},	// German (not confirmed)
		{ 4,		"it"	},	// Italian (not confirmed)
		{ 14,		"ja"	},	// Japanese
		{ 51,		"ko"	},	// Korean (not confirmed)
		{ 52,		"zh"	},	// Chinese (not confirmed)
	};
	String strLine = GetEnv("__CF_USER_TEXT_ENCODING");
	const char* strp = ::strchr(strLine.c_str(), ':');
	if (strp == nullptr) return Gurax_Symbol(en);
	strp++;
	strp = ::strchr(strp, ':');
	if (strp == nullptr) return Gurax_Symbol(en);
	strp++;
	ULong key = ::strtoul(strp, nullptr, 0); // returns zero for invalid format
	for (size_t i = 0; i < ArraySizeOf(assocInfoTbl); i++) {
		if (assocInfoTbl[i].key == key) {
			return Symbol::Add(assocInfoTbl[i].value);
		}
	}
	return Gurax_Symbol(en);
}
#endif

const Symbol* OAL::GetLangCode()
{
	String str = GetEnv("LANG");
	const char* strp = str.c_str();
	const char* p = strp;
	while (*p != '\0' && *p != '_' && *p != '.') p++;
	String lang = String(strp, p - strp);
	if (lang.empty()) {
		//return GetLangCodeFromCFUserTextEncoding();	// for Mac environment
		return Gurax_Symbol(en);
	} else if (lang == "C") {
		return Gurax_Symbol(en);
	}
	return Symbol::Add(lang.c_str());
}

String OAL::ToNativeString(const char* str)
{
	return str;
}

String OAL::FromNativeString(const char* str)
{
	return str;
}

bool OAL::ChangeDir(const char* dirName)
{
	return ::chdir(ToNativeString(dirName).c_str()) == 0;
}

bool OAL::ChangeMode(const char* pathName, mode_t mode, bool followLinkFlag)
{
	//return followLinkFlag?
	//	::chmod(ToNativeString(pathName).c_str(), mode) == 0 :
	//	lchmod(ToNativeString(pathName).c_str(), mode) == 0;
	return ::chmod(ToNativeString(pathName).c_str(), mode) == 0;
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
	//return followLinkFlag?
	//	::chmod(pathNameEnc.c_str(), st_mode) == 0 :
	//	lchmod(pathNameEnc.c_str(), st_mode) == 0;
	return ::chmod(pathNameEnc.c_str(), st_mode) == 0;
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
				int bytesRead = ::read(fdSrc.get(), pMemory->GetPointerC<char>(), pMemory->GetBytes());
				if (bytesRead == 0) break;
				if (::write(fdDst.get(), pMemory->GetPointerC<char>(), bytesRead) < bytesRead) return false;
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
		char* tgt = new char [statSrc.st_size];
		if (::readlink(pathNameSrcN.c_str(), tgt, statSrc.st_size) < 0) return false;
		if (::symlink(tgt, pathNameDstN.c_str()) < 0) return false;
		delete[] tgt;
		return true;
	} else if (S_ISSOCK(statSrc.st_mode)) {
		// nothing to do
	}
	return false;
}

bool OAL::CreateLink(const char* pathNameSrc, const char* pathNameDst)
{
	return ::symlink(pathNameSrc, pathNameDst) == 0;
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

void OAL::Sleep(Double secs)
{
	struct timeval tv;
	tv.tv_sec = static_cast<long>(secs);
	tv.tv_usec = static_cast<long>((secs - tv.tv_sec) * 1000000);
	::select(0, nullptr, nullptr, nullptr, &tv);
}

OAL::FileType OAL::GetFileType(const char* pathName)
{
	struct stat stat;
	if (::stat(ToNativeString(pathName).c_str(), &stat) != 0) return FileType::None;
	return
		S_ISREG(stat.st_mode)? FileType::Normal :
		S_ISDIR(stat.st_mode)? FileType::Directory :
		S_ISBLK(stat.st_mode)? FileType::Device :
		S_ISCHR(stat.st_mode)? FileType::Device :
		S_ISFIFO(stat.st_mode)? FileType::FIFO :
		S_ISLNK(stat.st_mode)? FileType::Link :
		S_ISSOCK(stat.st_mode)? FileType::Socket :
		FileType::Unknown;
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
			char* buff = pMemory->GetPointerC<char>();
			size_t bytesRead = pStreamCIn->Read(sig, buff, pMemory->GetBytes());
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
			char* buff = pMemory->GetPointerC<char>();
			size_t bytesRead = ::read(fdsCOut[0], buff, pMemory->GetBytes());
			pStreamCOut->Write(buff, bytesRead);
			if (Error::IsIssued()) goto done;
		}
		if (FD_ISSET(fdsCErr[0], &fdsRead)) {
			idleFlag = false;
			char* buff = pMemory->GetPointerC<char>();
			size_t bytesRead = ::read(fdsCErr[0], buff, pMemory->GetBytes());
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

DateTime* OAL::CreateDateTimeCur(bool utcFlag)
{
	time_t t;
	::time(&t);
	struct tm tm;
	if (utcFlag) {
		gmtime_r(&t, &tm);
		return CreateDateTime(tm, 0);
	} else {
		localtime_r(&t, &tm);
		return CreateDateTime(tm, GetSecsOffsetTZ());
	}
}

int OAL::GetSecsOffsetTZ()
{
	struct timeval tv;
	struct timezone tz;
	if (::gettimeofday(&tv, &tz) < 0) return 0;
	return -tz.tz_minuteswest * 60;
}

String OAL::ReadLink(const char* pathName)
{
	size_t bytes = 1024;
	for (int i = 0; i < 8; i++) {
		char* buff = new char [bytes + 1];
		int size = ::readlink(pathName, buff, bytes);
		if (size >= 0) {
			buff[size] = '\0';
			String rtn = FromNativeString(buff);
			delete[] buff;
			return rtn;
		}
		delete[] buff;
		if (errno != EFAULT) return "";
		bytes *= 2;
	}
	return String("");
}

bool OAL::FollowLink(String& pathName)
{
	for (int i = 0; i < 100; i++) {
		struct stat stat;
		int rtn = ::lstat(pathName.c_str(), &stat);
		if (rtn < 0) break;
		if (!S_ISLNK(stat.st_mode)) {
			pathName = PathName(pathName).Regulate();
			return true;
		}
		String pathNameLink = ReadLink(pathName.c_str());
		if (pathNameLink.empty()) {
			break;
		} else if (PathName(pathNameLink).IsAbsName()) {
			pathName = pathNameLink;
		} else {
			String dirName = PathName(pathName).ExtractDirName();
			if (dirName.empty()) dirName = "/";
			pathName = PathName(dirName).JoinAfter(pathNameLink.c_str());
		}
	}
	return false;
}

#if defined(GURAX_ON_DARWIN)

String OAL::GetPathName_Executable()
{
	String pathName;
	uint32_t bytes = 1024;
	char* buff = new char[bytes];
	if (::_NSGetExecutablePath(buff, &bytes) != 0) {
		delete[] buff;
		buff = new char[bytes];
		if (::_NSGetExecutablePath(buff, &bytes) != 0) return "";
	}
	return PathName(FromNativeString(buff)).Regulate();
}

#elif defined(GURAX_ON_LINUX)

String OAL::GetPathName_Executable()
{
	return PathName(ReadLink("/proc/self/exe")).Regulate();
}

#else

String OAL::GetPathName_Executable()
{
	return "/usr/bin/gurax";
}

#endif

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
			(!pattern || PathName(fileName).DoesMatchPattern(pattern))) break;
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

//-----------------------------------------------------------------------------
// OAL::Thread (POSIX)
//-----------------------------------------------------------------------------
static void *start_routine(void *arg)
{
	RefPtr<OAL::Thread> pThread(reinterpret_cast<OAL::Thread*>(arg));
	::pthread_detach(::pthread_self());
	pThread->Run();
	return 0;
}

OAL::Thread::Thread()
{
}

OAL::Thread::~Thread()
{
}

void OAL::Thread::Start()
{
	::pthread_create(&_pt, nullptr, &start_routine, Reference());
}

void OAL::Thread::Wait()
{
}

String OAL::Thread::ToString(const StringStyle& ss) const
{
	return "Thread";
}

//-----------------------------------------------------------------------------
// OAL::Semaphore (POSIX)
//-----------------------------------------------------------------------------
OAL::Semaphore::Semaphore()
{
	::sem_init(&_sem, 0, 1);
}

OAL::Semaphore::~Semaphore()
{
	::sem_destroy(&_sem);
}

void OAL::Semaphore::Wait()
{
	::sem_wait(&_sem);
}

void OAL::Semaphore::Release()
{
	::sem_post(&_sem);
}

String OAL::Semaphore::ToString(const StringStyle& ss) const
{
	return "Semaphore";
}

#endif

}
