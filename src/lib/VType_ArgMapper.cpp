//==============================================================================
// VType_ArgMapper.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgMapper
//------------------------------------------------------------------------------
VType_ArgMapper VTYPE_ArgMapper("ArgMapper");

void VType_ArgMapper::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_ArgMapper
//------------------------------------------------------------------------------
String Value_ArgMapper::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetIterator().ToString(StringStyle().Digest());
	str += ">";
	return str;
}

String Value_ArgMapper::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

Iterator* Value_ArgMapper::DoGenIterator()
{
	return GetIterator().Clone();
}

void Value_ArgMapper::UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const
{
	//GetIterator().GetFlags()
}

}
