//==============================================================================
// Shadow_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Shadow_obj
//------------------------------------------------------------------------------
bool Shadow_obj::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Shadow_obj::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Shadow_obj::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Shadow_obj");
}

//------------------------------------------------------------------------------
// Shadow_objList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Shadow_objOwner
//------------------------------------------------------------------------------
void Shadow_objOwner::Clear()
{
	for (Shadow_obj* pShadow_obj : *this) Shadow_obj::Delete(pShadow_obj);
	clear();
}

Gurax_EndModuleScope(model_obj)
