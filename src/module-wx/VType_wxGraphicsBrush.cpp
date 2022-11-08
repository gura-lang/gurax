//==============================================================================
// VType_wxGraphicsBrush.cpp
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

${help.ComposePropertyHelp(wx.GraphicsBrush, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsBrush, `en)}

${help.ComposeMethodHelp(wx.GraphicsBrush, `en)}
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
// VType_wxGraphicsBrush
//------------------------------------------------------------------------------
VType_wxGraphicsBrush VTYPE_wxGraphicsBrush("GraphicsBrush");

void VType_wxGraphicsBrush::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsBrush
//------------------------------------------------------------------------------
VType& Value_wxGraphicsBrush::vtype = VTYPE_wxGraphicsBrush;

String Value_wxGraphicsBrush::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsBrush");
}

Gurax_EndModuleScope(wx)
