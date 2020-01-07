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
	return 0;
}

//-----------------------------------------------------------------------------
// Stream_reader_Store
// Compression method #0: stored (no compression)
//-----------------------------------------------------------------------------
bool Stream_reader_Store::Initialize()
{
	return false;
}
	
size_t Stream_reader_Store::DoRead(void* buff, size_t bytes)
{
	return 0;
}

bool Stream_reader_Store::DoSeek(size_t offset, size_t offsetPrev)
{
	return false;
}

//-----------------------------------------------------------------------------
// Stream_reader_Deflate
// Compression method #8: Deflated
//-----------------------------------------------------------------------------
bool Stream_reader_Deflate::Initialize()
{
	return false;
}
	
size_t Stream_reader_Deflate::DoRead(void* buff, size_t bytes)
{
	return 0;
}

bool Stream_reader_Deflate::DoSeek(size_t offset, size_t offsetPrev)
{
	return false;
}

//-----------------------------------------------------------------------------
// Stream_reader_BZIP2
// Compression method #12: BZIP2
//-----------------------------------------------------------------------------
bool Stream_reader_BZIP2::Initialize()
{
	return false;
}
	
size_t Stream_reader_BZIP2::DoRead(void* buff, size_t bytes)
{
	return 0;
}

bool Stream_reader_BZIP2::DoSeek(size_t offset, size_t offsetPrev)
{
	return false;
}

//-----------------------------------------------------------------------------
// Stream_reader_Deflate64
// Compression method #9: Enhanced Deflating using Deflate64(tm)
//-----------------------------------------------------------------------------
bool Stream_reader_Deflate64::Initialize()
{
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

Gurax_EndModuleScope(zip)
