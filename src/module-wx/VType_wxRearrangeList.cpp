//==============================================================================
// VType_wxRearrangeList.cpp
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
// VType_wxRearrangeList
//------------------------------------------------------------------------------
VType_wxRearrangeList VTYPE_wxRearrangeList("RearrangeList");

void VType_wxRearrangeList::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCheckListBox, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxRearrangeList
//------------------------------------------------------------------------------
VType& Value_wxRearrangeList::vtype = VTYPE_wxRearrangeList;

String Value_wxRearrangeList::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RearrangeList");
}

//------------------------------------------------------------------------------
// Value_wxRearrangeList::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
