﻿//==============================================================================
// VType_wxGridHeaderLabelsRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridHeaderLabelsRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridHeaderLabelsRenderer, `en)}

${help.ComposeMethodHelp(wx.GridHeaderLabelsRenderer, `en)}
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
// VType_wxGridHeaderLabelsRenderer
//------------------------------------------------------------------------------
VType_wxGridHeaderLabelsRenderer VTYPE_wxGridHeaderLabelsRenderer("GridHeaderLabelsRenderer");

void VType_wxGridHeaderLabelsRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridHeaderLabelsRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridHeaderLabelsRenderer::vtype = VTYPE_wxGridHeaderLabelsRenderer;

String Value_wxGridHeaderLabelsRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridHeaderLabelsRenderer");
}

Gurax_EndModuleScope(wx)
