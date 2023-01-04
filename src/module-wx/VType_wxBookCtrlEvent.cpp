﻿//==============================================================================
// VType_wxBookCtrlEvent.cpp
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

${help.ComposePropertyHelp(wx.BookCtrlEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BookCtrlEvent, `en)}

${help.ComposeMethodHelp(wx.BookCtrlEvent, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.BookCtrlEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.BookCtrlEvent, `ja)}

${help.ComposeMethodHelp(wx.BookCtrlEvent, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BookCtrlEvent#GetOldSelection()
Gurax_DeclareMethodAlias(wxBookCtrlEvent, GetOldSelection_gurax, "GetOldSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBookCtrlEvent, GetOldSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetOldSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlEvent#GetSelection()
Gurax_DeclareMethodAlias(wxBookCtrlEvent, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxBookCtrlEvent, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlEvent#SetOldSelection(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlEvent, SetOldSelection_gurax, "SetOldSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBookCtrlEvent, SetOldSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetOldSelection(page);
	return Gurax::Value::nil();
}

// wx.BookCtrlEvent#SetSelection(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlEvent, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxBookCtrlEvent, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(page);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBookCtrlEvent
//------------------------------------------------------------------------------
VType_wxBookCtrlEvent VTYPE_wxBookCtrlEvent("BookCtrlEvent");

void VType_wxBookCtrlEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBookCtrlEvent, GetOldSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlEvent, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlEvent, SetOldSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlEvent, SetSelection_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBookCtrlEvent
//------------------------------------------------------------------------------
VType& Value_wxBookCtrlEvent::vtype = VTYPE_wxBookCtrlEvent;
EventValueFactoryDeriv<Value_wxBookCtrlEvent> Value_wxBookCtrlEvent::eventValueFactory;

String Value_wxBookCtrlEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BookCtrlEvent");
}

Gurax_EndModuleScope(wx)
