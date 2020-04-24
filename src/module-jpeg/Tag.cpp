//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
	_typeId(typeId), _tagId(tagId), _pSymbol(pSymbol), _pValue(pValue), _pValueCooked(pValueCooked)
{
}

Tag* Tag::Create(UInt typeId, UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked)
{
	switch (typeId) {
	case TypeId::BYTE:
		return new Tag_BYTE(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::ASCII:
		return new Tag_ASCII(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::SHORT:
		return new Tag_SHORT(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::LONG:
		return new Tag_LONG(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::RATIONAL:
		return new Tag_RATIONAL(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::UNDEFINED:
		return new Tag_UNDEFINED(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::SLONG:
		return new Tag_SLONG(tagId, pSymbol, pValue, pValueCooked);
	case TypeId::SRATIONAL:
		return new Tag_SRATIONAL(tagId, pSymbol, pValue, pValueCooked);
	default:
		break;
	}
	return nullptr;
}

bool Tag::CheckRangedNumber(const Value& value, Double numMin, Double numMax)
{
	auto CheckSub = [numMin, numMax](const Value& value) {
		if (!value.IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::ValueError, "number value is expected");
			return false;
		}
		Double num = Value_Number::GetNumber<Double>(value);
		if (num <= numMin && num <= numMax) return true;
		Error::Issue(ErrorType::RangeError, "value number is out of range");
		return false;
	};
	if (!value.IsType(VTYPE_List)) return CheckSub(value);
	for (const Value* pValue : Value_List::GetValueOwner(value)) {
		if (!CheckSub(value)) return false;
	}
	return true;
};

String Tag::ToString(const StringStyle& ss) const
{
	String str;
	str += _pSymbol->GetName();
	str += ":";
	str += _pValue->ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
bool Tag_BYTE::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
}

bool Tag_BYTE::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
bool Tag_ASCII::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_String);
}

bool Tag_ASCII::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
bool Tag_SHORT::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x0000, 0xffff);
}

bool Tag_SHORT::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
bool Tag_LONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, 0x00000000, 0xffffffff);
}

bool Tag_LONG::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
bool Tag_RATIONAL::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Rational);
		(value.IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
}

bool Tag_RATIONAL::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
bool Tag_UNDEFINED::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Binary);
}

bool Tag_UNDEFINED::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
bool Tag_SLONG::CheckAcceptableValue(Value& value) const
{
	return CheckRangedNumber(value, -0x80000000, 0x7fffffff);
}

bool Tag_SLONG::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
bool Tag_SRATIONAL::CheckAcceptableValue(Value& value) const
{
	return value.IsType(VTYPE_Rational);
		(value.IsType(VTYPE_List) &&
			Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
}

bool Tag_SRATIONAL::WriteToStream(Stream& stream) const
{
	return true;
}

//------------------------------------------------------------------------------
// TagList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TagOwner
//------------------------------------------------------------------------------
void TagOwner::Clear()
{
	for (Tag* pTag : *this) Tag::Delete(pTag);
	clear();
}

//------------------------------------------------------------------------------
// TagMap
//------------------------------------------------------------------------------
void TagMap::Clear()
{
	for (auto iter = begin(); iter != end(); iter++) Tag::Delete(iter->second);
	clear();
}

Tag* TagMap::Lookup(const Symbol* pSymbol) const
{
	auto iter = find(pSymbol);
	return (iter == end())? nullptr : iter->second;
}

Gurax_EndModuleScope(jpeg)
