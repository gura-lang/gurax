﻿//==============================================================================
// VType_wxGridColumnHeaderRendererDefault.cpp
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

${help.ComposePropertyHelp(wx.GridColumnHeaderRendererDefault, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridColumnHeaderRendererDefault, `en)}

${help.ComposeMethodHelp(wx.GridColumnHeaderRendererDefault, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GridColumnHeaderRendererDefault, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GridColumnHeaderRendererDefault, `ja)}

${help.ComposeMethodHelp(wx.GridColumnHeaderRendererDefault, `ja)}
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
// VType_wxGridColumnHeaderRendererDefault
//------------------------------------------------------------------------------
VType_wxGridColumnHeaderRendererDefault VTYPE_wxGridColumnHeaderRendererDefault("GridColumnHeaderRendererDefault");

void VType_wxGridColumnHeaderRendererDefault::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGridColumnHeaderRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridColumnHeaderRendererDefault
//------------------------------------------------------------------------------
VType& Value_wxGridColumnHeaderRendererDefault::vtype = VTYPE_wxGridColumnHeaderRendererDefault;

String Value_wxGridColumnHeaderRendererDefault::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridColumnHeaderRendererDefault");
}

Gurax_EndModuleScope(wx)
