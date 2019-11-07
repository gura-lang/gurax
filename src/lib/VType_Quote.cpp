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
	// Declaration of VType
	Declare(VType::Empty, Flag::Immutable);
}

Value* VType_Quote::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.IsInstanceOf(VTYPE_Expr)? value.Reference() : nullptr;
}

//------------------------------------------------------------------------------
// Value_Quote
//------------------------------------------------------------------------------
VType& Value_Quote::vtype = VTYPE_Quote;

}
