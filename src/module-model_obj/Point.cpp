//==============================================================================
// Point.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------------
const Vertex4* Point::GetV(const Content& content, size_t iIndex) const
{
	return (iIndex < _indexList.size())? content.GetV(_indexList[iIndex]) : nullptr;
}

bool Point::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Point::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Point::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Point:%zuelements", _indexList.size());
}

//------------------------------------------------------------------------------
// PointList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PointOwner
//------------------------------------------------------------------------------
void PointOwner::Clear()
{
	for (Point* pPoint : *this) Point::Delete(pPoint);
	clear();
}

Gurax_EndModuleScope(model_obj)
