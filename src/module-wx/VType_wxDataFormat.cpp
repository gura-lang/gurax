﻿//==============================================================================
// VType_wxDataFormat.cpp
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

${help.ComposePropertyHelp(wx.DataFormat, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataFormat, `en)}

${help.ComposeMethodHelp(wx.DataFormat, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.DataFormat, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.DataFormat, `ja)}

${help.ComposeMethodHelp(wx.DataFormat, `ja)}
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
// VType_wxDataFormat
//------------------------------------------------------------------------------
VType_wxDataFormat VTYPE_wxDataFormat("DataFormat");

void VType_wxDataFormat::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataFormat
//------------------------------------------------------------------------------
VType& Value_wxDataFormat::vtype = VTYPE_wxDataFormat;

String Value_wxDataFormat::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataFormat");
}

Gurax_EndModuleScope(wx)
