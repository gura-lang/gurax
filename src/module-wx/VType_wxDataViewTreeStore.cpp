﻿//==============================================================================
// VType_wxDataViewTreeStore.cpp
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

${help.ComposePropertyHelp(wx.DataViewTreeStore, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewTreeStore, `en)}

${help.ComposeMethodHelp(wx.DataViewTreeStore, `en)}
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
// VType_wxDataViewTreeStore
//------------------------------------------------------------------------------
VType_wxDataViewTreeStore VTYPE_wxDataViewTreeStore("DataViewTreeStore");

void VType_wxDataViewTreeStore::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDataViewModel, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewTreeStore
//------------------------------------------------------------------------------
VType& Value_wxDataViewTreeStore::vtype = VTYPE_wxDataViewTreeStore;

String Value_wxDataViewTreeStore::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewTreeStore");
}

Gurax_EndModuleScope(wx)
