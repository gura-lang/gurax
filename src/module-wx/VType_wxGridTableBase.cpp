//==============================================================================
// VType_wxGridTableBase.cpp
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
// VType_wxGridTableBase
//------------------------------------------------------------------------------
VType_wxGridTableBase VTYPE_wxGridTableBase("GridTableBase");

void VType_wxGridTableBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxGridTableBase
//------------------------------------------------------------------------------
VType& Value_wxGridTableBase::vtype = VTYPE_wxGridTableBase;

String Value_wxGridTableBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridTableBase");
}

Gurax_EndModuleScope(wx)
