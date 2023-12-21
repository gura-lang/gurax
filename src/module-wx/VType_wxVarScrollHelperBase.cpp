﻿//==============================================================================
// VType_wxVarScrollHelperBase.cpp
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

${help.ComposePropertyHelp(wx.VarScrollHelperBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.VarScrollHelperBase, `en)}

${help.ComposeMethodHelp(wx.VarScrollHelperBase, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.VarScrollHelperBase, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.VarScrollHelperBase, `ja)}

${help.ComposeMethodHelp(wx.VarScrollHelperBase, `ja)}
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
// VType_wxVarScrollHelperBase
//------------------------------------------------------------------------------
VType_wxVarScrollHelperBase VTYPE_wxVarScrollHelperBase("VarScrollHelperBase");

void VType_wxVarScrollHelperBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxVarScrollHelperBase
//------------------------------------------------------------------------------
VType& Value_wxVarScrollHelperBase::vtype = VTYPE_wxVarScrollHelperBase;

String Value_wxVarScrollHelperBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VarScrollHelperBase");
}

Gurax_EndModuleScope(wx)
