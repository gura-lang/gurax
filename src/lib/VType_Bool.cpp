//==============================================================================
// VType_Bool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
VType_Bool VTYPE_Bool("Bool");

void VType_Bool::DoPrepare(Frame& frameOuter)
{
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Bool
//------------------------------------------------------------------------------
VType& Value_Bool::vtype = VTYPE_Bool;

String Value_Bool::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%s>", _flag? "true" : "false");
	return str;
}

String Value_Bool::ToStringDetail(const StringStyle& ss) const
{
	return _flag? "true" : "false";
}

}
