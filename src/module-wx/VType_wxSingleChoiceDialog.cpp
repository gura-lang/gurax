﻿//==============================================================================
// VType_wxSingleChoiceDialog.cpp
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

${help.ComposePropertyHelp(wx.SingleChoiceDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SingleChoiceDialog, `en)}

${help.ComposeMethodHelp(wx.SingleChoiceDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SingleChoiceDialog#GetSelection()
Gurax_DeclareMethodAlias(wxSingleChoiceDialog, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSingleChoiceDialog, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.SingleChoiceDialog#GetStringSelection()
Gurax_DeclareMethodAlias(wxSingleChoiceDialog, GetStringSelection_gurax, "GetStringSelection")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSingleChoiceDialog, GetStringSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetStringSelection();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.SingleChoiceDialog#SetSelection(selection as Number)
Gurax_DeclareMethodAlias(wxSingleChoiceDialog, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("selection", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSingleChoiceDialog, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int selection = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(selection);
	return Gurax::Value::nil();
}

// wx.SingleChoiceDialog#ShowModal()
Gurax_DeclareMethodAlias(wxSingleChoiceDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxSingleChoiceDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSingleChoiceDialog
//------------------------------------------------------------------------------
VType_wxSingleChoiceDialog VTYPE_wxSingleChoiceDialog("SingleChoiceDialog");

void VType_wxSingleChoiceDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSingleChoiceDialog, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxSingleChoiceDialog, GetStringSelection_gurax));
	Assign(Gurax_CreateMethod(wxSingleChoiceDialog, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxSingleChoiceDialog, ShowModal_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSingleChoiceDialog
//------------------------------------------------------------------------------
VType& Value_wxSingleChoiceDialog::vtype = VTYPE_wxSingleChoiceDialog;

String Value_wxSingleChoiceDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SingleChoiceDialog");
}

//------------------------------------------------------------------------------
// Value_wxSingleChoiceDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
