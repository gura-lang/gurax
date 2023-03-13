//==============================================================================
// Connect.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Connect
//------------------------------------------------------------------------------
bool Connect::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Connect::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Connect::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Connect");
}

//------------------------------------------------------------------------------
// ConnectList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ConnectOwner
//------------------------------------------------------------------------------
void ConnectOwner::Clear()
{
	for (Connect* pConnect : *this) Connect::Delete(pConnect);
	clear();
}

Gurax_EndModuleScope(model_obj)
