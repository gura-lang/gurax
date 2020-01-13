//==============================================================================
// ZIPFormat.cpp
//==============================================================================
#include "stdafx.h"
#include "ZIPFormat.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
Gurax_RealizeSymbol(store);
Gurax_RealizeSymbol(shrink);
Gurax_RealizeSymbol(factor1);
Gurax_RealizeSymbol(factor2);
Gurax_RealizeSymbol(factor3);
Gurax_RealizeSymbol(factor4);
Gurax_RealizeSymbol(implode);
Gurax_RealizeSymbol(deflate);
Gurax_RealizeSymbol(deflate64);
Gurax_RealizeSymbol(pkware);
Gurax_RealizeSymbol(bzip2);
Gurax_RealizeSymbol(lzma);
Gurax_RealizeSymbol(tersa);
Gurax_RealizeSymbol(lz77);
Gurax_RealizeSymbol(wavpack);
Gurax_RealizeSymbol(ppmd);

//-----------------------------------------------------------------------------
// Stream_Reader
//-----------------------------------------------------------------------------
Stream_Reader::Stream_Reader(Stream* pStreamSrc, CentralFileHeader* pHdr) :
	Stream(Flag::Readable), _pStreamSrc(pStreamSrc), _pHdr(pHdr),
	_name(pHdr->GetFileName()), _bytesUncompressed(pHdr->GetUncompressedSize()),
	_bytesCompressed(pHdr->GetCompressedSize()), _crc32Expected(pHdr->GetCrc32()),
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

//-----------------------------------------------------------------------------
// Stream_Reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
Stream_Reader_Store::Stream_Reader_Store(Stream* pStreamSrc, CentralFileHeader* pHdr) :
	Stream_Reader(pStreamSrc, pHdr)
{
}

bool Stream_Reader_Store::Initialize()
{
	return false;
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
Stream_Reader_Deflate::Stream_Reader_Deflate(Stream* pStreamSrc, CentralFileHeader* pHdr) :
	Stream_Reader(pStreamSrc, pHdr)
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
Stream_Reader_BZIP2::Stream_Reader_BZIP2(Stream* pStreamSrc, CentralFileHeader* pHdr) :
	Stream_Reader(pStreamSrc, pHdr)
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
Stream_Reader_Deflate64::Stream_Reader_Deflate64(Stream* pStreamSrc, CentralFileHeader* pHdr) :
	Stream_Reader(pStreamSrc, pHdr)
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
	return new Value_Stat(_pHdr->Reference());
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
	return new Value_Stat(_pHdr->Reference());
}

Gurax_EndModuleScope(zip)
