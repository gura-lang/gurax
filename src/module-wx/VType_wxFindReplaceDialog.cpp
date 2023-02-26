﻿//==============================================================================
// VType_wxFindReplaceDialog.cpp
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

${help.ComposePropertyHelp(wx.FindReplaceDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FindReplaceDialog, `en)}

${help.ComposeMethodHelp(wx.FindReplaceDialog, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FindReplaceDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FindReplaceDialog, `ja)}

${help.ComposeMethodHelp(wx.FindReplaceDialog, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FindReplaceDialog(parent:nil as wx.Window, data as wx.FindReplaceData, title as String, style? as Number) {block?}
Gurax_DeclareConstructorAlias(FindReplaceDialog_gurax, "FindReplaceDialog")
{
	Declare(VTYPE_wxFindReplaceDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::Nil);
	DeclareArg("data", VTYPE_wxFindReplaceData, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(FindReplaceDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	Value_wxFindReplaceData& value_data = args_gurax.Pick<Value_wxFindReplaceData>();
	wxFindReplaceData* data = value_data.GetEntityPtr();
	const char* title = args_gurax.PickString();
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxFindReplaceDialog::EntityT(parent, data, title, style);
	RefPtr<Value_wxFindReplaceDialog> pValue_gurax(new Value_wxFindReplaceDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FindReplaceDialog#Create(parent as wx.Window, data as wx.FindReplaceData, title as String, style? as Number)
Gurax_DeclareMethodAlias(wxFindReplaceDialog, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_wxFindReplaceData, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxFindReplaceDialog, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	Value_wxFindReplaceData& value_data = args_gurax.Pick<Value_wxFindReplaceData>();
	wxFindReplaceData* data = value_data.GetEntityPtr();
	const char* title = args_gurax.PickString();
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, data, title, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.FindReplaceDialog#GetData() {block?}
Gurax_DeclareMethodAlias(wxFindReplaceDialog, GetData_gurax, "GetData")
{
	Declare(VTYPE_wxFindReplaceData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFindReplaceDialog, GetData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFindReplaceData(
		*pEntity_gurax->GetData()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFindReplaceDialog
//------------------------------------------------------------------------------
VType_wxFindReplaceDialog VTYPE_wxFindReplaceDialog("FindReplaceDialog");

void VType_wxFindReplaceDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(FindReplaceDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFindReplaceDialog, Create_gurax));
	Assign(Gurax_CreateMethod(wxFindReplaceDialog, GetData_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFindReplaceDialog
//------------------------------------------------------------------------------
VType& Value_wxFindReplaceDialog::vtype = VTYPE_wxFindReplaceDialog;

String Value_wxFindReplaceDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FindReplaceDialog");
}

//------------------------------------------------------------------------------
// Value_wxFindReplaceDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
