﻿//==============================================================================
// VType_wxFontPickerCtrl.cpp
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

${help.ComposePropertyHelp(wx.FontPickerCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FontPickerCtrl, `en)}

${help.ComposeMethodHelp(wx.FontPickerCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontPickerCtrl(parent as wx.Window, id as Number, font? as wx.Font, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(FontPickerCtrl_gurax, "FontPickerCtrl")
{
	Declare(VTYPE_wxFontPickerCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(FontPickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxFont& font = args_gurax.IsValid()? args_gurax.Pick<Value_wxFont>().GetEntity() : wxNullFont;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFNTP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFontPickerCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFontPickerCtrl::EntityT(parent, id, font, pos, size, style, validator, name);
	RefPtr<Value_wxFontPickerCtrl> pValue_gurax(new Value_wxFontPickerCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FontPickerCtrl#Create(parent as wx.Window, id as Number, font? as wx.Font, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxFontPickerCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontPickerCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxFont& font = args_gurax.IsValid()? args_gurax.Pick<Value_wxFont>().GetEntity() : wxNullFont;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFNTP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFontPickerCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, font, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.FontPickerCtrl#GetMaxPointSize()
Gurax_DeclareMethodAlias(wxFontPickerCtrl, GetMaxPointSize_gurax, "GetMaxPointSize")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFontPickerCtrl, GetMaxPointSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetMaxPointSize();
	return new Gurax::Value_Number(rtn);
}

// wx.FontPickerCtrl#GetSelectedFont() {block?}
Gurax_DeclareMethodAlias(wxFontPickerCtrl, GetSelectedFont_gurax, "GetSelectedFont")
{
	Declare(VTYPE_wxFont, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontPickerCtrl, GetSelectedFont_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFont(
		pEntity_gurax->GetSelectedFont()));
}

// wx.FontPickerCtrl#SetMaxPointSize(max as Number)
Gurax_DeclareMethodAlias(wxFontPickerCtrl, SetMaxPointSize_gurax, "SetMaxPointSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontPickerCtrl, SetMaxPointSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int max = args_gurax.PickNumber<unsigned int>();
	// Function body
	pEntity_gurax->SetMaxPointSize(max);
	return Gurax::Value::nil();
}

// wx.FontPickerCtrl#SetSelectedFont(font as wx.Font)
Gurax_DeclareMethodAlias(wxFontPickerCtrl, SetSelectedFont_gurax, "SetSelectedFont")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("font", VTYPE_wxFont, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFontPickerCtrl, SetSelectedFont_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetSelectedFont(font);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFontPickerCtrl
//------------------------------------------------------------------------------
VType_wxFontPickerCtrl VTYPE_wxFontPickerCtrl("FontPickerCtrl");

void VType_wxFontPickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable, Gurax_CreateConstructor(FontPickerCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFontPickerCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxFontPickerCtrl, GetMaxPointSize_gurax));
	Assign(Gurax_CreateMethod(wxFontPickerCtrl, GetSelectedFont_gurax));
	Assign(Gurax_CreateMethod(wxFontPickerCtrl, SetMaxPointSize_gurax));
	Assign(Gurax_CreateMethod(wxFontPickerCtrl, SetSelectedFont_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFontPickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxFontPickerCtrl::vtype = VTYPE_wxFontPickerCtrl;

String Value_wxFontPickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontPickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxFontPickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
