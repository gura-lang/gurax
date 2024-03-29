﻿//==============================================================================
// VType_wxCalendarDateAttr.cpp
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

${help.ComposePropertyHelp(wx.CalendarDateAttr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CalendarDateAttr, `en)}

${help.ComposeMethodHelp(wx.CalendarDateAttr, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.CalendarDateAttr, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.CalendarDateAttr, `ja)}

${help.ComposeMethodHelp(wx.CalendarDateAttr, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.CalendarDateAttr(args* as Any) {block?}
Gurax_DeclareConstructorAlias(CalendarDateAttr_gurax, "CalendarDateAttr")
{
	Declare(VTYPE_wxCalendarDateAttr, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(CalendarDateAttr_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("border", VTYPE_Number);
			pDeclCallable->DeclareArg("colBorder", VTYPE_wxColour, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCalendarDateBorder border = args.PickNumber<wxCalendarDateBorder>();
		const wxColour& colBorder = args.IsValid()? args.Pick<Value_wxColour>().GetEntity() : wxNullColour;
		wxCalendarDateAttr rtn(border, colBorder);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxCalendarDateAttr(rtn));
	} while (0);
	Error::ClearIssuedFlag();
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("colText", VTYPE_wxColour, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("colBack", VTYPE_wxColour, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("colBorder", VTYPE_wxColour, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("font", VTYPE_wxFont, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("border", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxColour& colText = args.IsValid()? args.Pick<Value_wxColour>().GetEntity() : wxNullColour;
		const wxColour& colBack = args.IsValid()? args.Pick<Value_wxColour>().GetEntity() : wxNullColour;
		const wxColour& colBorder = args.IsValid()? args.Pick<Value_wxColour>().GetEntity() : wxNullColour;
		const wxFont& font = args.IsValid()? args.Pick<Value_wxFont>().GetEntity() : wxNullFont;
		wxCalendarDateBorder border = args.IsValid()? args.PickNumber<wxCalendarDateBorder>() : wxCAL_BORDER_NONE;
		wxCalendarDateAttr rtn(colText, colBack, colBorder, font, border);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxCalendarDateAttr(rtn));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CalendarDateAttr#GetBackgroundColour() {block?}
Gurax_DeclareMethodAlias(wxCalendarDateAttr, GetBackgroundColour_gurax, "GetBackgroundColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, GetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetBackgroundColour()));
}

// wx.CalendarDateAttr#GetBorder()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, GetBorder_gurax, "GetBorder")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, GetBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxCalendarDateBorder rtn = pEntity_gurax->GetBorder();
	return new Gurax::Value_Number(rtn);
}

// wx.CalendarDateAttr#GetBorderColour() {block?}
Gurax_DeclareMethodAlias(wxCalendarDateAttr, GetBorderColour_gurax, "GetBorderColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, GetBorderColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetBorderColour()));
}

// wx.CalendarDateAttr#GetFont() {block?}
Gurax_DeclareMethodAlias(wxCalendarDateAttr, GetFont_gurax, "GetFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, GetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(pEntity_gurax->GetFont()));
}

// wx.CalendarDateAttr#GetTextColour() {block?}
Gurax_DeclareMethodAlias(wxCalendarDateAttr, GetTextColour_gurax, "GetTextColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, GetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetTextColour()));
}

// wx.CalendarDateAttr#HasBackgroundColour()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, HasBackgroundColour_gurax, "HasBackgroundColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, HasBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasBackgroundColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#HasBorder()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, HasBorder_gurax, "HasBorder")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, HasBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasBorder();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#HasBorderColour()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, HasBorderColour_gurax, "HasBorderColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, HasBorderColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasBorderColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#HasFont()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, HasFont_gurax, "HasFont")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, HasFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasFont();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#HasTextColour()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, HasTextColour_gurax, "HasTextColour")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, HasTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasTextColour();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#IsHoliday()
Gurax_DeclareMethodAlias(wxCalendarDateAttr, IsHoliday_gurax, "IsHoliday")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, IsHoliday_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsHoliday();
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarDateAttr#SetBackgroundColour(colBack as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetBackgroundColour_gurax, "SetBackgroundColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colBack", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colBack = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBack = value_colBack.GetEntity();
	// Function body
	pEntity_gurax->SetBackgroundColour(colBack);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr#SetBorder(border as Number)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetBorder_gurax, "SetBorder")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("border", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetBorder_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxCalendarDateBorder border = args_gurax.PickNumber<wxCalendarDateBorder>();
	// Function body
	pEntity_gurax->SetBorder(border);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr#SetBorderColour(col as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetBorderColour_gurax, "SetBorderColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetBorderColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_col = args_gurax.Pick<Value_wxColour>();
	const wxColour& col = value_col.GetEntity();
	// Function body
	pEntity_gurax->SetBorderColour(col);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr#SetFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetFont_gurax, "SetFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFont& value_font = args_gurax.Pick<Value_wxFont>();
	const wxFont& font = value_font.GetEntity();
	// Function body
	pEntity_gurax->SetFont(font);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr#SetHoliday(holiday as Bool)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetHoliday_gurax, "SetHoliday")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("holiday", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetHoliday_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool holiday = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetHoliday(holiday);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr#SetTextColour(colText as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarDateAttr, SetTextColour_gurax, "SetTextColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colText", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxCalendarDateAttr, SetTextColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colText = args_gurax.Pick<Value_wxColour>();
	const wxColour& colText = value_colText.GetEntity();
	// Function body
	pEntity_gurax->SetTextColour(colText);
	return Gurax::Value::nil();
}

// wx.CalendarDateAttr.GetMark() {block?}
Gurax_DeclareClassMethodAlias(wxCalendarDateAttr, GetMark_gurax, "GetMark")
{
	Declare(VTYPE_wxCalendarDateAttr, Flag::None);
}

Gurax_ImplementClassMethodEx(wxCalendarDateAttr, GetMark_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxCalendarDateAttr(wxCalendarDateAttr::GetMark()));
}

// wx.CalendarDateAttr.SetMark(m as wx.CalendarDateAttr)
Gurax_DeclareClassMethodAlias(wxCalendarDateAttr, SetMark_gurax, "SetMark")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("m", VTYPE_wxCalendarDateAttr, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxCalendarDateAttr, SetMark_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCalendarDateAttr& value_m = args_gurax.Pick<Value_wxCalendarDateAttr>();
	const wxCalendarDateAttr& m = value_m.GetEntity();
	// Function body
	wxCalendarDateAttr::SetMark(m);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCalendarDateAttr
//------------------------------------------------------------------------------
VType_wxCalendarDateAttr VTYPE_wxCalendarDateAttr("CalendarDateAttr");

void VType_wxCalendarDateAttr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(CalendarDateAttr_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetBorder_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetBorderColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetFont_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, HasBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, HasBorder_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, HasBorderColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, HasFont_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, HasTextColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, IsHoliday_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetBorder_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetBorderColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetFont_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetHoliday_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetTextColour_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, GetMark_gurax));
	Assign(Gurax_CreateMethod(wxCalendarDateAttr, SetMark_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCalendarDateAttr
//------------------------------------------------------------------------------
VType& Value_wxCalendarDateAttr::vtype = VTYPE_wxCalendarDateAttr;

String Value_wxCalendarDateAttr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CalendarDateAttr");
}

Gurax_EndModuleScope(wx)
