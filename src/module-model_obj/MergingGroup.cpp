//==============================================================================
// MergingGroup.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// MergingGroup
//------------------------------------------------------------------------------
bool MergingGroup::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	return true;
}

bool MergingGroup::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String MergingGroup::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.MergingGroup");
}

//------------------------------------------------------------------------------
// MergingGroupList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MergingGroupOwner
//------------------------------------------------------------------------------
void MergingGroupOwner::Clear()
{
	for (MergingGroup* pMergingGroup : *this) MergingGroup::Delete(pMergingGroup);
	clear();
}

Gurax_EndModuleScope(model_obj)
