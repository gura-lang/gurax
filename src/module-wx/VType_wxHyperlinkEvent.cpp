﻿//==============================================================================
// VType_wxHyperlinkEvent.cpp
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

${help.ComposePropertyHelp(wx.HyperlinkEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HyperlinkEvent, `en)}

${help.ComposeMethodHelp(wx.HyperlinkEvent, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HyperlinkEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HyperlinkEvent, `ja)}

${help.ComposeMethodHelp(wx.HyperlinkEvent, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HyperlinkEvent#GetURL()
Gurax_DeclareMethodAlias(wxHyperlinkEvent, GetURL_gurax, "GetURL")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxHyperlinkEvent, GetURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetURL();
	//return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.HyperlinkEvent#SetURL(url as String)
Gurax_DeclareMethodAlias(wxHyperlinkEvent, SetURL_gurax, "SetURL")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxHyperlinkEvent, SetURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* url = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetURL(url);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHyperlinkEvent
//------------------------------------------------------------------------------
VType_wxHyperlinkEvent VTYPE_wxHyperlinkEvent("HyperlinkEvent");

void VType_wxHyperlinkEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHyperlinkEvent, GetURL_gurax));
	Assign(Gurax_CreateMethod(wxHyperlinkEvent, SetURL_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkEvent
//------------------------------------------------------------------------------
VType& Value_wxHyperlinkEvent::vtype = VTYPE_wxHyperlinkEvent;
EventValueFactoryDeriv<Value_wxHyperlinkEvent> Value_wxHyperlinkEvent::eventValueFactory;

String Value_wxHyperlinkEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HyperlinkEvent");
}

Gurax_EndModuleScope(wx)
