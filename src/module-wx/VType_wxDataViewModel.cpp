﻿//==============================================================================
// VType_wxDataViewModel.cpp
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

${help.ComposePropertyHelp(wx.DataViewModel, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DataViewModel, `en)}

${help.ComposeMethodHelp(wx.DataViewModel, `en)}
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
// VType_wxDataViewModel
//------------------------------------------------------------------------------
VType_wxDataViewModel VTYPE_wxDataViewModel("DataViewModel");

void VType_wxDataViewModel::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxDataViewModel
//------------------------------------------------------------------------------
VType& Value_wxDataViewModel::vtype = VTYPE_wxDataViewModel;

String Value_wxDataViewModel::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DataViewModel");
}

Gurax_EndModuleScope(wx)
