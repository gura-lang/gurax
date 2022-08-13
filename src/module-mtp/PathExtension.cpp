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
StatEx::StatEx() : Stat(nullptr, "", Flag::Reg, 0, 0, 0, 0)
{
}

#if 0
StatEx* StatEx::ReadDirectory(Stream& streamSrc)
{
#if 0
	std::unique_ptr<Header> pHeader(new Header());
	char buffBlock[Header::BLOCKSIZE];
	int nTerminator = 0;
	for (;;) {
		size_t bytesRead = streamSrc.Read(buffBlock, Header::BLOCKSIZE);
		if (Error::IsIssued()) return nullptr;
		if (bytesRead < Header::BLOCKSIZE) return nullptr;
		bool zeroBlockFlag = true;
		UInt32* p = reinterpret_cast<UInt32 *>(buffBlock);
		for (int i = 0; i < Header::BLOCKSIZE / sizeof(UInt32); i++, p++) {
			if (*p != 0x00000000) {
				zeroBlockFlag = false;
				break;
			}
		}
		if (!zeroBlockFlag) break;
		nTerminator++;
		if (nTerminator == 2) return nullptr;
	}
	star_header& hdrRaw = *reinterpret_cast<star_header *>(buffBlock);
	if (!pHeader->SetRawHeader(hdrRaw)) return nullptr;
	pHeader->SetOffset(streamSrc.GetOffset());
	return new StatEx(pHeader.release());
#endif
	return nullptr;
}
#endif

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":mtp";
	return str;
}

//------------------------------------------------------------------------------
// StatExList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StatExOwner
//------------------------------------------------------------------------------
void StatExOwner::Clear()
{
	for (StatEx* pStatEx : *this) StatEx::Delete(pStatEx);
	clear();
}

bool StatExOwner::ReadDirectory(Device& device)
{
#if 0
	for (;;) {
		RefPtr<StatEx> pStatEx(StatEx::ReadDirectory(streamSrc));
		if (!pStatEx) break;
		streamSrc.Seek(pStatEx->GetHeader().CalcBlocks() * Header::BLOCKSIZE, Stream::SeekMode::Cur);
		push_back(pStatEx.release());
	}
	return !Error::IsIssued();
#endif
	return false;
}

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
bool DirectoryEx::ReadDirectory()
{
	StatExOwner statExOwner;
	if (!statExOwner.ReadDirectory(GetCoreEx().GetDevice())) return false;
	for (StatEx* pStatEx : statExOwner) {
		//const char* pathName = pStatEx->GetHeader().GetName();
		Type type = pStatEx->IsDir()? Type::Folder : Type::Item;
		//GetCoreEx().AddChildInTree(pathName, new CoreEx(type, GetStreamSrc().Reference(), pStatEx->Reference()));
	}
	return true;
}

void DirectoryEx::DoRewindChild()
{
	//_idxChild = 0;
}

Directory* DirectoryEx::DoNextChild()
{
#if 0
	CoreOwner& coreOwner = GetCoreEx().GetCoreOwner();
	if (_idxChild >= coreOwner.size()) return nullptr;
	RefPtr<Directory> pDirectory(coreOwner[_idxChild]->GenerateDirectory());
	_idxChild++;
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
#endif
	return nullptr;
}

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
#if 0
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) return nullptr;
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? Stream_Reader::Create(GetStreamSrc(), *pStatEx) : nullptr;
#endif
	return nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	//StatEx* pStatEx = GetCoreEx().GetStatEx();
	//return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
	return nullptr;
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
