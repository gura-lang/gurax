//==============================================================================
// VType_EvtHandler.cpp
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
Gurax_DeclareConstructor(EvtHandler)
{
	Declare(VTYPE_EvtHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.EvtHandler` instance.");
}

Gurax_ImplementConstructor(EvtHandler)
{
	// Function body
	auto pEntity = new Value_EvtHandler::EntityT();
	RefPtr<Value_EvtHandler> pValue(new Value_EvtHandler(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.EvtHandler#Bind(eventType as wx.EventType, func as Function, id? as Number, lastId? as Number):void
Gurax_DeclareMethod(EvtHandler, Bind)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("eventType", VTYPE_EventType, ArgOccur::Once, ArgFlag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("lastId", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

class EventUserData : public wxObject {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunc;
public:
	EventUserData(Processor* pProcessor, Function* pFunc) : _pProcessor(pProcessor), _pFunc(pFunc) {}
public:
	void Eval(wxEvent& event) {
		Value::Delete(_pFunc->EvalEasy(*_pProcessor, new Value_Event(event.Clone())));
	}
};

void HandlerFunc(wxEvent& event)
{
	wxDynamicCast(event.GetEventUserData(), EventUserData)->Eval(event);
}

Gurax_ImplementMethod(EvtHandler, Bind)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	wxEventType eventType = args.Pick<Value_EventType>().GetEntity();
	Function& func = args.PickFunction();
	int id = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	int lastId = args.IsValid()? args.PickNumber<int>() : wxID_ANY;
	// Function body
	pEntity->Bind(eventType, &HandlerFunc, id, lastId, new EventUserData(processor.Reference(), func.Reference()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_EvtHandler
//------------------------------------------------------------------------------
VType_EvtHandler VTYPE_EvtHandler("EvtHandler");

void VType_EvtHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EvtHandler));
	// Assignment of method
	Assign(Gurax_CreateMethod(EvtHandler, Bind));
	// Assignment of property
	//Assign(Gurax_CreateProperty(EvtHandler, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_EvtHandler
//------------------------------------------------------------------------------
VType& Value_EvtHandler::vtype = VTYPE_EvtHandler;

String Value_EvtHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EvtHandler");
}

//------------------------------------------------------------------------------
// Value_EvtHandler::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
