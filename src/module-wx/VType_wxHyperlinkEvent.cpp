//==============================================================================
// VType_wxHyperlinkEvent.cpp
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
// VType_wxHyperlinkEvent
//------------------------------------------------------------------------------
VType_wxHyperlinkEvent VTYPE_wxHyperlinkEvent("HyperlinkEvent");

void VType_wxHyperlinkEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxHyperlinkEvent
//------------------------------------------------------------------------------
VType& Value_wxHyperlinkEvent::vtype = VTYPE_wxHyperlinkEvent;
EventValueFactoryDeriv<Value_wxHyperlinkEvent> Value_wxHyperlinkEvent::eventValueFactory;

String Value_wxHyperlinkEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HyperlinkEvent");
}

Gurax_EndModuleScope(wx)