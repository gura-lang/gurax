//==============================================================================
// VType_wxPGAttributeStorage.cpp
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
// VType_wxPGAttributeStorage
//------------------------------------------------------------------------------
VType_wxPGAttributeStorage VTYPE_wxPGAttributeStorage("PGAttributeStorage");

void VType_wxPGAttributeStorage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxPGAttributeStorage
//------------------------------------------------------------------------------
VType& Value_wxPGAttributeStorage::vtype = VTYPE_wxPGAttributeStorage;

String Value_wxPGAttributeStorage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PGAttributeStorage");
}

Gurax_EndModuleScope(wx)
