//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_PATHEXTENSION_H
#define GURAX_MODULE_ZIP_PATHEXTENSION_H
#include <gurax.h>
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)
	
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
	// Referable declaration
	Gurax_DeclareReferable(StatEx);
private:
	std::unique_ptr<CentralFileHeader> _pCentralFileHeader;
public:
	StatEx(CentralFileHeader* pCentralFileHeader);
public:
	CentralFileHeader& GetCentralFileHeader() { return *_pCentralFileHeader; }
	const CentralFileHeader& GetCentralFileHeader() const { return *_pCentralFileHeader; }
public:
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//-----------------------------------------------------------------------------
// StatExList
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE StatExList : public ListBase<StatEx*> {
public:
	StatEx* FindByName(const char* fileName) const;
	bool Write(Stream& streamDst) const;
};

//-----------------------------------------------------------------------------
// StatExOwner
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE StatExOwner : public StatExList {
public:
	~StatExOwner() { Clear(); }
	void Clear();
	bool ReadCentralDirectory(Stream& streamSrc);
};

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
class DirectoryEx : public Directory {
public:
	class CoreEx : public Core {
	public:
		Gurax_DeclareReferable(CoreEx);
	private:
		RefPtr<Stream> _pStreamSrc;
		RefPtr<StatEx> _pStatEx;	// may be nullptr
	public:
		CoreEx(Type type, Stream* pStreamSrc, StatEx* pStatEx) :
			Core(type, PathName::SepPlatform, PathName::CaseFlagPlatform, new CoreOwner()),
			_pStreamSrc(pStreamSrc), _pStatEx(pStatEx) {}
		Stream& GetStreamSrc() { return *_pStreamSrc; }
		StatEx* GetStatEx() { return _pStatEx.get(); }
	public:
		virtual Directory* GenerateDirectory() override { return new DirectoryEx(Reference()); }
	};
private:
	size_t _idxChild;
public:
	DirectoryEx(CoreEx* pCoreEx) : Directory(pCoreEx), _idxChild(0) {}
public:
	static Directory* CreateTop(Stream& streamSrc);
	CoreEx& GetCoreEx() { return dynamic_cast<CoreEx&>(*_pCore); }
	Stream& GetStreamSrc() { return GetCoreEx().GetStreamSrc(); }
	StatEx* GetStatEx() { return GetCoreEx().GetStatEx(); }
	bool ReadCentralDirectory();
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value_Stat* DoCreateStatValue() override;
};

//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
class Stream_Reader : public Stream {
protected:
	RefPtr<Stream> _pStreamSrc;
	RefPtr<StatEx> _pStatEx;
	String _name;
	size_t _bytesUncompressed;
	size_t _bytesCompressed;
	UInt32 _crc32Expected;
	bool _seekedFlag;
	CRC32 _crc32;
public:
	Stream_Reader(Stream* pStreamSrc, StatEx* pStatEx);
public:
	size_t CheckCRC32(const void* buff, size_t bytesRead);
public:
	static Stream* Create(Stream& streamSrc, const StatEx& statEx);
public:
	virtual bool Initialize() = 0;
	virtual const char* GetName() const override { return _name.c_str(); }
	virtual const char* GetIdentifier() const override { return _name.c_str(); }
	virtual bool DoWrite(const void* buff, size_t len) override { return false; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoClose() override { return true; }
	virtual size_t DoGetBytes() override { return _bytesUncompressed; }
	virtual Value_Stat* DoCreateStatValue() override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
class Stream_Reader_Store : public Stream_Reader {
private:
	size_t _offsetTop;
public:
	Stream_Reader_Store(Stream* pStreamSrc, StatEx* pStatEx);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t bytes) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate
// Compression method #8: Deflated
//-----------------------------------------------------------------------------
class Stream_Reader_Deflate : public Stream_Reader {
private:
	RefPtr<ZLib::Stream_Reader> _pStreamReader;
public:
	Stream_Reader_Deflate(Stream* pStreamSrc, StatEx* pStatEx);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_BZIP2
// Compression method #12: BZIP2
//-----------------------------------------------------------------------------
class Stream_Reader_BZIP2 : public Stream_Reader {
private:
	RefPtr<BZLib::Stream_Reader> _pStreamReader;
public:
	Stream_Reader_BZIP2(Stream* pStreamSrc, StatEx* pStatEx);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate64
// Compression method #9: Enhanced Deflating using Deflate64(tm)
//-----------------------------------------------------------------------------
class Stream_Reader_Deflate64 : public Stream_Reader {
public:
	Stream_Reader_Deflate64(Stream* pStreamSrc, StatEx* pStatEx);
	virtual bool Initialize() override;
	virtual size_t DoRead(void* buff, size_t len) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
};

Gurax_EndModuleScope(zip)

#endif
