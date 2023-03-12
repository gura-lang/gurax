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

bool Face::FeedField(const char* field, size_t iParam)
{
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
