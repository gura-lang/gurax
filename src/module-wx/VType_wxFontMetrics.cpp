//==============================================================================
// VType_wxFontMetrics.cpp
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
// VType_wxFontMetrics
//------------------------------------------------------------------------------
VType_wxFontMetrics VTYPE_wxFontMetrics("FontMetrics");

void VType_wxFontMetrics::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFontMetrics
//------------------------------------------------------------------------------
VType& Value_wxFontMetrics::vtype = VTYPE_wxFontMetrics;

String Value_wxFontMetrics::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontMetrics");
}

Gurax_EndModuleScope(wx)
