//==============================================================================
// VType_Member_Normal.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_Normal
//------------------------------------------------------------------------------
VType_Member_Normal VTYPE_Member_Normal("Member_Normal");

void VType_Member_Normal::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_Normal
//------------------------------------------------------------------------------
String Value_Member_Normal::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

}
