//==============================================================================
// VType_wxSpinEvent.cpp
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

${help.ComposePropertyHelp(wxSpinEvent)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxSpinEvent)}

${help.ComposeMethodHelp(wxSpinEvent)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SpinEvent#GetPosition()
Gurax_DeclareMethodAlias(wxSpinEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinEvent#SetPosition(pos as Number)
Gurax_DeclareMethodAlias(wxSpinEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinEvent, SetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pos = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetPosition(pos);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSpinEvent
//------------------------------------------------------------------------------
VType_wxSpinEvent VTYPE_wxSpinEvent("SpinEvent");

void VType_wxSpinEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSpinEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxSpinEvent, SetPosition_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSpinEvent
//------------------------------------------------------------------------------
VType& Value_wxSpinEvent::vtype = VTYPE_wxSpinEvent;
EventValueFactoryDeriv<Value_wxSpinEvent> Value_wxSpinEvent::eventValueFactory;

String Value_wxSpinEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SpinEvent");
}

Gurax_EndModuleScope(wx)
