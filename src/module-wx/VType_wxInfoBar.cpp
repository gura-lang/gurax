﻿//==============================================================================
// VType_wxInfoBar.cpp
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

${help.ComposePropertyHelp(wx.InfoBar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.InfoBar, `en)}

${help.ComposeMethodHelp(wx.InfoBar, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.InfoBar(parent as wx.Window, winid? as Number) {block?}
Gurax_DeclareConstructorAlias(InfoBar_gurax, "InfoBar")
{
	Declare(VTYPE_wxInfoBar, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.InfoBar.
)**");
}

Gurax_ImplementConstructorEx(InfoBar_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool winid_validFlag = args_gurax.IsValid();
	wxWindowID winid = winid_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	// Function body
	auto pEntity_gurax = new Value_wxInfoBar::EntityT(parent, winid);
	RefPtr<Value_wxInfoBar> pValue_gurax(new Value_wxInfoBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.InfoBar#Create(parent as wx.Window, winid? as Number)
Gurax_DeclareMethodAlias(wxInfoBar, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool winid_validFlag = args_gurax.IsValid();
	wxWindowID winid = winid_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, winid);
	return new Gurax::Value_Bool(rtn);
}

// wx.InfoBar#AddButton(btnid as Number, label? as String)
Gurax_DeclareMethodAlias(wxInfoBar, AddButton_gurax, "AddButton")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("btnid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, AddButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindowID btnid = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	pEntity_gurax->AddButton(btnid, label);
	return Gurax::Value::nil();
}

// wx.InfoBar#Dismiss()
Gurax_DeclareMethodAlias(wxInfoBar, Dismiss_gurax, "Dismiss")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, Dismiss_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Dismiss();
	return Gurax::Value::nil();
}

// wx.InfoBar#RemoveButton(btnid as Number)
Gurax_DeclareMethodAlias(wxInfoBar, RemoveButton_gurax, "RemoveButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("btnid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, RemoveButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindowID btnid = args_gurax.PickNumber<wxWindowID>();
	// Function body
	pEntity_gurax->RemoveButton(btnid);
	return Gurax::Value::nil();
}

// wx.InfoBar#ShowMessage(msg as String, flags? as Number)
Gurax_DeclareMethodAlias(wxInfoBar, ShowMessage_gurax, "ShowMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("msg", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, ShowMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* msg = args_gurax.PickString();
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxICON_INFORMATION;
	// Function body
	pEntity_gurax->ShowMessage(msg, flags);
	return Gurax::Value::nil();
}

// wx.InfoBar#SetShowHideEffects(showEffect as Number, hideEffect as Number)
Gurax_DeclareMethodAlias(wxInfoBar, SetShowHideEffects_gurax, "SetShowHideEffects")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("showEffect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hideEffect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, SetShowHideEffects_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxShowEffect showEffect = args_gurax.PickNumber<wxShowEffect>();
	wxShowEffect hideEffect = args_gurax.PickNumber<wxShowEffect>();
	// Function body
	pEntity_gurax->SetShowHideEffects(showEffect, hideEffect);
	return Gurax::Value::nil();
}

// wx.InfoBar#GetShowEffect()
Gurax_DeclareMethodAlias(wxInfoBar, GetShowEffect_gurax, "GetShowEffect")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, GetShowEffect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxShowEffect rtn = pEntity_gurax->GetShowEffect();
	return new Gurax::Value_Number(rtn);
}

// wx.InfoBar#GetHideEffect()
Gurax_DeclareMethodAlias(wxInfoBar, GetHideEffect_gurax, "GetHideEffect")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, GetHideEffect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxShowEffect rtn = pEntity_gurax->GetHideEffect();
	return new Gurax::Value_Number(rtn);
}

// wx.InfoBar#SetEffectDuration(duration as Number)
Gurax_DeclareMethodAlias(wxInfoBar, SetEffectDuration_gurax, "SetEffectDuration")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("duration", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, SetEffectDuration_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int duration = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetEffectDuration(duration);
	return Gurax::Value::nil();
}

// wx.InfoBar#GetEffectDuration()
Gurax_DeclareMethodAlias(wxInfoBar, GetEffectDuration_gurax, "GetEffectDuration")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, GetEffectDuration_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetEffectDuration();
	return new Gurax::Value_Number(rtn);
}

// wx.InfoBar#SetFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxInfoBar, SetFont_gurax, "SetFont")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxInfoBar, SetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFont& value_font = args_gurax.Pick<Value_wxFont>();
	const wxFont& font = value_font.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetFont(font);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxInfoBar
//------------------------------------------------------------------------------
VType_wxInfoBar VTYPE_wxInfoBar("InfoBar");

void VType_wxInfoBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(InfoBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxInfoBar, Create_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, AddButton_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, Dismiss_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, RemoveButton_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, ShowMessage_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, SetShowHideEffects_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, GetShowEffect_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, GetHideEffect_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, SetEffectDuration_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, GetEffectDuration_gurax));
	Assign(Gurax_CreateMethod(wxInfoBar, SetFont_gurax));
}

//------------------------------------------------------------------------------
// Value_wxInfoBar
//------------------------------------------------------------------------------
VType& Value_wxInfoBar::vtype = VTYPE_wxInfoBar;

String Value_wxInfoBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.InfoBar");
}

//------------------------------------------------------------------------------
// Value_wxInfoBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
