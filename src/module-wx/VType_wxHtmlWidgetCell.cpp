//==============================================================================
// VType_wxHtmlWidgetCell.cpp
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

${help.ComposePropertyHelp(wx.HtmlWidgetCell, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.HtmlWidgetCell, `en)}

${help.ComposeMethodHelp(wx.HtmlWidgetCell, `en)}
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
// VType_wxHtmlWidgetCell
//------------------------------------------------------------------------------
VType_wxHtmlWidgetCell VTYPE_wxHtmlWidgetCell("HtmlWidgetCell");

void VType_wxHtmlWidgetCell::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHtmlCell, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHtmlWidgetCell
//------------------------------------------------------------------------------
VType& Value_wxHtmlWidgetCell::vtype = VTYPE_wxHtmlWidgetCell;

String Value_wxHtmlWidgetCell::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlWidgetCell");
}

Gurax_EndModuleScope(wx)
