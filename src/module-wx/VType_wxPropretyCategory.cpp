//==============================================================================
// VType_wxPropretyCategory.cpp
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
// VType_wxPropretyCategory
//------------------------------------------------------------------------------
VType_wxPropretyCategory VTYPE_wxPropretyCategory("PropretyCategory");

void VType_wxPropretyCategory::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPGProperty, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPropretyCategory
//------------------------------------------------------------------------------
VType& Value_wxPropretyCategory::vtype = VTYPE_wxPropretyCategory;

String Value_wxPropretyCategory::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PropretyCategory");
}

Gurax_EndModuleScope(wx)
