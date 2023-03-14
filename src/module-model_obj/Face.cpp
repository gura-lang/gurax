//==============================================================================
// Face.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Face
//------------------------------------------------------------------------------
const Vertex4* Face::GetV(const Content& content, size_t iIndexTriplet) const
{
	return (iIndexTriplet < _indexTripletList.size())? content.GetV(_indexTripletList[iIndexTriplet].iV) : nullptr;
}

const Vertex3* Face::GetVt(const Content& content, size_t iIndexTriplet) const
{
	return (iIndexTriplet < _indexTripletList.size())? content.GetVt(_indexTripletList[iIndexTriplet].iVt) : nullptr;
}

const Vertex3* Face::GetVn(const Content& content, size_t iIndexTriplet) const
{
	return (iIndexTriplet < _indexTripletList.size())? content.GetVn(_indexTripletList[iIndexTriplet].iVn) : nullptr;
}

bool Face::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	int iV, iVt, iVn;
	if (!tokenizer.ExtractIndexTriplet(&iV, &iVt, &iVn)) {
		return false;
	} else if (iV <= 0) {
		Error::Issue(ErrorType::FormatError, "invalid index for vertex");
		return false;
	}
	AddIndexTriplet(iV, iVt, iVn);
	return true;
}

bool Face::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	if (nParams < 3) {
		Error::Issue(ErrorType::FormatError, "at least three index-triplets must exist");
		return false;
	}
	return true;
}

String Face::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Face:%zuelements", _indexTripletList.size());
}

//------------------------------------------------------------------------------
// FaceList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FaceOwner
//------------------------------------------------------------------------------
void FaceOwner::Clear()
{
	for (Face* pFace : *this) Face::Delete(pFace);
	clear();
}

Gurax_EndModuleScope(model_obj)
