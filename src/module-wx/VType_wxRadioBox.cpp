﻿//==============================================================================
// VType_wxRadioBox.cpp
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

${help.ComposePropertyHelp(wx.RadioBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RadioBox, `en)}

${help.ComposeMethodHelp(wx.RadioBox, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RadioBox, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RadioBox, `ja)}

${help.ComposeMethodHelp(wx.RadioBox, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RadioBox(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, choices[]? as String, majorDimension? as Number, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(RadioBox_gurax, "RadioBox")
{
	Declare(VTYPE_wxRadioBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareArg("majorDimension", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RadioBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	bool majorDimension_validFlag = args_gurax.IsValid();
	int majorDimension = majorDimension_validFlag? args_gurax.PickNumber<int>() : 0;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxRA_SPECIFY_COLS;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxRadioBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxRadioBox::EntityT(parent, id, label, pos, size, choices, majorDimension, style, validator, name);
	RefPtr<Value_wxRadioBox> pValue_gurax(new Value_wxRadioBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RadioBox#Enable(n as Number, enable? as Bool)
Gurax_DeclareMethodAlias(wxRadioBox, Enable_gurax, "Enable")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, Enable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	bool enable = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->Enable(n, enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.RadioBox#FindString(string as String, bCase? as Bool)
Gurax_DeclareMethodAlias(wxRadioBox, FindString_gurax, "FindString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bCase", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, FindString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	bool bCase = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	int rtn = pEntity_gurax->FindString(string, bCase);
	return new Gurax::Value_Number(rtn);
}

// wx.RadioBox#GetColumnCount()
Gurax_DeclareMethodAlias(wxRadioBox, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetColumnCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RadioBox#GetItemFromPoint(pt as wx.Point)
Gurax_DeclareMethodAlias(wxRadioBox, GetItemFromPoint_gurax, "GetItemFromPoint")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetItemFromPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	// Function body
	int rtn = pEntity_gurax->GetItemFromPoint(pt);
	return new Gurax::Value_Number(rtn);
}

// wx.RadioBox#GetItemHelpText(item as Number)
Gurax_DeclareMethodAlias(wxRadioBox, GetItemHelpText_gurax, "GetItemHelpText")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetItemHelpText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	// Function body
	wxString rtn = pEntity_gurax->GetItemHelpText(item);
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.RadioBox#GetItemToolTip(item as Number) {block?}
Gurax_DeclareMethodAlias(wxRadioBox, GetItemToolTip_gurax, "GetItemToolTip")
{
	Declare(VTYPE_wxToolTip, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRadioBox, GetItemToolTip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolTip(
		*pEntity_gurax->GetItemToolTip(item)));
}

// wx.RadioBox#GetRowCount()
Gurax_DeclareMethodAlias(wxRadioBox, GetRowCount_gurax, "GetRowCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetRowCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetRowCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RadioBox#IsItemEnabled(n as Number)
Gurax_DeclareMethodAlias(wxRadioBox, IsItemEnabled_gurax, "IsItemEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, IsItemEnabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	bool rtn = pEntity_gurax->IsItemEnabled(n);
	return new Gurax::Value_Bool(rtn);
}

// wx.RadioBox#IsItemShown(n as Number)
Gurax_DeclareMethodAlias(wxRadioBox, IsItemShown_gurax, "IsItemShown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, IsItemShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	bool rtn = pEntity_gurax->IsItemShown(n);
	return new Gurax::Value_Bool(rtn);
}

// wx.RadioBox#SetItemHelpText(item as Number, helptext as String)
Gurax_DeclareMethodAlias(wxRadioBox, SetItemHelpText_gurax, "SetItemHelpText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("helptext", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, SetItemHelpText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	const char* helptext = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetItemHelpText(item, helptext);
	return Gurax::Value::nil();
}

// wx.RadioBox#SetItemToolTip(item as Number, text as String)
Gurax_DeclareMethodAlias(wxRadioBox, SetItemToolTip_gurax, "SetItemToolTip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, SetItemToolTip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	const char* text = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetItemToolTip(item, text);
	return Gurax::Value::nil();
}

// wx.RadioBox#SetSelection(n as Number)
Gurax_DeclareMethodAlias(wxRadioBox, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(n);
	return Gurax::Value::nil();
}

// wx.RadioBox#Show(item as Number, show? as Bool)
Gurax_DeclareMethodAlias(wxRadioBox, Show_gurax, "Show")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->Show(item, show);
	return new Gurax::Value_Bool(rtn);
}

// wx.RadioBox#GetCount()
Gurax_DeclareMethodAlias(wxRadioBox, GetCount_gurax, "GetCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RadioBox#GetString(n as Number)
Gurax_DeclareMethodAlias(wxRadioBox, GetString_gurax, "GetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	wxString rtn = pEntity_gurax->GetString(n);
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.RadioBox#SetString(n as Number, string as String)
Gurax_DeclareMethodAlias(wxRadioBox, SetString_gurax, "SetString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, SetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	const char* string = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetString(n, string);
	return Gurax::Value::nil();
}

// wx.RadioBox#GetSelection()
Gurax_DeclareMethodAlias(wxRadioBox, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRadioBox, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRadioBox
//------------------------------------------------------------------------------
VType_wxRadioBox VTYPE_wxRadioBox("RadioBox");

void VType_wxRadioBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(RadioBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRadioBox, Enable_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, FindString_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetItemFromPoint_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetItemHelpText_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetItemToolTip_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetRowCount_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, IsItemEnabled_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, IsItemShown_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, SetItemHelpText_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, SetItemToolTip_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, Show_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetCount_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetString_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, SetString_gurax));
	Assign(Gurax_CreateMethod(wxRadioBox, GetSelection_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRadioBox
//------------------------------------------------------------------------------
VType& Value_wxRadioBox::vtype = VTYPE_wxRadioBox;

String Value_wxRadioBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RadioBox");
}

//------------------------------------------------------------------------------
// Value_wxRadioBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
