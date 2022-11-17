//==============================================================================
// PathExtension.cpp
//==============================================================================
#include "stdafx.h"
#include "PathExtension.h"
#include "VType_StatEx.h"
#include <sys/stat.h>

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return !pDirectoryParent;
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe)
{
	if (**pPathName == '\0') return new DirectoryEx(Directory::Type::Folder, "", nullptr);
	String pathName;
	for (const char*& p = *pPathName; ; p++) {
		char ch = *p;
		if (!(ch == '\0' || PathName::IsSep(ch))) {
			pathName += ch;
			continue;
		}
		OAL::FileType fileType = pathName.empty()? OAL::FileType::Directory : OAL::GetFileType(pathName.c_str());
		if (fileType == OAL::FileType::None && typeWouldBe == Directory::Type::None) {
			Error::Issue(ErrorType::PathError, "specified path is not found: %s", pathName.c_str());
			return nullptr;
		}
		if (ch == '\0' || fileType != OAL::FileType::Directory) break;
		pathName += ch;
	}
	String driveLetter;
	String prefix;
	StringList fields;
	PathName(pathName).SplitIntoFields(&driveLetter, &prefix, fields);
	String pathNameAccum;
	pathNameAccum += driveLetter;
	pathNameAccum += prefix;
	RefPtr<Directory> pDirectory;
	if (!pathNameAccum.empty()) {
		pDirectory.reset(new DirectoryEx(Directory::Type::Folder, pathNameAccum, nullptr));
	}
	for (auto pField = fields.begin(); pField != fields.end(); pField++) {
		const String& field = *pField;
		if (field.empty()) break;
		Directory::Type type = typeWouldBe;
		if (type == Directory::Type::None) {
			type = (pField + 1 == fields.end())? Directory::Type::Item : Directory::Type::Folder;
		}
		if (pField != fields.begin()) pathNameAccum += PathName::SepPlatform;
		pathNameAccum += field;
		RefPtr<StatEx> pStatEx(StatEx::Create(PathName(pathNameAccum).MakeAbsName().c_str()));
		if (pStatEx) {
			type = pStatEx->IsDir()? Directory::Type::Folder : Directory::Type::Item;
		}
		RefPtr<Directory> pDirectoryNew(new DirectoryEx(type, field, pStatEx.release()));
		if (pDirectory) pDirectoryNew->SetDirectoryParent(pDirectory.Reference());
		pDirectory.reset(pDirectoryNew.release());
	}
	return pDirectory? pDirectory.release() : new DirectoryEx(Directory::Type::Folder, "", nullptr);
}

PathMgr::Existence PathMgrEx::DoCheckExistence(Directory* pDirectoryParent, const char** pPathName)
{
	if (!**pPathName) return Existence::Exist;
	String pathName;
	for (const char* p = *pPathName; ; p++) {
		if (*p) pathName += *p;
		if (*p == '\0' || PathName::IsSep(*p)) {
			OAL::FileType fileType = OAL::GetFileType(pathName.c_str());
			if (fileType == OAL::FileType::None) return Existence::None;
			if (*p == '\0' || fileType != OAL::FileType::Directory) {
				*pPathName = p;
				break;
			}
		}
	}
	return Existence::Exist;
}

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)

StatEx::StatEx(String name, const WIN32_FILE_ATTRIBUTE_DATA& attrData) :
	Stat(OAL::CreateDateTime(attrData.ftCreationTime),
		OAL::CreateDateTime(attrData.ftLastWriteTime),
		OAL::CreateDateTime(attrData.ftLastAccessTime),
		name, MakeFlags(attrData.dwFileAttributes),
		MakeMode(attrData.dwFileAttributes), attrData.nFileSizeLow, 0, 0)
{
}

#if 0
StatEx::StatEx(String name, const BY_HANDLE_FILE_INFORMATION& attrData) :
	Stat(OAL::CreateDateTime(attrData.ftCreationTime),
		OAL::CreateDateTime(attrData.ftLastWriteTime),
		OAL::CreateDateTime(attrData.ftLastAccessTime),
		name, MakeFlags(attrData.dwFileAttributes),
		MakeMode(attrData.dwFileAttributes), attrData.nFileSizeLow, 0, 0)
{
}

StatEx::StatEx(String name, const WIN32_FIND_DATA& findData) :
	Stat(OAL::CreateDateTime(findData.ftCreationTime),
		OAL::CreateDateTime(findData.ftLastWriteTime),
		OAL::CreateDateTime(findData.ftLastAccessTime),
		name, MakeFlags(findData.dwFileAttributes),
		MakeMode(findData.dwFileAttributes), findData.nFileSizeLow, 0, 0)
{
}
#endif

StatEx* StatEx::Create(const char* fileName)
{
	ULong attr = 0;
	WIN32_FILE_ATTRIBUTE_DATA attrData;
	String pathName = PathName(fileName).MakeAbsName();
	if (::GetFileAttributesEx(OAL::ToNativeString(pathName.c_str()).c_str(),
						GetFileExInfoStandard, &attrData) == 0) return nullptr;
	return new StatEx(PathName(fileName).ExtractBottomName(), attrData);
}

UInt32 StatEx::MakeFlags(DWORD dwFileAttributes)
{
	UInt32 flags = 0;
	if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		flags |= Flag::Dir;
	} else {
		flags |= Flag::Reg;
	}
	return flags;
}

UInt16 StatEx::MakeMode(DWORD dwFileAttributes)
{
	UInt16 mode = 0;
	if (dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
		mode |= 0666;
	} else {
		mode |= 0777;
	}
	return mode;
}

#else

StatEx::StatEx(String name, struct stat& sb) :
	Stat(OAL::CreateDateTime(sb.st_ctime),
		OAL::CreateDateTime(sb.st_mtime),
		OAL::CreateDateTime(sb.st_atime),
		name, MakeFlags(sb), sb.st_mode & 0777, sb.st_size, sb.st_uid, sb.st_gid)
{
}

StatEx* StatEx::Create(const char* pathName)
{
	struct stat sb;
	String pathName_ = PathName(pathName).MakeAbsName();
	if (::stat(OAL::ToNativeString(pathName_.c_str()).c_str(), &sb) < 0) return nullptr;
	return new StatEx(PathName(pathName).ExtractBottomName(), sb);
}

UInt32 StatEx::MakeFlags(struct stat& sb)
{
	UInt32 flags = 0;
	if (S_ISDIR(sb.st_mode))  flags |= Flag::Dir;
	if (S_ISCHR(sb.st_mode))  flags |= Flag::Chr;
	if (S_ISBLK(sb.st_mode))  flags |= Flag::Blk;
	if (S_ISREG(sb.st_mode))  flags |= Flag::Reg;
	if (S_ISFIFO(sb.st_mode)) flags |= Flag::Fifo;
	if (S_ISLNK(sb.st_mode))  flags |= Flag::Lnk;
	if (S_ISSOCK(sb.st_mode)) flags |= Flag::Sock;
	return flags;
}

#endif

//------------------------------------------------------------------------------
// DirectoryEx
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)

DirectoryEx::DirectoryEx(Type type, String name, StatEx* pStatEx) :
	Directory(type, name, PathName::SepPlatform, PathName::CaseFlagPlatform),
	_pStatEx(pStatEx), _hFind(INVALID_HANDLE_VALUE)
{
}

DirectoryEx::~DirectoryEx()
{
	::FindClose(_hFind);
}

void DirectoryEx::DoRewindChild()
{
	::FindClose(_hFind);
	_hFind = INVALID_HANDLE_VALUE;
}

Directory* DirectoryEx::DoNextChild()
{
	WIN32_FIND_DATA findData;
	if (_hFind == INVALID_HANDLE_VALUE) {
		String pathName(MakeFullPathName(false));
		if (!pathName.empty()) pathName += '\\';
		pathName += "*.*";
		_hFind = ::FindFirstFile(OAL::ToNativeString(pathName.c_str()).c_str(), &findData);
		if (_hFind == INVALID_HANDLE_VALUE) return nullptr;
	} else if (!::FindNextFile(_hFind, &findData)) {
		::FindClose(_hFind);
		_hFind = INVALID_HANDLE_VALUE;
		return nullptr;
	}
	while (::strcmp(findData.cFileName, ".") == 0 ||
		::strcmp(findData.cFileName, "..") == 0) {
		if (!::FindNextFile(_hFind, &findData)) {
			::FindClose(_hFind);
			_hFind = INVALID_HANDLE_VALUE;
			return nullptr;
		}
	}
	Type type = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? Type::Folder : Type::Item;
	RefPtr<Directory> pDirectory(new DirectoryEx(type, OAL::FromNativeString(findData.cFileName).c_str(), nullptr));
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
}

#else

DirectoryEx::DirectoryEx(Type type, String name, StatEx* pStatEx) :
	Directory(type, name, PathName::SepPlatform, PathName::CaseFlagPlatform),
	_pStatEx(pStatEx), _pDir(nullptr)
{
}

DirectoryEx::~DirectoryEx()
{
	if (_pDir) closedir(_pDir);
}

void DirectoryEx::DoRewindChild()
{
	if (_pDir) {
		closedir(_pDir);
		_pDir = nullptr;
	}
}

Directory* DirectoryEx::DoNextChild()
{
	if (!_pDir) {
		String pathName(MakeFullPathName(false));
		_pDir = opendir(pathName.empty()? "." : OAL::ToNativeString(pathName.c_str()).c_str());
		if (!_pDir) return nullptr;
	}
	struct dirent* pEnt = nullptr;
	for (;;) {
		pEnt = readdir(_pDir);
		if (!pEnt) {
			closedir(_pDir);
			_pDir = nullptr;
			return nullptr;
		}
		if (::strcmp(pEnt->d_name, ".") != 0 && ::strcmp(pEnt->d_name, "..") != 0) break;
	}
	Type type = (pEnt->d_type == DT_DIR)? Type::Folder : Type::Item;
	RefPtr<Directory> pDirectory(new DirectoryEx(type, OAL::FromNativeString(pEnt->d_name).c_str(), nullptr));
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
}

#endif

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
	openFlags &= Stream::OpenFlag::Read | Stream::OpenFlag::Write | Stream::OpenFlag::Append;
	const char* mode =
		(openFlags == Stream::OpenFlag::Read)? "rb" :
		(openFlags == Stream::OpenFlag::Write)? "wb" :
		(openFlags == Stream::OpenFlag::Append)? "ab" :
		(openFlags == (Stream::OpenFlag::Read | Stream::OpenFlag::Write))? "r+b" :
		(openFlags == (Stream::OpenFlag::Write | Stream::OpenFlag::Append))? "w+b" :
		(openFlags == (Stream::OpenFlag::Read | Stream::OpenFlag::Append))? "a+b" :
		(openFlags == (Stream::OpenFlag::Read | Stream::OpenFlag::Write | Stream::OpenFlag::Append))? "w+b" :
		"rb";
	String pathName = MakeFullPathName(false);
	FILE* fp = ::fopen(OAL::ToNativeString(pathName.c_str()).c_str(), mode);
	if (!fp) {
		Error::Issue(ErrorType::IOError, "failed to open a file '%s'", pathName.c_str());
		return nullptr;
	}
	Stream::Flags flags = Stream::Flag::Readable;
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) flags |= Stream::Flag::Writable;
	return new StreamEx(flags, fp, pathName);
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	if (!_pStatEx) {
		_pStatEx.reset(StatEx::Create(MakeFullPathName(false).c_str()));
		if (!_pStatEx) {
			Error::Issue(ErrorType::IOError, "failed to get file status");
			return nullptr;
		}
	}
	return new Value_Stat(_pStatEx->Reference());
}

//------------------------------------------------------------------------------
// StreamEx
//------------------------------------------------------------------------------
size_t StreamEx::DoGetBytes()
{
	struct stat sb;
	if (::fstat(fileno(_fp), &sb) < 0) return 0;
	return sb.st_size;
}

Stat* StreamEx::DoCreateStat()
{
	return StatEx::Create(_pathName.c_str());
}

Value_Stat* StreamEx::DoCreateStatValue()
{
	return new Value_StatEx(StatEx::Create(_pathName.c_str()));
}

size_t StreamEx::DoRead(void* buff, size_t len)
{
	size_t lenRead = ::fread(buff, 1, len, _fp);
	_offset += lenRead;
	return lenRead;
}

bool StreamEx::DoWrite(const void* buff, size_t len)
{
	size_t lenWritten = ::fwrite(buff, 1, len, _fp);
	_offset += lenWritten;
	return len == lenWritten;
}

bool StreamEx::DoSeek(size_t offset, size_t offsetPrev)
{
	if (!_fp) return true;
	if (::fseek(_fp, static_cast<long>(offset), SEEK_SET) != 0) {
		Error::Issue(ErrorType::IOError, "seek error");
		return false;
	}
	_offset = offset;
	return true;
}

Gurax_EndModuleScope(fs)
