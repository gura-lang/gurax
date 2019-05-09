//==============================================================================
// VType_Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Error
//------------------------------------------------------------------------------
VType_Error VTYPE_Error("Error");

void VType_Error::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Error
//------------------------------------------------------------------------------
String Value_Error::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetError().GetErrorType().GetName();
	str += ">";
	return str;
}

String Value_Error::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
