//==============================================================================
// VType_ArgMapper.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ArgMapper, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ArgMapper, `en)}

${help.ComposeMethodHelp(ArgMapper, `en)}
)""";

//------------------------------------------------------------------------------
// VType_ArgMapper
//------------------------------------------------------------------------------
VType_ArgMapper VTYPE_ArgMapper("ArgMapper");

void VType_ArgMapper::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_ArgMapper
//------------------------------------------------------------------------------
VType& Value_ArgMapper::vtype = VTYPE_ArgMapper;

String Value_ArgMapper::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetIterator().ToString(StringStyle::Quote_NilVisible));
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
