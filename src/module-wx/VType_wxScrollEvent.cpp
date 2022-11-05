//==============================================================================
// VType_wxScrollEvent.cpp
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

${help.ComposePropertyHelp(wxScrollEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxScrollEvent, `en)}

${help.ComposeMethodHelp(wxScrollEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ScrollEvent#GetOrientation()
Gurax_DeclareMethodAlias(wxScrollEvent, GetOrientation_gurax, "GetOrientation")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrollEvent, GetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetOrientation();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrollEvent#GetPosition()
Gurax_DeclareMethodAlias(wxScrollEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrollEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetPosition();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrollEvent#SetOrientation(orient as Number)
Gurax_DeclareMethodAlias(wxScrollEvent, SetOrientation_gurax, "SetOrientation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrollEvent, SetOrientation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetOrientation(orient);
	return Gurax::Value::nil();
}

// wx.ScrollEvent#SetPosition(pos as Number)
Gurax_DeclareMethodAlias(wxScrollEvent, SetPosition_gurax, "SetPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrollEvent, SetPosition_gurax, processor_gurax, argument_gurax)
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
// VType_wxScrollEvent
//------------------------------------------------------------------------------
VType_wxScrollEvent VTYPE_wxScrollEvent("ScrollEvent");

void VType_wxScrollEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxScrollEvent, GetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxScrollEvent, GetPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrollEvent, SetOrientation_gurax));
	Assign(Gurax_CreateMethod(wxScrollEvent, SetPosition_gurax));
}

//------------------------------------------------------------------------------
// Value_wxScrollEvent
//------------------------------------------------------------------------------
VType& Value_wxScrollEvent::vtype = VTYPE_wxScrollEvent;
EventValueFactoryDeriv<Value_wxScrollEvent> Value_wxScrollEvent::eventValueFactory;

String Value_wxScrollEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ScrollEvent");
}

Gurax_EndModuleScope(wx)
