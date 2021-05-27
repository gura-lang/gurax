//==============================================================================
// VType_EventType.cpp
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
// VType_EventType
//------------------------------------------------------------------------------
VType_EventType VTYPE_EventType("EventType");

void VType_EventType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(Gurax::VTYPE_Object, Flag::Immutable);
	//Declare(Gurax::VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EventType));
	// Assignment of method
	//Assign(Gurax_CreateMethod(EventType, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(EventType, propSkeleton));
	do {
		DeclCallable& d = GetDeclCallable();
		d.Declare(VTYPE_Nil, DeclCallable::Flag::None);
		d.DeclareArg("handler", VTYPE_EvtHandler, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("id", VTYPE_Number, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("funct", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	} while (0);
}

//------------------------------------------------------------------------------
// Value_EventType
//------------------------------------------------------------------------------
VType& Value_EventType::vtype = VTYPE_EventType;

String Value_EventType::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EventType");
}

const DeclCallable* Value_EventType::GetDeclCallable()
{
	return &VTYPE_EventType.GetDeclCallable();
}

Value* Value_EventType::DoEval(Processor& processor, Argument& argument) const
{
	// Target
	wxEventType eventType = GetEntity();
	const EventValueFactory& eventValueFactory = GetEventValueFactory();
	// Arguments
	ArgPicker args(argument);
	wxEvtHandler* pEvtHandler = args.Pick<Value_EvtHandler>().GetEntity();
	int id = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	Value& valueFunct = args.PickValue();
	// Function body
	pEvtHandler->Bind(eventType, &EventUserData::HandlerFunc, id, -1,
		new EventUserData(processor.Reference(), valueFunct.Reference(), Value::nil(), eventValueFactory));
	return Value::nil();
}

Gurax_EndModuleScope(wx)
