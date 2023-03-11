﻿//==============================================================================
// VType_wxGraphicsGradientStops.cpp
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

${help.ComposePropertyHelp(wx.GraphicsGradientStops, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsGradientStops, `en)}

${help.ComposeMethodHelp(wx.GraphicsGradientStops, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GraphicsGradientStops, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GraphicsGradientStops, `ja)}

${help.ComposeMethodHelp(wx.GraphicsGradientStops, `ja)}
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
// VType_wxGraphicsGradientStops
//------------------------------------------------------------------------------
VType_wxGraphicsGradientStops VTYPE_wxGraphicsGradientStops("GraphicsGradientStops");

void VType_wxGraphicsGradientStops::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsGradientStops
//------------------------------------------------------------------------------
VType& Value_wxGraphicsGradientStops::vtype = VTYPE_wxGraphicsGradientStops;

String Value_wxGraphicsGradientStops::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsGradientStops");
}

Gurax_EndModuleScope(wx)
