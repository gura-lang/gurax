//==============================================================================
// module-fs.cpp
//==============================================================================
#include "stdafx.h"

#if defined(GURAX_ON_MSWIN)
#else
#include <dirent.h>
#endif

Gurax_BeginModule(fs)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
class PathMgrEx : public PathMgr {
public:
	virtual bool IsResponsible(Directory* pDirectoryParent, const char* pathName) override;
protected:
	virtual Directory* DoOpenDirectory(Directory* pDirectoryParent,
									   const char** pPathName, NotFoundMode notFoundMode) override;
};

//------------------------------------------------------------------------------
// DirectoryEx
//------------------------------------------------------------------------------
class DirectoryEx : public Directory {
protected:
	RefPtr<Stat> _pStat;
#if defined(GURAX_ON_MSWIN)
	HANDLE _hFind;
#else
	DIR *_pDir;
#endif
public:
	DirectoryEx(Directory* pDirectoryParent, String name, Type type, Stat* pStat);
protected:
	~DirectoryEx();
protected:
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoGetStatValue() override;
};

//------------------------------------------------------------------------------
// StreamEx
//------------------------------------------------------------------------------
class StreamEx : public Stream {
private:
	FILE* _fp;
	String _pathName;
public:
	StreamEx(FILE* fp, String pathName) : _fp(fp), _pathName(pathName) {}
	virtual ~StreamEx() { ::fclose(_fp); }
	virtual const char* GetName() const override { return _pathName.c_str(); };
	virtual const char* GetIdentifier() const override { return _pathName.c_str(); }
	virtual void Close() override { ::fclose(_fp); }
	virtual int GetChar() override { return ::fgetc(_fp); }
	virtual bool PutChar(char ch) override { ::fputc(ch, _fp); return true; }
	virtual size_t Read(void* buff, size_t len) override {
		return ::fread(buff, 1, len, _fp);
	}
	virtual size_t Write(const void* buff, size_t len) override {
		return ::fwrite(buff, 1, len, _fp);
	}
};

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return pDirectoryParent == nullptr;
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent,
									  const char** pPathName, NotFoundMode notFoundMode)
{
	String pathName = PathName(*pPathName).MakeAbsName();
	RefPtr<Stat> pStat(Stat::Generate(pathName.c_str()));
	if (!pStat) return nullptr;
	Directory::Type type = pStat->IsDir()? Directory::Type::Container : Directory::Type::Item;
	return new DirectoryEx(pDirectoryParent, pathName.c_str(), type, pStat.release());
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
	if (_pStat) {
		_pStat.reset(Stat::Generate(MakePathName(false).c_str()));
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

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	// Prepare VType
	VTYPE_Stat.Prepare(frame);
	// Assignment of function
	//Assign(Gurax_CreateFunction(Exit));
	// Assignment of path manager
	Basement::Inst.AssignPathMgr(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(fs)
