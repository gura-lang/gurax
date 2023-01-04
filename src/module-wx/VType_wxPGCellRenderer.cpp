﻿//==============================================================================
// VType_wxPGCellRenderer.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.PGCellRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGCellRenderer, `en)}

${help.ComposeMethodHelp(wx.PGCellRenderer, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.PGCellRenderer, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.PGCellRenderer, `ja)}

${help.ComposeMethodHelp(wx.PGCellRenderer, `ja)}
)**";

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
// VType_wxPGCellRenderer
//------------------------------------------------------------------------------
VType_wxPGCellRenderer VTYPE_wxPGCellRenderer("PGCellRenderer");

void VType_wxPGCellRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGCellRenderer
//------------------------------------------------------------------------------
VType& Value_wxPGCellRenderer::vtype = VTYPE_wxPGCellRenderer;

String Value_wxPGCellRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGCellRenderer");
}

Gurax_EndModuleScope(wx)
