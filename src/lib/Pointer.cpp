//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"

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

bool Pointer::PutValue(ElemType elemType, const Value& value)
{
	
	return false;
}

bool Pointer::PutValues(ElemType elemType, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		if (!PutValue(elemType, *pValue)) return false;
	}
	return false;
}

bool Pointer::PutValueStay(ElemType elemType, const Value& value)
{
	return false;
}

bool Pointer::PutValuesStay(ElemType elemType, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		if (!PutValueStay(elemType, *pValue)) return false;
	}
	return false;
}

bool Pointer::CheckWritable() const
{
	if (IsWritable()) return true;
	Error::Issue(ErrorType::AccessError, "the pointer is not writable");
	return false;
}

String Pointer::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("Pointer:offset=%d", GetOffset());
	return str;
}

}
