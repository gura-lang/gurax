//==============================================================================
// VType_wxTreeListCtrl.cpp
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

${help.ComposePropertyHelp(wxTreeListCtrl)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxTreeListCtrl)}

${help.ComposeMethodHelp(wxTreeListCtrl)}
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
// VType_wxTreeListCtrl
//------------------------------------------------------------------------------
VType_wxTreeListCtrl VTYPE_wxTreeListCtrl("TreeListCtrl");

void VType_wxTreeListCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxTreeListCtrl
//------------------------------------------------------------------------------
VType& Value_wxTreeListCtrl::vtype = VTYPE_wxTreeListCtrl;

String Value_wxTreeListCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TreeListCtrl");
}

//------------------------------------------------------------------------------
// Value_wxTreeListCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
