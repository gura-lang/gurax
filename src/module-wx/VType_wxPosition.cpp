//==============================================================================
// VType_wxPosition.cpp
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
// VType_wxPosition
//------------------------------------------------------------------------------
VType_wxPosition VTYPE_wxPosition("Position");

void VType_wxPosition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPosition
//------------------------------------------------------------------------------
VType& Value_wxPosition::vtype = VTYPE_wxPosition;

String Value_wxPosition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Position");
}

Gurax_EndModuleScope(wx)
