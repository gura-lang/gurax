//==============================================================================
// VType_wxAuiToolBarItem.cpp
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

${help.ComposePropertyHelp(wx.AuiToolBarItem, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AuiToolBarItem, `en)}

${help.ComposeMethodHelp(wx.AuiToolBarItem, `en)}
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
// VType_wxAuiToolBarItem
//------------------------------------------------------------------------------
VType_wxAuiToolBarItem VTYPE_wxAuiToolBarItem("AuiToolBarItem");

void VType_wxAuiToolBarItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiToolBarItem
//------------------------------------------------------------------------------
VType& Value_wxAuiToolBarItem::vtype = VTYPE_wxAuiToolBarItem;

String Value_wxAuiToolBarItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiToolBarItem");
}

Gurax_EndModuleScope(wx)
