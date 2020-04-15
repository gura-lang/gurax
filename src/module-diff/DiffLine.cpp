//==============================================================================
// DiffLine.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(diff)

//------------------------------------------------------------------------------
// DiffLine
//------------------------------------------------------------------------------
bool DiffLine::Compose(const Value& value1, const Value& value2)
{
	if (!FeedSequence(_diff.A, value1) && !FeedSequence(_diff.B, value2)) return false;
	_diff.init();
	_diff.onHuge();
	_diff.compose();
	return true;
}

bool DiffLine::FeedSequence(Sequence& seq, const Value& value)
{
	
	return true;
}

String DiffLine::ToString(const StringStyle& ss) const
{
	return "diff.DiffLine";
}

Gurax_EndModuleScope(diff)
