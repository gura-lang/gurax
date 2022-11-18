﻿//==============================================================================
// VType_wxBufferedDC.cpp
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

${help.ComposePropertyHelp(wx.BufferedDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BufferedDC, `en)}

${help.ComposeMethodHelp(wx.BufferedDC, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BufferedDC#SetStyle(style as Number)
Gurax_DeclareMethodAlias(wxBufferedDC, SetStyle_gurax, "SetStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBufferedDC, SetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int style = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetStyle(style);
	return Gurax::Value::nil();
}

// wx.BufferedDC#GetStyle()
Gurax_DeclareMethodAlias(wxBufferedDC, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBufferedDC, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBufferedDC
//------------------------------------------------------------------------------
VType_wxBufferedDC VTYPE_wxBufferedDC("BufferedDC");

void VType_wxBufferedDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBufferedDC, SetStyle_gurax));
	Assign(Gurax_CreateMethod(wxBufferedDC, GetStyle_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBufferedDC
//------------------------------------------------------------------------------
VType& Value_wxBufferedDC::vtype = VTYPE_wxBufferedDC;

String Value_wxBufferedDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BufferedDC");
}

Gurax_EndModuleScope(wx)
