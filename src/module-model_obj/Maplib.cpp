//==============================================================================
// Maplib.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Maplib
//------------------------------------------------------------------------------
bool Maplib::FeedField(const char* field, size_t iParam)
{
	return true;
}

bool Maplib::FinishField(size_t nParams)
{
	return true;
}

String Maplib::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Maplib");
}

//------------------------------------------------------------------------------
// MaplibList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MaplibOwner
//------------------------------------------------------------------------------
void MaplibOwner::Clear()
{
	for (Maplib* pMaplib : *this) Maplib::Delete(pMaplib);
	clear();
}

Gurax_EndModuleScope(model_obj)
