﻿//==============================================================================
// VType_wxToolTip.cpp
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

${help.ComposePropertyHelp(wx.ToolTip, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ToolTip, `en)}

${help.ComposeMethodHelp(wx.ToolTip, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ToolTip, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ToolTip, `ja)}

${help.ComposeMethodHelp(wx.ToolTip, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ToolTip(tip as String) {block?}
Gurax_DeclareConstructorAlias(ToolTip_gurax, "ToolTip")
{
	Declare(VTYPE_wxToolTip, Flag::None);
	DeclareArg("tip", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ToolTip_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* tip = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolTip(
		wxToolTip(tip)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ToolTip#GetTip()
Gurax_DeclareMethodAlias(wxToolTip, GetTip_gurax, "GetTip")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxToolTip, GetTip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetTip();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.ToolTip#GetWindow() {block?}
Gurax_DeclareMethodAlias(wxToolTip, GetWindow_gurax, "GetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolTip, GetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetWindow()));
}

// wx.ToolTip#SetTip(tip as String)
Gurax_DeclareMethodAlias(wxToolTip, SetTip_gurax, "SetTip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tip", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolTip, SetTip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* tip = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetTip(tip);
	return Gurax::Value::nil();
}

// wx.ToolTip.Enable(flag as Bool)
Gurax_DeclareClassMethodAlias(wxToolTip, Enable_gurax, "Enable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxToolTip, Enable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flag = args_gurax.PickBool();
	// Function body
	wxToolTip::Enable(flag);
	return Gurax::Value::nil();
}

// wx.ToolTip.SetAutoPop(msecs as Number)
Gurax_DeclareClassMethodAlias(wxToolTip, SetAutoPop_gurax, "SetAutoPop")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("msecs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxToolTip, SetAutoPop_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long msecs = args_gurax.PickNumber<long>();
	// Function body
	wxToolTip::SetAutoPop(msecs);
	return Gurax::Value::nil();
}

// wx.ToolTip.SetDelay(msecs as Number)
Gurax_DeclareClassMethodAlias(wxToolTip, SetDelay_gurax, "SetDelay")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("msecs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxToolTip, SetDelay_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long msecs = args_gurax.PickNumber<long>();
	// Function body
	wxToolTip::SetDelay(msecs);
	return Gurax::Value::nil();
}

// wx.ToolTip.SetMaxWidth(width as Number)
Gurax_DeclareClassMethodAlias(wxToolTip, SetMaxWidth_gurax, "SetMaxWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxToolTip, SetMaxWidth_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	wxToolTip::SetMaxWidth(width);
	return Gurax::Value::nil();
}

// wx.ToolTip.SetReshow(msecs as Number)
Gurax_DeclareClassMethodAlias(wxToolTip, SetReshow_gurax, "SetReshow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("msecs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxToolTip, SetReshow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long msecs = args_gurax.PickNumber<long>();
	// Function body
	wxToolTip::SetReshow(msecs);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxToolTip
//------------------------------------------------------------------------------
VType_wxToolTip VTYPE_wxToolTip("ToolTip");

void VType_wxToolTip::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable, Gurax_CreateConstructor(ToolTip_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxToolTip, GetTip_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, GetWindow_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, SetTip_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, Enable_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, SetAutoPop_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, SetDelay_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, SetMaxWidth_gurax));
	Assign(Gurax_CreateMethod(wxToolTip, SetReshow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxToolTip
//------------------------------------------------------------------------------
VType& Value_wxToolTip::vtype = VTYPE_wxToolTip;

String Value_wxToolTip::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ToolTip");
}

Gurax_EndModuleScope(wx)
