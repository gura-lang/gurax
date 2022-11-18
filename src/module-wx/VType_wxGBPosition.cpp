﻿//==============================================================================
// VType_wxGBPosition.cpp
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

${help.ComposePropertyHelp(wx.GBPosition, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GBPosition, `en)}

${help.ComposeMethodHelp(wx.GBPosition, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GBPosition(row? as Number, col? as Number) {block?}
Gurax_DeclareConstructorAlias(GBPosition_gurax, "GBPosition")
{
	Declare(VTYPE_wxGBPosition, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(GBPosition_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool row_validFlag = args_gurax.IsValid();
	int row = row_validFlag? args_gurax.PickNumber<int>() : 0;
	bool col_validFlag = args_gurax.IsValid();
	int col = col_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxGBPosition(
		wxGBPosition(row, col)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GBPosition#GetCol()
Gurax_DeclareMethodAlias(wxGBPosition, GetCol_gurax, "GetCol")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGBPosition, GetCol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCol();
	return new Gurax::Value_Number(rtn);
}

// wx.GBPosition#GetRow()
Gurax_DeclareMethodAlias(wxGBPosition, GetRow_gurax, "GetRow")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxGBPosition, GetRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRow();
	return new Gurax::Value_Number(rtn);
}

// wx.GBPosition#SetCol(col as Number)
Gurax_DeclareMethodAlias(wxGBPosition, SetCol_gurax, "SetCol")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGBPosition, SetCol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetCol(col);
	return Gurax::Value::nil();
}

// wx.GBPosition#SetRow(row as Number)
Gurax_DeclareMethodAlias(wxGBPosition, SetRow_gurax, "SetRow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("row", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGBPosition, SetRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int row = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRow(row);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGBPosition
//------------------------------------------------------------------------------
VType_wxGBPosition VTYPE_wxGBPosition("GBPosition");

void VType_wxGBPosition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(GBPosition_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGBPosition, GetCol_gurax));
	Assign(Gurax_CreateMethod(wxGBPosition, GetRow_gurax));
	Assign(Gurax_CreateMethod(wxGBPosition, SetCol_gurax));
	Assign(Gurax_CreateMethod(wxGBPosition, SetRow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGBPosition
//------------------------------------------------------------------------------
VType& Value_wxGBPosition::vtype = VTYPE_wxGBPosition;

String Value_wxGBPosition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GBPosition");
}

Gurax_EndModuleScope(wx)
