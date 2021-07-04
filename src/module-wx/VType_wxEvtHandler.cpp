//==============================================================================
// VType_wxEvtHandler.cpp
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
// wx.EvtHandler() {block?}
Gurax_DeclareConstructorAlias(EvtHandler_gurax, "EvtHandler")
{
	Declare(VTYPE_wxEvtHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.EvtHandler.");
}

Gurax_ImplementConstructorEx(EvtHandler_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxEvtHandler::EntityT();
	RefPtr<Value_wxEvtHandler> pValue_gurax(new Value_wxEvtHandler(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.EvtHandler#Bind(eventType as wxEventType, funct as Any, userData? as Any, id? as Number, lastId? as Number)
Gurax_DeclareMethodAlias(wxEvtHandler, Bind_gurax, "Bind")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("eventType", VTYPE_wxEventType, ArgOccur::Once, ArgFlag::None);
	DeclareArg("funct", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("userData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("lastId", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEvtHandler, Bind_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxEventType& value_eventType = args_gurax.Pick<Value_wxEventType>();
	wxEventType eventType = value_eventType.GetEntity();
	const Gurax::Value& funct = args_gurax.PickValue();
	const Gurax::Value& userData = args_gurax.IsValid()? args_gurax.PickValue() : Value::C_nil();
	int id = args_gurax.IsValid()? args_gurax.PickNumber<int>() : wxID_ANY;
	int lastId = args_gurax.IsValid()? args_gurax.PickNumber<int>() : wxID_ANY;
	// Function body
	const EventValueFactory& eventValueFactory = value_eventType.GetEventValueFactory();
	pEntity_gurax->Bind(eventType, &EventUserData::HandlerFunc, id, lastId,
		new EventUserData(processor_gurax.Reference(), funct.Reference(), userData.Reference(), eventValueFactory));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxEvtHandler
//------------------------------------------------------------------------------
VType_wxEvtHandler VTYPE_wxEvtHandler("EvtHandler");

void VType_wxEvtHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EvtHandler_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxEvtHandler, Bind_gurax));
}

//------------------------------------------------------------------------------
// Value_wxEvtHandler
//------------------------------------------------------------------------------
VType& Value_wxEvtHandler::vtype = VTYPE_wxEvtHandler;

String Value_wxEvtHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EvtHandler");
}

//------------------------------------------------------------------------------
// Value_wxEvtHandler::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
