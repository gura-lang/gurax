//==============================================================================
// Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
Tag::Tag(UInt16 tagId, UInt16 typeId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
	_tagId(tagId), _typeId(typeId), _pSymbol(pSymbol), _pValue(pValue), _pValueCooked(pValueCooked)
{
}

bool Tag::CheckAcceptableValue(Value& value) const
{
	auto _CheckRangedNumber = [](const Value& value, Double numMin, Double numMax) {
		if (!value.IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::ValueError, "number value is expected");
			return false;
		}
		Double num = Value_Number::GetNumber<Double>(value);
		if (num <= numMin && num <= numMax) return true;
		Error::Issue(ErrorType::RangeError, "value number is out of range");
		return false;
	};
	auto CheckRangedNumber = [_CheckRangedNumber](const Value& value, Double numMin, Double numMax) {
		if (value.IsType(VTYPE_List)) {
			for (const Value* pValue : Value_List::GetValueOwner(value)) {
				if (!_CheckRangedNumber(value, numMin, numMax)) return false;
			}
			return true;
		}
		return _CheckRangedNumber(value, numMin, numMax);
	};
	switch (_typeId) {
	case TypeId::BYTE: {
		return value.IsType(VTYPE_Binary);
	}
	case TypeId::ASCII: {
		return value.IsType(VTYPE_String);
	}
	case TypeId::SHORT: {
		return CheckRangedNumber(value, -0x8000, 0x7fff);
	}
	case TypeId::LONG: {
		return CheckRangedNumber(value, -0x80000000, 0x7fffffff);
	}
	case TypeId::RATIONAL: {
		return value.IsType(VTYPE_Rational);
			(value.IsType(VTYPE_List) &&
			 Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
	}
	case TypeId::UNDEFINED: {
		return value.IsType(VTYPE_Binary);
	}
	case TypeId::SLONG: {
		return CheckRangedNumber(value, -0x80000000, 0x7fffffff);
	}
	case TypeId::SRATIONAL: {
		return value.IsType(VTYPE_Rational);
			(value.IsType(VTYPE_List) &&
			 Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Rational));
	}
	default:
		break;
	}
	IssueError_InvalidFormat();
	return false;
}

String Tag::ToString(const StringStyle& ss) const
{
	String str;
	str += _pSymbol->GetName();
	str += ":";
	str += _pValue->ToString(ss);
	return str;
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
