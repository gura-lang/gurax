//==============================================================================
// VType_wxPrintPreview.cpp
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

${help.ComposePropertyHelp(wx.PrintPreview, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PrintPreview, `en)}

${help.ComposeMethodHelp(wx.PrintPreview, `en)}
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
// VType_wxPrintPreview
//------------------------------------------------------------------------------
VType_wxPrintPreview VTYPE_wxPrintPreview("PrintPreview");

void VType_wxPrintPreview::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPrintPreview
//------------------------------------------------------------------------------
VType& Value_wxPrintPreview::vtype = VTYPE_wxPrintPreview;

String Value_wxPrintPreview::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PrintPreview");
}

Gurax_EndModuleScope(wx)
