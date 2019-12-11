//==============================================================================
// PathMgrEx.h
//==============================================================================
#ifndef GURAX_MODULE_FS_PATHMGREX_H
#define GURAX_MODULE_FS_PATHMGREX_H
#include <gurax.h>
#include "Stat.h"

Gurax_BeginModuleScope(fs)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
class PathMgrEx : public PathMgr {
public:
	virtual bool IsResponsible(Directory* pDirectoryParent, const char* pathName) override;
protected:
	virtual Directory* DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe) override;
	virtual Existence DoCheckExistence(Directory* pDirectoryParent, const char* pathName) override;
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
	StreamEx(Flags flags, FILE* fp, String pathName) : Stream(flags), _fp(fp), _pathName(pathName) {}
	virtual ~StreamEx() { ::fclose(_fp); }
	virtual const char* GetName() const override { return _pathName.c_str(); };
	virtual const char* GetIdentifier() const override { return _pathName.c_str(); }
	virtual void Close() override { ::fclose(_fp); }
	virtual int DoGetChar() override { return ::fgetc(_fp); }
	virtual bool DoPutChar(char ch) override { ::fputc(ch, _fp); return true; }
	virtual size_t Read(void* buff, size_t len) override {
		return ::fread(buff, 1, len, _fp);
	}
	virtual size_t Write(const void* buff, size_t len) override {
		return ::fwrite(buff, 1, len, _fp);
	}
	virtual void Flush() override { ::fflush(_fp); }
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

Gurax_EndModuleScope(fs)

#endif
