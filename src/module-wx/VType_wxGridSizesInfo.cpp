//==============================================================================
// VType_wxGridSizesInfo.cpp
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

${help.ComposePropertyHelp(wx.GridSizesInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GridSizesInfo, `en)}

${help.ComposeMethodHelp(wx.GridSizesInfo, `en)}
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
// VType_wxGridSizesInfo
//------------------------------------------------------------------------------
VType_wxGridSizesInfo VTYPE_wxGridSizesInfo("GridSizesInfo");

void VType_wxGridSizesInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridSizesInfo
//------------------------------------------------------------------------------
VType& Value_wxGridSizesInfo::vtype = VTYPE_wxGridSizesInfo;

String Value_wxGridSizesInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridSizesInfo");
}

Gurax_EndModuleScope(wx)
