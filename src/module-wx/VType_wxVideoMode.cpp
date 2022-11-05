//==============================================================================
// VType_wxVideoMode.cpp
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

${help.ComposePropertyHelp(wxVideoMode, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxVideoMode, `en)}

${help.ComposeMethodHelp(wxVideoMode, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.VideoMode(width? as Number, height? as Number, depth? as Number, freq? as Number) {block?}
Gurax_DeclareConstructorAlias(VideoMode_gurax, "VideoMode")
{
	Declare(VTYPE_wxVideoMode, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("depth", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("freq", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.VideoMode.");
}

Gurax_ImplementConstructorEx(VideoMode_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool width_validFlag = args_gurax.IsValid();
	int width = width_validFlag? args_gurax.PickNumber<int>() : 0;
	bool height_validFlag = args_gurax.IsValid();
	int height = height_validFlag? args_gurax.PickNumber<int>() : 0;
	bool depth_validFlag = args_gurax.IsValid();
	int depth = depth_validFlag? args_gurax.PickNumber<int>() : 0;
	bool freq_validFlag = args_gurax.IsValid();
	int freq = freq_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxVideoMode(
		wxVideoMode(width, height, depth, freq)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.VideoMode#Matches(other as wx.VideoMode)
Gurax_DeclareMethodAlias(wxVideoMode, Matches_gurax, "Matches")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("other", VTYPE_wxVideoMode, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxVideoMode, Matches_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxVideoMode& value_other = args_gurax.Pick<Value_wxVideoMode>();
	const wxVideoMode& other = value_other.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->Matches(other);
	return new Gurax::Value_Bool(rtn);
}

// wx.VideoMode#GetWidth()
Gurax_DeclareMethodAlias(wxVideoMode, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxVideoMode, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.VideoMode#GetHeight()
Gurax_DeclareMethodAlias(wxVideoMode, GetHeight_gurax, "GetHeight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxVideoMode, GetHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.VideoMode#GetDepth()
Gurax_DeclareMethodAlias(wxVideoMode, GetDepth_gurax, "GetDepth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxVideoMode, GetDepth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDepth();
	return new Gurax::Value_Number(rtn);
}

// wx.VideoMode#IsOk()
Gurax_DeclareMethodAlias(wxVideoMode, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxVideoMode, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxVideoMode, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxVideoMode, w)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().w);
}

Gurax_ImplementPropertySetter(wxVideoMode, w)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int w = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().w = w;
}

Gurax_DeclareProperty_RW(wxVideoMode, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxVideoMode, h)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().h);
}

Gurax_ImplementPropertySetter(wxVideoMode, h)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int h = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().h = h;
}

Gurax_DeclareProperty_RW(wxVideoMode, bpp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxVideoMode, bpp)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().bpp);
}

Gurax_ImplementPropertySetter(wxVideoMode, bpp)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int bpp = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().bpp = bpp;
}

Gurax_DeclareProperty_RW(wxVideoMode, refresh)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(wxVideoMode, refresh)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().refresh);
}

Gurax_ImplementPropertySetter(wxVideoMode, refresh)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int refresh = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().refresh = refresh;
}

//------------------------------------------------------------------------------
// VType_wxVideoMode
//------------------------------------------------------------------------------
VType_wxVideoMode VTYPE_wxVideoMode("VideoMode");

void VType_wxVideoMode::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(VideoMode_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxVideoMode, Matches_gurax));
	Assign(Gurax_CreateMethod(wxVideoMode, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxVideoMode, GetHeight_gurax));
	Assign(Gurax_CreateMethod(wxVideoMode, GetDepth_gurax));
	Assign(Gurax_CreateMethod(wxVideoMode, IsOk_gurax));
	// Assignment of property
	Assign(Gurax_CreateProperty(wxVideoMode, w));
	Assign(Gurax_CreateProperty(wxVideoMode, h));
	Assign(Gurax_CreateProperty(wxVideoMode, bpp));
	Assign(Gurax_CreateProperty(wxVideoMode, refresh));
}

//------------------------------------------------------------------------------
// Value_wxVideoMode
//------------------------------------------------------------------------------
VType& Value_wxVideoMode::vtype = VTYPE_wxVideoMode;

String Value_wxVideoMode::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VideoMode");
}

Gurax_EndModuleScope(wx)
