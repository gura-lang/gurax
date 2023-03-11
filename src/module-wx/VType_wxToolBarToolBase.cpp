﻿//==============================================================================
// VType_wxToolBarToolBase.cpp
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

${help.ComposePropertyHelp(wx.ToolBarToolBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ToolBarToolBase, `en)}

${help.ComposeMethodHelp(wx.ToolBarToolBase, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ToolBarToolBase, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ToolBarToolBase, `ja)}

${help.ComposeMethodHelp(wx.ToolBarToolBase, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ToolBarToolBase#GetId()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetId_gurax, "GetId")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetId();
	return new Gurax::Value_Number(rtn);
}

// wx.ToolBarToolBase#GetControl() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetControl_gurax, "GetControl")
{
	Declare(VTYPE_wxControl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxControl(
		pEntity_gurax->GetControl()));
}

// wx.ToolBarToolBase#IsStretchable()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsStretchable_gurax, "IsStretchable")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsStretchable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsStretchable();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#IsButton()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsButton_gurax, "IsButton")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsButton();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#IsControl()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsControl_gurax, "IsControl")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsControl();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#IsSeparator()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsSeparator_gurax, "IsSeparator")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsSeparator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSeparator();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#IsStretchableSpace()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsStretchableSpace_gurax, "IsStretchableSpace")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsStretchableSpace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsStretchableSpace();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#GetStyle()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.ToolBarToolBase#GetKind()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetKind_gurax, "GetKind")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetKind_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxItemKind rtn = pEntity_gurax->GetKind();
	return new Gurax::Value_Number(rtn);
}

// wx.ToolBarToolBase#MakeStretchable()
Gurax_DeclareMethodAlias(wxToolBarToolBase, MakeStretchable_gurax, "MakeStretchable")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, MakeStretchable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeStretchable();
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#IsEnabled()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsEnabled_gurax, "IsEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsEnabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEnabled();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#IsToggled()
Gurax_DeclareMethodAlias(wxToolBarToolBase, IsToggled_gurax, "IsToggled")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, IsToggled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsToggled();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#CanBeToggled()
Gurax_DeclareMethodAlias(wxToolBarToolBase, CanBeToggled_gurax, "CanBeToggled")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, CanBeToggled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanBeToggled();
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#GetNormalBitmap() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetNormalBitmap_gurax, "GetNormalBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetNormalBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetNormalBitmap()));
}

// wx.ToolBarToolBase#GetDisabledBitmap() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetDisabledBitmap_gurax, "GetDisabledBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetDisabledBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetDisabledBitmap()));
}

// wx.ToolBarToolBase#GetBitmap() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetBitmap_gurax, "GetBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetBitmap()));
}

// wx.ToolBarToolBase#GetLabel()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetLabel_gurax, processor_gurax, argument_gurax)
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

// wx.ToolBarToolBase#GetShortHelp()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetShortHelp_gurax, "GetShortHelp")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetShortHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetShortHelp();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.ToolBarToolBase#GetLongHelp()
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetLongHelp_gurax, "GetLongHelp")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetLongHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLongHelp();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.ToolBarToolBase#GetClientData() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetClientData_gurax, "GetClientData")
{
	Declare(VTYPE_wxObject, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxObject(
		*pEntity_gurax->GetClientData()));
}

// wx.ToolBarToolBase#Enable(enable as Bool)
Gurax_DeclareMethodAlias(wxToolBarToolBase, Enable_gurax, "Enable")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, Enable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.PickBool();
	// Function body
	bool rtn = pEntity_gurax->Enable(enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#Toggle(toggle as Bool)
Gurax_DeclareMethodAlias(wxToolBarToolBase, Toggle_gurax, "Toggle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("toggle", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, Toggle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool toggle = args_gurax.PickBool();
	// Function body
	bool rtn = pEntity_gurax->Toggle(toggle);
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#SetToggle(toggle as Bool)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetToggle_gurax, "SetToggle")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("toggle", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetToggle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool toggle = args_gurax.PickBool();
	// Function body
	bool rtn = pEntity_gurax->SetToggle(toggle);
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#SetShortHelp(help as String)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetShortHelp_gurax, "SetShortHelp")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("help", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetShortHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* help = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetShortHelp(help);
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#SetLongHelp(help as String)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetLongHelp_gurax, "SetLongHelp")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("help", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetLongHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* help = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetLongHelp(help);
	return new Gurax::Value_Bool(rtn);
}

// wx.ToolBarToolBase#SetNormalBitmap(bmp as wx.Bitmap)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetNormalBitmap_gurax, "SetNormalBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetNormalBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bmp = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bmp = value_bmp.GetEntity();
	// Function body
	pEntity_gurax->SetNormalBitmap(bmp);
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#SetDisabledBitmap(bmp as wx.Bitmap)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetDisabledBitmap_gurax, "SetDisabledBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetDisabledBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bmp = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bmp = value_bmp.GetEntity();
	// Function body
	pEntity_gurax->SetDisabledBitmap(bmp);
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#SetLabel(label as String)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetLabel_gurax, "SetLabel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetLabel_gurax, processor_gurax, argument_gurax)
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

// wx.ToolBarToolBase#SetClientData(clientData as wx.Object)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetClientData_gurax, "SetClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("clientData", VTYPE_wxObject, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxObject& value_clientData = args_gurax.Pick<Value_wxObject>();
	wxObject* clientData = value_clientData.GetEntityPtr();
	// Function body
	pEntity_gurax->SetClientData(clientData);
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#Detach()
Gurax_DeclareMethodAlias(wxToolBarToolBase, Detach_gurax, "Detach")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, Detach_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Detach();
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#Attach(tbar as wx.ToolBar)
Gurax_DeclareMethodAlias(wxToolBarToolBase, Attach_gurax, "Attach")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("tbar", VTYPE_wxToolBar, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, Attach_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxToolBar& value_tbar = args_gurax.Pick<Value_wxToolBar>();
	wxToolBar* tbar = value_tbar.GetEntityPtr();
	// Function body
	pEntity_gurax->Attach(tbar);
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#SetDropdownMenu(menu as wx.Menu)
Gurax_DeclareMethodAlias(wxToolBarToolBase, SetDropdownMenu_gurax, "SetDropdownMenu")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, SetDropdownMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDropdownMenu(menu);
	return Gurax::Value::nil();
}

// wx.ToolBarToolBase#GetDropdownMenu() {block?}
Gurax_DeclareMethodAlias(wxToolBarToolBase, GetDropdownMenu_gurax, "GetDropdownMenu")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxToolBarToolBase, GetDropdownMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenu(
		pEntity_gurax->GetDropdownMenu()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxToolBarToolBase
//------------------------------------------------------------------------------
VType_wxToolBarToolBase VTYPE_wxToolBarToolBase("ToolBarToolBase");

void VType_wxToolBarToolBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetId_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetControl_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsStretchable_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsButton_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsControl_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsSeparator_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsStretchableSpace_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetKind_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, MakeStretchable_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsEnabled_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, IsToggled_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, CanBeToggled_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetNormalBitmap_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetDisabledBitmap_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetShortHelp_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetLongHelp_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetClientData_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, Enable_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, Toggle_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetToggle_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetShortHelp_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetLongHelp_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetNormalBitmap_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetDisabledBitmap_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetLabel_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetClientData_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, Detach_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, Attach_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, SetDropdownMenu_gurax));
	Assign(Gurax_CreateMethod(wxToolBarToolBase, GetDropdownMenu_gurax));
}

//------------------------------------------------------------------------------
// Value_wxToolBarToolBase
//------------------------------------------------------------------------------
VType& Value_wxToolBarToolBase::vtype = VTYPE_wxToolBarToolBase;

String Value_wxToolBarToolBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ToolBarToolBase");
}

Gurax_EndModuleScope(wx)
