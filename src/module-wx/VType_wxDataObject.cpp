//==============================================================================
// VType_wxDataObject.cpp
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

${help.ComposePropertyHelp(wx.DataObject, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataObject, `en)}

${help.ComposeMethodHelp(wx.DataObject, `en)}
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
// VType_wxDataObject
//------------------------------------------------------------------------------
VType_wxDataObject VTYPE_wxDataObject("DataObject");

void VType_wxDataObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataObject
//------------------------------------------------------------------------------
VType& Value_wxDataObject::vtype = VTYPE_wxDataObject;

String Value_wxDataObject::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataObject");
}

Gurax_EndModuleScope(wx)
