﻿//==============================================================================
// VType_wxSplitterWindow.cpp
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

${help.ComposePropertyHelp(wx.SplitterWindow, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SplitterWindow, `en)}

${help.ComposeMethodHelp(wx.SplitterWindow, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SplitterWindow, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SplitterWindow, `ja)}

${help.ComposeMethodHelp(wx.SplitterWindow, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.SplitterWindow(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(SplitterWindow_gurax, "SplitterWindow")
{
	Declare(VTYPE_wxSplitterWindow, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(SplitterWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSP_3D;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : "splitterWindow";
	// Function body
	auto pEntity_gurax = new Value_wxSplitterWindow::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxSplitterWindow> pValue_gurax(new Value_wxSplitterWindow(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SplitterWindow#Create(parent as wx.Window, id? as Number, point? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxSplitterWindow, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("point", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& point = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSP_3D;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : "splitter";
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, point, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#GetMinimumPaneSize()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetMinimumPaneSize_gurax, "GetMinimumPaneSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetMinimumPaneSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMinimumPaneSize();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetSashGravity()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetSashGravity_gurax, "GetSashGravity")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetSashGravity_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetSashGravity();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetSashPosition()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetSashPosition_gurax, "GetSashPosition")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetSashPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSashPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetSashSize()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetSashSize_gurax, "GetSashSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetSashSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSashSize();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetDefaultSashSize()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetDefaultSashSize_gurax, "GetDefaultSashSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetDefaultSashSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDefaultSashSize();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetSplitMode()
Gurax_DeclareMethodAlias(wxSplitterWindow, GetSplitMode_gurax, "GetSplitMode")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetSplitMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxSplitMode rtn = pEntity_gurax->GetSplitMode();
	return new Gurax::Value_Number(rtn);
}

// wx.SplitterWindow#GetWindow1() {block?}
Gurax_DeclareMethodAlias(wxSplitterWindow, GetWindow1_gurax, "GetWindow1")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetWindow1_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(pEntity_gurax->GetWindow1()));
}

// wx.SplitterWindow#GetWindow2() {block?}
Gurax_DeclareMethodAlias(wxSplitterWindow, GetWindow2_gurax, "GetWindow2")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxSplitterWindow, GetWindow2_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(pEntity_gurax->GetWindow2()));
}

// wx.SplitterWindow#Initialize(window as wx.Window)
Gurax_DeclareMethodAlias(wxSplitterWindow, Initialize_gurax, "Initialize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, Initialize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	pEntity_gurax->Initialize(window);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#IsSashInvisible()
Gurax_DeclareMethodAlias(wxSplitterWindow, IsSashInvisible_gurax, "IsSashInvisible")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, IsSashInvisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSashInvisible();
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#IsSplit()
Gurax_DeclareMethodAlias(wxSplitterWindow, IsSplit_gurax, "IsSplit")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, IsSplit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSplit();
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#OnDoubleClickSash(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, OnDoubleClickSash_gurax, "OnDoubleClickSash")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, OnDoubleClickSash_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->OnDoubleClickSash(x, y);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#OnSashPositionChange(newSashPosition as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, OnSashPositionChange_gurax, "OnSashPositionChange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("newSashPosition", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, OnSashPositionChange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int newSashPosition = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->OnSashPositionChange(newSashPosition);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#OnUnsplit(removed as wx.Window)
Gurax_DeclareMethodAlias(wxSplitterWindow, OnUnsplit_gurax, "OnUnsplit")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("removed", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, OnUnsplit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_removed = args_gurax.Pick<Value_wxWindow>();
	wxWindow* removed = value_removed.GetEntityPtr();
	// Function body
	pEntity_gurax->OnUnsplit(removed);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#ReplaceWindow(winOld as wx.Window, winNew as wx.Window)
Gurax_DeclareMethodAlias(wxSplitterWindow, ReplaceWindow_gurax, "ReplaceWindow")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("winOld", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winNew", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, ReplaceWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_winOld = args_gurax.Pick<Value_wxWindow>();
	wxWindow* winOld = value_winOld.GetEntityPtr();
	Value_wxWindow& value_winNew = args_gurax.Pick<Value_wxWindow>();
	wxWindow* winNew = value_winNew.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->ReplaceWindow(winOld, winNew);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#SetMinimumPaneSize(paneSize as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetMinimumPaneSize_gurax, "SetMinimumPaneSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("paneSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetMinimumPaneSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int paneSize = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinimumPaneSize(paneSize);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SetSashGravity(gravity as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetSashGravity_gurax, "SetSashGravity")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gravity", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetSashGravity_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double gravity = args_gurax.PickNumber<double>();
	// Function body
	pEntity_gurax->SetSashGravity(gravity);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SetSashPosition(position as Number, redraw? as Bool)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetSashPosition_gurax, "SetSashPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("position", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("redraw", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetSashPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int position = args_gurax.PickNumber<int>();
	bool redraw = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetSashPosition(position, redraw);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SetSashSize(size as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetSashSize_gurax, "SetSashSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetSashSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int size = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSashSize(size);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SetSplitMode(mode as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetSplitMode_gurax, "SetSplitMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetSplitMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int mode = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSplitMode(mode);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SetSashInvisible(invisible? as Bool)
Gurax_DeclareMethodAlias(wxSplitterWindow, SetSashInvisible_gurax, "SetSashInvisible")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("invisible", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SetSashInvisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool invisible = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetSashInvisible(invisible);
	return Gurax::Value::nil();
}

// wx.SplitterWindow#SplitHorizontally(window1 as wx.Window, window2 as wx.Window, sashPosition? as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SplitHorizontally_gurax, "SplitHorizontally")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window1", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("window2", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sashPosition", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SplitHorizontally_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window1 = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window1 = value_window1.GetEntityPtr();
	Value_wxWindow& value_window2 = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window2 = value_window2.GetEntityPtr();
	bool sashPosition_validFlag = args_gurax.IsValid();
	int sashPosition = sashPosition_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	bool rtn = pEntity_gurax->SplitHorizontally(window1, window2, sashPosition);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#SplitVertically(window1 as wx.Window, window2 as wx.Window, sashPosition? as Number)
Gurax_DeclareMethodAlias(wxSplitterWindow, SplitVertically_gurax, "SplitVertically")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window1", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("window2", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sashPosition", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, SplitVertically_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window1 = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window1 = value_window1.GetEntityPtr();
	Value_wxWindow& value_window2 = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window2 = value_window2.GetEntityPtr();
	bool sashPosition_validFlag = args_gurax.IsValid();
	int sashPosition = sashPosition_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	bool rtn = pEntity_gurax->SplitVertically(window1, window2, sashPosition);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#Unsplit(toRemove? as wx.Window)
Gurax_DeclareMethodAlias(wxSplitterWindow, Unsplit_gurax, "Unsplit")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("toRemove", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, Unsplit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* toRemove = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	// Function body
	bool rtn = pEntity_gurax->Unsplit(toRemove);
	return new Gurax::Value_Bool(rtn);
}

// wx.SplitterWindow#UpdateSize()
Gurax_DeclareMethodAlias(wxSplitterWindow, UpdateSize_gurax, "UpdateSize")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxSplitterWindow, UpdateSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UpdateSize();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSplitterWindow
//------------------------------------------------------------------------------
VType_wxSplitterWindow VTYPE_wxSplitterWindow("SplitterWindow");

void VType_wxSplitterWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(SplitterWindow_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSplitterWindow, Create_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetMinimumPaneSize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetSashGravity_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetSashPosition_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetSashSize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetDefaultSashSize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetSplitMode_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetWindow1_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, GetWindow2_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, Initialize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, IsSashInvisible_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, IsSplit_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, OnDoubleClickSash_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, OnSashPositionChange_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, OnUnsplit_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, ReplaceWindow_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetMinimumPaneSize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetSashGravity_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetSashPosition_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetSashSize_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetSplitMode_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SetSashInvisible_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SplitHorizontally_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, SplitVertically_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, Unsplit_gurax));
	Assign(Gurax_CreateMethod(wxSplitterWindow, UpdateSize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSplitterWindow
//------------------------------------------------------------------------------
VType& Value_wxSplitterWindow::vtype = VTYPE_wxSplitterWindow;

String Value_wxSplitterWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SplitterWindow");
}

//------------------------------------------------------------------------------
// Value_wxSplitterWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
