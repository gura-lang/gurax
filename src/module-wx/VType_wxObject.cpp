//==============================================================================
// VType_wxObject.cpp
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
// VType_wxObject
//------------------------------------------------------------------------------
VType_wxObject VTYPE_wxObject("Object");

void VType_wxObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
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
