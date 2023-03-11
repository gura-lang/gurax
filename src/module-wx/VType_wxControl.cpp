﻿//==============================================================================
// VType_wxControl.cpp
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

${help.ComposePropertyHelp(wx.Control, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Control, `en)}

${help.ComposeMethodHelp(wx.Control, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Control, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Control, `ja)}

${help.ComposeMethodHelp(wx.Control, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Control(parent:nil as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(Control_gurax, "Control")
{
	Declare(VTYPE_wxControl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Control_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxControlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxControl::EntityT(parent, id, pos, size, style, validator, name);
	RefPtr<Value_wxControl> pValue_gurax(new Value_wxControl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Control#Command(event as wx.CommandEvent)
Gurax_DeclareMethodAlias(wxControl, Command_gurax, "Command")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("event", VTYPE_wxCommandEvent, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxControl, Command_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCommandEvent& value_event = args_gurax.Pick<Value_wxCommandEvent>();
	wxCommandEvent& event = value_event.GetEntity();
	// Function body
	pEntity_gurax->Command(event);
	return Gurax::Value::nil();
}

// wx.Control#GetLabel()
Gurax_DeclareMethodAlias(wxControl, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxControl, GetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLabel();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Control#GetLabelText()
Gurax_DeclareMethodAlias(wxControl, GetLabelText_gurax, "GetLabelText")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxControl, GetLabelText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLabelText();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Control#GetSizeFromTextSizeXY(xlen as Number, ylen? as Number) {block?}
Gurax_DeclareMethodAlias(wxControl, GetSizeFromTextSizeXY_gurax, "GetSizeFromTextSizeXY")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("xlen", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ylen", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxControl, GetSizeFromTextSizeXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int xlen = args_gurax.PickNumber<int>();
	bool ylen_validFlag = args_gurax.IsValid();
	int ylen = ylen_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSizeFromTextSize(xlen, ylen)));
}

// wx.Control#GetSizeFromTextSize(tsize as wx.Size) {block?}
Gurax_DeclareMethodAlias(wxControl, GetSizeFromTextSize_gurax, "GetSizeFromTextSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("tsize", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxControl, GetSizeFromTextSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_tsize = args_gurax.Pick<Value_wxSize>();
	const wxSize& tsize = value_tsize.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetSizeFromTextSize(tsize)));
}

// wx.Control#SetLabel(label as String)
Gurax_DeclareMethodAlias(wxControl, SetLabel_gurax, "SetLabel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxControl, SetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetLabel(label);
	return Gurax::Value::nil();
}

// wx.Control#SetLabelText(text as String)
Gurax_DeclareMethodAlias(wxControl, SetLabelText_gurax, "SetLabelText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxControl, SetLabelText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetLabelText(text);
	return Gurax::Value::nil();
}

// wx.Control#SetLabelMarkup(markup as String)
Gurax_DeclareMethodAlias(wxControl, SetLabelMarkup_gurax, "SetLabelMarkup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("markup", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxControl, SetLabelMarkup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* markup = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetLabelMarkup(markup);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxControl
//------------------------------------------------------------------------------
VType_wxControl VTYPE_wxControl("Control");

void VType_wxControl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(Control_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxControl, Command_gurax));
	Assign(Gurax_CreateMethod(wxControl, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxControl, GetLabelText_gurax));
	Assign(Gurax_CreateMethod(wxControl, GetSizeFromTextSizeXY_gurax));
	Assign(Gurax_CreateMethod(wxControl, GetSizeFromTextSize_gurax));
	Assign(Gurax_CreateMethod(wxControl, SetLabel_gurax));
	Assign(Gurax_CreateMethod(wxControl, SetLabelText_gurax));
	Assign(Gurax_CreateMethod(wxControl, SetLabelMarkup_gurax));
}

//------------------------------------------------------------------------------
// Value_wxControl
//------------------------------------------------------------------------------
VType& Value_wxControl::vtype = VTYPE_wxControl;

String Value_wxControl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Control");
}

//------------------------------------------------------------------------------
// Value_wxControl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
