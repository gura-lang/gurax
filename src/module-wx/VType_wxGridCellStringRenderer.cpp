//==============================================================================
// VType_wxGridCellStringRenderer.cpp
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
// VType_wxGridCellStringRenderer
//------------------------------------------------------------------------------
VType_wxGridCellStringRenderer VTYPE_wxGridCellStringRenderer("GridCellStringRenderer");

void VType_wxGridCellStringRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCellRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellStringRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellStringRenderer::vtype = VTYPE_wxGridCellStringRenderer;

String Value_wxGridCellStringRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellStringRenderer");
}

Gurax_EndModuleScope(wx)