//==============================================================================
// VType_wxCloseEvent.cpp
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
// wx.CloseEvent#CanVeto()
Gurax_DeclareMethodAlias(wxCloseEvent, CanVeto_gurax, "CanVeto")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, CanVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->CanVeto();
	return new Gurax::Value_Bool(rtn);
}

// wx.CloseEvent#GetLoggingOff()
Gurax_DeclareMethodAlias(wxCloseEvent, GetLoggingOff_gurax, "GetLoggingOff")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, GetLoggingOff_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetLoggingOff();
	return new Gurax::Value_Bool(rtn);
}

// wx.CloseEvent#SetCanVeto(canVeto as Bool)
Gurax_DeclareMethodAlias(wxCloseEvent, SetCanVeto_gurax, "SetCanVeto")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("canVeto", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, SetCanVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool canVeto = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetCanVeto(canVeto);
	return Gurax::Value::nil();
}

// wx.CloseEvent#SetLoggingOff(loggingOff as Bool)
Gurax_DeclareMethodAlias(wxCloseEvent, SetLoggingOff_gurax, "SetLoggingOff")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("loggingOff", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, SetLoggingOff_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool loggingOff = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetLoggingOff(loggingOff);
	return Gurax::Value::nil();
}

// wx.CloseEvent#Veto(veto? as Bool)
Gurax_DeclareMethodAlias(wxCloseEvent, Veto_gurax, "Veto")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("veto", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, Veto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool veto = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Veto(veto);
	return Gurax::Value::nil();
}

// wx.CloseEvent#GetVeto()
Gurax_DeclareMethodAlias(wxCloseEvent, GetVeto_gurax, "GetVeto")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCloseEvent, GetVeto_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetVeto();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCloseEvent
//------------------------------------------------------------------------------
VType_wxCloseEvent VTYPE_wxCloseEvent("CloseEvent");

void VType_wxCloseEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCloseEvent, CanVeto_gurax));
	Assign(Gurax_CreateMethod(wxCloseEvent, GetLoggingOff_gurax));
	Assign(Gurax_CreateMethod(wxCloseEvent, SetCanVeto_gurax));
	Assign(Gurax_CreateMethod(wxCloseEvent, SetLoggingOff_gurax));
	Assign(Gurax_CreateMethod(wxCloseEvent, Veto_gurax));
	Assign(Gurax_CreateMethod(wxCloseEvent, GetVeto_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCloseEvent
//------------------------------------------------------------------------------
VType& Value_wxCloseEvent::vtype = VTYPE_wxCloseEvent;
EventValueFactoryDeriv<Value_wxCloseEvent> Value_wxCloseEvent::eventValueFactory;

String Value_wxCloseEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CloseEvent");
}

Gurax_EndModuleScope(wx)
