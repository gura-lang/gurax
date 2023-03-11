﻿//==============================================================================
// VType_wxRichTextAttr.cpp
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

${help.ComposePropertyHelp(wx.RichTextAttr, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextAttr, `en)}

${help.ComposeMethodHelp(wx.RichTextAttr, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RichTextAttr, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RichTextAttr, `ja)}

${help.ComposeMethodHelp(wx.RichTextAttr, `ja)}
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
// VType_wxRichTextAttr
//------------------------------------------------------------------------------
VType_wxRichTextAttr VTYPE_wxRichTextAttr("RichTextAttr");

void VType_wxRichTextAttr::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxTextAttr, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextAttr
//------------------------------------------------------------------------------
VType& Value_wxRichTextAttr::vtype = VTYPE_wxRichTextAttr;

String Value_wxRichTextAttr::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextAttr");
}

Gurax_EndModuleScope(wx)
