//==============================================================================
// VType_wxPGCellRenderer.cpp
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
// VType_wxPGCellRenderer
//------------------------------------------------------------------------------
VType_wxPGCellRenderer VTYPE_wxPGCellRenderer("PGCellRenderer");

void VType_wxPGCellRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGCellRenderer
//------------------------------------------------------------------------------
VType& Value_wxPGCellRenderer::vtype = VTYPE_wxPGCellRenderer;

String Value_wxPGCellRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGCellRenderer");
}

Gurax_EndModuleScope(wx)
