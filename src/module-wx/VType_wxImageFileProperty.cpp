//==============================================================================
// VType_wxImageFileProperty.cpp
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
// VType_wxImageFileProperty
//------------------------------------------------------------------------------
VType_wxImageFileProperty VTYPE_wxImageFileProperty("ImageFileProperty");

void VType_wxImageFileProperty::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFileProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxImageFileProperty
//------------------------------------------------------------------------------
VType& Value_wxImageFileProperty::vtype = VTYPE_wxImageFileProperty;

String Value_wxImageFileProperty::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ImageFileProperty");
}

Gurax_EndModuleScope(wx)
