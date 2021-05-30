//==============================================================================
// VType_wxCommandEvent.cpp
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
// VType_wxCommandEvent
//------------------------------------------------------------------------------
VType_wxCommandEvent VTYPE_wxCommandEvent("CommandEvent");

void VType_wxCommandEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	// Assignment of property
}

//------------------------------------------------------------------------------
// Value_wxCommandEvent
//------------------------------------------------------------------------------
VType& Value_wxCommandEvent::vtype = VTYPE_wxCommandEvent;
EventValueFactoryDeriv<Value_wxCommandEvent> Value_wxCommandEvent::eventValueFactory;

String Value_wxCommandEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CommandEvent");
}

Gurax_EndModuleScope(wx)
