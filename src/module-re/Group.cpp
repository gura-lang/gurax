//==============================================================================
// Group.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Group
//------------------------------------------------------------------------------
Group::Group(Match* pMatch, int posBegin, int posEnd) :
	_pMatch(pMatch), _posBegin(posBegin), _posEnd(posEnd)
{
}

String Group::GetString() const
{
	return GetMatch().GetSourceStringSTL().substr(GetPosBegin(), GetPosEnd() - GetPosBegin());
}

String Group::ToString(const StringStyle& ss) const
{
	return String().Format("re.Group:%d-%d", GetPosBegin(), GetPosEnd());
}

Gurax_EndModuleScope(re)
