//==============================================================================
// VType_Member_MapToList.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapToList
//------------------------------------------------------------------------------
VType_Member_MapToList VTYPE_Member_MapToList("Member_MapToList");

void VType_Member_MapToList::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapToList
//------------------------------------------------------------------------------
String Value_Member_MapToList::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

}
