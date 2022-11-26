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

bool Pointer::PutValue(ElemType elemType, bool bigEndianFlag, const Value& value)
{
	if (value.IsType(VTYPE_Number)) {
		switch (elemType) {
		case Pointer::ElemType::Int8:
			return bigEndianFlag?
				Put<Int8, true>(Value_Number::GetNumber<Int8>(value)) :
				Put<Int8, false>(Value_Number::GetNumber<Int8>(value));
		case Pointer::ElemType::UInt8:
			return bigEndianFlag?
				Put<UInt8, true>(Value_Number::GetNumber<UInt8>(value)) :
				Put<UInt8, false>(Value_Number::GetNumber<UInt8>(value));
		case Pointer::ElemType::Int16:
			return bigEndianFlag?
				Put<Int16, true>(Value_Number::GetNumber<Int16>(value)) :
				Put<Int16, false>(Value_Number::GetNumber<Int16>(value));
		case Pointer::ElemType::UInt16:
			return bigEndianFlag?
				Put<UInt16, true>(Value_Number::GetNumber<UInt16>(value)) :
				Put<UInt16, false>(Value_Number::GetNumber<UInt16>(value));
		case Pointer::ElemType::Int32:
			return bigEndianFlag?
				Put<Int32, true>(Value_Number::GetNumber<Int32>(value)) :
				Put<Int32, false>(Value_Number::GetNumber<Int32>(value));
		case Pointer::ElemType::UInt32:
			return bigEndianFlag?
				Put<UInt32, true>(Value_Number::GetNumber<UInt32>(value)) :
				Put<UInt32, false>(Value_Number::GetNumber<UInt32>(value));
		case Pointer::ElemType::Int64:
			return bigEndianFlag?
				Put<Int64, true>(Value_Number::GetNumber<Int64>(value)) :
				Put<Int64, false>(Value_Number::GetNumber<Int64>(value));
		case Pointer::ElemType::UInt64:
			return bigEndianFlag?
				Put<UInt64, true>(Value_Number::GetNumber<UInt64>(value)) :
				Put<UInt64, false>(Value_Number::GetNumber<UInt64>(value));
		case Pointer::ElemType::Float:
			return bigEndianFlag?
				Put<Float, true>(Value_Number::GetNumber<Float>(value)) :
				Put<Float, false>(Value_Number::GetNumber<Float>(value));
		case Pointer::ElemType::Double:
			return bigEndianFlag?
				Put<Double, true>(Value_Number::GetNumber<Double>(value)) :
				Put<Double, false>(Value_Number::GetNumber<Double>(value));
		default:
			break;
		}
	} else if (value.IsType(VTYPE_Iterator)) {
		return PutValues(elemType, bigEndianFlag, Value_Iterator::GetIterator(value));
	} else if (value.IsType(VTYPE_List)) {
		return PutValues(elemType, bigEndianFlag, Value_List::GetValueOwner(value));
	} else {
		Error::Issue(ErrorType::TypeError, "invalid type");
		return false;
	}
	return true;
}

bool Pointer::PutValues(ElemType elemType, bool bigEndianFlag, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		if (!PutValue(elemType, bigEndianFlag, *pValue)) return false;
	}
	return true;
}

bool Pointer::PutValues(ElemType elemType, bool bigEndianFlag, Iterator& iterator)
{
	for (;;) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (!PutValue(elemType, bigEndianFlag, *pValue)) return false;
	}
	return !Error::IsIssued();
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
	size_t bytesEntire = GetBytesEntire();
	str.Format("Pointer:%s:%d", GetName(), GetOffset());
	if (bytesEntire != static_cast<size_t>(-1)) str.Format("/%d", bytesEntire);
	return str;
}

}
