//==============================================================================
// VType_wxGridCornerHeaderRenderer.cpp
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
// VType_wxGridCornerHeaderRenderer
//------------------------------------------------------------------------------
VType_wxGridCornerHeaderRenderer VTYPE_wxGridCornerHeaderRenderer("GridCornerHeaderRenderer");

void VType_wxGridCornerHeaderRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCornerHeaderRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCornerHeaderRenderer::vtype = VTYPE_wxGridCornerHeaderRenderer;

String Value_wxGridCornerHeaderRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCornerHeaderRenderer");
}

Gurax_EndModuleScope(wx)
