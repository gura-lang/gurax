//==============================================================================
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
	str.Format("Pointer:%s:%s:%d", GetName(), _elemType.pSymbol->GetName(), GetOffset());
	if (bytesEntire != static_cast<size_t>(-1)) str.Format("/%d", bytesEntire);
	str.Format("byte");
	return str;
}

}
