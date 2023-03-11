﻿//==============================================================================
// VType_wxPalette.cpp
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

${help.ComposePropertyHelp(wx.Palette, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Palette, `en)}

${help.ComposeMethodHelp(wx.Palette, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Palette, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Palette, `ja)}

${help.ComposeMethodHelp(wx.Palette, `ja)}
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
// VType_wxPalette
//------------------------------------------------------------------------------
VType_wxPalette VTYPE_wxPalette("Palette");

void VType_wxPalette::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPalette
//------------------------------------------------------------------------------
VType& Value_wxPalette::vtype = VTYPE_wxPalette;

String Value_wxPalette::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Palette");
}

Gurax_EndModuleScope(wx)
