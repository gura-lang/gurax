﻿//==============================================================================
// VType_wxGraphicsMatrix.cpp
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

${help.ComposePropertyHelp(wx.GraphicsMatrix, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsMatrix, `en)}

${help.ComposeMethodHelp(wx.GraphicsMatrix, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GraphicsMatrix, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GraphicsMatrix, `ja)}

${help.ComposeMethodHelp(wx.GraphicsMatrix, `ja)}
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
// VType_wxGraphicsMatrix
//------------------------------------------------------------------------------
VType_wxGraphicsMatrix VTYPE_wxGraphicsMatrix("GraphicsMatrix");

void VType_wxGraphicsMatrix::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsMatrix
//------------------------------------------------------------------------------
VType& Value_wxGraphicsMatrix::vtype = VTYPE_wxGraphicsMatrix;

String Value_wxGraphicsMatrix::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsMatrix");
}

Gurax_EndModuleScope(wx)
