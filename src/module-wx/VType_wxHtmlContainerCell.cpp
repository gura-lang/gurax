//==============================================================================
// VType_wxHtmlContainerCell.cpp
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
// VType_wxHtmlContainerCell
//------------------------------------------------------------------------------
VType_wxHtmlContainerCell VTYPE_wxHtmlContainerCell("HtmlContainerCell");

void VType_wxHtmlContainerCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHtmlCell, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlContainerCell
//------------------------------------------------------------------------------
VType& Value_wxHtmlContainerCell::vtype = VTYPE_wxHtmlContainerCell;

String Value_wxHtmlContainerCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlContainerCell");
}

Gurax_EndModuleScope(wx)
