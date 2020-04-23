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
	switch (_typeId) {
	case TypeId::BYTE: {
		return value.IsType(VTYPE_Binary);
	}
	case TypeId::ASCII: {
		return value.IsType(VTYPE_String);
	}
	case TypeId::SHORT: {
		return value.IsType(VTYPE_Number) ||
			(value.IsType(VTYPE_List) &&
			 Value_List::GetValueTypedOwner(value).RefreshVTypeOfElems().IsIdentical(VTYPE_Number));
	}
	case TypeId::LONG: {
		return value.IsType(VTYPE_Number);
	}
	case TypeId::RATIONAL: {
		return value.IsType(VTYPE_Number);
	}
	case TypeId::UNDEFINED: {
		return value.IsType(VTYPE_Binary);
	}
	case TypeId::SLONG: {
		return value.IsType(VTYPE_Number);
	}
	case TypeId::SRATIONAL: {
		return value.IsType(VTYPE_Number);
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
