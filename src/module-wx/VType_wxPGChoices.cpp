//==============================================================================
// VType_wxPGChoices.cpp
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
// VType_wxPGChoices
//------------------------------------------------------------------------------
VType_wxPGChoices VTYPE_wxPGChoices("PGChoices");

void VType_wxPGChoices::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGChoices
//------------------------------------------------------------------------------
VType& Value_wxPGChoices::vtype = VTYPE_wxPGChoices;

String Value_wxPGChoices::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGChoices");
}

Gurax_EndModuleScope(wx)