//==============================================================================
// VType_wxEventType.cpp
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
// VType_wxEventType
//------------------------------------------------------------------------------
VType_wxEventType VTYPE_wxEventType("EventType");

void VType_wxEventType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	//Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EventType));
	// Assignment of method
	//Assign(Gurax_CreateMethod(EventType, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(EventType, propSkeleton));
	do {
		DeclCallable& d = GetDeclCallable();
		d.Declare(VTYPE_Nil, DeclCallable::Flag::None);
		d.DeclareArg("handler", VTYPE_wxEvtHandler, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("funct", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("userData", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
		d.DeclareArg("id", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
		d.DeclareArg("lastId", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	} while (0);
}

//------------------------------------------------------------------------------
// Value_wxEventType
//------------------------------------------------------------------------------
VType& Value_wxEventType::vtype = VTYPE_wxEventType;

String Value_wxEventType::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, String().Format("wx.EventType:%s", GetName()));
}

const DeclCallable* Value_wxEventType::GetDeclCallable()
{
	return &VTYPE_wxEventType.GetDeclCallable();
}

Value* Value_wxEventType::DoEval(Processor& processor, Argument& argument) const
{
	// Target
	wxEventType eventType = GetEntity();
	const EventValueFactory& eventValueFactory = GetEventValueFactory();
	// Arguments
	ArgPicker args(argument);
	wxEvtHandler* pEvtHandler = args.Pick<Value_wxEvtHandler>().GetEntityPtr();
	Value& valueFunct = args.PickValue();
	const Value& userData = args.IsValid()? args.PickValue() : Value::C_nil();
	int id = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	int lastId = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	// Function body
	pEvtHandler->Bind(eventType, &EventUserData::HandlerFunc, id, -1,
		new EventUserData(processor.Reference(), valueFunct.Reference(), userData.Reference(), eventValueFactory));
	return Value::nil();
}

Gurax_EndModuleScope(wx)
