﻿//==============================================================================
// VType_wxMenuBar.cpp
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

${help.ComposePropertyHelp(wx.MenuBar, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MenuBar, `en)}

${help.ComposeMethodHelp(wx.MenuBar, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.MenuBar(style? as Number) {block?}
Gurax_DeclareConstructorAlias(MenuBar_gurax, "MenuBar")
{
	Declare(VTYPE_wxMenuBar, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.MenuBar.
)**");
}

Gurax_ImplementConstructorEx(MenuBar_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxMenuBar::EntityT(style);
	RefPtr<Value_wxMenuBar> pValue_gurax(new Value_wxMenuBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MenuBar#Append(menu as wx.Menu, title as String)
Gurax_DeclareMethodAlias(wxMenuBar, Append_gurax, "Append")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	const char* title = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->Append(menu, title);
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#Check(id as Number, check as Bool)
Gurax_DeclareMethodAlias(wxMenuBar, Check_gurax, "Check")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("check", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Check_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	bool check = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Check(id, check);
	return Gurax::Value::nil();
}

// wx.MenuBar#Enable(id as Number, enable as Bool)
Gurax_DeclareMethodAlias(wxMenuBar, Enable_gurax, "Enable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Enable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	bool enable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Enable(id, enable);
	return Gurax::Value::nil();
}

// wx.MenuBar#IsEnabledTop(pos as Number)
Gurax_DeclareMethodAlias(wxMenuBar, IsEnabledTop_gurax, "IsEnabledTop")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, IsEnabledTop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsEnabledTop(pos);
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#EnableTop(pos as Number, enable as Bool)
Gurax_DeclareMethodAlias(wxMenuBar, EnableTop_gurax, "EnableTop")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, EnableTop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	bool enable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->EnableTop(pos, enable);
	return Gurax::Value::nil();
}

// wx.MenuBar#FindMenu(title as String)
Gurax_DeclareMethodAlias(wxMenuBar, FindMenu_gurax, "FindMenu")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, FindMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	// Function body
	int rtn = pEntity_gurax->FindMenu(title);
	return new Gurax::Value_Number(rtn);
}

// wx.MenuBar#FindMenuItem(menuString as String, itemString as String)
Gurax_DeclareMethodAlias(wxMenuBar, FindMenuItem_gurax, "FindMenuItem")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("menuString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("itemString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, FindMenuItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* menuString = args_gurax.PickString();
	const char* itemString = args_gurax.PickString();
	// Function body
	int rtn = pEntity_gurax->FindMenuItem(menuString, itemString);
	return new Gurax::Value_Number(rtn);
}

// wx.MenuBar#GetHelpString(id as Number)
Gurax_DeclareMethodAlias(wxMenuBar, GetHelpString_gurax, "GetHelpString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetHelpString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	wxString rtn = pEntity_gurax->GetHelpString(id);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.MenuBar#GetLabel(id as Number)
Gurax_DeclareMethodAlias(wxMenuBar, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	wxString rtn = pEntity_gurax->GetLabel(id);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.MenuBar#GetMenu(menuIndex as Number) {block?}
Gurax_DeclareMethodAlias(wxMenuBar, GetMenu_gurax, "GetMenu")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareArg("menuIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t menuIndex = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenu(
		pEntity_gurax->GetMenu(menuIndex)));
}

// wx.MenuBar#GetMenuCount()
Gurax_DeclareMethodAlias(wxMenuBar, GetMenuCount_gurax, "GetMenuCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetMenuCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetMenuCount();
	return new Gurax::Value_Number(rtn);
}

// wx.MenuBar#GetMenuLabel(pos as Number)
Gurax_DeclareMethodAlias(wxMenuBar, GetMenuLabel_gurax, "GetMenuLabel")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetMenuLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	// Function body
	wxString rtn = pEntity_gurax->GetMenuLabel(pos);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.MenuBar#GetMenuLabelText(pos as Number)
Gurax_DeclareMethodAlias(wxMenuBar, GetMenuLabelText_gurax, "GetMenuLabelText")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetMenuLabelText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	// Function body
	wxString rtn = pEntity_gurax->GetMenuLabelText(pos);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.MenuBar#Insert(pos as Number, menu as wx.Menu, title as String)
Gurax_DeclareMethodAlias(wxMenuBar, Insert_gurax, "Insert")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Insert_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	const char* title = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->Insert(pos, menu, title);
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#IsChecked(id as Number)
Gurax_DeclareMethodAlias(wxMenuBar, IsChecked_gurax, "IsChecked")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, IsChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->IsChecked(id);
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#IsEnabled(id as Number)
Gurax_DeclareMethodAlias(wxMenuBar, IsEnabled_gurax, "IsEnabled")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, IsEnabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->IsEnabled(id);
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#Refresh(eraseBackground? as Bool, rect? as wx.Rect)
Gurax_DeclareMethodAlias(wxMenuBar, Refresh_gurax, "Refresh")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("eraseBackground", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Refresh_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool eraseBackground = args_gurax.IsValid()? args_gurax.PickBool() : true;
	const wxRect* rect = args_gurax.IsValid()? args_gurax.Pick<Value_wxRect>().GetEntityPtr() : nullptr;
	// Function body
	pEntity_gurax->Refresh(eraseBackground, rect);
	return Gurax::Value::nil();
}

// wx.MenuBar#Remove(pos as Number) {block?}
Gurax_DeclareMethodAlias(wxMenuBar, Remove_gurax, "Remove")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Remove_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenu(
		pEntity_gurax->Remove(pos)));
}

// wx.MenuBar#Replace(pos as Number, menu as wx.Menu, title as String) {block?}
Gurax_DeclareMethodAlias(wxMenuBar, Replace_gurax, "Replace")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Replace_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu* menu = value_menu.GetEntityPtr();
	const char* title = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenu(
		pEntity_gurax->Replace(pos, menu, title)));
}

// wx.MenuBar#SetHelpString(id as Number, helpString as String)
Gurax_DeclareMethodAlias(wxMenuBar, SetHelpString_gurax, "SetHelpString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("helpString", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, SetHelpString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	const char* helpString = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetHelpString(id, helpString);
	return Gurax::Value::nil();
}

// wx.MenuBar#SetLabel(id as Number, label as String)
Gurax_DeclareMethodAlias(wxMenuBar, SetLabel_gurax, "SetLabel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, SetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	const char* label = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetLabel(id, label);
	return Gurax::Value::nil();
}

// wx.MenuBar#SetMenuLabel(pos as Number, label as String)
Gurax_DeclareMethodAlias(wxMenuBar, SetMenuLabel_gurax, "SetMenuLabel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, SetMenuLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t pos = args_gurax.PickNumber<size_t>();
	const char* label = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetMenuLabel(pos, label);
	return Gurax::Value::nil();
}

// wx.MenuBar#GetFrame() {block?}
Gurax_DeclareMethodAlias(wxMenuBar, GetFrame_gurax, "GetFrame")
{
	Declare(VTYPE_wxFrame, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, GetFrame_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFrame(
		pEntity_gurax->GetFrame()));
}

// wx.MenuBar#IsAttached()
Gurax_DeclareMethodAlias(wxMenuBar, IsAttached_gurax, "IsAttached")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, IsAttached_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsAttached();
	return new Gurax::Value_Bool(rtn);
}

// wx.MenuBar#Attach(frame as wx.Frame)
Gurax_DeclareMethodAlias(wxMenuBar, Attach_gurax, "Attach")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("frame", VTYPE_wxFrame, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Attach_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFrame& value_frame = args_gurax.Pick<Value_wxFrame>();
	wxFrame* frame = value_frame.GetEntityPtr();
	// Function body
	pEntity_gurax->Attach(frame);
	return Gurax::Value::nil();
}

// wx.MenuBar#Detach()
Gurax_DeclareMethodAlias(wxMenuBar, Detach_gurax, "Detach")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxMenuBar, Detach_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Detach();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMenuBar
//------------------------------------------------------------------------------
VType_wxMenuBar VTYPE_wxMenuBar("MenuBar");

void VType_wxMenuBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(MenuBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMenuBar, Append_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Check_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Enable_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, IsEnabledTop_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, EnableTop_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, FindMenu_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, FindMenuItem_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetHelpString_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetMenu_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetMenuCount_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetMenuLabel_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetMenuLabelText_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Insert_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, IsChecked_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, IsEnabled_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Refresh_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Remove_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Replace_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, SetHelpString_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, SetLabel_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, SetMenuLabel_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, GetFrame_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, IsAttached_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Attach_gurax));
	Assign(Gurax_CreateMethod(wxMenuBar, Detach_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMenuBar
//------------------------------------------------------------------------------
VType& Value_wxMenuBar::vtype = VTYPE_wxMenuBar;

String Value_wxMenuBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuBar");
}

//------------------------------------------------------------------------------
// Value_wxMenuBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
