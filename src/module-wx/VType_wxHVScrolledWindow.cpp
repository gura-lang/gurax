//==============================================================================
// VType_wxHVScrolledWindow.cpp
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
// VType_wxHVScrolledWindow
//------------------------------------------------------------------------------
VType_wxHVScrolledWindow VTYPE_wxHVScrolledWindow("HVScrolledWindow");

void VType_wxHVScrolledWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHVScrolledWindow
//------------------------------------------------------------------------------
VType& Value_wxHVScrolledWindow::vtype = VTYPE_wxHVScrolledWindow;

String Value_wxHVScrolledWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HVScrolledWindow");
}

//------------------------------------------------------------------------------
// Value_wxHVScrolledWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
