//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_PATHEXTENSION_H
#define GURAX_MODULE_TAR_PATHEXTENSION_H
#include <gurax.h>
#include "TARFormat.h"

Gurax_BeginModuleScope(tar)
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
#endif

Gurax_EndModuleScope(tar)

#endif
