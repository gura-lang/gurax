﻿//==============================================================================
// VType_wxDataViewTreeCtrl.cpp
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

${help.ComposePropertyHelp(wx.DataViewTreeCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewTreeCtrl, `en)}

${help.ComposeMethodHelp(wx.DataViewTreeCtrl, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.DataViewTreeCtrl, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.DataViewTreeCtrl, `ja)}

${help.ComposeMethodHelp(wx.DataViewTreeCtrl, `ja)}
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
// VType_wxDataViewTreeCtrl
//------------------------------------------------------------------------------
VType_wxDataViewTreeCtrl VTYPE_wxDataViewTreeCtrl("DataViewTreeCtrl");

void VType_wxDataViewTreeCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDataViewCtrl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewTreeCtrl
//------------------------------------------------------------------------------
VType& Value_wxDataViewTreeCtrl::vtype = VTYPE_wxDataViewTreeCtrl;

String Value_wxDataViewTreeCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewTreeCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDataViewTreeCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
