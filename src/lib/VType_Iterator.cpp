//==============================================================================
// VType_Iterator.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Iterator
//------------------------------------------------------------------------------
VType_Iterator VTYPE_Iterator("Iterator");

void VType_Iterator::DoPrepare(Frame& frame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frame.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Iterator
//------------------------------------------------------------------------------
String Value_Iterator::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetIterator().ToString(StringStyle().Digest());
	str += ">";
	return str;
}

String Value_Iterator::ToStringDetail(const StringStyle& ss) const
{
	return GetIterator().ToString(ss);
}

}
