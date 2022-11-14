﻿//==============================================================================
// VType_wxHScrolledWindow.cpp
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

${help.ComposePropertyHelp(wx.HScrolledWindow, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HScrolledWindow, `en)}

${help.ComposeMethodHelp(wx.HScrolledWindow, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HScrolledWindow#GetColumnCount()
Gurax_DeclareMethodAlias(wxHScrolledWindow, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetColumnCount();
	return new Gurax::Value_Number(rtn);
}

// wx.HScrolledWindow#GetVisibleColumnsBegin()
Gurax_DeclareMethodAlias(wxHScrolledWindow, GetVisibleColumnsBegin_gurax, "GetVisibleColumnsBegin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, GetVisibleColumnsBegin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleColumnsBegin();
	return new Gurax::Value_Number(rtn);
}

// wx.HScrolledWindow#GetVisibleColumnsEnd()
Gurax_DeclareMethodAlias(wxHScrolledWindow, GetVisibleColumnsEnd_gurax, "GetVisibleColumnsEnd")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, GetVisibleColumnsEnd_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetVisibleColumnsEnd();
	return new Gurax::Value_Number(rtn);
}

// wx.HScrolledWindow#IsColumnVisible(column as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, IsColumnVisible_gurax, "IsColumnVisible")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, IsColumnVisible_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#RefreshColumn(column as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, RefreshColumn_gurax, "RefreshColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, RefreshColumn_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#RefreshColumns(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, RefreshColumns_gurax, "RefreshColumns")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, RefreshColumns_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#ScrollColumnPages(pages as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, ScrollColumnPages_gurax, "ScrollColumnPages")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pages", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, ScrollColumnPages_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#ScrollColumns(columns as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, ScrollColumns_gurax, "ScrollColumns")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("columns", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, ScrollColumns_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#ScrollToColumn(column as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, ScrollToColumn_gurax, "ScrollToColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, ScrollToColumn_gurax, processor_gurax, argument_gurax)
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

// wx.HScrolledWindow#SetColumnCount(columnCount as Number)
Gurax_DeclareMethodAlias(wxHScrolledWindow, SetColumnCount_gurax, "SetColumnCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("columnCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxHScrolledWindow, SetColumnCount_gurax, processor_gurax, argument_gurax)
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

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHScrolledWindow
//------------------------------------------------------------------------------
VType_wxHScrolledWindow VTYPE_wxHScrolledWindow("HScrolledWindow");

void VType_wxHScrolledWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHScrolledWindow, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, GetVisibleColumnsBegin_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, GetVisibleColumnsEnd_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, IsColumnVisible_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, RefreshColumn_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, RefreshColumns_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, ScrollColumnPages_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, ScrollColumns_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, ScrollToColumn_gurax));
	Assign(Gurax_CreateMethod(wxHScrolledWindow, SetColumnCount_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHScrolledWindow
//------------------------------------------------------------------------------
VType& Value_wxHScrolledWindow::vtype = VTYPE_wxHScrolledWindow;

String Value_wxHScrolledWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HScrolledWindow");
}

//------------------------------------------------------------------------------
// Value_wxHScrolledWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
