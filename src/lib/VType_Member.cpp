//==============================================================================
// VType_Member.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member
//------------------------------------------------------------------------------
VType_Member VTYPE_Member("Member");

void VType_Member::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Member
//------------------------------------------------------------------------------
String Value_Member::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

}
