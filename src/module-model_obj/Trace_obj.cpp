//==============================================================================
// Trace_obj.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Trace_obj
//------------------------------------------------------------------------------
bool Trace_obj::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool Trace_obj::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	Error::Issue(ErrorType::UnimplementedError, "%d: %s is not implemented", tokenizer.GetLineNo(), GetName());
	return false;
}

String Trace_obj::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Trace_obj");
}

//------------------------------------------------------------------------------
// Trace_objList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Trace_objOwner
//------------------------------------------------------------------------------
void Trace_objOwner::Clear()
{
	for (Trace_obj* pTrace_obj : *this) Trace_obj::Delete(pTrace_obj);
	clear();
}

Gurax_EndModuleScope(model_obj)
