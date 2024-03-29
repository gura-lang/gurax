//==============================================================================
// D_interp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// D_interp
//------------------------------------------------------------------------------
bool D_interp::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool D_interp::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String D_interp::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.D_interp");
}

//------------------------------------------------------------------------------
// D_interpList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// D_interpOwner
//------------------------------------------------------------------------------
void D_interpOwner::Clear()
{
	for (D_interp* pD_interp : *this) D_interp::Delete(pD_interp);
	clear();
}

Gurax_EndModuleScope(model_obj)
