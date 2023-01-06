//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_PATHEXTENSION_H
#define GURAX_MODULE_TAR_PATHEXTENSION_H
#include <gurax.h>
#include "TARFormat.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
class PathMgrEx : public PathMgr {
public:
	PathMgrEx() : PathMgr("tar") {}
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
	std::unique_ptr<Header> _pHeader;
public:
	StatEx(Header* pHeader);
public:
	Header& GetHeader() { return *_pHeader; }
	const Header& GetHeader() const { return *_pHeader; }
	bool IsDir() const { return GetHeader().GetTypeFlag() == Header::DIRTYPE; }
public:
	static StatEx* ReadDirectory(Stream& streamSrc);
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//-----------------------------------------------------------------------------
// StatExList
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE StatExList : public ListBase<StatEx*> {
};

//-----------------------------------------------------------------------------
// StatExOwner
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE StatExOwner : public StatExList {
public:
	~StatExOwner() { Clear(); }
	void Clear();
	bool ReadDirectory(Stream& streamSrc);
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
			Core(type, '/', true, new CoreOwner()), _pStreamSrc(pStreamSrc), _pStatEx(pStatEx) {}
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
	bool ReadDirectory();
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
	size_t _offsetTop;
public:
	Stream_Reader(Stream* pStreamSrc, StatEx* pStatEx);
public:
	static Stream* Create(Stream& streamSrc, const StatEx& statEx);
public:
	virtual const char* GetName() const override { return _pStatEx->GetName(); }
	virtual const char* GetIdentifier() const override { return _pStatEx->GetName(); }
	virtual size_t DoRead(void* buff, size_t bytes) override;
	virtual bool DoSeek(size_t offset, size_t offsetPrev) override;
	virtual bool DoWrite(const void* buff, size_t len) override { return false; }
	virtual bool DoFlush() override { return false; }
	virtual bool DoClose() override { return true; }
	virtual size_t DoGetBytes() override { return _pStatEx->GetBytes(); }
	virtual Value_Stat* DoCreateStatValue() override;
};

Gurax_EndModuleScope(tar)

#endif
