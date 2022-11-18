﻿//==============================================================================
// VType_wxProgressDialog.cpp
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

${help.ComposePropertyHelp(wx.ProgressDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ProgressDialog, `en)}

${help.ComposeMethodHelp(wx.ProgressDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ProgressDialog(title as String, message as String, maximum? as Number, parent? as wx.Window, style? as Number) {block?}
Gurax_DeclareConstructorAlias(ProgressDialog_gurax, "ProgressDialog")
{
	Declare(VTYPE_wxProgressDialog, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maximum", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ProgressDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	const char* message = args_gurax.PickString();
	bool maximum_validFlag = args_gurax.IsValid();
	int maximum = maximum_validFlag? args_gurax.PickNumber<int>() : 100;
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : (wxPD_APP_MODAL | wxPD_AUTO_HIDE);
	// Function body
	auto pEntity_gurax = new Value_wxProgressDialog::EntityT(title, message, maximum, parent, style);
	RefPtr<Value_wxProgressDialog> pValue_gurax(new Value_wxProgressDialog(pEntity_gurax));
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
// VType_wxProgressDialog
//------------------------------------------------------------------------------
VType_wxProgressDialog VTYPE_wxProgressDialog("ProgressDialog");

void VType_wxProgressDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGenericProgressDialog, Flag::Mutable, Gurax_CreateConstructor(ProgressDialog_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxProgressDialog
//------------------------------------------------------------------------------
VType& Value_wxProgressDialog::vtype = VTYPE_wxProgressDialog;

String Value_wxProgressDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ProgressDialog");
}

//------------------------------------------------------------------------------
// Value_wxProgressDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
