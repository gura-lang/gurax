//==============================================================================
// VType_wxGridCellRenderer.cpp
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
// VType_wxGridCellRenderer
//------------------------------------------------------------------------------
VType_wxGridCellRenderer VTYPE_wxGridCellRenderer("GridCellRenderer");

void VType_wxGridCellRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRefCounter, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridCellRenderer::vtype = VTYPE_wxGridCellRenderer;

String Value_wxGridCellRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellRenderer");
}

Gurax_EndModuleScope(wx)
