//==============================================================================
// Vertex3.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex3
//------------------------------------------------------------------------------
bool Vertex3::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Vertex3::FinishField(size_t nParams)
{
	return true;
}

String Vertex3::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Vertex3:%g,%g,%g", _x, _y, _z);
}

//------------------------------------------------------------------------------
// Vertex3List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Vertex3Owner
//------------------------------------------------------------------------------
void Vertex3Owner::Clear()
{
	for (Vertex3* pVertex3 : *this) Vertex3::Delete(pVertex3);
	clear();
}

Gurax_EndModuleScope(model_obj)
