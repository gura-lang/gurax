//==============================================================================
// VType_wxAccessible.cpp
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
// VType_wxAccessible
//------------------------------------------------------------------------------
VType_wxAccessible VTYPE_wxAccessible("Accessible");

void VType_wxAccessible::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAccessible
//------------------------------------------------------------------------------
VType& Value_wxAccessible::vtype = VTYPE_wxAccessible;

String Value_wxAccessible::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Accessible");
}

Gurax_EndModuleScope(wx)