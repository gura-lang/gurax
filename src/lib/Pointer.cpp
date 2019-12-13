//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/Pointer.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
bool Pointer::Advance(int distance)
{
	if (distance >= 0) {
		_offset += distance;
		return true;
	}
	if (_offset >= static_cast<size_t>(-distance)) {
		_offset += distance;
		return true;
	}
	Error::Issue(ErrorType::RangeError, "pointer offset is out of range");
	return false;
}

bool Pointer::PackStay(const char* format, const ValueList& valListArg)
{
	size_t offset = _offset;
	if (!Pack(format, valListArg)) return false;
	_offset = offset;
	return true;
}

Value* Pointer::UnpackStay(const char* format, const ValueList& valListArg, bool exceedErrorFlag)
{
	size_t offset = _offset;
	RefPtr<Value> pValue(Unpack(format, valListArg, exceedErrorFlag));
	_offset = offset;
	return pValue.release();
}

String Pointer::ToString(const StringStyle& ss) const
{
	return "Pointer";
}

//------------------------------------------------------------------------------
// Pointer_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer_Binary : public Pointer {
protected:
	RefPtr<Value_Binary> _pValue;
public:
	Pointer_Binary(size_t offset, Value_Binary* pValue);
	Pointer_Binary(const Pointer_Binary& src);
	Value_Binary& GetValue() { return *_pValue; }
	const Value_Binary& GetValue() const { return *_pValue; }
	Binary& GetBinary() { return _pValue->GetBinary(); }
	const Binary& GetBinary() const { return _pValue->GetBinary(); }
public:
	// Virtual functions of Packer
	virtual bool StorePrepare(size_t bytes) override;
	virtual void StoreBuffer(const void* buff, size_t bytes) override;
	virtual const UInt8* ExtractPrepare(size_t bytes) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Binary(*this); }
	virtual const Value& GetTarget() const override { return *_pValue; }
	virtual const UInt8* GetPointerC() const override;
	virtual UInt8* GetWritablePointerC() const override;
	virtual size_t GetEntireSize() const override;
	virtual bool IsWritable() const override;
};

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
	//if (!GetBinary().IsWritable()) {
	//	Error::Issue(ErrorType::ValueError, "not a writable binary");
	//	return false;
	//}
	return true;
}

void Pointer_Binary::StoreBuffer(const void* buff, size_t bytes)
{
	size_t offsetNext = _offset + bytes;
	if (buff) {
		Binary& binary = GetBinary();
		const UInt8* buffp = reinterpret_cast<const UInt8*>(buff);
		if (_offset < binary.size()) {
			size_t bytesToCopy = std::min(binary.size() - _offset, bytes);
			std::copy(buffp, buffp + bytesToCopy, binary.begin() + _offset);
			buffp += bytesToCopy;
			bytes -= bytesToCopy;
		} else if (_offset > binary.size()) {
			binary.append(_offset - binary.size(), '\0');
		}
		binary.append(buffp, buffp + bytes);
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

size_t Pointer_Binary::GetEntireSize() const
{
	return GetBinary().size();
}

bool Pointer_Binary::IsWritable() const
{
	//return _pObjBinary->IsWritable();
	return true;
}

}
