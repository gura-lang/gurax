//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_CURL_PATHEXTENSION_H
#define GURAX_MODULE_CURL_PATHEXTENSION_H
#include <gurax.h>

Gurax_BeginModuleScope(curl)
	
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

#if 0
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
#endif

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
class DirectoryEx : public Directory {
public:
	class CoreEx : public Core {
	public:
		Gurax_DeclareReferable(CoreEx);
	public:
		CoreEx(Type type) :
			Core(type, PathName::SepPlatform, PathName::CaseFlagPlatform, new CoreOwner()) {}
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
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value_Stat* DoCreateStatValue() override;
};

Gurax_EndModuleScope(curl)

#endif
