//==============================================================================
// VType_wxGraphicsMatrix.cpp
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
// VType_wxGraphicsMatrix
//------------------------------------------------------------------------------
VType_wxGraphicsMatrix VTYPE_wxGraphicsMatrix("GraphicsMatrix");

void VType_wxGraphicsMatrix::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsMatrix
//------------------------------------------------------------------------------
VType& Value_wxGraphicsMatrix::vtype = VTYPE_wxGraphicsMatrix;

String Value_wxGraphicsMatrix::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsMatrix");
}

Gurax_EndModuleScope(wx)
