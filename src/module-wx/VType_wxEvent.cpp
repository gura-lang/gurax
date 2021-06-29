//==============================================================================
// VType_wxEvent.cpp
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
// wx.Event#GetEventType()
Gurax_DeclareMethodAlias(wxEvent, GetEventType_gurax, "GetEventType")
{
	Declare(VTYPE_wxEventType, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetEventType_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return LookupEventType(pEntity_gurax->GetEventType()).Reference();
}

// wx.Event#GetEventCategory()
Gurax_DeclareMethodAlias(wxEvent, GetEventCategory_gurax, "GetEventCategory")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetEventCategory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxEventCategory rtn = pEntity_gurax->GetEventCategory();
	return new Gurax::Value_Number(rtn);
}

// wx.Event#GetId()
Gurax_DeclareMethodAlias(wxEvent, GetId_gurax, "GetId")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetId();
	return new Gurax::Value_Number(rtn);
}

// wx.Event#GetEventUserData()
Gurax_DeclareMethodAlias(wxEvent, GetEventUserData_gurax, "GetEventUserData")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetEventUserData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return valueThis_gurax.GetValueUserData().Reference();
}

// wx.Event#GetSkipped()
Gurax_DeclareMethodAlias(wxEvent, GetSkipped_gurax, "GetSkipped")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetSkipped_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetSkipped();
	return new Gurax::Value_Bool(rtn);
}

// wx.Event#GetTimestamp()
Gurax_DeclareMethodAlias(wxEvent, GetTimestamp_gurax, "GetTimestamp")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, GetTimestamp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetTimestamp();
	return new Gurax::Value_Number(rtn);
}

// wx.Event#IsCommandEvent()
Gurax_DeclareMethodAlias(wxEvent, IsCommandEvent_gurax, "IsCommandEvent")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, IsCommandEvent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsCommandEvent();
	return new Gurax::Value_Bool(rtn);
}

// wx.Event#ResumePropagation(propagationLevel as Number)
Gurax_DeclareMethodAlias(wxEvent, ResumePropagation_gurax, "ResumePropagation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("propagationLevel", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, ResumePropagation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int propagationLevel = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ResumePropagation(propagationLevel);
	return Gurax::Value::nil();
}

// wx.Event#SetId(id as Number)
Gurax_DeclareMethodAlias(wxEvent, SetId_gurax, "SetId")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, SetId_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int id = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetId(id);
	return Gurax::Value::nil();
}

// wx.Event#SetTimestamp(timeStamp? as Number)
Gurax_DeclareMethodAlias(wxEvent, SetTimestamp_gurax, "SetTimestamp")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("timeStamp", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, SetTimestamp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long timeStamp = args_gurax.IsValid()? args_gurax.PickNumber<long>() : 0;
	// Function body
	pEntity_gurax->SetTimestamp(timeStamp);
	return Gurax::Value::nil();
}

// wx.Event#ShouldPropagate()
Gurax_DeclareMethodAlias(wxEvent, ShouldPropagate_gurax, "ShouldPropagate")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, ShouldPropagate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ShouldPropagate();
	return new Gurax::Value_Bool(rtn);
}

// wx.Event#Skip(skip? as Bool)
Gurax_DeclareMethodAlias(wxEvent, Skip_gurax, "Skip")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("skip", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, Skip_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool skip = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Skip(skip);
	return Gurax::Value::nil();
}

// wx.Event#StopPropagation()
Gurax_DeclareMethodAlias(wxEvent, StopPropagation_gurax, "StopPropagation")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvent, StopPropagation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->StopPropagation();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxEvent
//------------------------------------------------------------------------------
VType_wxEvent VTYPE_wxEvent("Event");

void VType_wxEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxEvent, GetEventType_gurax));
	Assign(Gurax_CreateMethod(wxEvent, GetEventCategory_gurax));
	Assign(Gurax_CreateMethod(wxEvent, GetId_gurax));
	Assign(Gurax_CreateMethod(wxEvent, GetEventUserData_gurax));
	Assign(Gurax_CreateMethod(wxEvent, GetSkipped_gurax));
	Assign(Gurax_CreateMethod(wxEvent, GetTimestamp_gurax));
	Assign(Gurax_CreateMethod(wxEvent, IsCommandEvent_gurax));
	Assign(Gurax_CreateMethod(wxEvent, ResumePropagation_gurax));
	Assign(Gurax_CreateMethod(wxEvent, SetId_gurax));
	Assign(Gurax_CreateMethod(wxEvent, SetTimestamp_gurax));
	Assign(Gurax_CreateMethod(wxEvent, ShouldPropagate_gurax));
	Assign(Gurax_CreateMethod(wxEvent, Skip_gurax));
	Assign(Gurax_CreateMethod(wxEvent, StopPropagation_gurax));
}

//------------------------------------------------------------------------------
// Value_wxEvent
//------------------------------------------------------------------------------
VType& Value_wxEvent::vtype = VTYPE_wxEvent;

String Value_wxEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Event");
}

Gurax_EndModuleScope(wx)
