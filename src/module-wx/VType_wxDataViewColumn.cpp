﻿//==============================================================================
// VType_wxDataViewColumn.cpp
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

${help.ComposePropertyHelp(wx.DataViewColumn, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewColumn, `en)}

${help.ComposeMethodHelp(wx.DataViewColumn, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DataViewColumn(title as Any, renderer as wx.DataViewRenderer, model_column as Number, width? as Number, align? as Number, flags? as Number) {block?}
Gurax_DeclareConstructorAlias(DataViewColumn_gurax, "DataViewColumn")
{
	Declare(VTYPE_wxDataViewColumn, Flag::None);
	DeclareArg("title", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("renderer", VTYPE_wxDataViewRenderer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("model_column", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("align", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.DataViewColumn.");
}

Gurax_ImplementConstructorEx(DataViewColumn_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::Value& title = args_gurax.PickValue();
	Value_wxDataViewRenderer& value_renderer = args_gurax.Pick<Value_wxDataViewRenderer>();
	wxDataViewRenderer* renderer = value_renderer.GetEntityPtr();
	unsigned int model_column = args_gurax.PickNumber<unsigned int>();
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : wxDVC_DEFAULT_WIDTH;
	bool align_validFlag = args_gurax.IsValid();
	wxAlignment align = align_validFlag? args_gurax.PickNumber<wxAlignment>() : wxALIGN_CENTER;
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : wxDATAVIEW_COL_RESIZABLE;
	// Function body
	if (title.IsType(VTYPE_String)) {
		return new Value_wxDataViewColumn(new wxDataViewColumn(Value_String::GetString(title), renderer, model_column, width, align, flags));
	} else if (title.IsType(VTYPE_wxBitmap)) {
		return new Value_wxDataViewColumn(new wxDataViewColumn(Value_wxBitmap::GetEntity(title), renderer, model_column, width, align, flags));
	}
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DataViewColumn#GetModelColumn()
Gurax_DeclareMethodAlias(wxDataViewColumn, GetModelColumn_gurax, "GetModelColumn")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewColumn, GetModelColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetModelColumn();
	return new Gurax::Value_Number(rtn);
}

// wx.DataViewColumn#GetOwner() {block?}
Gurax_DeclareMethodAlias(wxDataViewColumn, GetOwner_gurax, "GetOwner")
{
	Declare(VTYPE_wxDataViewCtrl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewColumn, GetOwner_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewCtrl(
		pEntity_gurax->GetOwner()));
}

// wx.DataViewColumn#GetRenderer() {block?}
Gurax_DeclareMethodAlias(wxDataViewColumn, GetRenderer_gurax, "GetRenderer")
{
	Declare(VTYPE_wxDataViewRenderer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDataViewColumn, GetRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDataViewRenderer(
		pEntity_gurax->GetRenderer()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDataViewColumn
//------------------------------------------------------------------------------
VType_wxDataViewColumn VTYPE_wxDataViewColumn("DataViewColumn");

void VType_wxDataViewColumn::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSettableHeaderColumn, Flag::Mutable, Gurax_CreateConstructor(DataViewColumn_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDataViewColumn, GetModelColumn_gurax));
	Assign(Gurax_CreateMethod(wxDataViewColumn, GetOwner_gurax));
	Assign(Gurax_CreateMethod(wxDataViewColumn, GetRenderer_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDataViewColumn
//------------------------------------------------------------------------------
VType& Value_wxDataViewColumn::vtype = VTYPE_wxDataViewColumn;

String Value_wxDataViewColumn::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewColumn");
}

Gurax_EndModuleScope(wx)
