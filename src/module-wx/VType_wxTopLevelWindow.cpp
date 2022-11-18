﻿//==============================================================================
// VType_wxTopLevelWindow.cpp
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

${help.ComposePropertyHelp(wx.TopLevelWindow, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TopLevelWindow, `en)}

${help.ComposeMethodHelp(wx.TopLevelWindow, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.TopLevelWindow(parent:nil as wx.Window, id as Number, title as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(TopLevelWindow_gurax, "TopLevelWindow")
{
	Declare(VTYPE_wxTopLevelWindow, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(TopLevelWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* title = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_FRAME_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFrameNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxTopLevelWindow::EntityT(parent, id, title, pos, size, style, name);
	RefPtr<Value_wxTopLevelWindow> pValue_gurax(new Value_wxTopLevelWindow(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TopLevelWindow#CanSetTransparent()
Gurax_DeclareMethodAlias(wxTopLevelWindow, CanSetTransparent_gurax, "CanSetTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, CanSetTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanSetTransparent();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#CenterOnScreen(direction? as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, CenterOnScreen_gurax, "CenterOnScreen")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, CenterOnScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	pEntity_gurax->CenterOnScreen(direction);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#CentreOnScreen(direction? as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, CentreOnScreen_gurax, "CentreOnScreen")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, CentreOnScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool direction_validFlag = args_gurax.IsValid();
	int direction = direction_validFlag? args_gurax.PickNumber<int>() : wxBOTH;
	// Function body
	pEntity_gurax->CentreOnScreen(direction);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#EnableCloseButton(enable? as Bool)
Gurax_DeclareMethodAlias(wxTopLevelWindow, EnableCloseButton_gurax, "EnableCloseButton")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, EnableCloseButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->EnableCloseButton(enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#GetDefaultItem() {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, GetDefaultItem_gurax, "GetDefaultItem")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, GetDefaultItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetDefaultItem()));
}

// wx.TopLevelWindow#GetIcon() {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIcon(
		pEntity_gurax->GetIcon()));
}

// wx.TopLevelWindow#GetIcons() {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, GetIcons_gurax, "GetIcons")
{
	Declare(VTYPE_wxIconBundle, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, GetIcons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIconBundle(
		pEntity_gurax->GetIcons()));
}

// wx.TopLevelWindow#GetTitle()
Gurax_DeclareMethodAlias(wxTopLevelWindow, GetTitle_gurax, "GetTitle")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, GetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetTitle();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.TopLevelWindow#Iconize(iconize? as Bool)
Gurax_DeclareMethodAlias(wxTopLevelWindow, Iconize_gurax, "Iconize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("iconize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, Iconize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool iconize = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Iconize(iconize);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#IsActive()
Gurax_DeclareMethodAlias(wxTopLevelWindow, IsActive_gurax, "IsActive")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, IsActive_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsActive();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#IsAlwaysMaximized()
Gurax_DeclareMethodAlias(wxTopLevelWindow, IsAlwaysMaximized_gurax, "IsAlwaysMaximized")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, IsAlwaysMaximized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsAlwaysMaximized();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#IsFullScreen()
Gurax_DeclareMethodAlias(wxTopLevelWindow, IsFullScreen_gurax, "IsFullScreen")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, IsFullScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFullScreen();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#IsIconized()
Gurax_DeclareMethodAlias(wxTopLevelWindow, IsIconized_gurax, "IsIconized")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, IsIconized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsIconized();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#IsMaximized()
Gurax_DeclareMethodAlias(wxTopLevelWindow, IsMaximized_gurax, "IsMaximized")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, IsMaximized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsMaximized();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#Layout()
Gurax_DeclareMethodAlias(wxTopLevelWindow, Layout_gurax, "Layout")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, Layout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Layout();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#Maximize(maximize? as Bool)
Gurax_DeclareMethodAlias(wxTopLevelWindow, Maximize_gurax, "Maximize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("maximize", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, Maximize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool maximize = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Maximize(maximize);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#MSWGetSystemMenu() {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, MSWGetSystemMenu_gurax, "MSWGetSystemMenu")
{
	Declare(VTYPE_wxMenu, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, MSWGetSystemMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenu(
		pEntity_gurax->MSWGetSystemMenu()));
}

// wx.TopLevelWindow#RequestUserAttention(flags? as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, RequestUserAttention_gurax, "RequestUserAttention")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, RequestUserAttention_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxUSER_ATTENTION_INFO;
	// Function body
	pEntity_gurax->RequestUserAttention(flags);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#Restore()
Gurax_DeclareMethodAlias(wxTopLevelWindow, Restore_gurax, "Restore")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, Restore_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Restore();
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetDefaultItem(win as wx.Window) {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetDefaultItem_gurax, "SetDefaultItem")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetDefaultItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->SetDefaultItem(win)));
}

// wx.TopLevelWindow#SetTmpDefaultItem(win as wx.Window) {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetTmpDefaultItem_gurax, "SetTmpDefaultItem")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareArg("win", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetTmpDefaultItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_win = args_gurax.Pick<Value_wxWindow>();
	wxWindow* win = value_win.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->SetTmpDefaultItem(win)));
}

// wx.TopLevelWindow#GetTmpDefaultItem() {block?}
Gurax_DeclareMethodAlias(wxTopLevelWindow, GetTmpDefaultItem_gurax, "GetTmpDefaultItem")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, GetTmpDefaultItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetTmpDefaultItem()));
}

// wx.TopLevelWindow#SetIcon(icon as wx.Icon)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetIcon_gurax, "SetIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icon", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_icon = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& icon = value_icon.GetEntity();
	// Function body
	pEntity_gurax->SetIcon(icon);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetIcons(icons as wx.IconBundle)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetIcons_gurax, "SetIcons")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icons", VTYPE_wxIconBundle, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetIcons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIconBundle& value_icons = args_gurax.Pick<Value_wxIconBundle>();
	const wxIconBundle& icons = value_icons.GetEntity();
	// Function body
	pEntity_gurax->SetIcons(icons);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetMaxSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetMaxSize_gurax, "SetMaxSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetMaxSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetMaxSize(size);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetMinSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetMinSize_gurax, "SetMinSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetMinSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetMinSize(size);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetSizeHints(minW as Number, minH as Number, maxW? as Number, maxH? as Number, incW? as Number, incH? as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetSizeHints_gurax, "SetSizeHints")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minW", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minH", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxW", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("maxH", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("incW", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("incH", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetSizeHints_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minW = args_gurax.PickNumber<int>();
	int minH = args_gurax.PickNumber<int>();
	bool maxW_validFlag = args_gurax.IsValid();
	int maxW = maxW_validFlag? args_gurax.PickNumber<int>() : -1;
	bool maxH_validFlag = args_gurax.IsValid();
	int maxH = maxH_validFlag? args_gurax.PickNumber<int>() : -1;
	bool incW_validFlag = args_gurax.IsValid();
	int incW = incW_validFlag? args_gurax.PickNumber<int>() : -1;
	bool incH_validFlag = args_gurax.IsValid();
	int incH = incH_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	pEntity_gurax->SetSizeHints(minW, minH, maxW, maxH, incW, incH);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetTitle(title as String)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetTitle_gurax, "SetTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetTitle(title);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#SetTransparent(alpha as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetTransparent_gurax, "SetTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxByte alpha = args_gurax.PickNumber<wxByte>();
	// Function body
	bool rtn = pEntity_gurax->SetTransparent(alpha);
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#ShouldPreventAppExit()
Gurax_DeclareMethodAlias(wxTopLevelWindow, ShouldPreventAppExit_gurax, "ShouldPreventAppExit")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, ShouldPreventAppExit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShouldPreventAppExit();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#OSXSetModified(modified as Bool)
Gurax_DeclareMethodAlias(wxTopLevelWindow, OSXSetModified_gurax, "OSXSetModified")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("modified", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, OSXSetModified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool modified = args_gurax.PickBool();
	// Function body
	pEntity_gurax->OSXSetModified(modified);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#OSXIsModified()
Gurax_DeclareMethodAlias(wxTopLevelWindow, OSXIsModified_gurax, "OSXIsModified")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, OSXIsModified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->OSXIsModified();
	return new Gurax::Value_Bool(rtn);
}

// wx.TopLevelWindow#SetRepresentedFilename(filename as String)
Gurax_DeclareMethodAlias(wxTopLevelWindow, SetRepresentedFilename_gurax, "SetRepresentedFilename")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, SetRepresentedFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetRepresentedFilename(filename);
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#ShowWithoutActivating()
Gurax_DeclareMethodAlias(wxTopLevelWindow, ShowWithoutActivating_gurax, "ShowWithoutActivating")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, ShowWithoutActivating_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ShowWithoutActivating();
	return Gurax::Value::nil();
}

// wx.TopLevelWindow#ShowFullScreen(show as Bool, style? as Number)
Gurax_DeclareMethodAlias(wxTopLevelWindow, ShowFullScreen_gurax, "ShowFullScreen")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTopLevelWindow, ShowFullScreen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFULLSCREEN_ALL;
	// Function body
	bool rtn = pEntity_gurax->ShowFullScreen(show, style);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTopLevelWindow
//------------------------------------------------------------------------------
VType_wxTopLevelWindow VTYPE_wxTopLevelWindow("TopLevelWindow");

void VType_wxTopLevelWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNonOwnedWindow, Flag::Mutable, Gurax_CreateConstructor(TopLevelWindow_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTopLevelWindow, CanSetTransparent_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, CenterOnScreen_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, CentreOnScreen_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, EnableCloseButton_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, GetDefaultItem_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, GetIcons_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, GetTitle_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, Iconize_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, IsActive_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, IsAlwaysMaximized_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, IsFullScreen_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, IsIconized_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, IsMaximized_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, Layout_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, Maximize_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, MSWGetSystemMenu_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, RequestUserAttention_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, Restore_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetDefaultItem_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetTmpDefaultItem_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, GetTmpDefaultItem_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetIcon_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetIcons_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetMaxSize_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetMinSize_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetSizeHints_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetTitle_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetTransparent_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, ShouldPreventAppExit_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, OSXSetModified_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, OSXIsModified_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, SetRepresentedFilename_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, ShowWithoutActivating_gurax));
	Assign(Gurax_CreateMethod(wxTopLevelWindow, ShowFullScreen_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTopLevelWindow
//------------------------------------------------------------------------------
VType& Value_wxTopLevelWindow::vtype = VTYPE_wxTopLevelWindow;

String Value_wxTopLevelWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TopLevelWindow");
}

//------------------------------------------------------------------------------
// Value_wxTopLevelWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
