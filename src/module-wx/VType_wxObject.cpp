//==============================================================================
// VType_wxObject.cpp
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

${help.ComposePropertyHelp(wx.Object, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Object, `en)}

${help.ComposeMethodHelp(wx.Object, `en)}
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
// VType_wxObject
//------------------------------------------------------------------------------
VType_wxObject VTYPE_wxObject("Object");

void VType_wxObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxObject
//------------------------------------------------------------------------------
VType& Value_wxObject::vtype = VTYPE_wxObject;

String Value_wxObject::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Object");
}

Gurax_EndModuleScope(wx)
