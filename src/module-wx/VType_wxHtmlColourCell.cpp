//==============================================================================
// VType_wxHtmlColourCell.cpp
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
// VType_wxHtmlColourCell
//------------------------------------------------------------------------------
VType_wxHtmlColourCell VTYPE_wxHtmlColourCell("HtmlColourCell");

void VType_wxHtmlColourCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHtmlCell, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlColourCell
//------------------------------------------------------------------------------
VType& Value_wxHtmlColourCell::vtype = VTYPE_wxHtmlColourCell;

String Value_wxHtmlColourCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlColourCell");
}

Gurax_EndModuleScope(wx)
