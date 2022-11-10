﻿//==============================================================================
// VType_wxPasswordEntryDialog.cpp
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

${help.ComposePropertyHelp(wx.PasswordEntryDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PasswordEntryDialog, `en)}

${help.ComposeMethodHelp(wx.PasswordEntryDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PasswordEntryDialog(parent as wx.Window, message as String, caption? as String, defaultValue? as String, style? as Number, pos? as wx.Point) {block?}
Gurax_DeclareConstructorAlias(PasswordEntryDialog_gurax, "PasswordEntryDialog")
{
	Declare(VTYPE_wxPasswordEntryDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultValue", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.PasswordEntryDialog.");
}

Gurax_ImplementConstructorEx(PasswordEntryDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* message = args_gurax.PickString();
	const char* caption = args_gurax.IsValid()? args_gurax.PickString() : wxGetPasswordFromUserPromptStr;
	const char* defaultValue = args_gurax.IsValid()? args_gurax.PickString() : "";
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxTextEntryDialogStyle;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	auto pEntity_gurax = new Value_wxPasswordEntryDialog::EntityT(parent, message, caption, defaultValue, style, pos);
	RefPtr<Value_wxPasswordEntryDialog> pValue_gurax(new Value_wxPasswordEntryDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPasswordEntryDialog
//------------------------------------------------------------------------------
VType_wxPasswordEntryDialog VTYPE_wxPasswordEntryDialog("PasswordEntryDialog");

void VType_wxPasswordEntryDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxTextEntryDialog, Flag::Mutable, Gurax_CreateConstructor(PasswordEntryDialog_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPasswordEntryDialog
//------------------------------------------------------------------------------
VType& Value_wxPasswordEntryDialog::vtype = VTYPE_wxPasswordEntryDialog;

String Value_wxPasswordEntryDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PasswordEntryDialog");
}

//------------------------------------------------------------------------------
// Value_wxPasswordEntryDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
