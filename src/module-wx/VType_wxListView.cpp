//==============================================================================
// VType_wxListView.cpp
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

${help.ComposePropertyHelp(wx.ListView, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ListView, `en)}

${help.ComposeMethodHelp(wx.ListView, `en)}
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
// VType_wxListView
//------------------------------------------------------------------------------
VType_wxListView VTYPE_wxListView("ListView");

void VType_wxListView::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxListCtrl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxListView
//------------------------------------------------------------------------------
VType& Value_wxListView::vtype = VTYPE_wxListView;

String Value_wxListView::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ListView");
}

//------------------------------------------------------------------------------
// Value_wxListView::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
