﻿//==============================================================================
// VType_wxCharBuffer.cpp
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

${help.ComposePropertyHelp(wx.CharBuffer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CharBuffer, `en)}

${help.ComposeMethodHelp(wx.CharBuffer, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.CharBuffer, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.CharBuffer, `ja)}

${help.ComposeMethodHelp(wx.CharBuffer, `ja)}
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
// VType_wxCharBuffer
//------------------------------------------------------------------------------
VType_wxCharBuffer VTYPE_wxCharBuffer("CharBuffer");

void VType_wxCharBuffer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCharBuffer
//------------------------------------------------------------------------------
VType& Value_wxCharBuffer::vtype = VTYPE_wxCharBuffer;

String Value_wxCharBuffer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CharBuffer");
}

Gurax_EndModuleScope(wx)
