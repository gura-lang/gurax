﻿//==============================================================================
// VType_wxFloatProperty.cpp
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

${help.ComposePropertyHelp(wx.FloatProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FloatProperty, `en)}

${help.ComposeMethodHelp(wx.FloatProperty, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FloatProperty, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FloatProperty, `ja)}

${help.ComposeMethodHelp(wx.FloatProperty, `ja)}
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
// VType_wxFloatProperty
//------------------------------------------------------------------------------
VType_wxFloatProperty VTYPE_wxFloatProperty("FloatProperty");

void VType_wxFloatProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFloatProperty
//------------------------------------------------------------------------------
VType& Value_wxFloatProperty::vtype = VTYPE_wxFloatProperty;

String Value_wxFloatProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FloatProperty");
}

Gurax_EndModuleScope(wx)
