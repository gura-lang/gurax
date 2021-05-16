//==============================================================================
// VType_Event.cpp
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
// VType_Event
//------------------------------------------------------------------------------
VType_Event VTYPE_Event("Event");

void VType_Event::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(Gurax::VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Event, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Event, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Event
//------------------------------------------------------------------------------
VType& Value_Event::vtype = VTYPE_Event;

String Value_Event::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Event");
}

Gurax_EndModuleScope(wx)
