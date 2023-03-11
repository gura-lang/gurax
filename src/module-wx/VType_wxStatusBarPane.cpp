﻿//==============================================================================
// VType_wxStatusBarPane.cpp
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

${help.ComposePropertyHelp(wx.StatusBarPane, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StatusBarPane, `en)}

${help.ComposeMethodHelp(wx.StatusBarPane, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.StatusBarPane, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.StatusBarPane, `ja)}

${help.ComposeMethodHelp(wx.StatusBarPane, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StatusBarPane(style? as Number, width? as Number) {block?}
Gurax_DeclareConstructorAlias(StatusBarPane_gurax, "StatusBarPane")
{
	Declare(VTYPE_wxStatusBarPane, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(StatusBarPane_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : wxSB_NORMAL;
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStatusBarPane(
		wxStatusBarPane(style, width)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StatusBarPane#GetWidth()
Gurax_DeclareMethodAlias(wxStatusBarPane, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStatusBarPane, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.StatusBarPane#GetStyle()
Gurax_DeclareMethodAlias(wxStatusBarPane, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxStatusBarPane, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.StatusBarPane#GetText()
Gurax_DeclareMethodAlias(wxStatusBarPane, GetText_gurax, "GetText")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxStatusBarPane, GetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetText();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStatusBarPane
//------------------------------------------------------------------------------
VType_wxStatusBarPane VTYPE_wxStatusBarPane("StatusBarPane");

void VType_wxStatusBarPane::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(StatusBarPane_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStatusBarPane, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxStatusBarPane, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxStatusBarPane, GetText_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStatusBarPane
//------------------------------------------------------------------------------
VType& Value_wxStatusBarPane::vtype = VTYPE_wxStatusBarPane;

String Value_wxStatusBarPane::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StatusBarPane");
}

Gurax_EndModuleScope(wx)
