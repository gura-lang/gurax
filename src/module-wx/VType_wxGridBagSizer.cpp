//==============================================================================
// VType_wxGridBagSizer.cpp
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
// VType_wxGridBagSizer
//------------------------------------------------------------------------------
VType_wxGridBagSizer VTYPE_wxGridBagSizer("GridBagSizer");

void VType_wxGridBagSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxFlexGridSizer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridBagSizer
//------------------------------------------------------------------------------
VType& Value_wxGridBagSizer::vtype = VTYPE_wxGridBagSizer;

String Value_wxGridBagSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridBagSizer");
}

Gurax_EndModuleScope(wx)