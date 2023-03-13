//==============================================================================
// Mtllib.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Mtllib
//------------------------------------------------------------------------------
bool Mtllib::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Mtllib::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Mtllib::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Mtllib");
}

//------------------------------------------------------------------------------
// MtllibList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MtllibOwner
//------------------------------------------------------------------------------
void MtllibOwner::Clear()
{
	for (Mtllib* pMtllib : *this) Mtllib::Delete(pMtllib);
	clear();
}

Gurax_EndModuleScope(model_obj)
