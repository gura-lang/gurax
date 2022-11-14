﻿//==============================================================================
// VType_wxSettableHeaderColumn.cpp
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

${help.ComposePropertyHelp(wx.SettableHeaderColumn, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SettableHeaderColumn, `en)}

${help.ComposeMethodHelp(wx.SettableHeaderColumn, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SettableHeaderColumn#SetTitle(title as String)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetTitle_gurax, "SetTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetTitle_gurax, processor_gurax, argument_gurax)
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

// wx.SettableHeaderColumn#SetBitmap(bitmap as wx.Bitmap)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetBitmap_gurax, "SetBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	// Function body
	pEntity_gurax->SetBitmap(bitmap);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWidth(width);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetMinWidth(minWidth as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetMinWidth_gurax, "SetMinWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minWidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetMinWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minWidth = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinWidth(minWidth);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetAlignment(align as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetAlignment_gurax, "SetAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("align", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxAlignment align = args_gurax.PickNumber<wxAlignment>();
	// Function body
	pEntity_gurax->SetAlignment(align);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetFlags(flags as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetFlags_gurax, "SetFlags")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlags(flags);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#ChangeFlag(flag as Number, set as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, ChangeFlag_gurax, "ChangeFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("set", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, ChangeFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flag = args_gurax.PickNumber<int>();
	bool set = args_gurax.PickBool();
	// Function body
	pEntity_gurax->ChangeFlag(flag, set);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetFlag(flag as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetFlag_gurax, "SetFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flag = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlag(flag);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#ClearFlag(flag as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, ClearFlag_gurax, "ClearFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, ClearFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flag = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ClearFlag(flag);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#ToggleFlag(flag as Number)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, ToggleFlag_gurax, "ToggleFlag")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, ToggleFlag_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flag = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ToggleFlag(flag);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetResizeable(resizable as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetResizeable_gurax, "SetResizeable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("resizable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetResizeable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool resizable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetResizeable(resizable);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetSortable(sortable as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetSortable_gurax, "SetSortable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sortable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetSortable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool sortable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetSortable(sortable);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetReorderable(reorderable as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetReorderable_gurax, "SetReorderable")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("reorderable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetReorderable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool reorderable = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetReorderable(reorderable);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetHidden(hidden as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetHidden_gurax, "SetHidden")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hidden", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetHidden_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool hidden = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetHidden(hidden);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#UnsetAsSortKey()
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, UnsetAsSortKey_gurax, "UnsetAsSortKey")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, UnsetAsSortKey_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UnsetAsSortKey();
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#SetSortOrder(ascending as Bool)
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, SetSortOrder_gurax, "SetSortOrder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ascending", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, SetSortOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool ascending = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetSortOrder(ascending);
	return Gurax::Value::nil();
}

// wx.SettableHeaderColumn#ToggleSortOrder()
Gurax_DeclareMethodAlias(wxSettableHeaderColumn, ToggleSortOrder_gurax, "ToggleSortOrder")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxSettableHeaderColumn, ToggleSortOrder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ToggleSortOrder();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSettableHeaderColumn
//------------------------------------------------------------------------------
VType_wxSettableHeaderColumn VTYPE_wxSettableHeaderColumn("SettableHeaderColumn");

void VType_wxSettableHeaderColumn::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHeaderColumn, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetTitle_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetMinWidth_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetFlags_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, ChangeFlag_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetFlag_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, ClearFlag_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, ToggleFlag_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetResizeable_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetSortable_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetReorderable_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetHidden_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, UnsetAsSortKey_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, SetSortOrder_gurax));
	Assign(Gurax_CreateMethod(wxSettableHeaderColumn, ToggleSortOrder_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSettableHeaderColumn
//------------------------------------------------------------------------------
VType& Value_wxSettableHeaderColumn::vtype = VTYPE_wxSettableHeaderColumn;

String Value_wxSettableHeaderColumn::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SettableHeaderColumn");
}

Gurax_EndModuleScope(wx)
