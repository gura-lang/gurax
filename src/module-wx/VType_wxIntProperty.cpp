﻿//==============================================================================
// VType_wxIntProperty.cpp
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

${help.ComposePropertyHelp(wx.IntProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.IntProperty, `en)}

${help.ComposeMethodHelp(wx.IntProperty, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.IntProperty, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.IntProperty, `ja)}

${help.ComposeMethodHelp(wx.IntProperty, `ja)}
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
// VType_wxIntProperty
//------------------------------------------------------------------------------
VType_wxIntProperty VTYPE_wxIntProperty("IntProperty");

void VType_wxIntProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxIntProperty
//------------------------------------------------------------------------------
VType& Value_wxIntProperty::vtype = VTYPE_wxIntProperty;

String Value_wxIntProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.IntProperty");
}

Gurax_EndModuleScope(wx)
