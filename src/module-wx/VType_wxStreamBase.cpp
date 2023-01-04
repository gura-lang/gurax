﻿//==============================================================================
// VType_wxStreamBase.cpp
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

${help.ComposePropertyHelp(wx.StreamBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StreamBase, `en)}

${help.ComposeMethodHelp(wx.StreamBase, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.StreamBase, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.StreamBase, `ja)}

${help.ComposeMethodHelp(wx.StreamBase, `ja)}
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
// VType_wxStreamBase
//------------------------------------------------------------------------------
VType_wxStreamBase VTYPE_wxStreamBase("StreamBase");

void VType_wxStreamBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxStreamBase
//------------------------------------------------------------------------------
VType& Value_wxStreamBase::vtype = VTYPE_wxStreamBase;

String Value_wxStreamBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StreamBase");
}

Gurax_EndModuleScope(wx)
