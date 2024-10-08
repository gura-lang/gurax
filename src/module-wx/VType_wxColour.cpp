﻿//==============================================================================
// VType_wxColour.cpp
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

${help.ComposePropertyHelp(wx.Colour, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Colour, `en)}

${help.ComposeMethodHelp(wx.Colour, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Colour, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Colour, `ja)}

${help.ComposeMethodHelp(wx.Colour, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Colour(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Colour_gurax, "Colour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Colour_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.Colour(colourName as String)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colourName", VTYPE_String);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const char* colourName = args.PickString();
		return new Value_wxColour(wxColour(colourName));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Colour(red as unsigned_char = 0, green as unsigned_char = 0, blue as unsigned_char = 0, alpha as unsigned_char = wxALPHA_OPAQUE)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("red", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("green", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("blue", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("alpha", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		unsigned char red = args.IsValid()? args.PickNumber<unsigned char>() : 0;
		unsigned char green = args.IsValid()? args.PickNumber<unsigned char>() : 0;
		unsigned char blue = args.IsValid()? args.PickNumber<unsigned char>() : 0;
		unsigned char alpha = args.IsValid()? args.PickNumber<unsigned char>() : wxALPHA_OPAQUE;
		return new Value_wxColour(wxColour(red, green, blue, alpha));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Colour#Alpha()
Gurax_DeclareMethodAlias(wxColour, Alpha_gurax, "Alpha")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, Alpha_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned char rtn = pEntity_gurax->Alpha();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#Blue()
Gurax_DeclareMethodAlias(wxColour, Blue_gurax, "Blue")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, Blue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned char rtn = pEntity_gurax->Blue();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#GetAsString(flags? as Number)
Gurax_DeclareMethodAlias(wxColour, GetAsString_gurax, "GetAsString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, GetAsString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	long flags = flags_validFlag? args_gurax.PickNumber<long>() : wxC2S_CSS_SYNTAX;
	// Function body
	wxString rtn = pEntity_gurax->GetAsString(flags);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Colour#Green()
Gurax_DeclareMethodAlias(wxColour, Green_gurax, "Green")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, Green_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned char rtn = pEntity_gurax->Green();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#IsOk()
Gurax_DeclareMethodAlias(wxColour, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Colour#Red()
Gurax_DeclareMethodAlias(wxColour, Red_gurax, "Red")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, Red_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned char rtn = pEntity_gurax->Red();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#MakeDisabled(brightness? as Number)
Gurax_DeclareMethodAlias(wxColour, MakeDisabled_gurax, "MakeDisabled")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("brightness", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, MakeDisabled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool brightness_validFlag = args_gurax.IsValid();
	unsigned char brightness = brightness_validFlag? args_gurax.PickNumber<unsigned char>() : 255;
	// Function body
	pEntity_gurax->MakeDisabled(brightness);
	return valueThis_gurax.Reference();
}

// wx.Colour#ChangeLightness(ialpha as Number)
Gurax_DeclareMethodAlias(wxColour, ChangeLightness_gurax, "ChangeLightness")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("ialpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, ChangeLightness_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int ialpha = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ChangeLightness(ialpha);
	return valueThis_gurax.Reference();
}

// wx.Colour#SetRGB(colRGB as Number)
Gurax_DeclareMethodAlias(wxColour, SetRGB_gurax, "SetRGB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colRGB", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, SetRGB_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxUint32 colRGB = args_gurax.PickNumber<wxUint32>();
	// Function body
	pEntity_gurax->SetRGB(colRGB);
	return Gurax::Value::nil();
}

// wx.Colour#SetRGBA(colRGBA as Number)
Gurax_DeclareMethodAlias(wxColour, SetRGBA_gurax, "SetRGBA")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colRGBA", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, SetRGBA_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxUint32 colRGBA = args_gurax.PickNumber<wxUint32>();
	// Function body
	pEntity_gurax->SetRGBA(colRGBA);
	return Gurax::Value::nil();
}

// wx.Colour#GetRGB()
Gurax_DeclareMethodAlias(wxColour, GetRGB_gurax, "GetRGB")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, GetRGB_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxUint32 rtn = pEntity_gurax->GetRGB();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#GetRGBA()
Gurax_DeclareMethodAlias(wxColour, GetRGBA_gurax, "GetRGBA")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxColour, GetRGBA_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxUint32 rtn = pEntity_gurax->GetRGBA();
	return new Gurax::Value_Number(rtn);
}

// wx.Colour#Set(red as Number, green as Number, blue as Number, alpha? as Number)
Gurax_DeclareMethodAlias(wxColour, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxColour, Set_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char red = args_gurax.PickNumber<unsigned char>();
	unsigned char green = args_gurax.PickNumber<unsigned char>();
	unsigned char blue = args_gurax.PickNumber<unsigned char>();
	bool alpha_validFlag = args_gurax.IsValid();
	unsigned char alpha = alpha_validFlag? args_gurax.PickNumber<unsigned char>() : wxALPHA_OPAQUE;
	// Function body
	pEntity_gurax->Set(red, green, blue, alpha);
	return Gurax::Value::nil();
}

// wx.Colour.MakeMonoRGB(r as Number, g as Number, b as Number, on as Bool)
Gurax_DeclareClassMethodAlias(wxColour, MakeMonoRGB_gurax, "MakeMonoRGB")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("on", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxColour, MakeMonoRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char r = args_gurax.PickNumber<unsigned char>();
	unsigned char g = args_gurax.PickNumber<unsigned char>();
	unsigned char b = args_gurax.PickNumber<unsigned char>();
	bool on = args_gurax.PickBool();
	// Function body
	wxColour::MakeMono(&r, &g, &b, on);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// wx.Colour.MakeDisabledRGB(r as Number, g as Number, b as Number, brightness? as Number)
Gurax_DeclareClassMethodAlias(wxColour, MakeDisabledRGB_gurax, "MakeDisabledRGB")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("brightness", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxColour, MakeDisabledRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char r = args_gurax.PickNumber<unsigned char>();
	unsigned char g = args_gurax.PickNumber<unsigned char>();
	unsigned char b = args_gurax.PickNumber<unsigned char>();
	bool brightness_validFlag = args_gurax.IsValid();
	unsigned char brightness = brightness_validFlag? args_gurax.PickNumber<unsigned char>() : 255;
	// Function body
	wxColour::MakeDisabled(&r, &g, &b, brightness);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// wx.Colour.MakeGreyRGB(r as Number, g as Number, b as Number, weight_r? as Number, weight_g? as Number, weight_b? as Number)
Gurax_DeclareClassMethodAlias(wxColour, MakeGreyRGB_gurax, "MakeGreyRGB")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("weight_r", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("weight_g", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("weight_b", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxColour, MakeGreyRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char r = args_gurax.PickNumber<unsigned char>();
	unsigned char g = args_gurax.PickNumber<unsigned char>();
	unsigned char b = args_gurax.PickNumber<unsigned char>();
	bool weight_r_validFlag = args_gurax.IsValid();
	double weight_r = weight_r_validFlag? args_gurax.PickNumber<double>() : 1.;
	bool weight_g_validFlag = args_gurax.IsValid();
	double weight_g = weight_g_validFlag? args_gurax.PickNumber<double>() : 1.;
	bool weight_b_validFlag = args_gurax.IsValid();
	double weight_b = weight_b_validFlag? args_gurax.PickNumber<double>() : 1.;
	// Function body
	wxColour::MakeGrey(&r, &g, &b, weight_r, weight_g, weight_b);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

// wx.Colour.AlphaBlend(fg as Number, bg as Number, alpha as Number)
Gurax_DeclareClassMethodAlias(wxColour, AlphaBlend_gurax, "AlphaBlend")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("fg", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bg", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("alpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxColour, AlphaBlend_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char fg = args_gurax.PickNumber<unsigned char>();
	unsigned char bg = args_gurax.PickNumber<unsigned char>();
	double alpha = args_gurax.PickNumber<double>();
	// Function body
	unsigned char rtn = wxColour::AlphaBlend(fg, bg, alpha);
	return new Gurax::Value_Number(rtn);
}

// wx.Colour.ChangeLightnessRGB(r as Number, g as Number, b as Number, ialpha as Number)
Gurax_DeclareClassMethodAlias(wxColour, ChangeLightnessRGB_gurax, "ChangeLightnessRGB")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("r", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("g", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("b", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ialpha", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxColour, ChangeLightnessRGB_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned char r = args_gurax.PickNumber<unsigned char>();
	unsigned char g = args_gurax.PickNumber<unsigned char>();
	unsigned char b = args_gurax.PickNumber<unsigned char>();
	int ialpha = args_gurax.PickNumber<int>();
	// Function body
	wxColour::ChangeLightness(&r, &g, &b, ialpha);
	return Value_Tuple::Create(new Value_Number(r), new Value_Number(g), new Value_Number(b));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxColour
//------------------------------------------------------------------------------
VType_wxColour VTYPE_wxColour("Colour");

void VType_wxColour::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Colour_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxColour, Alpha_gurax));
	Assign(Gurax_CreateMethod(wxColour, Blue_gurax));
	Assign(Gurax_CreateMethod(wxColour, GetAsString_gurax));
	Assign(Gurax_CreateMethod(wxColour, Green_gurax));
	Assign(Gurax_CreateMethod(wxColour, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxColour, Red_gurax));
	Assign(Gurax_CreateMethod(wxColour, MakeDisabled_gurax));
	Assign(Gurax_CreateMethod(wxColour, ChangeLightness_gurax));
	Assign(Gurax_CreateMethod(wxColour, SetRGB_gurax));
	Assign(Gurax_CreateMethod(wxColour, SetRGBA_gurax));
	Assign(Gurax_CreateMethod(wxColour, GetRGB_gurax));
	Assign(Gurax_CreateMethod(wxColour, GetRGBA_gurax));
	Assign(Gurax_CreateMethod(wxColour, Set_gurax));
	Assign(Gurax_CreateMethod(wxColour, MakeMonoRGB_gurax));
	Assign(Gurax_CreateMethod(wxColour, MakeDisabledRGB_gurax));
	Assign(Gurax_CreateMethod(wxColour, MakeGreyRGB_gurax));
	Assign(Gurax_CreateMethod(wxColour, AlphaBlend_gurax));
	Assign(Gurax_CreateMethod(wxColour, ChangeLightnessRGB_gurax));
}

Value* VType_wxColour::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Value_Color> pValueCasted(value.Cast<Value_Color>(processor, flags));
	if (pValueCasted) {
		const Color& color = pValueCasted->GetColor();
		return new Value_wxColour(wxColour(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_wxColour
//------------------------------------------------------------------------------
VType& Value_wxColour::vtype = VTYPE_wxColour;

String Value_wxColour::ToString(const StringStyle& ss) const
{
	const wxColour& color = GetEntity();
	return ToStringGeneric(ss, String().Format("wx.Colour:#%02X%02X%02X", color.Red(), color.Green(), color.Blue()));
}

Gurax_EndModuleScope(wx)
