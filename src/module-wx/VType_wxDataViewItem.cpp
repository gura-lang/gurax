//==============================================================================
// VType_wxDataViewItem.cpp
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

${help.ComposePropertyHelp(wxDataViewItem)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDataViewItem)}

${help.ComposeMethodHelp(wxDataViewItem)}
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
// VType_wxDataViewItem
//------------------------------------------------------------------------------
VType_wxDataViewItem VTYPE_wxDataViewItem("DataViewItem");

void VType_wxDataViewItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewItem
//------------------------------------------------------------------------------
VType& Value_wxDataViewItem::vtype = VTYPE_wxDataViewItem;

String Value_wxDataViewItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewItem");
}

Gurax_EndModuleScope(wx)
