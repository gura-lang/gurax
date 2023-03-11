﻿//==============================================================================
// VType_wxContextHelpButton.cpp
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

${help.ComposePropertyHelp(wx.ContextHelpButton, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ContextHelpButton, `en)}

${help.ComposeMethodHelp(wx.ContextHelpButton, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ContextHelpButton, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ContextHelpButton, `ja)}

${help.ComposeMethodHelp(wx.ContextHelpButton, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ContextHelpButton(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(ContextHelpButton_gurax, "ContextHelpButton")
{
	Declare(VTYPE_wxContextHelpButton, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ContextHelpButton_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_CONTEXT_HELP;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxBU_AUTODRAW;
	// Function body
	auto pEntity_gurax = new Value_wxContextHelpButton::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxContextHelpButton> pValue_gurax(new Value_wxContextHelpButton(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxContextHelpButton
//------------------------------------------------------------------------------
VType_wxContextHelpButton VTYPE_wxContextHelpButton("ContextHelpButton");

void VType_wxContextHelpButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxBitmapButton, Flag::Mutable, Gurax_CreateConstructor(ContextHelpButton_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxContextHelpButton
//------------------------------------------------------------------------------
VType& Value_wxContextHelpButton::vtype = VTYPE_wxContextHelpButton;

String Value_wxContextHelpButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ContextHelpButton");
}

//------------------------------------------------------------------------------
// Value_wxContextHelpButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
