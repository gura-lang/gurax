﻿//==============================================================================
// VType_wxBusyCursor.cpp
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

${help.ComposePropertyHelp(wx.BusyCursor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.BusyCursor, `en)}

${help.ComposeMethodHelp(wx.BusyCursor, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.BusyCursor, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.BusyCursor, `ja)}

${help.ComposeMethodHelp(wx.BusyCursor, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.BusyCursor(cursor? as wx.Cursor) {block?}
Gurax_DeclareConstructorAlias(BusyCursor_gurax, "BusyCursor")
{
	Declare(VTYPE_wxBusyCursor, Flag::None);
	DeclareArg("cursor", VTYPE_wxCursor, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(BusyCursor_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const wxCursor* cursor = args_gurax.IsValid()? args_gurax.Pick<Value_wxCursor>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBusyCursor(
		wxBusyCursor(cursor)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBusyCursor
//------------------------------------------------------------------------------
VType_wxBusyCursor VTYPE_wxBusyCursor("BusyCursor");

void VType_wxBusyCursor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(BusyCursor_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxBusyCursor
//------------------------------------------------------------------------------
VType& Value_wxBusyCursor::vtype = VTYPE_wxBusyCursor;

String Value_wxBusyCursor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BusyCursor");
}

Gurax_EndModuleScope(wx)
