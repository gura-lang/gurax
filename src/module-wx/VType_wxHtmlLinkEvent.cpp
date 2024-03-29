﻿//==============================================================================
// VType_wxHtmlLinkEvent.cpp
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

${help.ComposePropertyHelp(wx.HtmlLinkEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlLinkEvent, `en)}

${help.ComposeMethodHelp(wx.HtmlLinkEvent, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HtmlLinkEvent, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HtmlLinkEvent, `ja)}

${help.ComposeMethodHelp(wx.HtmlLinkEvent, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HtmlLinkEvent#GetLinkInfo() {block?}
Gurax_DeclareMethodAlias(wxHtmlLinkEvent, GetLinkInfo_gurax, "GetLinkInfo")
{
	Declare(VTYPE_wxHtmlLinkInfo, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHtmlLinkEvent, GetLinkInfo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlLinkInfo(pEntity_gurax->GetLinkInfo()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlLinkEvent
//------------------------------------------------------------------------------
VType_wxHtmlLinkEvent VTYPE_wxHtmlLinkEvent("HtmlLinkEvent");

void VType_wxHtmlLinkEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHtmlLinkEvent, GetLinkInfo_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHtmlLinkEvent
//------------------------------------------------------------------------------
VType& Value_wxHtmlLinkEvent::vtype = VTYPE_wxHtmlLinkEvent;
EventValueFactoryDeriv<Value_wxHtmlLinkEvent> Value_wxHtmlLinkEvent::eventValueFactory;

String Value_wxHtmlLinkEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlLinkEvent");
}

Gurax_EndModuleScope(wx)
