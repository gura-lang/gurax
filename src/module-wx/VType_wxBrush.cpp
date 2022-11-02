//==============================================================================
// VType_wxBrush.cpp
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

${help.ComposePropertyHelp(wxBrush)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxBrush)}

${help.ComposeMethodHelp(wxBrush)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Brush(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Brush_gurax, "Brush")
{
	Declare(VTYPE_wxBrush, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Brush.");
}

Gurax_ImplementConstructorEx(Brush_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.Brush(colour as const_Colour_r, style as BrushStyle = wxBRUSHSTYLE_SOLID)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colour", VTYPE_wxColour);
			pDeclCallable->DeclareArg("style", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxColour& colour = args.Pick<Value_wxColour>().GetEntity();
		wxBrushStyle style = args.IsValid()? args.PickNumber<wxBrushStyle>() : wxBRUSHSTYLE_SOLID;
		return new Value_wxBrush(wxBrush(colour, style));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Brush(stippleBitmap as const_Bitmap_r)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("stippleBitmap", VTYPE_wxBitmap);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& stippleBitmap = args.Pick<Value_wxBitmap>().GetEntity();
		return new Value_wxBrush(wxBrush(stippleBitmap));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Brush#GetColour() {block?}
Gurax_DeclareMethodAlias(wxBrush, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetColour()));
}

// wx.Brush#GetStipple() {block?}
Gurax_DeclareMethodAlias(wxBrush, GetStipple_gurax, "GetStipple")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, GetStipple_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		*pEntity_gurax->GetStipple()));
}

// wx.Brush#GetStyle()
Gurax_DeclareMethodAlias(wxBrush, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxBrushStyle rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.Brush#IsHatch()
Gurax_DeclareMethodAlias(wxBrush, IsHatch_gurax, "IsHatch")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, IsHatch_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsHatch();
	return new Gurax::Value_Bool(rtn);
}

// wx.Brush#IsOk()
Gurax_DeclareMethodAlias(wxBrush, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Brush#IsNonTransparent()
Gurax_DeclareMethodAlias(wxBrush, IsNonTransparent_gurax, "IsNonTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, IsNonTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsNonTransparent();
	return new Gurax::Value_Bool(rtn);
}

// wx.Brush#IsTransparent()
Gurax_DeclareMethodAlias(wxBrush, IsTransparent_gurax, "IsTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, IsTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsTransparent();
	return new Gurax::Value_Bool(rtn);
}

// wx.Brush#SetStipple(bitmap as wx.Bitmap)
Gurax_DeclareMethodAlias(wxBrush, SetStipple_gurax, "SetStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, SetStipple_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	// Function body
	pEntity_gurax->SetStipple(bitmap);
	return Gurax::Value::nil();
}

// wx.Brush#SetStyle(style as Number)
Gurax_DeclareMethodAlias(wxBrush, SetStyle_gurax, "SetStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, SetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxBrushStyle style = args_gurax.PickNumber<wxBrushStyle>();
	// Function body
	pEntity_gurax->SetStyle(style);
	return Gurax::Value::nil();
}

// wx.Brush#SetColour(colour as wx.Colour)
Gurax_DeclareMethodAlias(wxBrush, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, SetColour_gurax, processor_gurax, argument_gurax)
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

// wx.Brush#SetColourRGB(red as Number, green as Number, blue as Number)
Gurax_DeclareMethodAlias(wxBrush, SetColourRGB_gurax, "SetColourRGB")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("red", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("green", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("blue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBrush, SetColourRGB_gurax, processor_gurax, argument_gurax)
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
	// Function body
	pEntity_gurax->SetColour(red, green, blue);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBrush
//------------------------------------------------------------------------------
VType_wxBrush VTYPE_wxBrush("Brush");

void VType_wxBrush::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Brush_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBrush, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxBrush, GetStipple_gurax));
	Assign(Gurax_CreateMethod(wxBrush, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxBrush, IsHatch_gurax));
	Assign(Gurax_CreateMethod(wxBrush, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxBrush, IsNonTransparent_gurax));
	Assign(Gurax_CreateMethod(wxBrush, IsTransparent_gurax));
	Assign(Gurax_CreateMethod(wxBrush, SetStipple_gurax));
	Assign(Gurax_CreateMethod(wxBrush, SetStyle_gurax));
	Assign(Gurax_CreateMethod(wxBrush, SetColour_gurax));
	Assign(Gurax_CreateMethod(wxBrush, SetColourRGB_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBrush
//------------------------------------------------------------------------------
VType& Value_wxBrush::vtype = VTYPE_wxBrush;

String Value_wxBrush::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Brush");
}

Gurax_EndModuleScope(wx)
