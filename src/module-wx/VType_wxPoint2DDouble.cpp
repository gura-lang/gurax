﻿//==============================================================================
// VType_wxPoint2DDouble.cpp
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

${help.ComposePropertyHelp(wx.Point2DDouble, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Point2DDouble, `en)}

${help.ComposeMethodHelp(wx.Point2DDouble, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Point2DDouble, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Point2DDouble, `ja)}

${help.ComposeMethodHelp(wx.Point2DDouble, `ja)}
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
// VType_wxPoint2DDouble
//------------------------------------------------------------------------------
VType_wxPoint2DDouble VTYPE_wxPoint2DDouble("Point2DDouble");

void VType_wxPoint2DDouble::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPoint2DDouble
//------------------------------------------------------------------------------
VType& Value_wxPoint2DDouble::vtype = VTYPE_wxPoint2DDouble;

String Value_wxPoint2DDouble::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Point2DDouble");
}

Gurax_EndModuleScope(wx)
