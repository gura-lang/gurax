//==============================================================================
// VType_wxEvent.cpp
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
// VType_wxEvent
//------------------------------------------------------------------------------
VType_wxEvent VTYPE_wxEvent("Event");

void VType_wxEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Event, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Event, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxEvent
//------------------------------------------------------------------------------
VType& Value_wxEvent::vtype = VTYPE_wxEvent;

String Value_wxEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Event");
}

Gurax_EndModuleScope(wx)
