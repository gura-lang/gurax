//==============================================================================
// VType_wxIconizeEvent.cpp
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

${help.ComposePropertyHelp(wxIconizeEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxIconizeEvent)}

${help.ComposeMethodHelp(wxIconizeEvent)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.IconizeEvent#IsIconized()
Gurax_DeclareMethodAlias(wxIconizeEvent, IsIconized_gurax, "IsIconized")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxIconizeEvent, IsIconized_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsIconized();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxIconizeEvent
//------------------------------------------------------------------------------
VType_wxIconizeEvent VTYPE_wxIconizeEvent("IconizeEvent");

void VType_wxIconizeEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxIconizeEvent, IsIconized_gurax));
}

//------------------------------------------------------------------------------
// Value_wxIconizeEvent
//------------------------------------------------------------------------------
VType& Value_wxIconizeEvent::vtype = VTYPE_wxIconizeEvent;
EventValueFactoryDeriv<Value_wxIconizeEvent> Value_wxIconizeEvent::eventValueFactory;

String Value_wxIconizeEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.IconizeEvent");
}

Gurax_EndModuleScope(wx)
