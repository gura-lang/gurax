//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
const Pointer::ElemType Pointer::ElemType::None(ElemTypeId::None);
const Pointer::ElemType Pointer::ElemType::Int8(ElemTypeId::Int8);
const Pointer::ElemType Pointer::ElemType::UInt8(ElemTypeId::UInt8);
const Pointer::ElemType Pointer::ElemType::Int16(ElemTypeId::Int16);
const Pointer::ElemType Pointer::ElemType::UInt16(ElemTypeId::UInt16);
const Pointer::ElemType Pointer::ElemType::Int32(ElemTypeId::Int32);
const Pointer::ElemType Pointer::ElemType::UInt32(ElemTypeId::UInt32);
const Pointer::ElemType Pointer::ElemType::Int64(ElemTypeId::Int64);
const Pointer::ElemType Pointer::ElemType::UInt64(ElemTypeId::UInt64);
const Pointer::ElemType Pointer::ElemType::Float(ElemTypeId::Float);
const Pointer::ElemType Pointer::ElemType::Double(ElemTypeId::Double);

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

bool Pointer::PutValue(const ElemType& elemType, bool bigEndianFlag, const Value& value)
{
	if (value.IsType(VTYPE_Number)) {
		switch (elemType.id) {
		case ElemTypeId::Int8:
			return bigEndianFlag?
				Put<Int8, true>(Value_Number::GetNumber<Int8>(value), true) :
				Put<Int8, false>(Value_Number::GetNumber<Int8>(value), true);
		case ElemTypeId::UInt8:
			return bigEndianFlag?
				Put<UInt8, true>(Value_Number::GetNumber<UInt8>(value), true) :
				Put<UInt8, false>(Value_Number::GetNumber<UInt8>(value), true);
		case ElemTypeId::Int16:
			return bigEndianFlag?
				Put<Int16, true>(Value_Number::GetNumber<Int16>(value), true) :
				Put<Int16, false>(Value_Number::GetNumber<Int16>(value), true);
		case ElemTypeId::UInt16:
			return bigEndianFlag?
				Put<UInt16, true>(Value_Number::GetNumber<UInt16>(value), true) :
				Put<UInt16, false>(Value_Number::GetNumber<UInt16>(value), true);
		case ElemTypeId::Int32:
			return bigEndianFlag?
				Put<Int32, true>(Value_Number::GetNumber<Int32>(value), true) :
				Put<Int32, false>(Value_Number::GetNumber<Int32>(value), true);
		case ElemTypeId::UInt32:
			return bigEndianFlag?
				Put<UInt32, true>(Value_Number::GetNumber<UInt32>(value), true) :
				Put<UInt32, false>(Value_Number::GetNumber<UInt32>(value), true);
		case ElemTypeId::Int64:
			return bigEndianFlag?
				Put<Int64, true>(Value_Number::GetNumber<Int64>(value), true) :
				Put<Int64, false>(Value_Number::GetNumber<Int64>(value), true);
		case ElemTypeId::UInt64:
			return bigEndianFlag?
				Put<UInt64, true>(Value_Number::GetNumber<UInt64>(value), true) :
				Put<UInt64, false>(Value_Number::GetNumber<UInt64>(value), true);
		case ElemTypeId::Float:
			return bigEndianFlag?
				Put<Float, true>(Value_Number::GetNumber<Float>(value), true) :
				Put<Float, false>(Value_Number::GetNumber<Float>(value), true);
		case ElemTypeId::Double:
			return bigEndianFlag?
				Put<Double, true>(Value_Number::GetNumber<Double>(value), true) :
				Put<Double, false>(Value_Number::GetNumber<Double>(value), true);
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

bool Pointer::PutValues(const ElemType& elemType, bool bigEndianFlag, const ValueList& valList)
{
	for (const Value* pValue : valList) {
		if (!PutValue(elemType, bigEndianFlag, *pValue)) return false;
	}
	return true;
}

bool Pointer::PutValues(const ElemType& elemType, bool bigEndianFlag, Iterator& iterator)
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

const Pointer::ElemType& Pointer::SymbolToElemType(const Symbol* pSymbol)
{
	return
		pSymbol->IsIdentical(Gurax_Symbol(int8))? 		ElemType::Int8 :
		pSymbol->IsIdentical(Gurax_Symbol(uint8))? 		ElemType::UInt8 :
		pSymbol->IsIdentical(Gurax_Symbol(int16))? 		ElemType::Int16 :
		pSymbol->IsIdentical(Gurax_Symbol(uint16))? 	ElemType::UInt16 :
		pSymbol->IsIdentical(Gurax_Symbol(int32))? 		ElemType::Int32 :
		pSymbol->IsIdentical(Gurax_Symbol(uint32))? 	ElemType::UInt32 :
		pSymbol->IsIdentical(Gurax_Symbol(int64))? 		ElemType::Int64 :
		pSymbol->IsIdentical(Gurax_Symbol(uint64))? 	ElemType::UInt64 :
		pSymbol->IsIdentical(Gurax_Symbol(float_))? 	ElemType::Float :
		pSymbol->IsIdentical(Gurax_Symbol(double_))?	ElemType::Double :
		ElemType::None;
}

}
