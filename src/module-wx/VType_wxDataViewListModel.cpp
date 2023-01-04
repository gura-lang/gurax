﻿//==============================================================================
// VType_wxDataViewListModel.cpp
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

${help.ComposePropertyHelp(wx.DataViewListModel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewListModel, `en)}

${help.ComposeMethodHelp(wx.DataViewListModel, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.DataViewListModel, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.DataViewListModel, `ja)}

${help.ComposeMethodHelp(wx.DataViewListModel, `ja)}
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
// VType_wxDataViewListModel
//------------------------------------------------------------------------------
VType_wxDataViewListModel VTYPE_wxDataViewListModel("DataViewListModel");

void VType_wxDataViewListModel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxDataViewModel, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewListModel
//------------------------------------------------------------------------------
VType& Value_wxDataViewListModel::vtype = VTYPE_wxDataViewListModel;

String Value_wxDataViewListModel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewListModel");
}

Gurax_EndModuleScope(wx)
