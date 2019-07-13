//==============================================================================
// VType_Member_MapToIter.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToIter
//------------------------------------------------------------------------------
VType_Member_MapToIter VTYPE_Member_MapToIter("Member_MapToIter");

void VType_Member_MapToIter::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapToIter
//------------------------------------------------------------------------------
String Value_Member_MapToIter::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

}
