//==============================================================================
// VType_wxCursor.cpp
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
// VType_wxCursor
//------------------------------------------------------------------------------
VType_wxCursor VTYPE_wxCursor("Cursor");

void VType_wxCursor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGDIObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCursor
//------------------------------------------------------------------------------
VType& Value_wxCursor::vtype = VTYPE_wxCursor;

String Value_wxCursor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Cursor");
}

Gurax_EndModuleScope(wx)
