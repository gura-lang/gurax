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
// wx.EvtHandler#Bind()
Gurax_DeclareMethod(EvtHandler, Bind)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

class EventUserData : public wxObject {
public:
	
};

void HandlerFunc(wxEvent& event)
{
	event.GetEventUserData();
}

Gurax_ImplementMethod(EvtHandler, Bind)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	Int num = args.PickNumber<Int>();
	// Function body
	pEntity->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &HandlerFunc, wxID_EXIT, -1, new EventUserData());
	return new Value_Number(num * 3);
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
