//==============================================================================
// VType_wxDataViewListStore.cpp
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

${help.ComposePropertyHelp(wx.DataViewListStore, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewListStore, `en)}

${help.ComposeMethodHelp(wx.DataViewListStore, `en)}
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
// VType_wxDataViewListStore
//------------------------------------------------------------------------------
VType_wxDataViewListStore VTYPE_wxDataViewListStore("DataViewListStore");

void VType_wxDataViewListStore::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDataViewIndexListModel, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewListStore
//------------------------------------------------------------------------------
VType& Value_wxDataViewListStore::vtype = VTYPE_wxDataViewListStore;

String Value_wxDataViewListStore::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewListStore");
}

Gurax_EndModuleScope(wx)
