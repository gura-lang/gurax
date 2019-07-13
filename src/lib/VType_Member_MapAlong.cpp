//==============================================================================
// VType_Member_MapAlong.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Member_MapAlong
//------------------------------------------------------------------------------
VType_Member_MapAlong VTYPE_Member_MapAlong("Member_MapAlong");

void VType_Member_MapAlong::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Member_MapAlong
//------------------------------------------------------------------------------
String Value_Member_MapAlong::ToStringDetail(const StringStyle& ss) const
{
	String str;
	//str += GetValueThis<Value>().ToStringDetail(ss);
	//str += '.';
	str += GetValueProp().ToStringDetail(ss);
	return str;
}

}
