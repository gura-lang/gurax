//==============================================================================
// BasicPointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer_String
//------------------------------------------------------------------------------
Pointer_String::Pointer_String(StringReferable* pString, size_t offset) : Pointer(offset), _pString(pString)
{
}

Pointer_String::Pointer_String(const Pointer_String& src) :
	Pointer_String(src._pString->Reference(), src._offset)
{
}

const UInt8* Pointer_String::ExtractPrepare(size_t bytes)
{
	const String& String = GetStringSTL();
	if (_offset + bytes <= String.size()) {
		const UInt8* p = reinterpret_cast<const UInt8*>(String.data() + _offset);
		_offset += bytes;
		return p;
	}
	return nullptr;
}

const void* Pointer_String::DoGetPointerC() const
{
	return GetStringSTL().data() + _offset;
}

void* Pointer_String::DoGetWritablePointerC() const
{
	return nullptr;
}

size_t Pointer_String::GetBytesEntire() const
{
	return GetStringSTL().size();
}

bool Pointer_String::IsWritable() const
{
	return false;
}

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

const void* Pointer_Binary::DoGetPointerC() const
{
	return GetBinary().data() + _offset;
}

void* Pointer_Binary::DoGetWritablePointerC() const
{
	return nullptr;
}

size_t Pointer_Binary::GetBytesEntire() const
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
	return _offset + bytes <= GetMemory().GetBytes();
}

void Pointer_Memory::StoreBuffer(const void* buff, size_t bytes)
{
	size_t offsetNext = _offset + bytes;
	if (buff) ::memcpy(GetMemory().GetPointerC<char>(_offset), buff, bytes);
	_offset = offsetNext;
}

const UInt8* Pointer_Memory::ExtractPrepare(size_t bytes)
{
	if (_offset + bytes > GetMemory().GetBytes()) return nullptr;
	const UInt8* p = GetMemory().GetPointerC<UInt8>(_offset);
	_offset += bytes;
	return p;
}

const void* Pointer_Memory::DoGetPointerC() const
{
	return GetMemory().GetPointerC<UInt8>(_offset);
}

void* Pointer_Memory::DoGetWritablePointerC() const
{
	return GetMemory().GetPointerC<UInt8>(_offset);
}

size_t Pointer_Memory::GetBytesEntire() const
{
	return GetMemory().GetBytes();
}

bool Pointer_Memory::IsWritable() const
{
	return true;
}

}
