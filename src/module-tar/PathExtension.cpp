//==============================================================================
// PathExtention.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return pDirectoryParent && //!pDirectoryParent->IsFolder() &&
		(String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".tar") ||
		 String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".tar.gz") ||
		 String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".tgz") ||
		 String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".tar.bz2"));
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe)
{
	const char* pathName = *pPathName;
	if (!pDirectoryParent) return nullptr;
	RefPtr<Stream> pStream(pDirectoryParent->OpenStream(Stream::OpenFlag::Read));
	if (!pStream) return nullptr;
	pStream.reset(pStream->CreateBwdSeekable());
	if (!pStream) return nullptr;
	RefPtr<Directory> pDirectory(DirectoryEx::CreateTop(*pStream));
	if (!pDirectory) return nullptr;
	pDirectory->SetDirectoryParent(Directory::Reference(pDirectoryParent));
	Directory* pDirectoryFound = (**pPathName == '\0')? pDirectory.get() : pDirectory->SearchInTree(pPathName);
	if (!pDirectoryFound) {
		Error::Issue(ErrorType::PathError, "specified path is not found: %s", pathName);
		return nullptr;
	}
	return pDirectoryFound->Reference();
}

PathMgr::Existence PathMgrEx::DoCheckExistence(Directory* pDirectoryParent, const char** pPathName)
{
#if 0
	RefPtr<Directory> pDirectory(DoOpenDirectory(pDirectoryParent, pPathName, Directory::Type::None));
	Error::Clear();
	return pDirectory? Existence::Exist : Existence::None;
#endif
	return Existence::None;
}

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
StatEx::StatEx(Header* pHeader) :
	Stat(pHeader->GetMTime().Reference(), pHeader->GetName(),
		 pHeader->IsFolder()? Flag::Dir : Flag::Reg,
		 pHeader->GetMode(), pHeader->GetSize(), pHeader->GetUid(), pHeader->GetGid()),
	_pHeader(pHeader)
{
}

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":tar";
	return str;
}

//------------------------------------------------------------------------------
// StatExList
//------------------------------------------------------------------------------
StatEx* StatExList::FindByName(const char* fileName) const
{
	PathName pathName(fileName);
	for (StatEx* pStatEx : *this) {
		if (pathName.DoesMatch(pStatEx->GetHeader().GetFileName())) return pStatEx;
	}
	return nullptr;
}

bool StatExList::Write(Stream& streamDst) const
{
	for (StatEx* pStatEx : *this) {
		if (!pStatEx->GetHeader().Write(streamDst)) return false;
	}
	return true;
}

//------------------------------------------------------------------------------
// StatExOwner
//------------------------------------------------------------------------------
void StatExOwner::Clear()
{
	for (StatEx* pStatEx : *this) StatEx::Delete(pStatEx);
	clear();
}

bool StatExOwner::ReadDirectory(Stream& streamSrc)
{
	std::unique_ptr<char []> buffBlock(new char [BLOCKSIZE]);
	int nTerminator = 0;
	for (;;) {
		size_t bytesRead = streamSrc.Read(buffBlock.get(), BLOCKSIZE);
		if (Error::IsIssued()) return false;
		if (bytesRead < BLOCKSIZE) {
			Error::Issue(ErrorType::FormatError, "failed to read a block");
			return false;
		}
		bool zeroBlockFlag = true;
		UInt32* p = reinterpret_cast<UInt32 *>(buffBlock.get());
		for (int i = 0; i < BLOCKSIZE / sizeof(UInt32); i++, p++) {
			if (*p != 0x00000000) {
				zeroBlockFlag = false;
				break;
			}
		}
		if (zeroBlockFlag) {
			nTerminator++;
			if (nTerminator == 2) break;
			continue;
		}
		nTerminator = 0;
		star_header& hdrRaw = *reinterpret_cast<star_header *>(buffBlock.get());
		std::unique_ptr<Header> pHeader(new Header());
		if (!pHeader->SetRawHeader(hdrRaw)) return nullptr;
		pHeader->SetOffset(streamSrc.GetOffset());
		streamSrc.Seek(pHeader->CalcBlocks() * BLOCKSIZE, Stream::SeekMode::Cur);
		push_back(new StatEx(pHeader.release()));
	}
	return true;
}

//-----------------------------------------------------------------------------
// DirectoryEx
//-----------------------------------------------------------------------------
Directory* DirectoryEx::CreateTop(Stream& streamSrc)
{
	RefPtr<DirectoryEx> pDirectoryEx(
		new DirectoryEx(new CoreEx(Type::Boundary, streamSrc.Reference(), nullptr)));
	return pDirectoryEx->ReadDirectory()? pDirectoryEx.release() : nullptr;
}

bool DirectoryEx::ReadDirectory()
{
	StatExOwner statExOwner;
	if (!statExOwner.ReadDirectory(GetStreamSrc())) return false;
	for (StatEx* pStatEx : statExOwner) {
		const char* pathName = pStatEx->GetHeader().GetName();
		Type type = (pStatEx->GetHeader().GetTypeFlag() == DIRTYPE)? Type::Folder : Type::Item;
		GetCoreEx().AddChildInTree(pathName, new CoreEx(type, GetStreamSrc().Reference(), pStatEx->Reference()));
		//pStatEx->GetCentralFileHeader().Print(*Stream::COut);
	}
	return true;
}

void DirectoryEx::DoRewindChild()
{
	_idxChild = 0;
}

Directory* DirectoryEx::DoNextChild()
{
	CoreOwner& coreOwner = GetCoreEx().GetCoreOwner();
	if (_idxChild >= coreOwner.size()) return nullptr;
	RefPtr<Directory> pDirectory(new DirectoryEx(dynamic_cast<CoreEx*>(coreOwner[_idxChild++]->Reference())));
	pDirectory->SetDirectoryParent(Reference());
	return pDirectory.release();
}

Stream* DirectoryEx::DoOpenStream(Stream::OpenFlags openFlags)
{
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) return nullptr;
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? Stream_Reader::Create(GetStreamSrc(), *pStatEx) : nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
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
	streamSrc.SetOffset(statEx.GetHeader().GetOffset());
	return new Stream_Reader(streamSrc.Reference(), statEx.Reference());
}

#if 0
size_t Stream_Reader::CheckCRC32(const void* buff, size_t bytesRead)
{
	if (_seekedFlag) return bytesRead;
	_crc32.Update(buff, bytesRead);
	if (bytesRead == 0 && _crc32Expected != _crc32.GetResult()) {
		Error::Issue(ErrorType::FormatError, "CRC error");
		return 0;
	}
	return bytesRead;
}
#endif

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
	return new Value_StatEx(_pStatEx.Reference());
}

Gurax_EndModuleScope(tar)
