//==============================================================================
// VType_wxColourData.cpp
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
// wx.ColourData() {block?}
Gurax_DeclareConstructorAlias(ColourData_gurax, "ColourData")
{
	Declare(VTYPE_wxColourData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ColourData.");
}

Gurax_ImplementConstructorEx(ColourData_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColourData(
		wxColourData()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ColourData#GetChooseFull()
Gurax_DeclareMethodAlias(wxColourData, GetChooseFull_gurax, "GetChooseFull")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, GetChooseFull_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetChooseFull();
	return new Gurax::Value_Bool(rtn);
}

// wx.ColourData#GetColour()
Gurax_DeclareMethodAlias(wxColourData, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetColour()));
}

// wx.ColourData#GetCustomColour(i as Number)
Gurax_DeclareMethodAlias(wxColourData, GetCustomColour_gurax, "GetCustomColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, GetCustomColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int i = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetCustomColour(i)));
}

// wx.ColourData#SetChooseFull(flag as Bool)
Gurax_DeclareMethodAlias(wxColourData, SetChooseFull_gurax, "SetChooseFull")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, SetChooseFull_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flag = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetChooseFull(flag);
	return Gurax::Value::nil();
}

// wx.ColourData#SetColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxColourData, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, SetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colour = args_gurax.Pick<Value_wxColour>();
	const wxColour& colour = value_colour.GetEntity();
	// Function body
	pEntity_gurax->SetColour(colour);
	return Gurax::Value::nil();
}

// wx.ColourData#SetCustomColour(i as Number, colour as wx.Colour)
Gurax_DeclareMethodAlias(wxColourData, SetCustomColour_gurax, "SetCustomColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("i", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, SetCustomColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int i = args_gurax.PickNumber<int>();
	Value_wxColour& value_colour = args_gurax.Pick<Value_wxColour>();
	const wxColour& colour = value_colour.GetEntity();
	// Function body
	pEntity_gurax->SetCustomColour(i, colour);
	return Gurax::Value::nil();
}

// wx.ColourData#ToString()
Gurax_DeclareMethodAlias(wxColourData, ToString_gurax, "ToString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, ToString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	const char* rtn = pEntity_gurax->ToString();
	return new Gurax::Value_String(rtn);
}

// wx.ColourData#FromString(str as String)
Gurax_DeclareMethodAlias(wxColourData, FromString_gurax, "FromString")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourData, FromString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* str = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->FromString(str);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxColourData
//------------------------------------------------------------------------------
VType_wxColourData VTYPE_wxColourData("ColourData");

void VType_wxColourData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable, Gurax_CreateConstructor(ColourData_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxColourData, GetChooseFull_gurax));
	Assign(Gurax_CreateMethod(wxColourData, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxColourData, GetCustomColour_gurax));
	Assign(Gurax_CreateMethod(wxColourData, SetChooseFull_gurax));
	Assign(Gurax_CreateMethod(wxColourData, SetColour_gurax));
	Assign(Gurax_CreateMethod(wxColourData, SetCustomColour_gurax));
	Assign(Gurax_CreateMethod(wxColourData, ToString_gurax));
	Assign(Gurax_CreateMethod(wxColourData, FromString_gurax));
}

//------------------------------------------------------------------------------
// Value_wxColourData
//------------------------------------------------------------------------------
VType& Value_wxColourData::vtype = VTYPE_wxColourData;

String Value_wxColourData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourData");
}

Gurax_EndModuleScope(wx)