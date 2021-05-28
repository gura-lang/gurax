//==============================================================================
// VType_wxTrackable.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTrackable
//------------------------------------------------------------------------------
VType_wxTrackable VTYPE_wxTrackable("Trackable");

void VType_wxTrackable::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(wxTrackable, Bind));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Trackable, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxTrackable
//------------------------------------------------------------------------------
VType& Value_wxTrackable::vtype = VTYPE_wxTrackable;

String Value_wxTrackable::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Trackable");
}

Gurax_EndModuleScope(wx)
