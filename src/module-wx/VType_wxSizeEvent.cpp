//==============================================================================
// VType_wxSizeEvent.cpp
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
// VType_wxSizeEvent
//------------------------------------------------------------------------------
VType_wxSizeEvent VTYPE_wxSizeEvent("SizeEvent");

void VType_wxSizeEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSizeEvent
//------------------------------------------------------------------------------
VType& Value_wxSizeEvent::vtype = VTYPE_wxSizeEvent;
EventValueFactoryDeriv<Value_wxSizeEvent> Value_wxSizeEvent::eventValueFactory;

String Value_wxSizeEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SizeEvent");
}

Gurax_EndModuleScope(wx)
