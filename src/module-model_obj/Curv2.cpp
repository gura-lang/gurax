//==============================================================================
// Curv2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Curv2
//------------------------------------------------------------------------------
bool Curv2::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Curv2::FinishField(size_t nParams)
{
	return true;
}

String Curv2::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Curv2");
}

//------------------------------------------------------------------------------
// Curv2List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Curv2Owner
//------------------------------------------------------------------------------
void Curv2Owner::Clear()
{
	for (Curv2* pCurv2 : *this) Curv2::Delete(pCurv2);
	clear();
}

Gurax_EndModuleScope(model_obj)
