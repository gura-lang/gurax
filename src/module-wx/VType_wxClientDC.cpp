﻿//==============================================================================
// VType_wxClientDC.cpp
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

${help.ComposePropertyHelp(wx.ClientDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ClientDC, `en)}

${help.ComposeMethodHelp(wx.ClientDC, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ClientDC, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ClientDC, `ja)}

${help.ComposeMethodHelp(wx.ClientDC, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ClientDC(window as wx.Window) {block?}
Gurax_DeclareConstructorAlias(ClientDC_gurax, "ClientDC")
{
	Declare(VTYPE_wxClientDC, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ClientDC_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	auto pEntity_gurax = new wxClientDC(window);
	RefPtr<Value_wxClientDC> pValue_gurax(new Value_wxClientDC(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxClientDC
//------------------------------------------------------------------------------
VType_wxClientDC VTYPE_wxClientDC("ClientDC");

void VType_wxClientDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxWindowDC, Flag::Mutable, Gurax_CreateConstructor(ClientDC_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxClientDC
//------------------------------------------------------------------------------
VType& Value_wxClientDC::vtype = VTYPE_wxClientDC;

String Value_wxClientDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ClientDC");
}

Gurax_EndModuleScope(wx)
