//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_PATHEXTENSION_H
#define GURAX_MODULE_CURL_PATHEXTENSION_H
#include <gurax.h>

Gurax_BeginModuleScope(curl)
	
#if 0
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
		Type GetType() const { return _type; }
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

#endif

Gurax_EndModuleScope(curl)

#endif
