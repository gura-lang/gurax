//==============================================================================
// VType_wxHtmlWindow.cpp
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
// VType_wxHtmlWindow
//------------------------------------------------------------------------------
VType_wxHtmlWindow VTYPE_wxHtmlWindow("HtmlWindow");

void VType_wxHtmlWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxScrolledWindow, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlWindow
//------------------------------------------------------------------------------
VType& Value_wxHtmlWindow::vtype = VTYPE_wxHtmlWindow;

String Value_wxHtmlWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlWindow");
}

//------------------------------------------------------------------------------
// Value_wxHtmlWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
