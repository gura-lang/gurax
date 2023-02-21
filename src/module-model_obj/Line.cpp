//==============================================================================
// Line.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Line
//------------------------------------------------------------------------------
const Vertex4* Line::GetV(const Content& content, size_t iIndexPair) const
{
	return (iIndexPair < _indexPairList.size())? content.GetV(_indexPairList[iIndexPair].iV) : nullptr;
}

const Vertex3* Line::GetVt(const Content& content, size_t iIndexPair) const
{
	return (iIndexPair < _indexPairList.size())? content.GetVt(_indexPairList[iIndexPair].iVt) : nullptr;
}

String Line::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Line:%zuelements", _indexPairList.size());
}

//------------------------------------------------------------------------------
// LineList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// LineOwner
//------------------------------------------------------------------------------
void LineOwner::Clear()
{
	for (Line* pLine : *this) Line::Delete(pLine);
	clear();
}

Gurax_EndModuleScope(model_obj)
