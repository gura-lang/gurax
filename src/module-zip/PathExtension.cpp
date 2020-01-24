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
	return pDirectoryParent && !pDirectoryParent->IsContainer() &&
		(String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".zip") ||
		 String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".gurc") ||
		 String::EndsWith<CharICase>(pDirectoryParent->GetName(), ".gurcw"));
}

Directory* PathMgrEx::DoOpenDirectory(Directory* pDirectoryParent, const char** pPathName, Directory::Type typeWouldBe)
{
	if (!pDirectoryParent) return nullptr;
	RefPtr<Stream> pStream(pDirectoryParent->OpenStream(Stream::OpenFlag::Read));
	if (!pStream) return nullptr;
	pStream.reset(pStream->CreateBwdSeekable());
	if (!pStream) return nullptr;
	RefPtr<Directory> pDirectory(CreateTopDirectory(*pStream));
	if (!pDirectory) return nullptr;
	pDirectory->SetDirectoryParent(*pDirectoryParent);

	return pDirectory.release();
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
	Stat(pCentralFileHeader->MakeLastModDateTime(), pCentralFileHeader->GetFileName(),
		 pCentralFileHeader->IsFolder()? Flag::Dir : Flag::Reg,
		 0666, pCentralFileHeader->GetUncompressedSize(), 0, 0),
	_pCentralFileHeader(pCentralFileHeader)
{
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
	if (!streamSrc.Seek(offsetCentralDirectory, Stream::SeekMode::Set)) return false;
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
// Directory_ZIPFile
//-----------------------------------------------------------------------------
Stream* Directory_ZIPFile::DoOpenStream(Stream::OpenFlags openFlags)
{
	return nullptr;
}

Value* Directory_ZIPFile::DoCreateStatValue()
{
	return new Value_StatEx(_pStatEx.Reference());
}

//-----------------------------------------------------------------------------
// Directory_ZIPFolder
//-----------------------------------------------------------------------------
Value* Directory_ZIPFolder::DoCreateStatValue()
{
	return new Value_StatEx(_pStatEx.Reference());
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

Value* Stream_Reader::DoCreateStatValue()
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
	return _pStreamSrc->Seek(_offsetTop + offset, SeekMode::Set);
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
	return _pStreamReader->Seek(offset, SeekMode::Set);
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
	return _pStreamReader->Seek(offset, SeekMode::Set);
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
