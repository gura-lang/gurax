//==============================================================================
// Stech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Stech
//------------------------------------------------------------------------------
bool Stech::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Stech::FinishField(size_t nParams)
{
	return true;
}

String Stech::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Stech");
}

//------------------------------------------------------------------------------
// StechList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StechOwner
//------------------------------------------------------------------------------
void StechOwner::Clear()
{
	for (Stech* pStech : *this) Stech::Delete(pStech);
	clear();
}

Gurax_EndModuleScope(model_obj)
