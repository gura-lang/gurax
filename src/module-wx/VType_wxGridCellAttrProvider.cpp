//==============================================================================
// VType_wxGridCellAttrProvider.cpp
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
// VType_wxGridCellAttrProvider
//------------------------------------------------------------------------------
VType_wxGridCellAttrProvider VTYPE_wxGridCellAttrProvider("GridCellAttrProvider");

void VType_wxGridCellAttrProvider::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxClientDataContainer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCellAttrProvider
//------------------------------------------------------------------------------
VType& Value_wxGridCellAttrProvider::vtype = VTYPE_wxGridCellAttrProvider;

String Value_wxGridCellAttrProvider::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCellAttrProvider");
}

Gurax_EndModuleScope(wx)
