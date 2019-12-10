//==============================================================================
// VType_ArgMapper.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// VType_ArgMapper
//------------------------------------------------------------------------------
VType_ArgMapper VTYPE_ArgMapper("ArgMapper");

void VType_ArgMapper::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_ArgMapper
//------------------------------------------------------------------------------
VType& Value_ArgMapper::vtype = VTYPE_ArgMapper;

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

Iterator* Value_ArgMapper::DoGenIterator() const
{
	return GetIterator().Reference();
}

bool Value_ArgMapper::ReadyToPickValue(Frame& frame, DeclArg& declArg)
{
	RefPtr<Value> pValue(GetIterator().NextValue());
	if (!pValue) return false;
	_pValue.reset(declArg.Cast(frame, *pValue));
	return !!_pValue;
}

bool Value_ArgMapper::ReadyToPickValueWithoutCast()
{
	_pValue.reset(GetIterator().NextValue());
	return !!_pValue;
}

void Value_ArgMapper::UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const
{
	flags &= GetIterator().GetFlags();
	if (GetIterator().IsLenDetermined()) {
		len = std::min(len, GetIterator().GetLength());
	}
}

}
