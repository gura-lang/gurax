//==============================================================================
// VType_wxDataViewTreeCtrl.cpp
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
// VType_wxDataViewTreeCtrl
//------------------------------------------------------------------------------
VType_wxDataViewTreeCtrl VTYPE_wxDataViewTreeCtrl("DataViewTreeCtrl");

void VType_wxDataViewTreeCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDataViewCtrl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewTreeCtrl
//------------------------------------------------------------------------------
VType& Value_wxDataViewTreeCtrl::vtype = VTYPE_wxDataViewTreeCtrl;

String Value_wxDataViewTreeCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewTreeCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDataViewTreeCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)