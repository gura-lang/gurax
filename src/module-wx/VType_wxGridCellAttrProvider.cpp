﻿//==============================================================================
// VType_wxGridCellAttrProvider.cpp
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

${help.ComposePropertyHelp(wx.GridCellAttrProvider, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridCellAttrProvider, `en)}

${help.ComposeMethodHelp(wx.GridCellAttrProvider, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GridCellAttrProvider() {block?}
Gurax_DeclareConstructorAlias(GridCellAttrProvider_gurax, "GridCellAttrProvider")
{
	Declare(VTYPE_wxGridCellAttrProvider, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.GridCellAttrProvider.
)**");
}

Gurax_ImplementConstructorEx(GridCellAttrProvider_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCellAttrProvider(
		wxGridCellAttrProvider()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridCellAttrProvider#SetAttr(attr as wx.GridCellAttr, row as Number, col as Number)
Gurax_DeclareMethodAlias(wxGridCellAttrProvider, SetAttr_gurax, "SetAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("attr", VTYPE_wxGridCellAttr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellAttrProvider, SetAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellAttr& value_attr = args_gurax.Pick<Value_wxGridCellAttr>();
	wxGridCellAttr* attr = value_attr.GetEntityPtr();
	int row = args_gurax.PickNumber<int>();
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetAttr(attr, row, col);
	return Gurax::Value::nil();
}

// wx.GridCellAttrProvider#SetRowAttr(attr as wx.GridCellAttr, row as Number)
Gurax_DeclareMethodAlias(wxGridCellAttrProvider, SetRowAttr_gurax, "SetRowAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("attr", VTYPE_wxGridCellAttr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellAttrProvider, SetRowAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellAttr& value_attr = args_gurax.Pick<Value_wxGridCellAttr>();
	wxGridCellAttr* attr = value_attr.GetEntityPtr();
	int row = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRowAttr(attr, row);
	return Gurax::Value::nil();
}

// wx.GridCellAttrProvider#SetColAttr(attr as wx.GridCellAttr, col as Number)
Gurax_DeclareMethodAlias(wxGridCellAttrProvider, SetColAttr_gurax, "SetColAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("attr", VTYPE_wxGridCellAttr, ArgOccur::Once, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellAttrProvider, SetColAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGridCellAttr& value_attr = args_gurax.Pick<Value_wxGridCellAttr>();
	wxGridCellAttr* attr = value_attr.GetEntityPtr();
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetColAttr(attr, col);
	return Gurax::Value::nil();
}

// wx.GridCellAttrProvider#GetCornerRenderer() {block?}
Gurax_DeclareMethodAlias(wxGridCellAttrProvider, GetCornerRenderer_gurax, "GetCornerRenderer")
{
	Declare(VTYPE_wxGridCornerHeaderRenderer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxGridCellAttrProvider, GetCornerRenderer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridCornerHeaderRenderer(
		pEntity_gurax->GetCornerRenderer()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridCellAttrProvider
//------------------------------------------------------------------------------
VType_wxGridCellAttrProvider VTYPE_wxGridCellAttrProvider("GridCellAttrProvider");

void VType_wxGridCellAttrProvider::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxClientDataContainer, Flag::Mutable, Gurax_CreateConstructor(GridCellAttrProvider_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridCellAttrProvider, SetAttr_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttrProvider, SetRowAttr_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttrProvider, SetColAttr_gurax));
	Assign(Gurax_CreateMethod(wxGridCellAttrProvider, GetCornerRenderer_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridCellAttrProvider
//------------------------------------------------------------------------------
VType& Value_wxGridCellAttrProvider::vtype = VTYPE_wxGridCellAttrProvider;

String Value_wxGridCellAttrProvider::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellAttrProvider");
}

Gurax_EndModuleScope(wx)
