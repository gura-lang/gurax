﻿//==============================================================================
// VType_wxAuiDefaultToolBarArt.cpp
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

${help.ComposePropertyHelp(wx.AuiDefaultToolBarArt, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AuiDefaultToolBarArt, `en)}

${help.ComposeMethodHelp(wx.AuiDefaultToolBarArt, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.AuiDefaultToolBarArt, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.AuiDefaultToolBarArt, `ja)}

${help.ComposeMethodHelp(wx.AuiDefaultToolBarArt, `ja)}
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
// VType_wxAuiDefaultToolBarArt
//------------------------------------------------------------------------------
VType_wxAuiDefaultToolBarArt VTYPE_wxAuiDefaultToolBarArt("AuiDefaultToolBarArt");

void VType_wxAuiDefaultToolBarArt::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxAuiToolBarArt, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiDefaultToolBarArt
//------------------------------------------------------------------------------
VType& Value_wxAuiDefaultToolBarArt::vtype = VTYPE_wxAuiDefaultToolBarArt;

String Value_wxAuiDefaultToolBarArt::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiDefaultToolBarArt");
}

Gurax_EndModuleScope(wx)
