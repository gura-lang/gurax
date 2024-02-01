//==============================================================================
// VType_ArgMapper_Multiple.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ArgMapper_Multiple, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ArgMapper_Multiple, `en)}

${help.ComposeMethodHelp(ArgMapper_Multiple, `en)}
)""";

//------------------------------------------------------------------------------
// VType_ArgMapper_Multiple
//------------------------------------------------------------------------------
VType_ArgMapper_Multiple VTYPE_ArgMapper_Multiple("ArgMapper_Multiple");

void VType_ArgMapper_Multiple::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_List, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_ArgMapper_Multiple
//------------------------------------------------------------------------------
VType& Value_ArgMapper_Multiple::vtype = VTYPE_ArgMapper_Multiple;

String Value_ArgMapper_Multiple::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetValueOwner().ToString(StringStyle(ss).SetWithSquare()));
}

bool Value_ArgMapper_Multiple::ReadyToPickValue(Processor& processor, Frame& frame, DeclArg& declArg)
{
	ValueTypedOwner& valueTypedOwner = _pValuePicked->GetValueTypedOwner();
	valueTypedOwner.Clear();
	for (Value* pValue : GetValueOwner()) {
		if (!pValue->ReadyToPickValue(processor, frame, declArg)) return false;
		valueTypedOwner.Add(pValue->PickValue());
	}
	return true;
}

bool Value_ArgMapper_Multiple::ReadyToPickValueWithoutCast()
{
	ValueTypedOwner& valueTypedOwner = _pValuePicked->GetValueTypedOwner();
	valueTypedOwner.Clear();
	for (Value* pValue : GetValueOwner()) {
		if (!pValue->ReadyToPickValueWithoutCast()) return false;
		valueTypedOwner.Add(pValue->PickValue());
	}
	return true;
}

void Value_ArgMapper_Multiple::UpdateIteratorInfo(Iterator::Flags& flags, size_t& len) const
{
	for (Value* pValue : GetValueOwner()) {
		pValue->UpdateIteratorInfo(flags, len);
	}
}

}
