﻿//==============================================================================
// VType_wxPGPropertyFlags.cpp
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

${help.ComposePropertyHelp(wx.PGPropertyFlags, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PGPropertyFlags, `en)}

${help.ComposeMethodHelp(wx.PGPropertyFlags, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.PGPropertyFlags, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.PGPropertyFlags, `ja)}

${help.ComposeMethodHelp(wx.PGPropertyFlags, `ja)}
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
// VType_wxPGPropertyFlags
//------------------------------------------------------------------------------
VType_wxPGPropertyFlags VTYPE_wxPGPropertyFlags("PGPropertyFlags");

void VType_wxPGPropertyFlags::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGPropertyFlags
//------------------------------------------------------------------------------
VType& Value_wxPGPropertyFlags::vtype = VTYPE_wxPGPropertyFlags;

String Value_wxPGPropertyFlags::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGPropertyFlags");
}

Gurax_EndModuleScope(wx)
