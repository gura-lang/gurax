﻿//==============================================================================
// VType_wxGridBagSizer.cpp
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

${help.ComposePropertyHelp(wx.GridBagSizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridBagSizer, `en)}

${help.ComposeMethodHelp(wx.GridBagSizer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridBagSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.GridBagSizer#FindItemAtPoint(pt as wx.Point) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, FindItemAtPoint_gurax, "FindItemAtPoint")
{
	Declare(VTYPE_wxGBSizerItem, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, FindItemAtPoint_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBSizerItem(
		*pEntity_gurax->FindItemAtPoint(pt)));
}

// wx.GridBagSizer#FindItemAtPosition(pos as wx.GBPosition) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, FindItemAtPosition_gurax, "FindItemAtPosition")
{
	Declare(VTYPE_wxGBSizerItem, Flag::None);
	DeclareArg("pos", VTYPE_wxGBPosition, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, FindItemAtPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGBPosition& value_pos = args_gurax.Pick<Value_wxGBPosition>();
	const wxGBPosition& pos = value_pos.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBSizerItem(
		*pEntity_gurax->FindItemAtPosition(pos)));
}

// wx.GridBagSizer#FindItemWithData(userData as wx.Object) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, FindItemWithData_gurax, "FindItemWithData")
{
	Declare(VTYPE_wxGBSizerItem, Flag::None);
	DeclareArg("userData", VTYPE_wxObject, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, FindItemWithData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxObject& value_userData = args_gurax.Pick<Value_wxObject>();
	const wxObject* userData = value_userData.GetEntityPtr();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBSizerItem(
		*pEntity_gurax->FindItemWithData(userData)));
}

// wx.GridBagSizer#GetCellSize(row as Number, col as Number) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, GetCellSize_gurax, "GetCellSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, GetCellSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int row = args_gurax.PickNumber<int>();
	int col = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetCellSize(row, col)));
}

// wx.GridBagSizer#GetEmptyCellSize() {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, GetEmptyCellSize_gurax, "GetEmptyCellSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, GetEmptyCellSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetEmptyCellSize()));
}

// wx.GridBagSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxGridBagSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxGridBagSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

// wx.GridBagSizer#SetEmptyCellSize(sz as wx.Size)
Gurax_DeclareMethodAlias(wxGridBagSizer, SetEmptyCellSize_gurax, "SetEmptyCellSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("sz", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridBagSizer, SetEmptyCellSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_sz = args_gurax.Pick<Value_wxSize>();
	const wxSize& sz = value_sz.GetEntity();
	// Function body
	pEntity_gurax->SetEmptyCellSize(sz);
	return Gurax::Value::nil();
}

// wx.GridBagSizer#Add(window as wx.Window, pos as wx.GBPosition, span? as wx.GBSpan, flag? as Number, border? as Number, userData? as wx.Object) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, Add_gurax, "Add")
{
	Declare(VTYPE_wxSizerItem, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxGBPosition, ArgOccur::Once, ArgFlag::None);
	DeclareArg("span", VTYPE_wxGBSpan, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("userData", VTYPE_wxObject, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, Add_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	Value_wxGBPosition& value_pos = args_gurax.Pick<Value_wxGBPosition>();
	const wxGBPosition& pos = value_pos.GetEntity();
	const wxGBSpan& span = args_gurax.IsValid()? args_gurax.Pick<Value_wxGBSpan>().GetEntity() : wxDefaultSpan;
	bool flag_validFlag = args_gurax.IsValid();
	int flag = flag_validFlag? args_gurax.PickNumber<int>() : 0;
	bool border_validFlag = args_gurax.IsValid();
	int border = border_validFlag? args_gurax.PickNumber<int>() : 0;
	wxObject* userData = args_gurax.IsValid()? args_gurax.Pick<Value_wxObject>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerItem(
		*pEntity_gurax->Add(window, pos, span, flag, border, userData)));
}

// wx.GridBagSizer#CheckForIntersection(item as wx.GBSizerItem, excludeItem? as wx.GBSizerItem)
Gurax_DeclareMethodAlias(wxGridBagSizer, CheckForIntersection_gurax, "CheckForIntersection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_wxGBSizerItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("excludeItem", VTYPE_wxGBSizerItem, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridBagSizer, CheckForIntersection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGBSizerItem& value_item = args_gurax.Pick<Value_wxGBSizerItem>();
	wxGBSizerItem* item = value_item.GetEntityPtr();
	wxGBSizerItem* excludeItem = args_gurax.IsValid()? args_gurax.Pick<Value_wxGBSizerItem>().GetEntityPtr() : nullptr;
	// Function body
	bool rtn = pEntity_gurax->CheckForIntersection(item, excludeItem);
	return new Gurax::Value_Bool(rtn);
}

// wx.GridBagSizer#FindItem(window as wx.Window) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, FindItem_gurax, "FindItem")
{
	Declare(VTYPE_wxGBSizerItem, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, FindItem_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBSizerItem(
		*pEntity_gurax->FindItem(window)));
}

// wx.GridBagSizer#GetItemPosition(window as wx.Window) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, GetItemPosition_gurax, "GetItemPosition")
{
	Declare(VTYPE_wxGBPosition, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, GetItemPosition_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBPosition(
		pEntity_gurax->GetItemPosition(window)));
}

// wx.GridBagSizer#GetItemSpan(window as wx.Window) {block?}
Gurax_DeclareMethodAlias(wxGridBagSizer, GetItemSpan_gurax, "GetItemSpan")
{
	Declare(VTYPE_wxGBSpan, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridBagSizer, GetItemSpan_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBSpan(
		pEntity_gurax->GetItemSpan(window)));
}

// wx.GridBagSizer#SetItemPosition(window as wx.Window, pos as wx.GBPosition)
Gurax_DeclareMethodAlias(wxGridBagSizer, SetItemPosition_gurax, "SetItemPosition")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxGBPosition, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridBagSizer, SetItemPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	Value_wxGBPosition& value_pos = args_gurax.Pick<Value_wxGBPosition>();
	const wxGBPosition& pos = value_pos.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetItemPosition(window, pos);
	return new Gurax::Value_Bool(rtn);
}

// wx.GridBagSizer#SetItemSpan(window as wx.Window, span as wx.GBSpan)
Gurax_DeclareMethodAlias(wxGridBagSizer, SetItemSpan_gurax, "SetItemSpan")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("span", VTYPE_wxGBSpan, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridBagSizer, SetItemSpan_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	Value_wxGBSpan& value_span = args_gurax.Pick<Value_wxGBSpan>();
	const wxGBSpan& span = value_span.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetItemSpan(window, span);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridBagSizer
//------------------------------------------------------------------------------
VType_wxGridBagSizer VTYPE_wxGridBagSizer("GridBagSizer");

void VType_wxGridBagSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFlexGridSizer, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridBagSizer, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, FindItemAtPoint_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, FindItemAtPosition_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, FindItemWithData_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, GetCellSize_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, GetEmptyCellSize_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, RecalcSizes_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, SetEmptyCellSize_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, Add_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, CheckForIntersection_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, FindItem_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, GetItemPosition_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, GetItemSpan_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, SetItemPosition_gurax));
	Assign(Gurax_CreateMethod(wxGridBagSizer, SetItemSpan_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridBagSizer
//------------------------------------------------------------------------------
VType& Value_wxGridBagSizer::vtype = VTYPE_wxGridBagSizer;

String Value_wxGridBagSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridBagSizer");
}

Gurax_EndModuleScope(wx)
