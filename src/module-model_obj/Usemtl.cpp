//==============================================================================
// Usemtl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Usemtl
//------------------------------------------------------------------------------
bool Usemtl::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Usemtl::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Usemtl::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Usemtl");
}

//------------------------------------------------------------------------------
// UsemtlList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// UsemtlOwner
//------------------------------------------------------------------------------
void UsemtlOwner::Clear()
{
	for (Usemtl* pUsemtl : *this) Usemtl::Delete(pUsemtl);
	clear();
}

Gurax_EndModuleScope(model_obj)
