//==============================================================================
// VType_wxFloatPropert.cpp
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

${help.ComposePropertyHelp(wxFloatPropert)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxFloatPropert)}

${help.ComposeMethodHelp(wxFloatPropert)}
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
// VType_wxFloatPropert
//------------------------------------------------------------------------------
VType_wxFloatPropert VTYPE_wxFloatPropert("FloatPropert");

void VType_wxFloatPropert::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFloatPropert
//------------------------------------------------------------------------------
VType& Value_wxFloatPropert::vtype = VTYPE_wxFloatPropert;

String Value_wxFloatPropert::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FloatPropert");
}

Gurax_EndModuleScope(wx)
