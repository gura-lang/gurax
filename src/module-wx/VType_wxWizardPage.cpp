﻿//==============================================================================
// VType_wxWizardPage.cpp
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

${help.ComposePropertyHelp(wx.WizardPage, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.WizardPage, `en)}

${help.ComposeMethodHelp(wx.WizardPage, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.WizardPage, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.WizardPage, `ja)}

${help.ComposeMethodHelp(wx.WizardPage, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.WizardPage#Create(parent as wx.Wizard, bitmap? as wx.Bitmap)
Gurax_DeclareMethodAlias(wxWizardPage, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWizard, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxWizardPage, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWizard& value_parent = args_gurax.Pick<Value_wxWizard>();
	wxWizard* parent = value_parent.GetEntityPtr();
	const wxBitmap& bitmap = args_gurax.IsValid()? args_gurax.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, bitmap);
	return new Gurax::Value_Bool(rtn);
}

// wx.WizardPage#GetBitmap() {block?}
Gurax_DeclareMethodAlias(wxWizardPage, GetBitmap_gurax, "GetBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxWizardPage, GetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetBitmap()));
}

// wx.WizardPage#GetNext() {block?}
Gurax_DeclareMethodAlias(wxWizardPage, GetNext_gurax, "GetNext")
{
	Declare(VTYPE_wxWizardPage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxWizardPage, GetNext_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWizardPage(
		pEntity_gurax->GetNext()));
}

// wx.WizardPage#GetPrev() {block?}
Gurax_DeclareMethodAlias(wxWizardPage, GetPrev_gurax, "GetPrev")
{
	Declare(VTYPE_wxWizardPage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxWizardPage, GetPrev_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWizardPage(
		pEntity_gurax->GetPrev()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxWizardPage
//------------------------------------------------------------------------------
VType_wxWizardPage VTYPE_wxWizardPage("WizardPage");

void VType_wxWizardPage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxWizardPage, Create_gurax));
	Assign(Gurax_CreateMethod(wxWizardPage, GetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxWizardPage, GetNext_gurax));
	Assign(Gurax_CreateMethod(wxWizardPage, GetPrev_gurax));
}

//------------------------------------------------------------------------------
// Value_wxWizardPage
//------------------------------------------------------------------------------
VType& Value_wxWizardPage::vtype = VTYPE_wxWizardPage;

String Value_wxWizardPage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.WizardPage");
}

//------------------------------------------------------------------------------
// Value_wxWizardPage::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
