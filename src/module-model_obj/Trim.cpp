//==============================================================================
// Trim.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trim
//------------------------------------------------------------------------------
bool Trim::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Trim::FinishField(size_t nParams)
{
	return true;
}

String Trim::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Trim");
}

//------------------------------------------------------------------------------
// TrimList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TrimOwner
//------------------------------------------------------------------------------
void TrimOwner::Clear()
{
	for (Trim* pTrim : *this) Trim::Delete(pTrim);
	clear();
}

Gurax_EndModuleScope(model_obj)
