//==============================================================================
// VType_wxFontInfo.cpp
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

${help.ComposePropertyHelp(wxFontInfo)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxFontInfo)}

${help.ComposeMethodHelp(wxFontInfo)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontInfo(arg? as Any) {block?}
Gurax_DeclareConstructorAlias(FontInfo_gurax, "FontInfo")
{
	Declare(VTYPE_wxFontInfo, Flag::None);
	DeclareArg("arg", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.FontInfo.");
}

Gurax_ImplementConstructorEx(FontInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::Value& arg = args_gurax.IsValid()? args_gurax.PickValue() : Value::C_nil();
	// Function body
	if (arg.IsInvalid()) {
		return new Value_wxFontInfo(wxFontInfo());
	} else if (arg.IsInstanceOf(VTYPE_Number)) {
		int pointSize = Value_Number::GetNumber<int>(arg);
		return new Value_wxFontInfo(wxFontInfo(pointSize));
	} else if (arg.IsInstanceOf(VTYPE_wxSize)) {
		const wxSize& pixelSize = Value_wxSize::GetEntity(arg);
		return new Value_wxFontInfo(wxFontInfo(pixelSize));
	} else {
		Error::Issue(ErrorType::TypeError,
			"The argument arg takes a value of Number or wx.Size");
		return Value::nil();
	}
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FontInfo#Family(family as Number)
Gurax_DeclareMethodAlias(wxFontInfo, Family_gurax, "Family")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("family", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Family_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontFamily family = args_gurax.PickNumber<wxFontFamily>();
	// Function body
	pEntity_gurax->Family(family);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#FaceName(faceName as String)
Gurax_DeclareMethodAlias(wxFontInfo, FaceName_gurax, "FaceName")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("faceName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, FaceName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* faceName = args_gurax.PickString();
	// Function body
	pEntity_gurax->FaceName(faceName);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Bold(bold? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Bold_gurax, "Bold")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("bold", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Bold_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool bold = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Bold(bold);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Light(light? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Light_gurax, "Light")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("light", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Light_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool light = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Light(light);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Italic(italic? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Italic_gurax, "Italic")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("italic", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Italic_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool italic = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Italic(italic);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Slant(slant? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Slant_gurax, "Slant")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("slant", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Slant_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool slant = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Slant(slant);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#AntiAliased(antiAliased? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, AntiAliased_gurax, "AntiAliased")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("antiAliased", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, AntiAliased_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool antiAliased = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->AntiAliased(antiAliased);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Underlined(underlined? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Underlined_gurax, "Underlined")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("underlined", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Underlined_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool underlined = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Underlined(underlined);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Strikethrough(strikethrough? as Bool)
Gurax_DeclareMethodAlias(wxFontInfo, Strikethrough_gurax, "Strikethrough")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("strikethrough", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Strikethrough_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool strikethrough = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Strikethrough(strikethrough);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#Encoding(encoding as Number)
Gurax_DeclareMethodAlias(wxFontInfo, Encoding_gurax, "Encoding")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("encoding", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, Encoding_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontEncoding encoding = args_gurax.PickNumber<wxFontEncoding>();
	// Function body
	pEntity_gurax->Encoding(encoding);
	return valueThis_gurax.Reference();
}

// wx.FontInfo#AllFlags(flags as Number)
Gurax_DeclareMethodAlias(wxFontInfo, AllFlags_gurax, "AllFlags")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFontInfo, AllFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->AllFlags(flags);
	return valueThis_gurax.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFontInfo
//------------------------------------------------------------------------------
VType_wxFontInfo VTYPE_wxFontInfo("FontInfo");

void VType_wxFontInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(FontInfo_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFontInfo, Family_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, FaceName_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Bold_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Light_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Italic_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Slant_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, AntiAliased_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Underlined_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Strikethrough_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, Encoding_gurax));
	Assign(Gurax_CreateMethod(wxFontInfo, AllFlags_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFontInfo
//------------------------------------------------------------------------------
VType& Value_wxFontInfo::vtype = VTYPE_wxFontInfo;

String Value_wxFontInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontInfo");
}

Gurax_EndModuleScope(wx)
