//==============================================================================
// module-fs.cpp
//==============================================================================
#include "stdafx.h"

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
public:
	DirectoryEx(Directory* pDirectoryParent, String name, Type type, Stat* pStat);
protected:
	~DirectoryEx();
public:
	const Stat& GetStat() const { return *_pStat; }
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
	bool _closeAtDeletionFlag;
	String _name;
	String _identifier;
public:
	StreamEx(FILE* fp, bool closeAtDeletionFlag, String name, String identifier) :
		_fp(fp), _closeAtDeletionFlag(closeAtDeletionFlag),
		_name(std::move(name)), _identifier(std::move(identifier)) {}
	StreamEx(FILE* fp, bool closeAtDeletionFlag, String name) :
		StreamEx(fp, closeAtDeletionFlag, name, name) {}
	virtual ~StreamEx() {
		if (_closeAtDeletionFlag) ::fclose(_fp);
	}
	virtual const char* GetName() const override { return _name.c_str(); };
	virtual const char* GetIdentifier() const override { return _identifier.c_str(); }
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
DirectoryEx::DirectoryEx(Directory* pDirectoryParent, String name, Type type, Stat* pStat) :
	Directory(pDirectoryParent, name, type, PathName::SepPlatform, PathName::CaseFlagPlatform),
	_pStat(pStat)
{
}

DirectoryEx::~DirectoryEx()
{
}

Directory* DirectoryEx::DoNextChild()
{
	return nullptr;
}

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
	const char* pathName = GetName();
	FILE* fp = ::fopen(pathName, mode);
	if (!fp) {
		Error::Issue(ErrorType::IOError, "failed to open a file '%s'", pathName);
		return nullptr;
	}
	return new StreamEx(fp, true, pathName, pathName);
}

Value* DirectoryEx::DoGetStatValue()
{
	return new Value_Stat(GetStat().Reference());
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
