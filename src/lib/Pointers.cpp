//==============================================================================
// Pointers.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer_Binary
//------------------------------------------------------------------------------
Pointer_Binary::Pointer_Binary(size_t offset, Value_Binary* pValue) : Pointer(offset), _pValue(pValue)
{
}

Pointer_Binary::Pointer_Binary(const Pointer_Binary& src) : Pointer_Binary(src._offset, src._pValue->Reference())
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

}
