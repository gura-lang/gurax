//==============================================================================
// VType_wxGridColumnHeaderRenderer.cpp
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

${help.ComposePropertyHelp(wx.GridColumnHeaderRenderer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridColumnHeaderRenderer, `en)}

${help.ComposeMethodHelp(wx.GridColumnHeaderRenderer, `en)}
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
// VType_wxGridColumnHeaderRenderer
//------------------------------------------------------------------------------
VType_wxGridColumnHeaderRenderer VTYPE_wxGridColumnHeaderRenderer("GridColumnHeaderRenderer");

void VType_wxGridColumnHeaderRenderer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridHeaderLabelsRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridColumnHeaderRenderer
//------------------------------------------------------------------------------
VType& Value_wxGridColumnHeaderRenderer::vtype = VTYPE_wxGridColumnHeaderRenderer;

String Value_wxGridColumnHeaderRenderer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridColumnHeaderRenderer");
}

Gurax_EndModuleScope(wx)
