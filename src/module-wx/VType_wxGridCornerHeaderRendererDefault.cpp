//==============================================================================
// VType_wxGridCornerHeaderRendererDefault.cpp
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

${help.ComposePropertyHelp(wxGridCornerHeaderRendererDefault, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxGridCornerHeaderRendererDefault, `en)}

${help.ComposeMethodHelp(wxGridCornerHeaderRendererDefault, `en)}
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
// VType_wxGridCornerHeaderRendererDefault
//------------------------------------------------------------------------------
VType_wxGridCornerHeaderRendererDefault VTYPE_wxGridCornerHeaderRendererDefault("GridCornerHeaderRendererDefault");

void VType_wxGridCornerHeaderRendererDefault::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridCornerHeaderRenderer, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridCornerHeaderRendererDefault
//------------------------------------------------------------------------------
VType& Value_wxGridCornerHeaderRendererDefault::vtype = VTYPE_wxGridCornerHeaderRendererDefault;

String Value_wxGridCornerHeaderRendererDefault::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridCornerHeaderRendererDefault");
}

Gurax_EndModuleScope(wx)
