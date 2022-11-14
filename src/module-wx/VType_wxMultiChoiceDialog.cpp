﻿//==============================================================================
// VType_wxMultiChoiceDialog.cpp
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

${help.ComposePropertyHelp(wx.MultiChoiceDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MultiChoiceDialog, `en)}

${help.ComposeMethodHelp(wx.MultiChoiceDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.MultiChoiceDialog(parent as wx.Window, message as String, caption as String, choices[] as String, style? as Number, pos? as wx.Point) {block?}
Gurax_DeclareConstructorAlias(MultiChoiceDialog_gurax, "MultiChoiceDialog")
{
	Declare(VTYPE_wxMultiChoiceDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.MultiChoiceDialog.
)**");
}

Gurax_ImplementConstructorEx(MultiChoiceDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* message = args_gurax.PickString();
	const char* caption = args_gurax.PickString();
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxCHOICEDLG_STYLE;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	auto pEntity_gurax = new Value_wxMultiChoiceDialog::EntityT(parent, message, caption, choices, style, pos);
	RefPtr<Value_wxMultiChoiceDialog> pValue_gurax(new Value_wxMultiChoiceDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MultiChoiceDialog#GetSelections()
Gurax_DeclareMethodAlias(wxMultiChoiceDialog, GetSelections_gurax, "GetSelections")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMultiChoiceDialog, GetSelections_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayInt rtn = pEntity_gurax->GetSelections();
	return Util::CreateList(rtn);
}

// wx.MultiChoiceDialog#SetSelections(selections[] as Number)
Gurax_DeclareMethodAlias(wxMultiChoiceDialog, SetSelections_gurax, "SetSelections")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("selections", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMultiChoiceDialog, SetSelections_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayInt selections = Util::CreateArrayInt(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetSelections(selections);
	return Gurax::Value::nil();
}

// wx.MultiChoiceDialog#ShowModal()
Gurax_DeclareMethodAlias(wxMultiChoiceDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxMultiChoiceDialog, ShowModal_gurax, processor_gurax, argument_gurax)
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
// VType_wxMultiChoiceDialog
//------------------------------------------------------------------------------
VType_wxMultiChoiceDialog VTYPE_wxMultiChoiceDialog("MultiChoiceDialog");

void VType_wxMultiChoiceDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(MultiChoiceDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMultiChoiceDialog, GetSelections_gurax));
	Assign(Gurax_CreateMethod(wxMultiChoiceDialog, SetSelections_gurax));
	Assign(Gurax_CreateMethod(wxMultiChoiceDialog, ShowModal_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMultiChoiceDialog
//------------------------------------------------------------------------------
VType& Value_wxMultiChoiceDialog::vtype = VTYPE_wxMultiChoiceDialog;

String Value_wxMultiChoiceDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MultiChoiceDialog");
}

//------------------------------------------------------------------------------
// Value_wxMultiChoiceDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
