//==============================================================================
// VType_wxHVScrolledWindow.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HVScrolledWindow#EnablePhysicalScrolling(vscrolling? as Bool, hscrolling? as Bool)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, EnablePhysicalScrolling_gurax, "EnablePhysicalScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("vscrolling", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("hscrolling", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, EnablePhysicalScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool vscrolling = args_gurax.IsValid()? args_gurax.PickBool() : true;
	bool hscrolling = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->EnablePhysicalScrolling(vscrolling, hscrolling);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#GetRowColumnCount() {block?}
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetRowColumnCount_gurax, "GetRowColumnCount")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetRowColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetRowColumnCount()));
}

// wx.HVScrolledWindow#GetVisibleBegin() {block?}
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleBegin_gurax, "GetVisibleBegin")
{
	Declare(VTYPE_wxPosition, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleBegin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPosition(
		pEntity_gurax->GetVisibleBegin()));
}

// wx.HVScrolledWindow#GetVisibleEnd() {block?}
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleEnd_gurax, "GetVisibleEnd")
{
	Declare(VTYPE_wxPosition, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPosition(
		pEntity_gurax->GetVisibleEnd()));
}

// wx.HVScrolledWindow#SetRowColumnCount(rowCount as Number, columnCount as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, SetRowColumnCount_gurax, "SetRowColumnCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rowCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("columnCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, SetRowColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t rowCount = args_gurax.PickNumber<size_t>();
	size_t columnCount = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetRowColumnCount(rowCount, columnCount);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#IsVisible(row as Number, column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, IsVisible_gurax, "IsVisible")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, IsVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsVisible(row, column);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#RefreshRowColumn(row as Number, column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshRowColumn_gurax, "RefreshRowColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshRowColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RefreshRowColumn(row, column);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#RefreshRowsColumns(fromRow as Number, toRow as Number, fromColumn as Number, toColumn as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshRowsColumns_gurax, "RefreshRowsColumns")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("fromRow", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("toRow", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fromColumn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("toColumn", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshRowsColumns_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t fromRow = args_gurax.PickNumber<size_t>();
	size_t toRow = args_gurax.PickNumber<size_t>();
	size_t fromColumn = args_gurax.PickNumber<size_t>();
	size_t toColumn = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RefreshRowsColumns(fromRow, toRow, fromColumn, toColumn);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#ScrollToRowColumn(row as Number, column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollToRowColumn_gurax, "ScrollToRowColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollToRowColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->ScrollToRowColumn(row, column);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#VirtualHitTest(x as Number, y as Number) {block?}
Gurax_DeclareMethodAlias(wxHVScrolledWindow, VirtualHitTest_gurax, "VirtualHitTest")
{
	Declare(VTYPE_wxPosition, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, VirtualHitTest_gurax, processor_gurax, argument_gurax)
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
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPosition(
		pEntity_gurax->VirtualHitTest(x, y)));
}

// wx.HVScrolledWindow#GetColumnCount()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetColumnCount();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#GetVisibleColumnsBegin()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleColumnsBegin_gurax, "GetVisibleColumnsBegin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleColumnsBegin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleColumnsBegin();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#GetVisibleColumnsEnd()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleColumnsEnd_gurax, "GetVisibleColumnsEnd")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleColumnsEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleColumnsEnd();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#IsColumnVisible(column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, IsColumnVisible_gurax, "IsColumnVisible")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, IsColumnVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsColumnVisible(column);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#RefreshColumn(column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshColumn_gurax, "RefreshColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RefreshColumn(column);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#RefreshColumns(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshColumns_gurax, "RefreshColumns")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshColumns_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->RefreshColumns(from, to);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#ScrollColumnPages(pages as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollColumnPages_gurax, "ScrollColumnPages")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pages", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollColumnPages_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pages = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollColumnPages(pages);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#ScrollColumns(columns as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollColumns_gurax, "ScrollColumns")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("columns", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollColumns_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int columns = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollColumns(columns);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#ScrollToColumn(column as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollToColumn_gurax, "ScrollToColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollToColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t column = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->ScrollToColumn(column);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#SetColumnCount(columnCount as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, SetColumnCount_gurax, "SetColumnCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("columnCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, SetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t columnCount = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetColumnCount(columnCount);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#GetRowCount()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetRowCount_gurax, "GetRowCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetRowCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetRowCount();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#GetVisibleRowsBegin()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleRowsBegin_gurax, "GetVisibleRowsBegin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleRowsBegin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleRowsBegin();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#GetVisibleRowsEnd()
Gurax_DeclareMethodAlias(wxHVScrolledWindow, GetVisibleRowsEnd_gurax, "GetVisibleRowsEnd")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, GetVisibleRowsEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleRowsEnd();
	return new Gurax::Value_Number(rtn);
}

// wx.HVScrolledWindow#IsRowVisible(row as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, IsRowVisible_gurax, "IsRowVisible")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, IsRowVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsRowVisible(row);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#RefreshRow(row as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshRow_gurax, "RefreshRow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RefreshRow(row);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#RefreshRows(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, RefreshRows_gurax, "RefreshRows")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, RefreshRows_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->RefreshRows(from, to);
	return Gurax::Value::nil();
}

// wx.HVScrolledWindow#ScrollRowPages(pages as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollRowPages_gurax, "ScrollRowPages")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pages", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollRowPages_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pages = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollRowPages(pages);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#ScrollRows(rows as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollRows_gurax, "ScrollRows")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("rows", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollRows_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int rows = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollRows(rows);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#ScrollToRow(row as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, ScrollToRow_gurax, "ScrollToRow")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, ScrollToRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t row = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->ScrollToRow(row);
	return new Gurax::Value_Bool(rtn);
}

// wx.HVScrolledWindow#SetRowCount(rowCount as Number)
Gurax_DeclareMethodAlias(wxHVScrolledWindow, SetRowCount_gurax, "SetRowCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rowCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHVScrolledWindow, SetRowCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t rowCount = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetRowCount(rowCount);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHVScrolledWindow
//------------------------------------------------------------------------------
VType_wxHVScrolledWindow VTYPE_wxHVScrolledWindow("HVScrolledWindow");

void VType_wxHVScrolledWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, EnablePhysicalScrolling_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetRowColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleBegin_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleEnd_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, SetRowColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, IsVisible_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshRowColumn_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshRowsColumns_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollToRowColumn_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, VirtualHitTest_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleColumnsBegin_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleColumnsEnd_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, IsColumnVisible_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshColumn_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshColumns_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollColumnPages_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollColumns_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollToColumn_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, SetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetRowCount_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleRowsBegin_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, GetVisibleRowsEnd_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, IsRowVisible_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshRow_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, RefreshRows_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollRowPages_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollRows_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, ScrollToRow_gurax));
	Assign(Gurax_CreateMethod(wxHVScrolledWindow, SetRowCount_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHVScrolledWindow
//------------------------------------------------------------------------------
VType& Value_wxHVScrolledWindow::vtype = VTYPE_wxHVScrolledWindow;

String Value_wxHVScrolledWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HVScrolledWindow");
}

//------------------------------------------------------------------------------
// Value_wxHVScrolledWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
