//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_PATHEXTENSION_H
#define GURAX_MODULE_ZIP_PATHEXTENSION_H
#include <gurax.h>
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)
	
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
	bool IsFolder() const { return String::EndsWithPathSep(GetCentralFileHeader().GetFileName()); }
};

//-----------------------------------------------------------------------------
// StatExList
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE StatExList : public std::vector<StatEx*> {
public:
	StatEx* FindByName(const char* fileName) const;
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
// Directory_ZIPFile
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_ZIPFile : public Directory {
private:
	RefPtr<StatEx> _pStatEx;
public:
	Directory_ZIPFile(StatEx* pStatEx) :
		Directory(Directory::Type::Item,
				  PathName::SepPlatform, PathName::CaseFlagPlatform), _pStatEx(pStatEx) {}
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoCreateStatValue() override;
};

//-----------------------------------------------------------------------------
// Directory_ZIPFolder
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Directory_ZIPFolder : public Directory_CustomContainer {
private:
	RefPtr<StatEx> _pStatEx;
public:
	Directory_ZIPFolder(StatEx* pStatEx) :
		Directory_CustomContainer(Directory::Type::Container,
								  PathName::SepPlatform, PathName::CaseFlagPlatform), _pStatEx(pStatEx) {}
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value* DoCreateStatValue() override;
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
	virtual bool Initialize() = 0;
	virtual const char* GetName() const override { return _name.c_str(); }
	virtual const char* GetIdentifier() const override { return _name.c_str(); }
	virtual size_t DoWrite(const void* buff, size_t len) override { return 0; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoClose() override { return true; }
	virtual size_t DoGetSize() override { return _bytesUncompressed; }
	virtual Value* DoCreateStatValue() override;
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
