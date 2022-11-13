﻿//==============================================================================
// VType_wxBoxSizer.cpp
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

${help.ComposePropertyHelp(wx.BoxSizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BoxSizer, `en)}

${help.ComposeMethodHelp(wx.BoxSizer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BoxSizer(orient as Number) {block?}
Gurax_DeclareConstructorAlias(BoxSizer_gurax, "BoxSizer")
{
	Declare(VTYPE_wxBoxSizer, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.BoxSizer.
)**");
}

Gurax_ImplementConstructorEx(BoxSizer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	auto pEntity_gurax = new wxBoxSizer(orient);
	RefPtr<Value_wxBoxSizer> pValue_gurax(new Value_wxBoxSizer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BoxSizer#AddSpacer(size as Number) {block?}
Gurax_DeclareMethodAlias(wxBoxSizer, AddSpacer_gurax, "AddSpacer")
{
	Declare(VTYPE_wxSizerItem, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxBoxSizer, AddSpacer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int size = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerItem(
		*pEntity_gurax->AddSpacer(size)));
}

// wx.BoxSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxBoxSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxBoxSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.BoxSizer#GetOrientation()
Gurax_DeclareMethodAlias(wxBoxSizer, GetOrientation_gurax, "GetOrientation")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxBoxSizer, GetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetOrientation();
	return new Gurax::Value_Number(rtn);
}

// wx.BoxSizer#SetOrientation(orient as Number)
Gurax_DeclareMethodAlias(wxBoxSizer, SetOrientation_gurax, "SetOrientation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxBoxSizer, SetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetOrientation(orient);
	return Gurax::Value::nil();
}

// wx.BoxSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxBoxSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxBoxSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBoxSizer
//------------------------------------------------------------------------------
VType_wxBoxSizer VTYPE_wxBoxSizer("BoxSizer");

void VType_wxBoxSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSizer, Flag::Mutable, Gurax_CreateConstructor(BoxSizer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBoxSizer, AddSpacer_gurax));
	Assign(Gurax_CreateMethod(wxBoxSizer, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxBoxSizer, GetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxBoxSizer, SetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxBoxSizer, RecalcSizes_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBoxSizer
//------------------------------------------------------------------------------
VType& Value_wxBoxSizer::vtype = VTYPE_wxBoxSizer;

String Value_wxBoxSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BoxSizer");
}

Gurax_EndModuleScope(wx)
