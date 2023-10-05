﻿//==============================================================================
// VType_wxHtmlLinkInfo.cpp
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

${help.ComposePropertyHelp(wx.HtmlLinkInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlLinkInfo, `en)}

${help.ComposeMethodHelp(wx.HtmlLinkInfo, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HtmlLinkInfo, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HtmlLinkInfo, `ja)}

${help.ComposeMethodHelp(wx.HtmlLinkInfo, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.HtmlLinkInfo(href as String, target? as String) {block?}
Gurax_DeclareConstructorAlias(HtmlLinkInfo_gurax, "HtmlLinkInfo")
{
	Declare(VTYPE_wxHtmlLinkInfo, Flag::None);
	DeclareArg("href", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("target", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(HtmlLinkInfo_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* href = args_gurax.PickString();
	const char* target = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	auto pEntity_gurax = new wxHtmlLinkInfo(href, target);
	RefPtr<Value_wxHtmlLinkInfo> pValue_gurax(new Value_wxHtmlLinkInfo(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HtmlLinkInfo#GetHref()
Gurax_DeclareMethodAlias(wxHtmlLinkInfo, GetHref_gurax, "GetHref")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxHtmlLinkInfo, GetHref_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetHref();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.HtmlLinkInfo#GetHtmlCell() {block?}
Gurax_DeclareMethodAlias(wxHtmlLinkInfo, GetHtmlCell_gurax, "GetHtmlCell")
{
	Declare(VTYPE_wxHtmlCell, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxHtmlLinkInfo, GetHtmlCell_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlCell(
		*pEntity_gurax->GetHtmlCell()));
}

// wx.HtmlLinkInfo#GetTarget()
Gurax_DeclareMethodAlias(wxHtmlLinkInfo, GetTarget_gurax, "GetTarget")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxHtmlLinkInfo, GetTarget_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetTarget();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlLinkInfo
//------------------------------------------------------------------------------
VType_wxHtmlLinkInfo VTYPE_wxHtmlLinkInfo("HtmlLinkInfo");

void VType_wxHtmlLinkInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(HtmlLinkInfo_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHtmlLinkInfo, GetHref_gurax));
	Assign(Gurax_CreateMethod(wxHtmlLinkInfo, GetHtmlCell_gurax));
	Assign(Gurax_CreateMethod(wxHtmlLinkInfo, GetTarget_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHtmlLinkInfo
//------------------------------------------------------------------------------
VType& Value_wxHtmlLinkInfo::vtype = VTYPE_wxHtmlLinkInfo;

String Value_wxHtmlLinkInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlLinkInfo");
}

Gurax_EndModuleScope(wx)
