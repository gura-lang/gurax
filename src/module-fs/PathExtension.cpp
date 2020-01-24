//==============================================================================
// PathExtension.cpp
//==============================================================================
#include "stdafx.h"

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
	if (!**pPathName) return new DirectoryEx("", Directory::Type::Container, nullptr);
	String pathName;
	for (const char* p = *pPathName; ; p++) {
		if (*p) pathName += *p;
		if (*p == '\0' || PathName::IsSep(*p)) {
			OAL::FileType fileType = OAL::GetFileType(pathName.c_str());
			if (fileType != OAL::FileType::None) {
				// nothing to do
			} else if (typeWouldBe == Directory::Type::None || (*p != '\0' && *(p + 1) != '\0')) {
				Error::Issue(ErrorType::PathError, "specified path is not found: %s", pathName.c_str());
				return nullptr;
			}
			if (*p == '\0' || fileType != OAL::FileType::Directory) {
				if (fileType != OAL::FileType::None && typeWouldBe != Directory::Type::None) {
					// this means overwriting of an existing file
					//Error::Issue(ErrorType::PathError, "specified path already exists");
					//return nullptr;
				}
				*pPathName = p;
				break;
			}
		}
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
		pDirectory.reset(new DirectoryEx(pathNameAccum, Directory::Type::Root, nullptr));
	}
	for (auto pField = fields.begin(); pField != fields.end(); pField++) {
		const String& field = *pField;
		if (field.empty()) break;
		Directory::Type type = typeWouldBe;
		if (type == Directory::Type::None) {
			type = (pField + 1 == fields.end())? Directory::Type::Item : Directory::Type::Container;
		}
		if (pField != fields.begin()) pathNameAccum += PathName::SepPlatform;
		pathNameAccum += field;
		RefPtr<StatEx> pStatEx(StatEx::Create(PathName(pathNameAccum).MakeAbsName().c_str()));
		if (pStatEx) {
			type = pStatEx->IsDir()? Directory::Type::Container : Directory::Type::Item;
		}
		RefPtr<Directory> pDirectoryNew(new DirectoryEx(field, type, pStatEx.release()));
		if (pDirectory) pDirectoryNew->SetDirectoryParent(*pDirectory);
		pDirectory.reset(pDirectoryNew.release());
	}
	return pDirectory? pDirectory.release() : new DirectoryEx("", Directory::Type::Container, nullptr);
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
StatEx::StatEx(struct stat& sb, String pathName) :
	Stat(OAL::CreateDateTime(sb.st_ctime), OAL::CreateDateTime(sb.st_mtime),
		 OAL::CreateDateTime(sb.st_atime),
		 pathName, 0, sb.st_mode & 0777, sb.st_size, sb.st_uid, sb.st_gid)
{
	if (S_ISDIR(sb.st_mode))  _flags |= Flag::Dir;
	if (S_ISCHR(sb.st_mode))  _flags |= Flag::Chr;
	if (S_ISBLK(sb.st_mode))  _flags |= Flag::Blk;
	if (S_ISREG(sb.st_mode))  _flags |= Flag::Reg;
	if (S_ISFIFO(sb.st_mode)) _flags |= Flag::Fifo;
	if (S_ISLNK(sb.st_mode))  _flags |= Flag::Lnk;
	if (S_ISSOCK(sb.st_mode)) _flags |= Flag::Sock;
}

StatEx* StatEx::Create(const char* pathName)
{
	struct stat sb;
	String pathNameAbs = PathName(pathName).MakeAbsName();
	String pathNameAbsN = OAL::ToNativeString(pathNameAbs.c_str());
	if (::stat(pathNameAbsN.c_str(), &sb) < 0) return nullptr;
	return new StatEx(sb, pathNameAbs);
}

#if defined(GURAX_ON_MSWIN)

StatEx::StatEx(const char* pathName, const BY_HANDLE_FILE_INFORMATION& attrData)
{
}

StatEx::StatEx(const char* pathName, const WIN32_FILE_ATTRIBUTE_DATA& attrData)
{
}

StatEx::StatEx(const char* pathName, const WIN32_FIND_DATA& findData)
{
}

#endif

//------------------------------------------------------------------------------
// DirectoryEx
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)

DirectoryEx::DirectoryEx(String name, Type type, StatEx* pStatEx) :
	Directory(name, type, PathName::SepPlatform, PathName::CaseFlagPlatform),
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
	return nullptr;
}

#else

DirectoryEx::DirectoryEx(String name, Type type, StatEx* pStatEx) :
	Directory(name, type, PathName::SepPlatform, PathName::CaseFlagPlatform),
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
		String pathNameEnc = OAL::ToNativeString(pathName.c_str());
		_pDir = opendir(pathNameEnc.empty()? "." : pathNameEnc.c_str());
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
	Type type = (pEnt->d_type == DT_DIR)? Type::Container : Type::Item;
	RefPtr<Directory> pDirectory(new DirectoryEx(OAL::FromNativeString(pEnt->d_name).c_str(), type, nullptr));
	pDirectory->SetDirectoryParent(*this);
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
	FILE* fp = ::fopen(pathName.c_str(), mode);
	if (!fp) {
		Error::Issue(ErrorType::IOError, "failed to open a file '%s'", pathName.c_str());
		return nullptr;
	}
	Stream::Flags flags = Stream::Flag::Readable;
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) flags |= Stream::Flag::Writable;
	return new StreamEx(flags, fp, pathName);
}

Value* DirectoryEx::DoCreateStatValue()
{
	if (!_pStatEx) {
		_pStatEx.reset(StatEx::Create(MakeFullPathName(false).c_str()));
		if (!_pStatEx) {
			Error::Issue(ErrorType::IOError, "failed to get file status");
			return Value::nil();
		}
	}
	return new Value_Stat(_pStatEx->Reference());
}

//------------------------------------------------------------------------------
// StreamEx
//------------------------------------------------------------------------------
size_t StreamEx::DoGetSize()
{
	struct stat sb;
	if (::fstat(fileno(_fp), &sb) < 0) return 0;
	return sb.st_size;
}

Stat* StreamEx::DoCreateStat()
{
	struct stat sb;
	if (::fstat(fileno(_fp), &sb) < 0) return nullptr;
	RefPtr<StatEx> pStatEx(new StatEx(sb, PathName(_pathName).MakeAbsName()));
	return pStatEx.release();
}

Value* StreamEx::DoCreateStatValue()
{
	struct stat sb;
	if (::fstat(fileno(_fp), &sb) < 0) return nullptr;
	RefPtr<StatEx> pStatEx(new StatEx(sb, PathName(_pathName).MakeAbsName()));
	return new Value_StatEx(pStatEx.release());
}

bool StreamEx::DoSeek(size_t offset, size_t offsetPrev)
{
	if (!_fp) return true;
	if (::fseek(_fp, static_cast<long>(offset), SEEK_SET) != 0) {
		Error::Issue(ErrorType::IOError, "seek error");
		return false;
	}
	return true;
}

Gurax_EndModuleScope(fs)
