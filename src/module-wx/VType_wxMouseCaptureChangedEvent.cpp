//==============================================================================
// VType_wxMouseCaptureChangedEvent.cpp
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

${help.ComposePropertyHelp(wx.MouseCaptureChangedEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MouseCaptureChangedEvent, `en)}

${help.ComposeMethodHelp(wx.MouseCaptureChangedEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MouseCaptureChangedEvent#GetCapturedWindow() {block?}
Gurax_DeclareMethodAlias(wxMouseCaptureChangedEvent, GetCapturedWindow_gurax, "GetCapturedWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxMouseCaptureChangedEvent, GetCapturedWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetCapturedWindow()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
VType_wxMouseCaptureChangedEvent VTYPE_wxMouseCaptureChangedEvent("MouseCaptureChangedEvent");

void VType_wxMouseCaptureChangedEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMouseCaptureChangedEvent, GetCapturedWindow_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMouseCaptureChangedEvent
//------------------------------------------------------------------------------
VType& Value_wxMouseCaptureChangedEvent::vtype = VTYPE_wxMouseCaptureChangedEvent;
EventValueFactoryDeriv<Value_wxMouseCaptureChangedEvent> Value_wxMouseCaptureChangedEvent::eventValueFactory;

String Value_wxMouseCaptureChangedEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MouseCaptureChangedEvent");
}

Gurax_EndModuleScope(wx)
