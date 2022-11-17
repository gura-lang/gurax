//==============================================================================
// PathExtension.h
//==============================================================================
#ifndef GURAX_MODULE_MTP_PATHEXTENSION_H
#define GURAX_MODULE_MTP_PATHEXTENSION_H
#include <gurax.h>
#include "Device.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StatEx : public Stat {
public:
	// Referable declaration
	Gurax_DeclareReferable(StatEx);
public:
	StatEx(DateTime* pDateTimeC, DateTime* pDateTimeM, DateTime* pDateTimeA,
		String fileName, UInt32 flags, size_t fileSize);
public:
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const;
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
		RefPtr<Device> _pDevice;
		StringW _objectID;
		RefPtr<StatEx> _pStat;
	public:
		CoreEx(Device* pDevice, Type type, StringW objectID, StatEx* pStat) : 
			Core(type, pStat->GetName(), '/', true, new CoreOwner()), _pDevice(pDevice), _objectID(objectID), _pStat(pStat) {}
		Device& GetDevice() { return *_pDevice; }
		LPCWSTR GetObjectID() const { return _objectID.c_str(); }
		StatEx& GetStat() const { return *_pStat; }
	public:
		bool Initialize();
		virtual Directory* GenerateDirectory() override;
	};
public:
	Gurax_DeclareReferable(DirectoryEx);
private:
	CComPtr<IEnumPortableDeviceObjectIDs> _pEnumPortableDeviceObjectIDs;
	struct {
		LPWSTR objectIDs[32];
		DWORD nObjectIDs;
		DWORD iObjectID;
		bool lastFlag;
	} _browse;
public:
	DirectoryEx(CoreEx* pCore, DirectoryEx* pDirectoryParent);
	~DirectoryEx();
public:
	static DirectoryEx* Create(DirectoryEx* pDirectoryParent, LPCWSTR objectID);
	CoreEx& GetCoreEx() { return dynamic_cast<CoreEx&>(*_pCore); }
	Device& GetDevice() { return GetCoreEx().GetDevice(); }
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
	virtual Stream* DoOpenStream(Stream::OpenFlags openFlags) override;
	virtual Value_Stat* DoCreateStatValue() override;
protected:
	void DestroyBrowse();
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

Gurax_EndModuleScope(mtp)

#endif
