﻿//==============================================================================
// VType_wxPaintDC.cpp
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

${help.ComposePropertyHelp(wx.PaintDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PaintDC, `en)}

${help.ComposeMethodHelp(wx.PaintDC, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PaintDC(window as wx.Window) {block?}
Gurax_DeclareConstructorAlias(PaintDC_gurax, "PaintDC")
{
	Declare(VTYPE_wxPaintDC, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(PaintDC_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	auto pEntity_gurax = new wxPaintDC(window);
	RefPtr<Value_wxPaintDC> pValue_gurax(new Value_wxPaintDC(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPaintDC
//------------------------------------------------------------------------------
VType_wxPaintDC VTYPE_wxPaintDC("PaintDC");

void VType_wxPaintDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxClientDC, Flag::Mutable, Gurax_CreateConstructor(PaintDC_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPaintDC
//------------------------------------------------------------------------------
VType& Value_wxPaintDC::vtype = VTYPE_wxPaintDC;

String Value_wxPaintDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PaintDC");
}

Gurax_EndModuleScope(wx)
