//==============================================================================
// VType_wxGDIImageHandler.cpp
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
// VType_wxGDIImageHandler
//------------------------------------------------------------------------------
VType_wxGDIImageHandler VTYPE_wxGDIImageHandler("GDIImageHandler");

void VType_wxGDIImageHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGDIImageHandler
//------------------------------------------------------------------------------
VType& Value_wxGDIImageHandler::vtype = VTYPE_wxGDIImageHandler;

String Value_wxGDIImageHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GDIImageHandler");
}

Gurax_EndModuleScope(wx)
