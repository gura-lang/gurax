﻿//==============================================================================
// VType_wxFileName.cpp
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

${help.ComposePropertyHelp(wx.FileName, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileName, `en)}

${help.ComposeMethodHelp(wx.FileName, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.FileName, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.FileName, `ja)}

${help.ComposeMethodHelp(wx.FileName, `ja)}
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
// VType_wxFileName
//------------------------------------------------------------------------------
VType_wxFileName VTYPE_wxFileName("FileName");

void VType_wxFileName::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFileName
//------------------------------------------------------------------------------
VType& Value_wxFileName::vtype = VTYPE_wxFileName;

String Value_wxFileName::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileName");
}

Gurax_EndModuleScope(wx)
