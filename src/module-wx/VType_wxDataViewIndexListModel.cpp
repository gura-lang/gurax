//==============================================================================
// VType_wxDataViewIndexListModel.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
// VType_wxDataViewIndexListModel
//------------------------------------------------------------------------------
VType_wxDataViewIndexListModel VTYPE_wxDataViewIndexListModel("DataViewIndexListModel");

void VType_wxDataViewIndexListModel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDataViewListModel, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewIndexListModel
//------------------------------------------------------------------------------
VType& Value_wxDataViewIndexListModel::vtype = VTYPE_wxDataViewIndexListModel;

String Value_wxDataViewIndexListModel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewIndexListModel");
}

Gurax_EndModuleScope(wx)
