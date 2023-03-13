//==============================================================================
// Scrv.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Scrv
//------------------------------------------------------------------------------
bool Scrv::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Scrv::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Scrv::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Scrv");
}

//------------------------------------------------------------------------------
// ScrvList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ScrvOwner
//------------------------------------------------------------------------------
void ScrvOwner::Clear()
{
	for (Scrv* pScrv : *this) Scrv::Delete(pScrv);
	clear();
}

Gurax_EndModuleScope(model_obj)
