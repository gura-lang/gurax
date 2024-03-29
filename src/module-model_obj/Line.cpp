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

bool Line::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	int iV, iVt;
	if (!tokenizer.ExtractIndexPair(&iV, &iVt)) {
		return false;
	} else if (iV <= 0) {
		Error::Issue(ErrorType::FormatError, "invalid index for vertex");
		return false;
	}
	AddIndexPair(iV, iVt);
	return true;
}

bool Line::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	if (nParams < 2) {
		Error::Issue(ErrorType::FormatError, "at least two index-pairs must exist");
		return false;
	}
	return true;
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
