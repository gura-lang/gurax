//==============================================================================
// VType_wxGridRowHeaderRendererDefault.cpp
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
// VType_wxGridRowHeaderRendererDefault
//------------------------------------------------------------------------------
VType_wxGridRowHeaderRendererDefault VTYPE_wxGridRowHeaderRendererDefault("GridRowHeaderRendererDefault");

void VType_wxGridRowHeaderRendererDefault::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridRowHeaderRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridRowHeaderRendererDefault
//------------------------------------------------------------------------------
VType& Value_wxGridRowHeaderRendererDefault::vtype = VTYPE_wxGridRowHeaderRendererDefault;

String Value_wxGridRowHeaderRendererDefault::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridRowHeaderRendererDefault");
}

Gurax_EndModuleScope(wx)