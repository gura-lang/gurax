//==============================================================================
// VType_wxFileCtrlEvent.cpp
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
// VType_wxFileCtrlEvent
//------------------------------------------------------------------------------
VType_wxFileCtrlEvent VTYPE_wxFileCtrlEvent("FileCtrlEvent");

void VType_wxFileCtrlEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxFileCtrlEvent
//------------------------------------------------------------------------------
VType& Value_wxFileCtrlEvent::vtype = VTYPE_wxFileCtrlEvent;
EventValueFactoryDeriv<Value_wxFileCtrlEvent> Value_wxFileCtrlEvent::eventValueFactory;

String Value_wxFileCtrlEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileCtrlEvent");
}

Gurax_EndModuleScope(wx)
