﻿//==============================================================================
// VType_wxGraphicsPath.cpp
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

${help.ComposePropertyHelp(wx.GraphicsPath, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsPath, `en)}

${help.ComposeMethodHelp(wx.GraphicsPath, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GraphicsPath, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GraphicsPath, `ja)}

${help.ComposeMethodHelp(wx.GraphicsPath, `ja)}
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
// VType_wxGraphicsPath
//------------------------------------------------------------------------------
VType_wxGraphicsPath VTYPE_wxGraphicsPath("GraphicsPath");

void VType_wxGraphicsPath::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsPath
//------------------------------------------------------------------------------
VType& Value_wxGraphicsPath::vtype = VTYPE_wxGraphicsPath;

String Value_wxGraphicsPath::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsPath");
}

Gurax_EndModuleScope(wx)
