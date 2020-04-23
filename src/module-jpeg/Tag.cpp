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

bool Tag::CheckAcceptableValue(const Value& value) const
{
	switch (_typeId) {
	case TypeId::BYTE: {
		break;
	}
	case TypeId::ASCII: {
		break;
	}
	case TypeId::SHORT: {
		break;
	}
	case TypeId::LONG: {
		break;
	}
	case TypeId::RATIONAL: {
		break;
	}
	case TypeId::UNDEFINED: {
		break;
	}
	case TypeId::SLONG: {
		break;
	}
	case TypeId::SRATIONAL: {
		break;
	}
	default: {
		IssueError_InvalidFormat();
		return false;
	}
	}
	return true;
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
