﻿//==============================================================================
// VType_wxMiniFrame.cpp
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

${help.ComposePropertyHelp(wx.MiniFrame, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MiniFrame, `en)}

${help.ComposeMethodHelp(wx.MiniFrame, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.MiniFrame, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.MiniFrame, `ja)}

${help.ComposeMethodHelp(wx.MiniFrame, `ja)}
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
// VType_wxMiniFrame
//------------------------------------------------------------------------------
VType_wxMiniFrame VTYPE_wxMiniFrame("MiniFrame");

void VType_wxMiniFrame::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxFrame, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMiniFrame
//------------------------------------------------------------------------------
VType& Value_wxMiniFrame::vtype = VTYPE_wxMiniFrame;

String Value_wxMiniFrame::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MiniFrame");
}

//------------------------------------------------------------------------------
// Value_wxMiniFrame::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
