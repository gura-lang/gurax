//==============================================================================
// VType_wxGraphicsGradientStops.cpp
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
// VType_wxGraphicsGradientStops
//------------------------------------------------------------------------------
VType_wxGraphicsGradientStops VTYPE_wxGraphicsGradientStops("GraphicsGradientStops");

void VType_wxGraphicsGradientStops::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsGradientStops
//------------------------------------------------------------------------------
VType& Value_wxGraphicsGradientStops::vtype = VTYPE_wxGraphicsGradientStops;

String Value_wxGraphicsGradientStops::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsGradientStops");
}

Gurax_EndModuleScope(wx)
