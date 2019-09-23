//==============================================================================
// PathMgrEx.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return pDirectoryParent == nullptr;
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName)
{
	String pathName = PathName(*pPathName).MakeAbsName();
	RefPtr<Stat> pStat(Stat::Create(pathName.c_str()));
	if (!pStat) return nullptr;
	Directory::Type type = pStat->IsDir()? Directory::Type::Container : Directory::Type::Item;
	return new DirectoryEx(pDirectoryParent, pathName.c_str(), type, pStat.release());
}

PathMgr::Existence PathMgrEx::DoCheckExistence(Directory* pDirectoryParent, const char* pathName)
{
	return (pDirectoryParent == nullptr && OAL::DoesExist(pathName))? Existence::Exist : Existence::None;
}

//------------------------------------------------------------------------------
// DirectoryEx
//------------------------------------------------------------------------------
#if defined(GURAX_ON_MSWIN)
DirectoryEx::DirectoryEx(Directory* pDirectoryParent, String name, Type type, Stat* pStat) :
	Directory(pDirectoryParent, name, type, PathName::SepPlatform, PathName::CaseFlagPlatform),
	_pStat(pStat), _hFind(INVALID_HANDLE_VALUE)
{
}

DirectoryEx::~DirectoryEx()
{
	::FindClose(_hFind);
}

Directory* DirectoryEx::DoNextChild()
{
	return nullptr;
}

#else

DirectoryEx::DirectoryEx(Directory* pDirectoryParent, String name, Type type, Stat* pStat) :
	Directory(pDirectoryParent, name, type, PathName::SepPlatform, PathName::CaseFlagPlatform),
	_pStat(pStat), _pDir(nullptr)
{
}

DirectoryEx::~DirectoryEx()
{
	if (_pDir) closedir(_pDir);
}

Directory* DirectoryEx::DoNextChild()
{
	if (!_pDir) {
		String pathName(MakePathName(false));
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
	return new DirectoryEx(Reference(), OAL::FromNativeString(pEnt->d_name).c_str(), type, nullptr);
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
	String pathName = MakePathName(false);
	FILE* fp = ::fopen(pathName.c_str(), mode);
	if (!fp) {
		Error::Issue(ErrorType::IOError, "failed to open a file '%s'", pathName.c_str());
		return nullptr;
	}
	return new StreamEx(fp, pathName);
}

Value* DirectoryEx::DoGetStatValue()
{
	if (!_pStat) {
		_pStat.reset(Stat::Create(MakePathName(false).c_str()));
		if (!_pStat) {
			Error::Issue(ErrorType::IOError, "failed to get file status");
			return Value::nil();
		}
	}
	return new Value_Stat(_pStat->Reference());
}

//------------------------------------------------------------------------------
// StreamEx
//------------------------------------------------------------------------------

Gurax_EndModuleScope(fs)
