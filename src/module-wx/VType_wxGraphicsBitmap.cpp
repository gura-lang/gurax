﻿//==============================================================================
// VType_wxGraphicsBitmap.cpp
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

${help.ComposePropertyHelp(wx.GraphicsBitmap, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsBitmap, `en)}

${help.ComposeMethodHelp(wx.GraphicsBitmap, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GraphicsBitmap, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GraphicsBitmap, `ja)}

${help.ComposeMethodHelp(wx.GraphicsBitmap, `ja)}
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
// VType_wxGraphicsBitmap
//------------------------------------------------------------------------------
VType_wxGraphicsBitmap VTYPE_wxGraphicsBitmap("GraphicsBitmap");

void VType_wxGraphicsBitmap::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsBitmap
//------------------------------------------------------------------------------
VType& Value_wxGraphicsBitmap::vtype = VTYPE_wxGraphicsBitmap;

String Value_wxGraphicsBitmap::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsBitmap");
}

Gurax_EndModuleScope(wx)
