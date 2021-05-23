//==============================================================================
// VType_CommandEvent.cpp
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
// VType_CommandEvent
//------------------------------------------------------------------------------
VType_CommandEvent VTYPE_CommandEvent("CommandEvent");

void VType_CommandEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(Gurax::VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(CommandEvent, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(CommandEvent, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_CommandEvent
//------------------------------------------------------------------------------
VType& Value_CommandEvent::vtype = VTYPE_CommandEvent;
//EventValueFactoryDeriv<Value_CommandEvent> Value_CommandEvent::eventValueFactory;

String Value_CommandEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CommandEvent");
}

Gurax_EndModuleScope(wx)
