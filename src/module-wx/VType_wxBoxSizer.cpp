//==============================================================================
// VType_wxBoxSizer.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

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
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BoxSizer(orient as Number) {block?}
Gurax_DeclareConstructorAlias(BoxSizer_gurax, "BoxSizer")
{
	Declare(VTYPE_wxBoxSizer, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.BoxSizer.");
}

Gurax_ImplementConstructorEx(BoxSizer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBoxSizer(
		wxBoxSizer(orient)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBoxSizer
//------------------------------------------------------------------------------
VType_wxBoxSizer VTYPE_wxBoxSizer("BoxSizer");

void VType_wxBoxSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSizer, Flag::Mutable, Gurax_CreateConstructor(BoxSizer_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxBoxSizer
//------------------------------------------------------------------------------
VType& Value_wxBoxSizer::vtype = VTYPE_wxBoxSizer;

String Value_wxBoxSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BoxSizer");
}

Gurax_EndModuleScope(wx)
