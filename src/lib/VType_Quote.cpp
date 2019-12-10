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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// VType_Quote
//------------------------------------------------------------------------------
VType_Quote VTYPE_Quote("Quote");

void VType_Quote::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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
