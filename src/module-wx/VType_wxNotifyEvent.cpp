//==============================================================================
// VType_wxNotifyEvent.cpp
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

${help.ComposePropertyHelp(wxNotifyEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxNotifyEvent, `en)}

${help.ComposeMethodHelp(wxNotifyEvent, `en)}
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
// VType_wxNotifyEvent
//------------------------------------------------------------------------------
VType_wxNotifyEvent VTYPE_wxNotifyEvent("NotifyEvent");

void VType_wxNotifyEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxNotifyEvent
//------------------------------------------------------------------------------
VType& Value_wxNotifyEvent::vtype = VTYPE_wxNotifyEvent;
EventValueFactoryDeriv<Value_wxNotifyEvent> Value_wxNotifyEvent::eventValueFactory;

String Value_wxNotifyEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.NotifyEvent");
}

Gurax_EndModuleScope(wx)
