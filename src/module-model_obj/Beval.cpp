//==============================================================================
// Beval.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Beval
//------------------------------------------------------------------------------
bool Beval::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Beval::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Beval::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Beval");
}

//------------------------------------------------------------------------------
// BevalList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BevalOwner
//------------------------------------------------------------------------------
void BevalOwner::Clear()
{
	for (Beval* pBeval : *this) Beval::Delete(pBeval);
	clear();
}

Gurax_EndModuleScope(model_obj)
