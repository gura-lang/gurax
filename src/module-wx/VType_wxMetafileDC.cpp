//==============================================================================
// VType_wxMetafileDC.cpp
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

${help.ComposePropertyHelp(wxMetafileDC)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxMetafileDC)}

${help.ComposeMethodHelp(wxMetafileDC)}
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
// VType_wxMetafileDC
//------------------------------------------------------------------------------
VType_wxMetafileDC VTYPE_wxMetafileDC("MetafileDC");

void VType_wxMetafileDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMetafileDC
//------------------------------------------------------------------------------
VType& Value_wxMetafileDC::vtype = VTYPE_wxMetafileDC;

String Value_wxMetafileDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MetafileDC");
}

Gurax_EndModuleScope(wx)
