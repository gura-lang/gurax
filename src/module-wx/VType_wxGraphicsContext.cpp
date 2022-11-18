﻿//==============================================================================
// VType_wxGraphicsContext.cpp
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

${help.ComposePropertyHelp(wx.GraphicsContext, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GraphicsContext, `en)}

${help.ComposeMethodHelp(wx.GraphicsContext, `en)}
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
// VType_wxGraphicsContext
//------------------------------------------------------------------------------
VType_wxGraphicsContext VTYPE_wxGraphicsContext("GraphicsContext");

void VType_wxGraphicsContext::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGraphicsObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGraphicsContext
//------------------------------------------------------------------------------
VType& Value_wxGraphicsContext::vtype = VTYPE_wxGraphicsContext;

String Value_wxGraphicsContext::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GraphicsContext");
}

Gurax_EndModuleScope(wx)
