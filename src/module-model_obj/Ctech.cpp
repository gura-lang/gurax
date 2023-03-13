//==============================================================================
// Ctech.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Ctech
//------------------------------------------------------------------------------
bool Ctech::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Ctech::FinishField(size_t nParams)
{
	return true;
}

String Ctech::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Ctech");
}

//------------------------------------------------------------------------------
// CtechList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CtechOwner
//------------------------------------------------------------------------------
void CtechOwner::Clear()
{
	for (Ctech* pCtech : *this) Ctech::Delete(pCtech);
	clear();
}

Gurax_EndModuleScope(model_obj)
