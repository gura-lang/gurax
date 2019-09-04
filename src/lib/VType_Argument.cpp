//==============================================================================
// VType_Argument.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Argument#IsSet(symbol:Symbol):Bool
Gurax_DeclareMethod(Argument, IsSet)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns `true` if the argument has te specified symbol in its attribute list.");
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
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Argument, IsSet));
}

//------------------------------------------------------------------------------
// Value_Argument
//------------------------------------------------------------------------------
VType& Value_Argument::vtype = VTYPE_Argument;

}
