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
		}
		nTerminator = 0;
		star_header& hdrRaw = *reinterpret_cast<star_header *>(buffBlock.get());
		std::unique_ptr<Header> pHdr(new Header());
		pHdr->SetOffset(streamSrc.GetOffset());
		if (!pHdr->SetRawHeader(hdrRaw)) return nullptr;
		push_back(new StatEx(pHdr.release()));
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
#if 0
	for (StatEx* pStatEx : statExOwner) {
		const char* pathName = pStatEx->GetCentralFileHeader().GetFileName();
		Type type = String::EndsWithPathSep(pathName)? Type::Folder : Type::Item;
		GetCoreEx().AddChildInTree(pathName, new CoreEx(type, GetStreamSrc().Reference(), pStatEx->Reference()));
		//pStatEx->GetCentralFileHeader().Print(*Stream::COut);
	}
	//GetCoreEx().Print(*Stream::COut);
#endif
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
#if 0
	if (openFlags & (Stream::OpenFlag::Write | Stream::OpenFlag::Append)) return nullptr;
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? Stream_Reader::Create(GetStreamSrc(), *pStatEx) : nullptr;
#endif
	return nullptr;
}

Value_Stat* DirectoryEx::DoCreateStatValue()
{
#if 0
	StatEx* pStatEx = GetCoreEx().GetStatEx();
	return pStatEx? new Value_StatEx(pStatEx->Reference()) : nullptr;
#endif
	return nullptr;
}

#if 0
//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
Stream_Reader::Stream_Reader(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _pStatEx(pStatEx),
	_name(pStatEx->GetCentralFileHeader().GetFileName()),
	_bytesUncompressed(pStatEx->GetCentralFileHeader().GetUncompressedSize()),
	_bytesCompressed(pStatEx->GetCentralFileHeader().GetCompressedSize()),
	_crc32Expected(pStatEx->GetCentralFileHeader().GetCrc32()),
	_seekedFlag(false)
{
}

Stream* Stream_Reader::Create(Stream& streamSrc, const StatEx& statEx)
{
	const CentralFileHeader& hdr = statEx.GetCentralFileHeader();
	size_t offset = hdr.GetRelativeOffsetOfLocalHeader();
	streamSrc.SetOffset(offset);
	if (Error::IsIssued()) return nullptr;
	do {
		UInt32 signature;
		if (!ReadStream(streamSrc, &signature)) return nullptr;
		if (signature != LocalFileHeader::Signature) {
			Error::Issue(ErrorType::FormatError, "invalid ZIP format");
			return nullptr;
		}
		LocalFileHeader hdr;
		if (!hdr.Read(streamSrc)) return nullptr;
	} while (0);
	UInt16 compressionMethod = hdr.GetCompressionMethod();
	RefPtr<Stream_Reader> pStream;
	if (compressionMethod == CompressionMethod::Store) {
		pStream.reset(new Stream_Reader_Store(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::Shrink) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor1) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor2) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor3) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor4) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Implode) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Factor1) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::Deflate) {
		pStream.reset(new Stream_Reader_Deflate(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::Deflate64) {
		pStream.reset(new Stream_Reader_Deflate64(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::PKWARE) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::BZIP2) {
		pStream.reset(new Stream_Reader_BZIP2(streamSrc.Reference(), statEx.Reference()));
	} else if (compressionMethod == CompressionMethod::LZMA) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::TERSA) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::LZ77) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::WavPack) {
		// unsupported
	} else if (compressionMethod == CompressionMethod::PPMd) {
		// unsupported
	}
	if (!pStream) {
		Error::Issue(ErrorType::FormatError, "unsupported compression method %d", compressionMethod);
		return nullptr;
	}
	if (!pStream->Initialize()) return nullptr;
	return pStream.release();
}

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

Value_Stat* Stream_Reader::DoCreateStatValue()
{
	return new Value_StatEx(_pStatEx->Reference());
}

//-----------------------------------------------------------------------------
// Stream_Reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
Stream_Reader_Store::Stream_Reader_Store(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream_Reader(pStreamSrc, pStatEx), _offsetTop(pStreamSrc->GetOffset())
{
}

bool Stream_Reader_Store::Initialize()
{
	return true;
}
	
size_t Stream_Reader_Store::DoRead(void* buff, size_t bytes)
{
	size_t bytesRest = _bytesUncompressed - (_pStreamSrc->GetOffset() - _offsetTop);
	if (bytes > bytesRest) bytes = bytesRest;
	size_t bytesRead = _pStreamSrc->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_Reader_Store::DoSeek(size_t offset, size_t offsetPrev)
{
	return _pStreamSrc->SetOffset(_offsetTop + offset);
}

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate
// Compression method #8: Deflated
//-----------------------------------------------------------------------------
Stream_Reader_Deflate::Stream_Reader_Deflate(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream_Reader(pStreamSrc, pStatEx)
{
}

bool Stream_Reader_Deflate::Initialize()
{
	_pStreamReader.reset(new ZLib::Stream_Reader(_pStreamSrc->Reference(), _bytesCompressed));
	return _pStreamReader->Initialize(-MAX_WBITS);
}
	
size_t Stream_Reader_Deflate::DoRead(void* buff, size_t bytes)
{
	size_t bytesRead = _pStreamReader->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_Reader_Deflate::DoSeek(size_t offset, size_t offsetPrev)
{
	_seekedFlag = true;
	return _pStreamReader->SetOffset(offset);
}

//-----------------------------------------------------------------------------
// Stream_Reader_BZIP2
// Compression method #12: BZIP2
//-----------------------------------------------------------------------------
Stream_Reader_BZIP2::Stream_Reader_BZIP2(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream_Reader(pStreamSrc, pStatEx)
{
}

bool Stream_Reader_BZIP2::Initialize()
{
	_pStreamReader.reset(new BZLib::Stream_Reader(_pStreamSrc->Reference(), _bytesCompressed));
	int verbosity = 0, small = 0;
	return _pStreamReader->Initialize(verbosity, small);
}
	
size_t Stream_Reader_BZIP2::DoRead(void* buff, size_t bytes)
{
	size_t bytesRead = _pStreamReader->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_Reader_BZIP2::DoSeek(size_t offset, size_t offsetPrev)
{
	_seekedFlag = true;
	return _pStreamReader->SetOffset(offset);
}

//-----------------------------------------------------------------------------
// Stream_Reader_Deflate64
// Compression method #9: Enhanced Deflating using Deflate64(tm)
//-----------------------------------------------------------------------------
Stream_Reader_Deflate64::Stream_Reader_Deflate64(Stream* pStreamSrc, StatEx* pStatEx) :
	Stream_Reader(pStreamSrc, pStatEx)
{
}

bool Stream_Reader_Deflate64::Initialize()
{
	Error::Issue(ErrorType::UnimplementedError, "this compression method is not implemented yet");
	return false;
}
	
size_t Stream_Reader_Deflate64::DoRead(void* buff, size_t bytes)
{
	return 0;
}

bool Stream_Reader_Deflate64::DoSeek(size_t offset, size_t offsetPrev)
{
	return false;
}
#endif

Gurax_EndModuleScope(tar)
