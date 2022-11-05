//==============================================================================
// VType_wxPen.cpp
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

${help.ComposePropertyHelp(wx.Pen, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Pen, `en)}

${help.ComposeMethodHelp(wx.Pen, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Pen(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Pen_gurax, "Pen")
{
	Declare(VTYPE_wxPen, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Pen.");
}

Gurax_ImplementConstructorEx(Pen_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wx.Pen(colour as const_Colour_r, width as int = 1, style as PenStyle = wxPENSTYLE_SOLID)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colour", VTYPE_wxColour);
			pDeclCallable->DeclareArg("width", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("style", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxColour& colour = args.Pick<Value_wxColour>().GetEntity();
		int width = args.IsValid()? args.PickNumber<int>() : 1;
		wxPenStyle style = args.IsValid()? args.PickNumber<wxPenStyle>() : wxPENSTYLE_SOLID;
		return new Value_wxPen(wxPen(colour, width, style));
	} while (0);
	Error::ClearIssuedFlag();
	// wx.Pen(stipple as const_Bitmap_r, width as int)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("stipple", VTYPE_wxBitmap);
			pDeclCallable->DeclareArg("width", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxBitmap& stipple = args.Pick<Value_wxBitmap>().GetEntity();
		int width = args.IsValid()? args.PickNumber<int>() : 1;
		return new Value_wxPen(wxPen(stipple, width));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Pen#GetCap()
Gurax_DeclareMethodAlias(wxPen, GetCap_gurax, "GetCap")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetCap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxPenCap rtn = pEntity_gurax->GetCap();
	return new Gurax::Value_Number(rtn);
}

// wx.Pen#GetColour() {block?}
Gurax_DeclareMethodAlias(wxPen, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetColour()));
}

// wx.Pen#GetDashes()
Gurax_DeclareMethodAlias(wxPen, GetDashes_gurax, "GetDashes")
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetDashes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxDash* dashes;
	int n = pEntity_gurax->GetDashes(&dashes);
	return Value_List::Create(dashes, n);
}

// wx.Pen#GetJoin()
Gurax_DeclareMethodAlias(wxPen, GetJoin_gurax, "GetJoin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetJoin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxPenJoin rtn = pEntity_gurax->GetJoin();
	return new Gurax::Value_Number(rtn);
}

// wx.Pen#GetStipple() {block?}
Gurax_DeclareMethodAlias(wxPen, GetStipple_gurax, "GetStipple")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetStipple_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		*pEntity_gurax->GetStipple()));
}

// wx.Pen#GetStyle()
Gurax_DeclareMethodAlias(wxPen, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxPenStyle rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.Pen#GetWidth()
Gurax_DeclareMethodAlias(wxPen, GetWidth_gurax, "GetWidth")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, GetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWidth();
	return new Gurax::Value_Number(rtn);
}

// wx.Pen#IsOk()
Gurax_DeclareMethodAlias(wxPen, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Pen#IsNonTransparent()
Gurax_DeclareMethodAlias(wxPen, IsNonTransparent_gurax, "IsNonTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, IsNonTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsNonTransparent();
	return new Gurax::Value_Bool(rtn);
}

// wx.Pen#IsTransparent()
Gurax_DeclareMethodAlias(wxPen, IsTransparent_gurax, "IsTransparent")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, IsTransparent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsTransparent();
	return new Gurax::Value_Bool(rtn);
}

// wx.Pen#SetCap(capStyle as Number)
Gurax_DeclareMethodAlias(wxPen, SetCap_gurax, "SetCap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("capStyle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetCap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxPenCap capStyle = args_gurax.PickNumber<wxPenCap>();
	// Function body
	pEntity_gurax->SetCap(capStyle);
	return Gurax::Value::nil();
}

// wx.Pen#SetDashes(dash[] as Number)
Gurax_DeclareMethodAlias(wxPen, SetDashes_gurax, "SetDashes")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dash", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetDashes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto dash = args_gurax.PickNumList<wxDash>();
	// Function body
	int n = dash.sizeT<int>();
	pEntity_gurax->SetDashes(n, dash);
	return Value::nil();
}

// wx.Pen#SetJoin(join_style as Number)
Gurax_DeclareMethodAlias(wxPen, SetJoin_gurax, "SetJoin")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("join_style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetJoin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxPenJoin join_style = args_gurax.PickNumber<wxPenJoin>();
	// Function body
	pEntity_gurax->SetJoin(join_style);
	return Gurax::Value::nil();
}

// wx.Pen#SetStipple(stipple as wx.Bitmap)
Gurax_DeclareMethodAlias(wxPen, SetStipple_gurax, "SetStipple")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stipple", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetStipple_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_stipple = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& stipple = value_stipple.GetEntity();
	// Function body
	pEntity_gurax->SetStipple(stipple);
	return Gurax::Value::nil();
}

// wx.Pen#SetStyle(style as Number)
Gurax_DeclareMethodAlias(wxPen, SetStyle_gurax, "SetStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxPenStyle style = args_gurax.PickNumber<wxPenStyle>();
	// Function body
	pEntity_gurax->SetStyle(style);
	return Gurax::Value::nil();
}

// wx.Pen#SetWidth(width as Number)
Gurax_DeclareMethodAlias(wxPen, SetWidth_gurax, "SetWidth")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetWidth(width);
	return Gurax::Value::nil();
}

// wx.Pen#SetColour(args* as Any)
Gurax_DeclareMethodAlias(wxPen, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPen, SetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// SetColour(colour as Colour_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colour", VTYPE_wxColour);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxColour& colour = args.Pick<Value_wxColour>().GetEntity();
		pEntity_gurax->SetColour(colour);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// SetColour(red as unsigned_char, green as unsigned_char, blue as unsigned_char) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("red", VTYPE_Number);
			pDeclCallable->DeclareArg("green", VTYPE_Number);
			pDeclCallable->DeclareArg("blue", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		unsigned char red = args.PickNumber<unsigned char>();
		unsigned char green = args.PickNumber<unsigned char>();
		unsigned char blue = args.PickNumber<unsigned char>();
		pEntity_gurax->SetColour(red, green, blue);
		return Value::nil();
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPen
//------------------------------------------------------------------------------
VType_wxPen VTYPE_wxPen("Pen");

void VType_wxPen::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Pen_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPen, GetCap_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetDashes_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetJoin_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetStipple_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxPen, GetWidth_gurax));
	Assign(Gurax_CreateMethod(wxPen, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxPen, IsNonTransparent_gurax));
	Assign(Gurax_CreateMethod(wxPen, IsTransparent_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetCap_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetDashes_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetJoin_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetStipple_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetStyle_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetWidth_gurax));
	Assign(Gurax_CreateMethod(wxPen, SetColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPen
//------------------------------------------------------------------------------
VType& Value_wxPen::vtype = VTYPE_wxPen;

String Value_wxPen::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Pen");
}

Gurax_EndModuleScope(wx)
