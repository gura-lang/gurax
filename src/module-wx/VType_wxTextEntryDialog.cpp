﻿//==============================================================================
// VType_wxTextEntryDialog.cpp
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

${help.ComposePropertyHelp(wx.TextEntryDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.TextEntryDialog, `en)}

${help.ComposeMethodHelp(wx.TextEntryDialog, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.TextEntryDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.TextEntryDialog, `ja)}

${help.ComposeMethodHelp(wx.TextEntryDialog, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.TextEntryDialog(parent:nil as wx.Window, message as String, caption? as String, value? as String, style? as Number, pos? as wx.Point) {block?}
Gurax_DeclareConstructorAlias(TextEntryDialog_gurax, "TextEntryDialog")
{
	Declare(VTYPE_wxTextEntryDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(TextEntryDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxGetTextFromUserPromptStr;
	bool value_validFlag = args_gurax.IsValid();
	wxString value = value_validFlag? wxString(args_gurax.PickString()) : "";
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTextEntryDialogStyle;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	auto pEntity_gurax = new Value_wxTextEntryDialog::EntityT(parent, message, caption, value, style, pos);
	RefPtr<Value_wxTextEntryDialog> pValue_gurax(new Value_wxTextEntryDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TextEntryDialog#Create(parent as wx.Window, message as String, caption? as String, value? as String, style? as Number, pos? as wx.Point)
Gurax_DeclareMethodAlias(wxTextEntryDialog, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxGetTextFromUserPromptStr;
	bool value_validFlag = args_gurax.IsValid();
	wxString value = value_validFlag? wxString(args_gurax.PickString()) : "";
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTextEntryDialogStyle;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, message, caption, value, style, pos);
	return new Gurax::Value_Bool(rtn);
}

// wx.TextEntryDialog#GetValue()
Gurax_DeclareMethodAlias(wxTextEntryDialog, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.TextEntryDialog#SetMaxLength(len as Number)
Gurax_DeclareMethodAlias(wxTextEntryDialog, SetMaxLength_gurax, "SetMaxLength")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, SetMaxLength_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned long len = args_gurax.PickNumber<unsigned long>();
	// Function body
	pEntity_gurax->SetMaxLength(len);
	return Gurax::Value::nil();
}

// wx.TextEntryDialog#SetValue(value as String)
Gurax_DeclareMethodAlias(wxTextEntryDialog, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString value(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetValue(value);
	return Gurax::Value::nil();
}

// wx.TextEntryDialog#ShowModal()
Gurax_DeclareMethodAlias(wxTextEntryDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

// wx.TextEntryDialog#SetTextValidator(args* as Any)
Gurax_DeclareMethodAlias(wxTextEntryDialog, SetTextValidator_gurax, "SetTextValidator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxTextEntryDialog, SetTextValidator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// SetTextValidator(validator as const_TextValidator_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("validator", VTYPE_wxTextValidator);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxTextValidator& validator = args.Pick<Value_wxTextValidator>().GetEntity();
		pEntity_gurax->SetTextValidator(validator);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	// SetTextValidator(style as TextValidatorStyle = wxFILTER_NONE) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("style", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxTextValidatorStyle style = args.IsValid()? args.PickNumber<wxTextValidatorStyle>() : wxFILTER_NONE;
		pEntity_gurax->SetTextValidator(style);
		return Value::nil();
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTextEntryDialog
//------------------------------------------------------------------------------
VType_wxTextEntryDialog VTYPE_wxTextEntryDialog("TextEntryDialog");

void VType_wxTextEntryDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(TextEntryDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTextEntryDialog, Create_gurax));
	Assign(Gurax_CreateMethod(wxTextEntryDialog, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxTextEntryDialog, SetMaxLength_gurax));
	Assign(Gurax_CreateMethod(wxTextEntryDialog, SetValue_gurax));
	Assign(Gurax_CreateMethod(wxTextEntryDialog, ShowModal_gurax));
	Assign(Gurax_CreateMethod(wxTextEntryDialog, SetTextValidator_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTextEntryDialog
//------------------------------------------------------------------------------
VType& Value_wxTextEntryDialog::vtype = VTYPE_wxTextEntryDialog;

String Value_wxTextEntryDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TextEntryDialog");
}

//------------------------------------------------------------------------------
// Value_wxTextEntryDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
