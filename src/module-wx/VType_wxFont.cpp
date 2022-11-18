﻿//==============================================================================
// VType_wxFont.cpp
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

${help.ComposePropertyHelp(wx.Font, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Font, `en)}

${help.ComposeMethodHelp(wx.Font, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Font(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Font_gurax, "Font")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Font_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wxFont()
	if (args.empty()) {
		return new Value_wxFont(wxFont());
	}
	// wxFont(fontInfo as wx.FontInfo)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("fontInfo", VTYPE_wxFontInfo);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxFontInfo& fontInfo = args.Pick<Value_wxFontInfo>().GetEntity();
		return new Value_wxFont(wxFont(fontInfo));
	} while (0);
	Error::ClearIssuedFlag();
	// wxFont(pointSize as Number, family as Number, style as Number, weight as Number,
	//	underline? as Bool, faceName? as String, encoding? as Number)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pointSize", VTYPE_Number);
			pDeclCallable->DeclareArg("family", VTYPE_Number);
			pDeclCallable->DeclareArg("style", VTYPE_Number);
			pDeclCallable->DeclareArg("weight", VTYPE_Number);
			pDeclCallable->DeclareArg("underline", VTYPE_Bool, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("faceName", VTYPE_String, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("encoding", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int pointSize = args.PickNumber<int>();
		wxFontFamily family = args.PickNumber<wxFontFamily>();
		wxFontStyle style = args.PickNumber<wxFontStyle>();
		wxFontWeight weight = args.PickNumber<wxFontWeight>();
		bool underline = args.IsValid()? args.PickBool() : false;
		const char* faceName = args.IsValid()? args.PickString(): "";
		wxFontEncoding encoding = args.IsValid()? args.PickNumber<wxFontEncoding>() : wxFONTENCODING_DEFAULT;
		return new Value_wxFont(wxFont(pointSize, family, style, weight, underline, faceName, encoding));
	} while (0);
	Error::ClearIssuedFlag();
	// wxFont(pixelSize as wx.Size, family as Number, style as Number, weight as Number,
	//	underline? as Bool, faceName? as String, encoding? as Number)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pixelSize", VTYPE_wxSize);
			pDeclCallable->DeclareArg("family", VTYPE_Number);
			pDeclCallable->DeclareArg("style", VTYPE_Number);
			pDeclCallable->DeclareArg("weight", VTYPE_Number);
			pDeclCallable->DeclareArg("underline", VTYPE_Bool, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("faceName", VTYPE_String, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("encoding", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxSize& pixelSize = args.Pick<Value_wxSize>().GetEntity();
		wxFontFamily family = args.PickNumber<wxFontFamily>();
		wxFontStyle style = args.PickNumber<wxFontStyle>();
		wxFontWeight weight = args.PickNumber<wxFontWeight>();
		bool underline = args.IsValid()? args.PickBool() : false;
		const char* faceName = args.IsValid()? args.PickString(): "";
		wxFontEncoding encoding = args.IsValid()? args.PickNumber<wxFontEncoding>() : wxFONTENCODING_DEFAULT;
		return new Value_wxFont(wxFont(pixelSize, family, style, weight, underline, faceName, encoding));
	} while (0);
	Error::ClearIssuedFlag();
	// wxFont(nativeInfoString as String)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("nativeInfoString", VTYPE_String);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const char* nativeInfoString = args.PickString();
		return new Value_wxFont(wxFont(nativeInfoString));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Font#GetEncoding()
Gurax_DeclareMethodAlias(wxFont, GetEncoding_gurax, "GetEncoding")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetEncoding_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFontEncoding rtn = pEntity_gurax->GetEncoding();
	return new Gurax::Value_Number(rtn);
}

// wx.Font#GetFaceName()
Gurax_DeclareMethodAlias(wxFont, GetFaceName_gurax, "GetFaceName")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetFaceName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFaceName();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.Font#GetFamily()
Gurax_DeclareMethodAlias(wxFont, GetFamily_gurax, "GetFamily")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetFamily_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFontFamily rtn = pEntity_gurax->GetFamily();
	return new Gurax::Value_Number(rtn);
}

// wx.Font#GetNativeFontInfoDesc()
Gurax_DeclareMethodAlias(wxFont, GetNativeFontInfoDesc_gurax, "GetNativeFontInfoDesc")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetNativeFontInfoDesc_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetNativeFontInfoDesc();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.Font#GetNativeFontInfoUserDesc()
Gurax_DeclareMethodAlias(wxFont, GetNativeFontInfoUserDesc_gurax, "GetNativeFontInfoUserDesc")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetNativeFontInfoUserDesc_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetNativeFontInfoUserDesc();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.Font#GetPointSize()
Gurax_DeclareMethodAlias(wxFont, GetPointSize_gurax, "GetPointSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetPointSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPointSize();
	return new Gurax::Value_Number(rtn);
}

// wx.Font#GetPixelSize() {block?}
Gurax_DeclareMethodAlias(wxFont, GetPixelSize_gurax, "GetPixelSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, GetPixelSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetPixelSize()));
}

// wx.Font#GetStyle()
Gurax_DeclareMethodAlias(wxFont, GetStyle_gurax, "GetStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFontStyle rtn = pEntity_gurax->GetStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.Font#GetUnderlined()
Gurax_DeclareMethodAlias(wxFont, GetUnderlined_gurax, "GetUnderlined")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetUnderlined_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetUnderlined();
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#GetStrikethrough()
Gurax_DeclareMethodAlias(wxFont, GetStrikethrough_gurax, "GetStrikethrough")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetStrikethrough_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetStrikethrough();
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#GetWeight()
Gurax_DeclareMethodAlias(wxFont, GetWeight_gurax, "GetWeight")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, GetWeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFontWeight rtn = pEntity_gurax->GetWeight();
	return new Gurax::Value_Number(rtn);
}

// wx.Font#IsFixedWidth()
Gurax_DeclareMethodAlias(wxFont, IsFixedWidth_gurax, "IsFixedWidth")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, IsFixedWidth_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFixedWidth();
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#IsOk()
Gurax_DeclareMethodAlias(wxFont, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#Bold() {block?}
Gurax_DeclareMethodAlias(wxFont, Bold_gurax, "Bold")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Bold_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Bold()));
}

// wx.Font#Italic() {block?}
Gurax_DeclareMethodAlias(wxFont, Italic_gurax, "Italic")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Italic_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Italic()));
}

// wx.Font#Larger() {block?}
Gurax_DeclareMethodAlias(wxFont, Larger_gurax, "Larger")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Larger_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Larger()));
}

// wx.Font#Smaller() {block?}
Gurax_DeclareMethodAlias(wxFont, Smaller_gurax, "Smaller")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Smaller_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Smaller()));
}

// wx.Font#Underlined() {block?}
Gurax_DeclareMethodAlias(wxFont, Underlined_gurax, "Underlined")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Underlined_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Underlined()));
}

// wx.Font#Strikethrough() {block?}
Gurax_DeclareMethodAlias(wxFont, Strikethrough_gurax, "Strikethrough")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Strikethrough_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Strikethrough()));
}

// wx.Font#MakeBold()
Gurax_DeclareMethodAlias(wxFont, MakeBold_gurax, "MakeBold")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeBold_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeBold();
	return valueThis_gurax.Reference();
}

// wx.Font#MakeItalic()
Gurax_DeclareMethodAlias(wxFont, MakeItalic_gurax, "MakeItalic")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeItalic_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeItalic();
	return valueThis_gurax.Reference();
}

// wx.Font#MakeLarger()
Gurax_DeclareMethodAlias(wxFont, MakeLarger_gurax, "MakeLarger")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeLarger_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeLarger();
	return valueThis_gurax.Reference();
}

// wx.Font#MakeSmaller()
Gurax_DeclareMethodAlias(wxFont, MakeSmaller_gurax, "MakeSmaller")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeSmaller_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeSmaller();
	return valueThis_gurax.Reference();
}

// wx.Font#MakeUnderlined()
Gurax_DeclareMethodAlias(wxFont, MakeUnderlined_gurax, "MakeUnderlined")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeUnderlined_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeUnderlined();
	return valueThis_gurax.Reference();
}

// wx.Font#MakeStrikethrough()
Gurax_DeclareMethodAlias(wxFont, MakeStrikethrough_gurax, "MakeStrikethrough")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxFont, MakeStrikethrough_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->MakeStrikethrough();
	return valueThis_gurax.Reference();
}

// wx.Font#Scale(x as Number) {block?}
Gurax_DeclareMethodAlias(wxFont, Scale_gurax, "Scale")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Scale_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	float x = args_gurax.PickNumber<float>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Scale(x)));
}

// wx.Font#Scaled(x as Number) {block?}
Gurax_DeclareMethodAlias(wxFont, Scaled_gurax, "Scaled")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFont, Scaled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	float x = args_gurax.PickNumber<float>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->Scaled(x)));
}

// wx.Font#SetEncoding(encoding as Number)
Gurax_DeclareMethodAlias(wxFont, SetEncoding_gurax, "SetEncoding")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("encoding", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetEncoding_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontEncoding encoding = args_gurax.PickNumber<wxFontEncoding>();
	// Function body
	pEntity_gurax->SetEncoding(encoding);
	return Gurax::Value::nil();
}

// wx.Font#SetFaceName(faceName as String)
Gurax_DeclareMethodAlias(wxFont, SetFaceName_gurax, "SetFaceName")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("faceName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetFaceName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* faceName = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetFaceName(faceName);
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#SetFamily(family as Number)
Gurax_DeclareMethodAlias(wxFont, SetFamily_gurax, "SetFamily")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("family", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetFamily_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontFamily family = args_gurax.PickNumber<wxFontFamily>();
	// Function body
	pEntity_gurax->SetFamily(family);
	return Gurax::Value::nil();
}

// wx.Font#SetNativeFontInfo(info as String)
Gurax_DeclareMethodAlias(wxFont, SetNativeFontInfo_gurax, "SetNativeFontInfo")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("info", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetNativeFontInfo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* info = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetNativeFontInfo(info);
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#SetNativeFontInfoUserDesc(info as String)
Gurax_DeclareMethodAlias(wxFont, SetNativeFontInfoUserDesc_gurax, "SetNativeFontInfoUserDesc")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("info", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetNativeFontInfoUserDesc_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* info = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetNativeFontInfoUserDesc(info);
	return new Gurax::Value_Bool(rtn);
}

// wx.Font#SetPointSize(pointSize as Number)
Gurax_DeclareMethodAlias(wxFont, SetPointSize_gurax, "SetPointSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pointSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetPointSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pointSize = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPointSize(pointSize);
	return Gurax::Value::nil();
}

// wx.Font#SetPixelSize(pixelSize as wx.Size)
Gurax_DeclareMethodAlias(wxFont, SetPixelSize_gurax, "SetPixelSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pixelSize", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetPixelSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_pixelSize = args_gurax.Pick<Value_wxSize>();
	const wxSize& pixelSize = value_pixelSize.GetEntity();
	// Function body
	pEntity_gurax->SetPixelSize(pixelSize);
	return Gurax::Value::nil();
}

// wx.Font#SetStyle(style as Number)
Gurax_DeclareMethodAlias(wxFont, SetStyle_gurax, "SetStyle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontStyle style = args_gurax.PickNumber<wxFontStyle>();
	// Function body
	pEntity_gurax->SetStyle(style);
	return Gurax::Value::nil();
}

// wx.Font#SetSymbolicSize(size as Number)
Gurax_DeclareMethodAlias(wxFont, SetSymbolicSize_gurax, "SetSymbolicSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetSymbolicSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontSymbolicSize size = args_gurax.PickNumber<wxFontSymbolicSize>();
	// Function body
	pEntity_gurax->SetSymbolicSize(size);
	return Gurax::Value::nil();
}

// wx.Font#SetSymbolicSizeRelativeTo(size as Number, base as Number)
Gurax_DeclareMethodAlias(wxFont, SetSymbolicSizeRelativeTo_gurax, "SetSymbolicSizeRelativeTo")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetSymbolicSizeRelativeTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontSymbolicSize size = args_gurax.PickNumber<wxFontSymbolicSize>();
	int base = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSymbolicSizeRelativeTo(size, base);
	return Gurax::Value::nil();
}

// wx.Font#SetUnderlined(underlined as Bool)
Gurax_DeclareMethodAlias(wxFont, SetUnderlined_gurax, "SetUnderlined")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("underlined", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetUnderlined_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool underlined = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetUnderlined(underlined);
	return Gurax::Value::nil();
}

// wx.Font#SetStrikethrough(strikethrough as Bool)
Gurax_DeclareMethodAlias(wxFont, SetStrikethrough_gurax, "SetStrikethrough")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("strikethrough", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetStrikethrough_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool strikethrough = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetStrikethrough(strikethrough);
	return Gurax::Value::nil();
}

// wx.Font#SetWeight(weight as Number)
Gurax_DeclareMethodAlias(wxFont, SetWeight_gurax, "SetWeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("weight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFont, SetWeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFontWeight weight = args_gurax.PickNumber<wxFontWeight>();
	// Function body
	pEntity_gurax->SetWeight(weight);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFont
//------------------------------------------------------------------------------
VType_wxFont VTYPE_wxFont("Font");

void VType_wxFont::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable, Gurax_CreateConstructor(Font_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFont, GetEncoding_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetFaceName_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetFamily_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetNativeFontInfoDesc_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetNativeFontInfoUserDesc_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetPointSize_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetPixelSize_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetStyle_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetUnderlined_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetStrikethrough_gurax));
	Assign(Gurax_CreateMethod(wxFont, GetWeight_gurax));
	Assign(Gurax_CreateMethod(wxFont, IsFixedWidth_gurax));
	Assign(Gurax_CreateMethod(wxFont, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxFont, Bold_gurax));
	Assign(Gurax_CreateMethod(wxFont, Italic_gurax));
	Assign(Gurax_CreateMethod(wxFont, Larger_gurax));
	Assign(Gurax_CreateMethod(wxFont, Smaller_gurax));
	Assign(Gurax_CreateMethod(wxFont, Underlined_gurax));
	Assign(Gurax_CreateMethod(wxFont, Strikethrough_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeBold_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeItalic_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeLarger_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeSmaller_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeUnderlined_gurax));
	Assign(Gurax_CreateMethod(wxFont, MakeStrikethrough_gurax));
	Assign(Gurax_CreateMethod(wxFont, Scale_gurax));
	Assign(Gurax_CreateMethod(wxFont, Scaled_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetEncoding_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetFaceName_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetFamily_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetNativeFontInfo_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetNativeFontInfoUserDesc_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetPointSize_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetPixelSize_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetStyle_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetSymbolicSize_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetSymbolicSizeRelativeTo_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetUnderlined_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetStrikethrough_gurax));
	Assign(Gurax_CreateMethod(wxFont, SetWeight_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFont
//------------------------------------------------------------------------------
VType& Value_wxFont::vtype = VTYPE_wxFont;

String Value_wxFont::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Font");
}

Gurax_EndModuleScope(wx)
