//==============================================================================
// VType_wxColourProperty.cpp
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
// VType_wxColourProperty
//------------------------------------------------------------------------------
VType_wxColourProperty VTYPE_wxColourProperty("ColourProperty");

void VType_wxColourProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSystemColourProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxColourProperty
//------------------------------------------------------------------------------
VType& Value_wxColourProperty::vtype = VTYPE_wxColourProperty;

String Value_wxColourProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourProperty");
}

Gurax_EndModuleScope(wx)