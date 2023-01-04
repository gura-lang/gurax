﻿//==============================================================================
// VType_wxFontDialog.cpp
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

${help.ComposePropertyHelp(wx.FontDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FontDialog, `en)}

${help.ComposeMethodHelp(wx.FontDialog, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FontDialog, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FontDialog, `ja)}

${help.ComposeMethodHelp(wx.FontDialog, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontDialog(parent as wx.Window, data? as wx.FontData) {block?}
Gurax_DeclareConstructorAlias(FontDialog_gurax, "FontDialog")
{
	Declare(VTYPE_wxFontDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_wxFontData, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(FontDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxFontData* data = args_gurax.IsValid()? args_gurax.Pick<Value_wxFontData>().GetEntityPtr() : nullptr;
	// Function body
	if (data) {
		return new Value_wxFontDialog(new wxFontDialog(parent, *data));
	} else {
		return new Value_wxFontDialog(new wxFontDialog(parent));
	}
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FontDialog#ShowModal()
Gurax_DeclareMethodAlias(wxFontDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxFontDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

// wx.FontDialog#GetFontData() {block?}
Gurax_DeclareMethodAlias(wxFontDialog, GetFontData_gurax, "GetFontData")
{
	Declare(VTYPE_wxFontData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxFontDialog, GetFontData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFontData(
		pEntity_gurax->GetFontData()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFontDialog
//------------------------------------------------------------------------------
VType_wxFontDialog VTYPE_wxFontDialog("FontDialog");

void VType_wxFontDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(FontDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFontDialog, ShowModal_gurax));
	Assign(Gurax_CreateMethod(wxFontDialog, GetFontData_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFontDialog
//------------------------------------------------------------------------------
VType& Value_wxFontDialog::vtype = VTYPE_wxFontDialog;

String Value_wxFontDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontDialog");
}

//------------------------------------------------------------------------------
// Value_wxFontDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
