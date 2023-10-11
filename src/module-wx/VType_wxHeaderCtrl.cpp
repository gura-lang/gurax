﻿//==============================================================================
// VType_wxHeaderCtrl.cpp
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

${help.ComposePropertyHelp(wx.HeaderCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HeaderCtrl, `en)}

${help.ComposeMethodHelp(wx.HeaderCtrl, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HeaderCtrl, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HeaderCtrl, `ja)}

${help.ComposeMethodHelp(wx.HeaderCtrl, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HeaderCtrl#Create(parent as wx.Window, winid? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxHeaderCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxHD_DEFAULT_STYLE;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxHeaderCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, winid, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.HeaderCtrl#SetColumnCount(count as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, SetColumnCount_gurax, "SetColumnCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, SetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int count = args_gurax.PickNumber<unsigned int>();
	// Function body
	pEntity_gurax->SetColumnCount(count);
	return Gurax::Value::nil();
}

// wx.HeaderCtrl#GetColumnCount()
Gurax_DeclareMethodAlias(wxHeaderCtrl, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetColumnCount();
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderCtrl#IsEmpty()
Gurax_DeclareMethodAlias(wxHeaderCtrl, IsEmpty_gurax, "IsEmpty")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, IsEmpty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEmpty();
	return new Gurax::Value_Bool(rtn);
}

// wx.HeaderCtrl#UpdateColumn(idx as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, UpdateColumn_gurax, "UpdateColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, UpdateColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int idx = args_gurax.PickNumber<unsigned int>();
	// Function body
	pEntity_gurax->UpdateColumn(idx);
	return Gurax::Value::nil();
}

// wx.HeaderCtrl#SetColumnsOrder(order[] as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, SetColumnsOrder_gurax, "SetColumnsOrder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, SetColumnsOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayInt order = Util::CreateArrayInt(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetColumnsOrder(order);
	return Gurax::Value::nil();
}

// wx.HeaderCtrl#GetColumnsOrder()
Gurax_DeclareMethodAlias(wxHeaderCtrl, GetColumnsOrder_gurax, "GetColumnsOrder")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, GetColumnsOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayInt rtn = pEntity_gurax->GetColumnsOrder();
	return Util::CreateList(rtn);
}

// wx.HeaderCtrl#GetColumnAt(pos as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, GetColumnAt_gurax, "GetColumnAt")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, GetColumnAt_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	// Function body
	unsigned int rtn = pEntity_gurax->GetColumnAt(pos);
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderCtrl#GetColumnPos(idx as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, GetColumnPos_gurax, "GetColumnPos")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, GetColumnPos_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int idx = args_gurax.PickNumber<unsigned int>();
	// Function body
	unsigned int rtn = pEntity_gurax->GetColumnPos(idx);
	return new Gurax::Value_Number(rtn);
}

// wx.HeaderCtrl#ResetColumnsOrder()
Gurax_DeclareMethodAlias(wxHeaderCtrl, ResetColumnsOrder_gurax, "ResetColumnsOrder")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, ResetColumnsOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ResetColumnsOrder();
	return Gurax::Value::nil();
}

// wx.HeaderCtrl#ShowColumnsMenu(pt as wx.Point, title? as String)
Gurax_DeclareMethodAlias(wxHeaderCtrl, ShowColumnsMenu_gurax, "ShowColumnsMenu")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, ShowColumnsMenu_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	bool title_validFlag = args_gurax.IsValid();
	wxString title = title_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	bool rtn = pEntity_gurax->ShowColumnsMenu(pt, title);
	return new Gurax::Value_Bool(rtn);
}

// wx.HeaderCtrl#AddColumnsItems(menu as wx.Menu, idColumnsBase? as Number)
Gurax_DeclareMethodAlias(wxHeaderCtrl, AddColumnsItems_gurax, "AddColumnsItems")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("menu", VTYPE_wxMenu, ArgOccur::Once, ArgFlag::None);
	DeclareArg("idColumnsBase", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, AddColumnsItems_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxMenu& value_menu = args_gurax.Pick<Value_wxMenu>();
	wxMenu& menu = value_menu.GetEntity();
	bool idColumnsBase_validFlag = args_gurax.IsValid();
	int idColumnsBase = idColumnsBase_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->AddColumnsItems(menu, idColumnsBase);
	return Gurax::Value::nil();
}

// wx.HeaderCtrl#ShowCustomizeDialog()
Gurax_DeclareMethodAlias(wxHeaderCtrl, ShowCustomizeDialog_gurax, "ShowCustomizeDialog")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, ShowCustomizeDialog_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShowCustomizeDialog();
	return new Gurax::Value_Bool(rtn);
}

// wx.HeaderCtrl#GetColumnTitleWidth(col as wx.HeaderColumn)
Gurax_DeclareMethodAlias(wxHeaderCtrl, GetColumnTitleWidth_gurax, "GetColumnTitleWidth")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("col", VTYPE_wxHeaderColumn, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHeaderCtrl, GetColumnTitleWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxHeaderColumn& value_col = args_gurax.Pick<Value_wxHeaderColumn>();
	const wxHeaderColumn& col = value_col.GetEntity();
	// Function body
	int rtn = pEntity_gurax->GetColumnTitleWidth(col);
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHeaderCtrl
//------------------------------------------------------------------------------
VType_wxHeaderCtrl VTYPE_wxHeaderCtrl("HeaderCtrl");

void VType_wxHeaderCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHeaderCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, SetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, IsEmpty_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, UpdateColumn_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, SetColumnsOrder_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, GetColumnsOrder_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, GetColumnAt_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, GetColumnPos_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, ResetColumnsOrder_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, ShowColumnsMenu_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, AddColumnsItems_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, ShowCustomizeDialog_gurax));
	Assign(Gurax_CreateMethod(wxHeaderCtrl, GetColumnTitleWidth_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHeaderCtrl
//------------------------------------------------------------------------------
VType& Value_wxHeaderCtrl::vtype = VTYPE_wxHeaderCtrl;

String Value_wxHeaderCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HeaderCtrl");
}

//------------------------------------------------------------------------------
// Value_wxHeaderCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
