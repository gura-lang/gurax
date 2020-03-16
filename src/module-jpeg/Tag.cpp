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

String Tag::ToString(const StringStyle& ss) const
{
	return "jpeg.Tag";
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

Gurax_EndModuleScope(jpeg)
