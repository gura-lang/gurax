//==============================================================================
// Bmat.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Bmat
//------------------------------------------------------------------------------
bool Bmat::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Bmat::FinishField(size_t nParams)
{
	return true;
}

String Bmat::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Bmat");
}

//------------------------------------------------------------------------------
// BmatList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BmatOwner
//------------------------------------------------------------------------------
void BmatOwner::Clear()
{
	for (Bmat* pBmat : *this) Bmat::Delete(pBmat);
	clear();
}

Gurax_EndModuleScope(model_obj)
