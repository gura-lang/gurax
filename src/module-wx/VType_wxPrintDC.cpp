//==============================================================================
// VType_wxPrintDC.cpp
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

${help.ComposePropertyHelp(wxPrintDC)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxPrintDC)}

${help.ComposeMethodHelp(wxPrintDC)}
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
// VType_wxPrintDC
//------------------------------------------------------------------------------
VType_wxPrintDC VTYPE_wxPrintDC("PrintDC");

void VType_wxPrintDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPrintDC
//------------------------------------------------------------------------------
VType& Value_wxPrintDC::vtype = VTYPE_wxPrintDC;

String Value_wxPrintDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PrintDC");
}

Gurax_EndModuleScope(wx)
