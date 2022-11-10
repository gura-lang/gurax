﻿//==============================================================================
// VType_wxWrapSizer.cpp
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

${help.ComposePropertyHelp(wx.WrapSizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.WrapSizer, `en)}

${help.ComposeMethodHelp(wx.WrapSizer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.WrapSizer(orient as Number, flag? as Number) {block?}
Gurax_DeclareConstructorAlias(WrapSizer_gurax, "WrapSizer")
{
	Declare(VTYPE_wxWrapSizer, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flag", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.WrapSizer.");
}

Gurax_ImplementConstructorEx(WrapSizer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	bool flag_validFlag = args_gurax.IsValid();
	int flag = flag_validFlag? args_gurax.PickNumber<int>() : wxWRAPSIZER_DEFAULT_FLAGS;
	// Function body
	auto pEntity_gurax = new wxWrapSizer(orient, flag);
	RefPtr<Value_wxWrapSizer> pValue_gurax(new Value_wxWrapSizer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.WrapSizer#InformFirstDirection(direction as Number, size as Number, availableOtherDir as Number)
Gurax_DeclareMethodAlias(wxWrapSizer, InformFirstDirection_gurax, "InformFirstDirection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("availableOtherDir", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWrapSizer, InformFirstDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int direction = args_gurax.PickNumber<int>();
	int size = args_gurax.PickNumber<int>();
	int availableOtherDir = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->InformFirstDirection(direction, size, availableOtherDir);
	return new Gurax::Value_Bool(rtn);
}

// wx.WrapSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxWrapSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWrapSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

// wx.WrapSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxWrapSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWrapSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxWrapSizer
//------------------------------------------------------------------------------
VType_wxWrapSizer VTYPE_wxWrapSizer("WrapSizer");

void VType_wxWrapSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBoxSizer, Flag::Mutable, Gurax_CreateConstructor(WrapSizer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxWrapSizer, InformFirstDirection_gurax));
	Assign(Gurax_CreateMethod(wxWrapSizer, RecalcSizes_gurax));
	Assign(Gurax_CreateMethod(wxWrapSizer, CalcMin_gurax));
}

//------------------------------------------------------------------------------
// Value_wxWrapSizer
//------------------------------------------------------------------------------
VType& Value_wxWrapSizer::vtype = VTYPE_wxWrapSizer;

String Value_wxWrapSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.WrapSizer");
}

Gurax_EndModuleScope(wx)
