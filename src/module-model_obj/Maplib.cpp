//==============================================================================
// Maplib.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Maplib
//------------------------------------------------------------------------------
bool Maplib::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Maplib::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
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
