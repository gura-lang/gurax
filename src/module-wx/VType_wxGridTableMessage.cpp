//==============================================================================
// VType_wxGridTableMessage.cpp
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
// VType_wxGridTableMessage
//------------------------------------------------------------------------------
VType_wxGridTableMessage VTYPE_wxGridTableMessage("GridTableMessage");

void VType_wxGridTableMessage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridTableMessage
//------------------------------------------------------------------------------
VType& Value_wxGridTableMessage::vtype = VTYPE_wxGridTableMessage;

String Value_wxGridTableMessage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridTableMessage");
}

Gurax_EndModuleScope(wx)