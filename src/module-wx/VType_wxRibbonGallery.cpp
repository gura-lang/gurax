//==============================================================================
// VType_wxRibbonGallery.cpp
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
// VType_wxRibbonGallery
//------------------------------------------------------------------------------
VType_wxRibbonGallery VTYPE_wxRibbonGallery("RibbonGallery");

void VType_wxRibbonGallery::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRibbonGallery
//------------------------------------------------------------------------------
VType& Value_wxRibbonGallery::vtype = VTYPE_wxRibbonGallery;

String Value_wxRibbonGallery::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonGallery");
}

//------------------------------------------------------------------------------
// Value_wxRibbonGallery::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)