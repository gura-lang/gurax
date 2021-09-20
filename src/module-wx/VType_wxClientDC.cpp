//==============================================================================
// VType_wxClientDC.cpp
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
// wx.ClientDC(window as wx.Window) {block?} {block?}
Gurax_DeclareConstructorAlias(ClientDC_gurax, "ClientDC")
{
	Declare(VTYPE_wxClientDC, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ClientDC.");
}

Gurax_ImplementConstructorEx(ClientDC_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxClientDC(
		wxClientDC(window)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxClientDC
//------------------------------------------------------------------------------
VType_wxClientDC VTYPE_wxClientDC("ClientDC");

void VType_wxClientDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindowDC, Flag::Mutable, Gurax_CreateConstructor(ClientDC_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxClientDC
//------------------------------------------------------------------------------
VType& Value_wxClientDC::vtype = VTYPE_wxClientDC;

String Value_wxClientDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ClientDC");
}

Gurax_EndModuleScope(wx)
