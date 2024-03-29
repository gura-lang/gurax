﻿//==============================================================================
// VType_wxRichTextRange.cpp
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

${help.ComposePropertyHelp(wx.RichTextRange, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RichTextRange, `en)}

${help.ComposeMethodHelp(wx.RichTextRange, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RichTextRange, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RichTextRange, `ja)}

${help.ComposeMethodHelp(wx.RichTextRange, `ja)}
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
// VType_wxRichTextRange
//------------------------------------------------------------------------------
VType_wxRichTextRange VTYPE_wxRichTextRange("RichTextRange");

void VType_wxRichTextRange::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRichTextRange
//------------------------------------------------------------------------------
VType& Value_wxRichTextRange::vtype = VTYPE_wxRichTextRange;

String Value_wxRichTextRange::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RichTextRange");
}

Gurax_EndModuleScope(wx)
