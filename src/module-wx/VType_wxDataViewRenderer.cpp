//==============================================================================
// VType_wxDataViewRenderer.cpp
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
// VType_wxDataViewRenderer
//------------------------------------------------------------------------------
VType_wxDataViewRenderer VTYPE_wxDataViewRenderer("DataViewRenderer");

void VType_wxDataViewRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewRenderer
//------------------------------------------------------------------------------
VType& Value_wxDataViewRenderer::vtype = VTYPE_wxDataViewRenderer;

String Value_wxDataViewRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewRenderer");
}

Gurax_EndModuleScope(wx)