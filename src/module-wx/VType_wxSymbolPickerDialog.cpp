﻿//==============================================================================
// VType_wxSymbolPickerDialog.cpp
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

${help.ComposePropertyHelp(wx.SymbolPickerDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SymbolPickerDialog, `en)}

${help.ComposeMethodHelp(wx.SymbolPickerDialog, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SymbolPickerDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SymbolPickerDialog, `ja)}

${help.ComposeMethodHelp(wx.SymbolPickerDialog, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.SymbolPickerDialog(symbol as String, initialFont as String, normalTextFont as String, parent as wx.Window, id? as Number, title? as String, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(SymbolPickerDialog_gurax, "SymbolPickerDialog")
{
	Declare(VTYPE_wxSymbolPickerDialog, Flag::None);
	DeclareArg("symbol", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("initialFont", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("normalTextFont", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(SymbolPickerDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* symbol = args_gurax.PickString();
	const char* initialFont = args_gurax.PickString();
	const char* normalTextFont = args_gurax.PickString();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* title = args_gurax.IsValid()? args_gurax.PickString() : "Symbols";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : ((wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) | wxCLOSE_BOX);
	// Function body
	auto pEntity_gurax = new Value_wxSymbolPickerDialog::EntityT(symbol, initialFont, normalTextFont, parent, id, title, pos, size, style);
	RefPtr<Value_wxSymbolPickerDialog> pValue_gurax(new Value_wxSymbolPickerDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SymbolPickerDialog#Create(symbol as String, initialFont as String, normalTextFont as String, parent as wx.Window, id? as Number, caption? as String, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("symbol", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("initialFont", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("normalTextFont", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* symbol = args_gurax.PickString();
	const char* initialFont = args_gurax.PickString();
	const char* normalTextFont = args_gurax.PickString();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* caption = args_gurax.IsValid()? args_gurax.PickString() : "Symbols";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxSize(400, 300);
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : ((wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) | wxCLOSE_BOX);
	// Function body
	bool rtn = pEntity_gurax->Create(symbol, initialFont, normalTextFont, parent, id, caption, pos, size, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.SymbolPickerDialog#GetFontName()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, GetFontName_gurax, "GetFontName")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, GetFontName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFontName();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.SymbolPickerDialog#GetFromUnicode()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, GetFromUnicode_gurax, "GetFromUnicode")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, GetFromUnicode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetFromUnicode();
	return new Gurax::Value_Bool(rtn);
}

// wx.SymbolPickerDialog#GetNormalTextFontName()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, GetNormalTextFontName_gurax, "GetNormalTextFontName")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, GetNormalTextFontName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetNormalTextFontName();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.SymbolPickerDialog#GetSymbol()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, GetSymbol_gurax, "GetSymbol")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, GetSymbol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetSymbol();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.SymbolPickerDialog#GetSymbolChar()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, GetSymbolChar_gurax, "GetSymbolChar")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, GetSymbolChar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSymbolChar();
	return new Gurax::Value_Number(rtn);
}

// wx.SymbolPickerDialog#HasSelection()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, HasSelection_gurax, "HasSelection")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, HasSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.SymbolPickerDialog#SetFontName(value as String)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, SetFontName_gurax, "SetFontName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, SetFontName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* value = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetFontName(value);
	return Gurax::Value::nil();
}

// wx.SymbolPickerDialog#SetFromUnicode(value as Bool)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, SetFromUnicode_gurax, "SetFromUnicode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, SetFromUnicode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool value = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetFromUnicode(value);
	return Gurax::Value::nil();
}

// wx.SymbolPickerDialog#SetNormalTextFontName(value as String)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, SetNormalTextFontName_gurax, "SetNormalTextFontName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, SetNormalTextFontName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* value = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetNormalTextFontName(value);
	return Gurax::Value::nil();
}

// wx.SymbolPickerDialog#SetSymbol(value as String)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, SetSymbol_gurax, "SetSymbol")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, SetSymbol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* value = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetSymbol(value);
	return Gurax::Value::nil();
}

// wx.SymbolPickerDialog#SetUnicodeMode(unicodeMode as Bool)
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, SetUnicodeMode_gurax, "SetUnicodeMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("unicodeMode", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, SetUnicodeMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool unicodeMode = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetUnicodeMode(unicodeMode);
	return Gurax::Value::nil();
}

// wx.SymbolPickerDialog#UseNormalFont()
Gurax_DeclareMethodAlias(wxSymbolPickerDialog, UseNormalFont_gurax, "UseNormalFont")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxSymbolPickerDialog, UseNormalFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->UseNormalFont();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSymbolPickerDialog
//------------------------------------------------------------------------------
VType_wxSymbolPickerDialog VTYPE_wxSymbolPickerDialog("SymbolPickerDialog");

void VType_wxSymbolPickerDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(SymbolPickerDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, Create_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, GetFontName_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, GetFromUnicode_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, GetNormalTextFontName_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, GetSymbol_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, GetSymbolChar_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, HasSelection_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, SetFontName_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, SetFromUnicode_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, SetNormalTextFontName_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, SetSymbol_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, SetUnicodeMode_gurax));
	Assign(Gurax_CreateMethod(wxSymbolPickerDialog, UseNormalFont_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSymbolPickerDialog
//------------------------------------------------------------------------------
VType& Value_wxSymbolPickerDialog::vtype = VTYPE_wxSymbolPickerDialog;

String Value_wxSymbolPickerDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SymbolPickerDialog");
}

//------------------------------------------------------------------------------
// Value_wxSymbolPickerDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
