//==============================================================================
// VType_ErrorType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_ErrorType
//------------------------------------------------------------------------------
VType_ErrorType VTYPE_ErrorType("ErrorType");

void VType_ErrorType::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_ErrorType
//------------------------------------------------------------------------------
String Value_ErrorType::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetErrorType().GetName();
	str += ">";
	return str;
}

String Value_ErrorType::ToStringDetail(const StringStyle& ss) const
{
	return GetErrorType().GetName();
}

}
