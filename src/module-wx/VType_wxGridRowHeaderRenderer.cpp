//==============================================================================
// VType_wxGridRowHeaderRenderer.cpp
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
// VType_wxGridRowHeaderRenderer
//------------------------------------------------------------------------------
VType_wxGridRowHeaderRenderer VTYPE_wxGridRowHeaderRenderer("GridRowHeaderRenderer");

void VType_wxGridRowHeaderRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridHeaderLabelsRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridRowHeaderRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridRowHeaderRenderer::vtype = VTYPE_wxGridRowHeaderRenderer;

String Value_wxGridRowHeaderRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridRowHeaderRenderer");
}

Gurax_EndModuleScope(wx)
