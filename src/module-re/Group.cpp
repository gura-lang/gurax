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
	return GetMatch().GetStringSTL().substr(_posBegin, _posEnd - _posBegin);
}

String Group::ToString(const StringStyle& ss) const
{
	String str;
	str.Printf("re.Group:%d:%d", _posBegin, _posEnd);
	return str;
}

Gurax_EndModuleScope(re)
