﻿//==============================================================================
// VType_wxSplashScreen.cpp
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

${help.ComposePropertyHelp(wx.SplashScreen, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SplashScreen, `en)}

${help.ComposeMethodHelp(wx.SplashScreen, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SplashScreen, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SplashScreen, `ja)}

${help.ComposeMethodHelp(wx.SplashScreen, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.SplashScreen(bitmap as wx.Bitmap, splashStyle as Number, milliseconds as Number, parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(SplashScreen_gurax, "SplashScreen")
{
	Declare(VTYPE_wxSplashScreen, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("splashStyle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("milliseconds", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(SplashScreen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	long splashStyle = args_gurax.PickNumber<long>();
	int milliseconds = args_gurax.PickNumber<int>();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : ((wxBORDER_SIMPLE | wxFRAME_NO_TASKBAR) | wxSTAY_ON_TOP);
	// Function body
	auto pEntity_gurax = new Value_wxSplashScreen::EntityT(bitmap, splashStyle, milliseconds, parent, id, pos, size, style);
	RefPtr<Value_wxSplashScreen> pValue_gurax(new Value_wxSplashScreen(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SplashScreen#GetSplashStyle()
Gurax_DeclareMethodAlias(wxSplashScreen, GetSplashStyle_gurax, "GetSplashStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplashScreen, GetSplashStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetSplashStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.SplashScreen#GetTimeout()
Gurax_DeclareMethodAlias(wxSplashScreen, GetTimeout_gurax, "GetTimeout")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplashScreen, GetTimeout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTimeout();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSplashScreen
//------------------------------------------------------------------------------
VType_wxSplashScreen VTYPE_wxSplashScreen("SplashScreen");

void VType_wxSplashScreen::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxFrame, Flag::Mutable, Gurax_CreateConstructor(SplashScreen_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSplashScreen, GetSplashStyle_gurax));
	Assign(Gurax_CreateMethod(wxSplashScreen, GetTimeout_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSplashScreen
//------------------------------------------------------------------------------
VType& Value_wxSplashScreen::vtype = VTYPE_wxSplashScreen;

String Value_wxSplashScreen::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SplashScreen");
}

//------------------------------------------------------------------------------
// Value_wxSplashScreen::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
