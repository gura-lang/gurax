//==============================================================================
// VType_VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
VType_VType VTYPE_VType("VType");

void VType_VType::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
String Value_VType::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetVTypeThis().MakeFullName();
	str += ">";
	return str;
}

String Value_VType::ToStringDetail(const StringStyle& ss) const
{
	return GetVTypeThis().MakeFullName();
}

}
