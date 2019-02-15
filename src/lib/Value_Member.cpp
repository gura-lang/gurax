//==============================================================================
// Value_Member.cpp
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
	frame.AssignVType(*this);
}

//------------------------------------------------------------------------------
// Value_Member
//------------------------------------------------------------------------------
String Value_Member::ToStringDetail(const StringStyle& ss) const
{
	String rtn;
	//rtn += GetValueTarget().ToStringDetail(ss);
	//rtn += '.';
	rtn += GetValueProp().ToStringDetail(ss);
	return rtn;
}

}
