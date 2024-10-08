﻿//==============================================================================
// VType_wxGridCellAttr.cpp
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

${help.ComposePropertyHelp(wx.GridCellAttr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellAttr, `en)}

${help.ComposeMethodHelp(wx.GridCellAttr, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GridCellAttr, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GridCellAttr, `ja)}

${help.ComposeMethodHelp(wx.GridCellAttr, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellAttr#Clone() {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, Clone_gurax, "Clone")
{
	Declare(VTYPE_wxGridCellAttr, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, Clone_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellAttr(*pEntity_gurax->Clone()));
}

// wx.GridCellAttr#DecRef()
Gurax_DeclareMethodAlias(wxGridCellAttr, DecRef_gurax, "DecRef")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, DecRef_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DecRef();
	return Gurax::Value::nil();
}

// wx.GridCellAttr#GetAlignment(&hAlign:nilRef as Number, &vAlign:nilRef as Number)
Gurax_DeclareMethodAlias(wxGridCellAttr, GetAlignment_gurax, "GetAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("vAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> hAlign(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> vAlign(args_gurax.PickReferencer().Reference());
	// Function body
	int hAlign_, vAlign_;
	pEntity_gurax->GetAlignment(&hAlign_, &vAlign_);
	hAlign->SetValue(processor_gurax, new Value_Number(&hAlign_));
	vAlign->SetValue(processor_gurax, new Value_Number(&vAlign_));
	return Value::nil();
}

// wx.GridCellAttr#GetBackgroundColour() {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, GetBackgroundColour_gurax, "GetBackgroundColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetBackgroundColour()));
}

// wx.GridCellAttr#GetEditor(grid as wx.Grid, row as Number, col as Number) {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, GetEditor_gurax, "GetEditor")
{
	Declare(VTYPE_wxGridCellEditor, Flag::None);
	DeclareArg("grid", VTYPE_wxGrid, ArgOccur::Once, ArgFlag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetEditor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGrid& value_grid = args_gurax.Pick<Value_wxGrid>();
	const wxGrid* grid = value_grid.GetEntityPtr();
	int row = args_gurax.PickNumber<int>();
	int col = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellEditor(*pEntity_gurax->GetEditor(grid, row, col)));
}

// wx.GridCellAttr#GetFont() {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, GetFont_gurax, "GetFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(pEntity_gurax->GetFont()));
}

// wx.GridCellAttr#GetNonDefaultAlignment(&hAlign:nilRef as Number, &vAlign:nilRef as Number)
Gurax_DeclareMethodAlias(wxGridCellAttr, GetNonDefaultAlignment_gurax, "GetNonDefaultAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("vAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetNonDefaultAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> hAlign(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> vAlign(args_gurax.PickReferencer().Reference());
	// Function body
	int hAlign_, vAlign_;
	pEntity_gurax->GetNonDefaultAlignment(&hAlign_, &vAlign_);
	hAlign->SetValue(processor_gurax, new Value_Number(&hAlign_));
	vAlign->SetValue(processor_gurax, new Value_Number(&vAlign_));
	return Value::nil();
}

// wx.GridCellAttr#GetRenderer(grid as wx.Grid, row as Number, col as Number) {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, GetRenderer_gurax, "GetRenderer")
{
	Declare(VTYPE_wxGridCellRenderer, Flag::None);
	DeclareArg("grid", VTYPE_wxGrid, ArgOccur::Once, ArgFlag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGrid& value_grid = args_gurax.Pick<Value_wxGrid>();
	const wxGrid* grid = value_grid.GetEntityPtr();
	int row = args_gurax.PickNumber<int>();
	int col = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellRenderer(pEntity_gurax->GetRenderer(grid, row, col)));
}

// wx.GridCellAttr#GetTextColour() {block?}
Gurax_DeclareMethodAlias(wxGridCellAttr, GetTextColour_gurax, "GetTextColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetTextColour()));
}

// wx.GridCellAttr#HasAlignment()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasAlignment_gurax, "HasAlignment")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasAlignment();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasBackgroundColour()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasBackgroundColour_gurax, "HasBackgroundColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasBackgroundColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasEditor()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasEditor_gurax, "HasEditor")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasEditor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasEditor();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasFont()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasFont_gurax, "HasFont")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasFont();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasRenderer()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasRenderer_gurax, "HasRenderer")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasRenderer();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasTextColour()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasTextColour_gurax, "HasTextColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasTextColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#IncRef()
Gurax_DeclareMethodAlias(wxGridCellAttr, IncRef_gurax, "IncRef")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, IncRef_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->IncRef();
	return Gurax::Value::nil();
}

// wx.GridCellAttr#IsReadOnly()
Gurax_DeclareMethodAlias(wxGridCellAttr, IsReadOnly_gurax, "IsReadOnly")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, IsReadOnly_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsReadOnly();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#SetAlignment(hAlign as Number, vAlign as Number)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetAlignment_gurax, "SetAlignment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("hAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vAlign", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetAlignment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int hAlign = args_gurax.PickNumber<int>();
	int vAlign = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetAlignment(hAlign, vAlign);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetBackgroundColour(colBack as wx.Colour)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetBackgroundColour_gurax, "SetBackgroundColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colBack", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colBack = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBack = value_colBack.GetEntity();
	// Function body
	pEntity_gurax->SetBackgroundColour(colBack);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetDefAttr(defAttr as wx.GridCellAttr)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetDefAttr_gurax, "SetDefAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("defAttr", VTYPE_wxGridCellAttr, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetDefAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellAttr& value_defAttr = args_gurax.Pick<Value_wxGridCellAttr>();
	wxGridCellAttr* defAttr = value_defAttr.GetEntityPtr();
	// Function body
	pEntity_gurax->SetDefAttr(defAttr);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetEditor(editor as wx.GridCellEditor)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetEditor_gurax, "SetEditor")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("editor", VTYPE_wxGridCellEditor, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetEditor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellEditor& value_editor = args_gurax.Pick<Value_wxGridCellEditor>();
	wxGridCellEditor* editor = value_editor.GetEntityPtr();
	// Function body
	pEntity_gurax->SetEditor(editor);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetFont_gurax, "SetFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFont& value_font = args_gurax.Pick<Value_wxFont>();
	const wxFont& font = value_font.GetEntity();
	// Function body
	pEntity_gurax->SetFont(font);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetReadOnly(isReadOnly? as Bool)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetReadOnly_gurax, "SetReadOnly")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("isReadOnly", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetReadOnly_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool isReadOnly = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetReadOnly(isReadOnly);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetRenderer(renderer as wx.GridCellRenderer)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetRenderer_gurax, "SetRenderer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("renderer", VTYPE_wxGridCellRenderer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellRenderer& value_renderer = args_gurax.Pick<Value_wxGridCellRenderer>();
	wxGridCellRenderer* renderer = value_renderer.GetEntityPtr();
	// Function body
	pEntity_gurax->SetRenderer(renderer);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetTextColour(colText as wx.Colour)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetTextColour_gurax, "SetTextColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colText", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colText = args_gurax.Pick<Value_wxColour>();
	const wxColour& colText = value_colText.GetEntity();
	// Function body
	pEntity_gurax->SetTextColour(colText);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#MergeWith(mergefrom as wx.GridCellAttr)
Gurax_DeclareMethodAlias(wxGridCellAttr, MergeWith_gurax, "MergeWith")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mergefrom", VTYPE_wxGridCellAttr, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, MergeWith_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellAttr& value_mergefrom = args_gurax.Pick<Value_wxGridCellAttr>();
	wxGridCellAttr* mergefrom = value_mergefrom.GetEntityPtr();
	// Function body
	pEntity_gurax->MergeWith(mergefrom);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetSize(num_rows as Number, num_cols as Number)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetSize_gurax, "SetSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("num_rows", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num_cols", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int num_rows = args_gurax.PickNumber<int>();
	int num_cols = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSize(num_rows, num_cols);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#SetOverflow(allow? as Bool)
Gurax_DeclareMethodAlias(wxGridCellAttr, SetOverflow_gurax, "SetOverflow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("allow", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, SetOverflow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool allow = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetOverflow(allow);
	return Gurax::Value::nil();
}

// wx.GridCellAttr#HasReadWriteMode()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasReadWriteMode_gurax, "HasReadWriteMode")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasReadWriteMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasReadWriteMode();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasOverflowMode()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasOverflowMode_gurax, "HasOverflowMode")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasOverflowMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasOverflowMode();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#HasSize()
Gurax_DeclareMethodAlias(wxGridCellAttr, HasSize_gurax, "HasSize")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, HasSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasSize();
	return new Gurax::Value_Bool(rtn);
}

// wx.GridCellAttr#GetSize(&num_rows:nilRef as Number, &num_cols:nilRef as Number)
Gurax_DeclareMethodAlias(wxGridCellAttr, GetSize_gurax, "GetSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("num_rows", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
	DeclareArg("num_cols", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> num_rows(args_gurax.PickReferencer().Reference());
	RefPtr<Referencer> num_cols(args_gurax.PickReferencer().Reference());
	// Function body
	int num_rows_, num_cols_;
	pEntity_gurax->GetSize(&num_rows_, &num_cols_);
	num_rows->SetValue(processor_gurax, new Value_Number(&num_rows_));
	num_cols->SetValue(processor_gurax, new Value_Number(&num_cols_));
	return Value::nil();
}

// wx.GridCellAttr#GetOverflow()
Gurax_DeclareMethodAlias(wxGridCellAttr, GetOverflow_gurax, "GetOverflow")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGridCellAttr, GetOverflow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetOverflow();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellAttr
//------------------------------------------------------------------------------
VType_wxGridCellAttr VTYPE_wxGridCellAttr("GridCellAttr");

void VType_wxGridCellAttr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxClientDataContainer, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellAttr, Clone_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, DecRef_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetEditor_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetFont_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetNonDefaultAlignment_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetRenderer_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasAlignment_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasEditor_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasFont_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasRenderer_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasTextColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, IncRef_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, IsReadOnly_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetAlignment_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetDefAttr_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetEditor_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetFont_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetReadOnly_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetRenderer_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, MergeWith_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetSize_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, SetOverflow_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasReadWriteMode_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasOverflowMode_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, HasSize_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetSize_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttr, GetOverflow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellAttr
//------------------------------------------------------------------------------
VType& Value_wxGridCellAttr::vtype = VTYPE_wxGridCellAttr;

String Value_wxGridCellAttr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellAttr");
}

Gurax_EndModuleScope(wx)
