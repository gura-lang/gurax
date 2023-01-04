﻿//==============================================================================
// VType_wxHtmlWordCell.cpp
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

${help.ComposePropertyHelp(wx.HtmlWordCell, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlWordCell, `en)}

${help.ComposeMethodHelp(wx.HtmlWordCell, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HtmlWordCell, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HtmlWordCell, `ja)}

${help.ComposeMethodHelp(wx.HtmlWordCell, `ja)}
)**";

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
// VType_wxHtmlWordCell
//------------------------------------------------------------------------------
VType_wxHtmlWordCell VTYPE_wxHtmlWordCell("HtmlWordCell");

void VType_wxHtmlWordCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxHtmlCell, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlWordCell
//------------------------------------------------------------------------------
VType& Value_wxHtmlWordCell::vtype = VTYPE_wxHtmlWordCell;

String Value_wxHtmlWordCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlWordCell");
}

Gurax_EndModuleScope(wx)
