//==============================================================================
// VType_wxGraphicsFont.cpp
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

${help.ComposePropertyHelp(wxGraphicsFont)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxGraphicsFont)}

${help.ComposeMethodHelp(wxGraphicsFont)}
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
// VType_wxGraphicsFont
//------------------------------------------------------------------------------
VType_wxGraphicsFont VTYPE_wxGraphicsFont("GraphicsFont");

void VType_wxGraphicsFont::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsFont
//------------------------------------------------------------------------------
VType& Value_wxGraphicsFont::vtype = VTYPE_wxGraphicsFont;

String Value_wxGraphicsFont::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsFont");
}

Gurax_EndModuleScope(wx)
