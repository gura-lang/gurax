﻿//==============================================================================
// VType_wxHeaderColumn.cpp
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

${help.ComposePropertyHelp(wx.HeaderColumn, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HeaderColumn, `en)}

${help.ComposeMethodHelp(wx.HeaderColumn, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.HeaderColumn, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.HeaderColumn, `ja)}

${help.ComposeMethodHelp(wx.HeaderColumn, `ja)}
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
// VType_wxHeaderColumn
//------------------------------------------------------------------------------
VType_wxHeaderColumn VTYPE_wxHeaderColumn("HeaderColumn");

void VType_wxHeaderColumn::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHeaderColumn
//------------------------------------------------------------------------------
VType& Value_wxHeaderColumn::vtype = VTYPE_wxHeaderColumn;

String Value_wxHeaderColumn::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HeaderColumn");
}

Gurax_EndModuleScope(wx)
