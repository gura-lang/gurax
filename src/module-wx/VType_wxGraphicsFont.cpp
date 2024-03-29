﻿//==============================================================================
// VType_wxGraphicsFont.cpp
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

${help.ComposePropertyHelp(wx.GraphicsFont, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsFont, `en)}

${help.ComposeMethodHelp(wx.GraphicsFont, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GraphicsFont, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GraphicsFont, `ja)}

${help.ComposeMethodHelp(wx.GraphicsFont, `ja)}
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
// VType_wxGraphicsFont
//------------------------------------------------------------------------------
VType_wxGraphicsFont VTYPE_wxGraphicsFont("GraphicsFont");

void VType_wxGraphicsFont::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsFont
//------------------------------------------------------------------------------
VType& Value_wxGraphicsFont::vtype = VTYPE_wxGraphicsFont;

String Value_wxGraphicsFont::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsFont");
}

Gurax_EndModuleScope(wx)
