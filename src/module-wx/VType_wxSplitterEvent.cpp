//==============================================================================
// VType_wxSplitterEvent.cpp
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

${help.ComposePropertyHelp(wx.SplitterEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SplitterEvent, `en)}

${help.ComposeMethodHelp(wx.SplitterEvent, `en)}
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
// VType_wxSplitterEvent
//------------------------------------------------------------------------------
VType_wxSplitterEvent VTYPE_wxSplitterEvent("SplitterEvent");

void VType_wxSplitterEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSplitterEvent
//------------------------------------------------------------------------------
VType& Value_wxSplitterEvent::vtype = VTYPE_wxSplitterEvent;
EventValueFactoryDeriv<Value_wxSplitterEvent> Value_wxSplitterEvent::eventValueFactory;

String Value_wxSplitterEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SplitterEvent");
}

Gurax_EndModuleScope(wx)
