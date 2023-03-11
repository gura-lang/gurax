﻿//==============================================================================
// VType_wxHtmlHelpController.cpp
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

${help.ComposePropertyHelp(wx.HtmlHelpController, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlHelpController, `en)}

${help.ComposeMethodHelp(wx.HtmlHelpController, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HtmlHelpController, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HtmlHelpController, `ja)}

${help.ComposeMethodHelp(wx.HtmlHelpController, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlHelpController
//------------------------------------------------------------------------------
VType_wxHtmlHelpController VTYPE_wxHtmlHelpController("HtmlHelpController");

void VType_wxHtmlHelpController::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxHelpControllerBase, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlHelpController
//------------------------------------------------------------------------------
VType& Value_wxHtmlHelpController::vtype = VTYPE_wxHtmlHelpController;

String Value_wxHtmlHelpController::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlHelpController");
}

Gurax_EndModuleScope(wx)
