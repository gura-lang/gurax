﻿//==============================================================================
// VType_wxColourPickerEvent.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.ColourPickerEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ColourPickerEvent, `en)}

${help.ComposeMethodHelp(wx.ColourPickerEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ColourPickerEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ColourPickerEvent, `ja)}

${help.ComposeMethodHelp(wx.ColourPickerEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ColourPickerEvent#GetColour() {block?}
Gurax_DeclareMethodAlias(wxColourPickerEvent, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxColourPickerEvent, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetColour()));
}

// wx.ColourPickerEvent#SetColour(pos as wx.Colour)
Gurax_DeclareMethodAlias(wxColourPickerEvent, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColourPickerEvent, SetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_pos = args_gurax.Pick<Value_wxColour>();
	const wxColour& pos = value_pos.GetEntity();
	// Function body
	pEntity_gurax->SetColour(pos);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxColourPickerEvent
//------------------------------------------------------------------------------
VType_wxColourPickerEvent VTYPE_wxColourPickerEvent("ColourPickerEvent");

void VType_wxColourPickerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxColourPickerEvent, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxColourPickerEvent, SetColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxColourPickerEvent
//------------------------------------------------------------------------------
VType& Value_wxColourPickerEvent::vtype = VTYPE_wxColourPickerEvent;
EventValueFactoryDeriv<Value_wxColourPickerEvent> Value_wxColourPickerEvent::eventValueFactory;

String Value_wxColourPickerEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourPickerEvent");
}

Gurax_EndModuleScope(wx)
