//==============================================================================
// Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
bool Content::Read(Stream& stream)
{
	if (!ReadHeader(stream)) return false;
	UInt32 biWidth = Gurax_UnpackUInt32(_bih.biWidth);
	UInt32 biHeight = Gurax_UnpackUInt32(_bih.biHeight);
	UInt16 biBitCount = Gurax_UnpackUInt16(_bih.biBitCount);
	size_t bytes = ImageMgrEx::CalcDIBImageSize(biWidth, biHeight, biBitCount, false);
	_pMemory.reset(new MemoryHeap(bytes));
	if (stream.Read(_pMemory->GetPointerC<void>(), bytes) < bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	return true;
}

bool Content::Write(Stream& stream) const
{
	if (!WriteHeader(stream)) {
		IssueError_FailToWrite();
		return false;
	}
	const Memory* pMemory = GetMemory();
	if (pMemory && !stream.Write(pMemory->GetPointerC<void>(), pMemory->GetBytes())) {
		IssueError_FailToWrite();
		return false;
	}
	return true;
}

bool Content::ReadHeader(Stream& stream)
{
	if (stream.Read(&_bfh, BitmapFileHeader::bytes) < BitmapFileHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (stream.Read(&_bih, BitmapInfoHeader::bytes) < BitmapInfoHeader::bytes) {
		IssueError_InvalidFormat();
		return false;
	}
	if (Gurax_UnpackUInt16(_bfh.bfType) != 0x4d42) {
		IssueError_InvalidFormat();
		return false;
	}
	return true;
}

bool Content::WriteHeader(Stream& stream) const
{
	if (!stream.Write(&_bfh, BitmapFileHeader::bytes)) {
		IssueError_FailToWrite();
		return false;
	}
	if (!stream.Write(&_bih, BitmapInfoHeader::bytes)) {
		IssueError_FailToWrite();
		return false;
	}
	return true;
}

String Content::ToString(const StringStyle& ss) const
{
	return "bmp.Content";
}

Gurax_EndModuleScope(bmp)
