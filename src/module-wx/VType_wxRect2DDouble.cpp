//==============================================================================
// VType_wxRect2DDouble.cpp
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

${help.ComposePropertyHelp(wxRect2DDouble)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRect2DDouble)}

${help.ComposeMethodHelp(wxRect2DDouble)}
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
// VType_wxRect2DDouble
//------------------------------------------------------------------------------
VType_wxRect2DDouble VTYPE_wxRect2DDouble("Rect2DDouble");

void VType_wxRect2DDouble::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRect2DDouble
//------------------------------------------------------------------------------
VType& Value_wxRect2DDouble::vtype = VTYPE_wxRect2DDouble;

String Value_wxRect2DDouble::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Rect2DDouble");
}

Gurax_EndModuleScope(wx)
