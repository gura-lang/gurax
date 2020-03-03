//==============================================================================
// Pointers.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer_Binary
//------------------------------------------------------------------------------
Pointer_Binary::Pointer_Binary(BinaryReferable* pBinary, size_t offset) : Pointer(offset), _pBinary(pBinary)
{
}

Pointer_Binary::Pointer_Binary(const Pointer_Binary& src) :
	Pointer_Binary(src._pBinary->Reference(), src._offset)
{
}

bool Pointer_Binary::StorePrepare(size_t bytes)
{
	return GetBinary().CheckWritable();
}

void Pointer_Binary::StoreBuffer(const void* buff, size_t bytes)
{
	size_t offsetNext = _offset + bytes;
	if (buff) {
		Binary& binary = GetBinary();
		const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
		if (_offset < binary.size()) {
			size_t bytesRest = binary.size() - _offset;
			binary.replace(_offset, std::min(bytesRest, bytes), buffp, bytes);
		} else {
			if (_offset > binary.size()) binary.append(_offset - binary.size(), '\0');
			binary.append(buffp, buffp + bytes);
		}
	}
	_offset = offsetNext;
}

const UInt8* Pointer_Binary::ExtractPrepare(size_t bytes)
{
	Binary& binary = GetBinary();
	if (_offset + bytes <= binary.size()) {
		const UInt8* p = reinterpret_cast<const UInt8*>(binary.data() + _offset);
		_offset += bytes;
		return p;
	}
	return nullptr;
}

const UInt8* Pointer_Binary::GetPointerC() const
{
	return GetBinary().data() + _offset;
}

UInt8* Pointer_Binary::GetWritablePointerC() const
{
	return nullptr;
}

size_t Pointer_Binary::GetSizeEntire() const
{
	return GetBinary().size();
}

bool Pointer_Binary::IsWritable() const
{
	return GetBinary().IsWritable();
}

//------------------------------------------------------------------------------
// Pointer_Memory
//------------------------------------------------------------------------------
Pointer_Memory::Pointer_Memory(Memory* pMemory, size_t offset) : Pointer(offset), _pMemory(pMemory)
{
}

Pointer_Memory::Pointer_Memory(const Pointer_Memory& src) :
	Pointer_Memory(src._pMemory->Reference(), src._offset)
{
}

bool Pointer_Memory::StorePrepare(size_t bytes)
{
	return _offset + bytes <= GetMemory().GetSize();
}

void Pointer_Memory::StoreBuffer(const void* buff, size_t bytes)
{
	size_t offsetNext = _offset + bytes;
	if (buff) ::memcpy(GetMemory().GetPointer<char>(_offset), buff, bytes);
	_offset = offsetNext;
}

const UInt8* Pointer_Memory::ExtractPrepare(size_t bytes)
{
	if (_offset + bytes > GetMemory().GetSize()) return nullptr;
	const UInt8* p = GetMemory().GetPointer<UInt8>(_offset);
	_offset += bytes;
	return p;
}

const UInt8* Pointer_Memory::GetPointerC() const
{
	return GetMemory().GetPointer<UInt8>(_offset);
}

UInt8* Pointer_Memory::GetWritablePointerC() const
{
	return GetMemory().GetPointer<UInt8>(_offset);
}

size_t Pointer_Memory::GetSizeEntire() const
{
	return GetMemory().GetSize();
}

bool Pointer_Memory::IsWritable() const
{
	return true;
}

}
