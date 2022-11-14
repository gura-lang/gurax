//==============================================================================
// VType_Quote.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Quote, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Quote, `en)}

${help.ComposeMethodHelp(Quote, `en)}
)**";

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
VType_Quote VTYPE_Quote("Quote");

void VType_Quote::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VType::Invalid, Flag::Immutable);
}

Value* VType_Quote::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.IsInstanceOf(VTYPE_Expr)? value.Reference() : nullptr;
}

//------------------------------------------------------------------------------
// Value_Quote
//------------------------------------------------------------------------------
VType& Value_Quote::vtype = VTYPE_Quote;

String Value_Quote::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetExpr().ToString(ss));
}

}
