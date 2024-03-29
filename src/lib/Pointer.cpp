﻿//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
void Pointer::Bootup()
{
}

bool Pointer::AdvanceByByte(int distance)
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
	if (value.IsType(VTYPE_Iterator)) {
		return PutValues(elemType, bigEndianFlag, Value_Iterator::GetIterator(value));
	} else if (value.IsType(VTYPE_List)) {
		return PutValues(elemType, bigEndianFlag, Value_List::GetValueOwner(value));
	}
	bool forwardFlag = true;
	return elemType.putFunc(*this, value, bigEndianFlag, forwardFlag);
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
	if (bytesEntire == static_cast<size_t>(-1)) {
		str.Format("Pointer:%s:%s:%dbyte", GetName(), _elemType.pSymbol->GetName(), GetOffset());
	} else {
		str.Format("Pointer:%s:%s:%d/%dbytes", GetName(), _elemType.pSymbol->GetName(), GetOffset(), bytesEntire);
	}
	return str;
}

}
