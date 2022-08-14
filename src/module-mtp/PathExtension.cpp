//==============================================================================
// PathExtention.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mtp)

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
/*
StatEx::StatEx(Header* pHeader) :
	Stat(pHeader->GetMTime().Reference(), PathName(pHeader->GetName()).ExtractBottomName(),
		 pHeader->IsFolder()? Flag::Dir : Flag::Reg,
		 pHeader->GetMode(), pHeader->GetSize(), pHeader->GetUid(), pHeader->GetGid()),
	_pHeader(pHeader)
{
}
*/
StatEx::StatEx(String fileName, size_t fileSize, DateTime* dtModification, bool folderFlag) :	
	Stat(nullptr, "", Flag::Reg, 0, 0, 0, 0)
{
}

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":mtp";
	return str;
}

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
DirectoryEx::DirectoryEx(CoreEx* pCore, DirectoryEx* pDirectoryParent) :
	Directory(pCore), _pDirectoryParent(pDirectoryParent)
{
	_browse.nObjectIDs = 0;
	_browse.iObjectID = 0;
	_browse.lastFlag = false;
}

DirectoryEx::~DirectoryEx()
{
	DestroyBrowse();
}

DirectoryEx* DirectoryEx::Create(DirectoryEx* pDirectoryParent, LPCWSTR objectID)
{
	IPortableDeviceProperties* pPortableDeviceProperties = pDirectoryParent->GetDevice().GetPortableDeviceProperties();
	IPortableDeviceKeyCollection* pPortableDeviceKeyCollection = pDirectoryParent->GetDevice().GetPortableDeviceKeyCollection();
	CComPtr<IPortableDeviceValues> pPortableDeviceValues;
	if (FAILED(pPortableDeviceProperties->GetValues(
		objectID, pPortableDeviceKeyCollection, &pPortableDeviceValues))) return nullptr;
	String fileName;
	do { // WPD_OBJECT_ORIGINAL_FILE_NAME: VT_LPWSTR
		LPWSTR value = nullptr;
		if (FAILED(pPortableDeviceValues->
				GetStringValue(WPD_OBJECT_ORIGINAL_FILE_NAME, &value))) return nullptr;
		fileName = WSTRToString(value);
		::CoTaskMemFree(value);
	} while (0);
	bool folderFlag = false;
	const Symbol *pFileType = Symbol::Empty;
	do { // WPD_OBJECT_CONTENT_TYPE: VT_CLSID
		GUID value;
		if (FAILED(pPortableDeviceValues->
				GetGuidValue(WPD_OBJECT_CONTENT_TYPE, &value))) return nullptr;
		folderFlag = IsEqualGUID(value, WPD_CONTENT_TYPE_FOLDER);
	} while (0);
	size_t fileSize = 0;
	do { // WPD_OBJECT_SIZE: VT_UI8
		ULONGLONG value = 0;
		if (FAILED(pPortableDeviceValues->
				GetUnsignedLargeIntegerValue(WPD_OBJECT_SIZE, &value))) return false;
		fileSize = static_cast<size_t>(value);
	} while (0);
	RefPtr<DateTime> pDateTimeC;
	do { // WPD_OBJECT_DATE_MODIFIED: VT_DATE
		PROPVARIANT value;
		if (FAILED(pPortableDeviceValues->
				GetValue(WPD_OBJECT_DATE_CREATED, &value))) return false;
		COleDateTime oleDateTime(value.date);
		SYSTEMTIME st;
		oleDateTime.GetAsSystemTime(st);
		pDateTimeC.reset(OAL::CreateDateTime(st, OAL::GetSecsOffsetTZ()));
	} while (0);
	RefPtr<DateTime> pDateTimeM;
	do { // WPD_OBJECT_DATE_MODIFIED: VT_DATE
		PROPVARIANT value;
		if (FAILED(pPortableDeviceValues->
				GetValue(WPD_OBJECT_DATE_MODIFIED, &value))) return false;
		COleDateTime oleDateTime(value.date);
		SYSTEMTIME st;
		oleDateTime.GetAsSystemTime(st);
		pDateTimeM.reset(OAL::CreateDateTime(st, OAL::GetSecsOffsetTZ()));
	} while (0);
	RefPtr<DateTime> pDateTimeA(pDateTimeM.Reference());
	RefPtr<CoreEx> pCore;
	return new DirectoryEx(pCore.release(), pDirectoryParent);
}

void DirectoryEx::DoRewindChild()
{
	::printf("DoRewindChild()\n");
	//_idxChild = 0;
}

Directory* DirectoryEx::DoNextChild()
{
	::printf("DoNextChild()\n");
	IPortableDeviceContent* pPortableDeviceContent = GetCoreEx().GetDevice().GetPortableDeviceContent();
	if (_browse.iObjectID >= _browse.nObjectIDs) {
		DestroyBrowse();
		if (_browse.lastFlag) return nullptr;
		if (!_pEnumPortableDeviceObjectIDs) {
			if (FAILED(pPortableDeviceContent->EnumObjects(
				0, GetCoreEx().GetObjectID(), nullptr, &_pEnumPortableDeviceObjectIDs))) return nullptr;
		}
		HRESULT hr = _pEnumPortableDeviceObjectIDs->Next(
				Gurax_ArraySizeOf(_browse.objectIDs), _browse.objectIDs, &_browse.nObjectIDs);
		if (hr != S_OK) _browse.lastFlag = true;
		if (_browse.nObjectIDs == 0) return nullptr;
	}
	LPWSTR objectID = _browse.objectIDs[_browse.iObjectID++];
	return DirectoryEx::Create(Reference(), objectID);
}

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
	::printf("DoOpenStream()\n");
#if 0
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) return nullptr;
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? Stream_Reader::Create(GetStreamSrc(), *pStatEx) : nullptr;
#endif
	return nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	::printf("DoCreateStatValue()\n");
	//StatEx* pStatEx = GetCoreEx().GetStatEx();
	//return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
	return nullptr;
}

void DirectoryEx::DestroyBrowse()
{
	for (DWORD i = 0; i < _browse.nObjectIDs; i++) {
		::CoTaskMemFree(_browse.objectIDs[i]);
	}
	_browse.nObjectIDs = 0;
	_browse.iObjectID = 0;
}

//-----------------------------------------------------------------------------
// DirectoryEx::CoreEx
//-----------------------------------------------------------------------------
bool DirectoryEx::CoreEx::Initialize()
{
	return true;
}

Directory* DirectoryEx::CoreEx::GenerateDirectory()
{
	//return new DirectoryEx(Reference());
	return nullptr;
}

//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
Stream_Reader::Stream_Reader(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _pStatEx(pStatEx),
	_offsetTop(pStreamSrc->GetOffset())
{
}

Stream* Stream_Reader::Create(Stream& streamSrc, const StatEx& statEx)
{
	//streamSrc.SetOffset(statEx.GetHeader().GetOffset());
	//return new Stream_Reader(streamSrc.Reference(), statEx.Reference());
	return nullptr;
}

size_t Stream_Reader::DoRead(void* buff, size_t bytes)
{
	size_t bytesRest = _pStatEx->GetBytes() - (_pStreamSrc->GetOffset() - _offsetTop);
	if (bytes > bytesRest) bytes = bytesRest;
	size_t bytesRead = _pStreamSrc->Read(buff, bytes);
	return bytesRead;
}

bool Stream_Reader::DoSeek(size_t offset, size_t offsetPrev)
{
	return _pStreamSrc->SetOffset(_offsetTop + offset);
}

Value_Stat* Stream_Reader::DoCreateStatValue()
{
	//return new Value_StatEx(_pStatEx.Reference());
	return nullptr;
}

Gurax_EndModuleScope(mtp)
