﻿//==============================================================================
// VType_wxSVGFileDC.cpp
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

${help.ComposePropertyHelp(wx.SVGFileDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SVGFileDC, `en)}

${help.ComposeMethodHelp(wx.SVGFileDC, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.SVGFileDC, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.SVGFileDC, `ja)}

${help.ComposeMethodHelp(wx.SVGFileDC, `ja)}
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
// VType_wxSVGFileDC
//------------------------------------------------------------------------------
VType_wxSVGFileDC VTYPE_wxSVGFileDC("SVGFileDC");

void VType_wxSVGFileDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSVGFileDC
//------------------------------------------------------------------------------
VType& Value_wxSVGFileDC::vtype = VTYPE_wxSVGFileDC;

String Value_wxSVGFileDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SVGFileDC");
}

Gurax_EndModuleScope(wx)
