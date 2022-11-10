﻿//==============================================================================
// VType_wxDataViewCtrl.cpp
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

${help.ComposePropertyHelp(wx.DataViewCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewCtrl, `en)}

${help.ComposeMethodHelp(wx.DataViewCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DataViewCtrl(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(DataViewCtrl_gurax, "DataViewCtrl")
{
	Declare(VTYPE_wxDataViewCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.DataViewCtrl.");
}

Gurax_ImplementConstructorEx(DataViewCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxDataViewCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxDataViewCtrl::EntityT(parent, id, pos, size, style, validator, name);
	RefPtr<Value_wxDataViewCtrl> pValue_gurax(new Value_wxDataViewCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DataViewCtrl#Create(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxDataViewCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxDataViewCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#AppendColumn(col as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, AppendColumn_gurax, "AppendColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, AppendColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_col = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* col = value_col.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AppendColumn(col);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#PrependColumn(col as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, PrependColumn_gurax, "PrependColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, PrependColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_col = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* col = value_col.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->PrependColumn(col);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#InsertColumn(pos as Number, col as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, InsertColumn_gurax, "InsertColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, InsertColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	Value_wxDataViewColumn& value_col = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* col = value_col.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->InsertColumn(pos, col);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#AssociateModel(model as wx.DataViewModel)
Gurax_DeclareMethodAlias(wxDataViewCtrl, AssociateModel_gurax, "AssociateModel")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("model", VTYPE_wxDataViewModel, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, AssociateModel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewModel& value_model = args_gurax.Pick<Value_wxDataViewModel>();
	wxDataViewModel* model = value_model.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->AssociateModel(model);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#ClearColumns()
Gurax_DeclareMethodAlias(wxDataViewCtrl, ClearColumns_gurax, "ClearColumns")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, ClearColumns_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ClearColumns();
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#Collapse(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, Collapse_gurax, "Collapse")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, Collapse_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->Collapse(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#DeleteColumn(column as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, DeleteColumn_gurax, "DeleteColumn")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("column", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, DeleteColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_column = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* column = value_column.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->DeleteColumn(column);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#EditItem(item as wx.DataViewItem, column as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, EditItem_gurax, "EditItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, EditItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	Value_wxDataViewColumn& value_column = args_gurax.Pick<Value_wxDataViewColumn>();
	const wxDataViewColumn* column = value_column.GetEntityPtr();
	// Function body
	pEntity_gurax->EditItem(item, column);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#EnableDragSource(format as wx.DataFormat)
Gurax_DeclareMethodAlias(wxDataViewCtrl, EnableDragSource_gurax, "EnableDragSource")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("format", VTYPE_wxDataFormat, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, EnableDragSource_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataFormat& value_format = args_gurax.Pick<Value_wxDataFormat>();
	const wxDataFormat& format = value_format.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->EnableDragSource(format);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#EnableDropTarget(format as wx.DataFormat)
Gurax_DeclareMethodAlias(wxDataViewCtrl, EnableDropTarget_gurax, "EnableDropTarget")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("format", VTYPE_wxDataFormat, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, EnableDropTarget_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataFormat& value_format = args_gurax.Pick<Value_wxDataFormat>();
	const wxDataFormat& format = value_format.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->EnableDropTarget(format);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#EnsureVisible(item as wx.DataViewItem, column? as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, EnsureVisible_gurax, "EnsureVisible")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_wxDataViewColumn, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, EnsureVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	const wxDataViewColumn* column = args_gurax.IsValid()? args_gurax.Pick<Value_wxDataViewColumn>().GetEntityPtr() : nullptr;
	// Function body
	pEntity_gurax->EnsureVisible(item, column);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#Expand(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, Expand_gurax, "Expand")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, Expand_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->Expand(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#ExpandAncestors(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, ExpandAncestors_gurax, "ExpandAncestors")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, ExpandAncestors_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->ExpandAncestors(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#GetColumn(pos as Number) {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetColumn_gurax, "GetColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewColumn(
		pEntity_gurax->GetColumn(pos)));
}

// wx.DataViewCtrl#GetColumnCount()
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetColumnCount();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewCtrl#GetColumnPosition(column as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetColumnPosition_gurax, "GetColumnPosition")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("column", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetColumnPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_column = args_gurax.Pick<Value_wxDataViewColumn>();
	const wxDataViewColumn* column = value_column.GetEntityPtr();
	// Function body
	int rtn = pEntity_gurax->GetColumnPosition(column);
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewCtrl#GetExpanderColumn() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetExpanderColumn_gurax, "GetExpanderColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetExpanderColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewColumn(
		pEntity_gurax->GetExpanderColumn()));
}

// wx.DataViewCtrl#GetCurrentItem() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetCurrentItem_gurax, "GetCurrentItem")
{
	Declare(VTYPE_wxDataViewItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetCurrentItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewItem(
		pEntity_gurax->GetCurrentItem()));
}

// wx.DataViewCtrl#GetCurrentColumn() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetCurrentColumn_gurax, "GetCurrentColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetCurrentColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewColumn(
		pEntity_gurax->GetCurrentColumn()));
}

// wx.DataViewCtrl#GetIndent()
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetIndent_gurax, "GetIndent")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetIndent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetIndent();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewCtrl#GetItemRect(item as wx.DataViewItem, col? as wx.DataViewColumn) {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetItemRect_gurax, "GetItemRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetItemRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	const wxDataViewColumn* col = args_gurax.IsValid()? args_gurax.Pick<Value_wxDataViewColumn>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetItemRect(item, col)));
}

// wx.DataViewCtrl#GetModel() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetModel_gurax, "GetModel")
{
	Declare(VTYPE_wxDataViewModel, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetModel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewModel(
		pEntity_gurax->GetModel()));
}

// wx.DataViewCtrl#GetSelectedItemsCount()
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetSelectedItemsCount_gurax, "GetSelectedItemsCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetSelectedItemsCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelectedItemsCount();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewCtrl#GetSelection() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_wxDataViewItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewItem(
		pEntity_gurax->GetSelection()));
}

// wx.DataViewCtrl#GetSortingColumn() {block?}
Gurax_DeclareMethodAlias(wxDataViewCtrl, GetSortingColumn_gurax, "GetSortingColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, GetSortingColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewColumn(
		pEntity_gurax->GetSortingColumn()));
}

// wx.DataViewCtrl#HasSelection()
Gurax_DeclareMethodAlias(wxDataViewCtrl, HasSelection_gurax, "HasSelection")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, HasSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#IsExpanded(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, IsExpanded_gurax, "IsExpanded")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, IsExpanded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->IsExpanded(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#IsSelected(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, IsSelected_gurax, "IsSelected")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, IsSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->IsSelected(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.DataViewCtrl#Select(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, Select_gurax, "Select")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, Select_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->Select(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#SelectAll()
Gurax_DeclareMethodAlias(wxDataViewCtrl, SelectAll_gurax, "SelectAll")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, SelectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SelectAll();
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#SetExpanderColumn(col as wx.DataViewColumn)
Gurax_DeclareMethodAlias(wxDataViewCtrl, SetExpanderColumn_gurax, "SetExpanderColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxDataViewColumn, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, SetExpanderColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewColumn& value_col = args_gurax.Pick<Value_wxDataViewColumn>();
	wxDataViewColumn* col = value_col.GetEntityPtr();
	// Function body
	pEntity_gurax->SetExpanderColumn(col);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#SetCurrentItem(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, SetCurrentItem_gurax, "SetCurrentItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, SetCurrentItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->SetCurrentItem(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#SetIndent(indent as Number)
Gurax_DeclareMethodAlias(wxDataViewCtrl, SetIndent_gurax, "SetIndent")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("indent", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, SetIndent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int indent = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetIndent(indent);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#Unselect(item as wx.DataViewItem)
Gurax_DeclareMethodAlias(wxDataViewCtrl, Unselect_gurax, "Unselect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxDataViewItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, Unselect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDataViewItem& value_item = args_gurax.Pick<Value_wxDataViewItem>();
	const wxDataViewItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->Unselect(item);
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#UnselectAll()
Gurax_DeclareMethodAlias(wxDataViewCtrl, UnselectAll_gurax, "UnselectAll")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, UnselectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->UnselectAll();
	return Gurax::Value::nil();
}

// wx.DataViewCtrl#SetRowHeight(rowHeight as Number)
Gurax_DeclareMethodAlias(wxDataViewCtrl, SetRowHeight_gurax, "SetRowHeight")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("rowHeight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewCtrl, SetRowHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int rowHeight = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->SetRowHeight(rowHeight);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDataViewCtrl
//------------------------------------------------------------------------------
VType_wxDataViewCtrl VTYPE_wxDataViewCtrl("DataViewCtrl");

void VType_wxDataViewCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(DataViewCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDataViewCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, AppendColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, PrependColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, InsertColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, AssociateModel_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, ClearColumns_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, Collapse_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, DeleteColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, EditItem_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, EnableDragSource_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, EnableDropTarget_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, EnsureVisible_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, Expand_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, ExpandAncestors_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetColumnPosition_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetExpanderColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetCurrentItem_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetCurrentColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetIndent_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetItemRect_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetModel_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetSelectedItemsCount_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, GetSortingColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, HasSelection_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, IsExpanded_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, IsSelected_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, Select_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, SelectAll_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, SetExpanderColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, SetCurrentItem_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, SetIndent_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, Unselect_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, UnselectAll_gurax));
	Assign(Gurax_CreateMethod(wxDataViewCtrl, SetRowHeight_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDataViewCtrl
//------------------------------------------------------------------------------
VType& Value_wxDataViewCtrl::vtype = VTYPE_wxDataViewCtrl;

String Value_wxDataViewCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDataViewCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
