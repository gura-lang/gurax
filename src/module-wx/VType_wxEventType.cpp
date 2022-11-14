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

${help.ComposePropertyHelp(wx.EventType, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.EventType, `en)}

${help.ComposeMethodHelp(wx.EventType, `en)}
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
// wx.EventType#name
Gurax_DeclareProperty_R(wxEventType, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxEventType, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetName());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// wx.EventType == wx.EventType
Gurax_ImplementOpBinary(Eq, wxEventType, wxEventType)
{
	wxEventType eventTypeL = Value_wxEventType::GetEntity(valueL);
	wxEventType eventTypeR = Value_wxEventType::GetEntity(valueR);
	return new Value_Bool(eventTypeL == eventTypeR);
}

// wx.EventType != wx.EventType
Gurax_ImplementOpBinary(Ne, wxEventType, wxEventType)
{
	wxEventType eventTypeL = Value_wxEventType::GetEntity(valueL);
	wxEventType eventTypeR = Value_wxEventType::GetEntity(valueR);
	return new Value_Bool(eventTypeL != eventTypeR);
}

//------------------------------------------------------------------------------
// VType_wxEventType
//------------------------------------------------------------------------------
VType_wxEventType VTYPE_wxEventType("EventType");

void VType_wxEventType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	//Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EventType));
	// Assignment of method
	//Assign(Gurax_CreateMethod(EventType, OnInit));
	// Assignment of property
	Assign(Gurax_CreateProperty(wxEventType, name));
	do {
		DeclCallable& d = GetDeclCallable();
		d.Declare(VTYPE_Nil, DeclCallable::Flag::None);
		d.DeclareArg("handler", VTYPE_wxEvtHandler, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("funct", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
		d.DeclareArg("userData", VTYPE_Any, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
		d.DeclareArg("id", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
		d.DeclareArg("lastId", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	} while (0);
	// Assignment of operator
	Gurax_AssignOpBinary(Eq,	wxEventType, wxEventType);
	Gurax_AssignOpBinary(Ne,	wxEventType, wxEventType);
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
