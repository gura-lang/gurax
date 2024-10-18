//==============================================================================
// Memory
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Memory
//------------------------------------------------------------------------------
Memory* Memory::Empty = nullptr;

void Memory::Bootup()
{
	//static char* buff = "";
	Empty = new MemorySloth(0, new char[1]);
}

String Memory::MakeId() const
{
	return String().Format("%p", _buff);
}

bool Memory::Serialize(Stream& stream) const
{
	size_t bytes = GetBytes();
	if (!stream.SerializePackedNumber<UInt64>(bytes)) return false;
	return stream.Write(GetPointerC<void>(), bytes);
}

Memory* Memory::Deserialize(Stream& stream)
{
	const char* errMsg = "invalid format of serialized memory";
	size_t bytes = 0;
	if (!stream.DeserializePackedNumber<size_t>(bytes)) return nullptr;
	if (bytes == 0) return new MemoryHeap(1);
	RefPtr<Memory> pMemory(new MemoryHeap(bytes));
	if (stream.Read(pMemory->GetPointerC<void>(), bytes) != bytes) {
		Error::Issue(ErrorType::FormatError, errMsg);
		return nullptr;
	}
	return pMemory.release();
}

//------------------------------------------------------------------------------
// MemoryOwner
//------------------------------------------------------------------------------
MemoryOwner::~MemoryOwner()
{
	Clear();
}

void MemoryOwner::Clear()
{
	for (Memory* pMemory : *this) Memory::Delete(pMemory);
	clear();
}

//------------------------------------------------------------------------------
// MemorySloth
//------------------------------------------------------------------------------
Memory* MemorySloth::Clone() const
{
	return new MemorySloth(_bytes, _buff);
}

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// MemoryHeap
//------------------------------------------------------------------------------
MemoryHeap::MemoryHeap(size_t bytes)
{
	_bytes = bytes;
	_buff = reinterpret_cast<char*>(::LocalAlloc(LMEM_FIXED, _bytes));
}

MemoryHeap::~MemoryHeap()
{
	::LocalFree(_buff);
}

Memory* MemoryHeap::Clone() const
{
	void* buff = ::LocalAlloc(LMEM_FIXED, _bytes);
	if (buff == nullptr) return nullptr;
	::memcpy(buff, _buff, _bytes);
	return new MemoryHeap(_bytes, buff);
}

//------------------------------------------------------------------------------
// MemoryDIB
//------------------------------------------------------------------------------
MemoryDIB::MemoryDIB() : _hBitmap(nullptr)
{
}

MemoryDIB::~MemoryDIB()
{
	if (_hBitmap != nullptr) ::DeleteObject(_hBitmap);
}

bool MemoryDIB::AllocBuffer(size_t width, size_t height, size_t bitsPerPixel)
{
	BITMAPINFO bmi;
	BITMAPINFOHEADER& hdr = bmi.bmiHeader;
	::memset(&bmi, 0, sizeof(BITMAPINFO));
	hdr.biSize = sizeof(BITMAPINFOHEADER);
	hdr.biWidth = static_cast<int>(width);
	hdr.biHeight = -static_cast<int>(height);
	hdr.biPlanes = 1;
	hdr.biBitCount = static_cast<WORD>(bitsPerPixel);
	hdr.biCompression = BI_RGB;
	hdr.biSizeImage = 0;
	hdr.biXPelsPerMeter = 0;
	hdr.biYPelsPerMeter = 0;
	hdr.biClrUsed = 0;
	hdr.biClrImportant = 0;
	void* buff = nullptr;
	_hBitmap = ::CreateDIBSection(nullptr, &bmi, DIB_RGB_COLORS, &buff, nullptr, 0);
	_buff = reinterpret_cast<char*>(buff);
	_bytes = ((bitsPerPixel + 7) / 8 * width + 3) / 4 * 4;
	return _hBitmap != nullptr && _buff != nullptr;
}

Memory* MemoryDIB::Clone() const
{
	return nullptr;
}

#else

//------------------------------------------------------------------------------
// MemoryHeap
//------------------------------------------------------------------------------
MemoryHeap::MemoryHeap(size_t bytes)
{
	_bytes = bytes;
	_buff = reinterpret_cast<char*>(::malloc(_bytes));
}

MemoryHeap::~MemoryHeap()
{
	::free(_buff);
}

Memory* MemoryHeap::Clone() const
{
	void* buff = ::malloc(_bytes);
	if (buff == nullptr) return nullptr;
	::memcpy(buff, _buff, _bytes);
	return new MemoryHeap(_bytes, buff);
}

#endif

}
