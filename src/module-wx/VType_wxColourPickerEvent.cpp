//==============================================================================
// VType_wxColourPickerEvent.cpp
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
// VType_wxColourPickerEvent
//------------------------------------------------------------------------------
VType_wxColourPickerEvent VTYPE_wxColourPickerEvent("ColourPickerEvent");

void VType_wxColourPickerEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxColourPickerEvent
//------------------------------------------------------------------------------
VType& Value_wxColourPickerEvent::vtype = VTYPE_wxColourPickerEvent;
EventValueFactoryDeriv<Value_wxColourPickerEvent> Value_wxColourPickerEvent::eventValueFactory;

String Value_wxColourPickerEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourPickerEvent");
}

Gurax_EndModuleScope(wx)
