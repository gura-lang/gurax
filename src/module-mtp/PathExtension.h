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
private:
	//std::unique_ptr<Header> _pHeader;
public:
	StatEx();
public:
	//Header& GetHeader() { return *_pHeader; }
	//const Header& GetHeader() const { return *_pHeader; }
	//bool IsDir() const { return GetHeader().GetTypeFlag() == Header::DIRTYPE; }
public:
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
	bool ReadDirectory(Device& device);
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
		String _fileName;
		StringW _objectID;
		RefPtr<Device> _pDevice;
		CComPtr<IPortableDeviceKeyCollection> _pPortableDeviceKeyCollection;
	public:
		CoreEx(Type type, String fileName, StringW objectID, Device* pDevice) : 
			Core(type, '/', true, new CoreOwner()), _fileName(fileName), _objectID(objectID), _pDevice(pDevice) {}
		Device& GetDevice() { return *_pDevice; }
	public:
		bool Initialize();
		virtual Directory* GenerateDirectory() override;
	};
private:
	RefPtr<DirectoryEx> _pDirectoryParent;
public:
	//DirectoryEx(CoreEx* pCoreEx) : Directory(pCoreEx) {}
	DirectoryEx(DirectoryEx* pDirectoryParent, String fileName, Directory::Type type,
		Device* pDevice, StringW objectID) :
		Directory(new CoreEx(type, fileName, objectID, pDevice)),
		_pDirectoryParent(pDirectoryParent) {}
public:
	static Directory* CreateTop(Device* pDevice);
	CoreEx& GetCoreEx() { return dynamic_cast<CoreEx&>(*_pCore); }
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

Gurax_EndModuleScope(mtp)

#endif
