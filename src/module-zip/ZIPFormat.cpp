//==============================================================================
// ZIPFormat.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

//-----------------------------------------------------------------------------
// Stream_reader
//-----------------------------------------------------------------------------
Stream_reader::Stream_reader(Stream* pStreamSrc, const CentralFileHeader& hdr) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _hdr(hdr),
	_name(hdr.GetFileName()), _bytesUncompressed(hdr.GetUncompressedSize()),
	_bytesCompressed(hdr.GetCompressedSize()), _crc32Expected(hdr.GetCrc32()),
	_seekedFlag(false)
{
}

size_t Stream_reader::CheckCRC32(const void* buff, size_t bytesRead)
{
	if (_seekedFlag) return bytesRead;
	_crc32.Update(buff, bytesRead);
	if (bytesRead == 0 && _crc32Expected != _crc32.GetResult()) {
		Error::Issue(ErrorType::FormatError, "CRC error");
		return 0;
	}
	return bytesRead;
}

//-----------------------------------------------------------------------------
// Stream_reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
Stream_reader_Store::Stream_reader_Store(Stream* pStreamSrc, const CentralFileHeader& hdr) :
	Stream_reader(pStreamSrc, hdr)
{
}

bool Stream_reader_Store::Initialize()
{
	return false;
}
	
size_t Stream_reader_Store::DoRead(void* buff, size_t bytes)
{
	size_t bytesRest = _bytesUncompressed - (_pStreamSrc->GetOffset() - _offsetTop);
	if (bytes > bytesRest) bytes = bytesRest;
	size_t bytesRead = _pStreamSrc->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_reader_Store::DoSeek(size_t offset, size_t offsetPrev)
{
	return _pStreamSrc->Seek(_offsetTop + offset, SeekMode::Set);
}

//-----------------------------------------------------------------------------
// Stream_reader_Deflate
// Compression method #8: Deflated
//-----------------------------------------------------------------------------
Stream_reader_Deflate::Stream_reader_Deflate(Stream* pStreamSrc, const CentralFileHeader& hdr) :
	Stream_reader(pStreamSrc, hdr)
{
}

bool Stream_reader_Deflate::Initialize()
{
	_pStreamReader.reset(new ZLib::Stream_Reader(_pStreamSrc->Reference(), _bytesCompressed));
	return _pStreamReader->Initialize(-MAX_WBITS);
}
	
size_t Stream_reader_Deflate::DoRead(void* buff, size_t bytes)
{
	size_t bytesRead = _pStreamReader->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_reader_Deflate::DoSeek(size_t offset, size_t offsetPrev)
{
	_seekedFlag = true;
	return _pStreamReader->Seek(offset, SeekMode::Set);
}

//-----------------------------------------------------------------------------
// Stream_reader_BZIP2
// Compression method #12: BZIP2
//-----------------------------------------------------------------------------
Stream_reader_BZIP2::Stream_reader_BZIP2(Stream* pStreamSrc, const CentralFileHeader& hdr) :
	Stream_reader(pStreamSrc, hdr)
{
}

bool Stream_reader_BZIP2::Initialize()
{
	_pStreamReader.reset(new BZLib::Stream_Reader(_pStreamSrc->Reference(), _bytesCompressed));
	int verbosity = 0, small = 0;
	return _pStreamReader->Initialize(verbosity, small);
}
	
size_t Stream_reader_BZIP2::DoRead(void* buff, size_t bytes)
{
	size_t bytesRead = _pStreamReader->Read(buff, bytes);
	return CheckCRC32(buff, bytesRead);
}

bool Stream_reader_BZIP2::DoSeek(size_t offset, size_t offsetPrev)
{
	_seekedFlag = true;
	return _pStreamReader->Seek(offset, SeekMode::Set);
}

//-----------------------------------------------------------------------------
// Stream_reader_Deflate64
// Compression method #9: Enhanced Deflating using Deflate64(tm)
//-----------------------------------------------------------------------------
Stream_reader_Deflate64::Stream_reader_Deflate64(Stream* pStreamSrc, const CentralFileHeader& hdr) :
	Stream_reader(pStreamSrc, hdr)
{
}

bool Stream_reader_Deflate64::Initialize()
{
	Error::Issue(ErrorType::UnimplementedError, "this compression method is not implemented yet");
	return false;
}
	
size_t Stream_reader_Deflate64::DoRead(void* buff, size_t bytes)
{
	return 0;
}

bool Stream_reader_Deflate64::DoSeek(size_t offset, size_t offsetPrev)
{
	return false;
}

//-----------------------------------------------------------------------------
// Directory_ZIPFile
//-----------------------------------------------------------------------------
Directory* Directory_ZIPFile::DoNextChild()
{
	return nullptr;
}

Stream* Directory_ZIPFile::DoOpenStream(Stream::OpenFlags openFlags)
{
	return nullptr;
}

Value* Directory_ZIPFile::DoGetStatValue()
{
	return nullptr;
}

//-----------------------------------------------------------------------------
// Directory_ZIPFolder
//-----------------------------------------------------------------------------
Stream* Directory_ZIPFolder::DoOpenStream(Stream::OpenFlags openFlags)
{
	return nullptr;
}

Value* Directory_ZIPFolder::DoGetStatValue()
{
	return nullptr;
}

Gurax_EndModuleScope(zip)
