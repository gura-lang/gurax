//==============================================================================
// VType_wxMemoryDC.cpp
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

${help.ComposePropertyHelp(wxMemoryDC, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxMemoryDC, `en)}

${help.ComposeMethodHelp(wxMemoryDC, `en)}
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
// VType_wxMemoryDC
//------------------------------------------------------------------------------
VType_wxMemoryDC VTYPE_wxMemoryDC("MemoryDC");

void VType_wxMemoryDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMemoryDC
//------------------------------------------------------------------------------
VType& Value_wxMemoryDC::vtype = VTYPE_wxMemoryDC;

String Value_wxMemoryDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MemoryDC");
}

Gurax_EndModuleScope(wx)
