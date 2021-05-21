//==============================================================================
// VType_EventType.cpp
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
// VType_EventType
//------------------------------------------------------------------------------
VType_EventType VTYPE_EventType("EventType");

void VType_EventType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(Gurax::VTYPE_Object, Flag::Immutable);
	//Declare(Gurax::VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EventType));
	// Assignment of method
	//Assign(Gurax_CreateMethod(EventType, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(EventType, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_EventType
//------------------------------------------------------------------------------
VType& Value_EventType::vtype = VTYPE_EventType;

String Value_EventType::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EventType");
}

Gurax_EndModuleScope(wx)
