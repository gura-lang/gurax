//==============================================================================
// PathExtention.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// PathMgrEx
//------------------------------------------------------------------------------
bool PathMgrEx::IsResponsible(Directory* pDirectoryParent, const char* pathName)
{
	return pDirectoryParent && //!pDirectoryParent->IsFolder() &&
		(String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".zip") ||
		String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".gurc") ||
		String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".gurcw"));
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
	RefPtr<Directory> pDirectory(DoOpenDirectory(pDirectoryParent, pPathName, Directory::Type::None));
	Error::Clear();
	return pDirectory? Existence::Exist : Existence::None;
}

//------------------------------------------------------------------------------
// StatEx
//------------------------------------------------------------------------------
StatEx::StatEx(CentralFileHeader* pCentralFileHeader) :
	Stat(pCentralFileHeader->MakeLastModDateTime(),
		PathName(pCentralFileHeader->GetFileName()).ExtractBottomName(),
		pCentralFileHeader->IsFolder()? Flag::Dir : Flag::Reg,
		0666, pCentralFileHeader->GetUncompressedSize(), 0, 0),
	_pCentralFileHeader(pCentralFileHeader)
{
}

String StatEx::ToString(const StringStyle& ss) const
{
	String str = Stat::ToString(ss);
	str += ":zip";
	str += ":";
	const Symbol* pSymbol = CompressionMethodToSymbol(_pCentralFileHeader->GetCompressionMethod());
	str += pSymbol->GetName();
	return str;
}

//------------------------------------------------------------------------------
// StatExList
//------------------------------------------------------------------------------
StatEx* StatExList::FindByName(const char* fileName) const
{
	PathName pathName(fileName);
	for (StatEx* pStatEx : *this) {
		if (pathName.DoesMatch(pStatEx->GetCentralFileHeader().GetFileName())) return pStatEx;
	}
	return nullptr;
}

bool StatExList::Write(Stream& streamDst) const
{
	for (StatEx* pStatEx : *this) {
		if (!pStatEx->GetCentralFileHeader().Write(streamDst)) return false;
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

bool StatExOwner::ReadCentralDirectory(Stream& streamSrc)
{
	UInt32 offsetCentralDirectory = SeekCentralDirectory(streamSrc);
	if (Error::IsIssued()) return false;
	if (!streamSrc.SetOffset(offsetCentralDirectory)) return false;
	UInt32 signature;
	while (ReadStream(streamSrc, &signature)) {
		//::printf("%08x\n", signature);
		if (signature == LocalFileHeader::Signature) {
			LocalFileHeader hdr;
			if (!hdr.Read(streamSrc)) return false;
			if (!hdr.SkipFileData(streamSrc)) return false;
		} else if (signature == ArchiveExtraDataRecord::Signature) {
			ArchiveExtraDataRecord record;
			if (!record.Read(streamSrc)) return false;
		} else if (signature == CentralFileHeader::Signature) {
			std::unique_ptr<CentralFileHeader> pCentralFileHeader(new CentralFileHeader());
			if (!pCentralFileHeader->Read(streamSrc)) return false;
			push_back(new StatEx(pCentralFileHeader.release()));
		} else if (signature == DigitalSignature::Signature) {
			DigitalSignature signature;
			if (!signature.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectory::Signature) {
			Zip64EndOfCentralDirectory dir;
			if (!dir.Read(streamSrc)) return false;
		} else if (signature == Zip64EndOfCentralDirectoryLocator::Signature) {
			Zip64EndOfCentralDirectoryLocator loc;
			if (!loc.Read(streamSrc)) return false;
		} else if (signature == EndOfCentralDirectoryRecord::Signature) {
			EndOfCentralDirectoryRecord record;
			if (!record.Read(streamSrc)) return false;
			break;
		} else {
			Error::Issue(ErrorType::FormatError, "unknown signature %08x", signature);
			return false;
		}
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
	return pDirectoryEx->ReadCentralDirectory()? pDirectoryEx.release() : nullptr;
}

bool DirectoryEx::ReadCentralDirectory()
{
	StatExOwner statExOwner;
	if (!statExOwner.ReadCentralDirectory(GetStreamSrc())) return false;
	for (StatEx* pStatEx : statExOwner) {
		const char* pathName = pStatEx->GetCentralFileHeader().GetFileName();
		Type type = String::EndsWithPathSep(pathName)? Type::Folder : Type::Item;
		GetCoreEx().AddChildInTree(pathName, new CoreEx(type, GetStreamSrc().Reference(), pStatEx->Reference()));
		//pStatEx->GetCentralFileHeader().Print(*Stream::COut);
	}
	//GetCoreEx().Print(*Stream::COut);
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
	RefPtr<Directory> pDirectory(coreOwner[_idxChild]->GenerateDirectory());
	_idxChild++;
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

Gurax_EndModuleScope(zip)
