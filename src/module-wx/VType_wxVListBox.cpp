﻿//==============================================================================
// VType_wxVListBox.cpp
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

${help.ComposePropertyHelp(wx.VListBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.VListBox, `en)}

${help.ComposeMethodHelp(wx.VListBox, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.VListBox#Clear()
Gurax_DeclareMethodAlias(wxVListBox, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.VListBox#DeselectAll()
Gurax_DeclareMethodAlias(wxVListBox, DeselectAll_gurax, "DeselectAll")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, DeselectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DeselectAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#GetFirstSelected(cookie as Number)
Gurax_DeclareMethodAlias(wxVListBox, GetFirstSelected_gurax, "GetFirstSelected")
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("cookie", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetFirstSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long cookie = args_gurax.PickNumber<unsigned long>();
	// Function body
	int rtn = pEntity_gurax->GetFirstSelected(cookie);
	return Value_Tuple::Create(new Value_Number(rtn), new Value_Number(cookie));
}

// wx.VListBox#GetItemCount()
Gurax_DeclareMethodAlias(wxVListBox, GetItemCount_gurax, "GetItemCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetItemCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetItemCount();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetMargins() {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetMargins_gurax, "GetMargins")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetMargins()));
}

// wx.VListBox#GetItemRect(item as Number) {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetItemRect_gurax, "GetItemRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetItemRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetItemRect(item)));
}

// wx.VListBox#GetNextSelected(cookie as Number)
Gurax_DeclareMethodAlias(wxVListBox, GetNextSelected_gurax, "GetNextSelected")
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("cookie", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetNextSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long cookie = args_gurax.PickNumber<unsigned long>();
	// Function body
	int rtn = pEntity_gurax->GetNextSelected(cookie);
	return Value_Tuple::Create(new Value_Number(rtn), new Value_Number(cookie));
}

// wx.VListBox#GetSelectedCount()
Gurax_DeclareMethodAlias(wxVListBox, GetSelectedCount_gurax, "GetSelectedCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetSelectedCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetSelectedCount();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetSelection()
Gurax_DeclareMethodAlias(wxVListBox, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetSelectionBackground() {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetSelectionBackground_gurax, "GetSelectionBackground")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, GetSelectionBackground_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetSelectionBackground()));
}

// wx.VListBox#HasMultipleSelection()
Gurax_DeclareMethodAlias(wxVListBox, HasMultipleSelection_gurax, "HasMultipleSelection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, HasMultipleSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasMultipleSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#IsCurrent(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, IsCurrent_gurax, "IsCurrent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, IsCurrent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsCurrent(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#IsSelected(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, IsSelected_gurax, "IsSelected")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, IsSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsSelected(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#Select(item as Number, select? as Bool)
Gurax_DeclareMethodAlias(wxVListBox, Select_gurax, "Select")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("select", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, Select_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	bool select = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->Select(item, select);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SelectAll()
Gurax_DeclareMethodAlias(wxVListBox, SelectAll_gurax, "SelectAll")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SelectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->SelectAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SelectRange(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxVListBox, SelectRange_gurax, "SelectRange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SelectRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t from = args_gurax.PickNumber<size_t>();
	size_t to = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->SelectRange(from, to);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SetItemCount(count as Number)
Gurax_DeclareMethodAlias(wxVListBox, SetItemCount_gurax, "SetItemCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SetItemCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t count = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetItemCount(count);
	return Gurax::Value::nil();
}

// wx.VListBox#SetSelection(selection as Number)
Gurax_DeclareMethodAlias(wxVListBox, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("selection", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int selection = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(selection);
	return Gurax::Value::nil();
}

// wx.VListBox#SetSelectionBackground(col as wx.Colour)
Gurax_DeclareMethodAlias(wxVListBox, SetSelectionBackground_gurax, "SetSelectionBackground")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SetSelectionBackground_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_col = args_gurax.Pick<Value_wxColour>();
	const wxColour& col = value_col.GetEntity();
	// Function body
	pEntity_gurax->SetSelectionBackground(col);
	return Gurax::Value::nil();
}

// wx.VListBox#Toggle(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, Toggle_gurax, "Toggle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, Toggle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->Toggle(item);
	return Gurax::Value::nil();
}

// wx.VListBox#SetMargins(pt as wx.Point)
Gurax_DeclareMethodAlias(wxVListBox, SetMargins_gurax, "SetMargins")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SetMargins_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetMargins(pt);
	return Gurax::Value::nil();
}

// wx.VListBox#SetMarginsXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxVListBox, SetMarginsXY_gurax, "SetMarginsXY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxVListBox, SetMarginsXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCoord x = args_gurax.PickNumber<wxCoord>();
	wxCoord y = args_gurax.PickNumber<wxCoord>();
	// Function body
	pEntity_gurax->SetMargins(x, y);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxVListBox
//------------------------------------------------------------------------------
VType_wxVListBox VTYPE_wxVListBox("VListBox");

void VType_wxVListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxVScrolledWindow, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxVListBox, Clear_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, DeselectAll_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetFirstSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetItemCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetMargins_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetItemRect_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetNextSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelectedCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelectionBackground_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, HasMultipleSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, IsCurrent_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, IsSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, Select_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SelectAll_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SelectRange_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetItemCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetSelectionBackground_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, Toggle_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetMargins_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetMarginsXY_gurax));
}

//------------------------------------------------------------------------------
// Value_wxVListBox
//------------------------------------------------------------------------------
VType& Value_wxVListBox::vtype = VTYPE_wxVListBox;

String Value_wxVListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VListBox");
}

//------------------------------------------------------------------------------
// Value_wxVListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
