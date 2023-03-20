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
	_filenames.push_back(tokenizer.GetField());
	return true;
}

bool Mtllib::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
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
