﻿//==============================================================================
// VType_wxSpinCtrlDouble.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.SpinCtrlDouble, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SpinCtrlDouble, `en)}

${help.ComposeMethodHelp(wx.SpinCtrlDouble, `en)}
)""";

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
// VType_wxSpinCtrlDouble
//------------------------------------------------------------------------------
VType_wxSpinCtrlDouble VTYPE_wxSpinCtrlDouble("SpinCtrlDouble");

void VType_wxSpinCtrlDouble::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSpinCtrlDouble
//------------------------------------------------------------------------------
VType& Value_wxSpinCtrlDouble::vtype = VTYPE_wxSpinCtrlDouble;

String Value_wxSpinCtrlDouble::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SpinCtrlDouble");
}

//------------------------------------------------------------------------------
// Value_wxSpinCtrlDouble::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
