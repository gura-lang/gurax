//==============================================================================
// VType_wxAcceleratorTable.cpp
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
// VType_wxAcceleratorTable
//------------------------------------------------------------------------------
VType_wxAcceleratorTable VTYPE_wxAcceleratorTable("AcceleratorTable");

void VType_wxAcceleratorTable::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAcceleratorTable
//------------------------------------------------------------------------------
VType& Value_wxAcceleratorTable::vtype = VTYPE_wxAcceleratorTable;

String Value_wxAcceleratorTable::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AcceleratorTable");
}

Gurax_EndModuleScope(wx)