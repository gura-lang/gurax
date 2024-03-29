﻿//==============================================================================
// VType_wxMessageDialog.cpp
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

${help.ComposePropertyHelp(wx.MessageDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MessageDialog, `en)}

${help.ComposeMethodHelp(wx.MessageDialog, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.MessageDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.MessageDialog, `ja)}

${help.ComposeMethodHelp(wx.MessageDialog, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.MessageDialog(parent:nil as wx.Window, message as String, caption? as String, style? as Number, pos? as wx.Point) {block?}
Gurax_DeclareConstructorAlias(MessageDialog_gurax, "MessageDialog")
{
	Declare(VTYPE_wxMessageDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(MessageDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	wxString message(args_gurax.PickString());
	bool caption_validFlag = args_gurax.IsValid();
	wxString caption = caption_validFlag? wxString(args_gurax.PickString()) : wxMessageBoxCaptionStr;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : (wxOK | wxCENTRE);
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	auto pEntity_gurax = new Value_wxMessageDialog::EntityT(parent, message, caption, style, pos);
	RefPtr<Value_wxMessageDialog> pValue_gurax(new Value_wxMessageDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MessageDialog#SetExtendedMessage(extendedMessage as String)
Gurax_DeclareMethodAlias(wxMessageDialog, SetExtendedMessage_gurax, "SetExtendedMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("extendedMessage", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, SetExtendedMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString extendedMessage(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetExtendedMessage(extendedMessage);
	return Gurax::Value::nil();
}

// wx.MessageDialog#SetMessage(message as String)
Gurax_DeclareMethodAlias(wxMessageDialog, SetMessage_gurax, "SetMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, SetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString message(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetMessage(message);
	return Gurax::Value::nil();
}

// wx.MessageDialog#ShowModal()
Gurax_DeclareMethodAlias(wxMessageDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

// wx.MessageDialog#GetCaption()
Gurax_DeclareMethodAlias(wxMessageDialog, GetCaption_gurax, "GetCaption")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetCaption_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetCaption();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetMessage()
Gurax_DeclareMethodAlias(wxMessageDialog, GetMessage_gurax, "GetMessage")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetMessage();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetExtendedMessage()
Gurax_DeclareMethodAlias(wxMessageDialog, GetExtendedMessage_gurax, "GetExtendedMessage")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetExtendedMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetExtendedMessage();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetMessageDialogStyle()
Gurax_DeclareMethodAlias(wxMessageDialog, GetMessageDialogStyle_gurax, "GetMessageDialogStyle")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetMessageDialogStyle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetMessageDialogStyle();
	return new Gurax::Value_Number(rtn);
}

// wx.MessageDialog#HasCustomLabels()
Gurax_DeclareMethodAlias(wxMessageDialog, HasCustomLabels_gurax, "HasCustomLabels")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, HasCustomLabels_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasCustomLabels();
	return new Gurax::Value_Bool(rtn);
}

// wx.MessageDialog#GetYesLabel()
Gurax_DeclareMethodAlias(wxMessageDialog, GetYesLabel_gurax, "GetYesLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetYesLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetYesLabel();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetNoLabel()
Gurax_DeclareMethodAlias(wxMessageDialog, GetNoLabel_gurax, "GetNoLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetNoLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetNoLabel();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetOKLabel()
Gurax_DeclareMethodAlias(wxMessageDialog, GetOKLabel_gurax, "GetOKLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetOKLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetOKLabel();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetCancelLabel()
Gurax_DeclareMethodAlias(wxMessageDialog, GetCancelLabel_gurax, "GetCancelLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetCancelLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetCancelLabel();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetHelpLabel()
Gurax_DeclareMethodAlias(wxMessageDialog, GetHelpLabel_gurax, "GetHelpLabel")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetHelpLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetHelpLabel();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.MessageDialog#GetEffectiveIcon()
Gurax_DeclareMethodAlias(wxMessageDialog, GetEffectiveIcon_gurax, "GetEffectiveIcon")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMessageDialog, GetEffectiveIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetEffectiveIcon();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMessageDialog
//------------------------------------------------------------------------------
VType_wxMessageDialog VTYPE_wxMessageDialog("MessageDialog");

void VType_wxMessageDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(MessageDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMessageDialog, SetExtendedMessage_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, SetMessage_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, ShowModal_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetCaption_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetMessage_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetExtendedMessage_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetMessageDialogStyle_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, HasCustomLabels_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetYesLabel_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetNoLabel_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetOKLabel_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetCancelLabel_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetHelpLabel_gurax));
	Assign(Gurax_CreateMethod(wxMessageDialog, GetEffectiveIcon_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMessageDialog
//------------------------------------------------------------------------------
VType& Value_wxMessageDialog::vtype = VTYPE_wxMessageDialog;

String Value_wxMessageDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MessageDialog");
}

//------------------------------------------------------------------------------
// Value_wxMessageDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
