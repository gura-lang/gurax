﻿//==============================================================================
// VType_wxEditEnumProperty.cpp
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

${help.ComposePropertyHelp(wx.EditEnumProperty, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.EditEnumProperty, `en)}

${help.ComposeMethodHelp(wx.EditEnumProperty, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.EditEnumProperty, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.EditEnumProperty, `ja)}

${help.ComposeMethodHelp(wx.EditEnumProperty, `ja)}
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
// VType_wxEditEnumProperty
//------------------------------------------------------------------------------
VType_wxEditEnumProperty VTYPE_wxEditEnumProperty("EditEnumProperty");

void VType_wxEditEnumProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxEnumProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxEditEnumProperty
//------------------------------------------------------------------------------
VType& Value_wxEditEnumProperty::vtype = VTYPE_wxEditEnumProperty;

String Value_wxEditEnumProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EditEnumProperty");
}

Gurax_EndModuleScope(wx)
