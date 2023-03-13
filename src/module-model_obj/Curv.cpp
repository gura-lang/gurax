//==============================================================================
// Curv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv
//------------------------------------------------------------------------------
bool Curv::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Curv::FinishField(size_t nParams)
{
	return true;
}

String Curv::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Curv");
}

//------------------------------------------------------------------------------
// CurvList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CurvOwner
//------------------------------------------------------------------------------
void CurvOwner::Clear()
{
	for (Curv* pCurv : *this) Curv::Delete(pCurv);
	clear();
}

Gurax_EndModuleScope(model_obj)
