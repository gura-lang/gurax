//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
template<typename T> bool PutFunc_T(Packer& packer, const Value& value, bool bigEndianFlag, bool forwardFlag)
{
	if (!packer.StorePrepare(sizeof(T))) return false;
	if (bigEndianFlag) {
		packer.Store<T, true>(Value_Number::GetNumber<T>(value), forwardFlag);
	} else {
		packer.Store<T, false>(Value_Number::GetNumber<T>(value), forwardFlag);
	}
	return true;
}

template<typename T> bool GetFunc_T(Packer& packer, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag)
{
	const UInt8* pByte = packer.ExtractPrepare(sizeof(T), forwardFlag);
	if (!pByte) {
		if (exceedErrorFlag) Error::Issue(ErrorType::RangeError, "exceeds the range");
		return false;
	}
	pValue.reset(new Value_Number(bigEndianFlag? packer.Extract<T, true>(pByte) : packer.Extract<T, false>(pByte)));
	return true;
}

Pointer::ElemType Pointer::ElemType::None;
Pointer::ElemType Pointer::ElemType::Int8;
Pointer::ElemType Pointer::ElemType::UInt8;
Pointer::ElemType Pointer::ElemType::Int16;
Pointer::ElemType Pointer::ElemType::UInt16;
Pointer::ElemType Pointer::ElemType::Int32;
Pointer::ElemType Pointer::ElemType::UInt32;
Pointer::ElemType Pointer::ElemType::Int64;
Pointer::ElemType Pointer::ElemType::UInt64;
Pointer::ElemType Pointer::ElemType::Float;
Pointer::ElemType Pointer::ElemType::Double;

void Pointer::Bootup()
{
	Pointer::ElemType::Int8.putFunc		= PutFunc_T<Int8>;
	Pointer::ElemType::Int8.getFunc		= GetFunc_T<Int8>;
	Pointer::ElemType::UInt8.putFunc	= PutFunc_T<UInt8>;
	Pointer::ElemType::UInt8.getFunc	= GetFunc_T<UInt8>;
	Pointer::ElemType::Int16.putFunc	= PutFunc_T<Int16>;
	Pointer::ElemType::Int16.getFunc	= GetFunc_T<Int16>;
	Pointer::ElemType::UInt16.putFunc	= PutFunc_T<UInt16>;
	Pointer::ElemType::UInt16.getFunc	= GetFunc_T<UInt16>;
	Pointer::ElemType::Int32.putFunc	= PutFunc_T<Int32>;
	Pointer::ElemType::Int32.getFunc	= GetFunc_T<Int32>;
	Pointer::ElemType::UInt32.putFunc	= PutFunc_T<UInt32>;
	Pointer::ElemType::UInt32.getFunc	= GetFunc_T<UInt32>;
	Pointer::ElemType::Int64.putFunc	= PutFunc_T<Int64>;
	Pointer::ElemType::Int64.getFunc	= GetFunc_T<Int64>;
	Pointer::ElemType::UInt64.putFunc	= PutFunc_T<UInt64>;
	Pointer::ElemType::UInt64.getFunc	= GetFunc_T<UInt64>;
	Pointer::ElemType::Float.putFunc	= PutFunc_T<Float>;
	Pointer::ElemType::Float.getFunc	= GetFunc_T<Float>;
	Pointer::ElemType::Double.putFunc	= PutFunc_T<Double>;
	Pointer::ElemType::Double.getFunc	= GetFunc_T<Double>;
}

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
	bool forwardFlag = true;
	if (value.IsType(VTYPE_Number)) {
		return elemType.putFunc(*this, value, bigEndianFlag, forwardFlag);
	} else if (value.IsType(VTYPE_Iterator)) {
		return PutValues(elemType, bigEndianFlag, Value_Iterator::GetIterator(value));
	} else if (value.IsType(VTYPE_List)) {
		return PutValues(elemType, bigEndianFlag, Value_List::GetValueOwner(value));
	} else {
		Error::Issue(ErrorType::TypeError, "invalid value type");
		return false;
	}
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
