//==============================================================================
// Step.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Step
//------------------------------------------------------------------------------
bool Step::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Step::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Step::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Step");
}

//------------------------------------------------------------------------------
// StepList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StepOwner
//------------------------------------------------------------------------------
void StepOwner::Clear()
{
	for (Step* pStep : *this) Step::Delete(pStep);
	clear();
}

Gurax_EndModuleScope(model_obj)
