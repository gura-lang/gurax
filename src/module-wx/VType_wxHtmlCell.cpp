//==============================================================================
// VType_wxHtmlCell.cpp
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

${help.ComposePropertyHelp(wx.HtmlCell, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlCell, `en)}

${help.ComposeMethodHelp(wx.HtmlCell, `en)}
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
// VType_wxHtmlCell
//------------------------------------------------------------------------------
VType_wxHtmlCell VTYPE_wxHtmlCell("HtmlCell");

void VType_wxHtmlCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlCell
//------------------------------------------------------------------------------
VType& Value_wxHtmlCell::vtype = VTYPE_wxHtmlCell;

String Value_wxHtmlCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlCell");
}

Gurax_EndModuleScope(wx)
