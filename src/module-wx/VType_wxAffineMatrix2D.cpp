//==============================================================================
// VType_wxAffineMatrix2D.cpp
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
// VType_wxAffineMatrix2D
//------------------------------------------------------------------------------
VType_wxAffineMatrix2D VTYPE_wxAffineMatrix2D("AffineMatrix2D");

void VType_wxAffineMatrix2D::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAffineMatrix2D
//------------------------------------------------------------------------------
VType& Value_wxAffineMatrix2D::vtype = VTYPE_wxAffineMatrix2D;

String Value_wxAffineMatrix2D::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AffineMatrix2D");
}

Gurax_EndModuleScope(wx)
