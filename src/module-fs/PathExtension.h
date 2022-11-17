//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_FS_PATHEXTENSION_H
#define GURAX_MODULE_FS_PATHEXTENSION_H
#include <gurax.h>

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
class PathMgrEx : public PathMgr {
public:
	virtual bool IsResponsible(Directory* pDirectoryParent, const char* pathName) override;
protected:
	virtual Directory* DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe) override;
	virtual Existence DoCheckExistence(Directory* pDirectoryParent, const char** pPathName) override;
};

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatEx : public Stat {
public:
	using Stat::Stat;
public:
#if defined(GURAX_ON_MSWIN)
	StatEx(String name, const WIN32_FILE_ATTRIBUTE_DATA& attrData);
	//StatEx(String name, const BY_HANDLE_FILE_INFORMATION& attrData);
	//StatEx(String name, const WIN32_FIND_DATA& findData);
	static UInt32 MakeFlags(DWORD dwFileAttributes);
	static UInt16 MakeMode(DWORD dwFileAttributes);
#else
	StatEx(String name, struct stat& sb);
	static UInt32 MakeFlags(struct stat& sb);
#endif
	static StatEx* Create(const char* pathName);
};

//------------------------------------------------------------------------------
// DirectoryEx
//------------------------------------------------------------------------------
class DirectoryEx : public Directory {
protected:
	RefPtr<StatEx> _pStatEx;
#if defined(GURAX_ON_MSWIN)
	HANDLE _hFind;
#else
	DIR* _pDir;
#endif
public:
	DirectoryEx(Type type, String name, StatEx* pStatEx);
protected:
	~DirectoryEx();
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value_Stat* DoCreateStatValue() override;
};

//------------------------------------------------------------------------------
// StreamEx
//------------------------------------------------------------------------------
class StreamEx : public Stream {
private:
	FILE* _fp;
	String _pathName;
public:
	StreamEx(Flags flags, FILE* fp, String pathName) : Stream(flags), _fp(fp), _pathName(pathName) {}
	virtual ~StreamEx() { Close(); }
public:
	virtual const char* GetName() const override { return _pathName.c_str(); };
	virtual const char* GetIdentifier() const override { return _pathName.c_str(); }
	virtual size_t DoGetBytes() override;
	virtual Stat* DoCreateStat() override;
	virtual Value_Stat* DoCreateStatValue() override;
	virtual bool DoClose() override { return ::fclose(_fp) == 0; }
	virtual int DoGetChar() override { _offset++; return ::fgetc(_fp); }
	virtual bool DoPutChar(char ch) override { _offset++; ::fputc(ch, _fp); return true; }
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoWrite(const void* buff, size_t len) override;
	virtual bool DoFlush() override { return ::fflush(_fp) == 0; }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

Gurax_EndModuleScope(fs)

#endif
