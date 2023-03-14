//==============================================================================
// SmoothingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// SmoothingGroup
//------------------------------------------------------------------------------
bool SmoothingGroup::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	if (iParam == 0) {
		if (!tokenizer.ExtractIndex(&_groupNumber)) return false;
	} else {
		Error::Issue(ErrorType::FormatError, "too many parameters for usemtl");
		return false;
	}
	return true;
}

bool SmoothingGroup::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	if (nParams < 1) {
		Error::Issue(ErrorType::FormatError, "lacking parameter for s");
		return false;
	}
	return true;
}

String SmoothingGroup::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.SmoothingGroup");
}

//------------------------------------------------------------------------------
// SmoothingGroupList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// SmoothingGroupOwner
//------------------------------------------------------------------------------
void SmoothingGroupOwner::Clear()
{
	for (SmoothingGroup* pSmoothingGroup : *this) SmoothingGroup::Delete(pSmoothingGroup);
	clear();
}

Gurax_EndModuleScope(model_obj)
