//==============================================================================
// VType_Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Argument, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Argument, `en)}

${help.ComposeMethodHelp(Argument, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Argument#IsSet(symbol:Symbol):Bool
Gurax_DeclareMethod(Argument, IsSet)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the argument has te specified symbol in its attribute list.
)**");
}

Gurax_ImplementMethod(Argument, IsSet)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	return new Value_Bool(valueThis.GetArgument().IsSet(pSymbol));
}

//------------------------------------------------------------------------------
// VType_Argument
//------------------------------------------------------------------------------
VType_Argument VTYPE_Argument("Argument");

void VType_Argument::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Argument, IsSet));
}

//------------------------------------------------------------------------------
// Value_Argument
//------------------------------------------------------------------------------
VType& Value_Argument::vtype = VTYPE_Argument;

String Value_Argument::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetArgument().ToString(
							ss.IsUnbracket()? ss : StringStyle::Cram));
}

}
