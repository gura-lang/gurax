//==============================================================================
// VType_wxDataViewListCtrl.cpp
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

${help.ComposePropertyHelp(wxDataViewListCtrl)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDataViewListCtrl)}

${help.ComposeMethodHelp(wxDataViewListCtrl)}
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
// VType_wxDataViewListCtrl
//------------------------------------------------------------------------------
VType_wxDataViewListCtrl VTYPE_wxDataViewListCtrl("DataViewListCtrl");

void VType_wxDataViewListCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDataViewCtrl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewListCtrl
//------------------------------------------------------------------------------
VType& Value_wxDataViewListCtrl::vtype = VTYPE_wxDataViewListCtrl;

String Value_wxDataViewListCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewListCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDataViewListCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
