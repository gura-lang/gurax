//==============================================================================
// VType_wxProcessEvent.cpp
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

${help.ComposePropertyHelp(wxProcessEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxProcessEvent)}

${help.ComposeMethodHelp(wxProcessEvent)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ProcessEvent#GetExitCode()
Gurax_DeclareMethodAlias(wxProcessEvent, GetExitCode_gurax, "GetExitCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxProcessEvent, GetExitCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetExitCode();
	return new Gurax::Value_Number(rtn);
}

// wx.ProcessEvent#GetPid()
Gurax_DeclareMethodAlias(wxProcessEvent, GetPid_gurax, "GetPid")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxProcessEvent, GetPid_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPid();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxProcessEvent
//------------------------------------------------------------------------------
VType_wxProcessEvent VTYPE_wxProcessEvent("ProcessEvent");

void VType_wxProcessEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxProcessEvent, GetExitCode_gurax));
	Assign(Gurax_CreateMethod(wxProcessEvent, GetPid_gurax));
}

//------------------------------------------------------------------------------
// Value_wxProcessEvent
//------------------------------------------------------------------------------
VType& Value_wxProcessEvent::vtype = VTYPE_wxProcessEvent;
EventValueFactoryDeriv<Value_wxProcessEvent> Value_wxProcessEvent::eventValueFactory;

String Value_wxProcessEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ProcessEvent");
}

Gurax_EndModuleScope(wx)
