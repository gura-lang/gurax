//==============================================================================
// VType_Quote.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
VType_Quote VTYPE_Quote("Quote");

void VType_Quote::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VType::Empty, Flag::Immutable);
}

Value* VType_Quote::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.IsInstanceOf(VTYPE_Expr)? value.Reference() : nullptr;
}

//------------------------------------------------------------------------------
// Value_Quote
//------------------------------------------------------------------------------

}
