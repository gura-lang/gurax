//==============================================================================
// VType_wxSize.cpp
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
// wx.wxSize(width? as Number, height? as Number) {block?}
Gurax_DeclareConstructorAlias(wxSize_gurax, "wxSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wxSize.");
}

Gurax_ImplementConstructorEx(wxSize_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	int height = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		wxSize(width, height)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSize
//------------------------------------------------------------------------------
VType_wxSize VTYPE_wxSize("Size");

void VType_wxSize::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(wxSize_gurax));
	// Assignment of method
	// Assignment of property
}

//------------------------------------------------------------------------------
// Value_wxSize
//------------------------------------------------------------------------------
VType& Value_wxSize::vtype = VTYPE_wxSize;

String Value_wxSize::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Size");
}

Gurax_EndModuleScope(wx)
