﻿//==============================================================================
// VType_wxGenericProgressDialog.cpp
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

${help.ComposePropertyHelp(wx.GenericProgressDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GenericProgressDialog, `en)}

${help.ComposeMethodHelp(wx.GenericProgressDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GenericProgressDialog(title as String, message as String, maximum? as Number, parent? as wx.Window, style? as Number) {block?}
Gurax_DeclareConstructorAlias(GenericProgressDialog_gurax, "GenericProgressDialog")
{
	Declare(VTYPE_wxGenericProgressDialog, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maximum", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.GenericProgressDialog.
)**");
}

Gurax_ImplementConstructorEx(GenericProgressDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	const char* message = args_gurax.PickString();
	bool maximum_validFlag = args_gurax.IsValid();
	int maximum = maximum_validFlag? args_gurax.PickNumber<int>() : 100;
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : (wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	// Function body
	auto pEntity_gurax = new Value_wxGenericProgressDialog::EntityT(title, message, maximum, parent, style);
	RefPtr<Value_wxGenericProgressDialog> pValue_gurax(new Value_wxGenericProgressDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GenericProgressDialog#GetValue()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

// wx.GenericProgressDialog#GetRange()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, GetRange_gurax, "GetRange")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, GetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRange();
	return new Gurax::Value_Number(rtn);
}

// wx.GenericProgressDialog#GetMessage()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, GetMessage_gurax, "GetMessage")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, GetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetMessage();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.GenericProgressDialog#Resume()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, Resume_gurax, "Resume")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, Resume_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Resume();
	return Gurax::Value::nil();
}

// wx.GenericProgressDialog#SetRange(maximum as Number)
Gurax_DeclareMethodAlias(wxGenericProgressDialog, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("maximum", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int maximum = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(maximum);
	return Gurax::Value::nil();
}

// wx.GenericProgressDialog#WasCancelled()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, WasCancelled_gurax, "WasCancelled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, WasCancelled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->WasCancelled();
	return new Gurax::Value_Bool(rtn);
}

// wx.GenericProgressDialog#WasSkipped()
Gurax_DeclareMethodAlias(wxGenericProgressDialog, WasSkipped_gurax, "WasSkipped")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxGenericProgressDialog, WasSkipped_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->WasSkipped();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGenericProgressDialog
//------------------------------------------------------------------------------
VType_wxGenericProgressDialog VTYPE_wxGenericProgressDialog("GenericProgressDialog");

void VType_wxGenericProgressDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(GenericProgressDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, GetRange_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, GetMessage_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, Resume_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, WasCancelled_gurax));
	Assign(Gurax_CreateMethod(wxGenericProgressDialog, WasSkipped_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGenericProgressDialog
//------------------------------------------------------------------------------
VType& Value_wxGenericProgressDialog::vtype = VTYPE_wxGenericProgressDialog;

String Value_wxGenericProgressDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GenericProgressDialog");
}

//------------------------------------------------------------------------------
// Value_wxGenericProgressDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
