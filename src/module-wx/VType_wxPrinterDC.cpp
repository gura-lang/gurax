//==============================================================================
// VType_wxPrinterDC.cpp
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

${help.ComposePropertyHelp(wx.PrinterDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PrinterDC, `en)}

${help.ComposeMethodHelp(wx.PrinterDC, `en)}
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
// VType_wxPrinterDC
//------------------------------------------------------------------------------
VType_wxPrinterDC VTYPE_wxPrinterDC("PrinterDC");

void VType_wxPrinterDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPrinterDC
//------------------------------------------------------------------------------
VType& Value_wxPrinterDC::vtype = VTYPE_wxPrinterDC;

String Value_wxPrinterDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PrinterDC");
}

Gurax_EndModuleScope(wx)
