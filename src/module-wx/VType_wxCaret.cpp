//==============================================================================
// VType_wxCaret.cpp
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
// VType_wxCaret
//------------------------------------------------------------------------------
VType_wxCaret VTYPE_wxCaret("Caret");

void VType_wxCaret::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxCaret
//------------------------------------------------------------------------------
VType& Value_wxCaret::vtype = VTYPE_wxCaret;

String Value_wxCaret::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Caret");
}

Gurax_EndModuleScope(wx)
